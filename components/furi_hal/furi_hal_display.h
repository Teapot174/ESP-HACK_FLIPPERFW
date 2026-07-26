/**
 * @file furi_hal_display.h
 * Board-independent display HAL API (color esp_lcd or monochrome SH1106).
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <esp_lcd_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Initialize board display hardware.
 */
void furi_hal_display_init(void);

/** Commit display buffer to screen
 *
 * Sends the u8g2 mono framebuffer directly to monochrome targets or converts
 * it to RGB565 with aspect-fit scaling for color targets.
 *
 * @param      data  pointer to u8g2 framebuffer data
 * @param      size  size of framebuffer data in bytes
 */
void furi_hal_display_commit(const uint8_t* data, uint32_t size);

/** Set display backlight brightness
 *
 * @param      brightness  brightness level [0-255]
 */
void furi_hal_display_set_backlight(uint8_t brightness);

/** Put the display panel into sleep mode.
 *
 * Intended for the power-off / deep-sleep path: the panel keeps drawing
 * ~10-15 mA while idle otherwise. Safe to call without holding the SPI bus
 * lock — it grabs the lock internally.
 */
void furi_hal_display_sleep(void);

/** Set the UI foreground color (the tint that fills the "ink" of every
 * monochrome u8g2 frame on color ports). Stored as RGB565 on color targets;
 * monochrome targets retain the value for API compatibility.
 *
 * Takes effect on the next frame commit (no full redraw needed).
 *
 * @param      color  RGB565 (byte-swapped) color value
 */
void furi_hal_display_set_fg_color(uint16_t color);

/** Get the current UI foreground color (RGB565 on color targets). Useful for
 * spectrum/animation drivers that need to derive the next frame's color.
 */
uint16_t furi_hal_display_get_fg_color(void);

/** Set/get the UI background color — fills the "set" mono pixels (the drawn
 * UI elements). Default is BOARD_LCD_BG_COLOR (typically black). Pairs with
 * fg_color to give the user full control of the bichromatic UI palette. */
void furi_hal_display_set_bg_color(uint16_t color);
uint16_t furi_hal_display_get_bg_color(void);

/** Get native panel dimensions (post swap_xy). Intended for full-screen
 * takeover apps (e.g. game emulators) that bypass the 128x64 framebuffer.
 */
uint16_t furi_hal_display_get_h_res(void);
uint16_t furi_hal_display_get_v_res(void);

/** Get the underlying esp_lcd panel handle for direct full-screen drawing.
 *
 * The returned handle must only be used while the caller holds the SPI bus
 * lock (furi_hal_spi_bus_lock) and has acquired fullscreen access via the
 * GUI service (gui_direct_draw_acquire). The Furi GUI HAL keeps rendering
 * its 128x64 framebuffer, so callers that do not pause the GUI will flicker.
 * Returns NULL for displays which are not managed by esp_lcd (for example SH1106).
 */
esp_lcd_panel_handle_t furi_hal_display_get_panel_handle(void);

#ifdef __cplusplus
}
#endif

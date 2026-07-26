/**
 * @file board_esp32_wroom_sh1106.h
 * DIY ESP32-WROOM-32 + SH1106 128x64 board definition.
 */

#pragma once

/* ---- Board metadata ---- */
#define BOARD_NAME   "ESP32-WROOM SH1106"
#define BOARD_TARGET "esp32"

/* ---- Four active-low buttons ---- */
#define BOARD_PIN_BUTTON_UP   27
#define BOARD_PIN_BUTTON_DOWN 26
#define BOARD_PIN_BUTTON_OK   33
#define BOARD_PIN_BUTTON_BACK 32
#define BOARD_PIN_BUTTON_BOOT BOARD_PIN_BUTTON_BACK
#define BOARD_PIN_BATTERY_ADC UINT16_MAX

/* ---- SH1106 OLED (I2C) ---- */
#define BOARD_DISPLAY_SH1106        1
#define BOARD_DISPLAY_I2C_PORT      I2C_NUM_0
#define BOARD_DISPLAY_I2C_ADDR      0x3C
#define BOARD_DISPLAY_I2C_FREQ_HZ   400000
#define BOARD_PIN_DISPLAY_SCL       22
#define BOARD_PIN_DISPLAY_SDA       21
#define BOARD_PIN_DISPLAY_RST       -1
#define BOARD_LCD_H_RES             128
#define BOARD_LCD_V_RES             64
#define BOARD_LCD_FG_COLOR          0xFFFF
#define BOARD_LCD_BG_COLOR          0x0000
#define BOARD_HAS_DISPLAY_BACKLIGHT 0

/* Compatibility resources: this display does not use SPI/control/backlight pins. */
#define BOARD_PIN_LCD_MOSI UINT16_MAX
#define BOARD_PIN_LCD_SCLK UINT16_MAX
#define BOARD_PIN_LCD_DC   UINT16_MAX
#define BOARD_PIN_LCD_CS   UINT16_MAX
#define BOARD_PIN_LCD_RST  UINT16_MAX
#define BOARD_PIN_LCD_BL   UINT16_MAX
#define BOARD_LCD_BL_ACTIVE_LOW false

/* ---- SD card (dedicated SPI2 bus) ---- */
#define BOARD_PIN_SD_CS   15
#define BOARD_PIN_SD_MOSI 13
#define BOARD_PIN_SD_SCLK 14
#define BOARD_PIN_SD_MISO 17

/* ---- CC1101 (independent software SPI) ---- */
#define BOARD_PIN_CC1101_GDO0 4
#define BOARD_PIN_CC1101_CSN  5
#define BOARD_PIN_CC1101_SCK  18
#define BOARD_PIN_CC1101_MOSI 23
#define BOARD_PIN_CC1101_MISO 19
#define BOARD_CC1101_SPI_SHARED 0

/* ---- Infrared ---- */
#define BOARD_PIN_IR_TX 16
#define BOARD_PIN_IR_RX 35

/* ---- Unused touch resources ---- */
#define BOARD_PIN_TOUCH_SCL     UINT16_MAX
#define BOARD_PIN_TOUCH_SDA     UINT16_MAX
#define BOARD_PIN_TOUCH_RST     UINT16_MAX
#define BOARD_PIN_TOUCH_INT     UINT16_MAX
#define BOARD_TOUCH_I2C_ADDR    0
#define BOARD_TOUCH_I2C_PORT    I2C_NUM_0
#define BOARD_TOUCH_I2C_FREQ_HZ 0
#define BOARD_TOUCH_I2C_TIMEOUT 0

/* ---- Features ---- */
#define BOARD_HAS_TOUCH   0
#define BOARD_HAS_ENCODER 0
#define BOARD_HAS_SD_CARD 1
#define BOARD_HAS_BLE     1
#define BOARD_HAS_RGB_LED 0
#define BOARD_HAS_VIBRO   0
#define BOARD_HAS_SPEAKER 0
#define BOARD_HAS_IR      1
#define BOARD_HAS_IBUTTON 0
#define BOARD_HAS_RFID    0
#define BOARD_HAS_NFC     0
#define BOARD_HAS_SUBGHZ  1
#define BOARD_HAS_NRF24   0
#define BOARD_HAS_MIC     0

/* Power service fallbacks (there is no fuel gauge/charger on this board). */
#define BQ27220_ADDR                        0x55
#define BQ25896_CHARGE_LIMIT                1280
#define FURI_HAL_POWER_VIRTUAL_CAPACITY_MAH (1300U)

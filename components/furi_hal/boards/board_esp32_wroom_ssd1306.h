/** ESP32-WROOM-32 + SSD1306 128x64 OLED board definition. */
#pragma once

/* Pinout, storage and peripheral capabilities are identical to the SH1106
 * WROOM board; only the display controller changes. */
#include "board_esp32_wroom_sh1106.h"

#undef BOARD_NAME
#undef BOARD_DISPLAY_SH1106
#define BOARD_NAME "ESP32-WROOM SSD1306"
#define BOARD_DISPLAY_SSD1306 1

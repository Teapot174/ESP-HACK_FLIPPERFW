/**
 * @file target_input.c
 * Four active-low GPIO buttons for the ESP32-WROOM SH1106 target.
 */

#include "target_input.h"

#include <boards/board.h>
#include <driver/gpio.h>
#include <esp_err.h>

#define TAG                   "InputButtons4"
#define INPUT_DEBOUNCE_POLLS  2U
#define INPUT_LONG_PRESS_MS   500U
#define INPUT_REPEAT_MS       200U
#define NUM_BUTTONS           4U

typedef struct {
    gpio_num_t gpio;
    InputKey key;
    bool raw_pressed;
    bool pressed;
    uint8_t debounce_polls;
    uint32_t press_started_at;
    uint32_t last_repeat_at;
    bool long_press_sent;
} ButtonState;

static ButtonState buttons[NUM_BUTTONS];

static void input_publish(FuriPubSub* pubsub, InputKey key, InputType type, uint32_t sequence) {
    InputEvent event = {
        .sequence_source = INPUT_SEQUENCE_SOURCE_HARDWARE,
        .sequence_counter = sequence,
        .key = key,
        .type = type,
    };
    furi_pubsub_publish(pubsub, &event);
}

static bool button_read(const ButtonState* button) {
    return gpio_get_level(button->gpio) == 0;
}

static void button_poll(ButtonState* button, FuriPubSub* pubsub, uint32_t now, uint32_t* sequence) {
    const bool raw = button_read(button);
    if(raw == button->raw_pressed) {
        if(button->debounce_polls < INPUT_DEBOUNCE_POLLS) button->debounce_polls++;
    } else {
        button->raw_pressed = raw;
        button->debounce_polls = 1;
    }

    if(button->debounce_polls < INPUT_DEBOUNCE_POLLS) return;

    if(button->pressed != raw) {
        button->pressed = raw;
        if(raw) {
            button->press_started_at = now;
            button->last_repeat_at = now;
            button->long_press_sent = false;
            input_publish(pubsub, button->key, InputTypePress, ++(*sequence));
        } else {
            if(!button->long_press_sent) {
                input_publish(pubsub, button->key, InputTypeShort, *sequence);
            }
            input_publish(pubsub, button->key, InputTypeRelease, *sequence);
        }
        return;
    }

    if(!button->pressed) return;
    if(!button->long_press_sent &&
       now - button->press_started_at >= furi_ms_to_ticks(INPUT_LONG_PRESS_MS)) {
        button->long_press_sent = true;
        button->last_repeat_at = now;
        input_publish(pubsub, button->key, InputTypeLong, *sequence);
    } else if(button->long_press_sent &&
              now - button->last_repeat_at >= furi_ms_to_ticks(INPUT_REPEAT_MS)) {
        button->last_repeat_at = now;
        input_publish(pubsub, button->key, InputTypeRepeat, *sequence);
    }
}

void target_input_init(void) {
    const struct {
        gpio_num_t gpio;
        InputKey key;
    } config[NUM_BUTTONS] = {
        {(gpio_num_t)BOARD_PIN_BUTTON_UP, InputKeyUp},
        {(gpio_num_t)BOARD_PIN_BUTTON_DOWN, InputKeyDown},
        {(gpio_num_t)BOARD_PIN_BUTTON_OK, InputKeyOk},
        {(gpio_num_t)BOARD_PIN_BUTTON_BACK, InputKeyBack},
    };

    for(size_t i = 0; i < NUM_BUTTONS; i++) {
        gpio_config_t gpio_config_data = {
            .pin_bit_mask = 1ULL << config[i].gpio,
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_ENABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE,
        };
        ESP_ERROR_CHECK(gpio_config(&gpio_config_data));

        buttons[i].gpio = config[i].gpio;
        buttons[i].key = config[i].key;
        buttons[i].raw_pressed = gpio_get_level(config[i].gpio) == 0;
        buttons[i].pressed = buttons[i].raw_pressed;
        buttons[i].debounce_polls = INPUT_DEBOUNCE_POLLS;
    }
}

void target_input_poll(FuriPubSub* pubsub, uint32_t* sequence_counter) {
    const uint32_t now = furi_get_tick();
    for(size_t i = 0; i < NUM_BUTTONS; i++) {
        button_poll(&buttons[i], pubsub, now, sequence_counter);
    }
}

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

#define LEDS_NUM 3

#define LED0_NODE DT_NODELABEL(led0_lcd)
#define LED1_NODE DT_NODELABEL(led1_lcd)
#define LED2_NODE DT_NODELABEL(led2_lcd)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0 DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN_LED0 DT_GPIO_PIN(LED0_NODE, gpios)
#endif

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
#define LED1 DT_GPIO_LABEL(LED1_NODE, gpios)
#define PIN_LED1 DT_GPIO_PIN(LED1_NODE, gpios)
#endif

#if DT_NODE_HAS_STATUS(LED2_NODE, okay)
#define LED2 DT_GPIO_LABEL(LED2_NODE, gpios)
#define PIN_LED2 DT_GPIO_PIN(LED2_NODE, gpios)
#endif

int main(void) {
#if defined PIN_LED0 && defined PIN_LED1 && defined PIN_LED2
    struct device *leds_dev[LEDS_NUM];
    uint8_t led_on_idx = 0;
    uint8_t last_led_on_idx = 0;
    gpio_pin_t led_pins[LEDS_NUM] = {PIN_LED0, PIN_LED1, PIN_LED2};

    for (uint8_t i = 0; i < LEDS_NUM; ++i) {
        leds_dev[i] = device_get_binding(LED0);
        if (leds_dev[i] == NULL)
            return -1;

        gpio_pin_configure(leds_dev[i], led_pins[i], GPIO_OUTPUT_ACTIVE);
    }

    while (1) {
        gpio_pin_set(leds_dev[last_led_on_idx], led_pins[last_led_on_idx], 0);
        gpio_pin_set(leds_dev[led_on_idx], led_pins[led_on_idx], 1);

        last_led_on_idx = led_on_idx;
        led_on_idx = (led_on_idx + 1) % LEDS_NUM;

        k_msleep(1000);
    }

    return 0;
#endif
}
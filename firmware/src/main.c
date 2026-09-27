#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define GPIO_SPEC(node_id, prop, idx)                                          \
    GPIO_DT_SPEC_GET_BY_IDX(node_id, prop, idx),

#define SWITCHES_NODE DT_PATH(switches)

static const struct gpio_dt_spec rows[] = {
    DT_FOREACH_PROP_ELEM(SWITCHES_NODE, row_gpios, GPIO_SPEC)};
static const struct gpio_dt_spec cols[] = {
    DT_FOREACH_PROP_ELEM(SWITCHES_NODE, col_gpios, GPIO_SPEC)};

int main(void) {
    for (int i = 0; i < ARRAY_SIZE(rows); i++) {
        if (!device_is_ready(rows[i].port)) {
            return 0;
        }
    }

    for (int i = 0; i < ARRAY_SIZE(cols); i++) {
        if (!device_is_ready(cols[i].port)) {
            return 0;
        }
    }

    for (int i = 0; i < ARRAY_SIZE(rows); i++) {
        gpio_pin_configure_dt(&rows[i],
                              GPIO_INPUT); // initialized as inactive for now
    }

    for (int i = 0; i < ARRAY_SIZE(cols); i++) {
        gpio_pin_configure_dt(&cols[i], GPIO_INPUT | GPIO_PULL_UP);
    }

    uint8_t raw_state;

    while (1) {
        raw_state = 0;

        for (int i = 0; i < ARRAY_SIZE(rows); i++) {
            for (int j = 0; j < ARRAY_SIZE(rows); j++) {
                if (i == j) {
                    gpio_pin_configure_dt(&rows[j], GPIO_OUTPUT_LOW);
                } else {
                    gpio_pin_configure_dt(&rows[j], GPIO_INPUT);
                }
            }

            k_busy_wait(10);

            for (int j = 0; j < ARRAY_SIZE(cols); j++) {
                if (gpio_pin_get_dt(&cols[j]) == 0) {
                    raw_state |= (1U << (i * ARRAY_SIZE(cols) + j));
                }
            }
        }

        for (int i = 7; i >= 0; i--) {
            printk("%d", (raw_state >> i) & 1);
        }

        printk("\n");

        for (int i = 0; i < ARRAY_SIZE(rows); i++) {
            gpio_pin_configure_dt(&rows[i],
                                  GPIO_INPUT); // inactivate outputs again
        }

        k_busy_wait(100000);
    }

    return 0;
}

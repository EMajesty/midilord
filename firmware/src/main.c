#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define SWITCHES_NODE DT_PATH(switches)

static const struct gpio_dt_spec r1 =
    GPIO_DT_SPEC_GET_BY_IDX(SWITCHES_NODE, row_gpios, 0);

int main(void) {
    device_is_ready(r1.port);
    while (1) {
        printk("R1: port=%s pin=%u flags=0x%x\n", r1.port->name, r1.pin,
               r1.dt_flags);
        k_sleep(K_SECONDS(1));
    }

    return 0;
}

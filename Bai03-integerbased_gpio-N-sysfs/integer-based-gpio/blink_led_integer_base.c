#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/gpio.h>

#define DRIVER_AUTHOR "wibu"
#define DRIVER_DESC   "Blinking Led"
#define GPIO_LED     31

static int __init Turn_on_led(void) {
    gpio_request(GPIO_LED, "led");
    gpio_direction_output(GPIO_LED, 0);
    gpio_set_value(GPIO_LED, 1);
    pr_info("Hello ae wibu\n");
    return 0;
}

static void __exit Turn_off_led(void) {
    gpio_set_value(GPIO_LED, 0);
    gpio_free(GPIO_LED);
}

module_init(Turn_on_led);
module_exit(Turn_off_led);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC); 
MODULE_VERSION("1.0"); 
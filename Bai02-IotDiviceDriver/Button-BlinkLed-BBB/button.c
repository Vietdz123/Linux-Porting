#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/delay.h>
#include "button.h"

#define DRIVER_AUTHOR "wibu-viet"
#define DRIVER_DESC   "Button Led"

uint32_t __iomem *base_addr;
uint32_t i = 0;

static int __init Turn_on_led(void) {
    base_addr = ioremap(GPIO_0_ADDRESS_BASE, GPIO_0_ADDRESS_SIZE);
    if (!base_addr)
		return -ENOMEM;

    *(base_addr + GPIO_OE_OFFSET / 4) &= ~GPIO_PIN_IN_14;
    *(base_addr + GPIO_OE_OFFSET / 4) &= GPIO_PIN_IN_14;          // set 1 is input
    if ((*(base_addr + GPIO_DATA_IN_OFFSET/4) & (0xFFFFBFFF)) == *(base_addr + GPIO_DATA_IN_OFFSET/4)) {
        pr_info("State Led Changed");
        
        if (i % 2 == 0) {
            *(base_addr + GPIO_SET_DATA_OUTPUT_OFFSET/4) |= GPIO_PIN_31;
            pr_info("Turn on Led\n");
        } else {
            *(base_addr + GPIO_CLEAR_DATA_OUTPUT_OFFSET/4) |= GPIO_PIN_31;
            pr_info("Turn off Led\n");
        }
        i++;
        
    }
    
    pr_info("Hello ae wibu\n");
	return 0;
}

static void __exit Turn_off_led(void) {
    *(base_addr + GPIO_CLEAR_DATA_OUTPUT_OFFSET/4) |= GPIO_PIN_31;
    iounmap(base_addr);
    pr_info("Goodbye ae wibu\n");
}

module_init(Turn_on_led);
module_exit(Turn_off_led);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC); 
MODULE_VERSION("1.0"); 
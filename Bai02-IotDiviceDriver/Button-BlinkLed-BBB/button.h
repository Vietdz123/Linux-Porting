#ifndef __BUTTON_H_
#define __BUTTON_H_

#define GPIO_0_ADDRESS_BASE              0x44E07000
#define GPIO_0_ADDRESS_SIZE              (0x44E07FFF - 0x44E07000)
#define GPIO_DATA_IN_OFFSET              0x138
#define GPIO_CLEAR_DATA_OUTPUT_OFFSET    0x190
#define GPIO_SET_DATA_OUTPUT_OFFSET      0x194
#define GPIO_OE_OFFSET                   0x134

#define GPIO_PIN_IN_14     (1<<14)
#define GPIO_PIN_31     (1<<31)

#endif
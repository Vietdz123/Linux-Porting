#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/irq.h>

#define IRQF_TRIGGER_NONE  0x00000000
#define IRQF_TRIGGER_RISING  0x00000001 Trigger on rising edge
#define IRQF_TRIGGER_FALLING  0x00000002 Trigger on falling edge
#define IRQF_TRIGGER_HIGH  0x00000004  Trigger on high level
#define IRQF_TRIGGER_LOW  0x00000008 Trigger on low level
#define IRQF_TRIGGER_MASK  (IRQF_TRIGGER_HIGH |IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING) //It seems that any signal triggers
#define IRQF_TRIGGER_PROBE  0x00000010

#define PIN_A_GPIO 30 //Set the interrupt pin to GPIO0_30
#define PIN_A_FLAGS GPIOF_IN
#define PIN_A_LABEL "HI_PIN_A"

#define PIN_LED_GPIO 31 // Set the output GPIO0_31

int k;
bool state=0;
static irqreturn_t irq_handler_pin_a(int irq, void *dev_id) //Interrupt handler
{
  printk (KERN_INFO "Hello from irq_handler_pin_a...%d state: %d \n",k,state);
  k++;
  if(state ==0) state =1;
  else state =0;
  gpio_set_value(PIN_LED_GPIO,state);
  return IRQ_HANDLED;
}

static int __init hello_interrupts_start(void) 
{
  int retval, irq, regval;
  printk (KERN_INFO "Loading hello_interrupts module...\n");
  
  retval = gpio_request_one(PIN_A_GPIO, PIN_A_FLAGS, PIN_A_LABEL);
  printk (KERN_INFO "HI: request GPIO pin#%i for IRQ (%i)\n", PIN_A_GPIO, retval);
  gpio_set_debounce(PIN_A_GPIO,20);
  gpio_direction_output(PIN_LED_GPIO, 0);
  
  irq = gpio_to_irq (PIN_A_GPIO);
  retval = request_irq (irq, irq_handler_pin_a, 1/*IRQF_TRIGGER_RISING */, PIN_A_LABEL, NULL);
  irq_set_irq_type ( irq, IRQ_TYPE_EDGE_BOTH);
 return 0;
}

static void __exit hello_interrupts_end(void)
 {
  printk ("HI: Releasing IRQ resources...\n");
  free_irq (gpio_to_irq (PIN_A_GPIO), NULL);
  gpio_free (PIN_A_GPIO);
  gpio_free (PIN_LED_GPIO);
}

module_init(hello_interrupts_start);
module_exit(hello_interrupts_end);


MODULE_AUTHOR("000");
MODULE_DESCRIPTION("A sample driver using interrupts");
MODULE_LICENSE("GPL");
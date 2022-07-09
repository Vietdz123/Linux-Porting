/******************************************************************************
*  @brief      GPIO sysfs driver (interger-based)
*
*  @author     Phonglt9 - phongxxxxx@gmail.com
*******************************************************************************/

#include <linux/module.h>  /* This module defines macro such as module_init/module_exit */
#include <linux/fs.h>      /* This module defines functions such as allocate major/minor number */
#include <linux/device.h>  /* This module defines functions such as class_create/device_create */
#include <linux/cdev.h>    /* This module defines functions such as kmalloc */
#include <linux/slab.h>    /* This module defines functions such as cdev_init/cdev_add */
#include <linux/uaccess.h> /* This module defines functions such as copy_to_user/copy_from_user */
#include <linux/string.h>  /* This module defines functions such as strncpy/strcmp */
#include <linux/gpio.h>    /* This module defines functions such as gpio_request/gpio_set_value */
#include <linux/io.h>

#define DRIVER_AUTHOR "Phonglt9 xxxxxxxx@gmail.com"
#define DRIVER_DESC   "GPIO sysfs driver (interger-based)"
#define IN "in"
#define OUT "out"
#define LED 31
#define BUTTON 14
static unsigned int GPIO_LED = 31;

static int32_t _value = 0;
static char _direct[8] = "in";

struct m_foo_dev {
    struct kobject *kobj_ref;
} mdev;

/*************** Function Prototypes *******************/
static int      __init hello_world_init(void);
static void     __exit hello_world_exit(void);

/***************** Sysfs functions *******************/
static ssize_t  value_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t  value_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);
static ssize_t  direction_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t  direction_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);

struct kobj_attribute value = __ATTR(value, 0660, value_show, value_store);
struct kobj_attribute direction = __ATTR(direction, 0660, direction_show, direction_store);

static ssize_t value_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)         //Hien thi gia tri thong qua bien buff
{
    int value;
    if (strcmp(IN, _direct) == 0) {
        pr_info("GPIO IN\n");
        value = gpio_get_value(BUTTON);
        sprintf(buf, "%d\n", value);
        pr_info("%s", buf);
        return value;
    }
    pr_info("GPIO OUT\n");
    value = sprintf(buf, "%d\n", _value);
    pr_info("%s", buf);
    return value;
}

static ssize_t value_store(struct kobject *kobj, struct kobj_attribute *attr,  const char *buf, size_t count)
{
    int32_t numb  = 0; 
    sscanf(buf, "%d", &numb);

    if (strcmp(IN, _direct) == 0) {
        return count;
    }

    switch (numb) {
        case 0: 
            gpio_set_value(LED, 0);
            break;
        case 1: 
            gpio_set_value(LED, 1);
            break;

        default:
            return count;
    }

    sscanf(buf, "%d", &_value);

    return count;
}

static ssize_t direction_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int count = sprintf(buf, "%s", _direct);
    pr_info("%s\n", _direct);
    return count;
}

static ssize_t direction_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    pr_info("User wrote: %s\n", buf);
    if (strncmp(IN, buf, count -1) == 0) {
        memset(_direct, 0, sizeof(_direct));
        strncpy(_direct, buf, count - 1);
        gpio_request(BUTTON, "Button");
        gpio_direction_input(BUTTON);
    
    } else if (strncmp(OUT, buf, count -1) == 0) {
        memset(_direct, 0, sizeof(_direct));
        strncpy(_direct, buf, count - 1);
        gpio_request(LED, "led");
        gpio_direction_output(LED, 0);
    
    } else {
        return count;
    }

    return count;
}

/* Initialize group attrs */
static struct attribute *attrs[] = {
    &direction.attr,
    &value.attr,
    NULL,
};

static struct attribute_group attr_group = {
    .attrs = attrs,
};

static int 
__init hello_world_init(void)   /* Constructor */
{   

    /* 01. It will create a directory under "/sys" , [firmware_kobj, class_kobj] */
    mdev.kobj_ref = kobject_create_and_add("bbb_gpios", NULL);

    /* 02. Creating group sys entry under "/sys/bbb_gpios/" */ 
    if (sysfs_create_group(mdev.kobj_ref, &attr_group)) {
        pr_err("Cannot create group atrributes......\n");
        goto rm_kobj;
    }

    /* 03. Request GPIO */ 

    pr_info("Hello! Initizliaze successfully!!\n");
    return 0;

rm_kobj:
    kobject_put(mdev.kobj_ref);
    return -1;
}

static void 
__exit hello_world_exit(void)   /* Destructor */
{
    gpio_free(GPIO_LED);                             /* 03 */
    sysfs_remove_group(mdev.kobj_ref, &attr_group);  /* 02 */
    kobject_put(mdev.kobj_ref);                      /* 01 */

    pr_info("Good bye my fen !!!\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC); 
MODULE_VERSION("1.0");  
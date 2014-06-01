/*
 * gpio.h
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include <types.h>
#include <utils.h>
#include <mm.h>

#define GPIO_BASE_PH	0x20200000
#define GPIO_BASE		0xF2000	/* ph 0x20200000 */

#define GPFSEL0			(GPIO_BASE+0x00)
#define GPFSEL1			(GPIO_BASE+0x04)
#define GPFSEL2			(GPIO_BASE+0x08)
#define GPFSEL3			(GPIO_BASE+0x0C)
#define GPFSEL4			(GPIO_BASE+0x10)
#define GPFSEL5			(GPIO_BASE+0x14)

#define GPSET0			(GPIO_BASE+0x1C)
#define GPSET1			(GPIO_BASE+0x20)
#define GPCLR0			(GPIO_BASE+0x28)
#define GPCLR1			(GPIO_BASE+0x2C)

#define GPLEV0			(GPIO_BASE+0x34)
#define GPLEV1			(GPIO_BASE+0x38)
#define GPEDS0			(GPIO_BASE+0x40)
#define GPEDS1			(GPIO_BASE+0x44)

#define GPREN0			(GPIO_BASE+0x4C)
#define GPREN1			(GPIO_BASE+0x50)
#define GPFEN0			(GPIO_BASE+0x58)
#define GPFEN1			(GPIO_BASE+0x5C)

#define GPHEN0			(GPIO_BASE+0x64)
#define GPHEN1			(GPIO_BASE+0x68)
#define GPLEN0			(GPIO_BASE+0x70)
#define GPLEN1			(GPIO_BASE+0x74)

#define GPAREN0			(GPIO_BASE+0x7C)
#define GPAREN1			(GPIO_BASE+0x80)
#define GPAFEN0			(GPIO_BASE+0x88)
#define GPAFEN1			(GPIO_BASE+0x8C)

#define GPPUD			(GPIO_BASE+0x94)
#define GPPUDCLK0		(GPIO_BASE+0x98)
#define GPPUDCLK1		(GPIO_BASE+0x9C)


#define GPIO_FUNC_IN	0b000
#define GPIO_FUNC_OUT	0b001
#define GPIO_FUNC_ALT0	0b100
#define GPIO_FUNC_ALT1	0b101
#define GPIO_FUNC_ALT2	0b110
#define GPIO_FUNC_ALT3	0b111
#define GPIO_FUNC_ALT4	0b011
#define GPIO_FUNC_ALT5	0b010


void init_gpio();
void gpio_set_led_on();
void gpio_set_led_off();


#endif  /* __GPIO_H__ */

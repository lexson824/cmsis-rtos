#include <printk.h>
#include <sched.h>
#include <syscall/syscall.h>
#include <fs/fs.h>
#include <drivers/gpio.h>
#include <drivers/led.h>
#include <drivers/spi.h>
#include <drivers/i2c.h>
#include <drivers/uart.h>
#include <drivers/tim.h>
#include <drivers/ssd1306.h>
#include <net/net.h>

extern void board_init(void);

int main(void)
{
    board_init();

    // sys
    sys_init();
    fs_init();

    // drivers
    gpio_init();
    led_init();
    spi_init();
    i2c_init();
    uart_init();
    tim_init();
    ssd1306_init();

    // w5500
    net_init();

    // task
    task_init();

    printk("fenix init finished, start user tasks ...\n");

    reset_msp();
    move_to_user_mode();
}

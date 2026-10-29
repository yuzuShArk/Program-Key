#include "hardware/i2c.h"
#include "pico/stdlib.h"

#include <cstdint>
#include <cstdio>

int main() {
    stdio_init_all();

    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    sleep_ms(3000);
    printf("I2C scan started\n");

    for (uint8_t address = 0x08; address <= 0x77; ++address) {
        uint8_t reg = 0x00;
        int result = i2c_write_blocking(i2c0, address, &reg, 1, false);

        if (result == 1) {
            printf("Device found at 0x%02X\n", address);
        }
    }

    printf("I2C scan finished\n");

    while (true) {
        sleep_ms(1000);
    }
}

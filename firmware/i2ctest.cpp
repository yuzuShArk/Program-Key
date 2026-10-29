
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <cstdint>
#include <cstdio>

int main() {
    stdio_init_all();

    i2c_init(i2c0, 100000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    sleep_ms(3000);

    for (int i = 0; i < 5; ++i) {
        uint8_t reg = 0x00;
        uint8_t data[2] = {};

        int write_result = i2c_write_blocking(i2c0, 0x5A, &reg, 1, true);
        printf("Write result: %d\n", write_result);

        if (write_result == 1) {
            int read_result = i2c_read_blocking(i2c0, 0x5A, data, 2, false);

            printf("Read result: %d\n", read_result);

            if (read_result == 2) {
                printf("Touch status: 0x%02X%02X\n", data[1], data[0]);
            }
        }
    }

    while (true) {
        sleep_ms(1000);
    }
}

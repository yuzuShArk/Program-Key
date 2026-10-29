
#include "hardware/i2c.h"
#include "pico/stdlib.h"

#include <cstdint>
#include <cstdio>

// MPR121 I2C address
constexpr uint8_t MPR121_ADDR = 0x5A;

// MPR121 register addresses
constexpr uint8_t TOUCH_STATUS_L = 0x00;
constexpr uint8_t ELECTRODE_CONFIG = 0x5E;

// Initialize I2C0 on GP4 (SDA) and GP5 (SCL)
void init_i2c() {
    i2c_init(i2c0, 100 * 1000);

    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);

    gpio_pull_up(4);
    gpio_pull_up(5);
}

// Write one MPR121 register
bool write_register(uint8_t reg, uint8_t value) {
    uint8_t data[] = {reg, value};

    return i2c_write_blocking(i2c0, MPR121_ADDR, data, 2, false) == 2;
}

// Read consecutive MPR121 registers
bool read_registers(uint8_t reg, uint8_t *data, size_t len) {
    int write_result = i2c_write_blocking(i2c0, MPR121_ADDR, &reg, 1, true);

    if (write_result != 1) {
        return false;
    }

    int read_result = i2c_read_blocking(i2c0, MPR121_ADDR, data, len, false);

    return read_result == static_cast<int>(len);
}

// Initialize MPR121 for 12 electrodes
bool init_mpr121() {
    // Stop electrode scanning before configuration
    if (!write_register(ELECTRODE_CONFIG, 0x00)) {
        return false;
    }

    // Set touch threshold = 12, release threshold = 6
    for (uint8_t i = 0; i < 12; ++i) {
        uint8_t touch_reg = 0x41 + 2 * i;

        if (!write_register(touch_reg, 12) ||
            !write_register(touch_reg + 1, 6)) {
            return false;
        }
    }

    // Filter configuration
    const uint8_t settings[][2] = {
        {0x2B, 0x01}, // MHD_R
        {0x2C, 0x01}, // NHD_R
        {0x2D, 0x00}, // NCL_R
        {0x2E, 0x00}, // FDL_R
        {0x2F, 0x01}, // MHD_F
        {0x30, 0x01}, // NHD_F
        {0x31, 0xFF}, // NCL_F
        {0x32, 0x02}, // FDL_F
        {0x33, 0x00}, // NHDT
        {0x34, 0x00}, // NCLT
        {0x35, 0x00}, // FDLT
        {0x5B, 0x00}, // Debounce
        {0x5C, 0x10}, // AFE_CONFIG1
        {0x5D, 0x20}, // AFE_CONFIG2
    };

    for (const auto &setting : settings) {
        if (!write_register(setting[0], setting[1])) {
            return false;
        }
    }

    // Enable 12 electrodes and start measurement
    return write_register(ELECTRODE_CONFIG, 0x8C);
}

int main() {
    stdio_init_all();
    sleep_ms(3000);

    init_i2c();

    printf("MPR121 test started\n");

    if (!init_mpr121()) {
        printf("MPR121 initialization failed\n");

        while (true) {
            sleep_ms(1000);
        }
    }

    printf("MPR121 initialized successfully\n");

    while (true) {
        uint8_t touch_status[2] = {};

        if (read_registers(TOUCH_STATUS_L, touch_status, 2)) {
            uint16_t touched = static_cast<uint16_t>(touch_status[0]) |
                               (static_cast<uint16_t>(touch_status[1]) << 8);

            printf("Touch status: 0x%04X\n", touched);
        } else {
            printf("Touch status read failed\n");
        }

        sleep_ms(200);
    }
}

#include "NRF24.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include <string.h>
#include <stdlib.h>

void NRF24_csnLow(NRF24 *nrf24) {
    gpio_put(nrf24->csn, 0);
}

void NRF24_csnHigh(NRF24 *nrf24) {
    gpio_put(nrf24->csn, 1);
}

void NRF24_ceLow(NRF24 *nrf24) {
    gpio_put(nrf24->ce, 0);
}

void NRF24_ceHigh(NRF24 *nrf24) {
    gpio_put(nrf24->ce, 1);
}

uint8_t NRF24_readReg(NRF24 *nrf24, uint8_t reg) {
    uint8_t result = 0;
    reg = (0b00011111 & reg);
    NRF24_csnLow(nrf24);
    spi_write_blocking(nrf24->port, &reg, 1);
    spi_read_blocking(nrf24->port, 0xff, &result, 1);
    NRF24_csnHigh(nrf24);

    return result;
}

void NRF24_writeReg(NRF24 *nrf24, uint8_t reg, uint8_t data) {
    NRF24_writeRegArray(nrf24, reg, &data, 1);
}

void NRF24_writeRegArray(NRF24 *nrf24, uint8_t reg, uint8_t *data, uint8_t size) {
    reg = 0b00100000 | (0b00011111 & reg);
    NRF24_csnLow(nrf24);
    spi_write_blocking(nrf24->port, &reg, 1);
    spi_write_blocking(nrf24->port, (uint8_t*)data, size);
    NRF24_csnHigh(nrf24);
}

void NRF24_config(NRF24 *nrf24) {
    NRF24_csnHigh(nrf24);
    NRF24_ceLow(nrf24);
    sleep_ms(11);

    NRF24_writeReg(nrf24, 0, 0b00001010); // config.
    sleep_us(1500);

    NRF24_writeReg(nrf24, 1, 0); // no ack.

    NRF24_writeReg(nrf24, 5, 60); // channel.

    NRF24_writeRegArray(nrf24, 0x0a, (uint8_t*)"gyroc", 5);
    NRF24_writeRegArray(nrf24, 0x10, (uint8_t*)"gyroc", 5);

    NRF24_writeReg(nrf24, 0x11, 32);
}

void NRF24_modeTX(NRF24 *nrf24) {
    uint8_t reg = NRF24_readReg(nrf24, 0);
    reg &= ~(1 << 0);
    NRF24_writeReg(nrf24, 0, reg);

    NRF24_ceLow(nrf24); // Correction from video, thanks schuhmann.

    sleep_us(130);
}

void NRF24_modeRX(NRF24 *nrf24) {
    uint8_t reg = NRF24_readReg(nrf24, 0);
    reg |= (1 << 0);
    NRF24_writeReg(nrf24, 0, reg);

    NRF24_ceHigh(nrf24); // Correction from video, thanks schuhmann.

    sleep_us(130);
}

void NRF24_sendMessage(NRF24 *nrf24, char *msg) {
    uint8_t reg = 0b10100000;
    NRF24_csnLow(nrf24);
    spi_write_blocking(nrf24->port, &reg, 1);
    spi_write_blocking(nrf24->port, (uint8_t*)msg, 32);
    NRF24_csnHigh(nrf24);

    NRF24_ceHigh(nrf24);
    sleep_us(10);
    NRF24_ceLow(nrf24);
}

void NRF24_receiveMessage(NRF24 *nrf24, char *msg) {
    uint8_t cmd = 0b01100001;
    NRF24_csnLow(nrf24);
    spi_write_blocking(nrf24->port, &cmd, 1);

    spi_read_blocking(nrf24->port, 0xff, (uint8_t*)msg, 32);
    NRF24_csnHigh(nrf24);
}

uint8_t NRF24_newMessage(NRF24 *nrf24) {
    uint8_t fifo_status = NRF24_readReg(nrf24, 0x17);

    return !(0x00000001 & fifo_status);
}

NRF24 *NRF24_create(spi_inst_t *port, uint16_t csn, uint16_t ce) {
    NRF24 *nrf24 = (NRF24 *)malloc(sizeof(NRF24));
    if (nrf24 != NULL) {
        nrf24->port = port;
        nrf24->csn = csn;
        nrf24->ce = ce;

        spi_init(nrf24->port, 1000000);
        gpio_set_function(10, GPIO_FUNC_SPI);
        gpio_set_function(11, GPIO_FUNC_SPI);
        gpio_set_function(12, GPIO_FUNC_SPI);

        gpio_init(nrf24->csn);
        gpio_init(nrf24->ce);

        gpio_set_dir(nrf24->csn, 1);
        gpio_set_dir(nrf24->ce, 1);

        NRF24_ceLow(nrf24);
        NRF24_csnHigh(nrf24);
    }
    return nrf24;
}

void NRF24_destroy(NRF24 *nrf24) {
    free(nrf24);
}


#ifndef __NRF24_H
#define __NRF24_H

#include "hardware/spi.h"
#include "hardware/gpio.h"

typedef struct {
	spi_inst_t *port;
	uint16_t csn;
	uint16_t ce;
}NRF24;

// CSN and CE controller functions
void NRF24_csnLow();
void NRF24_csnHigh();
void NRF24_ceLow();
void NRF24_csHigh();

// Register handler functions
uint8_t NRF24_readReg(NRF24 *nrf24, uint8_t reg);
void NRF24_writeReg(NRF24 *nrf24, uint8_t reg, uint8_t data);
void NRF24_writeRegArray(NRF24 *nrf24, uint8_t reg, uint8_t *data, uint8_t len);

// Configuration and mode setting
void NRF24_config(NRF24 *nrf24);
void NRF24_modeTX(NRF24 *nrf24);
void NRF24_modeRX(NRF24 *nrf24);

// Message handling
void NRF24_sendMessage(NRF24 *nrf24, char *msg);
void NRF24_receiveMessage(NRF24 *nrf24, char *msg);
uint8_t NRF24_newMessage(NRF24 *nrf24);

// Allocate and free memory
NRF24 *NRF24_create(spi_inst_t *port, uint16_t csn, uint16_t ce);
void NRF24_destroy(NRF24 *nrf24);

#endif

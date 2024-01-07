#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "NRF24.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
//    spi_inst_t *spi1 = spi1; // Assuming spi1 is declared globally in the library
	
	stdio_init_all();		
    	NRF24 *nrf24 = NRF24_create(spi1, 9, 8);
    	if (nrf24 == NULL) {
        	// Handle memory allocation failure
        	return 1;
    	}

    	NRF24_config(nrf24);
    	NRF24_modeRX(nrf24);
	
    	char receivedMessage[32];
    	while (1) {
        	if (NRF24_newMessage(nrf24)) {
            	NRF24_receiveMessage(nrf24, receivedMessage);
            	printf("Received Message: %s\n", receivedMessage);
        	}

//        	sleep_ms(1000);
    	}

    	NRF24_destroy(nrf24);
    	return 0;
}


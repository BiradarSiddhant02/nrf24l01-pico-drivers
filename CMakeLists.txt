cmake_minimum_required(VERSION 3.12)
include(src/pico_sdk_import.cmake)

project(nrf)

pico_sdk_init()


add_executable(nrf
	src/main.c
	src/NRF24.c
	src/NRF24.h
)
target_include_directories(nrf PUBLIC
	inc
)

target_link_libraries(nrf
	pico_stdlib
	hardware_spi
)

pico_enable_stdio_usb(nrf 1)
pico_enable_stdio_uart(nrf 0)

pico_add_extra_outputs(nrf)

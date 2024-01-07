# Pico SDK Signal Generation Project

This project demonstrates how to use the Raspberry Pi Pico SDK to generate a signal of 2 Hz with added noise of 100 Hz. The project uses the Pico SDK, which is the official software development kit for the Raspberry Pi Pico.

## Table of Contents

- [Introduction](#introduction)
- [Requirements](#requirements)
- [Installation](#installation)
- [License](#license)

## Introduction

This project showcases a simple signal generation application using the Raspberry Pi Pico microcontroller. The generated signal consists of a sinusoidal waveform with a frequency of 2 Hz, and it includes an added noise component with a frequency of 100 Hz. This emulates a signal generator. It is names 'master' since it is the master device in the SPI connection. the slave is in the repository (https://github.com/your-username/pico-slave.git)

## Requirements

To build and run this project, you'll need:

- [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/)
- [Pico SDK](https://github.com/raspberrypi/pico-sdk)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/BiradarSiddhant02/pico-nrf24l01-pico-drivers.git
   cd pico
2. Build the binaries
    ```bash
    mkdir build
    cd build
    export PICO_SDK_PATH=../../pico-sdk
    cmake ..
    make -j4
4. Write code in src folder in main.c file

## License

This project is licensed under the [MIT License](LICENSE) - see the [LICENSE](LICENSE) file for details.

# pico-master

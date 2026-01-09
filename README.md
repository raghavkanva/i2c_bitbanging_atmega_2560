# Software I2C Bit-Banging on ATmega2560

This repository contains a bare-metal implementation of the I2C protocol using GPIO (bit-banging) on the ATmega2560 microcontroller.  
The project interfaces an I2C LCD module and verifies bus activity using a logic analyzer.

The implementation does not use hardware I2C peripherals or Arduino Wire libraries.

---

## Description

- I2C protocol implemented in software using GPIO control - bit banging method
- START, STOP, address, data, and ACK handling implemented manually
- LCD interfaced via I2C expander
- Modular driver structure separating protocol, device, and application logic
- Signal-level verification performed using a logic analyzer

---

## Libraries (`lib/`)

The `lib/` directory contains bare-metal driver code:

### I2C Driver
- GPIO-based clock and data generation
- Software timing control
- START and STOP condition generation
- Byte write support with ACK detection

### LCD Driver
- LCD command and data handling
- Initialization sequence
- Character and string display support

All libraries are written without relying on Arduino framework APIs.

---

## Application (`src/`)

The `src/main.c` file contains:
- Microcontroller initialization
- I2C and LCD driver usage
- Application-level logic

The source file uses the drivers from `lib/` to demonstrate I2C LCD communication.

---

## Tools and Environment

- Microcontroller: ATmega2560
- Development environment: PlatformIO with VS Code
- Language: C
- Debug and validation: Logic analyzer

---

## Verification

I2C bus activity was captured using a logic analyzer to observe:
- START and STOP conditions
- Address transmission
- Data bytes
- Acknowledge bits

This confirms correct protocol sequencing at the signal level.

---

## Notes

- This project is intended for learning and understanding low-level protocol implementation
- Timing values are configurable and may be adjusted based on system requirements
- The repository focuses on clarity and separation of concerns rather than optimization

---

## License

This project is provided for educational purposes.


# Software I2C Bit-Banging on ATmega2560

This repository contains a bare-metal implementation of the I2C protocol using GPIO (bit-banging) on the ATmega2560 microcontroller.  
The project interfaces an I2C LCD module and verifies bus activity using a logic analyzer.

The implementation does not use hardware I2C peripherals or Arduino Wire libraries.

---

## Introduction

This project helped me understand how I2C communication protocol behaves at the system and signal level. By implementing I²C using GPIO and validating it with a logic analyzer, I learned how software logic, timing, and physical setup together determine correct system behavior—an important perspective for system-level and TM work.”

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
## Debugging & System Learnings

During validation of the software-implemented I²C bus, initial logic analyzer captures showed incorrect signal behavior, even though the software logic appeared correct. Instead of changing the code immediately, the debugging approach focused on isolating system-level factors.

By examining the physical measurement setup, it was observed that longer logic-analyzer probe wires introduced distortion in the captured signals. When the probe connections were shortened and the setup improved, the I²C waveforms matched the expected START, address, data, and ACK sequences.

This debugging process highlighted that observed behavior in embedded systems is influenced not only by software logic, but also by physical setup and measurement methodology. The key learning was the importance of validating assumptions at the system level before modifying implementation.

This experience highlighted that hardware demonstrations require careful attention to setup and measurement, since these directly influence how system behavior is observed and explained.

---

## Notes

- This project is intended for learning and understanding low-level protocol implementation
- Timing values are configurable and may be adjusted based on system requirements
- The repository focuses on clarity and separation of concerns rather than optimization

---

## License

This project is provided for educational purposes.


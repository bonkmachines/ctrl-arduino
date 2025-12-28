# CTRL Arduino Library Repository

## Project Overview

**CTRL** is an Arduino library that provides easy-to-use interfaces for controlling hardware components commonly used in Arduino projects. It supports buttons, rotary encoders, potentiometers, LEDs, and multiplexers with built-in debouncing, smooth input handling, and flexible instantiation methods.

- **Repository**: [bonkmachines/ctrl-arduino](https://github.com/bonkmachines/ctrl-arduino)
- **Version**: 1.5.1
- **Author**: Johannes Jan Prins <johannesprins@knalgeel.com>
- **License**: See LICENSE file
- **Category**: Device Control

## Project Structure

```
ctrl-arduino/
├── src/                          # Library source code
│   ├── CTRL.h                    # Main library header
│   ├── CtrlBase.h/cpp            # Base controller class
│   ├── CtrlBtn.h/cpp             # Button controller
│   ├── CtrlEnc.h/cpp             # Rotary encoder controller
│   ├── CtrlPot.h/cpp             # Potentiometer controller
│   ├── CtrlLed.h/cpp             # LED controller
│   ├── CtrlMux.h/cpp             # Multiplexer controller
│   ├── CtrlGroup.h/cpp           # Group controller for managing multiple devices
│   ├── Groupable.h/cpp           # Mixin for groupable devices
│   ├── Muxable.h/cpp             # Mixin for multiplexer-compatible devices
│   └── main.cpp                  # Main entry point
├── test/                         # Unit tests (Unity framework)
│   ├── test_button_*.cpp         # Button unit tests
│   ├── test_encoder_*.cpp        # Encoder unit tests
│   ├── test_potentiometer_*.cpp  # Potentiometer unit tests
│   ├── test_led.cpp              # LED unit tests
│   ├── test_group_*.cpp          # Group unit tests
│   ├── test_mulitiplexer_*.cpp   # Multiplexer unit tests
│   ├── test_main.cpp             # Test runner
│   ├── test_globals.h/cpp        # Global test utilities
│   └── unity_config.h            # Unity framework configuration
├── examples/                     # Example sketches
│   ├── buttons/                  # Button examples
│   ├── rotary_encoders/          # Encoder examples
│   ├── potentiometers/           # Potentiometer examples
│   ├── leds/                     # LED examples
│   ├── multiplexers/             # Multiplexer examples
│   └── groups/                   # Group examples
├── docs/                         # Documentation
│   ├── README.md                 # Documentation index
│   ├── buttons.md                # Button implementation guide
│   ├── rotary_encoders.md        # Encoder implementation guide
│   ├── potentiometers.md         # Potentiometer implementation guide
│   └── multiplexers.md           # Multiplexer implementation guide
├── .github/                      # GitHub configuration
│   └── workflows/                # CI/CD workflows
├── assets/                       # Repository assets (images, logos)
├── platformio.ini                # PlatformIO configuration
├── library.properties            # Arduino library metadata
├── README.md                     # Main project readme
├── LICENSE                       # License file
└── .gitignore                    # Git ignore rules

```

## Core Components

### Controllers

- **CtrlBtn** - Debounced button input with press/release callbacks
- **CtrlEnc** - Rotary encoder with rotation detection
- **CtrlPot** - Potentiometer input with smooth value handling
- **CtrlLed** - LED control with blinking/flashing patterns
- **CtrlMux** - Multiplexer support for expanding I/O capacity
- **CtrlGroup** - Group multiple controllers for batch operations

### Mixins

- **Groupable** - Allows devices to be part of a group
- **Muxable** - Enables device support for multiplexers

## Technologies & Tools

- **Language**: C++ (Arduino)
- **Build System**: PlatformIO
- **Testing Framework**: Unity
- **Hardware Targets**:
  - Teensy 4.1 (primary development board)
  - Arduino UNO (supported)
- **CI/CD**: GitHub Actions

## Configuration

### Build Environments (platformio.ini)

- **teensy41**: Development environment for Teensy 4.1 @ 24MHz
- **uno**: Arduino UNO support
- **ci**: Testing environment with Unity framework and code coverage

## Key Features

- Multiple hardware targets (Teensy, Arduino UNO)
- Uniform, flexible interfaces
- Debouncing for buttons and encoders
- Smooth potentiometer input handling
- Group management for multiple devices
- Multiplexer support for I/O expansion
- Comprehensive unit test coverage
- Full code examples for all components
- Detailed documentation

## Testing

The project includes comprehensive unit tests covering:

- Button states (basic, advanced, pull-up, pull-down, alternative)
- Encoder operations (basic, advanced, pull-up, pull-down, alternative)
- Potentiometer input (basic, advanced, common, alternative)
- LED functionality
- Grouping operations
- Multiplexer integration

Tests run on the `ci` environment using the Unity framework with code coverage tracking.

## Installation

### Arduino IDE
1. Open Library Manager
2. Search for "CTRL"
3. Click "INSTALL"

### Manual Installation
1. Download latest release from [GitHub Releases](https://github.com/bonkmachines/ctrl-arduino/releases)
2. Arduino IDE → Sketch → Include Library → Add .ZIP Library
3. Select the downloaded file

## Basic Usage

```cpp
#include <CtrlBtn.h>

void onPress() {
  Serial.println("Button pressed");
}

void onRelease() {
  Serial.println("Button released");
}

// pin: 1, debounce: 15ms, onPress callback, onRelease callback
CtrlBtn button(1, 15, onPress, onRelease);

void setup() {
  Serial.begin(9600);
}

void loop() {
  button.process();
}
```

## Development

- **Contact**: johannesprins@knalgeel.com
- **GitHub**: https://github.com/bonkmachines/ctrl-arduino
- **Issues & Features**: Submit via GitHub Issues

## CI/CD Status

The project uses GitHub Actions workflows for:
- Unit testing
- Example compilation
- Spell checking

See `.github/workflows/` for details.

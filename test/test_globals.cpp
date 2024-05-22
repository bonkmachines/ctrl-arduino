#include "test_globals.h"
#include <core_pins.h>

// Global button variable definitions
uint8_t buttonSig = 1;
uint8_t mockButtonInput = HIGH; // HIGH or LOW
uint16_t buttonBounceDuration = 15;
std::string buttonHandlerResult;

// Global encoder variable definitions
uint8_t encoderClkSig = 2;
uint8_t encoderDtSig = 3;
uint8_t mockClkInput = LOW; // HIGH or LOW
uint8_t mockDtInput = LOW; // HIGH or LOW
std::string encoderHandlerResult;

// Global potentiometer variable definitions
uint8_t potentiometerSig = 4;
uint16_t mockPotentiometerInput = 0; // 0 - 1023
int potentiometerHandlerResult;

// Global multiplexer variable definitions
uint8_t muxSig = 5;
uint8_t muxS0 = 6;
uint8_t muxS1 = 7;
uint8_t muxS2 = 8;
uint8_t muxS3 = 9;
uint8_t mockMuxDigitalInput = HIGH;
uint16_t mockMuxAnalogInput = 0;
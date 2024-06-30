#include "test_globals.h"
#include <core_pins.h>

// Global button variable definitions
uint8_t mockButtonInput = HIGH; // HIGH or LOW
std::string buttonHandlerResult;

// Global encoder variable definitions
uint8_t mockClkInput = LOW; // HIGH or LOW
uint8_t mockDtInput = LOW; // HIGH or LOW
std::string encoderHandlerResult;

// Global potentiometer variable definitions
uint16_t mockPotentiometerInput = 0; // 0 - 1023
int potentiometerHandlerResult;
std::string groupedPotentiometerHandlerResult;

// Global multiplexer variable definitions
uint8_t mockMuxBtnSigInput = HIGH;
uint8_t mockMuxEncClkInput = LOW;
uint8_t mockMuxEncDtInput = LOW;
uint16_t mockMuxPotSigInput = 0;
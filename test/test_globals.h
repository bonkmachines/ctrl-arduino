#ifndef TEST_GLOBALS_H
#define TEST_GLOBALS_H

#include <cstdint>
#include <string>

// Button variables
extern uint8_t mockButtonInput;
extern std::string buttonHandlerResult;

// Encoder variables
extern uint8_t mockClkInput;
extern uint8_t mockDtInput;
extern std::string encoderHandlerResult;

// Potentiometer variables
extern uint16_t mockPotentiometerInput;
extern int potentiometerHandlerResult;

// Multiplexer variables
extern uint8_t mockMuxBtnSigInput;
extern uint8_t mockMuxEncClkInput;
extern uint8_t mockMuxEncDtInput;
extern uint16_t mockMuxPotSigInput;

#endif //TEST_GLOBALS_H

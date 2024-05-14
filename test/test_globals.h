#ifndef TEST_GLOBALS_H
#define TEST_GLOBALS_H

#include <cstdint>
#include <string>

// Button variables
extern uint8_t buttonSig;
extern uint8_t mockButtonInput;
extern uint16_t buttonBounceDuration;
extern std::string buttonHandlerResult;

// Encoder variables
extern uint8_t encoderClkSig;
extern uint8_t encoderDtSig;
extern uint8_t mockClkInput;
extern uint8_t mockDtInput;
extern std::string encoderHandlerResult;

// Potentiometer variables
extern uint8_t potentiometerSig;
extern uint16_t mockPotentiometerInput;
extern int potentiometerHandlerResult;

// LED variables
extern uint8_t ledSig;
extern uint16_t mockLedOutput;

#endif //TEST_GLOBALS_H

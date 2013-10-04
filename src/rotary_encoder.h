#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <stdint.h>

typedef struct RotaryEncoder {
  uint8_t mask;
  uint8_t value;
} RotaryEncoder; 

RotaryEncoder *RotaryEncoder_create(uint8_t mask);
void RotaryEncoder_setup(uint8_t pina, uint8_t pinb);
uint8_t RotaryEncoder_read(RotaryEncoder *encoder);

#endif

#include "dbg.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct RotaryEncoder {
  uint8_t mask;
  uint8_t value;
} RotaryEncoder;

// all the possible 2bit states. Maps to potential read values off of the
// encoder pins. 
//
// ex: [0001] -> 2 -> -1
// ex: [0011] -> 5 -> 1
//
// 1 represents a turn in one direction
// -1 a turn in the other direction
// 0 represents an invalid state (maybe a bad conection etc.) in those cases
// we pretend we have moved nowhere!
static int8_t RotaryEncoder_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

RotaryEncoder *RotaryEncoder_create(uint8_t mask);
void RotaryEncoder_setup(uint8_t pina, uint8_t pinb);
uint8_t RotaryEncoder_read(RotaryEncoder *encoder);

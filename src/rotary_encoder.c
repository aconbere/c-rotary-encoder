#include "rotary_encoder.h"

#if defined(ARDUINO)
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#define PINC 0
#define INPUT 1
#define HIGH 1
void pinMode(uint8_t pin, uint8_t mode) {}
void digitalWrite(uint8_t pin, uint8_t value) {}
#else
# error Unknown platform, cannot define getCurrentMilliseconds.
#endif

void RotaryEncoder_setup(uint8_t pina, uint8_t pinb) {
  pinMode(pina, INPUT);
  digitalWrite(pina, HIGH);

  pinMode(pinb, INPUT);
  digitalWrite(pinb, HIGH);
}

RotaryEncoder *RotaryEncoder_create(uint8_t mask) {
  RotaryEncoder *encoder = calloc(1, sizeof(RotaryEncoder));
  encoder->mask = mask;
  encoder->value = 0;
  check_mem(encoder);
  return encoder;

error:
  return NULL;
}

uint8_t RotaryEncoder_read(RotaryEncoder *encoder) {
  // make room for the two bits from our pins
  encoder->value <<= 2;

  // PINC is a bitmap of the current state of all pins
  // encoder mask should define which pins we want to read
  // we do this so we are garunteed a consistent read off
  // of the pins at the same time.
  encoder->value |= ( PINC & encoder->mask );

  // There is no 4bit value, so we just mask off the top 4 bits
  // of our 8 bit integer
  return RotaryEncoder_states[encoder->value & 0x0f];
}

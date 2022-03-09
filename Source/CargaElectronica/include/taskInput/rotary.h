#ifndef __ROTARY_H__
#define __ROTARY_H__

#include <stdint.h>


void rotaryConfigure();

void rotaryTick();

uint8_t getRotaryPushState();
uint32_t getRotaryCounter();

#endif //__ROTARY_H__

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdint.h>

struct screenData{
    float current;
    float voltage;
};

void configureScreen();


void screenSetParams(struct screenData pData);

#endif //__SCREEN_H__
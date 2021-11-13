#ifndef __STATUS_H__
#define __STATUS_H__

#include <stdint.h>

struct __statusData{
    uint16_t supply;
};

extern __statusData statusData;

void statusMainLoop();

#endif //__STATUS_H__
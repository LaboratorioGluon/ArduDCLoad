#ifndef __MAININPUT_H__
#define __MAININPUT_H__


namespace taskInput {

    struct inputData{
        uint32_t rotaryCounter;
        uint8_t  rotarySwitch; // 0 = Off, 1 = Pressed
        uint16_t voltageSense;
        uint8_t  switchOk;
        uint8_t  switchBack;
    };

    extern struct inputData inputOutData;

    void inputInitialize();

    void inputMainLoop();
};


#endif
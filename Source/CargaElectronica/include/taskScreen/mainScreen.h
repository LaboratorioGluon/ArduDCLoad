#ifndef __MAIN_SCREEN_H__
#define __MAIN_SCREEN_H__


namespace taskScreen {

    struct screenData{
    };

    extern struct screenData screenOutData;

    void screenInitialize();

    void screenMainLoop();
};


#endif
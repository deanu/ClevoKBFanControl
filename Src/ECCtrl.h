//
//  ECCtrl.h
//  ClevoControl
//
//  Created by datasone on 9/8/2017.
//  Copyright © 2017 datasone. All rights reserved.
//
#ifndef ECCtrl_h
#define ECCtrl_h

#include <stdint.h>

struct ECCtrl {
    uint32_t arg0, arg1, arg2;
};

class ClevoCtrl
{
public:
    void setSwitch(int);
    void setMode(int);
    void setBrightness(int);
    void setautoFan();
    void setFan(int,int,int);
    void setfullColor(char*);
    void setsepColor(char*);
    struct ECCtrl ctrl;
    struct ECCtrl ctrl2;
};

#endif

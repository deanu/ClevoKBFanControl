//
//  ClevoCtrlWrapper.cpp
//  ClevoKBFanControl
//
//  Created by deanu on 2018/9/2.
//  Copyright © 2018年 deanu. All rights reserved.
//

#include <stdio.h>
#include "ECCtrl.h"
// extern "C" will cause the C++ compiler
// (remember, this is still C++ code!) to
// compile the function in such a way that
// it can be called from C
// (and Swift).
ClevoCtrl clevo;

extern "C" void setkbMode(int mode)
{
    // Create an instance of A, defined in
    // the library, and call getInt() on it:
    clevo.setMode(mode);
}

//void setlightSwitch(int);
//void setkbBrightness(int);
//void setmbFan(int);

extern "C" void setlightSwitch(int sch)
{
    // Create an instance of A, defined in
    // the library, and call getInt() on it:
    clevo.setSwitch(sch);
}

extern "C" void setkbBrightness(int brt)
{
    // Create an instance of A, defined in
    // the library, and call getInt() on it:
    clevo.setBrightness(brt);
}

extern "C" void setmbautoFan()
{
    // Create an instance of A, defined in
    // the library, and call getInt() on it:
    clevo.setautoFan();
}

extern "C" void setmbFan(int startTemp, int stopTemp,int fanMaxSpeed)
{
    // Create an instance of A, defined in
    // the library, and call getInt() on it:
    clevo.setFan(startTemp, stopTemp, fanMaxSpeed);
}

extern "C" void setfullcolor(char* color)
{
    // Create an instance of A, defined in
    // the library, and call getInt() on it:
    clevo.setfullColor(color);
}

extern "C" void setsepcolor(char* color){
    clevo.setsepColor(color);
}

#include "ECCtrl.h"
#include <iostream>
#include <sys/kern_control.h>
#include <sys/kern_event.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#define SET_KB_LED 0x67
#define SET_FAN 0x79

using std::string;

void sendctl(struct ECCtrl ctrl)
{
    struct ctl_info info;
    struct sockaddr_ctl addr;
    int fd = socket(PF_SYSTEM, SOCK_DGRAM, SYSPROTO_CONTROL);
    if (fd != -1)
    {
        bzero(&addr, sizeof(addr));
        addr.sc_len = sizeof(addr);
        addr.sc_family = AF_SYSTEM;
        addr.ss_sysaddr = AF_SYS_CONTROL;
        memset(&info, 0, sizeof(info));
        strcpy(info.ctl_name, "moe.datasone.clevocontrol.ctl");
        if (ioctl(fd, CTLIOCGINFO, &info))
        {
            exit(-1);
        }
        addr.sc_id = info.ctl_id;
        addr.sc_unit = 0;
        if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_ctl)))
            exit(-1);
        send(fd, &ctrl, sizeof(ECCtrl), 0);
    }
}

void ClevoCtrl::setMode(int mode) {
    ClevoCtrl::ctrl.arg0 = 0;
    ClevoCtrl::ctrl.arg1 = SET_KB_LED;
    ClevoCtrl::ctrl2.arg0 = 0;
    ClevoCtrl::ctrl2.arg1 = SET_KB_LED;
    ClevoCtrl::ctrl2.arg2 = 0x10000000;
    if (mode == 1)
        ClevoCtrl::ctrl.arg2 = 0x1002A000;
    else if (mode == 2)
        ClevoCtrl::ctrl.arg2 = 0x33010000;
    else if (mode == 3)
        ClevoCtrl::ctrl.arg2 = 0x80000000;
    else if (mode == 4)
        ClevoCtrl::ctrl.arg2 = 0xA0000000;
    else if (mode == 5)
        ClevoCtrl::ctrl.arg2 = 0x70000000;
    else if (mode == 6)
        ClevoCtrl::ctrl.arg2 = 0x90000000;
    else if (mode == 7)
        ClevoCtrl::ctrl.arg2 = 0xB0000000;
    sendctl(ClevoCtrl::ctrl2);
    sendctl(ClevoCtrl::ctrl);
}

//开关
void ClevoCtrl::setSwitch(int sch) {
    ClevoCtrl::ctrl.arg0 = 0;
    ClevoCtrl::ctrl.arg1 = SET_KB_LED;
    ClevoCtrl::ctrl.arg2 = 0xE0000000;
    if (sch == 0) {
        ClevoCtrl::ctrl.arg2 |= 0x003001;
        sendctl(ClevoCtrl::ctrl);
    }
    else
    {
        ClevoCtrl::ctrl.arg2 |= 0x07F001;
        sendctl(ClevoCtrl::ctrl);
    }
}

//亮度
void ClevoCtrl::setBrightness(int brt){
    uint8_t lvl_to_raw[] = { 63, 126, 189, 252 };
    ClevoCtrl::ctrl.arg0 = 0;
    ClevoCtrl::ctrl.arg1 = SET_KB_LED;
    ClevoCtrl::ctrl.arg2 = 0xF4000000 | lvl_to_raw[brt];
    sendctl(ClevoCtrl::ctrl);
}

//full color
void ClevoCtrl::setfullColor(char color[]){
    string state = color;
    string state_brg = state.substr(4, 2) + state.substr(0, 2) + state.substr(2, 2);
    uint32_t i = std::stoul(state_brg, nullptr, 16);
    ClevoCtrl::ctrl2.arg0 = 0;
    ClevoCtrl::ctrl2.arg1 = SET_KB_LED;
    ClevoCtrl::ctrl2.arg2 = 0x10000000;
    sendctl(ClevoCtrl::ctrl2);
    ClevoCtrl::ctrl.arg0 = 0;
    ClevoCtrl::ctrl.arg1 = SET_KB_LED;
    ClevoCtrl::ctrl.arg2 = 0xF0000000;
    ClevoCtrl::ctrl.arg2 |= i;
    sendctl(ClevoCtrl::ctrl);
    ClevoCtrl::ctrl.arg2 = 0xF1000000;
    ClevoCtrl::ctrl.arg2 |= i;
    sendctl(ClevoCtrl::ctrl);
    ClevoCtrl::ctrl.arg2 = 0xF2000000;
    ClevoCtrl::ctrl.arg2 |= i;
    sendctl(ClevoCtrl::ctrl);
}
//sep color
void ClevoCtrl::setsepColor(char color[]){
    ClevoCtrl::ctrl2.arg0 = 0;
    ClevoCtrl::ctrl2.arg1 = SET_KB_LED;
    ClevoCtrl::ctrl2.arg2 = 0x10000000;
    sendctl(ClevoCtrl::ctrl2);
    ClevoCtrl::ctrl.arg0 = 0;
    ClevoCtrl::ctrl.arg1 = SET_KB_LED;
    string stateList = color;
    string colors[3];
    for (int i = 0; i < 3; ++i) {
        colors[i] = stateList.substr(6 * i + i, 6);
        colors[i] = colors[i].substr(4, 2) + colors[i].substr(0, 2) + colors[i].substr(2, 2);
        uint32_t j = std::stoul(colors[i], nullptr, 16);
        ClevoCtrl::ctrl.arg2 = 0xF0000000 + i * 0x1000000;
        ClevoCtrl::ctrl.arg2 |= j;
        sendctl(ClevoCtrl::ctrl);
    }
}

//fan
void ClevoCtrl::setautoFan(){
    ClevoCtrl::ctrl.arg0 = 0;
    ClevoCtrl::ctrl.arg1 = SET_FAN;
    ClevoCtrl::ctrl.arg2 = 0x1000000;
    sendctl(ClevoCtrl::ctrl);
    ClevoCtrl::ctrl.arg2 = 0;
    ClevoCtrl::ctrl.arg2 |= 0x7000000;
    sendctl(ClevoCtrl::ctrl);
}

void ClevoCtrl::setFan(int startTemp,int stopTemp,int fanMaxSpeed){
    int ctrlData = (fanMaxSpeed << 16) + (stopTemp << 8) + startTemp;
    ctrlData |= 0x7000000;
    ClevoCtrl::ctrl.arg0 = 0;
    ClevoCtrl::ctrl.arg1 = SET_FAN;
    ClevoCtrl::ctrl.arg2 = ctrlData;
    sendctl(ClevoCtrl::ctrl);
}

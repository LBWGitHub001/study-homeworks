//
// Created by 28739 on 2024/1/30.
//

#include "Engineer.h"

Engineer::Engineer()
        : Robot() {
}

Engineer::Engineer(Engineer &eng)
        : Robot(eng) {
}

Engineer::~Engineer() {

}

Engineer::Engineer(int RobotId, int capId, int robId)
        : Robot(RobotId, capId, robId) {

}

void Engineer::inc_hp(int inc)   //增加机器人血量
{
    int hp = Get_hp();
    if (hp + inc <= HP_UPLINE[0])
        Set_hp(hp + inc);
}

void Engineer::inc_hot(int inc)  //增加机器人枪口热量
{
    int hot = Get_hot();
    Set_hp(hot + inc);
}

void Engineer::dec_hp(int dec)   //降低机器人血量
{
    int hp = Get_hp();
    if (hp - dec < 0)
        Set_hp(0);
    else
        Set_hp(hp - dec);
}

void Engineer::dec_hot(int dec)  //降低机器人枪口热量
{
    int hot = Get_hot();
    if (hot - dec < 0)
        Set_hot(0);
    else
        Set_hot(hot - dec);
}

Engineer &Engineer::operator=(Engineer &eng) {
    if (this == &eng) return *this;
    Set_hot(eng.Get_hot());
    Set_hp(eng.Get_hp());
    Set_hotUpline(eng.Get_hot_upline());
    Set_phUpline(eng.Get_hp_upline());
    return *this;

}



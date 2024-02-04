//
// Created by 28739 on 2024/1/30.
//

#include "Solider.h"

Solider::Solider()
        : Robot() {
}

Solider::Solider(Solider &sol)
        : Robot(sol) {
    _level = sol._level;

}

Solider::~Solider() {

}

Solider::Solider(int capId, int robotId, int robotType)
        : Robot(capId, robotId, robotType) {
    _level = 1;
}

Solider::Solider(int capId, int robotId, int robotType, int level)
        : Robot(capId, robotId, robotType), _level(level) {
}

void Solider::inc_hp(int inc)   //增加机器人血量
{
    int hp = Get_hp();
    if (hp + inc <= HP_UPLINE[_level])
        Set_hp(hp + inc);
}

void Solider::inc_hot(int inc)  //增加机器人枪口热量
{
    int hot = Get_hot();
    Set_hot(hot + inc);

}

void Solider::dec_hp(int dec)   //降低机器人血量
{
    int hp = Get_hp();
    if (hp - dec < 0)
        Set_hp(0);
    else
        Set_hp(hp - dec);
}

void Solider::dec_hot(int dec)  //降低机器人枪口热量
{
    int hot = Get_hot();
    if (hot - dec < 0)
        Set_hot(0);
    else
        Set_hot(hot - dec);
}


void Solider::Set_level(int level) {
    _level = level;
    Set_phUpline(HP_UPLINE[_level]);
    Set_hotUpline(HOT_UPLINE[_level]);
    Set_hp(HP_UPLINE[_level]);

}

Solider &Solider::operator=(Solider &sol) {
    if (this == &sol) return *this;
    Set_hot(sol.Get_hot());
    Set_hp(sol.Get_hp());
    Set_hotUpline(sol.Get_hot_upline());
    Set_phUpline(sol.Get_hp_upline());
    _level = sol._level;
    return *this;
}





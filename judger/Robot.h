//
//此类为抽象类，用于派生出Solider,Engineer类，并实现一些基础共同功能
//
#ifndef JUDGER_ROBOT_H
#define JUDGER_ROBOT_H

#include <iostream>
#include "Def.h"

//抽象类
const int HP_UPLINE[4] = {100, 300, 150, 250};
//                      步兵1     工程 步兵2     步兵3
const int HOT_UPLINE[4] = {100, 0, 200, 300};
//                        步兵1    工程 步兵2     步兵3

class Robot {
public:
    int _hp_upline;     //血量上限
    int _hot_upline;    //热量上限
    int _hp;            //血量
    int _hot;           //枪口热量
    int _cap_id;        //所属队伍标识符
    int _rob_id;        //机器人标识符
    int _rob_type;      //机器人类别0:工程1:步兵


    Robot() { ; }

    Robot(Robot &rob) {
        _hp_upline = rob._hp_upline;     //血量上限
        _hot_upline = rob._hot_upline;    //热量上限
        _hp = rob._hp;            //血量
        _hot = rob._hot;           //枪口热量
        _cap_id = rob._cap_id;        //所属队伍标识符
        _rob_id = rob._rob_id;        //机器人标识符
        _rob_type = rob._rob_type;      //机器人类别0:工程1:步兵
    }

    Robot(int capId, int robotId, int robotType) {
        _hp = _hp_upline = HP_UPLINE[robotType];
        _hot_upline = HOT_UPLINE[robotType];
        _hot = 0;
        _cap_id = capId;
        _rob_id = robotId;
        _rob_type = robotType;
    }

    virtual ~Robot() {
        //std::cout << "Cap:" << _cap_id << " ID:" << _rob_id << "free!" << std::endl;
    }

    int Get_hp() { return _hp; }      //获取机器人血量
    int Get_hot() { return _hot; }      //获取机器人枪口热量
    void Set_hp(int hp) { _hp = hp; }   //设置机器人血量
    void Set_hot(int hot) { _hot = hot; }  //设置机器人枪口热量
    int Get_hp_upline() { return _hot_upline; }

    int Get_hot_upline() { return _hp_upline; }

    int Get_capId() { return _cap_id; }    //获取机器人队伍信息
    int Get_robId() { return _rob_id; }     //获取机器人队伍中代号
    int Get_robType() { return _rob_type; }   //获取机器人类别
    int isTooHot() {
        return (_hot >= _hot_upline) ? (_hot - _hot_upline) : 0;
    }//判断是否过热
    virtual void inc_hp(int) = 0;   //增加机器人血量
    virtual void inc_hot(int) = 0;  //增加机器人枪口热量
    virtual void dec_hp(int) = 0;   //降低机器人血量
    virtual void dec_hot(int) = 0;  //降低机器人枪口热量

    virtual void Set_phUpline(int val) { _hp_upline = val; }//设置机器人最大生命值
    virtual void Set_hotUpline(int val) { _hot_upline = val; }//设置机器人最大热量

    Robot &operator=(Robot &rob) { //重载等号
        _hp_upline = rob._hp_upline;
        _hot_upline = rob._hot_upline;
        _hp = rob._hp;
        _hot = rob._hot;
        _cap_id = rob._cap_id;
        _rob_id = rob._rob_id;
        _rob_type = rob._rob_type;
    }
};


#endif //JUDGER_ROBOT_H

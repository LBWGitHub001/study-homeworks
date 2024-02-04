//
// 用于步兵的数据记录
//

#ifndef JUDGER_SOLIDER_H
#define JUDGER_SOLIDER_H

#include "Robot.h"
#include "Def.h"

class Solider :
        public Robot {
private:
    int _level;

public:
    Solider();

    Solider(Solider &sol);

    Solider(int capId, int robotId, int robotType);//新建机器人
    Solider(int capId, int robotId, int robotType, int level);

    ~Solider();

    void inc_hp(int);   //增加机器人血量
    void inc_hot(int);  //增加机器人枪口热量
    void dec_hp(int);   //降低机器人血量
    void dec_hot(int);  //降低机器人枪口热量

    int Get_level() { return _level; }//获取步兵等级
    void Set_level(int level);//设置步兵等级

    Solider &operator=(Solider &sol);


};


#endif //JUDGER_SOLIDER_H

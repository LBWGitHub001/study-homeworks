//
// 用于工兵的数据记录
//

#ifndef JUDGER_ENGINEER_H
#define JUDGER_ENGINEER_H

#include "Robot.h"

class Engineer
        : public Robot {
private:

public:
    Engineer();

    Engineer(Engineer &eng);

    Engineer(int RobotId, int capId, int robId);//新建机器人
    ~Engineer();

    void inc_hp(int);   //增加机器人血量
    void inc_hot(int);  //增加机器人枪口热量
    void dec_hp(int);   //降低机器人血量
    void dec_hot(int);  //降低机器人枪口热量
    Engineer &operator=(Engineer &eng);

};


#endif //JUDGER_ENGINEER_H

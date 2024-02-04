//
//管理类，此类设置为单例，不可以在外部被创建
//通过map,vector存储机器人的信息,从外部获取命令，并进行执行
//

#ifndef JUDGER_MANAGER_H
#define JUDGER_MANAGER_H

#include "Solider.h"
#include "Engineer.h"
#include "Def.h"
#include "Command.h"
#include <memory>

using namespace std;


class Manager {
private:
    map<int, vector<shared_ptr<Robot>>> surCapAcc;   //(正常)队伍id与队伍的映射
    map<int, vector<shared_ptr<Robot>>> desCapAcc;   //(被摧毁)队伍id与队伍的映射
    list<int> capList;                      //存储队伍信息

    Manager() = default;

    ~Manager() = default;

    shared_ptr<Robot> addRobot(int capId, int RobId, int RobType, map<int, vector<shared_ptr<Robot>>> &lib);

    shared_ptr<Robot> find(int capId, int robotId, map<int, vector<shared_ptr<Robot>>> &robotsLib);

    void removeVec(shared_ptr<Robot> aptr, vector<shared_ptr<Robot>> &vec);

public:
    bool commandRead(Command &cmd, int nums_cat);//读取命令并切返回是否读取成功
    bool refresh();     //刷新当前场上的所有机器人的状态，增加热量
    void showInfo();

    void showDestroy();

    //单例实现
    Manager(const Manager &) = delete;               //禁用拷贝构造
    Manager &operator=(const Manager &) = delete;    //禁用等于号
    static Manager &getManager() {
        static Manager mgr;
        return mgr;
    }

};


#endif //JUDGER_MANAGER_H

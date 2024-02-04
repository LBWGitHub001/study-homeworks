#include "Manager.h"

void Manager::removeVec(shared_ptr<Robot> aptr, vector<shared_ptr<Robot>> &vec) {//移除数据结构中vector中的元素
    remove(vec.begin(), vec.end(), aptr);
    vec.pop_back();
}


shared_ptr<Robot> Manager::addRobot(int capId, int RobId, int RobType, map<int, vector<shared_ptr<Robot>>> &lib) {
    //增加机器人带对应的vector中
    if (!desCapAcc[capId].empty())
        for (auto &iter: desCapAcc[capId]) {
            if (iter != nullptr && iter->Get_robId() == RobId) {
                if (iter->Get_robType() != RobType)
                    return nullptr;//复活的机器人与原来的类型不相同，不能使用同样的Id
                removeVec(iter, desCapAcc[capId]);
                break;
            }
        }
    switch (RobType) {
        case 1: {
            shared_ptr<Robot> eng = make_shared<Engineer>(capId, RobId, RobType);
            if (!lib[capId].empty()) {
                for (auto iter: lib[capId]) {
                    if (iter != nullptr && iter->Get_robId() == RobId) {
                        return nullptr;
                    }

                }
                lib[capId].push_back(eng);
                return eng;
            }
            vector<shared_ptr<Robot>> vec;
            vec.push_back(eng);
            lib[capId] = vec;
            capList.push_back(capId);
            return eng;
        }
        case 0: {
            shared_ptr<Robot> sol = make_shared<Solider>(capId, RobId, RobType);
            if (!lib[capId].empty()) {
                for (auto iter: lib[capId]) {
                    if (iter != nullptr && iter->Get_robId() == RobId) {
                        return nullptr;
                    }

                }
                lib[capId].push_back(sol);
                return sol;
            }
            vector<shared_ptr<Robot>> vec;
            vec.push_back(sol);
            lib[capId] = vec;
            capList.push_back(capId);
            return sol;
        }
        default:
            return nullptr;
    };
    return nullptr;
}

bool Manager::commandRead(Command &cmd, int nums_cat) {//读取从传入的命令,需要指定参数的个数，时间不计入参数
    char head;
    int *cat = new int[nums_cat];
    cat = cmd.Get_cmd(head, cat);
    switch (toupper(head)) {
        case 'A':
            if (addRobot(cat[0], cat[1], cat[2], surCapAcc) != nullptr)
                return true;
            else return false;
        case 'F': {
            shared_ptr<Robot> rob = find(cat[0], cat[1], surCapAcc);
            if (rob != nullptr) {
                rob->dec_hp(cat[2]);
                return true;
            }
            return false;
        }
        case 'H': {
            shared_ptr<Robot> rob = find(cat[0], cat[1], surCapAcc);
            if (rob != nullptr) {
                if (rob->Get_robType() == 0) {
                    rob->Set_hot(cat[2]);
                    return true;
                }
            }
            return false;
        }
        case 'U': {
            shared_ptr<Robot> rob = find(cat[0], cat[1], surCapAcc);
            if (rob != nullptr) {
                if (rob->Get_robType() == 0) {
                    Solider *sol = (Solider *) rob.get();
                    if (cat[2] > sol->Get_level()) {
                        sol->Set_level(cat[2]);
                        return true;
                    }
                }
            }
            return false;
        }
        case 'S':
            showInfo();
            return true;
        default:
            return false;
    }
}


void Manager::showInfo() {//测试用，展示全部的机器人信息，包括存在的和击毁的
    cout << "Survial:" << endl;
    for (auto &it1: surCapAcc) {
        for (auto it2: it1.second) {
            cout << "Cap:" << it2->Get_capId() << " Id:" << it2->Get_robId() << " Type:" << it2->Get_robType() << endl;
            if (it2 != nullptr && it2->Get_robType() == 0)
                cout << "level:" << ((Solider *) it2.get())->Get_level() << endl;
            cout << "Hp:" << it2->Get_hp() << " Hot:" << it2->Get_hot() << endl;
            cout << "############################" << endl;
        }
    }

    cout << "Destoried:" << endl;
    for (auto &it1: desCapAcc) {
        if (!it1.second.empty())
            for (auto it2: it1.second) {
                cout << "Cap:" << it2->Get_capId() << " Id:" << it2->Get_robId() << endl;
                cout << "Hp:" << it2->Get_hp() << " Hot:" << it2->Get_hot() << endl;
            }
    }
    cout << "over!" << endl;

}


shared_ptr<Robot> Manager::find(int capId, int robotId, map<int, vector<shared_ptr<Robot>>> &robotsLib) {
    //根据队伍Id和机器人Id查找机器人，并返回对应的指针，若不存在，发挥空指针
    for (auto iter: robotsLib[capId]) {
        if (iter != nullptr && iter->Get_robId() == robotId)
            return iter;
    }
    return nullptr;
}

bool Manager::refresh() {
    //刷新数据,包括过热扣血，被击毁机器人的移除
    for (const auto &iter: capList) {
        for (auto rob: surCapAcc[iter]) {
            if (rob != nullptr && rob->Get_robType() == 0) {
                rob->dec_hot(1);
                rob->dec_hp(rob->isTooHot());//过热扣血
            }
            if (rob != nullptr && rob->Get_hp() == 0) {//摧毁机器人
                switch (rob->Get_robType()) {
                    case 1: {
                        Engineer *desRob = (Engineer *) addRobot(rob->Get_capId(), rob->Get_robId(), rob->Get_robType(),
                                                                 desCapAcc).get();
                        desRob->Set_hot(0);
                        removeVec(rob, surCapAcc[iter]);
                        break;
                    }
                    case 0: {

                        Solider *desRob = (Solider *) addRobot(rob->Get_capId(), rob->Get_robId(), rob->Get_robType(),
                                                               desCapAcc).get();
                        desRob->Set_hot(0);
                        removeVec(rob, surCapAcc[iter]);
                        break;
                    }

                };
            }

        }

    }
    return true;
}

void Manager::showDestroy() {//展示被摧毁的机器人

    int count = 0;
    for (auto &it1: desCapAcc) {
        if (!it1.second.empty())
            for (auto it2: it1.second) {
                count++;
            }
    }
    int i = 1;
    for (auto &it1: desCapAcc) {
        if (!it1.second.empty())
            for (auto it2: it1.second) {
                cout << "D " << it2->Get_capId() << " " << it2->Get_robId();
                if (i != count)
                    cout << endl;
                i++;
            }
    }
}






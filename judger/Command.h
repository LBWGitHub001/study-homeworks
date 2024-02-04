//
//这个类用于构建命令传递，重载了>>运算符，由于接收标准io口的命令字
//

#ifndef JUDGER_COMMAND_H
#define JUDGER_COMMAND_H

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Command {
private:
    int time;
    char head;
    int *cat;
    int nums_cat;
public:
    Command() = delete;

    Command(int _nums_cat) {
        cat = new int[_nums_cat];
        head = '0';
        nums_cat = _nums_cat;
        time = 0;;
    }

    Command(Command &cmd) {
        cat = new int[cmd.nums_cat];
        nums_cat = cmd.nums_cat;
        head = cmd.head;
        time = cmd.time;
        memcpy(cat, cmd.cat, sizeof(int) * nums_cat);
    }//拷贝构造
    ~Command() { delete[] cat; }

    Command(int time, char head, int a, int b, int c) : time(time), head(head) {
        cat = new int[3];
        nums_cat = 3;
        cat[0] = a;
        cat[1] = b;
        cat[2] = c;
    }

    Command &operator=(Command &cmd) {
        time = cmd.time;
        cat = new int[cmd.nums_cat];
        nums_cat = cmd.nums_cat;
        head = cmd.head;
        memcpy(cat, cmd.cat, sizeof(int) * nums_cat);
        return *this;
    }

    friend istream &operator>>(istream &in, Command &cmd) {

        in >> cmd.time;

        in >> cmd.head;
        for (int i = 0; i < cmd.nums_cat; i++) {

            in >> cmd.cat[i];
        }
        return in;
    }

    friend ostream &operator<<(ostream &out, Command &cmd) {

        out << cmd.time << " ";

        out << cmd.head << " ";
        for (int i = 0; i < cmd.nums_cat; i++) {

            out << cmd.cat[i] << " ";
        }
        return out;
    }

    int *Get_cmd(char &Head, int *Cat) {
        Head = head;
        //memcpy(Cat,cat,nums_cat);
        return cat;
    }

    int getTime() { return time; }

};


#endif //JUDGER_COMMAND_H

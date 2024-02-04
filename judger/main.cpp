#include <iostream>
#include "Manager.h"
#include "Command.h"

long timer = 0;
Command cmd(3);

int main() {
    long a;
    std::cin >> a;
    const long N = a;
    for (int i = 0; i < N; i++) {
        std::cin >> cmd;
        Manager::getManager().commandRead(cmd, 3);
        long timer2 = cmd.getTime();
        for (; timer <= timer2; timer++) {
            Manager::getManager().refresh();
        }
    }
    Manager::getManager().showDestroy();
    return 0;
}
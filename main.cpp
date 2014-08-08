#include "gamefield.h"
#include <iostream>
#include <unistd.h>

int main()
{
    GameField f(56,25,
               //0         10        20        30        40        50
               //123456789012345678901234567890123456789012345678901234567890
                "                        x                               "
                "                      x x                               "
                "            xx      xx            xx                    "
                "           x   x    xx            xx                    "
                "xx        x     x   xx                                  "
                "xx        x   x xx    x x                               "
                "          x     x       x                               "
                "           x   x                                        "
                "            xx                                          "
              ,false, true);
    for(;;) {
        std::cout << "\033[2J\033[1;1H";
        std::cout<<f;
        f.evolve();
        usleep(100000);
    }
    return 0;
}

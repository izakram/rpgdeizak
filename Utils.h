//
// Utils.h
//
#include<cstdlib>

namespace combat_utils {
    int getRolledAttack(int attack) {
        int lowerLimit = attack * .80;
        return (rand() % (attack - lowerLimit + 1)) + lowerLimit;
    }
}
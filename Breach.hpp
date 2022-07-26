#ifndef BREACH_HPP_
#define BREACH_HPP_

#include "Data.hpp"

class Breach {
    public:
    BreachType inferBreach(double value, double lowerLimit, double upperLimit){
        BreachType breachType {NORMAL};
        if(value < lowerLimit) {
            breachType = TOO_LOW;
        }
        else if(value > upperLimit) {
            breachType = TOO_HIGH;
        }
        return breachType;
    }
};

#endif
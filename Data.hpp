#ifndef DATA_HPP_
#define DATA_HPP_

enum BreachType {
    TOO_LOW,
    NORMAL,
    TOO_HIGH
};

enum CoolingType {
    PASSIVE_COOLING,
    HI_ACTIVE_COOLING,
    MED_ACTIVE_COOLING
};

const double PASSIVE_COOLING_LOW {0};
const double PASSIVE_COOLING_HIGH {35};
const double HI_ACTIVE_LOW {0};
const double HI_ACTIVE_HIGH {45};
const double MED_ACTIVE_LOW {0};
const double MED_ACTIVE_HIGH {40};

#endif
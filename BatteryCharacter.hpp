#ifndef BATTERYCHARACTER_HPP_
#define BATTERYCHARACTER_HPP_

#include "Breach.hpp"
#include <iostream>
#include <map>

class BatteryCharacter : public Breach {
    public: 
    CoolingType m_CoolingType;
    std::string m_Brand;

    std::map<CoolingType, std::pair<double,double>> m_CoolingTypeLimits = {
        {PASSIVE_COOLING,std::make_pair(PASSIVE_COOLING_LOW, PASSIVE_COOLING_HIGH)},
        {HI_ACTIVE_COOLING,std::make_pair(HI_ACTIVE_LOW, HI_ACTIVE_HIGH)},
        {MED_ACTIVE_COOLING,std::make_pair(MED_ACTIVE_LOW, MED_ACTIVE_HIGH)}};

    BreachType classifyTemperatureBreach(double temperatureInC){
        return inferBreach(temperatureInC, m_CoolingTypeLimits[m_CoolingType].first, m_CoolingTypeLimits[m_CoolingType].second);
    }
}; 

#endif
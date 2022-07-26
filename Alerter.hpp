#ifndef ALERTER_HPP_
#define ALERTER_HPP_

#include "BatteryCharacter.hpp"
#include <map>

class Alerter : public BatteryCharacter {
    public:
    Alerter() = default;
    Alerter(const CoolingType coolingType, const std::string brand): BatteryCharacter(coolingType, brand)
    {}
    void checkAndAlert(double temperatureInC){
        BreachType breachType = BatteryCharacter::classifyTemperatureBreach(temperatureInC);
        printMessage(sendAlert(breachType));
    }

    void printMessage(std::string msg) {
        std::cout << msg << std::endl;
    }

    virtual std::string sendAlert(BreachType breachType) = 0;

};

class EmailAlerter : public Alerter {
    public:
    EmailAlerter() = default;
    EmailAlerter(const CoolingType coolingType, const std::string brand): Alerter(coolingType, brand),
                m_Recepient{"a.b@c.com"},
                m_LowBreachMsg{"To: " + m_Recepient + "\nHi, the temperature is too low"},
                m_HighBreachMsg{"To: " + m_Recepient + "\nHi, the temperature is too high"},
                m_NormalMsg{"To: " + m_Recepient + "\nHi, the temperature is normal"},
                m_BreachTypeMsgs{{BreachType::NORMAL,m_NormalMsg},
                                {BreachType::TOO_LOW,m_LowBreachMsg},
                                {BreachType::TOO_HIGH,m_HighBreachMsg}}
    {}

    std::string sendAlert(BreachType breachType){
        return m_BreachTypeMsgs[breachType];
    }
    private:
        std::string m_Recepient;
        std::string m_LowBreachMsg;
        std::string m_HighBreachMsg;
        std::string m_NormalMsg;
        std::map<BreachType, std::string> m_BreachTypeMsgs;
};

class ControllerAlerter : public Alerter {
    public:
    ControllerAlerter() = default;
    ControllerAlerter(const CoolingType coolingType, const std::string brand): Alerter(coolingType, brand)
    {}
    std::string sendAlert(BreachType breachType){
        std::string controlMsg = "0xfeed : " + std::to_string(breachType);
        return controlMsg;
  }
};

#endif
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "Alerter.hpp"
#include <iostream>

TEST_CASE("infers the breach according to limits") {
  Breach testBreach;
  REQUIRE(testBreach.inferBreach(10, 20, 30) == BreachType::TOO_LOW);
  REQUIRE(testBreach.inferBreach(15, 20, 30) == BreachType::TOO_LOW);
  REQUIRE(testBreach.inferBreach(20, 20, 30) == BreachType::NORMAL);
  REQUIRE(testBreach.inferBreach(25, 20, 30) == BreachType::NORMAL);
  REQUIRE(testBreach.inferBreach(30, 20, 30) == BreachType::NORMAL);
  REQUIRE(testBreach.inferBreach(35, 20, 30) == BreachType::TOO_HIGH);
}

TEST_CASE("identify breach type for Passive cooling and send alert"){
  EmailAlerter testEmailAlerter(CoolingType::PASSIVE_COOLING, "Siemens");
  std::string testLowBreachMsg = "To: a.b@c.com\nHi, the temperature is too low";
  std::string testHighBreachMsg = "To: a.b@c.com\nHi, the temperature is too high";
  std::string testNormalMsg = "To: a.b@c.com\nHi, the temperature is normal";

  REQUIRE(testEmailAlerter.sendAlert(BreachType::TOO_HIGH) == testHighBreachMsg);
  REQUIRE(testEmailAlerter.sendAlert(BreachType::TOO_LOW) == testLowBreachMsg);
  REQUIRE(testEmailAlerter.sendAlert(BreachType::NORMAL) == testNormalMsg);

  REQUIRE(testEmailAlerter.classifyTemperatureBreach(40) == BreachType::TOO_HIGH);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(0) == BreachType::NORMAL);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(-1) == BreachType::TOO_LOW);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(35) == BreachType::NORMAL);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(10) == BreachType::NORMAL);

  ControllerAlerter testControlAlerter(CoolingType::PASSIVE_COOLING, "Siemens");
  REQUIRE(testControlAlerter.sendAlert(BreachType::TOO_HIGH) == "0xfeed : 2");
  REQUIRE(testControlAlerter.sendAlert(BreachType::TOO_LOW) == "0xfeed : 0");
  REQUIRE(testControlAlerter.sendAlert(BreachType::NORMAL) == "0xfeed : 1");
}

TEST_CASE("identify breach type for High active cooling and send alert"){
  EmailAlerter testEmailAlerter(CoolingType::HI_ACTIVE_COOLING, "Siemens");
  
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(50) == BreachType::TOO_HIGH);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(0) == BreachType::NORMAL);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(-1) == BreachType::TOO_LOW);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(45) == BreachType::NORMAL);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(20) == BreachType::NORMAL);
}

TEST_CASE("identify breach type for medium active cooling and send alert"){
  EmailAlerter testEmailAlerter(CoolingType::MED_ACTIVE_COOLING, "Siemens");

  REQUIRE(testEmailAlerter.classifyTemperatureBreach(45) == BreachType::TOO_HIGH);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(0) == BreachType::NORMAL);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(-1) == BreachType::TOO_LOW);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(40) == BreachType::NORMAL);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(10) == BreachType::NORMAL);
}
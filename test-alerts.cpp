#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "Alerter.hpp"
#include <iostream>

TEST_CASE("infers the breach according to limits") {
  Breach testBreach;
  REQUIRE(testBreach.inferBreach(12, 20, 30) == BreachType::TOO_LOW);
  REQUIRE(testBreach.inferBreach(20, 20, 30) == BreachType::NORMAL);
  REQUIRE(testBreach.inferBreach(25, 20, 30) == BreachType::NORMAL);
  REQUIRE(testBreach.inferBreach(30, 20, 30) == BreachType::NORMAL);
  REQUIRE(testBreach.inferBreach(31, 20, 30) == BreachType::TOO_HIGH);
}

TEST_CASE_METHOD(EmailAlerter, "identify breach type and send alert"){
  EmailAlerter testEmailAlerter;
  std::string testLowBreachMsg = "To: a.b@c.com\nHi, the temperature is too low";
  std::string testHighBreachMsg = "To: a.b@c.com\nHi, the temperature is too high";
  std::string testNormalMsg = "To: a.b@c.com\nHi, the temperature is normal";

  REQUIRE(testEmailAlerter.sendAlert(BreachType::TOO_HIGH) == testHighBreachMsg);
  REQUIRE(testEmailAlerter.sendAlert(BreachType::TOO_LOW) == testLowBreachMsg);
  REQUIRE(testEmailAlerter.sendAlert(BreachType::NORMAL) == testNormalMsg);

  REQUIRE(testEmailAlerter.classifyTemperatureBreach(40) == BreachType::TOO_HIGH);
  REQUIRE(testEmailAlerter.classifyTemperatureBreach(-1) == BreachType::TOO_LOW);
}
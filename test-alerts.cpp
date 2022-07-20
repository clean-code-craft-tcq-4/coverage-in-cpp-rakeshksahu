#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to lower limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("classify temperate breach") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 45) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 10) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == TOO_HIGH);
}

TEST_CASE("Test checkAndAlert for HI_ACTIVE_COOLING") {

  BatteryCharacter batteryHAC;
  batteryHAC.coolingType = HI_ACTIVE_COOLING;

  checkAndAlert(TO_EMAIL, batteryHAC, 50);
}

TEST_CASE("Test checkAndAlert for MED_ACTIVE_COOLING") {

  BatteryCharacter batteryMAC;
  batteryMAC.coolingType = MED_ACTIVE_COOLING;

  checkAndAlert(TO_CONTROLLER, batteryMAC, 50);
}

TEST_CASE("Test checkAndAlert for PASSIVE_COOLING") {

  BatteryCharacter batteryPC;
  batteryPC.coolingType = PASSIVE_COOLING;

  checkAndAlert(TO_EMAIL, batteryPC, -10);

}

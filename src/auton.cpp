#include "constants.h"
#include "main.h"
#include "auton.h"
#include "api.h"
#include "okapi/api.hpp"

void auton() {
    lcd::initialize();
	lcd::set_background_color(LV_COLOR_BLACK);
	lcd::set_text_color(LV_COLOR_GREEN);
    lcd::print(0, "%d | %d", (name), (team));
    lcd::print(2, "AUTONOMOUS RUNNING");
    
    std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
        .withMotors( { -1, -9 }, { 2,10 })
        .withGains(
            { 0.001, 0, 0.0001 }, //distnacfe
            { 0.001, 0, 0.0001 }, //turn
            { 0.001, 0, 0.0001 } //angle
        )
        .withDimensions(GEAR_SET, {{ 4_in, 11.5_in }, imev5GreenTPR})
        .withMaxVoltage(127)
        .withLogger(
            std::make_shared<Logger> (
                TimeUtilFactory::createDefault().getTimer(),
                "/ser/sout",
                Logger::LogLevel::debug
            )
        )
        .build();

    toggle_im();
    chassis -> moveDistance(-0.1_m);
    chassis -> turnToAngle(90_deg);
    chassis -> moveDistance(0.1_m);
    toggle_im();
    toggle_rm();
    sleep(5);
    toggle_rm();
}

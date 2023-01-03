#include "auton.h"
#include "main.h"

using namespace okapi;

void auton() {
    lcd::initialize();
	lcd::set_background_color(LV_COLOR_BLACK);
	lcd::set_text_color(LV_COLOR_GREEN);
    lcd::print(0, "%d | %d", (NAME), (TEAM));
    lcd::print(2, "AUTONOMOUS RUNNING");
    
    std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
        .withMotors( { -1, -9 }, { 2,10 })
        .withDimensions(okapi::AbstractMotor::gearset::green, {{ 4_in, 11.5_in }, imev5GreenTPR})
        .withMaxVoltage(127)
        .withLogger(
            std::make_shared<Logger> (
                TimeUtilFactory::createDefault().getTimer(),
                "/ser/sout",
                Logger::LogLevel::debug
            )
        )
        .build();
    std::shared_ptr<AsyncPositionController<double, double>> intake = AsyncPosControllerBuilder()
        .withMotor(9)
        .withGains(
            { 
                0.001, 
                0.0001, 
                0.0001 
            }
        )
        .build();

    std::shared_ptr<AsyncPositionController<double, double>> flywheel = AsyncPosControllerBuilder()
        .withMotor(5)
        .withGains(
            { 
                0.001, 
                0.0001, 
                0.0001 
            }
        )
        .build();

    flywheel->setTarget(200);
    chassis->moveDistance(0.5_m);
    intake->setTarget(200);

}

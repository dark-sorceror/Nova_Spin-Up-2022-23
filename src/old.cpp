/*
#include "main.h"
#include "auton.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"

#include <cmath>
#include <math.h>

Controller ctr(E_CONTROLLER_MASTER);
Motor_Group lmtrs({1, 18});
Motor_Group rmtrs({2, 10});
Motor rm(4);
Motor im(3);
Motor cm(8);
Motor em(5);
ADIDigitalIn ls('d');

const int DEADBAND = 5;
const int DELAY_T = 20;
const std::string NAME = "cos(b) robotics";
const std::string TEAM = "3388N";

std::uint32_t now = pros::millis();
const int position = cm.get_raw_position(&now);

void initialize() {
	lcd::initialize();
	lcd::set_background_color(LV_COLOR_BLACK);
	lcd::set_text_color(LV_COLOR_GREEN);
	lcd::print(0, "%i", NAME);
	lcd::print(1, "%i", TEAM);

	lmtrs.set_brake_modes(E_MOTOR_BRAKE_HOLD);
	rmtrs.set_brake_modes(E_MOTOR_BRAKE_HOLD);
	cm.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	rm.set_gearing(pros::E_MOTOR_GEARSET_18);
	cm.set_gearing(pros::E_MOTOR_GEARSET_36);

	cm.set_encoder_units(E_MOTOR_ENCODER_COUNTS);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	auton();
}

void opcontrol() {
	cm.move_relative(-3375, 100);

	while (true) {
		int x = ctr.get_analog(ANALOG_RIGHT_X);
		int y = ctr.get_analog(ANALOG_LEFT_Y);

		if (abs(x) <= DEADBAND) x = 0;
		if (abs(y) <= DEADBAND) y = 0;

		int lp = -y - x;
		int rp = -y + x; 
		lmtrs = lp;
		rmtrs = -rp;

		if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			cm.move_relative(-50, 100);
			pros::delay(500);
			cm.move_relative(-8940, 100);
		}

		if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			em.move_relative(10000000, 200);
		}
		if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			em.move_velocity(-200);
		} else {
			em.move_velocity(0);
		}

		lcd::print(2, "position %d", cm.get_position());

		if (ctr.get_digital(E_CONTROLLER_DIGITAL_L2)) im.move_velocity(-600);
		else if (ctr.get_digital(E_CONTROLLER_DIGITAL_L1)) im.move_velocity(600);
		else im.move(0);

		if (ctr.get_digital(E_CONTROLLER_DIGITAL_A)) rm.move(127);
		else rm.move(0);
		
		pros::delay(20);

	}

}

#include "auton.h"
#include "main.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/control/async/asyncPosControllerBuilder.hpp"
#include "okapi/impl/device/motor/motor.hpp"
#include "pros/rtos.hpp"
#include <memory>

using namespace okapi;

void auton() {
    lcd::initialize();
	lcd::set_background_color(LV_COLOR_BLACK);
	lcd::set_text_color(LV_COLOR_GREEN);
    lcd::print(0, "%d | %d", (NAME), (TEAM));
    
    std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
        .withMotors( { 1, 18 }, { -2,-10 })
        .withDimensions(okapi::AbstractMotor::gearset::blue, {{ 4_in, 11.5_in }, imev5BlueTPR})
        .withMaxVelocity(100)
        .withLogger(
            std::make_shared<Logger> (
                TimeUtilFactory::createDefault().getTimer(),
                "/ser/sout",
                Logger::LogLevel::debug
            )
        )
        .build();


    //cm.move_relative(-3350, 100);
    
    rm.move_relative(700, 200);
    chassis->moveDistanceAsync(-0.25_m);
    pros::delay(1000);
    chassis->moveDistance(0.25_m);
    pros::delay(1000);
    
    chassis->moveDistance(0.5_m);
    
    
    chassis->turnAngle(45_deg);
    pros::delay(1000);
    chassis->moveDistance(-2_m);
    pros::delay(1000);
    chassis->turnAngle(180_deg);
    pros::delay(1000);
    cm.move_relative(-50, 100);
    pros::delay(500)                          ;
    cm.move_relative(-4470,100);
    pros::delay(1000);
    chassis->turnAngle(180_deg);
    pros::delay(1000);
    im.move_relative(-4000, 600);
    chassis->moveDistanceAsync(-1.5_m);
    
    cm.move_relative(-3350, 100);
    chassis->moveDistance(-0.5_m);
    cm.move_relative(-50, 100);
    pros::delay(500);
    cm.move_relative(-8940, 100);
    pros::delay(1000);
    chassis->turnAngle(150_deg);
    pros::delay(1000);
    im.move_relative(-4000, 600);
    chassis->moveDistanceAsync(-1_m);
    pros::delay(1000);
    chassis->turnAngle(-150_deg);
    pros::delay(1000);
    cm.move_relative(-50, 100);
    pros::delay(500);
    cm.move_relative(-8940, 100);

}
    */


    


    

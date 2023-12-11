#include "main.h"
#include "auton.h"
#include "selector.h"

Controller ctr(E_CONTROLLER_MASTER);
Motor_Group leftDrive({-18, 19, 20});
Motor_Group rightDrive({-8, 9, 10});
Imu imu(7);
Motor arm(16);
Motor flywheel(17);
ADIDigitalOut piston_1('A');
ADIDigitalOut piston_2('G');

const int DEADBAND = 5;
const int DELAY_T = 20;
const std::string NAME = "cos(b) robotics";
const std::string TEAM = "3388N";

void initialize() {
    imu.reset();

    leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    rightDrive.set_brake_modes(E_MOTOR_BRAKE_COAST);
    arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);

    lcd::initialize();
	lcd::set_background_color(LV_COLOR_BLACK);
	lcd::set_text_color(LV_COLOR_GREEN);
	lcd::print(0, "%s", NAME);  
	lcd::print(1, "%s", TEAM);
}

void disabled() {}

void competition_initialize() {
    selector::init();
}

void autonomous() {
    if (selector::auton == 1) {
        auton_red_close();
    }
}

void opcontrol() {
	while (true) {
		int x = ctr.get_analog(ANALOG_RIGHT_X);
		int y = ctr.get_analog(ANALOG_LEFT_Y);

		if (abs(x) <= DEADBAND) x = 0;
		if (abs(y) <= DEADBAND) y = 0;

		int leftPower = y - x;
		int rightPower = y + x; 
		leftDrive = leftPower;
		rightDrive = -rightPower;

        if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            arm = 80;
        } else if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            arm = -80;
        } else {
            arm = 0;
        }

        if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            flywheel = 95;
        } else if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            flywheel = -95;
        } else {
            flywheel = 0;
        }

        if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
            piston_1.set_value(100);
            piston_2.set_value(100);
        }

        if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            piston_1.set_value(0);
            piston_2.set_value(0);
        }
	
		pros::delay(20);
	}
}
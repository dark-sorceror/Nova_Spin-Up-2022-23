#include "main.h"
#include "auton.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"

#include <math.h>

Controller ctr(E_CONTROLLER_MASTER);
Motor_Group lmtrs({19, 20});
Motor_Group rmtrs({17, 18});
Motor rm(8);
Motor im(9);
Motor fm(5);
Motor ixm(4);

const int DEADBAND = 5;
const int DELAY_T = 20;
const okapi::AbstractMotor::gearset GEAR_SET = okapi::AbstractMotor::gearset::green;
const std::string NAME = "cos(b) robotics";
const std::string TEAM = "3388N";

int cycles = 0;
int count = 0;

bool rm_on = false;
bool im_on = false;
bool fly_on = false;
bool ixm_on = false;

void toggle_rm() { 
    rm_on = !rm_on;
    rm = 127; if (!rm_on); else rm = 0;
} 

void toggle_im(bool reverse) {
    im_on = !im_on;
	if (!im_on) {
		if (reverse) { 
			im = 127; 
		} else {
			im = -127;
		}
	} else {
		im.brake(); // test
	}
}

void toggle_fm() {
    fly_on = !fly_on;
    if (!fly_on) {
		ixm = 127;
		fm = -150;
    } else { 
        fm = 0;
        ixm = 0;
    }
}

void toggle_ixm() {
	ixm_on = !ixm_on;
	ixm = -127; if (!ixm_on); else ixm = 0;
}



void initialize() {
	printf("initialize");

	lmtrs.set_brake_modes(E_MOTOR_BRAKE_COAST);
	rmtrs.set_brake_modes(E_MOTOR_BRAKE_COAST);
	rm.set_brake_mode(E_MOTOR_BRAKE_COAST);
	//im.set_brake_mode(E_MOTOR_BRAKE_COAST);

	im.set_brake_mode(E_MOTOR_BRAKE_BRAKE); //TEST

	lcd::initialize();
	lcd::set_background_color(LV_COLOR_BLACK);
	lcd::set_text_color(LV_COLOR_GREEN);

	//autonomous();
}

void disabled() {}

void competition_initialize() {
	autonomous();
}

void autonomous() {
	printf("autonomous");
	auton();
}

void opcontrol() {
	lcd::print(0, "%s | %s", (NAME), (TEAM));

	while (true) {
		int x = ctr.get_analog(ANALOG_RIGHT_X);
		int y = ctr.get_analog(ANALOG_LEFT_Y);

		if (abs(x) < DEADBAND) x = 0;	
		if (abs(y) < DEADBAND) y = 0;

		// arcade control
		int lp = -y - x;
		int rp = -y + x; 
		lmtrs = lp;
		rmtrs = -rp;

		//pros::Task::create()
		if (ctr.get_digital(E_CONTROLLER_DIGITAL_LEFT)) toggle_rm();
		if (ctr.get_digital(E_CONTROLLER_DIGITAL_A)) { toggle_im(false); }
		else if (ctr.get_digital(E_CONTROLLER_DIGITAL_DOWN)) { toggle_im(true); }
		if (ctr.get_digital(E_CONTROLLER_DIGITAL_X)) toggle_fm();
		ixm = ctr.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

		lcd::print(2, "Time Elapsed: %d:%d", (((count / 50) % 3600) / 60), ((count / 50) % 60));

		ctr.print(0, 0, "Flywheel: %d", (fm.get_voltage()));

		//testing
		for (int i = 0; i<2; i++) lcd::print(i+3, "Motor (%d) | Position: %d | Temperature: %d", 
			(lmtrs[i].get_port()), (lp), (lmtrs[i].get_position()), (round(lmtrs[i].get_temperature())));
		for (int i = 0; i<2; i++) lcd::print(i+5, "Motor (%d) | Position: %d | Temperature: %d", 
			(rmtrs[i].get_port()), (rp), (rmtrs[i].get_position()), (round(rmtrs[i].get_temperature())));
		lcd::print(7, "Motor (3): %d | Motor (11): %d", (im.get_voltage()), (rm.get_voltage()));

		delay(DELAY_T);
		count ++;
	}
}
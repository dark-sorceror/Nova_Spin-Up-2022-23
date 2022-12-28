#include "main.h"
#include "auton.h"
#include "constants.h"

#include <math.h>

void initialize() {
	printf("initialize");

	lmtrs.set_brake_modes(E_MOTOR_BRAKE_COAST);
	rmtrs.set_brake_modes(E_MOTOR_BRAKE_COAST);
	rm.set_brake_mode(E_MOTOR_BRAKE_COAST);
	im.set_brake_mode(E_MOTOR_BRAKE_COAST);

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
	lcd::print(0, "%s | %s", (name), (team));

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
		if (ctr.get_digital(E_CONTROLLER_DIGITAL_L1)) toggle_im();
		if (ctr.get_digital(E_CONTROLLER_DIGITAL_X)) toggle_fm();

		lcd::print(2, "Time Elapsed: %d:%d", (((count / 50) % 3600) / 60), ((count / 50) % 60));

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
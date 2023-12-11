/*
#include "main.h"


void opcontrol() {
    
    auto profile = okapi::AsyncMotionProfileControllerBuilder().withLimits(
        {
            1.0,
            2.0,
            10.0
        }
    ).withOutput(chassis)
    .buildMotionProfileController();

    profile->generatePath({
        {0_ft, 0_ft, 0_deg},
        {0_ft, 3_ft, 0_deg}
    }, "Test");

    profile->setTarget("Test");

    profile->waitUntilSettled();

    //motor groups

    okapi::Controller master(okapi::ControllerId::master);

    auto chassis = okapi::ChassisControllerBuilder().withMotors(topLMot, topRMot, botLMot, topLMot).withDimensions({okapi::AbstractMotor::gearset::green, (84.0 / 60.0)}, {{4_in, 12.5_in}, okapi::imev5GreenTPR}).build();

    auto xModel = std::dynamic_pointer_cast<okapi::XDriveModel>(chassis->getModel());

    int flyState = 0;

    auto upArrow = okapi::ControllerButton(okapi::ControllerDigital::up);
    auto downArrow = okapi::ControllerButton(okapi::ControllerDigital::up);

    auto intake = okapi::Motor(intake1);
    
      while (true) {
        //arcade drive
        xModel->xArcade(
              master.getAnalog(strafeU),
              master.getAnalog(strafeD),
              master.getAnalog(rot)
        );

        switch (flyState) {
            case 0:
                intake.moveVelocity(0);
            case 1:
                intake.moveVoltage(120);
			case 2:
				
        }

        

        if (upArrow.isPressed() == true) {
            printf("%i", flyState);
            flyState = 1;
			
			ctr.get_digital_new_press(controller_digital_e_t button)
            upArrow.changedToReleased();
        } else if (downArrow.controllerGet()) {
            flyState = 2;
            downArrow.changedToReleased();
        }

        //little bit of delay
        pros::delay(20);




      }

void moveForward(float goalPos, float maxSpeed) {


    float startPos = left_drive.getCurrentPosition();
    float prevError = goalPos - startPos;
    float integral = 0;
    
    float error = goalPos - getCurrentPosition();
    
    float pid = error * kP;
    motor

    // move motors with 'pid' amount
    prevError = error;

    wait(15, msec);
    // stop motors
   
}
*/
#include "auton.h"
#include "main.h"
#include "pros/rtos.hpp"
#include <cmath>

/*
float startPos = left_drive.getCurrentPosition();
    float prevError = goalPos - startPos;
    float integral = 0;
    
    float error = goalPos - getCurrentPosition();
    
    float pid = error * kP;
    motor

    // move motors with 'pid' amount
    prevError = error;

    wait(15, msec);
    // stop motors*/

double averageDriveEncoderValue() {
    return fabs(leftDrive[0].get_position()) + fabs(leftDrive[1].get_position()) + fabs(leftDrive[2].get_position()) + fabs(rightDrive[0].get_position()) + fabs(rightDrive[1].get_position()) + fabs(rightDrive[2].get_position());
}

void resetDriveEncoders() {
    leftDrive.tare_position();
    rightDrive.tare_position();
}

void setDrive(int left, int right) {
    leftDrive[0] = -left;
    leftDrive[1], leftDrive[2] = left;
    rightDrive[0] = -right;
    rightDrive[1], rightDrive[2] = right;
}

void translate(int units, int voltage) {
    int direction = abs(units) / units;

    resetDriveEncoders();
    imu.reset();

    while(averageDriveEncoderValue() < abs(units)) {
        setDrive(voltage * direction + imu.get_heading(), voltage * direction - imu.get_heading());
        pros::delay(10);
    }

    setDrive(-10 * direction, -10 * direction);
    pros::delay(50);

    setDrive(0, 0);
}

void rotate(int degrees, int voltage) {
    int direction = abs(degrees) / degrees;

    imu.reset();

    setDrive(-voltage * direction, voltage * direction);

    while (fabs(imu.get_heading()) < abs(degrees * 10) - 50) {
        pros::delay(10);
    }

    pros::delay(100);

    if (fabs(imu.get_heading()) > abs(degrees * 10)) {
        setDrive(0.5* voltage * direction, 0.5* -voltage * direction);
        while (fabs(imu.get_heading()) > abs(degrees * 10)) {
            pros::delay(10);
        }
    } else if (fabs(imu.get_heading()) < abs(degrees * 10)) {
        setDrive(0.5* -voltage * direction, 0.5* voltage * direction);
         while (fabs(imu.get_heading()) < abs(degrees * 10)) {
            pros::delay(10);
        }
    }

    setDrive(0, 0);
}
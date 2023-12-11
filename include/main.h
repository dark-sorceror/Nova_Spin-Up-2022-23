/**
 * \file main.h
 *
 * Copyright (c) 2017-2022, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_

#define _PROS_MAIN_H_
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "okapi/api.hpp"
#include <iostream>
#include <string>

extern pros::Controller ctr;
extern pros::Motor_Group leftDrive;
extern pros::Motor_Group rightDrive;
extern pros::IMU imu;
extern pros::Motor arm;
extern pros::Motor flywheel;
extern pros::ADIDigitalOut piston_1;
extern pros::ADIDigitalOut piston_2;

extern const std::string NAME;
extern const std::string TEAM;

using namespace pros;

#ifdef __cplusplus

extern "C" {
    #endif
    void autonomous(void);
    void initialize(void);
    void disabled(void);
    void competition_initialize(void);
    void opcontrol(void);
    #ifdef __cplusplus
}

#endif

#ifdef __cplusplus
#endif

#endif

/**
 * \file constants.h
 *
 * Copyright (c) 2017-2022, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _CONSTANTS_H_

#define _CONSTANTS_H_

#include "api.h"
#include <iostream>
#include "okapi/api.hpp"

extern pros::Controller ctr;
extern pros::Motor_Group lmtrs;
extern pros::Motor_Group rmtrs;
extern pros::Motor im;
extern pros::Motor rm;
extern pros::Motor fm;

extern const int DEADBAND;
extern const int DELAY_T;
extern const okapi::AbstractMotor::gearset GEAR_SET;
extern const std::string name;
extern const std::string team;

extern int cycles;
extern int count;

void toggle_im(void);
void toggle_rm(void);
void toggle_fm(void);

#endif
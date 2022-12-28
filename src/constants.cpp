#include "api.h"
#include "okapi/api.hpp"
#include "constants.h"
#include "pros/misc.h"
#include <iostream>
#include <string>

using namespace pros;

Controller ctr(E_CONTROLLER_MASTER);
Motor_Group lmtrs({19, 20});
Motor_Group rmtrs({17, 18});
Motor rm(8);
Motor im(9);
Motor fm(5);

const int DEADBAND = 5;
const int DELAY_T = 20;
const okapi::AbstractMotor::gearset GEAR_SET = okapi::AbstractMotor::gearset::green;
const std::string name = "cos(b) robotics";
const std::string team = "3388N";

int cycles = 0;
int count = 0;

bool rm_on = false;
bool im_on = false;
bool fly_on = false;

void toggle_rm() { 
    rm_on = !rm_on;
    rm = 127; if (!rm_on); else rm = 0;
} 

void toggle_fm() {
    fly_on = !fly_on;
    if (!fly_on) {
        fm = -127; 
        im = 127;
    } else { 
        fm = 0;
        
    }
}

//test
void toggle_im() {
    im_on = !im_on;
    im.move_velocity(-127); if (!im_on); else im.brake();
}

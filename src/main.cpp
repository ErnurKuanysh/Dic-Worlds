#include "main.h"

void initialize() {
    chassis.calibrate();
    chassis.setPose(-57, 32.7, 80);
	pros::lcd::initialize();
    pros::Task screenTask(lcdscreen);
    pros::Task Int_cata(cata_int);
    pros::Task Future(FShoot);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    // Beta();
    WP();
}


void opcontrol() {
    Control();
    // lcdscreen();
}

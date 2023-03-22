#ifndef AUTO_H
#define AUTO_H 

#include "main.h"

void Beta(){
}

void WP(){
    BoostShoot();
    delay(100);
    Reload = false;
    intake_spin = true;
    chassis.moveTo(-70, 27, 300);
    chassis.moveTo(-35, 0, 100, 80);
    Reload = true;
    chassis.moveTo(-38, 0, 650, 80);
    chassis.moveTo(-13, 0, 2100, 40);
    // chassis.turnTo(-36,12,500);
    // chassis.follow("Wp1.txt", 3000, 10);
    intake_spin = false;
    chassis.turnTo(57, 57, 600);
    BoostShoot();
    delay(300);
    chassis.setPose(prePose);
    delay(200);
    intake_spin = true;
    chassis.moveTo(-22, -7, 600);
    chassis.turnTo(38, -52, 800);
    chassis.moveTo(38, -52, 2300, 90);
    chassis.turnTo(35, -69, 600, true);
    intake_spin = false;
    chassis.moveTo(35, -69, 550, 40);
    intake_spin = true;
    delay(150);
    intake_spin = false;
    chassis.moveTo(30, -48, 1000);
    chassis.turnTo(58, 58, 800, false, 50);
    FutureShoot(200, true);
    chassis.moveTo(58, 58, 420);
    chassis.moveTo(34, -48, 1000);
    // FutureShoot(240, true);
    // chassis.moveTo(62, 0, 360);
    // chassis.moveTo(38, -52, 500);

}


#endif
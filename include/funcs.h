#ifndef CONTROL_H
#define CONTROL_H

#include "main.h"

double Front = 0;
double Turn = 0;
double FrontT = 6;
double TurnT = 6.2;

bool pres[3] = {0,0,0};

bool ButtonPressed = false;
double IntakeSpeed = 0;

int catapos = 38;
bool IsCataReady = true;
bool IsCataDown = false;

bool intake_spin = false;
bool cata_spin = false;
bool Reload = true;
int futureShoot = -1;
bool boost = false;
int posedelay = 0;

lemlib::Pose prePose = chassis.getPose();

void Shoot(){
    prePose = chassis.getPose();
    cata_spin = true;
}

void BoostShoot(){
    Shoot();
    delay(50);
    Booster.set_value(true);
}

void Control(){
    while(true){
        // Front = pow(exp(1), (abs(Con.get_analog(ANALOG_LEFT_Y)) - 127) * Turn_t) * Con.get_analog(ANALOG_LEFT_Y);
        // Turn = pow(exp(1), (abs(Con.get_analog(ANALOG_RIGHT_X)) - 127) * Turn_t) * Con.get_analog(ANALOG_RIGHT_X);
        Front = double(exp(((fabs(Con.get_analog(ANALOG_LEFT_Y)) - 127) * FrontT) / 1000) * Con.get_analog(ANALOG_LEFT_Y)) * 12000 / 127;
        Turn = double(exp(((fabs(Con.get_analog(ANALOG_RIGHT_X)) - 127) * TurnT) / 1000) * Con.get_analog(ANALOG_RIGHT_X)) * 12000 / 127;
        Left1.move_voltage(Front + Turn);
        Left2.move_voltage(Front + Turn);
        Left3.move_voltage(Front + Turn);
        Right1.move_voltage(Front - Turn);
        Right2.move_voltage(Front - Turn);
        Right3.move_voltage(Front - Turn);
        if(Con.get_digital(E_CONTROLLER_DIGITAL_L2)){
            if(pres[0] == false){
                pres[0] = true;
            }
        }else{
            pres[0] = false;    
        }

        if(Con.get_digital(DIGITAL_LEFT)){
            BoostShoot();
        }

        delay(2);
    }
}


void cata_int(){
    while (true)
    {
        if(IntakeL.get_actual_velocity() <= 2 and Index.get() < catapos + 20){
            IsCataReady = true;
        }else if(Index.get() > catapos + 20){
            if(!ButtonPressed and IsCataDown){
                catapos ++;
            }
            IsCataReady = false;
            ButtonPressed = false;
            IsCataDown = false;
            cata_spin = false;
            Booster.set_value(false);
            posedelay = 30;
        }
        if(Con.get_digital(DIGITAL_L1)){
            ButtonPressed = true;
        }
        if(posedelay == 0){
            // chassis.setPose(prePose);
        }
        if(Index.get() < catapos + 20) IsCataDown = true;
        IntakeSpeed = ((Index.get() > catapos) * (Index.get() - catapos + 5)) * !IsCataReady * 3 * Reload + (Con.get_digital(DIGITAL_R1) + intake_spin) * -100 * bool(IsCataReady + !Reload) + (Con.get_digital(DIGITAL_L1) + cata_spin) * 100;
        IntakeL.move_voltage(IntakeSpeed * 120);
        IntakeR.move_voltage(IntakeSpeed * 120);
        delay(10);
        posedelay -= posedelay < 0 ? 0 : 1;
    }
}

void FutureShoot(int Time, bool Boost){
    boost = Boost;
    futureShoot = Time / 10;
}

void FShoot(){
    while(true){
        if(futureShoot == 0){
            BoostShoot();
        }
        futureShoot -= futureShoot < 0 ? 0 : 1;
        delay(10);
    }
}


void lcdscreen() {
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); 
        // pros::lcd::print(3, "Future: %f", double(futureShoot)); 
        // pros::lcd::print(4, "Cata: %f", double(cata_spin));s
        pros::lcd::print(3, "Gyro: %f", double(Gyro.get_heading()));
        // pros::lcd::print(3, "catapso: %f", double(catapos));
        // pros::lcd::print(4, "button: %f", double(ButtonPressed));
        // lcd::print(0, "Con %f\n", double(exp(((fabs(Con.get_analog(ANALOG_LEFT_Y)) - 127) * 6) / 1000) * Con.get_analog(ANALOG_LEFT_Y)));
        // lcd::print(1, "rigth: %d\n", Con.get_analog(ANALOG_LEFT_Y));
        pros::delay(10);
    }
}

#endif
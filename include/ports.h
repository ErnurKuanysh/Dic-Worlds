#ifndef PORTS_H
#define PORTS_H

#include "main.h"

Controller Con(E_CONTROLLER_MASTER);
Motor Left1(13, pros::E_MOTOR_GEARSET_06);
Motor Left2(12, pros::E_MOTOR_GEARSET_06);
Motor Left3(11, pros::E_MOTOR_GEARSET_06, true);
Motor Right1(18, pros::E_MOTOR_GEARSET_06, true);
Motor Right2(16, pros::E_MOTOR_GEARSET_06, true);
Motor Right3(17, pros::E_MOTOR_GEARSET_06);
Motor IntakeL(4, pros::E_MOTOR_GEARSET_06);
Motor IntakeR(2, pros::E_MOTOR_GEARSET_06, true);
Distance Index(8);
Imu Gyro(7);

ADIDigitalOut Booster('A');

extern Controller Con;
extern Motor Left1;
extern Motor Left2;
extern Motor Left3;
extern Motor Right1;
extern Motor Right2;
extern Motor Right3;
extern Motor IntakeL;
extern Motor IntakeR;
extern Distance Index;
extern Imu Gyro;

extern ADIDigitalOut Booster;
 
// drivetrain motor groups
MotorGroup left_side_motors({Left1, Left2, Left3});
MotorGroup right_side_motors({Right1, Right2, Right3});
 
lemlib::Drivetrain_t drivetrain {
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    10, // track width
    2.75, // wheel diameter
    600 // wheel rpm
};

// pros::ADIEncoder left_enc('A', 'B', true);/
// pros::ADIEncoder right_enc('C', 'D', false);
 
// left tracking wheel
// lemlib::TrackingWheel left_tracking_wheel(&left_enc, 2.75, -3.5); // 2.75" wheel diameter, -4.6" offset from tracking center
// right tracking wheel
// lemlib::TrackingWheel right_tracking_wheel(&right_enc, 2.75, 3.5); // 2.75" wheel diameter, 1.7" offset from tracking center
 
// odometry struct
lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &Gyro // inertial sensor
};
 
// forward/backward PID
lemlib::ChassisController_t lateralController {
    4, // kP
    30, // kD
    0.5, // smallErrorRange
    100, // smallErrorTimeout
    1.5, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    2.4, // kP
    20, // kD
    0.4, // smallErrorRange
    100, // smallErrorTimeout
    1.5, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
 
// create the chassis
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

#endif 
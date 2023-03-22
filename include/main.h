#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

#include "api.h"
#include <cmath>


// #include "okapi/api.hpp"
#include "pros/api_legacy.h"
#include "lemlib/api.hpp"

using namespace pros;
// using namespace pros::literals;
// using namespace okapi;

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
#include "ports.h"
#include "funcs.h"
#include "auto.h"
//#include <iostream>
#endif

#endif  // _PROS_MAIN_H_

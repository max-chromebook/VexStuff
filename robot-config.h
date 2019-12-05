#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
#include "vex_triport.h"
//
using namespace vex;
vex::brain Brain;
vex::motor FrontLeft(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor FrontRight(vex::PORT10, vex::gearSetting::ratio18_1, true);
vex::motor BackLeft(vex::PORT11, vex::gearSetting::ratio18_1, false);
vex::motor BackRight(vex::PORT20, vex::gearSetting::ratio18_1, true);
vex::motor LiftRight(vex::PORT9, vex::gearSetting::ratio18_1, false);
vex::motor LiftLeft(vex::PORT2, vex::gearSetting::ratio18_1, true);
vex::motor ClawMotor(vex::PORT6, vex::gearSetting::ratio18_1, false);
vex::motor LiftPlus(vex::PORT8, vex::gearSetting::ratio18_1,true); // right side third motor
vex::bumper LiftStop(Brain.ThreeWirePort.B);
vex::controller Controller1;
vex::competition Competition;
vex::motor_group DriveMotors(FrontLeft, FrontRight, BackLeft, BackRight);
vex::motor_group LiftMotors(LiftRight, LiftLeft/*, LiftPlus*/);
vex::motor_group LeftDrive(FrontLeft, BackLeft);
vex::motor_group RightDrive(FrontRight, BackRight);
double trackWidth = 13.5;     // Side to Side
double wheelBase = 11.5;        // Front wheel to back wheel
double externalGearRatio = 1.0; // Don't change this dummy
double wheeltravel = 9.42477796076;     // Diameter of the wheel times Pi
drivetrain DriveBase(LeftDrive, RightDrive, wheeltravel, trackWidth, wheelBase,distanceUnits::in, externalGearRatio);
int channel2;
int channel3;
long mapped2;
long mapped3;
int liftHight;
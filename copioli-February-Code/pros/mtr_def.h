#ifndef MTR_DEF_H
#define MTR_DEF_H
#include "main.h"

pros::Controller master (pros::E_CONTROLLER_MASTER);

pros::Motor driveLF (9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRF (20, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLB (1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRB (15, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor lift_1 (4, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intakeL (3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intakeR (19, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor tilter (10, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

void set_drive_motor_brake_modes(pros::motor_brake_mode_e type)
{
	driveLF.set_brake_mode(type); //coast default
  driveRF.set_brake_mode(type);
  driveLB.set_brake_mode(type);
  driveRB.set_brake_mode(type);
}

void set_lift_motor_brake_modes(pros::motor_brake_mode_e type)
{
	lift_1.set_brake_mode(type); //coast default
}

void set_intake_motor_brake_modes(pros::motor_brake_mode_e type)
{
	intakeL.set_brake_mode(type); //hold default
  intakeR.set_brake_mode(type);
}

void set_tilter_motor_brake_modes(pros::motor_brake_mode_e type)
{
	tilter.set_brake_mode(type); //hold default
}

void set_motor_brake_modes()
{
	set_drive_motor_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	set_lift_motor_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
	set_intake_motor_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	set_tilter_motor_brake_modes(pros::E_MOTOR_BRAKE_COAST);
}

#endif

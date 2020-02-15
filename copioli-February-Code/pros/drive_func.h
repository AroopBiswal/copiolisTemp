#ifndef DRIVE_FUNC_H
#define DRIVE_FUNC_H
#include "main.h"
#include "mtr_def.h"
#include "misc.h"
#include <cmath>
#include <iostream>
//#include "intake_func.h"
//#include <algorithm>
using namespace std;
#define drive_Kp_L 1
#define drive_Kp_R 1
//#define turn_Kp 1*/
void set_drive(float left, float right) //voltage
{
  driveLF.move_velocity(percent_to_velocity(left/127.0, driveLF.get_gearing()));
  driveRF.move_velocity(percent_to_velocity(right/127.0, driveRF.get_gearing()));
  driveLB.move_velocity(percent_to_velocity(left/127.0, driveLB.get_gearing()));
  driveRB.move_velocity(percent_to_velocity(right/127.0, driveRB.get_gearing()));
}
void set_drive_volts(int left, int right)
{
  driveLF = driveLB = left;
  driveRF = driveRB = right;
}
bool drive_hold_on = false;
bool drive_pressed = false;
void drive_train(int x, int y, bool speed_toggle) //voltage
{
  if(speed_toggle)
  {
    if(!drive_pressed)
    {
      drive_hold_on = !drive_hold_on;
      drive_pressed = true;
    }
  }
  else
  {
    drive_pressed = false;
  }
  if(drive_hold_on) set_drive_motor_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
  else set_drive_motor_brake_modes(pros::E_MOTOR_BRAKE_COAST);
  if(abs(x) < 3) x = 0;
  if(abs(y) < 3) y = 0;
  int left = y+x;
  int right = y-x;
  set_drive(left, right);
}
void reset_drive_encoders()
{
  driveLF.tare_position();
  driveRF.tare_position();
  driveLB.tare_position();
  driveRB.tare_position();
}


typedef struct
{
  int error;
  float Kp;
  int target;
  bool task_on;
  bool start;
} pid_struct;

int get_raw_left_drive_pos()
{
  std::uint32_t now = pros::millis();
  return (driveLF.get_raw_position(&now)+driveLB.get_raw_position(&now))/2;
}

int get_raw_right_drive_pos()
{
  std::uint32_t now = pros::millis();
  return (driveRF.get_raw_position(&now)+driveRB.get_raw_position(&now))/2;
}

int drive_forward_pid(pid_struct* drive_pid)
{
  drive_pid->error = drive_pid->target - (get_raw_left_drive_pos()+get_raw_right_drive_pos())/2;
  int output = drive_pid->Kp*drive_pid->error;
  if(output > 127) output = 127;
  else if(output < -127) output = -127;
  //cout << output << endl;
  return output;
}

int inches_to_ticks(float inches)
{
  return (inches/(4*M_PI))*900;
}

void drive_forward(float inches, pid_struct* drive_pid)
{
  drive_pid->target = inches_to_ticks(inches);
  reset_drive_encoders();
  while(true)
  {
    set_drive_volts(drive_forward_pid(drive_pid), drive_forward_pid(drive_pid));
    pros::delay(5);
  }
  set_drive_volts(0, 0);
}

pid_struct drive_pid;
void set_drive_target(float inches, pid_struct* drive_pid)
{
  drive_pid->start = true;
  drive_pid->target = inches_to_ticks(inches);
}

int target = 0;
void drive_task(void* param)
{
  int error = 0;
  float Kp = .6;
  reset_drive_encoders();
  while(true)
  {
    error = target - (get_raw_left_drive_pos()+get_raw_right_drive_pos())/2;
    int output = Kp*error;
    if(output > 127) output = 127;
    else if(output < -127) output = -127;
    set_drive_volts(output, output);
    pros::delay(5);
  }
}






















/*void drive_forward_block(float dist, float vel_proportion)
{
  reset_drive_encoders();
  driveLF.move_relative(inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveLF.get_gearing()));
  driveLB.move_relative(inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveLB.get_gearing()));
  driveRF.move_relative(inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveRF.get_gearing()));
  driveRB.move_relative(inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveRB.get_gearing()));
  float dist_val = degrees_to_inches(driveLF.get_position()+driveRB.get_position())/2.0;
  while(!(degrees_to_inches(driveLF.get_position()) < dist-5 && degrees_to_inches(driveLF.get_position()) < dist+5)) { pros::delay(2); }
}
void drive_forward(float dist, float vel_proportion)
{
  reset_drive_encoders();
  driveLF.move_relative(-1*inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveLF.get_gearing()));
  driveLB.move_relative(-1*inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveLB.get_gearing()));
  driveRF.move_relative(-1*inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveRF.get_gearing()));
  driveRB.move_relative(-1*inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveRB.get_gearing()));
}
void drive_turn_block(float dist, float vel_proportion)
{
  reset_drive_encoders();
  driveLF.move_relative(inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveLF.get_gearing()));
  driveLB.move_relative(inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveLB.get_gearing()));
  driveRF.move_relative(inches_to_degrees(dist), percent_to_velocity(-1*vel_proportion, driveRF.get_gearing()));
  driveRB.move_relative(inches_to_degrees(dist), percent_to_velocity(-1*vel_proportion, driveRB.get_gearing()));
  float dist_val = degrees_to_inches(abs(driveLF.get_position())+abs(driveRB.get_position()))/2.0;
  while(abs(dist-dist_val) > 3) { pros::delay(2); }
}
void drive_turn(float dist, float vel_proportion)
{
  reset_drive_encoders();
  driveLF.move_relative(inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveLF.get_gearing()));
  driveLB.move_relative(inches_to_degrees(dist), percent_to_velocity(vel_proportion, driveLB.get_gearing()));
  driveRF.move_relative(inches_to_degrees(dist), percent_to_velocity(-1*vel_proportion, driveRF.get_gearing()));
  driveRB.move_relative(inches_to_degrees(dist), percent_to_velocity(-1*vel_proportion, driveRB.get_gearing()));
}*/
#endif

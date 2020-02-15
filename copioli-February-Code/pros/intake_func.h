#ifndef INTAKE_FUNC_H
#define INTAKE_FUNC_H
#include "main.h"
#include "mtr_def.h"
#include "misc.h"
using namespace std;

void set_intake(float a) //voltage
{
  intakeL.move_velocity(percent_to_velocity(a/127, intakeL.get_gearing()));
  intakeR.move_velocity(percent_to_velocity(a/127, intakeR.get_gearing()));
}
void set_intake_volts(int a)
{
  intakeL = intakeR = a;
}
bool intake_speed_state = false;
bool intake_pressed = false;
void intake(bool up, bool down, bool speed_toggle)
{
  if(speed_toggle)
  {
    if(!intake_pressed)
    {
      intake_speed_state = !intake_speed_state;
      intake_pressed = true;
    }
  }
  else intake_pressed = false;
  float vel_percent = 0;
  if(up) vel_percent = 127;
  else if(down) vel_percent = -127;
  if(intake_speed_state) vel_percent /= 4.0;
  set_intake(vel_percent);
}
void reset_intake_encoders()
{
  intakeL.tare_position();
  intakeR.tare_position();
}
#endif

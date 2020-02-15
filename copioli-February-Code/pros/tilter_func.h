#ifndef TILTER_FUNC_H
#define TILTER_FUNC_H
#include "main.h"
#include "mtr_def.h"
#include "misc.h"
using namespace std;
void set_tilter(float a) //voltage
{
  float tilter_pos = tilter.get_position();
  cout << tilter_pos << endl;
  if(tilter_pos < 0 && tilter_pos >= -322) set_tilter_motor_brake_modes(pros::E_MOTOR_BRAKE_COAST);
  else set_tilter_motor_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
  tilter.move_velocity(percent_to_velocity(a/127, tilter.get_gearing()));
}
bool tilter_speed_state = false;
bool tilter_pressed = false;
void tilt(bool up, bool down, bool speed_toggle)
{
  if(speed_toggle)
  {
    if(!tilter_pressed)
    {
      tilter_speed_state = !tilter_speed_state;
      tilter_pressed = true;
    }
  }
  else
  {
    tilter_pressed = false;
  }
  float vel_percent = 0;
  if(up) vel_percent = -127;
  else if(down) vel_percent = 127;
  if(tilter_speed_state) vel_percent /= 4.0;
  set_tilter(vel_percent);
}
void reset_tilter_encoders()
{
  tilter.tare_position();
}
void move_tilter(float degrees, float vel_proportion)
{
  tilter.move_relative(degrees, percent_to_velocity(vel_proportion, tilter.get_gearing()));
}
void move_tilter_time(float voltage, float secs){
  set_tilter(voltage);
  pros::delay(secs);
  set_tilter(0);
}
#endif

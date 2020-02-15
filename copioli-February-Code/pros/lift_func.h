#ifndef LIFT_FUNC_H
#define LIFT_FUNC_H
#include "main.h"
#include "mtr_def.h"
#include "misc.h"
using namespace std;
void set_lift(float a)
{
  lift_1.move_velocity(percent_to_velocity(a/127, lift_1.get_gearing()));
}
bool lift_speed_state = false;
bool lift_pressed = false;
void lift(int a, bool speed_toggle)
{
  if(speed_toggle)
  {
    if(!lift_pressed)
    {
      lift_speed_state = !lift_speed_state;
      lift_pressed = true;
    }
  }
  else
  {
    lift_pressed = false;
  }
  if(abs(a) < 3) a = 0;
  if(lift_speed_state) a /= 4.0;
  set_lift(-a);
}
void reset_lift_encoders()
{
  lift_1.tare_position();
}
void move_lift(float degrees, float vel_proportion)
{
  lift_1.move_relative(degrees, percent_to_velocity(vel_proportion, lift_1.get_gearing()));
}
#endif

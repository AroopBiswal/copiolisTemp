#ifndef MISC_H
#define MISC_H
#include "main.h"
#include "math.h"
int voltage_to_velocity(float volts, pros::motor_gearset_e_t gearset)
{
  int multiplier;
  if(gearset == pros::E_MOTOR_GEARSET_18) multiplier = 200;
  else if(gearset == pros::E_MOTOR_GEARSET_36) multiplier = 100;
  else if(gearset == pros::E_MOTOR_GEARSET_06) multiplier = 600;
  float percent = volts/127;
  return percent*multiplier;
}
int percent_to_velocity(float percent, pros::motor_gearset_e_t gearset)
{
  int multiplier;
  if(gearset == pros::E_MOTOR_GEARSET_18) multiplier = 200;
  else if(gearset == pros::E_MOTOR_GEARSET_36) multiplier = 100;
  else if(gearset == pros::E_MOTOR_GEARSET_06) multiplier = 600;
  return percent*multiplier;
}
int sgn(int a)
{
  if(a != 0) return ((-1*a/a == -1)? 1:-1);
  else return 0;
}
/*float degrees_to_revs_drive(float degrees) //TODOS
{
  return (1/90.0)*(degrees-7);
}
float inches_to_revs_drive(float inches)
{
  //return inches/(6.29*4);
  return inches*(1.8/24.0);
}*/
int inches_to_degrees(float inches)
{
  //return (inches/(6.29*4))*360;
  return inches*(1.8/24.0)*360;
}
float degrees_to_inches(int degrees)
{
  //return (degrees/360)*(6.29*4);
  return degrees/360.0/1.8*24.0;
}

float my_max(float a, float b)
{
  if(abs(a) >= abs(b)) return a;
  else return b;
}


#endif

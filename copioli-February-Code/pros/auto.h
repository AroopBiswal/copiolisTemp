/*#ifndef AUTO_H
#define AUTO_H
#include "main.h"
#include "mtr_def.h"
#include "misc.h"
#include "drive_func.h"
#include "intake_func.h"
#include "tilter_func.h"
#include "lift_func.h"



void squareRed() //5
{
  reset_all_encoders();
//move_tilter(-700, 1); //move_tilter_up
  //move_tilter(650, 1);
  //pros::delay(500);
  //set_intake(127);
  drive_forward_block(-47, .4);
  pros::delay(100);
  drive_forward_block(-47, .4);
}
void squareBlue() //5
{

}
void rectRect() //8
{

}
void rectBlue() //8
{

}
#endif
*/

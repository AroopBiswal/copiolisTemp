#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include "vex.h"
#include "v5.h"
#include "v5_vcs.h"
using namespace vex;

void liftTrayAutomation(){
  double limit1 = 30;
  double limit2 = 45;
  double limit3 = 60;

  double tilt1 = 10.0;
  double tilt2 = 20.0;

  if((lift1.rotation(deg) > limit1) && (lift1.rotation(deg) < limit2)){
    tilter.rotateTo(tilt1, deg);
  }
  else if((lift1.rotation(deg) > limit2) && (lift1.rotation(deg) < limit3)){
    tilter.rotateTo(tilt2, deg);
  }
  else{
    //something silly ig \_(-.- )__/
  } 
}
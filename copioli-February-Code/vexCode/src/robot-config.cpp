#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor driveLF = motor(PORT9, ratio18_1);
motor driveRF = motor(PORT20, ratio18_1, true);
motor driveLB = motor(PORT1, ratio18_1);
motor driveRB = motor(PORT15, ratio18_1, true);


motor lift1 = motor(PORT4, ratio18_1);
motor intake1 = motor(PORT3, ratio18_1, true); //LEFT
motor intake2 = motor(PORT19, ratio18_1);
motor tilter = motor(PORT10, ratio18_1);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}

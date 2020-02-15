using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor driveLF;
extern motor driveRF;
extern motor driveLB;
extern motor driveRB;
extern motor lift1;
extern motor intake1;
extern motor intake2;
extern motor tilter;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
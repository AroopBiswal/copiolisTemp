#include "main.h"
#include "mtr_def.h"
#include "misc.h"
#include "drive_func.h"
#include "intake_func.h"
#include "tilter_func.h"
#include "lift_func.h"
//#include "auto.h"

using namespace std;


void reset_all_encoders()
{
  reset_lift_encoders();
  reset_drive_encoders();
  reset_tilter_encoders();
}

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
	set_motor_brake_modes();
	reset_all_encoders();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	pros::Task driveTask (drive_task, (void*)"PROS", TASK_PRIORITY_DEFAULT,
													 TASK_STACK_DEPTH_DEFAULT, "PID TASK");
	/*drive_pid.task_on = true;
	set_drive_target(36, &drive_pid);
	pros::delay(3000);
	set_drive_target(-36, &drive_pid);*/
	//drive_forward(36, &drive_pid);
	target = inches_to_ticks(36);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	while(true)
	{
		int32_t btn_a = master.get_digital(DIGITAL_A);
		int32_t joy_x_left = master.get_analog(ANALOG_LEFT_X);
		int32_t joy_y_left = master.get_analog(ANALOG_LEFT_Y);
		int32_t joy_y_right = master.get_analog(ANALOG_RIGHT_Y);
		int32_t btn_l1 = master.get_digital(DIGITAL_L1);
		int32_t btn_l2 = master.get_digital(DIGITAL_L2);
		int32_t btn_r1 = master.get_digital(DIGITAL_R1);
		int32_t btn_r2 = master.get_digital(DIGITAL_R2);

		drive_train(joy_x_left, joy_y_left, btn_a);
		lift(joy_y_right, btn_a);
		intake(btn_l1, btn_l2, btn_a);
		tilt(btn_r1, btn_r2, btn_a);
		pros::delay(5);
	}


}

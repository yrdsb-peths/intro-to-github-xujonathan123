#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

using namespace subsystems;

double currentPower = 0.0;
// double targetPower = 0.0;
// double rightX = 0.0;

// void updateSlewRate()
// {
//     double maxChange = 5;
//     currentPower += std::clamp(targetPower-currentPower, -maxChange, maxChange);
//     leftMotors.move(currentPower + rightX);
//     rightMotors.move(currentPower - rightX);
// }

void initialize() {
    // selector.init();
    pros::lcd::initialize();
    chassis.calibrate();
    chassis.setPose(0, 0, 0);
    leftMotors.set_brake_modes(pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE);
    rightMotors.set_brake_modes(pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE);
    rightArmMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftArmMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightArmMotor.set_zero_position(armState::IDLE);
    leftArmMotor.set_zero_position(armState::IDLE);
    //set colour to whatever colour we are
    intake.set_target_color(DONUT_COLOR::RED);
    //intake.piston_out();

}

void disabled() {}

void competition_initialize() {
    while (!screen.routeSelected) {
        screen.update();  // Handle input and update the screen
        pros::delay(20);  // Small delay for periodic updates
}
}
//ASSET(test_txt);

void autonomous() {
    // distanceAlign.startDistanceSensorTask();
    // auton.mogoRushRed();
    // auton.mogoRushRed();
    auton.swpRED();

    // auton.mogoRushRed();
    // //auton.run_auton(auton.get_selected_auton());
}

void opcontrol() {
    leftMotors.set_brake_modes(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);
    rightMotors.set_brake_modes(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);
    while (true) {
        master.print(0,0,"x:%.2Lfy:%.2Lft:%.0Lf", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
        // master.print(0,0,"dist:%5.2Lf", sensors.horizontal1->getDistanceTraveled());

        //rightX = master.get_analog(ANALOG_RIGHT_X);
        //
        movement.arcade_drive(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_X));
        clamp.run(DIGITAL_B);
        intake.run(DIGITAL_R1, DIGITAL_R2, DIGITAL_DOWN, DIGITAL_LEFT);




        pros::delay(10);

        pros::lcd::print(1, "x: %Lf", chassis.getPose().x);
        pros::lcd::print(2, "y: %Lf", chassis.getPose().y);
        pros::lcd::print(3, "theta: %Lf", chassis.getPose().theta);

    }
}

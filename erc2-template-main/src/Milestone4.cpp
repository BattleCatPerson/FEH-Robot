#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>

#define COUNTS_PER_INCH 33.74
#define COUNTS_PER_DEGREE 2.067

DigitalEncoder right_encoder(FEHIO::Pin8);
DigitalEncoder left_encoder(FEHIO::Pin10);
FEHMotor right_motor(FEHMotor::Motor1, 9.0);
FEHMotor left_motor(FEHMotor::Motor0, 9.0);
AnalogInputPin cds(FEHIO::Pin0);

void move_forward(int lpercent, int rpercent, int counts) // using encoders
{
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    // Set both motors to desired percent
    right_motor.SetPercent(-rpercent);
    left_motor.SetPercent(lpercent);

    // While the average of the left and right encoder is less than counts,
    // keep running motors
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
        ;

    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void move_backward(int lpercent, int rpercent, int counts) // using encoders
{
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    // Set both motors to desired percent
    right_motor.SetPercent(rpercent);
    left_motor.SetPercent(-lpercent);

    // While the average of the left and right encoder is less than counts,
    // keep running motors
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
        ;

    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_counterclockwise(int percent, int counts)
{
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    // Set both motors to desired percent
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(-percent);

    // While the average of the left and right encoder are less than counts,
    // keep running motors
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
        ;

    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_clockwise(int percent, int counts)
{
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    // Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    // While the average of the left and right encoder are less than counts,
    // keep running motors
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
        ;

    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

// //The function used to drive in your robot code.
// FUNCTION: DriveSomeDistance
// Call ResetPIDVariables Function
// //Be careful of potentially making your first time difference of 0, this can cause big errors!
// WHILE (Encoders * Conversion) < GoalDistance DO
// SetMotorPower( RightMotorPIDAdjustment(ExpectedSpeed))
// SetMotorPower( LeftMotorPIDAdjustment(ExpectedSpeed))
// Wait for Small Time to Get Data //To avoid time difference of 0
// END
float oldCountLeft = 0;
float oldCountRight = 0;
float newCountLeft = 0;
float newCountRight = 0;
float pastTime = 0;
float newTime = 0;
float iLeft = 0;
float iRight = 0;
float pLeft = 0;
float pRight = 0;
float dLeft = 0;
float dRight = 0;
float oldErrorLeft = 0;
float oldErrorRight = 0;
float leftErrorSum = 0;
float rightErrorSum = 0;
float oldMotorLeft = 0;
float oldMotorRight = 0;
void drive_distance(int percent, int inches)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    ResetPID();
    float goalCounts = inches * COUNTS_PER_INCH;
    // reset
    while ((right_encoder.Counts() + left_encoder.Counts()) / 2.0 < goalCounts)
    {
        // SetMotorPower( RightMotorPIDAdjustment(ExpectedSpeed))
        // SetMotorPower( LeftMotorPIDAdjustment(ExpectedSpeed))
        // Wait for Small Time to Get Data //To avoid time difference of 0
        oldCountLeft = left_encoder.Counts();
        oldCountRight = right_encoder.Counts();
        Sleep(0.1);
    }
    left_motor.Stop();
    right_motor.Stop();
}
// Stop Both Motors
// END
// //The function used to Reset PID each time.
// FUNCTION: ResetPIDVariables
void ResetPID()
{
    oldCountLeft = 0;
    oldCountRight = 0;
    newCountLeft = 0;
    newCountRight = 0;
    pastTime = 0;
    newTime = 0;
    iLeft = 0;
    iRight = 0;
    pLeft = 0;
    pRight = 0;
    dLeft = 0;
    dRight = 0;
    oldErrorLeft = 0;
    oldErrorRight = 0;
    leftErrorSum = 0;
    rightErrorSum = 0;
    oldMotorLeft = 0;
    oldMotorRight = 0;
}
// Reset all Variables to Initial State
// Record the Current Time
// Reset Encoders
// Wait for a Small Time to Get Data //To avoid time difference of 0
// END
// //The function used to do PID control
// FUNCTION: PIDAdjustment
// Find Change in Counts Since Last Time
// Find Change in Time Since Last Time
// Use to Find Actual Velocity
// Find Error
// Add Error to ErrorSum
// Calculate PTerm
// Calculate ITerm
// Calculate DTerm
// Save PastError, PastCounts, PastTime
// Created by: John Jackson
// Return (OldMotorPower + PTerm + ITerm + DTerm)
float PIDAdjustment()
{
    
    return 0;
}
// END
void ERCMain()
{
    int left_motor_percent = 30;
    int right_motor_percent = 32; // Input power level here
    float no_light = 2.75;
    float up_ramp_inches = 38;
    float light_degrees = 10;
    float to_window = 22;
    float push_window = 20;
    int fuck_up_divider = 2;
    float final_button = 2;
    float final_button_back = 1;

    // read light
    while (cds.Value() > no_light)
    {
    }
    // turn right 45 degrees 54
    move_backward(left_motor_percent, right_motor_percent, final_button * COUNTS_PER_INCH / fuck_up_divider);
    move_forward(left_motor_percent, right_motor_percent, final_button_back * COUNTS_PER_INCH / fuck_up_divider);
    // turn
    // move forward
    // turn left
    // move forward
    // lower arm
    // pick up bucket
    // raise arm
    // move backwards
    // turn right
    // move forward
    // drop bucket
    // move backwards
    // turn
    // hit a lever
}

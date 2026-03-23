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
void ERCMain()
{
    int left_motor_percent = 35;
    int right_motor_percent = 40; // Input power level here
    float no_light = 2.75;
    float up_ramp_inches = 42;
    float light_degrees = 10;
    float push_window = 10;
    // read light
    Sleep(3.0);
    while (cds.Value() > no_light)
    {
    }
    // turn right 45 degrees 54
    turn_clockwise(25, COUNTS_PER_DEGREE * 48);
    // drive up ramp
    move_forward(left_motor_percent, right_motor_percent, up_ramp_inches * COUNTS_PER_INCH);
    // turn around
    turn_counterclockwise(25, COUNTS_PER_DEGREE * 180); // 97
    move_backward(left_motor_percent, right_motor_percent, push_window * COUNTS_PER_INCH);
}

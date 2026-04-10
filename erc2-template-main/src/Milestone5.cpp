#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>

#define COUNTS_PER_INCH 33.74
#define COUNTS_PER_DEGREE 2.067

DigitalEncoder right_encoder(FEHIO::Pin12);
DigitalEncoder left_encoder(FEHIO::Pin14);
FEHMotor right_motor(FEHMotor::Motor1, 9.0);
FEHMotor left_motor(FEHMotor::Motor0, 9.0);
AnalogInputPin cds(FEHIO::Pin0);
FEHServo robot_arm(FEHServo::Servo7);
FEHServo turntable_arm(FEHServo::Servo6);

void move_forward(float lpercent, float rpercent, int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(-rpercent);
    left_motor.SetPercent(lpercent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
    {
        if (left_encoder.Counts() < right_encoder.Counts() - 2)
        {
            lpercent += 0.001;
        }
        else if (right_encoder.Counts() < left_encoder.Counts() - 2)
        {
            rpercent += 0.001;
        }
        right_motor.SetPercent(-rpercent);
        left_motor.SetPercent(lpercent);
    };
    right_motor.Stop();
    left_motor.Stop();
}
void move_backward(float lpercent, float rpercent, int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(rpercent);
    left_motor.SetPercent(-lpercent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
    {
        if (left_encoder.Counts() < right_encoder.Counts() - 2)
        {
            lpercent += 0.001;
        }
        else if (right_encoder.Counts() < left_encoder.Counts() - 2)
        {
            rpercent += 0.001;
        }
        right_motor.SetPercent(rpercent);
        left_motor.SetPercent(-lpercent);
    };
    right_motor.Stop();
    left_motor.Stop();
}
void turn_counterclockwise(int percent, int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(-percent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
        ;
    right_motor.Stop();
    left_motor.Stop();
}
void turn_clockwise(int percent, int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
        ;
    right_motor.Stop();
    left_motor.Stop();
}
float left_motor_percent = 25;
float right_motor_percent = 25; // Input power level here
float no_light = 2.75;
float fuck_up_divider = 2;
float final_button = 3;
float final_button_back = 2;
float diagonal = 19;
float back_bin = 18;
float turn_table_spin_time = 3;
int servo_max = 2500;
int servo_min = 500;
int turn_max = 2500;
int turn_min = 500;

void PressButton()
{
    move_backward(left_motor_percent, right_motor_percent, final_button * COUNTS_PER_INCH / fuck_up_divider);
    move_forward(left_motor_percent, right_motor_percent, final_button_back * COUNTS_PER_INCH / fuck_up_divider);
    // turn_clockwise(25, COUNTS_PER_DEGREE * 45 / fuck_up_divider);
}
void ToBin()
{
    turn_counterclockwise(15, COUNTS_PER_DEGREE * 45);
    move_forward(left_motor_percent, right_motor_percent, 1 * COUNTS_PER_INCH);
    turn_counterclockwise(15, COUNTS_PER_DEGREE * 15);
    move_forward(left_motor_percent, right_motor_percent, 2 * COUNTS_PER_INCH);
}
void SpinBin()
{
    robot_arm.SetDegree(30);
    Sleep(1.5);
    for (int i = 0; i < 3; i++)
    {
        robot_arm.SetDegree(105);
        Sleep(1.0);
        move_backward(left_motor_percent, right_motor_percent, 5 * COUNTS_PER_INCH);
        Sleep(1.0);
        robot_arm.SetDegree(30);
        Sleep(1.0);
        move_forward(left_motor_percent, right_motor_percent, 5 * COUNTS_PER_INCH);
        Sleep(1.0);
    }
    robot_arm.SetDegree(0);
    move_backward(left_motor_percent, right_motor_percent, 5 * COUNTS_PER_INCH);
    turn_clockwise(15, COUNTS_PER_DEGREE * 45);
    move_backward(left_motor_percent, right_motor_percent, 1 * COUNTS_PER_INCH);
    turn_clockwise(15, COUNTS_PER_DEGREE * 15);
    move_backward(left_motor_percent, right_motor_percent, 2 * COUNTS_PER_INCH);
    PressButton();
}


void ERCMain()
{
    // robot_arm.TouchCalibrate();
    // robot_arm.SetMin(0);
    // robot_arm.SetMax(180);
    // turn right 45 degrees 54
    // turntable_arm.TouchCalibrate();
    // left_encoder.ResetCounts();
    // right_encoder.ResetCounts();
    // left_motor.SetPercent(-25);
    // right_motor.SetPercent(25);
    // move_forward(25, 25, 2 * COUNTS_PER_INCH);
    // while (true)
    // {
    //     LCD.WriteLine(left_encoder.Counts());
    //     LCD.WriteLine(right_encoder.Counts());
    //     Sleep(0.5);
    //     LCD.Clear();
    // }

    robot_arm.SetMax(servo_max);
    robot_arm.SetMin(servo_min);
    robot_arm.SetDegree(0);
    while (cds.Value() > no_light)
    {
    }
    Sleep(1.0);
    PressButton();
    ToBin();
    SpinBin();

    // if left lower than right increase left speed by .0001
}

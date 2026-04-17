#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHRCS.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>

#define COUNTS_PER_INCH 33.74
#define COUNTS_PER_DEGREE 2.067
// Defines for pulsing the robot
#define PULSE_TIME 0.05
#define PULSE_POWER 25
// Orientation of AruCo Code
#define PLUS 0
#define MINUS 1
// RCS Delay time
#define RCS_WAIT_TIME_IN_SEC 0.35
DigitalEncoder right_encoder(FEHIO::Pin12);
DigitalEncoder left_encoder(FEHIO::Pin14);
FEHMotor right_motor(FEHMotor::Motor1, 9.0);
FEHMotor left_motor(FEHMotor::Motor0, 9.0);
AnalogInputPin cds(FEHIO::Pin0);
FEHServo robot_arm(FEHServo::Servo7);
FEHServo turntable_arm(FEHServo::Servo6);
FEHServo window_arm(FEHServo::Servo0);

void move_forward(float lpercent, float rpercent, int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(-rpercent);
    Sleep(150);
    right_encoder.ResetCounts();
    left_motor.SetPercent(lpercent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
    {
        // if (left_encoder.Counts() < right_encoder.Counts() - 2)
        // {
        //     lpercent += 0.002;
        // }
        // else if (right_encoder.Counts() < left_encoder.Counts() - 2)
        // {
        //     rpercent += 0.002;
        // }
        // right_motor.SetPercent(-rpercent);
        // left_motor.SetPercent(lpercent);
    };
    right_motor.Stop();
    left_motor.Stop();
}
void move_backward(float lpercent, float rpercent, int counts)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    right_motor.SetPercent(rpercent);
    Sleep(150);
    right_encoder.ResetCounts();
    left_motor.SetPercent(-lpercent);
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
    {
        // if (left_encoder.Counts() < right_encoder.Counts() - 2)
        // {
        //     lpercent += 0.002;
        // }
        // else if (right_encoder.Counts() < left_encoder.Counts() - 2)
        // {
        //     rpercent += 0.002;
        // }
        // right_motor.SetPercent(rpercent);
        // left_motor.SetPercent(-lpercent);
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
void pulse_forward(int percent, float seconds)
{
    // Set both motors to desired percent
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(percent);

    // Wait for the correct number of seconds
    Sleep(seconds);

    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
/*
 * Use RCS to move to the desired x_coordinate based on the orientation of the AruCo code
 */
void check_x(float x_coordinate, int orientation)
{
    // Determine the direction of the motors based on the orientation of the AruCo code
    int power = PULSE_POWER;
    if (orientation == MINUS)
    {
        power = -PULSE_POWER;
    }

    RCSPose *pose = RCS.RequestPosition();

    // Check if receiving proper RCS coordinates and whether the robot is within an acceptable range
    for (int i = 0; i < 10; i++)
    {
        if (pose->x >= 0 && (pose->x < x_coordinate - 1 || pose->x > x_coordinate + 1))
        {
            if (pose->x < x_coordinate + 1)
            {
                // Pulse the motors for a short duration in the correct direction
                pulse_forward(power, PULSE_TIME);
            }
            else if (pose->x > x_coordinate - 1)
            {
                // Pulse the motors for a short duration in the correct direction
                pulse_forward(-power, PULSE_TIME);
            }
            Sleep(RCS_WAIT_TIME_IN_SEC);

            pose = RCS.RequestPosition();
        }
    }
}

/*
 * Use RCS to move to the desired y_coordinate based on the orientation of the QR code
 */
void check_y(float y_coordinate, int orientation)
{
    // Determine the direction of the motors based on the orientation of the QR code
    int power = PULSE_POWER;
    if (orientation == MINUS)
    {
        power = -PULSE_POWER;
    }

    RCSPose *pose = RCS.RequestPosition();

    // Check if receiving proper RCS coordinates and whether the robot is within an acceptable range
    for (int i = 0; i < 10; i++)
    {
        if (pose->y >= 0 && (pose->y < y_coordinate - 1 || pose->y > y_coordinate + 1))
        {
            if (pose->y < y_coordinate + 1)
            {
                // Pulse the motors for a short duration in the correct direction
                pulse_forward(power, PULSE_TIME);
            }
            else if (pose->y > y_coordinate - 1)
            {
                // Pulse the motors for a short duration in the correct direction
                pulse_forward(-power, PULSE_TIME);
            }
            Sleep(RCS_WAIT_TIME_IN_SEC);

            pose = RCS.RequestPosition();
        }
    }
}
void check_heading(float heading)
{
    // You will need to fill out this one yourself and take into account
    // checking for proper RCS data and the edge conditions
    //(when you want the robot to go to 0 degrees or close to 0 degrees)

    /*
        SUGGESTED ALGORITHM:
        1. Check the current orientation of the QR code and the desired orientation of the QR code
        2. Check if the robot is within the desired threshold for the heading based on the orientation
        3. Pulse in the correct direction based on the orientation
    */
    RCSPose *pose = RCS.RequestPosition();
    int count = 0;
    while (pose->heading >= 0 && (pose->heading < heading - 2 || pose->heading > heading + 2) && count < 10)
    {
        float headingDifference = heading - pose->heading;
        if (headingDifference > 180)
            headingDifference -= 360;
        if (headingDifference < -180)
            headingDifference += 360;
        if (headingDifference > 0)
        {
            // CCW
            right_motor.SetPercent(-PULSE_POWER);
            left_motor.SetPercent(-PULSE_POWER);
        }
        else if (headingDifference <= 0)
        {
            // CW
            right_motor.SetPercent(PULSE_POWER);
            left_motor.SetPercent(PULSE_POWER);
        }
        Sleep(PULSE_TIME);
        right_motor.Stop();
        left_motor.Stop();
        Sleep(RCS_WAIT_TIME_IN_SEC);

        pose = RCS.RequestPosition();
        count++;
    }
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
float blue_light = .85;
float light_degrees = 10;
float to_humidifier_button = 6;

void PressButton()
{
    move_backward(left_motor_percent, right_motor_percent, final_button * COUNTS_PER_INCH);
    move_forward(left_motor_percent, right_motor_percent, final_button_back * COUNTS_PER_INCH);
    // turn_clockwise(25, COUNTS_PER_DEGREE * 45 / fuck_up_divider);
}
void ToBin()
{
    turn_counterclockwise(15, COUNTS_PER_DEGREE * 57);
    move_forward(left_motor_percent, right_motor_percent, 3.5 * COUNTS_PER_INCH);
}
void SpinBin()
{
    robot_arm.SetDegree(0);
    Sleep(1.5);
    for (int i = 0; i < 4; i++)
    {
        robot_arm.SetDegree(105);
        Sleep(1.0);
        move_backward(left_motor_percent, right_motor_percent, 3 * COUNTS_PER_INCH);
        Sleep(1.0);
        robot_arm.SetDegree(0);
        Sleep(1.0);
        move_forward(left_motor_percent, right_motor_percent, 3 * COUNTS_PER_INCH);
        Sleep(1.0);
    }
    robot_arm.SetDegree(0);
    move_forward(left_motor_percent, right_motor_percent, 4 * COUNTS_PER_INCH);
    turn_clockwise(25, COUNTS_PER_DEGREE * 97);
    check_heading(270);
}

void CompostBin()
{
    ToBin();
    SpinBin();
}
void ToBucket()
{
    // move_forward(left_motor_percent, right_motor_percent, to_bucket_one * COUNTS_PER_INCH / fuck_up_divider);
    // turn_counterclockwise(25, COUNTS_PER_DEGREE * 90 / fuck_up_divider);
    // move_forward(left_motor_percent, right_motor_percent, to_bucket_two * COUNTS_PER_INCH / fuck_up_divider);
    // turn_clockwise(25, COUNTS_PER_DEGREE * 8 / fuck_up_divider);
    // move_forward(left_motor_percent, right_motor_percent, to_bucket_two_two * COUNTS_PER_INCH / fuck_up_divider);
    // robot_arm.SetDegree(65); // lower arm
    // Sleep(2.0);
    // move_forward(left_motor_percent, right_motor_percent, to_bucket_three * COUNTS_PER_INCH / fuck_up_divider);
    // Sleep(1.0);
    // robot_arm.SetDegree(0); // raise arm
    // Sleep(2.0);
    // move_backward(left_motor_percent, right_motor_percent, (to_bucket_two + to_bucket_two_two + to_bucket_three) * COUNTS_PER_INCH / fuck_up_divider);
    // turn_clockwise(25, COUNTS_PER_DEGREE * 90 / fuck_up_divider);
    move_forward(left_motor_percent, right_motor_percent, 15 * COUNTS_PER_INCH);
    // turn_counterclockwise(25, COUNTS_PER_DEGREE * 47);
    check_y(20.5, PLUS);
    turn_counterclockwise(20, COUNTS_PER_DEGREE * 97);
    // check_heading(357);
    // move_backward(left_motor_percent, right_motor_percent, 2 * COUNTS_PER_INCH);
    check_x(17.69, MINUS);
    robot_arm.SetDegree(65);
    Sleep(2.0);
    move_forward(left_motor_percent, right_motor_percent, 5 * COUNTS_PER_INCH);
    robot_arm.SetDegree(55);
    Sleep(0.5);
    robot_arm.SetDegree(45);
    Sleep(0.5);
    robot_arm.SetDegree(35);
    Sleep(0.5);
    robot_arm.SetDegree(25);
    Sleep(0.5);
    robot_arm.SetDegree(15);
    Sleep(0.5);
    robot_arm.SetDegree(5);
    Sleep(0.5);
    robot_arm.SetDegree(0);
    Sleep(2.0);
}
void UpRamp()
{
    // move_forward(left_motor_percent, right_motor_percent, up_ramp_inches * COUNTS_PER_INCH / fuck_up_divider);
    // turn_counterclockwise(25, COUNTS_PER_DEGREE * 90 / fuck_up_divider);
    // move_forward(left_motor_percent, right_motor_percent, 8 * COUNTS_PER_INCH / fuck_up_divider);
    // move_forward(left_motor_percent, right_motor_percent, to_table * COUNTS_PER_INCH / fuck_up_divider);
    // turn_clockwise(25, COUNTS_PER_DEGREE * 90 / fuck_up_divider);
    move_backward(left_motor_percent, right_motor_percent, 4 * COUNTS_PER_INCH);
    turn_clockwise(25, 95 * COUNTS_PER_DEGREE);
    move_backward(left_motor_percent, right_motor_percent, 9 * COUNTS_PER_INCH);
    turn_clockwise(25, 98 * COUNTS_PER_DEGREE);
    // check_heading(180);
    move_forward(left_motor_percent, right_motor_percent, 12 * COUNTS_PER_INCH);
    // check_x(31.9, PLUS);
    check_x(34, PLUS);
    turn_counterclockwise(25, 97 * COUNTS_PER_DEGREE);
    check_heading(270);
    move_forward(left_motor_percent + 5, right_motor_percent, 25 * COUNTS_PER_INCH);
    move_forward(left_motor_percent, right_motor_percent, 10 * COUNTS_PER_INCH);
    check_heading(270);
    // move_forward(left_motor_percent + 2, right_motor_percent, 20 * COUNTS_PER_INCH);
    // move_forward(left_motor_percent + 3, right_motor_percent, 20 * COUNTS_PER_INCH);
    check_y(51.5, PLUS);
    //     turn_counterclockwise(25, COUNTS_PER_DEGREE * 90);
    //     move_forward(left_motor_percent, right_motor_percent, 8 * COUNTS_PER_INCH);
    //     check_x(25.71, MINUS);
    //     turn_clockwise(25, COUNTS_PER_DEGREE * 90);
    //     check_heading(270);
    //     move_forward(left_motor_percent, right_motor_percent, 15 * COUNTS_PER_INCH);
    //     check_y(61.55, PLUS);
}
void DropBucket()
{
    robot_arm.SetDegree(10); // lower arm
    Sleep(0.5);
    move_backward(left_motor_percent, right_motor_percent, .5 * COUNTS_PER_INCH);
    robot_arm.SetDegree(20); // lower arm
    Sleep(0.5);
    move_backward(left_motor_percent, right_motor_percent, .5 * COUNTS_PER_INCH);
    robot_arm.SetDegree(30); // lower arm
    Sleep(0.5);
    move_backward(left_motor_percent, right_motor_percent, .5 * COUNTS_PER_INCH);
    robot_arm.SetDegree(40); // lower arm
    move_backward(left_motor_percent, right_motor_percent, .5 * COUNTS_PER_INCH);
    // Sleep(0.5);
    // robot_arm.SetDegree(50); // lower arm
    // Sleep(0.5);
    // robot_arm.SetDegree(60); // lower arm
    // Sleep(0.5);
    // robot_arm.SetDegree(65); // lower arm
    Sleep(0.5);
    move_backward(left_motor_percent, right_motor_percent, 6 * COUNTS_PER_INCH);
    // turn_counterclockwise(25, COUNTS_PER_DEGREE * 45);
    robot_arm.SetDegree(0);
}
void Bucket()
{
    ToBucket();
    UpRamp();
    DropBucket();
}

void Window()
{
    // turn left
    turn_counterclockwise(15, COUNTS_PER_DEGREE * 95);
    move_backward(left_motor_percent, right_motor_percent, 6 * COUNTS_PER_INCH); // flatten against wall
    check_heading(0);
    move_forward(left_motor_percent, right_motor_percent, 11 * COUNTS_PER_INCH);
    Sleep(1.0);
    window_arm.SetDegree(0);
    Sleep(1.0);
    move_forward(left_motor_percent + 5, right_motor_percent, 7 * COUNTS_PER_INCH);
    window_arm.SetDegree(90);
    // drop the arm
    // move forward
}
void Humidifier()
{
    // turn 45 left
    // go straight
    // read light
    // if blue hit button
    // otherwise hit button
    turn_clockwise(15, 95 * COUNTS_PER_DEGREE);
    check_heading(270);
    move_forward(left_motor_percent, right_motor_percent, 5 * COUNTS_PER_INCH);
    check_y(51.5, PLUS);
    turn_counterclockwise(15, 95 * COUNTS_PER_DEGREE);
    check_heading(0);
    check_x(13.11, MINUS);
    bool isRed = false;
    Sleep(1.0);
    if (cds.Value() <= blue_light)
    {
        isRed = true;
    }
    if (isRed)
    {
        LCD.WriteLine("RED");
    }
    else
    {
        LCD.WriteLine("BLUE!");
    }
    LCD.WriteLine(cds.Value());

    // turn towards the correct light
    if (!isRed)
    {
        turn_counterclockwise(15, COUNTS_PER_DEGREE * 20);
        move_forward(left_motor_percent, right_motor_percent, 5 * COUNTS_PER_INCH);
        // turn_clockwise(15, COUNTS_PER_DEGREE * 20);
    }
    else
    {
        turn_clockwise(15, COUNTS_PER_DEGREE * 20);
        move_forward(left_motor_percent, right_motor_percent, 5 * COUNTS_PER_INCH);
        // turn_counterclockwise(15, COUNTS_PER_DEGREE * 20);
    }
    // move forward into the light
    // move_forward(left_motor_percent, right_motor_percent, 3 * COUNTS_PER_INCH);
    // Sleep(1.0);
    move_backward(left_motor_percent, right_motor_percent, 5 * COUNTS_PER_INCH);
    // unrotate
    if (!isRed)
    {
        // turn_counterclockwise(15, COUNTS_PER_DEGREE * 20);
        // move_backward(left_motor_percent, right_motor_percent, 5 * COUNTS_PER_INCH);
        turn_clockwise(15, COUNTS_PER_DEGREE * 20);
    }
    else
    {
        // turn_clockwise(15, COUNTS_PER_DEGREE * 20);
        // move_backward(left_motor_percent, right_motor_percent, 3 * COUNTS_PER_INCH);
        turn_counterclockwise(15, COUNTS_PER_DEGREE * 20);
    }
    turn_clockwise(15, COUNTS_PER_DEGREE * 100);
}
void Lever()
{
    move_forward(left_motor_percent, right_motor_percent, 6 * COUNTS_PER_INCH);
    check_y(58, PLUS);
    turn_counterclockwise(15, 49 * COUNTS_PER_DEGREE);
    // check_heading(180);
    check_heading(315);
    // check_x(19.43, MINUS);
    // turn_clockwise(15, 45 * COUNTS_PER_DEGREE);
    // check_heading(315);
    // int lever = RCS.GetLever();
    // if (lever == 0)
    // {
    // turn_counterclockwise(15, 45 * COUNTS_PER_DEGREE);
    // move_forward(left_motor_percent, right_motor_percent, 4 * COUNTS_PER_INCH);
    // }
    // else if (lever == 1)
    // {
    // go straight
    move_forward(left_motor_percent, right_motor_percent, 2 * COUNTS_PER_INCH);
    // }
    // else
    // {
    // tilt right
    // turn_clockwise(15, 45 * COUNTS_PER_DEGREE);
    // move_forward(left_motor_percent, right_motor_percent, 4 * COUNTS_PER_INCH);
    // }
    robot_arm.SetDegree(95);
    Sleep(1.0);
    move_backward(left_motor_percent, right_motor_percent, 3 * COUNTS_PER_INCH);
    robot_arm.SetDegree(110);
    move_forward(left_motor_percent, right_motor_percent, 3 * COUNTS_PER_INCH);
    Sleep(3.0);
    robot_arm.SetDegree(0);
    // if (lever == 0)
    // {
    // turn_clockwise(15, 45 * COUNTS_PER_DEGREE);
    // }
    // else if (lever == 2)
    // {
    // turn_counterclockwise(15, 45 * COUNTS_PER_DEGREE);
    // }
    // press lever
    // move back
    // lower arm
    // pull lever up
    // go back to spawn point
}
void DownRamp()
{
    move_backward(left_motor_percent, right_motor_percent, 18 * COUNTS_PER_INCH);
    turn_clockwise(15, 49 * COUNTS_PER_DEGREE);
    check_heading(270);
    move_backward(left_motor_percent, right_motor_percent, 40 * COUNTS_PER_INCH);
    turn_counterclockwise(15, 50 * COUNTS_PER_DEGREE);
    move_backward(left_motor_percent, right_motor_percent, 6 * COUNTS_PER_INCH);
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
    window_arm.SetMax(servo_max);
    window_arm.SetMin(servo_min);
    robot_arm.SetDegree(0);
    window_arm.SetDegree(90);
    RCS.InitializeTouchMenu("1020C2JUU");
    WaitForFinalAction();
    while (cds.Value() > no_light)
    {
    }
    PressButton();
    CompostBin();
    Bucket();
    Window();
    Humidifier();
    Lever();
    DownRamp();

    // Sleep(1.0);
    // PressButton();
    // CompostBin();
    // Bucket();
    // Lever();
    // Humidifier();
    // Window();
    // if left lower than right increase left speed by .0001
}

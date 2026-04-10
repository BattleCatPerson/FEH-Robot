// #include <FEHLCD.h>
// #include <FEHIO.h>
// #include <FEHUtility.h>
// #include <FEHMotor.h>
// #include <FEHServo.h>

// #define COUNTS_PER_INCH 33.74
// #define COUNTS_PER_DEGREE 2.067

// DigitalEncoder right_encoder(FEHIO::Pin8);
// DigitalEncoder left_encoder(FEHIO::Pin11);
// FEHMotor right_motor(FEHMotor::Motor1, 9.0);
// FEHMotor left_motor(FEHMotor::Motor0, 9.0);
// AnalogInputPin cds(FEHIO::Pin0);
// FEHServo robot_arm(FEHServo::Servo7);

// void move_forward(int lpercent, int rpercent, int counts)
// {
//     right_encoder.ResetCounts();
//     left_encoder.ResetCounts();
//     right_motor.SetPercent(-rpercent);
//     left_motor.SetPercent(lpercent);
//     while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
//         ;
//     right_motor.Stop();
//     left_motor.Stop();
// }
// void move_backward(int lpercent, int rpercent, int counts)
// {
//     right_encoder.ResetCounts();
//     left_encoder.ResetCounts();
//     right_motor.SetPercent(rpercent);
//     left_motor.SetPercent(-lpercent);
//     while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
//         ;
//     right_motor.Stop();
//     left_motor.Stop();
// }
// void turn_counterclockwise(int percent, int counts)
// {
//     right_encoder.ResetCounts();
//     left_encoder.ResetCounts();
//     right_motor.SetPercent(-percent);
//     left_motor.SetPercent(-percent);
//     while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
//         ;
//     right_motor.Stop();
//     left_motor.Stop();
// }
// void turn_clockwise(int percent, int counts)
// {
//     right_encoder.ResetCounts();
//     left_encoder.ResetCounts();
//     right_motor.SetPercent(percent);
//     left_motor.SetPercent(percent);
//     while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
//         ;
//     right_motor.Stop();
//     left_motor.Stop();
// }

// // //The function used to drive in your robot code.
// // FUNCTION: DriveSomeDistance
// // Call ResetPIDVariables Function
// // //Be careful of potentially making your first time difference of 0, this can cause big errors!
// // WHILE (Encoders * Conversion) < GoalDistance DO
// // SetMotorPower( RightMotorPIDAdjustment(ExpectedSpeed))
// // SetMotorPower( LeftMotorPIDAdjustment(ExpectedSpeed))
// // Wait for Small Time to Get Data //To avoid time difference of 0
// // END
// float oldCountLeft = 0;
// float oldCountRight = 0;
// float newCountLeft = 0;
// float newCountRight = 0;
// float pastTime = 0;
// float newTime = 0;
// float iLeft = 0;
// float iRight = 0;
// float pLeft = 0;
// float pRight = 0;
// float dLeft = 0;
// float dRight = 0;
// float oldErrorLeft = 0;
// float oldErrorRight = 0;
// float leftErrorSum = 0;
// float rightErrorSum = 0;
// float oldMotorLeft = 0;
// float oldMotorRight = 0;
// void drive_distance(int percent, int inches)
// {
//     right_encoder.ResetCounts();
//     left_encoder.ResetCounts();
//     // ResetPID();
//     float goalCounts = inches * COUNTS_PER_INCH;
//     // reset
//     while ((right_encoder.Counts() + left_encoder.Counts()) / 2.0 < goalCounts)
//     {
//         // SetMotorPower( RightMotorPIDAdjustment(ExpectedSpeed))
//         // SetMotorPower( LeftMotorPIDAdjustment(ExpectedSpeed))
//         // Wait for Small Time to Get Data //To avoid time difference of 0
//         oldCountLeft = left_encoder.Counts();
//         oldCountRight = right_encoder.Counts();
//         Sleep(0.1);
//     }
//     left_motor.Stop();
//     right_motor.Stop();
// }
// // Stop Both Motors
// // END
// // //The function used to Reset PID each time.
// // FUNCTION: ResetPIDVariables
// void ResetPID()
// {
//     oldCountLeft = 0;
//     oldCountRight = 0;
//     newCountLeft = 0;
//     newCountRight = 0;
//     pastTime = 0;
//     newTime = 0;
//     iLeft = 0;
//     iRight = 0;
//     pLeft = 0;
//     pRight = 0;
//     dLeft = 0;
//     dRight = 0;
//     oldErrorLeft = 0;
//     oldErrorRight = 0;
//     leftErrorSum = 0;
//     rightErrorSum = 0;
//     oldMotorLeft = 0;
//     oldMotorRight = 0;
// }
// // Reset all Variables to Initial State
// // Record the Current Time
// // Reset Encoders
// // Wait for a Small Time to Get Data //To avoid time difference of 0
// // END
// // //The function used to do PID control
// // FUNCTION: PIDAdjustment
// // Find Change in Counts Since Last Time
// // Find Change in Time Since Last Time
// // Use to Find Actual Velocity
// // Find Error
// // Add Error to ErrorSum
// // Calculate PTerm
// // Calculate ITerm
// // Calculate DTerm
// // Save PastError, PastCounts, PastTime
// // Created by: John Jackson
// // Return (OldMotorPower + PTerm + ITerm + DTerm)
// float PIDAdjustment()
// {

//     return 0;
// }
// // END
// int left_motor_percent = 30;
// int right_motor_percent = 32; // Input power level here
// float no_light = 2.75;
// float up_ramp_inches = 23;
// float light_degrees = 10;
// int fuck_up_divider = 2;
// float final_button = 3;
// float final_button_back = 2;
// float to_bucket_one = 15.5;
// float to_bucket_two = 6;
// float to_bucket_two_two = 4;
// float to_bucket_three = 3;
// float to_table = 15;
// float back_from_table = 10;
// float to_lever = 10;
// int servo_max = 2500;
// int servo_min = 500;
// void PressButton()
// {
//     move_backward(left_motor_percent, right_motor_percent, final_button * COUNTS_PER_INCH / fuck_up_divider);
//     move_forward(left_motor_percent, right_motor_percent, final_button_back * COUNTS_PER_INCH / fuck_up_divider);
//     // turn_clockwise(25, COUNTS_PER_DEGREE * 45 / fuck_up_divider);
// }
// void ToBucket()
// {
//     // move_forward(left_motor_percent, right_motor_percent, to_bucket_one * COUNTS_PER_INCH / fuck_up_divider);
//     // turn_counterclockwise(25, COUNTS_PER_DEGREE * 90 / fuck_up_divider);
//     // move_forward(left_motor_percent, right_motor_percent, to_bucket_two * COUNTS_PER_INCH / fuck_up_divider);
//     // turn_clockwise(25, COUNTS_PER_DEGREE * 8 / fuck_up_divider);
//     // move_forward(left_motor_percent, right_motor_percent, to_bucket_two_two * COUNTS_PER_INCH / fuck_up_divider);
//     // robot_arm.SetDegree(65); // lower arm
//     // Sleep(2.0);
//     // move_forward(left_motor_percent, right_motor_percent, to_bucket_three * COUNTS_PER_INCH / fuck_up_divider);
//     // Sleep(1.0);
//     // robot_arm.SetDegree(0); // raise arm
//     // Sleep(2.0);
//     // move_backward(left_motor_percent, right_motor_percent, (to_bucket_two + to_bucket_two_two + to_bucket_three) * COUNTS_PER_INCH / fuck_up_divider);
//     // turn_clockwise(25, COUNTS_PER_DEGREE * 90 / fuck_up_divider);
//     move_forward(left_motor_percent, right_motor_percent, 22 * COUNTS_PER_INCH / fuck_up_divider);
//     turn_counterclockwise(25, COUNTS_PER_DEGREE * 47 / fuck_up_divider);
//     move_backward(left_motor_percent, right_motor_percent, 5 * COUNTS_PER_INCH / fuck_up_divider);
//     robot_arm.SetDegree(65);
//     Sleep(2.0);
//     move_forward(left_motor_percent, right_motor_percent, 7 * COUNTS_PER_INCH / fuck_up_divider);
//     robot_arm.SetDegree(55);
//     Sleep(0.5);
//     robot_arm.SetDegree(45);
//     Sleep(0.5);
//     robot_arm.SetDegree(35);
//     Sleep(0.5);
//     robot_arm.SetDegree(25);
//     Sleep(0.5);
//     robot_arm.SetDegree(15);
//     Sleep(0.5);
//     robot_arm.SetDegree(5);
//     Sleep(0.5);
//     robot_arm.SetDegree(0);
//     Sleep(2.0);
// }
// void UpRamp()
// {
//     // move_forward(left_motor_percent, right_motor_percent, up_ramp_inches * COUNTS_PER_INCH / fuck_up_divider);
//     // turn_counterclockwise(25, COUNTS_PER_DEGREE * 90 / fuck_up_divider);
//     // move_forward(left_motor_percent, right_motor_percent, 8 * COUNTS_PER_INCH / fuck_up_divider);
//     // move_forward(left_motor_percent, right_motor_percent, to_table * COUNTS_PER_INCH / fuck_up_divider);
//     // turn_clockwise(25, COUNTS_PER_DEGREE * 90 / fuck_up_divider);
//     move_backward(left_motor_percent, right_motor_percent, 4 * COUNTS_PER_INCH / fuck_up_divider);
//     turn_clockwise(25, 47 * COUNTS_PER_DEGREE / fuck_up_divider);
//     move_backward(left_motor_percent, right_motor_percent, 21 * COUNTS_PER_INCH / fuck_up_divider);
//     turn_clockwise(25, 47 * COUNTS_PER_DEGREE / fuck_up_divider);
//     move_forward(left_motor_percent + 2, right_motor_percent, 20 * COUNTS_PER_INCH / fuck_up_divider);
//     move_forward(left_motor_percent + 3, right_motor_percent, 20 * COUNTS_PER_INCH / fuck_up_divider);
//     turn_counterclockwise(25, COUNTS_PER_DEGREE * 110 / fuck_up_divider);
//     move_forward(left_motor_percent, right_motor_percent, 8 * COUNTS_PER_INCH / fuck_up_divider);
//     turn_clockwise(25, COUNTS_PER_DEGREE * 110 / fuck_up_divider);
//     move_forward(left_motor_percent, right_motor_percent, 15 * COUNTS_PER_INCH / fuck_up_divider);
// }
// void DropBucket()
// {
//     robot_arm.SetDegree(10); // lower arm
//     Sleep(0.5);
//     robot_arm.SetDegree(20); // lower arm
//     Sleep(0.5);
//     robot_arm.SetDegree(30); // lower arm
//     Sleep(0.5);
//     robot_arm.SetDegree(40); // lower arm
//     Sleep(0.5);
//     robot_arm.SetDegree(50); // lower arm
//     Sleep(0.5);
//     robot_arm.SetDegree(60); // lower arm
//     Sleep(0.5);
//     robot_arm.SetDegree(65); // lower arm
//     Sleep(0.5);
//     move_backward(left_motor_percent, right_motor_percent, 8 * COUNTS_PER_INCH / fuck_up_divider);
//     turn_counterclockwise(25, COUNTS_PER_DEGREE * 45 / fuck_up_divider);
//     robot_arm.SetDegree(0);
// }
// void PressLever()
// {
//     move_forward(left_motor_percent, right_motor_percent, to_lever * COUNTS_PER_INCH / fuck_up_divider);

//     Sleep(0.5);
//     robot_arm.SetDegree(0);
//     move_backward(left_motor_percent, right_motor_percent, 2 * COUNTS_PER_INCH / fuck_up_divider);
//     robot_arm.SetDegree(90);
//     move_forward(left_motor_percent, right_motor_percent, 2 * COUNTS_PER_INCH / fuck_up_divider);
//     robot_arm.SetDegree(0);
// }
// void ERCMain()
// {
//     // robot_arm.TouchCalibrate();
//     // robot_arm.SetMin(0);
//     // robot_arm.SetMax(180);

//     // turn right 45 degrees 54
//     // left_encoder.ResetCounts();
//     // right_encoder.ResetCounts();
//     // left_motor.SetPercent(25);
//     // right_motor.SetPercent(25);
//     // while (true)
//     // {
//     //     LCD.WriteLine(left_encoder.Counts());
//     //     LCD.WriteLine(right_encoder.Counts());
//     //     Sleep(0.5);
//     //     LCD.Clear();
//     // }
//     robot_arm.SetMax(servo_max);
//     robot_arm.SetMin(servo_min);
//     robot_arm.SetDegree(0);
//     while (cds.Value() > no_light)
//     {
//     }
//     Sleep(1.0);
//     // if left lower than right increase left speed by .0001
//     PressButton();
//     ToBucket();
//     UpRamp();
//     DropBucket();
//     PressLever();
//     // UpRamp();
//     // DropBucket();
//     // PressLever();
// }

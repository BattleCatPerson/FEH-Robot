// #include <FEHLCD.h>
// #include <FEHIO.h>
// #include <FEHUtility.h>
// #include <FEHMotor.h>

// #define COUNTS_PER_INCH 33.74
// #define COUNTS_PER_DEGREE 2.067

// DigitalEncoder right_encoder(FEHIO::Pin8);
// DigitalEncoder left_encoder(FEHIO::Pin14);
// FEHMotor right_motor(FEHMotor::Motor1,9.0);
// FEHMotor left_motor(FEHMotor::Motor0,9.0);
// AnalogInputPin cds(FEHIO::Pin0);

// void move_forward(int lpercent, int rpercent, int counts) //using encoders
// {
//     //Reset encoder counts
//     right_encoder.ResetCounts();
//     left_encoder.ResetCounts();

//     //Set both motors to desired percent
//     right_motor.SetPercent(-rpercent);
//     left_motor.SetPercent(lpercent);

//     //While the average of the left and right encoder is less than counts,
//     //keep running motors
//     while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

//     //Turn off motors
//     right_motor.Stop();
//     left_motor.Stop();
// }
// void move_backward(int lpercent, int rpercent, int counts) //using encoders
// {
//     //Reset encoder counts
//     right_encoder.ResetCounts();
//     left_encoder.ResetCounts();

//     //Set both motors to desired percent
//     right_motor.SetPercent(rpercent);
//     left_motor.SetPercent(-lpercent);

//     //While the average of the left and right encoder is less than counts,
//     //keep running motors
//     while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

//     //Turn off motors
//     right_motor.Stop();
//     left_motor.Stop();
// }
// void turn_counterclockwise(int percent, int counts)
// {
//     // Reset encoder counts
//     right_encoder.ResetCounts();
//     left_encoder.ResetCounts();

//     // Set both motors to desired percent
//     right_motor.SetPercent(percent);
//     left_motor.SetPercent(-percent);

//     // While the average of the left and right encoder are less than counts,
//     // keep running motors
//     while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
//         ;

//     // Turn off motors
//     right_motor.Stop();
//     left_motor.Stop();
// }
// void turn_clockwise(int percent, int counts)
// {
//     // Reset encoder counts
//     right_encoder.ResetCounts();
//     left_encoder.ResetCounts();

//     // Set both motors to desired percent
//     right_motor.SetPercent(-percent);
//     left_motor.SetPercent(percent);

//     // While the average of the left and right encoder are less than counts,
//     // keep running motors
//     while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
//         ;

//     // Turn off motors
//     right_motor.Stop();
//     left_motor.Stop();
// }
// void ERCMain()
// {
//     int left_motor_percent = 40;
//     int right_motor_percent = 40; //Input power level here
//     float no_light = 0.1;
//     float start_light = 1.5;
//     float red_light = 2.47;
//     float blue_light = 1.69;
//     float up_ramp_inches = 18;
//     float to_humidifier_light = 4;
//     float to_humidifier_button = 2;
//     float down_ramp_inches = 2;

//     // read light
//     while (cds.Value() < start_light) {}
//     // turn right 45 degrees 
//     turn_clockwise(25, COUNTS_PER_DEGREE * 45);
//     // drive up ramp
//     move_forward(left_motor_percent, right_motor_percent, up_ramp_inches * COUNTS_PER_INCH);
//     // turn left 90 degrees
//     turn_counterclockwise(25, COUNTS_PER_DEGREE * 90);
//     // move forward onto light
//     move_forward(left_motor_percent, right_motor_percent, to_humidifier_light * COUNTS_PER_INCH);
//     // read light
//     bool isRed = false;
//     Sleep(1.0);
//     if (cds.Value() >= red_light - 0.25) {
//         isRed = true;
//     }
//     // turn towards the correct light
//     if (isRed) {
//         turn_counterclockwise(25, COUNTS_PER_DEGREE * 45);
//     }
//     else {
//         turn_clockwise(25, COUNTS_PER_DEGREE * 45);
//     }
//     // move forward into the light
//     move_forward(left_motor_percent, right_motor_percent, to_humidifier_button);
//     // move backwards to the position before
//     move_backward(left_motor_percent, right_motor_percent, to_humidifier_button);
//     // unrotate
//     if (isRed) {
//         turn_clockwise(25, COUNTS_PER_DEGREE * 45);
//     }
//     else {
//         turn_counterclockwise(25, COUNTS_PER_DEGREE * 45);
//     }
//     // turn around 180 degrees
//     turn_clockwise(25, COUNTS_PER_DEGREE * 180);
//     // move forwards, turn right 90 degrees, move back to starting area
//     move_forward(left_motor_percent, right_motor_percent, to_humidifier_light);
//     turn_clockwise(25, COUNTS_PER_DEGREE * 90);
//     move_forward(left_motor_percent, right_motor_percent, down_ramp_inches);
// }




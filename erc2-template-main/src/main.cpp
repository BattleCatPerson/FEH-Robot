// #include <FEHLCD.h>
// #include <FEHIO.h>
// #include <FEHUtility.h>
// #include <FEHMotor.h>

// DigitalEncoder right_encoder(FEHIO::Pin8);
// DigitalEncoder left_encoder(FEHIO::Pin14);
// FEHMotor right_motor(FEHMotor::Motor1,9.0);
// FEHMotor left_motor(FEHMotor::Motor0,9.0);

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

// void ERCMain()
// {
//     int left_motor_percent = 40;
//     int right_motor_percent = 40; //Input power level here
//      //Input power level here
//     int expected_counts = 33.74 * 36; //Input theoretical counts here

//     int x, y; //for touch screen

//     //Initialize the screen
//     LCD.Clear(BLACK);
//     LCD.SetFontColor(WHITE);

//     // LCD.WriteLine("Shaft Encoder Exploration Test");
//     // LCD.WriteLine("Touch the screen");
//     // while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
//     // while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed

//     move_forward(left_motor_percent, right_motor_percent, expected_counts); //see function
//     // Sleep(2.0);
//     move_backward(left_motor_percent, right_motor_percent, expected_counts);

//     Sleep(2.0); //Wait for counts to stabilize
//     // //Print out data
//     // LCD.Write("Theoretical Counts: ");
//     // LCD.WriteLine(expected_counts);
//     // LCD.Write("Motor Percent: ");
//     // LCD.WriteLine(motor_percent);
//     // LCD.Write("Actual LE Counts: ");
//     // LCD.WriteLine(left_encoder.Counts());
//     // LCD.Write("Actual RE Counts: ");
//     // LCD.WriteLine(right_encoder.Counts());
// }




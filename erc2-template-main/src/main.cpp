// #include <FEHLCD.h>
// #include <FEHIO.h>
// #include <FEHSD.h>
// #include <FEHUtility.h>
// #include <FEHMotor.h>
// // Declarations for analog optosensors
// AnalogInputPin right_opto(FEHIO::Pin2);
// AnalogInputPin middle_opto(FEHIO::Pin1);
// AnalogInputPin left_opto(FEHIO::Pin0);
// FEHMotor drive_motor_left(FEHMotor::Motor0, 9.0);
// FEHMotor drive_motor_right(FEHMotor::Motor1, 9.0);

// enum LineStates
// {
//     MIDDLE,
//     RIGHT,
//     LEFT
// };

// void ERCMain()
// {
//     int state = MIDDLE; // Set the initial state
//     while (true)
//     { // I will follow this line forever!
//         switch (state)
//         {
//             // If I am in the middle of the line...
//         case MIDDLE:
//             LCD.WriteLine("MIDDLE");
//             LCD.Clear();
//             // Set motor powers for driving straight

//             /* Drive */
//             drive_motor_left.SetPercent(10);
//             drive_motor_right.SetPercent(-10);
//             if (left_opto.Value() >= 2.8)
//             {
//                 state = LEFT; // update a new state
//             }
//             else if (right_opto.Value() >= 2.8)
//             {
//                 state = RIGHT;
//             }
//             /* Code for if left sensor is on the line */

//             break;

//             // If the right sensor is on the line...

//         case RIGHT:

//             // Set motor powers for right turn
//             LCD.WriteLine("RIGHT");
//             LCD.Clear();

//             drive_motor_left.SetPercent(10);
//             drive_motor_right.SetPercent(10);
//             if (middle_opto.Value() >= 2.8)
//             {
//                 state = MIDDLE;
//             }

//             /* Drive */

//             break;

//             // If the left sensor is on the line...

//         case LEFT:
//             LCD.WriteLine("LEFT");
//             LCD.Clear();

//             drive_motor_left.SetPercent(-10);
//             drive_motor_right.SetPercent(-10);
//             /* Mirror operation of RIGHT state */
//             if (middle_opto.Value() >= 2.8)
//             {
//                 state = MIDDLE;
//             }
//             break;
//         default: // Error. Something is very wrong.
//             break;
//         }
//         // Sleep a bit

//         Sleep(50);
//     }
// while (true)
// {
//     bool onLeft = left_opto.Value() > 1.6;
//     bool onMiddle = middle_opto.Value() > 2;
//     bool onRight = right_opto.Value() > 2.6;
//     LCD.WriteLine("On Left: " + onLeft);
//     LCD.WriteLine("On Middle: " + onMiddle);
//     LCD.WriteLine("On Right: " + onRight);
//     Sleep(0.5);
//     LCD.Clear();
// }
// }

// #include <FEHLCD.h>
// #include <FEHIO.h>
// #include <FEHSD.h>
// #include <FEHUtility.h>
// #include <FEH.h>

// // Declarations for analog optosensors
// AnalogInputPin right_opto(FEHIO::Pin2);
// AnalogInputPin middle_opto(FEHIO::Pin1);
// AnalogInputPin left_opto(FEHIO::Pin0);

// void ERCMain()
// {
//     int x, y; // for touch screen

//     // Initialize the screen
//     LCD.Clear(BLACK);
//     LCD.SetFontColor(WHITE);

//     LCD.WriteLine("Analog Optosensor Testing");
//     LCD.WriteLine("Touch the screen");
//     while (!LCD.Touch(&x, &y))
//         ; // Wait for screen to be pressed
//     while (LCD.Touch(&x, &y))
//         ; // Wait for screen to be unpressed

//     // Record values for optosensors on and off of the straight line
//     // Left Optosensor on straight line
//     LCD.Clear(BLACK);
//     LCD.WriteLine("Place left optosensor on straight line");
//     Sleep(0.25); // Wait to avoid double input
//     LCD.WriteLine("Touch screen to record value (1/12)");
//     while (!LCD.Touch(&x, &y))
//         ; // Wait for screen to be pressed
//     while (LCD.Touch(&x, &y))
//         ; // Wait for screen to be unpressed
//     // Write the value returned by the optosensor to the screen
//     float leftOptosensorValue = left_opto.Value();
//     LCD.Write("Left Optosensor Value:");
//     LCD.WriteLine(leftOptosensorValue);
//     Sleep(2.0); // Wait to avoid double input

//     // Left Optosensor off straight line
//     LCD.Clear(BLACK);
//     LCD.WriteLine("Place left optosensor off straight line");
//     Sleep(0.25); // Wait to avoid double input
//     LCD.WriteLine("Touch screen to record value (2/12)");
//     while (!LCD.Touch(&x, &y))
//         ; // Wait for screen to be pressed
//     while (LCD.Touch(&x, &y))
//         ; // Wait for screen to be unpressed
//     // Write the value returned by the optosensor to the screen
//     leftOptosensorValue = left_opto.Value();
//     LCD.Write("Left Optosensor Value (off line):");
//     LCD.WriteLine(leftOptosensorValue);
//     Sleep(2.0); // Wait to avoid double input

//     // Right Optosensor on straight line
//     LCD.Clear(BLACK);
//     LCD.WriteLine("Place right optosensor on straight line");
//     Sleep(0.25); // Wait to avoid double input
//     LCD.WriteLine("Touch screen to record value (1/12)");
//     while (!LCD.Touch(&x, &y))
//         ; // Wait for screen to be pressed
//     while (LCD.Touch(&x, &y))
//         ; // Wait for screen to be unpressed
//     // Write the value returned by the optosensor to the screen
//     float rightOptoValue = right_opto.Value();
//     LCD.Write("Right Optosensor Value:");
//     LCD.WriteLine(rightOptoValue);
//     Sleep(2.0); // Wait to avoid double input

//     // Right Optosensor off straight line
//     LCD.Clear(BLACK);
//     LCD.WriteLine("Place right optosensor off straight line");
//     Sleep(0.25); // Wait to avoid double input
//     LCD.WriteLine("Touch screen to record value (2/12)");
//     while (!LCD.Touch(&x, &y))
//         ; // Wait for screen to be pressed
//     while (LCD.Touch(&x, &y))
//         ; // Wait for screen to be unpressed
//     // Write the value returned by the optosensor to the screen
//     rightOptoValue = right_opto.Value();
//     LCD.Write("Right Optosensor Value (off line):");
//     LCD.WriteLine(rightOptoValue);
//     Sleep(2.0); // Wait to avoid double input

//     // Middle Optosensor on straight line
//     LCD.Clear(BLACK);
//     LCD.WriteLine("Place right optosensor on straight line");
//     Sleep(0.25); // Wait to avoid double input
//     LCD.WriteLine("Touch screen to record value (1/12)");
//     while (!LCD.Touch(&x, &y))
//         ; // Wait for screen to be pressed
//     while (LCD.Touch(&x, &y))
//         ; // Wait for screen to be unpressed
//     // Write the value returned by the optosensor to the screen
//     float middleOptoValue = middle_opto.Value();
//     LCD.Write("Middle Optosensor Value:");
//     LCD.WriteLine(middleOptoValue);
//     Sleep(2.0); // Wait to avoid double input
//     // Right Optosensor off straight line
//     LCD.Clear(BLACK);
//     LCD.WriteLine("Place right optosensor off straight line");
//     Sleep(0.25); // Wait to avoid double input
//     LCD.WriteLine("Touch screen to record value (2/12)");
//     while (!LCD.Touch(&x, &y))
//         ; // Wait for screen to be pressed
//     while (LCD.Touch(&x, &y))
//         ; // Wait for screen to be unpressed
//     // Write the value returned by the optosensor to the screen
//     middleOptoValue = middle_opto.Value();
//     LCD.Write("Middle Optosensor Value (off line):");
//     LCD.WriteLine(middleOptoValue);
//     Sleep(2.0); // Wait to avoid double input
//     // Print end message to screen
//     LCD.Clear(BLACK);
//     LCD.WriteLine("Test Finished");
// }

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>

// Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::Pin9);
DigitalEncoder left_encoder(FEHIO::Pin8);
FEHMotor right_motor(FEHMotor::Motor0, 9.0);
FEHMotor left_motor(FEHMotor::Motor1, 9.0);

void move_forward(int percent, int counts) // using encoders
{
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    // Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    // While the average of the left and right encoder is less than counts,
    // keep running motors
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
        ;

    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_right(int percent, int counts) // using encoders
{

    // Reset encoder counts

    right_encoder.ResetCounts();

    left_encoder.ResetCounts();

    // Set both motors to desired percent
    left_motor.SetPercent(percent);
    right_motor.SetPercent(0);

    // hint: set right motor backwards, left motor forwards

    //<ADD CODE HERE>
    while (left_encoder.Counts() <= counts * 1.85)
    {
    }

    // While the average of the left and right encoder is less than counts,

    // keep running motors

    //<ADD CODE HERE>

    // Turn off motors

    right_motor.Stop();

    left_motor.Stop();
}
void turn_left(int percent, int counts) // using encoders
{

    // Reset encoder counts

    right_encoder.ResetCounts();

    left_encoder.ResetCounts();

    // Set both motors to desired percent
    left_motor.SetPercent(0);
    right_motor.SetPercent(percent);

    // hint: set right motor backwards, left motor forwards

    //<ADD CODE HERE>
    while (right_encoder.Counts() <= counts * 1.85)
    {
    }

    // While the average of the left and right encoder is less than counts,

    // keep running motors

    //<ADD CODE HERE>

    // Turn off motors

    right_motor.Stop();

    left_motor.Stop();
}
void ERCMain()
{
    int motor_percent = 25;    // Input power level here
    double base_counts = 40.4;
    int rotation_counts = 243; 
    int x, y; // for touch screen
    move_forward(motor_percent, 566);
    turn_left(motor_percent, rotation_counts);
    move_forward(motor_percent, 404);
    turn_right(motor_percent, rotation_counts);
    move_forward(motor_percent, 162);

    // Initialize the screen
    // LCD.Clear(BLACK);
    // LCD.SetFontColor(WHITE);

    // LCD.WriteLine("Shaft Encoder Exploration Test");
    // LCD.WriteLine("Touch the screen");
    // while (!LCD.Touch(&x, &y))
    //     ; // Wait for screen to be pressed
    // while (LCD.Touch(&x, &y))
    //     ; // Wait for screen to be unpressed

    // move_forward(motor_percent, expected_counts); // see function

    // Sleep(2.0); // Wait for counts to stabilize
    // // Print out data
    // LCD.Write("Theoretical Counts: ");
    // LCD.WriteLine(expected_counts);
    // LCD.Write("Motor Percent: ");
    // LCD.WriteLine(motor_percent);
    // LCD.Write("Actual LE Counts: ");
    // LCD.WriteLine(left_encoder.Counts());
    // LCD.Write("Actual RE Counts: ");
    // LCD.WriteLine(right_encoder.Counts());
}

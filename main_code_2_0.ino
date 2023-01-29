/* Human Following + Obstacle avoiding Robot
    Team :
    Snahal Kumar
    Somya Sinha
    Sagar Jha
    Mentor : Dr.Sumeet Gupta

*/

/*  Motor Connections(M)
            __
      motor1(O):  :(O)motor4
               |  |
               |  |
      motor2(O):__:(O)motor3

*/

#include <AFMotor.h> //To Control Motor Movements
#include <Servo.h> //To Control Servo motor

#define MAX_DISTANCE 200
#define MAX_SPEED 110 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20 

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

boolean goesForward = false;
boolean goesBackward = false;

unsigned int speedSet = 0;

/* Declaring Middle Ultrasonic Pins */
#define Mtrig A1
#define Mecho A0
unsigned int Mduration = 0, Mdistance = 0;


#define RIGHT A2 // Right IR sensor connected to analog pin A2 of Arduino Uno:
#define LEFT A3  // Left IR sensor connected to analog pin A3 of Arduino Uno:

Servo myservo;
int pos = 0;

unsigned int Right_Value = 0; // Variable to store Right IR sensor value:
unsigned int Left_Value = 0;  // Variable to store Left IR sensor value:
unsigned int count = 0;
unsigned int R_S = 0;
unsigned int L_S = 0;

void setup()
{


    /* Configure input and output port of sensors */
    pinMode(Mtrig, OUTPUT);
    pinMode(Mecho, INPUT);


    Serial.begin(9600); // initailize serial communication at 9600 bits per second:
    myservo.attach(10); // servo attached to pin 10 of Arduino UNO

    {
        for (pos = 100; pos <= 180; pos += 1)
        {                       // goes from 100 degrees to 180 degrees:
            myservo.write(pos); // tell servo to move according to the value of 'pos' variable:
            delay(15);          // wait 15ms for the servo to reach the position:
        }
        for (pos = 180; pos >= 0; pos -= 1)
        {                       // goes from 180 degrees to 0 degrees:
            myservo.write(pos); // tell servo to move according to the value of 'pos' variable:
            delay(15);          // wait 15ms for the servo to reach the position:
        }
        for (pos = 0; pos <= 100; pos += 1)
        {                       // goes from 180 degrees to 0 degrees:
            myservo.write(pos); // tell servo to move according to the value of 'pos' variable:
            delay(15);          // wait 15ms for the servo to reach the position:
        }
    }
    myservo.write(100);
    delay(2000);
    pinMode(RIGHT, INPUT); // set analog pin RIGHT as an input:
    pinMode(LEFT, INPUT);  // set analog pin RIGHT as an input:
}

void loop()
{
    delay(50);
    distanceMeasure();    
    Right_Value = digitalRead(RIGHT); // read the value from Right IR sensor:
    delay(20);
    Left_Value = digitalRead(LEFT);   // read the value from Left IR sensor:

    Serial.print("RIGHT : ");
    Serial.println(Right_Value);
    Serial.print("LEFT : ");
    Serial.println(Left_Value);

    if (Mdistance < 45 && Mdistance > 15 && (Right_Value == 1) && (Left_Value == 1))
    {
        moveForward();
        // delay(2000);
        Serial.println("******************FORWARD");
    }
    else if ((Right_Value == 0 && Left_Value == 1) || (Right_Value == 1 && Left_Value == 0))
    {
        moveStop();
        // count++;
        Serial.print("RIGHT : ");
        Serial.println(Right_Value);
        Serial.print("LEFT : ");
        Serial.println(Left_Value);
        if ((Right_Value == 0 && Left_Value == 1))
        {
            // delay(1000);
            Serial.println("***************** Right first");
            while (Left_Value)
            {
                Left_Value = digitalRead(LEFT);
                delay(20);
            }
            Serial.println("***************** START ");
            // delay(1000);
        }
        else if ((Right_Value == 1 && Left_Value == 0))
        {
            // delay(1000);
            Serial.println("*****************Left First ");
            while (Right_Value)
            {
                Right_Value = digitalRead(RIGHT);
                delay(20);
            }
            Serial.println("***************** START");
            // delay(1000);
        }
    }
    else if (Mdistance < 10 && (Right_Value == 0) && (Left_Value == 0))
    {
        moveBackward();
        Right_Value = 1;
        Left_Value = 1;
        // delay(2000);
        Serial.println("******************BACK");
    }
    else if (Mdistance > 40 && (Right_Value == 1) && (Left_Value == 1))
    {
        moveStop();
        delay(100);
        lookRight();
        //It will look right first and then recursively call the left function 
    }
    else
    {
        moveStop();
        // delay(2000);
        Serial.println("******************STOP");
    }

    //######################################################
}

void distanceMeasure()
{
    // Middle ultrasonic
    digitalWrite(Mtrig, LOW);
    delayMicroseconds(2);
    digitalWrite(Mtrig, HIGH);
    delayMicroseconds(6);
    digitalWrite(Mtrig, LOW);

    // Read the signal from the sensor
    pinMode(Mecho, INPUT);
    Mduration = pulseIn(Mecho, HIGH); // in microsecond

    // Convert the time into a distance
    //##Distance = (Time x speed of sound in cm/ms ) / 2(sound has to travel back and forth.)
    Mdistance = (Mduration / 2) * 0.0343; // Divide by 29.1 or multiply by 0.0343
    Serial.print(" Middle : ");
    Serial.println(Mdistance);
    delay(2);
}

void moveStop()
{
    goesForward = false;
    goesBackward = false;
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}

void moveForward()
{

    if (!goesForward)
    {
        Serial.println("!!!!!!!!!!!!     F     !!!!!!!!!!!!!!");
        goesForward = true;
        goesBackward = false;
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
        for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 5) 
        {
            motor1.setSpeed(speedSet);
            motor2.setSpeed(speedSet);
            motor3.setSpeed(speedSet);
            motor4.setSpeed(speedSet);
            delay(5);
        }
    }
}

void moveBackward()
{
    if (!goesBackward)
    {
        Serial.println("!!!!!!!!!!!!     B     !!!!!!!!!!!!!!");
        goesForward = false;
        goesBackward = true;
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        motor3.run(BACKWARD);
        motor4.run(BACKWARD);
        for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 6)
        {
            motor1.setSpeed(speedSet);
            motor2.setSpeed(speedSet);
            motor3.setSpeed(speedSet);
            motor4.setSpeed(speedSet);
            delay(5);
        }
        delay(400);
    }
}

int turnRight(int z)
{
    motor1.setSpeed(200);
    motor2.setSpeed(200);
    motor3.setSpeed(200);
    motor4.setSpeed(200);
    Serial.println("******* RIGHT TURN ********");
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    delay(z);
    motor1.setSpeed(MAX_SPEED);
    motor2.setSpeed(MAX_SPEED);
    motor3.setSpeed(MAX_SPEED);
    motor4.setSpeed(MAX_SPEED);   
}

int turnLeft(int z)
{
    motor1.setSpeed(200);
    motor2.setSpeed(200);
    motor3.setSpeed(200);
    motor4.setSpeed(200);
    Serial.println("******* LEFT TURN ********");
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    delay(z);
    motor1.setSpeed(MAX_SPEED);
    motor2.setSpeed(MAX_SPEED);
    motor3.setSpeed(MAX_SPEED);
    motor4.setSpeed(MAX_SPEED);
}



int lookRight()
{
    myservo.write(50); 
    delay(500);
    distanceMeasure();
    //First it will look right for the human and mesures the distance 
    delay(500);
    if (Mdistance < 50)
    {
        myservo.write(100);
        // If distance < 50 then it will start movement
        delay(100);
        turnRight(200);
        return 1;
    }
    myservo.write(100);
    delay(500);
    distanceMeasure();
    if (Mdistance < 50)
    {
        moveForward();
        return 0;
    }
    lookLeft();
}

int lookLeft()
{
    myservo.write(150);
    delay(500);
    distanceMeasure();
    delay(500);
    if (Mdistance < 50)
    {
        myservo.write(100);
        delay(100);
        turnLeft(200);
        return 2;
    }
    myservo.write(100);
    delay(500);
    distanceMeasure();
    if (Mdistance < 50)
    {
        moveForward();
        return 0;
    }
    lookRight();
}

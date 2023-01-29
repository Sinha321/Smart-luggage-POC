# Human Following & Obstacle Avoidance Luggage (POC) ✅

In this project we present a prototype proof of concept that uses Arduino Uno along with sensors. It can follow humans and carry their luggage at the same time it can avoid the interference of other humans or animals that passes in between. 

<img
  src="https://github.com/Smart-Luggage-POC/Smart-luggage-POC/blob/main/images/Old%20man%20and%20robot.png"
  alt="Old Man"
  style="display: inline-block; margin: 0 auto; width: 100%; height:400px; ">
  

Our objective is to serve old people and medical centers or handicaped people to get the benefits of this automated robot. This robot will serve as a luggage carrier that can lift upto 20 kgs of weight or as a shopping cart. In medical centers this robot serves handicapped people as a wheel chair that follows the nurse or as an emergency bed.

## Introduction and Objective

A four wheel luggage carrier robot that can automatically mimic some human movements and functions like moving back left right and front with humans. To follow a person within a certain distance and avoid obstacles at the same time. 
Everyone tries to carry less baggage as it assures comfort but at times we don’t have a choice other than carrying huge and heavy luggages for long distance travel. A shopping-time robot that carries goods and walks behind people without a controller would be more helpful.

#### The main objectives are : 
* Luggage Carrier and Follower
* Automated Wheel Chair at Hospitals

<a href="https://github.com/Smart-Luggage-POC/Smart-luggage-POC/blob/main/images/Schematic.png" target="_blank">View Schematic</a>

## Working Methodology of Human Following

<img
  src="https://github.com/Smart-Luggage-POC/Smart-luggage-POC/blob/main/images/old%20women.png"
  alt="Old Women"
  style="display: inline-block; margin: 0 auto; width: 700px; height:400px; ">

There are 3 sensors having different purposes. Sensor in this image is used to detect the distance range to command the controller for back and front movement with acceleration. 
Other two sensors are used to detect the obstacle that crosses in between and for backward movement.

## Obstacle Avoidance Working Concept and Code
<img
  src="https://github.com/Smart-Luggage-POC/Smart-luggage-POC/blob/main/images/left%20right%20control.png"
  alt="Schematic"
  style="display: inline-block; margin: 0 auto; width: 100%; height:400px; ">
  
  
``` cpp
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
```
## Left Right Control of the Robot

<img
  src="https://github.com/Smart-Luggage-POC/Smart-luggage-POC/blob/main/images/looks.png"
  alt="LOOKS"
  style="display: inline-block; margin: 0 auto; width: 100%; height:400px; ">
  
<img
  src="https://github.com/Smart-Luggage-POC/Smart-luggage-POC/blob/main/images/left%20right%20serial.png"
  alt="LOOKS"
  style="display: inline-block; margin: 0 auto; width: 100%; height:400px; ">
  

When the front distance is greater than 45cm then it calls a function to check left then front then right recursively until it triggers distance less than 50cm.  As the distance condition becomes true then it calls the forward function and accelerates for the first time and continues to follow human with constant speed. 
If again the human moves toward left or right then the robot will stop and check for left, front and right to capture the human as distance.

  
### Function for Left look 
``` cpp
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
```

### Function for right look

``` cpp
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
```

For more fork this repo and support us with a star ⭐ Thanks !


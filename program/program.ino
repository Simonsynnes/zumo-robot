// LIBRARIES ----------------------------
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
//---------------------------------------


// SWITCH CASES -------------------------
const int case_normal = 0; // Look for opponent
const int case_chase = 1; // Opponent found
const int case_boundary_detected = 2; // Robot is standing on track limit
// --------------------------------------

// MOTOR --------------------------------
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     400
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms
// --------------------------------------

// ZUMO ---------------------------------
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
unsigned int sensor_values[6];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
//---------------------------------------

void setup() 
{
  button.waitForButton();
  delay(3000);  
}

void loop() 
{
   sensors.read(sensor_values);

  // Get all sensor data
  int lightSensorLeftValue = 0;
  int lightSensorRightValue = 0;
  int distanceSensorValue = 0;
  
  // Create action based on sensor data
  int action = validateSensorData(lightSensorLeftValue, lightSensorRightValue, distanceSensorValue);
  
  // Perform action based on sensor data
  switch (action)
  {
    case case_normal:
    normal();
    break;
    
    case case_chase:
    chase();
    break;
    
    case case_boundary_detected:
    boundaryDetected();
    break;
  }
}

int validateSensorData(int lightLeft, int lightRight, int distance)
{
  
}

void chase()
{

}

void normal()
{
  
}

void boundaryDetected()
{

}

void motorReverseTurnLeft()
{
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
}

void motorReverseTurnRight()
{
	motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
}

void motorTurnLeft()
{
  motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
}

void motorTurnRight()
{
  motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
}

void motorForward()
{
	motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
}

void motorReverse()
{
  motors.setSpeeds(REVERSE_SPEED, REVERSE_SPEED);
}

void motorStop()
{
	motors.setSpeeds(0, 0);
}

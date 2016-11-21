// LIBRARIES ----------------------------
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <avr/pgmspace.h>
#include <Wire.h>
#include <LSM303.h>
//---------------------------------------

// SWITCH CASES -------------------------
const int case_normal = 0; // Look for opponent
const int case_turn = 1;
const int case_chase = 2; // Opponent found
const int case_boundary_detected = 3; // Robot is standing on track limit
// --------------------------------------

// MOTOR --------------------------------
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        300
#define FORWARD_SPEED     300
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     50 // ms
// --------------------------------------

// ZUMO ---------------------------------
#define NUM_SENSORS 6
#define QTR_THRESHOLD  1600
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
unsigned int sensor_values[6];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
//---------------------------------------

// DISTANCE -----------------------------
int DISTANCE_SENSOR_FRONT_PIN = 2;
int SIGHT_THRESHOLD_1 = 150;

int DISTANCE_SENSOR_BACK_PIN = 0;
int SIGHT_THRESHOLD_2 = 400;
//---------------------------------------

void setup() 
{
  Serial.begin(9600);
  button.waitForButton();
  delay(5000);  
}

void loop() 
{
  int distanceSensorFrontValue = analogRead(DISTANCE_SENSOR_FRONT_PIN);
  int distanceSensorBackValue = analogRead(DISTANCE_SENSOR_BACK_PIN);
 
  
  sensors.read(sensor_values);

  // Get all sensor data
  int lightSensorLeftValue = sensor_values[0];
  int lightSensorRightValue = sensor_values[5];
  int opponentSensorValue = isOpponentInSight(distanceSensorFrontValue, distanceSensorBackValue);

    Serial.print("Left sensor: ");
    Serial.println(lightSensorLeftValue);
    Serial.print("Right sensor: ");
    Serial.println(lightSensorRightValue);
  
  // Create action based on sensor data
  int action = validateSensorData(lightSensorLeftValue, lightSensorRightValue, opponentSensorValue);
  
  // Perform action based on sensor data
  switch (action)
  {
    case case_normal:
		normal();
		break;

    case case_turn:
    turn();
    break;
    
    case case_chase:
		chase();
		break;
    
    case case_boundary_detected:
		boundaryDetected(lightSensorLeftValue, lightSensorRightValue);
		break;
  }
}

int validateSensorData(int lightLeft, int lightRight, int opponent)
{
  if (lightLeft > QTR_THRESHOLD || lightRight > QTR_THRESHOLD)
  {
    return case_boundary_detected;
  }
  
  if (opponent == case_chase)
  {
    return case_chase;
  }

  if (opponent == case_turn)
  {
    return case_turn;
  }
  
  return case_normal;
}

void chase()
{
	motorForward();
}

void turn()
{
   motorTurnRobotAround();
}

void normal()
{
	motorTurnLeft();
}

void boundaryDetected(int lightLeft, int lightRight)
{
  if (lightLeft > QTR_THRESHOLD)
  {
    motorReverseTurnRight();
  }
  else if (lightRight > QTR_THRESHOLD)
  {
    motorReverseTurnLeft();
  }
}

int isOpponentInSight(int frontSensor, int backSensor)
{
  if (frontSensor > SIGHT_THRESHOLD_1)
  {
    return case_chase;
  }

  if (backSensor > SIGHT_THRESHOLD_2)
  {
    return case_turn;
  }
  
   return 0;
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

void motorTurnRobotAround()
{
  motorStop();
  motors.setSpeeds(-400, 400);
  delay(425);
  motorStop();
}

void motorTurnLeft()
{
	motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
}

void motorTurnRight()
{
	motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
}

void motorReverse()
{
	motors.setSpeeds(REVERSE_SPEED, REVERSE_SPEED);
}

void motorForward()
{
	motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
}

void motorStop()
{
	motors.setSpeeds(0, 0);
}

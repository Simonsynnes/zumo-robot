<<<<<<< .merge_file_a01624
=======
// LIBRARIES ----------------------------
>>>>>>> .merge_file_a06592
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
<<<<<<< .merge_file_a01624
#include <avr/pgmspace.h>
#include <Wire.h>
#include <LSM303.h>

=======
//---------------------------------------
>>>>>>> .merge_file_a06592


// SWITCH CASES -------------------------
const int case_normal = 0; // Look for opponent
const int case_chase = 1; // Opponent found
const int case_boundary_detected = 2; // Robot is standing on track limit
// --------------------------------------
// Accelerometer Settings
#define RA_SIZE 3  // number of readings to include in running average of accelerometer readings
#define XY_ACCELERATION_THRESHOLD 2400  // for detection of contact (~16000 = magnitude of acceleration due to gravity)
// Dependency for Acceelreometer 
template <typename T>
class RunningAverage
{
  public:
    RunningAverage(void);
    RunningAverage(int);
    ~RunningAverage();
    void clear();
    void addValue(T);
    T getAverage() const;
    void fillValue(T, int);
  protected:
    int _size;
    int _cnt;
    int _idx;
    T _sum;
    T * _ar;
    static T zero;
};

<<<<<<< .merge_file_a01624
// Accelerometer Class -- extends the LSM303 Library to support reading and averaging the x-y acceleration 
class Accelerometer : public LSM303
{
  typedef struct acc_data_xy
  {
    unsigned long timestamp;
    int x;
    int y;
    float dir;
  } acc_data_xy;
  
  public: 
    Accelerometer() : ra_x(RA_SIZE), ra_y(RA_SIZE) {};
    ~Accelerometer() {};
    void enable(void);
    void getLogHeader(void);
    void readAcceleration(unsigned long timestamp);
    float len_xy() const;
    float dir_xy() const;
    int x_avg(void) const;
    int y_avg(void) const;
    long ss_xy_avg(void) const;
    float dir_xy_avg(void) const;
  private:
    acc_data_xy last;
    RunningAverage<int> ra_x;
    RunningAverage<int> ra_y;   
};

Accelerometer lsm303;
boolean in_contact;  // set when accelerometer detects contact with other rubuts

void setup()
{
 // Initiate LSM303
  lsm303.init();
  lsm303.enable();
=======
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
>>>>>>> .merge_file_a06592
}

void loop()
{
   sensors.read(sensor_values);

  // Get all sensor data
  int lightSensorLeftValue = 0;
  int lightSensorRightValue = 0;
  int distanceSensorValue = 0;

  // Create action based on sensor data
 

  // Perform action based on sensor data
<<<<<<< .merge_file_a01624

=======
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
  
>>>>>>> .merge_file_a06592
}

void chase()
{
   if (check_for_contact()) on_contact_made();
    motors.setSpeeds(speed, speed);
}


void normal()
{

}

void boundaryDetected()
{

}

<<<<<<< .merge_file_a01624

// chse functions:

bool check_for_contact() // check shit
{
  static long threshold_squared = (long) XY_ACCELERATION_THRESHOLD * (long) XY_ACCELERATION_THRESHOLD;
  return (lsm303.ss_xy_avg() >  threshold_squared) && \
  
}

// Accelerate if it sees enemies (ALLAHUAKBAR)
void on_contact_made()
{
  in_contact = true;
  contact_made_time = loop_start_time;
  

}
}
=======
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

void motorForward()
{
	motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
}

void motorStop()
{
	motors.setSpeeds(0, 0);
}
>>>>>>> .merge_file_a06592

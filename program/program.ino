#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <avr/pgmspace.h>
#include <Wire.h>
#include <LSM303.h>



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
}

void loop()
{
  // Get all sensor data
  int lightSensorLeftValue = 0;
  int lightSensorRightValue = 0;
  int distanceSensorValue = 0;

  // Create action based on sensor data
 

  // Perform action based on sensor data

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

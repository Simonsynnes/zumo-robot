// SWITCH CASES -------------------------
const int case_normal = 0; // Look for opponent
const int case_chase = 1; // Opponent found
const int case_boundary_detected = 2; // Robot is standing on track limit
// --------------------------------------

void setup() 
{

}

void loop() 
{
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
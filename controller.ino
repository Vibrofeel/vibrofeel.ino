// Assigning pins to controller
// Output pins need to have pwm output
// you can check your pinot of your board here
// https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
int small_motor = 3;
int large_motor = 5;

// holding values of the motor
// Because analogWrite can be quite expensive we are storring values in memory and calling analogWrite function when needed
int small_motor_value = 0;
int large_motorValue = 0;

void setup()
{
  pinMode(small_motor, OUTPUT);
  pinMode(large_motor, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(1);
}
void loop()
{
  // We are expecting 2 bytes from our sender after we got those values we execute the if statement  

  if (Serial.available() > 1)
  {
    int small_motor_received_value = Serial.read(); // First byte is small motor
    int large_motor_received_value = Serial.read(); // Second byte is large motor
    bool perform = true;

    // In case where we would receive more bytes that expected we turn off all the motors as 
    // the data being received is not correct and will render incorrect results 
    while (Serial.available())
    {
      Serial.read();
      perform = false;
    }
    if (!perform)
    {
      small_motor_received_value = 0;
      large_motor_received_value = 0;
    }

    // comparing values and updating the motors if needed

    // Small motor update
    if (small_motor_received_value != small_motor_value)
    {
      analogWrite(small_motor, small_motor_received_value);
    }
    small_motor_value = small_motor_received_value;

    //Large motor update
    if (large_motor_received_value != large_motorValue)
    {
      analogWrite(large_motor, large_motor_received_value);
    }
    large_motorValue = large_motor_received_value;
  }
}
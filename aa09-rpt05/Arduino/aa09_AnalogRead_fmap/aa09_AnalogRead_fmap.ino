/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Attach the center pin of a potentiometer to pin A0, 
  and the outside pins to +5V and ground.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  //float voltage = map(sensorValue, 0, 1023, 0.0, 5.0);  // map 0~1023 to 0~5
//  float voltage = sensorValue*(5.0/1023.0);
  float voltage = f_map(sensorValue, 0, 1023, 0.0, 5.0);  // map 0~1023 to 0~5
  // print out the value you read:
  Serial.print("AA09, Present voltage (0.0 ~ 5.0) : ");
  Serial.println(voltage);
  delay(500);        // delay in between reads for stability
}

float f_map(long x, long in_min, long in_max, float out_min, float out_max)
{
  return(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

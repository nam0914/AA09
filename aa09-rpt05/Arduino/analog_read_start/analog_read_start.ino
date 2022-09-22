/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Attach the center pin of a potentiometer to pin A0, 
  and the outside pins to +5V and ground.
*/

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  Serial.print("AA09,Present V(0~5.0):");
  float voltage = sensorValue*(5.0/1023.0);
  Serial.println(voltage);
  delay(500);
  
  
  // print out the value you read:


  
  delay(500);        // 2 Hz sampling
}

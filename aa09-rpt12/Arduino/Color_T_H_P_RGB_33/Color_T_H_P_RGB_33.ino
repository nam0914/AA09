/*
  Color & Temperature/Humidity

*/

#include <Arduino_HTS221.h>   // library for temperature & humidity
// Library: HTS221
#include <Arduino_APDS9960.h>
// Library: APDS9960 for gesture, proximity, color & luminosity
#include <Arduino_LPS22HB.h>
// for pressure
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }
  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
//    while (1);
  }
  //Serial.println("R,G,B,AL,T,H");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  
  // check if a color reading is available
  while (! APDS.colorAvailable()) {
    delay(5);
  }
  int r, g, b, aL;

  // read the color
  APDS.readColor(r, g, b, aL);

  // read T, H
  float temperature = HTS.readTemperature();
  float humidity = HTS.readHumidity();

  // read pressure
  float pressure = BARO.readPressure(MILLIBAR);

//  Serial.print("Pressure = ");
//  Serial.print(pressure);
//  Serial.println(" kPa");

  // print the values
//  Serial.print(r);
//  Serial.print(" g = ");
//  Serial.print(g);
//  Serial.print(" b = ");
//  Serial.print(b);
//  Serial.print(" aL = ");
//  Serial.print(aL);  
//
//  Serial.print(" Temperature = ");
//  Serial.print(temperature);
//  Serial.print(" °C");
//  Serial.print(" Humidity = ");
//  Serial.print(humidity);
//  Serial.println(" %");
  Serial.print("AA00,");
  Serial.print(temperature,1);  // temperature, float
  Serial.print(",");
  Serial.print(humidity,1);  // humidity, float
  Serial.print(",");
  Serial.print(int(aL));   // luminosity, int
  Serial.print(",");
  Serial.print(pressure, 1);  // pressure, mbar
  Serial.print(",");
  Serial.print(float(r*100.0/(r+g+b)), 1);  // r ratio
  Serial.print(",");
  Serial.print(float(g*100.0/(r+g+b)), 1);  // g ratio
  Serial.print(",");
  Serial.println(float(b*100.0/(r+g+b)), 1);  // b ratio
  
  delay(3000);
}

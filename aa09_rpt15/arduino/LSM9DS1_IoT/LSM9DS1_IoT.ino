#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(9600);   // 19200
  while (!Serial);

  if (!IMU.begin()) { // IMU센서를 초기화합니다. 초기화중 문제가 발생하면 오류를 발생시킵니다.
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

}

float aX, aY, aZ, gX, gY, gZ, mX, mY, mZ;

void loop() {
  
  delay(500);
  // 가속도, 자이로, 지자기 센서의 값이 모두 정상 출력되면 데이터 수집 시작.
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable() && IMU.magneticFieldAvailable()) { 
    // read the acceleration, gyroscope, and magnetic data
    IMU.readAcceleration(aX, aY, aZ);
    IMU.readGyroscope(gX, gY, gZ);
    IMU.readMagneticField(mX, mY, mZ);
    
    // Serial.print("AA09,");   // Change to your ID
    Serial.print(aX);
    Serial.print(',');
    Serial.print(aY);
    Serial.print(',');
    Serial.print(aZ);
    Serial.print(',');
    Serial.print(gX);
    Serial.print(',');
    Serial.print(gY);
    Serial.print(',');
    Serial.print(gZ);
    Serial.print(',');
    Serial.print(mX);
    Serial.print(',');
    Serial.print(mY);
    Serial.print(',');
    Serial.println(mZ);    
  }
}

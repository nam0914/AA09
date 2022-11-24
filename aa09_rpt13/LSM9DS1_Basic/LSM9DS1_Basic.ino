#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);  // 직렬통신 연결될 때 까지 대기
  Serial.println("Started");
  if (!IMU.begin()) { // IMU센서를 초기화합니다. 초기화중 문제가 발생하면 오류를 발생시킵니다.
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}
float ax, ay, az; // 가속도 센서의 XYZ값을 저장할 변수입니다.
float gx, gy, gz; // 자이로 센서의 XYZ값을 저장할 변수입니다.
float mx, my, mz; // 지자기 센서의 XYZ값을 저장할 변수입니다.

void loop() {
  delay(500);
  if (IMU.accelerationAvailable()) { // 가속도 센서의 값을 출력합니다.
    IMU.readAcceleration(ax, ay, az); // x, y, z에 각 축별 데이터를 넣습니다.
    //Serial.print("ACC 센서 - ");
    Serial.print(ax);
    Serial.print(',');
    Serial.print(ay);
    Serial.print(',');
    Serial.print(az);
    //Serial.print(" G's");
    Serial.print(',');
  }

  if (IMU.gyroscopeAvailable()) { // 자이로 센서의 값을 출력합니다.
    IMU.readGyroscope(gx, gy, gz);
    //Serial.print("GYRO 센서 - ");
    Serial.print(gx);
    Serial.print(',');
    Serial.print(gy);
    Serial.print(',');
    Serial.print(gz);
   // Serial.print(" degrees/second");
    Serial.print(',');
  }
  
  if (IMU.magneticFieldAvailable()) { // 지자기 센서의 값을 출력합니다.
    IMU.readMagneticField(mx, my, mz);
   // Serial.print("MAG 센서 - ");
    Serial.print(mx);
    Serial.print(',');
    Serial.print(my);
    Serial.print(',');
    Serial.print(mz);
    //Serial.println(" uT");
  }
    Serial.println();
}

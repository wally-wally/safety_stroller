#include <SoftwareSerial.h> // 블루투스 통신을 위한 헤더파일 선언
#include "Wire.h" // I2C통신을 위한 헤더파일 선언
#include "I2Cdev.h" // GY-521(MPU6050)의 통신을 위한 헤더파일 선언
#include "MPU6050.h" // 자이로 센서 동작을 위한 헤더파일 선언
#include "Servo.h" // 서보모터 동작을 위한 헤더파일 선언

#define newLED 11 
#define okLED 12 
#define oldLED 13 
 
MPU6050 mpu; // MPU6050을 제어하기 위해 mpu라는 MPU6050의 객체를 선언함
 
int16_t ax, ay, az; // 16비트 정수 자료형 으로 ax, ay, az 변수 선언
int16_t gx, gy, gz; // 16비트 정수 자료형 으로 gx, gy, gz 변수 선언

Servo myservo; // 브레이크 기능 동작을 위한 서보모터의 Servo 객체 선언
Servo myservo2; // 잠금 기능 동작을 위한 서보모터의 Servo 객체 선언
 
int val; // GY-521로 측정한 각도값 변수 선언
int first_angle = 0; // 브레이크 기능과 잠금 기능으로 사용되는 서보모터의 각도 초기값 선언

int trig = 6; // HC-SR04 trig핀 번호 선언(6번 핀)
int echo = 7; // HC-SR04 echo핀 번호 선언(7번 핀)
int buzzer = 8; // 피에조 부저 핀 번호 선언(8번 핀)
float duration; // 거리 측정을 위한 duration 변수 선언
float distance; // 거리 측정 값 distance 변수 선언

int stat = 0; // 벨트 잠금상태 확인(벨트 잠그면 0, 벨트 안 잠그면 1로 입력됨)
int belt_switch = 5; // 안전벨트의 ON/OFF 입력이 들어갈 핀(5번 핀)
int lock_pin = 10; // 잠금 기능을 위한 서보모터의 제어선 연결 핀(10번 핀)

int analogValue = 0;
float voltage = 0;
int ledDelay = 500; 

SoftwareSerial mySerial(2,3);

void setup(){
  Wire.begin();
  pinMode(belt_switch, INPUT_PULLUP); // 5번 핀의 내부 풀업 저항 사용
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(lock_pin,OUTPUT);
  pinMode(newLED, OUTPUT);
  pinMode(okLED, OUTPUT);
  pinMode(oldLED, OUTPUT); // LED의 핀모드를 OUTPUT으로 설정
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
  Serial.println("Hello World!");
  Serial.println("Initialize MPU");
  mpu.initialize(); // MPU6050을 사용하기 위해 모드를 설정함
  Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");
  myservo.attach(9); // 브레이크 기능 서보모터 9번 핀 설정
  myservo2.attach(lock_pin); // 잠금 기능 서보모터 10번 핀 설정
  mySerial.begin(9600);
  myservo.write(first_angle); // 브레이크 기능 서보모터의 초기 각도(0도) 설정
  myservo2.write(first_angle); // 잠금 기능 서보모터의 초기 각도(0도) 설정
}

int mode = 0; // 어플에서 MCU로 C, E, F 문자를 전송했을 때 받는 새로운 변수 선언(0으로 초기값 설정)

void loop(){
  digitalWrite(trig,HIGH);
  delay(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  distance = (duration/29)/2; // 초음파 거리 측정 센서(HC-SR04)와 관련된 수식 및 코드

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //MPU6050에서 가속도 센서 값과 자이로 센서 값의 정보를 받아와서 변수에 저장
  val = map(ay, -17000, 17000, 0, 179); // 센서에서 받아온 값을 0부터 179의 범위 내로 변환하여 val변수에 저장한다.  
  analogValue = analogRead(0);
  voltage = (((float)analogValue) / 1024.0 ) * 5.0;

  stat = digitalRead(belt_switch);
  
  Serial.print("Distance :");
  Serial.print(distance);
  Serial.print("cm");
  Serial.print("\t|\t");
  Serial.print("Angle :");
  Serial.print(val);
  Serial.print("degree");
  Serial.print("\t|\t");
  Serial.print("Voltage :");
  Serial.print(voltage); // A0핀에 들어오는 값을 측정하여 이 값을 전압값으로 바꿔줍니다.
  Serial.print("V");
  Serial.print("\t|\t");
  Serial.print("Belt Status : ");
  Serial.println(stat);

  if(voltage >= 2.5){ // 전압값이 2.5이상일 경우 배터리잔량 충분상태(녹색 LED ON)
    digitalWrite(newLED, HIGH);
    delay(ledDelay);
    digitalWrite(newLED, LOW);
  }
  else if(voltage < 2.5 && voltage >= 2.0){ // 전압값이 2.0이상 2.5미만일 경우 배터리잔량 중간상태(파란색 LED ON)
    digitalWrite(okLED, HIGH);
    delay(ledDelay);
    digitalWrite(okLED, LOW);
  }
  else if(voltage < 2.0){ // 전압값이 2.0미만일 경우 배터리 거의 다 쓴 상태(빨간색 LED ON)
    digitalWrite(oldLED, HIGH);
    delay(ledDelay);
    digitalWrite(oldLED, LOW);
  }  
  
  if(mySerial.available()){
    char in_data;
    in_data=mySerial.read();
     Serial.print("Receive Data : ");
     Serial.println(in_data);
      switch(in_data){   
       case 'A' : // 잠금 기능 ON(벨트 잠금 상태에 따라 서보모터 회전각도 설정)
        myservo2.write(first_angle+30);
       break;
      
       case 'B' : // 잠금 기능 OFF(서보모터 각도 0도로 무조건 설정)
       if(stat == HIGH){
        myservo2.write(first_angle+30);
       }
       else{
        myservo2.write(first_angle);
       }
       break; 

       case 'C': // 브레이크 기능 ON(Measure_Angle 함수 호출)
        mode=in_data;
        myservo.attach(9);
       break;

       case 'D': // 브레이크 기능 OFF(서보모터의 연결 해제)
        mode=in_data;
        myservo.write(first_angle);
       break;

       case 'E' : // 분실방지 기능 ON(Measure_Distance 함수 호출)
        mode=in_data;
       break; 
     
       case 'F' : // 분실방지 기능 OFF(Sound_OFF 함수 호출)
        mode=in_data;
       break;
      }
  }
  if(mode == 'C') Measure_Angle();
  if(mode == 'E') Measure_Distance();
  if(mode == 'F') Sound_OFF();
}

void Measure_Angle(){
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  val = map(ay, -17000, 17000, 0, 179);
    Serial.print("Degree : ");
    Serial.print(val);
    Serial.println("[degree]");
    delay(100);
     if(val>=78){
      myservo.write(first_angle+42);
      }
     else{
      myservo.write(first_angle);
      }
     delay(100);
    return;
 }

 void Measure_Distance(){
  digitalWrite(trig,HIGH);
  delay(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  distance = (duration/29)/2; // 초음파 거리 측정 센서(HC-SR04)와 관련된 수식 및 코드
    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.println("[cm]");
    delay(100);
    if(distance>=80){  
         tone(buzzer,1000,100);
         delay(100);
         tone(buzzer,1000,100);
         delay(100);       
        }
     else{ ; }
   delay(100);
 }

 void Sound_OFF(){
    noTone(buzzer);
    delay(100);
 }

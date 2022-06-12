#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
int vibr_pin = 3;
float x1 , x2 , y1 , y2 , z1 , z2 , x3 ,y3 ,z3, acc1 , acc2 , acc3;
int val1 ,val2 , val3;

void setup() {
  pinMode(vibr_pin , INPUT);
  Serial.begin(9600);
  if(!accel.begin())
   {
      Serial.println("No ADXL345 sensor detected.");
      while(1);
   }

}

void loop() {
  sensors_event_t event; 
  accel.getEvent(&event);
  
  x1 = event.acceleration.x;
  y1 = event.acceleration.y;
  z1 = event.acceleration.z;
  acc1 = measure_acc(x1 , y1);
  val1 = digitalRead(vibr_pin);

  delay(2000);

  x2 = event.acceleration.x;
  y2 = event.acceleration.y;
  z2 = event.acceleration.z;
  acc2 = measure_acc(x2 , y2);
  val2 = digitalRead(vibr_pin);

  if( abs(acc1 - acc2) >= 1.3 || abs(z1 - z2) > 1 || abs(val1-val2) > 1000){
    //accident might have occured
    delay(10000);
    //check after 10 seconds
    x3 = event.acceleration.x;
    y3 = event.acceleration.y;
    z3 = event.acceleration.z;
    acc3 = measure_acc(x3 , y3);

    if(val3 == 0 || val3>1000 || abs(acc3) > 1.3 || abs(acc3) < 0.2 ){
      Serial.println("AAAAHHH!!!!!");
      }
    }
}

float measure_acc(float a , float b) {
    float acc = sqrt((a * a) + (b * b));
    return acc;
  }

/*Motors */
int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

int ENA_pin_1 = 9;
int ENA_pin_2 = 10;
int speed_EN_1 = 50;
int speed_EN_2 = 58;
int speed_new = 1;

unsigned long level_time= 0;
unsigned long time_go_right = 275;
unsigned long myMeter = 2500; //1 meter
unsigned long myMeter_first = 3000; //1 meter

/*IR Sensors */
int pushButton_L = 7; //L sensor
int pushButton_R = 13; //R sensor 

/* PID CONTROL */
float Kp = 0;
float Ki = 0;
float Kd = 0;
int P;
int I; 
int D; 

void setup() 
{
  Serial.begin(9600);   
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT); 
  pinMode(ENA_pin_1, OUTPUT);
  pinMode(ENA_pin_2, OUTPUT);
  pinMode(pushButton_L, INPUT); //L sensor
  pinMode(pushButton_R, INPUT); //R sensor
}

void go_forward(int pos_1 = HIGH, int pos_2 = LOW) { 
  //clockwise + clockwise, 
  digitalWrite(motor1pin1, pos_1);
  digitalWrite(motor1pin2, pos_2);
  
  digitalWrite(motor2pin1, pos_1);
  digitalWrite(motor2pin2, pos_2);
//  delay(time_delay);
}

void go_back(int pos_1 = HIGH, int pos_2 = LOW) {
  //anti-clockwise + anti-clockwise
  go_forward(pos_2, pos_1);
}

void go_right(int pos_1 = LOW, int pos_2 = HIGH) {
  analogWrite(ENA_pin_1, speed_new);
  analogWrite(ENA_pin_2, speed_new);

  //clockwise + anti-clockwise
  digitalWrite(motor1pin1, pos_1);
  digitalWrite(motor1pin2, pos_2);
  
  digitalWrite(motor2pin1, pos_2);
  digitalWrite(motor2pin2, pos_1);
//  delay(3000);
}

void stop_func(int pos_1 = LOW, int pos_2 = HIGH) {
  digitalWrite(motor1pin1, pos_1); //added
  digitalWrite(motor1pin2, pos_1);
  digitalWrite(motor2pin1, pos_1);
  digitalWrite(motor2pin2, pos_1);//add-end
  analogWrite(ENA_pin_1, 0);
  analogWrite(ENA_pin_2, 0);
}

void go_left(int pos_1 = LOW, int pos_2 = HIGH) {
  //anti-clockwise + clockwise
  go_right(pos_2, pos_1);
}

void go_forward_right(unsigned long level_time) {
  while (millis() < myMeter + level_time) {
    Serial.println("FORWARD");
    go_forward();
  }
  
  while(millis() < myMeter + time_go_right + level_time) {
    Serial.println("RIGHT");
    go_right();
  }
}
/***************************************************************/

void loop() 
{

analogWrite(ENA_pin_1, speed_new);
  analogWrite(ENA_pin_2, speed_new);

   int color = 0; // tracking white(0) , black(1) color
   
   if( (digitalRead(pushButton_L) == color) && (digitalRead(pushButton_R) == color)) {
    go_forward();
    Serial.println("FORWARD");
   }
   if( (digitalRead(pushButton_L) == color) && (digitalRead(pushButton_R) != color)) { 
     go_left();
      Serial.println("LEFT");
   }  
   if( (digitalRead(pushButton_L) != color) && (digitalRead(pushButton_R) == color)) { 
     go_right();
      Serial.println("RIGHT");
   }
   if( (digitalRead(pushButton_L) != color) && (digitalRead(pushButton_R) != color)) { 
      go_back();
       Serial.println("BACK");
    }
}

/*****************************************************************************************
PID control 
Proportional = error
Integral = I + error 
Derivative = current error = last error 
error = set point - position 

*/
void PID_control() {
  uint16_t position = qtr.readLineBlack(sensorValues); //read current position - I THINK WE NEED ENCODER
  int error = 3500 - position; //3500 is the ideal position (the centre)

  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;
  int motorspeed = P*Kp + I*Ki + D*Kd; //calculate the correction
                                       //needed to be applied to the speed
  
  int motorspeeda = basespeeda + motorspeed;
  int motorspeedb = basespeedb - motorspeed;
  
  if (motorspeeda > maxspeeda) {
    motorspeeda = maxspeeda;
  }
  if (motorspeedb > maxspeedb) {
    motorspeedb = maxspeedb;
  }
  if (motorspeeda < 0) {
    motorspeeda = 0;
  }
  if (motorspeedb < 0) {
    motorspeedb = 0;
  } 
  forward_brake(motorspeeda, motorspeedb);
}

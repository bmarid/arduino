int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

int ENA_pin_1 = 9;
int ENA_pin_2 = 10;
int speed_EN_1 = 50;
int speed_EN_2 = 58;

unsigned long level_time= 0;

unsigned long time_go_right = 275;
unsigned long myMeter = 2500; //1 meter
unsigned long myMeter_first = 3000; //1 meter


int pushButton_L = 7; //L sensor
int pushButton_R = 13; //R sensor 


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

void loop() 
{
//  unsigned long currentMillis = millis();
  delay(2000);  
  analogWrite(ENA_pin_1, speed_EN_1);
  analogWrite(ENA_pin_2, speed_EN_2);

  if(digitalRead(pushButton_R)==HIGH && digitalRead(pushButton_L)==HIGH)
  {stop_func();} 
  
  else if(digitalRead(pushButton_R)==LOW && digitalRead(pushButton_L)==LOW)
  {go_forward();}

  else if(digitalRead(pushButton_R)==LOW && digitalRead(pushButton_L)==HIGH)
  {go_right();}

   else if(digitalRead(pushButton_R)==HIGH && digitalRead(pushButton_L)==LOW)
  {go_left();}

 // unsigned long start_time = millis();
 //1st
/*  while (millis() - start_time < myMeter) {
    Serial.println("1 FORWARD");
    Serial.println(millis());
    go_forward();
  }
  
  while(millis() - start_time  < myMeter + time_go_right) {
    Serial.println("1 RIGHT");
    go_right();
  }

  // read the input pin for encoder:
  int buttonState = digitalRead(pushButton);
  // print out the state of the encoder:
  Serial.println(buttonState);
  delay(1);  
  
  //2nd
  /*level_time = myMeter + time_go_right; //time of go_forward+go_right
  while (millis() - start_time < myMeter + level_time) {
     Serial.println("2 FORWARD");
    go_forward();
  }

  while(millis() - start_time < myMeter + time_go_right + level_time) {
    Serial.println("2 RIGHT");
    go_right();
  }

  //3rd
  level_time = myMeter + time_go_right; //time of go_forward+go_right
  level_time = level_time * 2;
  while (millis() - start_time < myMeter + level_time) {
     Serial.println("3 FORWARD");
    go_forward();
  }

  while(millis() - start_time < myMeter + time_go_right + level_time) {
    Serial.println("3 RIGHT");
    go_right();
  }
  
  //4th
  level_time = myMeter + time_go_right; //time of go_forward+go_right
  level_time = level_time * 3;
  while (millis() - start_time < myMeter + level_time) {
     Serial.println("4 FORWARD");
    go_forward();
  }

  while(millis() - start_time < myMeter + time_go_right + level_time) {
    Serial.println("4 RIGHT");
    go_right();
  }
  */
  
//  
//  while(millis()){
//    for(int i=0; i < 4; i++) {
//      level_time = myMeter + time_go_right; //time of go_forward+go_right
//      level_time = level_time * i;
//      go_forward_right(level_time);
//    }
//  }
   
  //encoder
  
//  delay(time_delay);
//  go_right();
//  delay(time_delay);
//  go_back();
//  delay(time_delay);
//  go_left();
//  delay(time_delay); 
}

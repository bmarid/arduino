//1st motor
int motor1pin1 = 2;
int motor1pin2 = 3;
//2nd motor
int motor2pin1 = 4;
int motor2pin2 = 5;

int ENA_pin_1 = 9;
int ENA_pin_2 = 10;

int speed_EN_1 = 50;
int speed_EN_2 = 58;

unsigned long level_time= 0;

unsigned long time_go_right = 275; //time for rotation to the right, 90 degree
unsigned long myMeter = 2500; //time to go 1 meter

void setup() {
  Serial.begin(9600);   
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT); 
  pinMode(ENA_pin_1, OUTPUT);
  pinMode(ENA_pin_2, OUTPUT);
}

void go_forward(int pos_1 = HIGH, int pos_2 = LOW) { 
  //clockwise + clockwise, 
  digitalWrite(motor1pin1, pos_1);
  digitalWrite(motor1pin2, pos_2);
  
  digitalWrite(motor2pin1, pos_1);
  digitalWrite(motor2pin2, pos_2);
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
}

void go_left(int pos_1 = LOW, int pos_2 = HIGH) {
  //anti-clockwise + clockwise
  go_right(pos_2, pos_1);
}

// future optimisation
//void go_forward_right(unsigned long start_time, unsigned long level_time) {
//  while (millis() - start_time < myMeter + level_time) {
//    Serial.println("FORWARD");
//    go_forward();
//  }
//
//  while(millis() - start_time < myMeter + time_go_right + level_time) {
//    Serial.println("RIGHT");
//    go_right();
//  }
//}

void loop() {
  // time to connect a cabel to battery
  delay(2000);  
  analogWrite(ENA_pin_1, speed_EN_1);
  analogWrite(ENA_pin_2, speed_EN_2);

  unsigned long start_time = millis();
 //1st
  while (millis() - start_time < myMeter) {
    Serial.println("1 FORWARD");
    Serial.println(millis());
    go_forward();
  }
  
  while(millis() - start_time  < myMeter + time_go_right) {
    Serial.println("1 RIGHT");
    go_right();
  }
  
  //2nd
  level_time = myMeter + time_go_right; //time of go_forward+go_right
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
  
}

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

int pushButton = 7;

unsigned long level_time= 0;
unsigned long time_go_right = 275; //time for rotation to the right, 90 degree
unsigned long myMeter = 2500; //time to go 1 meter

void setup() {
  Serial.begin(9600); 
  pinMode(pushButton, INPUT);
     
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

int counter = 0;

void loop() {
  // time to connect a cabel to battery
  delay(1000);  
  
  analogWrite(ENA_pin_1, speed_EN_1);
  analogWrite(ENA_pin_2, speed_EN_2);
  
  int buttonState = digitalRead(pushButton);
  Serial.println(buttonState);
  
  if(buttonState == 1){
    counter = counter + 1;
    Serial.println("counter = ");
    Serial.println(counter);
   }
   
   if(counter < 5) {
    Serial.println("Go forward");
    go_forward();
   } else {
    Serial.println("Go back");
    go_right();
    }

  
  
}

// define motors
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

// define IR sensors 
int pushButton_L = 7; //L sensor
int pushButton_R = 13; //R sensor 

// define constants for the PID controller
const float kp = 1.0;
const float ki = 0.1;
const float kd = 0.01;

// define variables to store the current and previous error values
float error = 0.0;
float prevError = 0.0;

// define variables to store the current and previous time values
unsigned long curTime = 0;
unsigned long prevTime = 0;

// define variables to store the current and previous output values
float curOutput = 0.0;
float prevOutput = 0.0;

// initialize motors and sensors
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

// forward function 
void go_forward(int pos_1 = HIGH, int pos_2 = LOW) { 
  //clockwise + clockwise, 
  digitalWrite(motor1pin1, pos_1);
  digitalWrite(motor1pin2, pos_2);
  
  digitalWrite(motor2pin1, pos_1);
  digitalWrite(motor2pin2, pos_2);
//  delay(time_delay);
}

// back function
void go_back(int pos_1 = HIGH, int pos_2 = LOW) {
  //anti-clockwise + anti-clockwise
  go_forward(pos_2, pos_1);
}

// right function 
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

//stop function 
void stop_func(int pos_1 = LOW, int pos_2 = HIGH) {
  digitalWrite(motor1pin1, pos_1); //added
  digitalWrite(motor1pin2, pos_1);
  digitalWrite(motor2pin1, pos_1);
  digitalWrite(motor2pin2, pos_1);//add-end
  analogWrite(ENA_pin_1, 0);
  analogWrite(ENA_pin_2, 0);
}

//left function 
void go_left(int pos_1 = LOW, int pos_2 = HIGH) {
  //anti-clockwise + clockwise
  go_right(pos_2, pos_1);
}

//travelling by millis 
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

void loop() {
  // read the sensor values and calculate the error value
  float sensorLeft = readSensor((pushButton_L);
  float sensorRight = readSensor(pushButton_R);
  error = sensorRight - sensorLeft;

  // calculate the time elapsed since the last iteration
  curTime = millis();
  float dt = curTime - prevTime;

  // calculate the proportional, integral, and derivative terms
  float pTerm = kp * error;
  float iTerm = ki * (error + prevError) * dt / 2.0;
  float dTerm = kd * (error - prevError) / dt;

  // calculate the output value
  curOutput = pTerm + iTerm + dTerm;

  // adjust the robot's movement based on the output value
  setMotors(curOutput, curOutput);

  // update the previous error, time, and output values
  prevError = error;
  prevTime = curTime;
  prevOutput = curOutput;
}
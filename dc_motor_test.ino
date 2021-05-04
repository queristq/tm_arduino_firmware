int m1_c1 = 3;
int m1_c2 = 5;
int m2_c1 = 6;
int m2_c2 = 9;

int incomingByte =5;
  
void setup() {
  // pin mode setup
  pinMode(m1_c1, OUTPUT);
  pinMode(m1_c2, OUTPUT);
  pinMode(m2_c1, OUTPUT);
  pinMode(m2_c2, OUTPUT);

  // init of the pin outputs
  digitalWrite(m1_c1, LOW);
  digitalWrite(m1_c2, LOW);
  digitalWrite(m2_c1, LOW);
  digitalWrite(m2_c2, LOW);  

  Serial.begin(57600);           // set up Serial library at 9600 bps
  Serial.println("Hello Arduino Code is starting");  // prints hello with ending line break 
}

void RightWheelVel(int v)  // v needs to be between -255 to 255
{
  if (v>0)
  {
    digitalWrite(m1_c1, LOW); 
    analogWrite(m1_c2, v);
  }
  else
  {
    analogWrite(m1_c1, -v);  
    digitalWrite(m1_c2, LOW); 
  }
}

void LeftWheelVel(int v)  // v needs to be between -255 to 255
{
  if (v>0)
  {
    analogWrite(m2_c1, v);
    digitalWrite(m2_c2, LOW); 
  }
  else
  {
    digitalWrite(m2_c1, LOW); 
    analogWrite(m2_c2, -v);  
  }   
}

void WheelVel(int right_v, int left_v)
{
  RightWheelVel(right_v);
  LeftWheelVel(left_v);
}

void loop() {
  int i = 0;
  float d = 1.0;
  int left_v = 0;
  int right_v = 0;
  int cmd = incomingByte - 48;
  
  switch (cmd) 
  {
    case 7:    // your hand is on the sensor
      left_v = 50;
      right_v = 255;
      break;
    case 8:    // your hand is on the sensor
      left_v = 255;
      right_v = 255;
      break;
    case 9:    // your hand is on the sensor
      left_v = 255;
      right_v = 50;
      break;
    case 4:    // your hand is on the sensor
      left_v = -255;
      right_v = 255;
      break;
    case 5:    // your hand is on the sensor
      left_v = 0;
      right_v = 0;
      break;
    case 6:    // your hand is on the sensor
      left_v = 255;
      right_v = -255;
      break;
    case 1:    // your hand is on the sensor
      left_v = -50;
      right_v = -255;
      break;
    case 2:    // your hand is on the sensor
      left_v = -255;
      right_v = -255;
      break;
    case 3:    // your hand is on the sensor
      left_v = -255;
      right_v = -50;
      break;
  }

  WheelVel(left_v, right_v);
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}

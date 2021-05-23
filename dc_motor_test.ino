int m1_d = 6;
int m1_w = 9;
int m2_d = 3;
int m2_w = 5;

int incomingByte =5;
int left_v = 0;
int right_v = 0;
  
void setup() {
  // pin mode setup
  pinMode(m1_d, OUTPUT);
  pinMode(m1_w, OUTPUT);
  pinMode(m2_d, OUTPUT);
  pinMode(m2_w, OUTPUT);

  // init of the pin outputs
  digitalWrite(m1_d, LOW);
  digitalWrite(m1_w, LOW);
  digitalWrite(m2_d, LOW);
  digitalWrite(m2_w, LOW);  

  Serial.begin(57600);           // set up Serial library at 9600 bps
  Serial.println("Hello Arduino Code is starting");  // prints hello with ending line break 
}

void RightWheelVel(int v)  // v needs to be between -255 to 255
{
  if (v>0)
  {
    digitalWrite(m2_d, LOW); 
    analogWrite(m2_w, v);
  }
  else
  {
    digitalWrite(m2_d, HIGH); 
    analogWrite(m2_w, -v);
  }
}

void LeftWheelVel(int v)  // v needs to be between -255 to 255
{
  if (v>0)
  {
    digitalWrite(m1_d, HIGH); 
    analogWrite(m1_w, v);
  }
  else
  {
    digitalWrite(m1_d, LOW); 
    analogWrite(m1_w, -v);
  }
}

void WheelVel(int right_v, int left_v)
{
  RightWheelVel(right_v);
  LeftWheelVel(left_v);
}

void loop() {
  int i = 0;
  int d = 4;

  int cmd = incomingByte - 48;
  
  switch (cmd) 
  {
    case 7:    // your hand is on the sensor
      right_v++;
      left_v = right_v * 0.3;
      break;
    case 8:    // your hand is on the sensor
      left_v++;
      right_v++;
      break;
    case 9:    // your hand is on the sensor
      left_v++;
      right_v = left_v*0.3;
      break;
    case 4:    // your hand is on the sensor
      left_v--;
      right_v++;
      break;
    case 5:    // your hand is on the sensor
      if(left_v>0) left_v--;
      else if (left_v<0) left_v++;
      else left_v = 0;
      if(right_v>0) right_v--;
      else if (right_v<0) right_v++;
      else right_v = 0;
      break;
    case 6:    // your hand is on the sensor
      left_v++;
      right_v--;
      break;
    case 1:    // your hand is on the sensor
      right_v--;
      left_v = right_v*0.3;
      break;
    case 2:    // your hand is on the sensor
      left_v--;
      right_v--;
      break;
    case 3:    // your hand is on the sensor
      left_v--;
      right_v=left_v*0.3;
      break;
  }
  if(left_v >254) left_v = 254;
  if(right_v > 254) right_v = 254;

  if(left_v < -254) left_v = -254;
  if(right_v < -254) right_v = -254;

  WheelVel(left_v, right_v);
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }

  delay(d);
}

//26 AIRSERVO   SETUPDONE access AirServo.write(AngleVlue); // 0 CLOSE 90 OPEN
//27 GASSERVO   SETUPDONE access GasServo.write(AngleVlue);
//AIR FLOW   
//39 GAS FLOW   SETUPDONE access flowrate();
//34 VOLTAGESENSOR SETUPDONE access readVoltage();
//35 CURRENTSENSOR SETUPDONE access readCurrent();
//33 STIRLINGRELAY SETUPDONE access digitalWrite(PumpRelay, HIGH); digitalWrite(PumpRelay, LOW); 
//32 PUMPRELAY     SETUPDONE access digitalWrite(StirlingRelay, HIGH); digitalWrite(StirlingRelay, LOW);
//25 IGNITERELAY   SETUPDONE access digitalWrite(IgniteRelay, HIGH); digitalWrite(IgniteRelay, LOW);   
//14 EMERGENCY     SETUPDONE access digitalRead(EMERGENCY);   

#include <ESP32Servo.h>
//servo
static const int AirServoPin = 26; 
static const int GasServoPin = 27; 
bool pumpActive = false;
bool gasActive = false;
bool outOfGas = false;
int airon = 90;
int airoff= 0;
int gason=  90;
int gasoff= 0;
 

//flow
const int AirFlow = 39;
double flow; //Liters of passing water volume
unsigned long pulse_freq;

//current voltage
const int voltagePin = 34;     // Analog pin for voltage measurement
const int currentPin = 35;    // Analog pin for current measurement
float voltage = 0;
float current = 0;

//RELAYS
const int PumpRelay = 32;     //digital pin dont forget common grounds
const int StirlingRelay = 33; //digital pin dont forget common grounds
const int IgniteRelay = 25;    //digital pin dont forget common grounds

// CONTROL VARIABLES
int TriggerOffTemperature = 50;
int StirlingStartTemperature = 150;          
int HalfLimitTemperature = 300;          
int FullLimitTemperature = 400;   
double flowForOutOfGas = 0.1;       

//TO SEND VARIABLES          
//int S52=0 //AIRFLOW           .      
//int S53=0  //VOLTAGE          .
//int S54=0  //CURRENT          .
//int S55=0  //STIRLING STATUS  . 
//int S56=0  //AIRPUMP  STATUS  .
//int S57=0  //IGNITION STATUS  .
//int S58=0  //GAS VALVE STATUS .
//int S59=0  //GAS AVAILABLE    .
//int S60=0  //AIR VALVE STATUS .
int dataValues[9]={0};       // to be sent serially


//TO RECEIVE VARIABLES
int d[3] = {0};
int tempOut = d[2];             // temp to be read serially
int tempBase = d[0];            // temp to be read serially

//EMERGENCY
const int EMERGENCY_PIN = 14;
volatile bool emergencyActive = false;  // Flag to track emergency state


Servo AirServo;
Servo GasServo;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  // put your setup code here, to run once:
  //SERVOS
  AirServo.attach(AirServoPin);
  GasServo.attach(GasServoPin);
  
  //FLOWSENSORS
  pinMode(AirFlow, INPUT);
  
  //CURRENT VOLTAGE
  pinMode(voltagePin, INPUT);
  pinMode(currentPin, INPUT);

  //RELAYS
  pinMode(PumpRelay, OUTPUT);
  pinMode(StirlingRelay, OUTPUT);
  pinMode(IgniteRelay, OUTPUT);

  //EMERGENCY
  pinMode(EMERGENCY_PIN, INPUT_PULLUP);  // Set EMERGENCY_PIN as input with internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(EMERGENCY_PIN), handleEmergencyInterrupt, CHANGE); 
}

void loop() {

  // Convert array c to string
  String arrayString = "";
  for (int i = 0; i < 9; i++) {
    arrayString += String(dataValues[i]);
      arrayString += ",";
  }

  // Send array string to ESP32 B
  Serial2.println(arrayString);
  Serial.println("sent this array");
  Serial.println(arrayString);

  // Receive array string from ESP32 B
  if (Serial2.available()) {
    String receivedString = Serial2.readStringUntil('\n');
    receivedString.trim();

    char receivedChars[receivedString.length() + 1];
    receivedString.toCharArray(receivedChars, sizeof(receivedChars));

    char* value = strtok(receivedChars, ",");
    int index = 0;
    while (value != NULL && index < 3) {
      d[index++] = atoi(value);
      value = strtok(NULL, ",");
    }
  }

  // Display received array d
  Serial.println("Received Array: ");
  for (int i = 0; i < 3; i++) {
    Serial.print(d[i]);
    Serial.print(" ");
  }

  tempOut = d[2];             // temp to be read serially
  Serial.println("tempout");
  Serial.println(tempOut);
  tempBase = d[0];            // temp to be read serially
  Serial.println("tempbase");
  Serial.println(tempBase);
  delay(100);
  
  while (!emergencyActive && (tempBase!=0)) {
  // NORMAL ON OPERATIONS

  // AIR FLOW ON
  //OPEN AIR VALVE
  if (!pumpActive){
    Serial.println("opening pump valve");
    
  AirServo.write(45);
  delay(500);
  AirServo.write(airon);
  delay(500);
  
  //TURN ON AIR PUMP
  digitalWrite(PumpRelay, HIGH);
  Serial.println("turned on pump");

  pumpActive = true;
  }

  // GAS FLOW ON
 if(gasActive && tempBase>TriggerOffTemperature){
  Serial.println("ignition off");
    digitalWrite(IgniteRelay, LOW);
  }
 
 if (!gasActive && !outOfGas){
  Serial.println("ignition on");
  digitalWrite(IgniteRelay, HIGH);
  GasServo.write(45);
  delay(500);
  GasServo.write(gason);
  delay(500); 
  Serial.println("gas valve open");
  gasActive = true;
 }


  // START STERLING
if(tempOut>StirlingStartTemperature){
  voltage = readVoltage(); 
  current = readCurrent();

  if(voltage<=0){
    Serial.println("strling started");
  digitalWrite(StirlingRelay, HIGH);
  delay(5000);
  digitalWrite(StirlingRelay, LOW);
  delay(5000);  
  }else{
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("Current: ");
  Serial.print(current);
  Serial.println(" A");

      };
    };
    
  //Limit1 reducing to 50%
  if(tempOut>HalfLimitTemperature){
    Serial.println("half limit exhibited");
    GasServo.write(45);
    delay(500);    
    };
    
  //Limit2 turning off gas
   if(tempOut>FullLimitTemperature){
    Serial.println("full limit exhibited");
    GasServo.write(gasoff);
    delay(500);
    gasActive = false;
    };

  //OUT OF GAS
    flowrate(); 
    if((flow <= flowForOutOfGas) && gasActive){
      Serial.println("out of gas");
      GasServo.write(gasoff);
      delay(500);
      outOfGas = true;
      }  

          dataValues[0] = flow*10;                                          //FLOW                   
          dataValues[1] = current*100;                                   //VOLTAGE        
          dataValues[2] = voltage*100;                                   //CURRENT
          dataValues[3] = digitalRead(StirlingRelay) == HIGH ? 5 : 2;    //STIRLING STATUS   
          dataValues[4] = digitalRead(PumpRelay) == HIGH ? 5 : 2;        //AIRPUMP  STATUS  
          dataValues[5] = digitalRead(IgniteRelay) == HIGH ? 5 : 2;      //IGNITION STATUS  
          dataValues[6] = gasActive ? 5 : 2;                             //GAS VALVE STATUS 
          dataValues[7] = outOfGas ? 2 : 5;                              //GAS AVAILABLE    
          dataValues[8] = pumpActive ? 5 : 2;                            //AIR VALVE STATUS 

  
  // SEND AND RECEIVE DATA AFTER EVERY ITTERATION
   Serial.println("non emergency data");
  // Convert array c to string
  String arrayString = "";
  for (int i = 0; i < 9; i++) {
    arrayString += String(dataValues[i]);
      arrayString += ",";
  }

  // Send array string to ESP32 B
  Serial2.println(arrayString);
  Serial.println(arrayString);

  // Receive array string from ESP32 B
  if (Serial2.available()) {
    String receivedString = Serial2.readStringUntil('\n');
    receivedString.trim();

    char receivedChars[receivedString.length() + 1];
    receivedString.toCharArray(receivedChars, sizeof(receivedChars));

    char* value = strtok(receivedChars, ",");
    int index = 0;
    while (value != NULL && index < 3) {
      d[index++] = atoi(value);
      value = strtok(NULL, ",");
    }
  }

  // Display received array d
  Serial.print("Received Array: ");
  for (int i = 0; i < 3; i++) {
    Serial.print(d[i]);
    Serial.print(" ");
  }
  Serial.println();

  tempOut = d[2];             // temp to be read serially
  tempBase = d[0];            // temp to be read serially
  Serial.println("tempout");
  Serial.println(tempOut);
  Serial.println("tempbase");
  Serial.println(tempBase);
  delay(100);

  delay(100);
  };
  
  while (emergencyActive) {
  // EMERGENCY OPERATIONS
  Serial.println("emergency operations");
  //SHUTDOWN GAS VALVE
  GasServo.write(gasoff);
  delay(500);
  gasActive = false;
  
  //COMPLETELY OPEN AIR VALVE
  AirServo.write(airon);
  delay(500);
  
  //TURN ON AIR PUMP
  digitalWrite(PumpRelay, HIGH);
  pumpActive = true;


          flowrate(); 
          dataValues[0] = flow;                                            //FLOW                   
          dataValues[1] = 0;                                               //VOLTAGE        
          dataValues[2] = 0;                                               //CURRENT
          dataValues[3] = digitalRead(StirlingRelay) == HIGH ? 5 : 2;      //STIRLING STATUS   
          dataValues[4] = digitalRead(PumpRelay) == HIGH ? 5 : 2;          //AIRPUMP  STATUS  
          dataValues[5] = digitalRead(IgniteRelay) == HIGH ? 5 : 2;        //IGNITION STATUS  
          dataValues[6] = gasActive ? 5 : 2;                               //GAS VALVE STATUS 
          dataValues[7] = outOfGas ? 5 : 2;                                //GAS AVAILABLE    
          dataValues[8] = pumpActive ? 5 : 2;                              //AIR VALVE STATUS 

  // SEND AND RECEIVE DATA AFTER EVERY ITTERATION

  // Convert array c to string
  String arrayString = "";
  for (int i = 0; i < 9; i++) {
    arrayString += String(dataValues[i]);
      arrayString += ",";
  }

  // Send array string to ESP32 B
  Serial2.println(arrayString);
  Serial.println(arrayString);

  // Receive array string from ESP32 B
  if (Serial2.available()) {
    String receivedString = Serial2.readStringUntil('\n');
    receivedString.trim();

    char receivedChars[receivedString.length() + 1];
    receivedString.toCharArray(receivedChars, sizeof(receivedChars));

    char* value = strtok(receivedChars, ",");
    int index = 0;
    while (value != NULL && index < 3) {
      d[index++] = atoi(value);
      value = strtok(NULL, ",");
    }
  }

  // Display received array d
  Serial.print("Received Array: ");
  for (int i = 0; i < 3; i++) {
    Serial.print(d[i]);
    Serial.print(" ");
  }
  Serial.println();

  tempOut = d[2];             // temp to be read serially
  tempBase = d[0];            // temp to be read serially
  Serial.println("tempout");
  Serial.println(tempOut);
  Serial.println("tempbase");
  Serial.println(tempBase);
  delay(100);

  delay(100);
  delay(100);
  }; 
delay(100);
}

void handleEmergencyInterrupt() {
  // Interrupt handler to set emergencyActive flag
  emergencyActive = digitalRead(EMERGENCY_PIN) == LOW;  // Set emergencyActive based on the state of the emergency button
}


void flowrate(){
    int pulse_freq = analogRead(AirFlow); // Read the sensor value
    flow = .00225 * pulse_freq;
    Serial.print(flow, DEC);
    Serial.println("L");
    delay(500);
  }


float readVoltage() {
  int rawValue = analogRead(voltagePin);  // Read raw ADC value
  float voltage = rawValue * (3.3 / 4095);  // Convert raw value to voltage (assuming 3.3V reference)
  return voltage;
}

float readCurrent() {
  int rawValue = analogRead(currentPin);  // Read raw ADC value
  float current = rawValue * (3.3 / 4095);  // Convert raw value to current (assuming 3.3V reference)
  return current;
}

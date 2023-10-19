// Define digital pins used for controlling demultiplexers
int demuxPin1 = 1;
int demuxPin2 = 2;
int demuxPin3 = 3;
int demuxIn1 = 4;
int demuxIn2 = 5;
int demuxIn3 = 6;

// to store three values from each sensor
int r1 = 0;
int r2 = 0;
int r3 = 0;


// VARIABLES FOR SERIAL MONITOR 
int sensors_start = 1;
int sensor_active = 1;
int sensors_end = 64;

//VARIABLE FOR NUMBER OF MUXES ATTACHED @TESTING RANGE 1-8
int muxes_attached = 8;

void setup() {
  // Set digital pins as outputs
  pinMode(demuxPin1, OUTPUT);
  pinMode(demuxPin2, OUTPUT);
  pinMode(demuxPin3, OUTPUT);
  pinMode(demuxIn1, OUTPUT);
  pinMode(demuxIn2, OUTPUT);
  pinMode(demuxIn3, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  //selecting multiplexer
 for (int i = 0; i < muxes_attached; i++) {
    select_mux(i); // function defined below
    delay(30);
 // selecting pin of selected multiplexer   
 for (int j = 0; j < 8; j++) {
    select_mux_line(j); // function defined below
    delay(30);

    // printing message incrementing to sensor number active
    if (sensor_active == sensors_end) {
    sensor_active = sensors_start; // set the variable to 1
    } else {
      sensor_active++; // increment the variable by one
    }

    Serial.println("MUX NUMBER: ");
    Serial.print(i);
    Serial.println("PIN NUMBER: ");
    Serial.println(j);
    
    Serial.println("READING FROM SENSOR: ")
    Serial.print(sensor_active)
    
    // sensor reading code goes here
    // r1 r2 r3

    // printing the average obtained from the sensors
    Serial.println(average(r1 , r2 , r3));
        
  }       
}

}

void select_mux(int i){
  // Set pins high or low based on binary value
    digitalWrite(demuxPin1, (i & 0x01) ? HIGH : LOW);
    digitalWrite(demuxPin2, (i & 0x02) ? HIGH : LOW);
    digitalWrite(demuxPin3, (i & 0x04) ? HIGH : LOW);
  }

void select_mux_line(int j){
  // Set pins high or low based on binary value
    digitalWrite(demuxIn1, (j & 0x01) ? HIGH : LOW);
    digitalWrite(demuxIn2, (j & 0x02) ? HIGH : LOW);
    digitalWrite(demuxIn3, (j & 0x04) ? HIGH : LOW);
  }

int average(int a, int b, int c){
  // take average of three readings to get most accurate readings from each sensor
  
  int average = (a + b + c) / 3 ;

  return average;
  }
  

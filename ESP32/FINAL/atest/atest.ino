#include <max6675.h>
//#include <cmath>
//
//// Define digital pins used for MUXSELECTION output 34 35 36 39 KUTTA
//int MUXSELECTOR1 = 39;
//int MUXSELECTOR2 = 14; //36;
//int MUXSELECTOR3 = 27;
//
//// Define digital pins used for SENSOR SELECTION output
//int SENSORSELECTOR1 = 32;
//int SENSORSELECTOR2 = 33;
//int SENSORSELECTOR3 = 25; //35;
//int SENSORSELECTOR4 = 26; //34;

// TEMPERATURE
int thermoCLK = 18;
int thermoCS = 5;
int thermoDO = 2;

// Create an instance of the MAX6675 class
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

// Define the array to store temperature readings
int temperatureArray[60];
int currentIndex = 0;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  // Set digital pins as outputs
//  pinMode(MUXSELECTOR1, OUTPUT);
//  pinMode(MUXSELECTOR2, OUTPUT);
//  pinMode(MUXSELECTOR3, OUTPUT);
//  pinMode(SENSORSELECTOR1, OUTPUT);
//  pinMode(SENSORSELECTOR2, OUTPUT);
//  pinMode(SENSORSELECTOR3, OUTPUT);
//  pinMode(SENSORSELECTOR4, OUTPUT);
}

void loop() {
  
//
//  digitalWrite(MUXSELECTOR1, LOW);
//  digitalWrite(MUXSELECTOR2, HIGH);  
//  digitalWrite(MUXSELECTOR3, HIGH);
//     
//
//  digitalWrite(SENSORSELECTOR1, LOW);
//  digitalWrite(SENSORSELECTOR2, LOW);
//  digitalWrite(SENSORSELECTOR3, LOW);
//  digitalWrite(SENSORSELECTOR4, LOW);
//  delay(2000);
//  
//  digitalWrite(SENSORSELECTOR1, HIGH);
//  digitalWrite(SENSORSELECTOR2, HIGH);
//  digitalWrite(SENSORSELECTOR3, HIGH);
//  digitalWrite(SENSORSELECTOR4, HIGH);
//  delay(2000);  
  

  

//  // Loop through all binary values from 0 to 15 (0000 to 1111)
//  for (int i = 0; i < 16; i++) {
//    // Set pins high or low based on binary value
//    digitalWrite(MUXSELECTOR1, (i & 0x01) ? HIGH : LOW);
//    digitalWrite(MUXSELECTOR2, (i & 0x02) ? HIGH : LOW);
//    digitalWrite(MUXSELECTOR3, (i & 0x04) ? HIGH : LOW);
//
//     Loop through all binary values from 0 to 15 (0000 to 1111)
//    for (int j = 0; j < 16; j++) {
//      digitalWrite(SENSORSELECTOR1, (j & 0x01) ? HIGH : LOW);
//      digitalWrite(SENSORSELECTOR2, (j & 0x02) ? HIGH : LOW);
//      digitalWrite(SENSORSELECTOR3, (j & 0x04) ? HIGH : LOW);
//      digitalWrite(SENSORSELECTOR4, (j & 0x08) ? HIGH : LOW);
//      delay(10000);
//    }
//
      // Read temperature from MAX6675
      delay(10000);
//      Serial.println(currentIndex);

      int temperature = thermocouple.readCelsius();
      while(temperature>600){
               Serial.println("over read");
//               Serial.println(temperature);
               temperature=0;
              int temperature = thermocouple.readCelsius();      
              delay(1000);  
        };
//////      if (std::isnan(temperature)) {
//////        temperature = 0.0;
//////      }
//
////
////      // Check if thermocouple is disconnected
////      if (isnan(temperature)) {
//////        Serial.println("Check Thermocouple: ");
//////        Serial.print(currentIndex);
////        temperatureArray[currentIndex] = 0;
////        currentIndex++;
////      } else {
//////        Serial.println("Received Thermocouple: ");
//////        Serial.println(currentIndex);
        Serial.println(temperature);
        delay(2000);
////
////        // Store temperature value in the array
////        temperatureArray[currentIndex] = int(temperature);
////        currentIndex++;
////
////        // Check if array is full
////        if (currentIndex == 60) {
//////          Serial.println("All values received");
////
////          // Convert the array to a string
////          String arrayString;
////          for (int i = 0; i < sizeof(temperatureArray) / sizeof(temperatureArray[0]); i++) {
////            arrayString += String(temperatureArray[i]);
////            if (i < sizeof(temperatureArray) / sizeof(temperatureArray[0]) - 1) {
////              arrayString += ",";
////            }
////          }
////        
////          // Send the array string over serial
////          Serial.println(arrayString);
////        
////          delay(10000);
////
////          // Reset the currentIndex for the next cycle
////          currentIndex = 0;
////        } 
////      }
//    }
//  }
}

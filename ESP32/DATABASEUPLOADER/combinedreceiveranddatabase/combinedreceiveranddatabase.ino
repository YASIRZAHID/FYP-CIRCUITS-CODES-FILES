#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YASIRF19AU17";
const char* password = "asksupervisor";
const char* serverName = "https://fypversionone-asksupervisor-yasirzahid.vercel.app/api/SENDING";

int receivedNumbers[60] = {66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66,  66 ,  66};

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {
  if (Serial.available()) {
    // Read the array string from serial
    String arrayString = Serial.readStringUntil('\n');
    
    // Convert the array string to an array of integers
    int index = 0;
    char* ptr = strtok(const_cast<char*>(arrayString.c_str()), ",");
    while (ptr != NULL && index < sizeof(receivedNumbers) / sizeof(receivedNumbers[0])) {
      receivedNumbers[index++] = atoi(ptr);
      ptr = strtok(NULL, ",");
    }
    
    // Print the received array on Serial Monitor
    for (int i = 0; i < index; i++) {
      Serial.print(receivedNumbers[i]);
      Serial.print(" ");
    }
    Serial.println();
    
    // Send data to the server
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;
      
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/json");
      
      String jsonPayload = "{\"S1\": " + String(receivedNumbers[0]) + ", \"S2\": " + String(receivedNumbers[1]) + ", \"S3\": " + String(receivedNumbers[2]) + ", \"S4\": " + String(receivedNumbers[3]) + ", \"S5\": " + String(receivedNumbers[4]) + ", \"S6\": " + String(receivedNumbers[5]) + ", \"S7\": " + String(receivedNumbers[6]) + ", \"S8\": " + String(receivedNumbers[7]) + ", \"S9\": " + String(receivedNumbers[8]) + ", \"S10\": " + String(receivedNumbers[9]) + ", \"S11\": " + String(receivedNumbers[10]) + ", \"S12\": " + String(receivedNumbers[11]) + ", \"S13\": " + String(receivedNumbers[12]) + ", \"S14\": " + String(receivedNumbers[13]) + ", \"S15\": " + String(receivedNumbers[14]) + ", \"S16\": " + String(receivedNumbers[15]) + ", \"S17\": " + String(receivedNumbers[16]) + ", \"S18\": " + String(receivedNumbers[17]) + ", \"S19\": " + String(receivedNumbers[18]) + ", \"S20\": " + String(receivedNumbers[19]) + ", \"S21\": " + String(receivedNumbers[20]) + ", \"S22\": " + String(receivedNumbers[21]) + ", \"S23\": " + String(receivedNumbers[22]) + ", \"S24\": " + String(receivedNumbers[23]) + ", \"S25\": " + String(receivedNumbers[24]) + ", \"S26\": " + String(receivedNumbers[25]) + ", \"S27\": " + String(receivedNumbers[26]) + ", \"S28\": " + String(receivedNumbers[27]) + ", \"S29\": " + String(receivedNumbers[28]) + ", \"S30\": " + String(receivedNumbers[29]) + ", \"S31\": " + String(receivedNumbers[30]) + ", \"S32\": " + String(receivedNumbers[31]) + ", \"S33\": " + String(receivedNumbers[32]) + ", \"S34\": " + String(receivedNumbers[33]) + ", \"S35\": " + String(receivedNumbers[34]) + ", \"S36\": " + String(receivedNumbers[35]) + ", \"S37\": " + String(receivedNumbers[36]) + ", \"S38\": " + String(receivedNumbers[37]) + ", \"S39\": " + String(receivedNumbers[38]) + ", \"S40\": " + String(receivedNumbers[39]) + ", \"S41\": " + String(receivedNumbers[40]) + ", \"S42\": " + String(receivedNumbers[41]) + ", \"S43\": " + String(receivedNumbers[42]) + ", \"S44\": " + String(receivedNumbers[43]) + ", \"S45\": " + String(receivedNumbers[44]) + ", \"S46\": " + String(receivedNumbers[45]) + ", \"S47\": " + String(receivedNumbers[46]) + ", \"S48\": " + String(receivedNumbers[47]) + ", \"S49\": " + String(receivedNumbers[48]) + ", \"S50\": " + String(receivedNumbers[49]) + ", \"S51\": " + String(receivedNumbers[50]) + ", \"S52\": " + String(receivedNumbers[51]) + ", \"S53\": " + String(receivedNumbers[52]) + ", \"S54\": " + String(receivedNumbers[53]) + ", \"S55\": " + String(receivedNumbers[54]) + ", \"S56\": " + String(receivedNumbers[55]) + ", \"S57\": " + String(receivedNumbers[56]) + ", \"S58\": " + String(receivedNumbers[57]) + ", \"S59\": " + String(receivedNumbers[58]) + ", \"S60\": " + String(receivedNumbers[59]) + "}";
      
      int httpResponseCode = http.POST(jsonPayload);
      
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      } else {
        Serial.println("Error on sending data");
      }
      
      http.end();
    }
  }else{}
}

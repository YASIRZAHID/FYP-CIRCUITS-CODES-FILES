#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YASIRF19AU17";
const char* password = "asksupervisor";
const char* serverName = "https://fypversionone-asksupervisor-yasirzahid.vercel.app/api/SENDING";

int numbers[60] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60};

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  
// received from esp32 A  
  if (Serial.available()) {
    // Read the array string from serial
    String arrayString = Serial.readStringUntil('\n');
    Serial.println("data received");
    Serial.println(arrayString);
    // Convert the array string to an array of integers
    int index = 0;
    char* ptr = strtok(const_cast<char*>(arrayString.c_str()), ",");
    while (ptr != NULL && index < sizeof(numbers) / sizeof(numbers[0])) {
      numbers[index++] = atoi(ptr);
      ptr = strtok(NULL, ",");
    }

    // Print the received array on Serial Monitor
            for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
             if (numbers[i] == 0) {
                numbers[i] = 1;
              }
            }
    Serial.println("converted to array");
    for (int i = 0; i < index; i++) {
      Serial.print(numbers[i]);
      Serial.print(" ");
    }
    Serial.println();

    // Send to esp32C 
    int tosend[3]={numbers[48],numbers[49],numbers[50]};

    // Convert array b to string
    String arrayString2 = "";
    for (int i = 0; i < 3; i++) {
      arrayString2 += String(tosend[i]);
      if (i != 5) {
        arrayString2 += ",";
      }
    }
    
    // Send array string to ESP32 C
    Serial2.println(arrayString2);

    // Receive array string from ESP32 C
    if (Serial2.available()) {
      String receivedString = Serial2.readStringUntil('\n');
      Serial.println("received from c");
      Serial.println(receivedString);
      receivedString.trim();
  
      char receivedChars[receivedString.length() + 1];
      receivedString.toCharArray(receivedChars, sizeof(receivedChars));
  
      char* value = strtok(receivedChars, ",");
      int index = 51;
      while (value != NULL && index < 60) {
        numbers[index++] = atoi(value);
        value = strtok(NULL, ",");
      }
    }


    // Send data to the server
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

        http.begin("https://fypversionone-7jboel1mj-yasirzahid.vercel.app/api/SENDING");  // Replace with your API endpoint URL

         http.addHeader("Content-Type", "application/json");

//      String jsonPayload = "{";
//      for (int i = 0; i < index; i++) {
//        jsonPayload += "\"S" + String(i + 1) + "\": " + String(numbers[i]);
//        if (i < index - 1) {
//          jsonPayload += ",";
//        }
//      }
//      jsonPayload += "}";
//

   String jsonPayload = "{\"S1\": " + String(numbers[0]) + ", \"S2\": " + String(numbers[1]) + ", \"S3\": " + String(numbers[2]) + ", \"S4\": " + String(numbers[3]) + ", \"S5\": " + String(numbers[4]) + ", \"S6\": " + String(numbers[5]) + ", \"S7\": " + String(numbers[6]) + ", \"S8\": " + String(numbers[7]) + ", \"S9\": " + String(numbers[8]) + ", \"S10\": " + String(numbers[9]) + ", \"S11\": " + String(numbers[10]) + ", \"S12\": " + String(numbers[11]) + ", \"S13\": " + String(numbers[12]) + ", \"S14\": " + String(numbers[13]) + ", \"S15\": " + String(numbers[14]) + ", \"S16\": " + String(numbers[15]) + ", \"S17\": " + String(numbers[16]) + ", \"S18\": " + String(numbers[17]) + ", \"S19\": " + String(numbers[18]) + ", \"S20\": " + String(numbers[19]) + ", \"S21\": " + String(numbers[20]) + ", \"S22\": " + String(numbers[21]) + ", \"S23\": " + String(numbers[22]) + ", \"S24\": " + String(numbers[23]) + ", \"S25\": " + String(numbers[24]) + ", \"S26\": " + String(numbers[25]) + ", \"S27\": " + String(numbers[26]) + ", \"S28\": " + String(numbers[27]) + ", \"S29\": " + String(numbers[28]) + ", \"S30\": " + String(numbers[29]) + ", \"S31\": " + String(numbers[30]) + ", \"S32\": " + String(numbers[31]) + ", \"S33\": " + String(numbers[32]) + ", \"S34\": " + String(numbers[33]) + ", \"S35\": " + String(numbers[34]) + ", \"S36\": " + String(numbers[35]) + ", \"S37\": " + String(numbers[36]) + ", \"S38\": " + String(numbers[37]) + ", \"S39\": " + String(numbers[38]) + ", \"S40\": " + String(numbers[39]) + ", \"S41\": " + String(numbers[40]) + ", \"S42\": " + String(numbers[41]) + ", \"S43\": " + String(numbers[42]) + ", \"S44\": " + String(numbers[43]) + ", \"S45\": " + String(numbers[44]) + ", \"S46\": " + String(numbers[45]) + ", \"S47\": " + String(numbers[46]) + ", \"S48\": " + String(numbers[47]) + ", \"S49\": " + String(numbers[48]) + ", \"S50\": " + String(numbers[49]) + ", \"S51\": " + String(numbers[50]) + ", \"S52\": " + String(numbers[51]) + ", \"S53\": " + String(numbers[52]) + ", \"S54\": " + String(numbers[53]) + ", \"S55\": " + String(numbers[54]) + ", \"S56\": " + String(numbers[55]) + ", \"S57\": " + String(numbers[56]) + ", \"S58\": " + String(numbers[57]) + ", \"S59\": " + String(numbers[58]) + ", \"S60\": " + String(numbers[59]) +"}";
  
      Serial.println(jsonPayload);

//      String jsonPayload = {"S1": 0, "S2": 0, "S3": 0, "S4": 0, "S5": 0, "S6": 0, "S7": 0, "S8": 0, "S9": 0, "S10": 0, "S11": 0, "S12": 0, "S13": 0, "S14": 0, "S15": 0, "S16": 0, "S17": 0, "S18": 0, "S19": 0, "S20": 0, "S21": 0, "S22": 0, "S23": 0, "S24": 0, "S25": 0, "S26": 0, "S27": 0, "S28": 0, "S29": 0, "S30": 0, "S31": 0, "S32": 0, "S33": 0, "S34": 0, "S35": 0, "S36": 0, "S37": 0, "S38": 0, "S39": 0, "S40": 0, "S41": 0, "S42": 0, "S43": 0, "S44": 0, "S45": 0, "S46": 0, "S47": 0, "S48": 0, "S49": 0, "S50": 0, "S51": 0, "S52": 0, "S53": 0, "S54": 0, "S55": 0, "S56": 0, "S57": 0, "S58": 0, "S59": 0, "S60": 0};
//      
      int httpResponseCode = http.POST(jsonPayload);

 // Check response
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP response: " + response);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
    }
  }
}

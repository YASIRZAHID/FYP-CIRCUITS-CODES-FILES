#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YASIRF19AU17";
const char* password = "asksupervisor";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Send HTTP POST request
  HTTPClient http;
  http.begin("https://fypversionone-asksupervisor-yasirzahid.vercel.app/api/SENDING");  // Replace with your API endpoint URL

  // Set content type and payload
  http.addHeader("Content-Type", "application/json");

   int numbers[60] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60};

   String jsonPayload = "{\"S1\": " + String(numbers[0]) + ", \"S2\": " + String(numbers[1]) + ", \"S3\": " + String(numbers[2]) + ", \"S4\": " + String(numbers[3]) + ", \"S5\": " + String(numbers[4]) + ", \"S6\": " + String(numbers[5]) + ", \"S7\": " + String(numbers[6]) + ", \"S8\": " + String(numbers[7]) + ", \"S9\": " + String(numbers[8]) + ", \"S10\": " + String(numbers[9]) + ", \"S11\": " + String(numbers[10]) + ", \"S12\": " + String(numbers[11]) + ", \"S13\": " + String(numbers[12]) + ", \"S14\": " + String(numbers[13]) + ", \"S15\": " + String(numbers[14]) + ", \"S16\": " + String(numbers[15]) + ", \"S17\": " + String(numbers[16]) + ", \"S18\": " + String(numbers[17]) + ", \"S19\": " + String(numbers[18]) + ", \"S20\": " + String(numbers[19]) + ", \"S21\": " + String(numbers[20]) + ", \"S22\": " + String(numbers[21]) + ", \"S23\": " + String(numbers[22]) + ", \"S24\": " + String(numbers[23]) + ", \"S25\": " + String(numbers[24]) + ", \"S26\": " + String(numbers[25]) + ", \"S27\": " + String(numbers[26]) + ", \"S28\": " + String(numbers[27]) + ", \"S29\": " + String(numbers[28]) + ", \"S30\": " + String(numbers[29]) + ", \"S31\": " + String(numbers[30]) + ", \"S32\": " + String(numbers[31]) + ", \"S33\": " + String(numbers[32]) + ", \"S34\": " + String(numbers[33]) + ", \"S35\": " + String(numbers[34]) + ", \"S36\": " + String(numbers[35]) + ", \"S37\": " + String(numbers[36]) + ", \"S38\": " + String(numbers[37]) + ", \"S39\": " + String(numbers[38]) + ", \"S40\": " + String(numbers[39]) + ", \"S41\": " + String(numbers[40]) + ", \"S42\": " + String(numbers[41]) + ", \"S43\": " + String(numbers[42]) + ", \"S44\": " + String(numbers[43]) + ", \"S45\": " + String(numbers[44]) + ", \"S46\": " + String(numbers[45]) + ", \"S47\": " + String(numbers[46]) + ", \"S48\": " + String(numbers[47]) + ", \"S49\": " + String(numbers[48]) + ", \"S50\": " + String(numbers[49]) + ", \"S51\": " + String(numbers[50]) + ", \"S52\": " + String(numbers[51]) + ", \"S53\": " + String(numbers[52]) + ", \"S54\": " + String(numbers[53]) + ", \"S55\": " + String(numbers[54]) + ", \"S56\": " + String(numbers[55]) + ", \"S57\": " + String(numbers[56]) + ", \"S58\": " + String(numbers[57]) + ", \"S59\": " + String(numbers[58]) + ", \"S60\": " + String(numbers[59]) +"}";

    Serial.println(jsonPayload);
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

void loop() {
  // Other code or tasks to perform
}

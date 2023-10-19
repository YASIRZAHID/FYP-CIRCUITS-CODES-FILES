int b[12] = {50, 50, 50,0,0,0,0,0,0,0,0,0};

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  // Convert array b to string
  String arrayString = "";
  for (int i = 0; i < 3; i++) {
    arrayString += String(b[i]);
  }

  // Send array string to ESP32 C
  Serial2.println(arrayString);

  // Receive array string from ESP32 C
  if (Serial2.available()) {
    String receivedString = Serial2.readStringUntil('\n');
    receivedString.trim();

    char receivedChars[receivedString.length() + 1];
    receivedString.toCharArray(receivedChars, sizeof(receivedChars));

    char* value = strtok(receivedChars, ",");
    int index = 3;
    while (value != NULL && index < 12) {
      b[index++] = atoi(value);
      value = strtok(NULL, ",");
    }
  }

  // Display received array b
  Serial.print("Received Array: ");
  for (int i = 0; i < 12; i++) {
    Serial.print(b[i]);
    Serial.print(" ");
  }
  Serial.println();

  delay(1000);
}

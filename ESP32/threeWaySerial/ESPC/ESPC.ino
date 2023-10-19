int dataValues[9] = {1,2,3,4,5,6,7,8,9};
int d[3] = {};

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
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

  delay(1000);
}

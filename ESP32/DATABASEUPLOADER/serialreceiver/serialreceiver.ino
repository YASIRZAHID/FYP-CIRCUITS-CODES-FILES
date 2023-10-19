int receivedNumbers[60];

void setup() {
  Serial.begin(9600);
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
  }

  delay(100);
}

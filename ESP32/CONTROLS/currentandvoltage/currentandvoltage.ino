const int voltagePin = 34;  // Analog pin for voltage measurement
const int currentPin = 35;  // Analog pin for current measurement

void setup() {
  Serial.begin(9600);
  pinMode(voltagePin, INPUT);
  pinMode(currentPin, INPUT);
}

void loop() {
  // Read voltage and current values
  float voltage = readVoltage();
  float current = readCurrent();

  // Print the measured values
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("Current: ");
  Serial.print(current);
  Serial.println(" A");

  delay(1000);  // Delay for one second
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

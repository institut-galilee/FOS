int led_pin = 3;

void setup() {
  // initialize serial:
  Serial.begin(9600);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int i  = Serial.parseInt();
    
    if (Serial.read() == '\n'){
      Serial.print("val i = ");
      Serial.println(i);
      analogWrite(led_pin, i);
    }
  }
}

int analog_pin = 0;

int led_pin = 9;

int val = 0;

void setup() {
  Serial.begin(9600);  
}

void loop() {
  val = analogRead(analog_pin);

  Serial.println(val);

  if(val <= 255){
    analogWrite(led_pin, val);
  }

  delay(1000);
}

int led_R = 11;
int led_G = 10;
int led_B = 9;
int i = 0;


void setup() {}

void loop() {
  
  
  for(i = 0; i <= 255; i += 5){
    analogWrite(led_R, i);
    delay(30);
  }

  analogWrite(led_R, 0);

  for(i = 0; i <= 255; i += 5){
    analogWrite(led_B, i);
    delay(30);
  }

  analogWrite(led_G, 0);

  for(i = 0; i <= 255; i += 5){
    analogWrite(led_G, i);
    delay(30);
  }

  analogWrite(led_B, 0);

}

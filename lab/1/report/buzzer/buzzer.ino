int pin = 5;

void setup() {}

void loop() {

  for(int i = 0; i <= 2000; i+=40){
    tone(pin, i);
    delay(30);
  }

  for(int j = 2000; j > 0; j-=40){
    tone(pin, j);
    delay(30);
  }

}

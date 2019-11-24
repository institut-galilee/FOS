# Rapport TP2 Partie 2

## ESP32

### LED

Essai d'utilisation de l'ESP32 avec une LED.

On tape une valeur dans le moniteur et l'ESP32 en fonction de la valeur, donne une intensité d'éclairage à la LED.

```c++
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
```
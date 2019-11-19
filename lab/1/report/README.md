# Rapport TP1

## Exercice 1

**But** : Faire clignoter une LED

### Schema de montage

![Schema de montage](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/blink_map.png)

### Code

```c++

  void setup() {
    pinMode(LED_BUILTIN, OUTPUT); //initialise le pin LED_BUILTIN comme un pin de sortie
  }
  
  void loop() {
    digitalWrite(LED_BUILTIN, HIGH);   // Allume la LED (HIGH equivaut a l'etat allumé = 1)
    delay(1000);                       // Attend pendant une seconde
    digitalWrite(LED_BUILTIN, LOW);    // Eteint la LED
    delay(1000);                       
  }
```

### Demonstration

![LED qui clignote](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Blink.jpg)


## Exercice 5

**But** : Augmenter/Diminuer la luminosite de la LED

### Schema de montage

![Schema de montage](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Fading_map.png)

### Code

```c++

int ledPin = 5;    // La LED est connecté au pin 5 qui permet d'envoyer des valeurs analogiques

void setup() {}

void loop() {
  // Augmente la luminosite de 5 tout les 30 ms
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // Envoie une valeur analogique entre 0 et 255 dans le pin 5
    analogWrite(ledPin, fadeValue); 
    delay(30);
  }

  // Diminue la luminosite de 5 tout les 30 ms
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    analogWrite(ledPin, fadeValue);
    delay(30);
  }
}
```

### Demonstration

![LED qui clignote](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Fading.jpg)

## Exercice 10

**But** : Utiliser une LED RGB

### Schema de montage

![Schema de montage](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/RGB_map.jpg)

### Code

```c++

int led_R = 11;
int led_G = 10;
int led_B = 9;

int i = 0;

void setup() {}

// Augmente petit a petit la luminosite de
// la LED RGB en Rouge, Bleu, Vert, tour a tour

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

```

### Demonstration

![LED qui clignote](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/RGB.jpg)

## Exercice 9

**But** : Utiliser un buzzer passif

### Schema de montage

![Schema de montage](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Buzzer_map.png)

### Code

```c++

int pin = 5;

void setup() {}

void loop() {

  for(int i = 0; i <= 2000; i+=40){
    tone(pin, i); // Envoie un signal de frequence i dans le pin
    delay(30);
  }

  for(int j = 2000; j > 0; j-=40){
    tone(pin, j); // Envoie un signal de frequence i dans le pin
    delay(30);
  }

}

```

### Demonstration

![LED qui clignote](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Buzzer.jpg)


## Exercice 6

**But** : Utiliser un bouton

### Schema de montage

![Schema de montage](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Button_map.png)

### Code

```c++

const int buttonPin = 2;


int buttonState = 0; // Etat du bouton 

// 1 = enfoncé, 0 = pas enfoncé 

void setup() {
  Serial.begin(9600); // Initialise une connexion serie
  pinMode(buttonPin, INPUT); // Initialise le pin comme etant un pin d'entree
}

void loop() {
  buttonState = digitalRead(buttonPin); // Recupere la valeur envoyé dans le pin (valeur digital = 0 ou 1)

  if (buttonState == HIGH) { // bouton enfoncé?
    Serial.println("Le bouton est enfoncé"); // envoie le message dans le port serie
  }
}

```

### Demonstration

![LED qui clignote](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Button.jpg)


## Exercice 4

**But** : Utiliser un potentiometre

### Schema de montage

![Schema de montage](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Potentiometre_map.png)

### Code

```c++

int analog_pin = 0;

int val = 0;

void setup() {
  Serial.begin(9600);  
}

void loop() {
  val = analogRead(analog_pin); // Recupere la valeur reçu dans le pin 0

  Serial.println(val); // Affiche cette valeur
  
  delay(1000);
}

```

### Demonstration

![LED qui clignote](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Potentiometre.jpg)

## Exercice Bonus

**But** : Utiliser un potentiometre avec une LED

### Schema de montage

![Schema de montage](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Potentiometre_bonus_map.png)

### Code

```c++

int analog_pin = 0;

int led_pin = 9;

int val = 0;

void setup() {
  Serial.begin(9600);  
}

void loop() {
  val = analogRead(analog_pin); // Recupere la valeur du potentiometre

  Serial.println(val);

  if(val <= 255){ // Si la valeur du potentiometre est inferieure a 255
    analogWrite(led_pin, val); // On envoit a la LED la valeur de luminosité
  }

  delay(1000);
}
```

### Demonstration

![LED qui clignote](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Poten1.jpg)
![LED qui clignote](https://github.com/institut-galilee/FOS/blob/master/lab/1/report/img/Poten2.jpg)

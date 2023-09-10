//running on a arduino uno with a relay shild
#define relay1Pin 7
#define relay2Pin 6
#define relay3Pin 5
#define relay4Pin 4


void setup() {
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);
  Serial.begin(9600);
}

// its on normaly open, so defualt low is off and high is on
void loop() {
  if (Serial.available() > 0) {
    char state = Serial.read();
    switch (state) {
      // trun on relays
      case '1':
        digitalWrite(relay1Pin, HIGH);
        //Serial.println("relay 1 ON");
        break;
      case '2':
        digitalWrite(relay2Pin, HIGH);
        //Serial.println("relay 2 ON");
        break;
      case '3':
        digitalWrite(relay3Pin, HIGH);
        //Serial.println("relay 3 ON");
        break;
      case '4':
        digitalWrite(relay4Pin, HIGH);
        //Serial.println("relay 4 ON");
        break;
      // trun off relays
      case '5':
        digitalWrite(relay1Pin, LOW);
        //Serial.println("relay 1 OFF");
        break;
      case '6':
        digitalWrite(relay2Pin, LOW);
        //Serial.println("relay 2 OFF");
        break;
      case '7':
        digitalWrite(relay3Pin, LOW);
        //Serial.println("relay 3 OFF");
        break;
      case '8':
        digitalWrite(relay4Pin, LOW);
        //Serial.println("relay 4 OFF");
        break;
      case '9':          // turn all relays off
        digitalWrite(relay4Pin, LOW);
        digitalWrite(relay3Pin, LOW);
        digitalWrite(relay2Pin, LOW);
        digitalWrite(relay1Pin, LOW);
        //Serial.println("All relays OFF");
        break;
      case '0':         // trun all relays on
        digitalWrite(relay4Pin, HIGH);
        digitalWrite(relay3Pin, HIGH);
        digitalWrite(relay2Pin, HIGH);
        digitalWrite(relay1Pin, HIGH);
        //Serial.println("All relays ON");
        break;
    }

  }
  delay(50);
}

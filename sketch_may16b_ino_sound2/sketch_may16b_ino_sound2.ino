const int trigPin = 5;
const int echoPin = 4;

const int bluePin = 11;
const int greenPin = 10;
const int redPin = 9;
const int buzzerPin = 7;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void sirenAlarm() {
  // Sirene auf
  for (int freq = 800; freq <= 1200; freq += 30) {
    tone(buzzerPin, freq);
    delay(20);
  }
  // Sirene ab
  for (int freq = 1200; freq >= 800; freq -= 30) {
    tone(buzzerPin, freq);
    delay(20);
  }
}

void sanftAufsteigend() {
  // Sanfte aufsteigende Töne
  tone(buzzerPin, 400); delay(200);
  tone(buzzerPin, 500); delay(200);
  tone(buzzerPin, 600); delay(200);
  noTone(buzzerPin);
  delay(600);
}

void loop() {
  long duration;
  float distance;

  // Ultraschall senden
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo messen
  duration = pulseIn(echoPin, HIGH);

  // Entfernung berechnen
  distance = duration * 0.034 / 2;

  Serial.print("Abstand: ");
  Serial.println(distance);

  // LEDs + Buzzer reset
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  noTone(buzzerPin);

  if (distance > 50) {
    // Blau — kein Alarm
    analogWrite(bluePin, 255);
    delay(200);

  } 
  else if (distance > 20 && distance <= 50) {
    // Gelb — sanft aufsteigend
    analogWrite(redPin, 60);
    analogWrite(greenPin, 12);
    sanftAufsteigend();

  } 
  else {
    // Rot — Sirene
    analogWrite(redPin, 255);
    sirenAlarm();
  }
}
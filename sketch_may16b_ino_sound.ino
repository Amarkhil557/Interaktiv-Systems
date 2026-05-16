const int trigPin = 5;
const int echoPin = 4;

const int bluePin = 11;
const int greenPin = 10;
const int redPin = 9;
const int buzzerPin = 7;  //  neu

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);  //  neu

  Serial.begin(9600);
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
  noTone(buzzerPin);  // ← neu

  if (distance > 50) {
    // Blau — kein Alarm
    analogWrite(bluePin, 255);

  } 
  else if (distance > 20 && distance <= 50) {
    // Gelb — leises ruhiges Piepen
    analogWrite(redPin, 60);
    analogWrite(greenPin, 12);
    tone(buzzerPin, 500);   // tiefer ruhiger Ton
    delay(200);
    noTone(buzzerPin);
    delay(600);             // lange Pause = ruhig

  } 
  else {
    // Rot — Alarm
    analogWrite(redPin, 255);
    tone(buzzerPin, 1000);  // hoher Ton
    delay(100);
    noTone(buzzerPin);
    delay(100);             // kurze Pause = schnell und dringend
  }

  delay(200);
}
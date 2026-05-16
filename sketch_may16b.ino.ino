const int trigPin = 5;
const int echoPin = 4;

const int bluePin = 11;
const int greenPin = 10;
const int redPin = 9;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);

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

  // LEDs reset
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  digitalWrite(bluePin, LOW);

  if (distance > 50) {
    // Blau
    analogWrite(bluePin, 255);
  } 
  else if (distance > 20 && distance <= 50) {
    // Gelb = Rot + Grün mischen
    analogWrite(redPin, 60);
    analogWrite(greenPin, 12);
    
  } 
  else {
    // Rot
    analogWrite(redPin, 255);
  }

  delay(200);
}

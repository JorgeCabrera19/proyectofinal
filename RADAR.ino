#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
const int laserPin = 13;
const int joystickButtonPin = 2; // Pin digital para el botón del joystick

long duration;
int distance;
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(laserPin, OUTPUT); // Configura el pin del láser como salida
  pinMode(joystickButtonPin, INPUT_PULLUP); // Configura el botón del joystick como entrada con pull-up
  Serial.begin(9600);
  myServo.attach(12);
}

void loop() {
  if (digitalRead(joystickButtonPin) == LOW) {
    // Si se presiona el botón del joystick, detiene el movimiento automático del servo
    stopAutomaticMovement();
  } else {
    // Si no se presiona el botón, continua con el movimiento automático del servo
    automaticMovement();
  }
}

void automaticMovement() {
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance < 10) {
      digitalWrite(laserPin, HIGH); // Enciende el láser si la distancia es menor a 10
    } else {
      digitalWrite(laserPin, LOW); // Apaga el láser si la distancia no es menor a 10
    }
  }

  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance < 10) {
      digitalWrite(laserPin, HIGH); // Enciende el láser si la distancia es menor a 10
    } else {
      digitalWrite(laserPin, LOW); // Apaga el láser si la distancia no es menor a 10
    }
  }
}

void stopAutomaticMovement() {
  // Detiene el movimiento del servo
  myServo.write(90); // Detiene el servo en la posición media (90 grados)
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}


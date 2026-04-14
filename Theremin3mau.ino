const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 3;
const int ledPin[] = {5,6,7};

float smoothedDistance = 0; 
float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  for(int i = 0; i < 3; i++) {
    pinMode(ledPin[i], OUTPUT);

  }
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  
  if (distance >= 1 && distance <= 40) {
    
    smoothedDistance = (smoothedDistance * 0.8) + (distance * 0.2);

    int pitch = map(smoothedDistance, 2, 40, 1500, 200); 
    pitch = constrain(pitch, 200, 1500);

    int brightness = map(smoothedDistance, 2, 40, 255, 0);
    brightness = constrain(brightness, 0, 255);

    Serial.println(distance);
    
    if (distance >= 27 && distance <= 40) {
        for(int i = 0; i < 2; i++) {
          digitalWrite(ledPin[i], LOW);
        }
        digitalWrite(ledPin[2], HIGH);
    }
    else if (distance>=13) {
      for(int i = 1; i < 3; i++) {
        digitalWrite(ledPin[i], HIGH);
      }
      digitalWrite(ledPin[0], LOW);
    }
    else {
      for(int i = 0; i < 3; i++) {
      digitalWrite(ledPin[i], HIGH);
      }
    }
  }
  else {
    for(int i = 0; i < 3; i++) {
          digitalWrite(ledPin[i], LOW);
    }
    noTone(buzzerPin); 
    Serial.println("Quá xa");
    delay(1000);
  }

  delay(20);
}
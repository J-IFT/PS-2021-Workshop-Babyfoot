const byte TRIGGER_PIN = 4; // Broche TRIGGER
const byte ECHO_PIN = 5;    // Broche ECHO
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s
/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;
float moy1;
const float distanceDif = 15;

void setup() {
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.

}

void loop() {
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN,LOW);

  long measure = pulseIn(ECHO_PIN,HIGH,MEASURE_TIMEOUT);
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  if(distance_mm >= (moy1 + distanceDif) || distance_mm < (moy1-distanceDif))
  {
     Serial.print(F("Distance: "));
  Serial.print(distance_mm);
  Serial.print(F("mm ("));
  Serial.print(distance_mm / 10.0, 2);
  Serial.print(F("cm, "));
  Serial.print(distance_mm / 1000.0, 2);
  Serial.println(F("m)"));
  delay(500);
  }

}

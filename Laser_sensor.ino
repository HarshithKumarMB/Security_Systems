int ldr_pin = A0;
int ledval = 0;
const int buzzer = 7; //buzzer to arduino pin 9

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(ldr_pin, INPUT);
}

void loop() {
  ledval = analogRead(ldr_pin);
  digitalWrite(buzzer, LOW);
  Serial.println(ledval);
  if(ledval <.f- 100){
    digitalWrite(buzzer, HIGH);
    delay(2000);
  }

}

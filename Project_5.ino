 

volatile bool armed = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EIMSK |= (1 << INT1);
  EICRA |= (1 << ISC11);
  EICRA &=~ (1 << ISC10); 
}


long distance;

ISR (INT1_vect) {
  armed = false;
}
void loop() {
  // put your main code here, to run repeatedly:

  DDRD |= 0x08;
  //pinMode(3, OUTPUT);


  PORTD &=~ 0x08;
  PORTD |= 0x08;
  //digitalWrite(3, LOW);
  //digitalWrite(3, HIGH);

  delayMicroseconds(5);

  PORTD &=~ 0x08;
  //digitalWrite(3, LOW);

  delayMicroseconds(750);

  DDRD &=~ 0x08;
  //pinMode(3, INPUT);
  long start = micros();

      armed = true;
      while (armed);
 
        distance = ((micros() - start) * 481) / 2827;
  
        Serial.println(distance);
        delay(2000);
  
}

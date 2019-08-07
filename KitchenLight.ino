#define GREEN    9
#define BLUE     10
#define RED      11
#define BUTTON   7
#define PIR      A0
#define RELAY    8

#define DARKNESS 650

#define DELAY    500
#define SECOND   DELAY * 2
#define MULT     100

#define SOME_MINUTES SECOND * 1 * MULT
#define HALF_AN_HOUR SECOND * 18 * MULT
#define ONE_HOUR     SECOND * 36 * MULT
#define TOO_MUCH     ONE_HOUR * 3

uint32_t count = 0;
uint32_t some_minutes = (uint32_t)SOME_MINUTES;
uint32_t half_an_hour = (uint32_t)HALF_AN_HOUR;
uint32_t one_hour = (uint32_t)ONE_HOUR;
uint32_t too_much = (uint32_t)TOO_MUCH;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(PIR,    INPUT);  
  pinMode(RED,    OUTPUT);
  pinMode(GREEN,  OUTPUT);  
  pinMode(BLUE,   OUTPUT);  
  pinMode(RELAY,  OUTPUT); 
  for(int i = 8; i < 13; i++){
    digitalWrite(i, HIGH);
    delay(3000);
    digitalWrite(i, LOW);
    delay(300);
  }
  //Serial.begin(9600);
}

void loop() {
  delay(DELAY);
  //Serial.println(count);
  //Serial.println(analogRead(A0));
  //Serial.println("==============");
  if(analogRead(PIR) > DARKNESS){count = some_minutes;}
  if(digitalRead(BUTTON) == LOW){
    count += some_minutes;
  }
  if(count > too_much){
    count = too_much;
    for(int i = 0; i < 5; i++){
      digitalWrite(RED, HIGH);
      delay(100);
      digitalWrite(RED, LOW);
      delay(100);
      digitalWrite(GREEN, HIGH);
      delay(100);
      digitalWrite(GREEN, LOW);
      delay(100);
    }
    if(digitalRead(BUTTON) == LOW){digitalWrite(RELAY, LOW); count = 0; delay(3000);}
  }
  if(count > one_hour){
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, HIGH);
  }
  else if(count > half_an_hour && count <= one_hour){
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, HIGH);
  }
  else if(count > 0 && count <= some_minutes){
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, HIGH);
  }
  if(count == 0){
    digitalWrite(RELAY, LOW);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  }  
  else {
    digitalWrite(RELAY, HIGH);
    count -= DELAY;
  }
}

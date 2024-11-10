#define LedG 10
#define LedR 9
#define LedB 8
#define bot 3
#define pinto A0

void setup() {
  // put your setup code here, to run once:
pinMode(LedR, OUTPUT);
pinMode(LedG, OUTPUT);
pinMode(LedB, OUTPUT);
pinMode(bot, INPUT);
pinMode(pinto, INPUT);

digitalWrite(LedR, LOW);
digitalWrite(LedG, LOW);
digitalWrite(LedB, LOW);

Serial.begin(9600);
}

int botS = 0;

void loop() {

  Serial.println(pinto);
   
  if(digitalRead(bot) == HIGH){
    botS = botS + 1;
  }
  delay (10);
  if(botS == 0){
    digitalWrite(LedR, LOW);
    digitalWrite(LedG, LOW);
    digitalWrite(LedB, LOW);
  }
  
  if(botS == 1){
    digitalWrite(LedR, HIGH);
    delay (300);
    digitalWrite(LedR, LOW);
    digitalWrite(LedG, HIGH);
    delay (300);
    digitalWrite(LedG, LOW);
    digitalWrite(LedB, HIGH);
    delay (300);
    digitalWrite(LedB, LOW);
  }
  if(botS == 2){
    digitalWrite(LedR, HIGH);
    delay (50);
    digitalWrite(LedR, LOW);
    digitalWrite(LedG, HIGH);
    delay (50);
    digitalWrite(LedG, LOW);
    digitalWrite(LedB, HIGH);
    delay (50);
    digitalWrite(LedB, LOW);
  }
  delay(10);
  if(botS == 3){
    digitalWrite(LedR, HIGH);
    digitalWrite(LedG, HIGH);
    digitalWrite(LedB, HIGH);
    }
  delay (20);
  if(botS == 4){
    digitalWrite(LedR, HIGH);
  }
  delay(20);
  if(botS == 5){
    digitalWrite(LedG, HIGH);
  }
  delay (20);
  if(botS == 6){
    digitalWrite(LedB, HIGH);
  }
  if(botS > 6){
    botS = 0;
  }
}


#define SENSOR A10
#define LED1R 26
#define LED1G 8
#define LED1B 16
#define LED2R 27
#define LED2G 9
#define LED2B 17
#define LED3R 2
#define LED3G 10
#define LED3B 18
#define LED4R 3
#define LED4G 11
#define LED4B 19
#define LED5R 4
#define LED5G 12
#define LED5B 20
#define LED6R 5
#define LED6G 13
#define LED6B 21

// Matriz para os LEDs
int led[6][3] = {{LED1R, LED1G, LED1B},
                 {LED2R, LED2G, LED2B},
                 {LED3R, LED3G, LED3B},
                 {LED4R, LED4G, LED4B},
                 {LED5R, LED5G, LED5B},
                 {LED6R, LED6G, LED6B}};

int ledTroca = 0;

bool tocou = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR, INPUT);
  Serial.begin(9600);
   // Inicialização dos valores digitais da matriz de leds
   for (int i = 0; i < 6; i++)
   {
     for (int j = 0; j < 3; j++)
     {
        pinMode(led[i][j], OUTPUT);
        digitalWrite(led[i][j], LOW);
     }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
   while (analogRead(SENSOR) > 144){
       tocou = true;
   }

   if (tocou) {
     rgb_led(1);
     tocou = false;
   }
}

void rgb_led(int n)
{
  if (ledTroca == 3)
    ledTroca = 0;
    
  digitalWrite(led[n-1][ledTroca], HIGH);
  //Serial.println(ledTroca);
  delay(100);
  digitalWrite(led[n-1][ledTroca], LOW);
  
  ledTroca++;
}

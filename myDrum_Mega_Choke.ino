//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																//
// Código Escrito por: Christian D'Aquino																						//
// Versão: 20150109																												//
// Editado por Rodrigo Amaral 																																//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// NÃO ESQUEÇA DE COLOCAR O BAUDRATE DO HAIRLESS COM O VALOR 115200

//******	Configurações do Usuário		************************************************************************************/

// EXPLICAÇÃO CONFIGURACAO DOS PADS 
// TODOS OS PARAMETROS ABAIXO ESTÃO POR ORDEM DOS PINOS ANALOGICOS, DESSA FORMA: ={A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15};
// SensorType[16] = TIPO DE CADA PAD; || 144 = PIEZO || 176 = CONTROLADOR DE HIHAAT || 128 = DESABILITADO ||													
// PadNote[16] = NOTA DE CADA UM DOS PINOS														
// thresholdMin[16]= VALOR MINIMO DOS PIEZOS PARA DISPARAR A NOTA													
// thresholdMax[16]= VALOR MAXIMO DOS PIEZOS														
// sensorScantime[16]= TEMPO DE LEITURA DE CADA UM DOS PIEZOS														
// sensorMasktime[16]= TEMPO DE LEITURA DO PIEZO QUE SERÁ IGNORADO

//CONFIGURACAO DEFAULT DAS NOTAS DOS PINOS (NOTAS UTILIZADAS NO ADDICTIVE DRUMS, PODE VARIAR COM OUTROS VST'S)
//A0 - NOTA (CC) 4 - CONTROLADOR DE HIHAT
//A1 - NOTA 38 - SNARE (CAIXA)
//A2 - NOTA 42 - SNARE SIDESTICK (ARO)
//A3 - NOTA 36 - KICK (BUMBO)
//A4 - NOTA 71 - TOM 1
//A5 - NOTA 69 - TOM 2
//A6 - NOTA 67 - TOM 3
//A7 - NOTA 65 - TOM 3 
//A8 - NOTA 47 - XTRA 1 (PAD EXTRA)
//A9 - NOTA 73 - XTRA 2 (PAD EXTRA)
//A10 - NOTA 8 - HIHAT (CHIMBAL)
//A11 - NOTA 77 - CYMBAL 1 (PRATO 1)
//A12 - NOTA 79 - CYMBAL 2 (PRATO 2)
//A13 - NOTA 81 - CYMBAL 3 (PRATO 3)
//A14 - NOTA 60 - RIDE TIP (CONDUÇÃO CORPO)
//A15 - NOTA 61 - RIDE BELL (CONDUÇÃO CÚPULA)

byte SensorType[16] ={176,144,128,144,128,144,144,144,128,128,144,144,144,128,144,128};													
byte PadNote[16] ={4,38,42,36,71,69,67,65,47,73,8,77,79,81,60,61};															
int thresholdMin[16]={50,700,700,700,700,700,700,700,700,700,700,700,700,700,700,700};															
int thresholdMax[16]={1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023};															
int sensorScantime[16]={10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};															
int sensorMasktime[16]={5,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90};	
int ledMask[16] = {0, 2, 2, 5, 9, 8, 5 , 2, 1 ,5, 3, 3, 2, 5, 9, 2};


#define READPIN 16 // DEFINE QUANTOS PINOS ANALÓGICOS DO ARDUINO SERÃO LIDOS, EM ORDEM (Ex: 1 = A0 || 2= A0, A1 e assim por diante. //														
													

//****** Configurações de Choke e dos Pinos Digitais Auxiliares*********************************//	

// Define as notas do chocke //

#define choke1 78
#define choke2 80   
#define choke3 82
#define chokeRide 63

// Define as Notas dos Plugs Digitais Auxiliares //

#define Aux1 47
#define Aux2 47
#define Aux3 47
#define Aux4 47
#define Aux5 47
#define Aux6 47
#define Aux7 47																	
																														
//******  NAO ALTERAR //	Configuração do programa //NAO ALTERAR SE NAO SOUBER O QUE ESTÁ FAZENDO!*********************************//

//Define os Pinos Digitais dos Chokes

#define Choke1_Pin 51 
#define Choke2_Pin 49
#define Choke3_Pin 47
#define ChokeRide_Pin 53 

//Define os Pinos Digitais Auxiliares

#define Aux1_Pin 33
#define Aux2_Pin 35
#define Aux3_Pin 37
#define Aux4_Pin 39
#define Aux5_Pin 41
#define Aux6_Pin 43
#define Aux7_Pin 45

// Define os Pinos Digitais dos LEDs

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

//Define o estado dos pinos digitais

int Choke1_State = LOW;
int Choke2_State = LOW;
int Choke3_State = LOW;
int ChokeRide_State = LOW;
int Aux1_State = LOW;
int Aux2_State = LOW;
int Aux3_State = LOW;
int Aux4_State = LOW;
int Aux5_State = LOW;
int Aux6_State = LOW;
int Aux7_State = LOW;

int currentSwitchState = LOW;

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define midichannel 0


// Matriz para os LEDs
int led[6][3] = {{LED1R, LED1G, LED1B},
               {LED2R, LED2G, LED2B},
               {LED3R, LED3G, LED3B},
               {LED4R, LED4G, LED4B},
               {LED5R, LED5G, LED5B},
               {LED6R, LED6G, LED6B}};

int ledTroca = 0;

int readSensor = 0;

unsigned long previousMillis[16];
unsigned long currentMillis[16];
unsigned int sensorReads[10];
int readNumber[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
boolean playNote[16] ={true, true, true,true,true,true,true,true,true,true,true,true,true, true, true,true};

int pin = 0;

void setup()
{
  //Serial.begin(115200);
  Serial.begin(9600);
  pinMode(Choke1_Pin, INPUT);
  pinMode(Choke2_Pin, INPUT);
  pinMode(Choke3_Pin, INPUT);
  pinMode(ChokeRide_Pin, INPUT);
  pinMode(Aux1_Pin, INPUT);
  pinMode(Aux2_Pin, INPUT);
  pinMode(Aux3_Pin, INPUT);
  pinMode(Aux4_Pin, INPUT);
  pinMode(Aux5_Pin, INPUT);
  pinMode(Aux6_Pin, INPUT);
  pinMode(Aux7_Pin, INPUT);
  
  digitalWrite(Choke1_Pin, HIGH);  // turn on internal pullup
  digitalWrite(Choke2_Pin, HIGH);  // turn on internal pullup
  digitalWrite(Choke3_Pin, HIGH);  // turn on internal pullup
  digitalWrite(ChokeRide_Pin, HIGH);  // turn on internal pullup  
  digitalWrite(Aux1_Pin, HIGH);  // turn on internal pullup
  digitalWrite(Aux2_Pin, HIGH);  // turn on internal pullup
  digitalWrite(Aux3_Pin, HIGH);  // turn on internal pullup
  digitalWrite(Aux4_Pin, HIGH);  // turn on internal pullup
  digitalWrite(Aux5_Pin, HIGH);  // turn on internal pullup
  digitalWrite(Aux6_Pin, HIGH);  // turn on internal pullup
  digitalWrite(Aux7_Pin, HIGH);  // turn on internal pullup
  
  // Inicialização dos valores digitais da matriz de leds
   for (int i = 0; i < 6; i++)
   {
     for (int j = 0; j < 3; j++)
     {
        pinMode(led[i][j], OUTPUT);
        digitalWrite(led[i][j], LOW);
     }
  }
	
	//while (!Serial) {
	//; // wait for serial port to connect. Needed for Arduino Leonardo only
	//}
  
	// set prescale to 8
	//cbi(ADCSRA,ADPS2);
	//sbi(ADCSRA,ADPS1);
	//sbi(ADCSRA,ADPS0);
	
	//Serial.flush();
  
}

void loop()

// ==================================== LEITURA DOS PINOS DIGITAIS ==================================== //

// CHOKE PRATO 01
{
currentSwitchState = digitalRead(Choke1_Pin);
if( currentSwitchState == LOW && Choke1_State == HIGH ) // push
MIDI_TX(144,  choke1, 127);
if( currentSwitchState == HIGH && Choke1_State == LOW ) // release
MIDI_TX(128, choke1, 127);
Choke1_State = currentSwitchState;

  
// CHOKE PRATO 02
{
currentSwitchState = digitalRead(Choke2_Pin);
if( currentSwitchState == LOW && Choke2_State == HIGH ) // push
MIDI_TX(144,  choke2, 127);
if( currentSwitchState == HIGH && Choke2_State == LOW ) // release
MIDI_TX(128, choke2, 127);
Choke2_State = currentSwitchState;

  
// CHOKE PRATO 03
{
currentSwitchState = digitalRead(Choke3_Pin);
if( currentSwitchState == LOW && Choke3_State == HIGH ) // push
MIDI_TX(144,  choke3, 127);
if( currentSwitchState == HIGH && Choke3_State == LOW ) // release
MIDI_TX(128, choke3, 127);
Choke3_State = currentSwitchState;

  
// CHOKE RIDE
{
currentSwitchState = digitalRead(ChokeRide_Pin);
if( currentSwitchState == LOW && ChokeRide_State == HIGH ) // push
MIDI_TX(144,  chokeRide, 127);
if( currentSwitchState == HIGH && ChokeRide_State == LOW ) // release
MIDI_TX(128, chokeRide, 127);
ChokeRide_State = currentSwitchState;

  
// AUX 1
{    
currentSwitchState = digitalRead(Aux1_Pin);
if( currentSwitchState == LOW && Aux1_State == HIGH ) // push
MIDI_TX(144,  Aux1, 127);
if( currentSwitchState == HIGH && Aux1_State == LOW ) // release
MIDI_TX(128, Aux1, 127);
Aux1_State = currentSwitchState;

  
// AUX 2
{    
currentSwitchState = digitalRead(Aux2_Pin);
if( currentSwitchState == LOW && Aux2_State == HIGH ) // push
MIDI_TX(144,  Aux2, 127);
if( currentSwitchState == HIGH && Aux2_State == LOW ) // release
MIDI_TX(128, Aux2, 127);
Aux2_State = currentSwitchState;


// AUX 3
{    
currentSwitchState = digitalRead(Aux3_Pin);
if( currentSwitchState == LOW && Aux3_State == HIGH ) // push
MIDI_TX(144,  Aux3, 127);
if( currentSwitchState == HIGH && Aux3_State == LOW ) // release
MIDI_TX(128, Aux3, 127);
Aux3_State = currentSwitchState;


// AUX 4
{    
currentSwitchState = digitalRead(Aux4_Pin);
if( currentSwitchState == LOW && Aux4_State == HIGH ) // push
MIDI_TX(144,  Aux4, 127);
if( currentSwitchState == HIGH && Aux4_State == LOW ) // release
MIDI_TX(128, Aux4, 127);
Aux4_State = currentSwitchState;


// AUX 5
{    
currentSwitchState = digitalRead(Aux5_Pin);
if( currentSwitchState == LOW && Aux5_State == HIGH ) // push
MIDI_TX(144,  Aux5, 127);
if( currentSwitchState == HIGH && Aux5_State == LOW ) // release
MIDI_TX(128, Aux5, 127);
Aux5_State = currentSwitchState;

  
// AUX 6
{    
currentSwitchState = digitalRead(Aux6_Pin);
if( currentSwitchState == LOW && Aux6_State == HIGH ) // push
MIDI_TX(144,  Aux6, 127);
if( currentSwitchState == HIGH && Aux6_State == LOW ) // release
MIDI_TX(128, Aux6, 127);
Aux6_State = currentSwitchState;

  
// AUX 7
{    
currentSwitchState = digitalRead(Aux7_Pin);
if( currentSwitchState == LOW && Aux7_State == HIGH ) // push
MIDI_TX(144,  Aux7, 127);
if( currentSwitchState == HIGH && Aux7_State == LOW ) // release
MIDI_TX(128, Aux7, 127);
Aux7_State = currentSwitchState;


//============================= LEITURA DOS PINOS ANALOGICOS =========================================================================//


	for(pin = 0; pin < READPIN; pin++)
	{
		readSensor = analogRead(pin);
                
                if((SensorType[pin] != 128) && (readSensor > thresholdMin[pin]) && ((currentMillis[pin] - previousMillis[pin]) <= sensorMasktime[pin]))
		{
			currentMillis[pin] = millis();
			
			if (readNumber[pin] < sensorScantime[pin])
			{
				if (readSensor > sensorReads[pin])
				{
					sensorReads[pin] = readSensor;
					
				}
				readNumber[pin]++;
			} else if (playNote[pin] == true)
			{
				
				playNote[pin] = false;
				int velocity = normalizeSensor(sensorReads[pin], pin);
				MIDI_TX(SensorType[pin], PadNote[pin], velocity);
			}
			
			
			
		} else if ((currentMillis[pin] - previousMillis[pin]) > sensorMasktime[pin])
		{
			playNote[pin] = true;
			readNumber[pin] = 0;
			sensorReads[pin] = 0;
			previousMillis[pin] = currentMillis[pin];
		}
	}

// =======================================================================================================================================================//
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
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

int IF =A3;

void setup(){
  pinMode(IF, INPUT);
  Serial.begin(9600);
}

void loop(){
  if(analogRead(A3) > 400)
  Serial.println(analogRead(A3));
}

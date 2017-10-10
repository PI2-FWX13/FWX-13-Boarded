#include<SoftwareSerial.h>
SoftwareSerial serial1(6, 7); // RX, TX


void setup(){
  serial1.begin(9600);
 
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}


void loop(){
  int recebe = 0;
  int freq = 20;
  int i;
  while(serial1.available()){
	char c_pointer[sizeof(float)];
    	for(int i = 0; i < sizeof(float); i++)
    		c_pointer + i = serial1.read();

	float *f_pointer = (float *) c_pointer;
	Serial.print(*f_pointer);
}
 

 
  if(recebe!=0 ){
    int i = 0; 
  while(i<(recebe*50)){
   //antihortio
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delay(freq);
  
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delay(freq);
  
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(freq);
  
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  delay(freq);
  i++;
  }
   i = 0;
  delay(1);
  while(i<(recebe*50)){
    //horario
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(20);
  
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(20);
  
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delay(20);
  
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  delay(20);
  i++;
  }
  i= 0;
  delay(1);
  
 } 
}


#include <TimerOne.h>

#include<SoftwareSerial.h>
SoftwareSerial serial1(6, 7); // RX, TX

#define MAX 500
/*int i, t, j, sentido_x[MAX], sentido_y[MAX], sentido_z[MAX];
int numberOfLines = 0;
float freq_x[MAX], freq_y[MAX], freq_z[MAX], tempo[MAX];
char definicao;*/
int numberOfLines;

void setup(){
  serial1.begin(9600);
  Serial.println("Entrou no setup");
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}


void loop(){  
  int i, t, j, sentido_x[MAX], sentido_y[MAX], sentido_z[MAX];

  float freq_x[MAX], freq_y[MAX], freq_z[MAX], tempo[MAX];
  char definicao;
  //Serial.println("Entrou no loop");
   if(serial1.available())
{
	Serial.println("Tem dados disponiveis");
	definicao = serial1.read();	
	
	if (definicao == 'N')
	{
		char c_pointer[sizeof(int)];
    		for(int i = 0; i < sizeof(int); i++)
                       *(c_pointer + i) = serial1.read();
		numberOfLines = *((int *) c_pointer);
                Serial.print("If de N: ");
                Serial.println(numberOfLines);

   	}

	if (definicao == 'X')
	{
		char c_pointer[sizeof(float)];
                Serial.print("If de X: ");
                Serial.println(numberOfLines);
		for(j = 0; j < numberOfLines; j++)
		{
                        
                        for(int i = 0; i < sizeof(float); i++)
    				*(c_pointer + i) = serial1.read();
		        freq_x[j] = *((float *) c_pointer);
                        digitalWrite(8, HIGH);
                        delay(freq_x[j]*10);
                        digitalWrite(8, LOW);
                        delay(freq_x[j]*10);
                        
                       
                }
   	}

	if (definicao == 'Y')
	{
		char c_pointer[sizeof(float)];
		for(int j = 0; j < numberOfLines; j++)
		{
    			for(int i = 0; i < sizeof(float); i++)
    				*(c_pointer + i) = serial1.read();
		        freq_y[j] = *((float *) c_pointer);
                                               
                        
		}
   	}
	
	if (definicao == 'Z')
	{
		char c_pointer[sizeof(float)];
		for(int j = 0; j < numberOfLines; j++)
		{
    			for(int i = 0; i < sizeof(float); i++)
    				*(c_pointer + i) = serial1.read();
		        freq_z[j] = *((float *) c_pointer);
                        
		}
   	}

	if (definicao == 'A')
	{
		char c_pointer[sizeof(int)];
		for(int j = 0; j < numberOfLines; j++)
		{
    			for(int i = 0; i < sizeof(int); i++)
    				*(c_pointer + i) = serial1.read();
		        sentido_x[j] = *((int *) c_pointer);
        	}
   	}

	if (definicao == 'B')
	{
		char c_pointer[sizeof(int)];
		for(int j = 0; j < numberOfLines; j++)
		{
    			for(int i = 0; i < sizeof(int); i++)
    				*(c_pointer + i) = serial1.read();
		        sentido_y[j] = *((int *) c_pointer);
		}
   	}

	if (definicao == 'C')
	{
		char c_pointer[sizeof(int)];
		for(int j = 0; j < numberOfLines; j++)
		{
    			for(int i = 0; i < sizeof(int); i++)
    				*(c_pointer + i) = serial1.read();
		        sentido_z[j] = *((int *) c_pointer);
		}
   	}

	if (definicao == 'T')
	{
		char c_pointer[sizeof(float)];
		for(int j = 0; j < numberOfLines; j++)
		{
    			for(int i = 0; i < sizeof(float); i++)
    				*(c_pointer + i) = serial1.read();
		        tempo[j] = *((float *) c_pointer);
                        
		}
   	}


/*if (definicao == 'N')
{
      digitalWrite(8, HIGH);
      delay(numberOfLines*500);
      digitalWrite(8, LOW);
      delay(numberOfLines*500);
}*/

}

/*for(int j = 0; j < numberOfLines; j++)
{
if (sentido_x[j] == 1)
{ 
	while(t < tempo[j]){
   	//antihorario
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
  delay(1);
}
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
  
 }*/ 
}




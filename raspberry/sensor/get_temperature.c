#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Para compilar gcc get_temperature.c -o run -lwiringPi -lm

int main() // Isso vai ser uma thread
{
	wiringPiSetup(); //Inicializa a WiringPi
	int in[] = {8, 9, 7, 0, 2, 3, 12, 13};
	for(int i=0; i<8; i++)
		pinMode(in[i], INPUT); //Denomina os pinos como entradas
	pinMode(14, OUTPUT);
	int b[8];

	while (1)
	{
		float temperatura = 0;
		digitalWrite(14, HIGH);
		delay(100);
		digitalWrite(14, LOW);
		delay(100);
		for (int i=0; i<8; i++)
		{
			b[i] = digitalRead(in[i]); //Lê as entradas
			printf("Bit [%d]: %d ", i, b[i]);
			temperatura += b[i]*(pow(2, i)); //Pega cada bit e multiplica pelo seu valor 
		}
		temperatura = (temperatura)*2; // 2 é porque o valor no circuito tá saindo pela metade
		printf("Temperatura: %f graus Celsius.\n", temperatura);
	}
}

// O código abaixo é para testar a lógica sem ter o circuito como entrada
/*int main() 
{
	int in[8] = {0, 0, 0, 0, 0, 0, 0, 1};
	double temperatura=0;

		for (int i=0; i<8; i++)
		{
			temperatura += in[i]*(pow(2,i));
		}
		printf("Temperatura: %f graus Celsius.\n", temperatura);
	
}*/
		


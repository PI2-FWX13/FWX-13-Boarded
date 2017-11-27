#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


// A pinagem foi aleatória porque não olhei pino por pino ainda na rasp
#define in1 0
#define in2 1
#define in3 2
#define in4 3
#define in5 4
#define in6 5
#define in7 6
#define in8 7


/*int main() // Isso vai ser uma thread
{
	wiringPiSetup(); //Inicializa a WiringPi
	int in[8];
	int j;
	for(j=0; j<8; j++)
		pinMode(in[j], INPUT); //Denomina os pinos como entradas

	int b[8];
	double temperatura=0;

	while (1)
	{
		int i;
		for (i=0; i<8; i++)
		{
			b[i] = digitalRead(in[i]); //Lê as entradas
			temperatura += b[i]*(pow(2, i)); //Pega cada bit e multiplica pelo seu valor
		}
		temperatura = (temperatura*0.019)*2; // 0.019 é a resolução e 2 é porque o valor no circuito tá saindo pela metade
		printf("Temperatura: %f graus Celsius.\n", temperatura);
	}
}*/

// O código abaixo é para testar a lógica sem ter o circuito como entrada
int main()
{
	int in[17] = {0, 0, 1, 1, 0, 1, 2, 3, 1, 1, 1, 1, 2, 3, 4, 1, 2};
	double temperatura=0;
	int i;


	/*if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}*/

	for (i=0; i<17; i++)
	{
		FILE *f = fopen("temperature.out", "a");
		sleep(1);
		temperatura += in[i]*(pow(2,i));
		temperatura = (temperatura*0.019);
		fprintf(f, "%lf\n", temperatura);
		temperatura = (temperatura*0.019);
		//printf("%lf\n", temperatura);
		fclose(f);
	}

	//printf("END\n");


}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "serial.h"
#include "read_gcode.h"

/* Informações para não esquecer:
Tamanho eixo x: 2*pi*r = 2*3.1415*100 = 628.3 mm
Tamanho eixo y: 1.2 m = 1200 mm
Tamanho eixo z: 20 cm = 200 mm
Cálculo velocidade: rpm = (frequencia x 60)/200*(nº de divisão de passo)
Sentido: 0 -> horário
     1 -> anti-horário
As variáveis que serão passadas para o ATMega serão: freq_x,freq_y,freq_z, sentido_x, sentido_y, sentido_z e tempo */

// Variáveis globais
FILE *fp;
/*int in[] = {8, 9, 7, 0, 2, 3, 12, 13};
int b[8];

void funcao_temperatura()
{
	/*struct sched_param sp;
    	sp.sched_priority == 60;
   	if(pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp))
	printf("ATENÇÃO: Erro em colocar prioridade na thread!\n");	
	
	while (1)
	{
		fp = fopen("temp", "ab+");
		float temperatura = 0;
		digitalWrite(14, HIGH);
		delay(100);
		digitalWrite(14, LOW);
		delay(100);
		for (int i=0; i<8; i++)
		{
			b[i] = digitalRead(in[i]); //Lê as entradas
			temperatura += b[i]*(pow(2, i)); //Pega cada bit e multiplica pelo seu valor 
		}
		temperatura = (temperatura)*2; // 2 é porque o valor no circuito tá saindo pela metade
		fprintf(fp, "%f\n", temperatura);
		fclose(fp);
		delay(1000);
	}
}*/

int main(void) {

    //for(int i=0; i<8; i++)
//	pinMode(in[i], INPUT); //Denomina os pinos como entradas para temperatura
  //  pinMode(14, OUTPUT);

   // pthread_t temp; 
   // pthread_create(&temp, NULL, funcao_temperatura, NULL); // Cria a thread
    wiringPiSetup(); // Inicializa a wiringPi

    /*struct sched_param sp;
    sp.sched_priority == 99;
    if(pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp))
	printf("ATENÇÃO: Erro em colocar prioridade na thread!\n");*/
    get_freq_sentido(); // Lê o GCode e faz todos os cálculos para variáveis

    if(serial_init() == -1) {
        printf("error to initialize serial port\n");
        exit(1);
    }
    //numberOfLines = 15;
    for(int n = 0; n < numberOfLines; n++) {
	printf("Entrei no for.\n");
	while(serial_read() != 100)
		printf("Esperando receber a tag do Arduino\n"); 
	if (n == 0)
		serial_write("ABC", 3 * sizeof(char));

	printf("Saí do ABC\n");	

	serial_write((char *) &freq_x[n], sizeof(float));
	serial_write((char *) &freq_y[n], sizeof(float));
	serial_write((char *) &freq_z[n], sizeof(float));
	serial_write((char *) &Xs[n], sizeof(float));
	serial_write((char *) &Ys[n], sizeof(float));
	serial_write((char *) &Zs[n], sizeof(float));
	serial_write((char *) &soma_rasp[n], sizeof(int));
	delay(2000);
	while (serial_read() == 'N')
	{
		printf("Soma_rasp: %d\n", soma_rasp[n]);
		printf("Chave: %c\n", serial_read());
		serial_write((char *) &freq_x[n], sizeof(float));
		serial_write((char *) &freq_y[n], sizeof(float));
		serial_write((char *) &freq_z[n], sizeof(float));
		serial_write((char *) &tempo[n], sizeof(float));
		serial_write((char *) &Xs[n], sizeof(float));
		serial_write((char *) &Ys[n], sizeof(float));
		serial_write((char *) &Zs[n], sizeof(float));
		serial_write((char *) &soma_rasp[n], sizeof(int));
		delay(2000);
	}
	delay(8000);
	printf("Frequencia x: %f\n", freq_x[n]);
	printf("Frequencia y: %f\n", freq_y[n]);
	delay(2000);
}
    serial_close();
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> // para o timer
#include <unistd.h> // para possíveis pausas
#include <signal.h> // para o sinal
#include "read_gcode.h"

/* Informações para não esquecer:
Tamanho eixo x: 2*pi*r = 2*3.1415*100 = 628.3 mm
Tamanho eixo y: 1.2 m = 1200 mm
Tamanho eixo z: 20 cm = 200 mm
Cálculo velocidade: rpm = (frequencia x 60)/200*(nº de divisão de passo)
Sentido: 0 -> horário
     1 -> anti-horário
*/


//Variáveis globais
float tempo_rest, time = 0, freq_atual, tempo_atual;
int tag = 0, ledState1 = LOW, ledState2 = LOW, ledState3 = LOW, ledState4 = LOW, m = -1 , n = -1;
char sentido_atual;
long interval, previousMillis = 0;
struct itimerval it_val;
float freq_x[] = {10, 6, 1};
char sentido_x[] = {1, 0, 0};
float tempo[] = {1, 1, 3.5};
int numberOfLines = 3;
float tempo_freq_atual;

// Protótipos
void configuracao_sinal(float freq_x);
int calculos(float *freq_x, char *sentido_x, float *tempo);
void controla_motor();
void sentido_horario();
void sentido_antihorario();
void escrever_saidas(int estado1, int estado2, int estado3, int estado4);

int main(void) {
	printf("Entrei na main\n");
	pinMode(8, OUTPUT);
 	pinMode(9, OUTPUT);
  	pinMode(7, OUTPUT);
  	pinMode(0, OUTPUT);
	//get_freq_sentido();
	calculos(freq_x, sentido_x, tempo);
}

void configuracao_sinal(float freq_x)
{
	printf("Entrei configuracao sinal\n");
	float tempo_freq;
	int retorno;
	tempo_freq = 1/freq_x;	
	if (signal(SIGALRM, (void (*)(int)) controla_motor) == SIG_ERR) 
	{
    		perror("Erro ao chamar o sinal.");
    		exit(1);
  	}
	if (tempo_freq < 1)
	{
  		it_val.it_value.tv_sec =   tempo_freq;
		printf("Período de x: %f\n", tempo_freq);
 		it_val.it_value.tv_usec =    tempo_freq*1000000;
		it_val.it_interval = it_val.it_value;
	}
	else
	{
		it_val.it_value.tv_sec = tempo_freq;
		printf("Período de x: %f\n", tempo_freq);
		it_val.it_value.tv_usec = tempo_freq/1000000;
		it_val.it_interval = it_val.it_value;
	}
	printf("Vai chamar o setitimer\n");
  
  	if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) 
	{
    		perror("Erro ao chamar o setitimer.");
    		exit(1);
 	}
}

int calculos(float *freq_x, char *sentido_x, float *tempo)
{ 
	int divisao_int;
	float restante;
       	printf("Entrei em calculos\n");	
	for (int i = 0; i < numberOfLines; i++)
	{
		printf("Entrei no for\n");
		tag = 0; 
		time = 0;
		freq_atual = freq_x[i];
		sentido_atual = sentido_x[i];
		tempo_atual = tempo[i];
		if (freq_x[i] == 0)
		{
			tag = 1;
			time = tempo[i] + 1;
			delay (tempo[i]);
			continue;  
		}
		tempo_freq_atual = 1/freq_x[i];
		divisao_int = tempo[i]/tempo_freq_atual;
		restante = tempo[i] - (divisao_int * tempo_freq_atual);
		tempo_rest = restante/divisao_int;
		printf("Tag: %d\n", tag);
		configuracao_sinal(freq_x[i]);
		while (tag == 0) 
		{	
			printf("Esperando...\n");
			pause();
		}
	}
	return 0;
}

  
void controla_motor()
{
  printf("Entrei no controlamotor\n");
  //interval = freq_atual;
  printf("Tempo total (time): %f\n", time);
  if (time >= tempo_atual)
{
        printf("Tempo esgotado\n");
        escrever_saidas(LOW, LOW, LOW, LOW);
        it_val.it_value.tv_sec = 0;
	it_val.it_value.tv_usec = 0;
	it_val.it_interval = it_val.it_value;
	setitimer(ITIMER_REAL, &it_val, NULL);
	tag = 1;
        return;
} 
  //unsigned long currentMillis = millis();
 
 // if(currentMillis - previousMillis > interval) 
    //previousMillis = currentMillis;   
  printf("Ponto x\n");
  if (sentido_atual == 0)   
      sentido_horario();
  if (sentido_atual == 1) 
      sentido_antihorario();
  
  time += tempo_freq_atual + tempo_rest;
}

void sentido_horario()
{
	printf("Sentido horario ok\n");
   if (n >= 3)
      n = 0;
   else n++;
   if (n == 0)
      ledState1 = LOW;
    else
       ledState1 = HIGH;
    if (n == 1)
      ledState2 = LOW;
    else
       ledState2 = HIGH;
    if (n == 2)
      ledState3 = LOW;
    else
       ledState3 = HIGH;
    if (n == 3)
      ledState4 = LOW;
    else
       ledState4 = HIGH;
    escrever_saidas(ledState1, ledState2, ledState3, ledState4);
}

void sentido_antihorario()
{
	printf("Sentido antihorario ok\n");
   if (m >= 3)
   	m = 0;
   else m++;
   if (m == 0)
      ledState4 = LOW;
    else
       ledState4 = HIGH;
    if (m == 1)
      ledState3 = LOW;
    else
       ledState3 = HIGH;
    if (m == 2)
      ledState2 = LOW;
    else
       ledState2 = HIGH;
    if (m == 3)
      ledState1 = LOW;
    else
       ledState1 = HIGH;
  escrever_saidas(ledState1, ledState2, ledState3, ledState4);
}

void escrever_saidas(int estado1, int estado2, int estado3, int estado4)
{
   digitalWrite(8, estado1);
   digitalWrite(9, estado2); 
   digitalWrite(7, estado3); 
   digitalWrite(0, estado4);
   printf("Estados: %d, %d, %d, %d\n", estado1, estado2, estado3, estado4);
} 


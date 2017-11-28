#include "read_gcode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <signal.h>

const int rpm_max = 60;

// arrays com os valores
float Xs[MAX_LEN];
float Ys[MAX_LEN];
float Zs[MAX_LEN];
float tempo[MAX_LEN];
float freq_x[MAX_LEN];
float freq_y[MAX_LEN];
float freq_z[MAX_LEN];
int sentido_x[MAX_LEN];
int sentido_y[MAX_LEN];
int sentido_z[MAX_LEN];
int numberOfLines;
int soma_rasp[MAX_LEN];
// same position for each value
int count = 0;

// Intern functions prototypes
int getCoordinates(char * line);
void readGCode();

int get_freq_sentido()
{
	int i;
	float tempo_x, tempo_y, tempo_z, rpm_x, rpm_y, rpm_z;

	readGCode();


	for(i=0; i < numberOfLines; i++)
	{
		if (i == 0) // Se for a primeira vez do loop, não há posição anterior, logo mede-se só com a primeira posição
		{
			tempo_x = Xs[i]/rpm_max;
			tempo_y = Ys[i]/rpm_max;
			tempo_z = Zs[i]/rpm_max;
		}
		else // Caso contrário, mede-se a diferença entre as duas posições na fórmula: vel = espaço/tempo
		{
			sentido_x[i] = sentido_y[i] = sentido_z[i] = 0;
			tempo_x = fabs((Xs[i]-Xs[i-1])/rpm_max);
			tempo_y = fabs((Ys[i]-Ys[i-1])/rpm_max);
			tempo_z = fabs((Zs[i]-Zs[i-1])/rpm_max);
		}

		if (tempo_x < 0) // Esses ifs são para caso a diferença seja negativa (ou seja, o motor tem que voltar - girar no sentido antihorário -)
			sentido_x[i] = 1;
		if (tempo_y < 0)
			sentido_y[i] = 1;
		if (tempo_z < 0)
			sentido_z[i] = 1;

        // Esses ifs são para escolher o maior tempo necessário entre os três motores. Assim, o maior tempo é o tempo que será utilizado para os três
		if (tempo_x > tempo_y && tempo_x > tempo_z)
			tempo[i] = tempo_x;
		if (tempo_y > tempo_x && tempo_y > tempo_z)
			tempo[i] = tempo_y;
		if (tempo_z > tempo_x && tempo_z > tempo_y)
			tempo[i] = tempo_z;
		

		if (tempo[i] == 0)
			continue;

		if (i == 0) // Mesma lógica do if (i == 0) de cima
		{
			rpm_x = Xs[i]/tempo[i];
			rpm_y = Ys[i]/tempo[i];
			rpm_z = Zs[i]/tempo[i];
		}
		else // agora calcula-se a velocidade de cada um de acordo com o que tem que andar no tempo já determinado acima
		{
			rpm_x = fabs((Xs[i] - Xs[i-1])/tempo[i]);
			rpm_y = fabs((Ys[i] - Ys[i-1])/tempo[i]);
			rpm_z = fabs((Zs[i] - Zs[i-1])/tempo[i]);
		}

		freq_x[i] = (rpm_x * 200)/60; // essa fórmula para calcular a frequência está escrita nos comentários na parte de cima do código
		freq_y[i] = (rpm_y * 200)/60;
		freq_z[i] = (rpm_z * 200)/60;

		freq_x[i] = 5 * freq_x[i];
		freq_y[i] = 5 * freq_y[i];
		freq_z[i] = 5 * freq_z[i];

		soma_rasp[i] = freq_x[i] + freq_y[i] + freq_z[i];
		}


	return 0;
}

//http://man7.org/linux/man-pages/man3/strtol.3.html
  int getCoordinates(char * line)
  {
    char *token;
    /* get the first token */
    token = strtok(line, " ");

    /* walk through other tokens */
    while( token != NULL ){
      //printf( "%s\n", token );
      if(*token == 'X'){
        token = strtok(NULL, " ");
        float x = atof(token);

        Xs[count] = x;
        //printf("X = %f\n",x);
      } else if(*token == 'Y'){
        token = strtok(NULL, " ");
        float y = atof(token);

        Ys[count] = y;
        //printf("Y = %f\n",y);
      }else if(*token == 'Z'){
        token = strtok(NULL, " ");
        float z = atof(token);

        Zs[count] = z;
        //printf("Z = %f\n",z);
      }

      token = strtok(NULL, " ");
    }

    count++;
  }


void readGCode()
{
  //https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
  //https://stackoverflow.com/questions/13399594/how-to-extract-numbers-from-string-in-c
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  numberOfLines = 0;

  fp = fopen("gcode", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // First value is 0
  Xs[count] = 0;
  Ys[count] = 0;
  Zs[count] = 0;

  while ((read = getline(&line, &len, fp)) != -1) {

    getCoordinates(line);

    // Set Next values so that it will not be null
    Xs[count] = Xs[count-1];
    Ys[count] = Ys[count-1];
    Zs[count] = Zs[count-1];

    numberOfLines++;
    //printf("Read X = %f Y = %f Z = %f\n",Xs[count],Ys[count],Zs[count]);
  }

  fclose(fp);
  if (line)
      free(line);
    return;
}




/*#include "read_gcode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <signal.h>

const int rpm_max = 90;
struct Instrucao instrucao[500];
int numberOfLines;

// same position for each value
int count = 0;

// Intern functions prototypes
int getCoordinates(char * line);
void readGCode();

int get_freq_sentido()
{
	int i;
	float tempo_x, tempo_y, tempo_z, rpm_x, rpm_y, rpm_z;

	readGCode();

	for(i=0; i < numberOfLines; i++)
	{
		if (i == 0) // Se for a primeira vez do loop, não há posição anterior, logo mede-se só com a primeira posição
		{
			tempo_x = instrucao[i].motores[0].posicao/rpm_max;
			tempo_y = instrucao[i].motores[1].posicao/rpm_max;
			tempo_z = instrucao[i].motores[2].posicao/rpm_max;
		}
		else // Caso contrário, mede-se a diferença entre as duas posições na fórmula: vel = espaço/tempo
		{
			//instrucao[i].motores[0].sentido = instrucao[i].motores[1].sentido = instrucao[i].motores[2].sentido = 0;
			tempo_x = fabs((instrucao[i].motores[0].posicao - instrucao[i-1].motores[0].posicao)/rpm_max);
			tempo_y = fabs((instrucao[i].motores[1].posicao - instrucao[i-1].motores[1].posicao)/rpm_max);
			tempo_z = fabs((instrucao[i].motores[2].posicao - instrucao[i-1].motores[2].posicao)/rpm_max);
		}

		/*if (tempo_x < 0) // Esses ifs são para caso a diferença seja negativa (ou seja, o motor tem que voltar - girar no sentido antihorário -)
			 instrucao[i].motores[0].sentido = 1;
		if (tempo_y < 0)
			 instrucao[i].motores[1].sentido = 1;
		if (tempo_z < 0)
			 instrucao[i].motores[2].sentido = 1;

        // Esses ifs são para escolher o maior tempo necessário entre os três motores. Assim, o maior tempo é o tempo que será utilizado para os três
		if (tempo_x > tempo_y && tempo_x > tempo_z)
			 instrucao[i].tempo = tempo_x;
		if (tempo_y > tempo_x && tempo_y > tempo_z)
			 instrucao[i].tempo = tempo_y;
		if (tempo_z > tempo_x && tempo_z > tempo_y)
			 instrucao[i].tempo = tempo_z;

		if (instrucao[i].tempo == 0)
			continue;

		if (i == 0) // Mesma lógica do if (i == 0) de cima
		{
			rpm_x = instrucao[i].motores[0].posicao/instrucao[i].tempo;
			rpm_y = instrucao[i].motores[1].posicao/instrucao[i].tempo;
			rpm_z = instrucao[i].motores[2].posicao/instrucao[i].tempo;
		}
		else // agora calcula-se a velocidade de cada um de acordo com o que tem que andar no tempo já determinado acima
		{
			rpm_x = fabs((instrucao[i].motores[0].posicao - instrucao[i-1].motores[0].posicao)/instrucao[i].tempo);
			rpm_y = fabs((instrucao[i].motores[1].posicao - instrucao[i-1].motores[1].posicao)/instrucao[i].tempo);
			rpm_z = fabs((instrucao[i].motores[2].posicao - instrucao[i-1].motores[2].posicao)/instrucao[i].tempo);
		}

		instrucao[i].motores[0].frequencia = (rpm_x * 200)/60; // essa fórmula para calcular a frequência está escrita nos comentários na parte de cima do código
		instrucao[i].motores[1].frequencia = (rpm_y * 200)/60;
		instrucao[i].motores[2].frequencia = (rpm_z * 200)/60;

		instrucao[i].soma_rasp = instrucao[i].motores[0].frequencia + instrucao[i].motores[1].frequencia + instrucao[i].motores[2].frequencia;

		}


	return 0;
}

//http://man7.org/linux/man-pages/man3/strtol.3.html
  int getCoordinates(char * line)
  {
    char *token;
    /* get the first token 
    token = strtok(line, " ");

    /* walk through other tokens 
    while( token != NULL ){
      //printf( "%s\n", token );
      if(*token == 'X'){
        token = strtok(NULL, " ");
        float x = atof(token);

        instrucao[count].motores[0].posicao = x;
        //printf("X = %f\n",x);
      } else if(*token == 'Y'){
        token = strtok(NULL, " ");
        float y = atof(token);

        instrucao[count].motores[1].posicao = y;
        //printf("Y = %f\n",y);
      }else if(*token == 'Z'){
        token = strtok(NULL, " ");
        float z = atof(token);

        instrucao[count].motores[2].posicao = z;
        //printf("Z = %f\n",z);
      }

      token = strtok(NULL, " ");
    }

    count++;
  }


void readGCode()
{
  //https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
  //https://stackoverflow.com/questions/13399594/how-to-extract-numbers-from-string-in-c
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  numberOfLines = 0;

  fp = fopen("gcode", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // First value is 0

  instrucao[count].motores[0].posicao = 0;
  instrucao[count].motores[1].posicao = 0;
  instrucao[count].motores[2].posicao = 0;

  while ((read = getline(&line, &len, fp)) != -1) {

    getCoordinates(line);

    // Set Next values so that it will not be null
    instrucao[count].motores[0].posicao = instrucao[count-1].motores[0].posicao;
    instrucao[count].motores[1].posicao = instrucao[count-1].motores[1].posicao;
    instrucao[count].motores[2].posicao = instrucao[count-1].motores[2].posicao;

    numberOfLines++;
    //printf("Read X = %f Y = %f Z = %f\n",Xs[count],Ys[count],Zs[count]);
  }

  fclose(fp);
  if (line)
      free(line);
    return;
}*/



#include "read_gcode.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Informações para não esquecer:
Tamanho eixo x: 2*pi*r = 2*3.1415*100 = 628.3 mm
Tamanho eixo y: 1.2 m = 1200 mm
Tamanho eixo z: 20 cm = 200 mm
Cálculo velocidade: rpm = (frequencia x 60)/200*(nº de divisão de passo)
Sentido: 0 -> horário
	 1 -> anti-horário
As variáveis que serão passadas para o ATMega serão: freq_x,freq_y,freq_z e sentido_x, sentido_y, sentido_z, tempo
Xs[3] = {123.00, 120.00, 243.00}, Ys[3] = {10.00, 1000.00, 920.00}, Zs[3] = {40.00, 40.00, 40.00},
	 1 -> anti-horário
As variáveis que serão passadas para o ATMega serão: freq_x,freq_y,freq_z e sentido_x, sentido_y, sentido_z
As variáveis que serão passadas para o ATMega serão: freq_x,freq_y,freq_z e sentido_x, sentido_y, sentido_z, tempo*/


#define freq_max 300
#define rpm_max 90

int main()
{
	int i;
	float tempo, rpm_x, rpm_y, rpm_z, freq_x, freq_y, freq_z;
	float tempo_x, tempo_y, tempo_z;
	int sentido_x=0, sentido_y=0, sentido_z=0; // Variáveis que controlarão o sentido dos motores
	printf("GETTING GCODE INPUT\n");

	readGCode();

	printf("START WINDING\n");

	for(i=0; i < 10; i++)
	{
		printf("INPUT %d\n",i);

		if (i == 0) // Se for a primeira vez do loop, não há posição anterior, logo mede-se só com a primeira posição
		{
			tempo_x = Xs[i]/rpm_max;
			tempo_y = Ys[i]/rpm_max;
			tempo_z = Zs[i]/rpm_max;
		}
		else // Caso contrário, mede-se a diferença entre as duas posições na fórmula: vel = espaço/tempo
		{
			sentido_x = sentido_y = sentido_z = 0;
			tempo_x = (Xs[i]-Xs[i-1])/rpm_max;
			tempo_y = (Ys[i]-Ys[i-1])/rpm_max;
			tempo_z = (Zs[i]-Zs[i-1])/rpm_max;
		}

		if (tempo_x < 0) // Esses ifs são para caso a diferença seja negativa (ou seja, o motor tem que voltar - girar no sentido antihorário -)
		{
			tempo_x *= -1;
			sentido_x = 1;
		}
		if (tempo_y < 0)
		{
			tempo_y *= -1;
			sentido_y = 1;
		}
		if (tempo_z < 0)
		{
			tempo_z *= -1;
			sentido_z = 1;
		}

		printf("Tempo em x: %f, Tempo em y: %f, Tempo em z:%f\n", tempo_x, tempo_y, tempo_z); // Todos esses printfs vão ser apagados, é só pra testar as saídas

        // Esses ifs são para escolher o maior tempo necessário entre os três motores. Assim, o maior tempo é o tempo que será utilizado para os três
		if (tempo_x > tempo_y && tempo_x > tempo_z)
			tempo = tempo_x;
		if (tempo_y > tempo_x && tempo_y > tempo_z)
			tempo = tempo_y;
		if (tempo_z > tempo_x && tempo_z > tempo_y)
			tempo = tempo_z;
		printf("Tempo que será utilizado: %f\n", tempo);
		tempo += 0.1; // Eu aumentei o tempo em 0.1 para não ser necessário usar a frequência máxima do motor, mas acho que depois vou colocar outra lógica

		if (i == 0) // Mesma lógica do if (i == 0) de cima
		{
			rpm_x = Xs[i]/tempo;
			rpm_y = Ys[i]/tempo;
			rpm_z = Zs[i]/tempo;
		}
		else // agora calcula-se a velocidade de cada um de acordo com o que tem que andar no tempo já determinado acima
		{
			rpm_x = (Xs[i] - Xs[i-1])/tempo;
			rpm_y = (Ys[i] - Ys[i-1])/tempo;
			rpm_z = (Zs[i] - Zs[i-1])/tempo;
		}
		if (rpm_x < 0)
			rpm_x *= -1;
		if (rpm_y < 0)
			rpm_y *= -1;
		if (rpm_z < 0)
			rpm_z *= -1;

		printf("RPM em x: %f\n", rpm_x);
		printf("RPM em y: %f\n", rpm_y);
		printf("RPM em z: %f\n", rpm_z);

		freq_x = (rpm_x * 200)/60; // essa fórmula para calcular a frequência está escrita nos comentários na parte de cima do código
		freq_y = (rpm_y * 200)/60;
		freq_z = (rpm_z * 200)/60;

		printf("Frequência em x: %f\n", freq_x);
		printf("Frequência em y: %f\n", freq_y);
		printf("Frequência em z: %f\n", freq_z);

		printf("Sentido que o motor vai girar em x: %d\n", sentido_x);
		printf("Sentido que o motor vai girar em y: %d\n", sentido_y);
		printf("Sentido que o motor vai girar em z: %d\n", sentido_z);
	}

	return 0;
}

#include <stdio.h>
#include <stdlib.h>


/* Informações para não esquecer:
Tamanho eixo x: 2*pi*r = 2*3.1415*100 = 628.3 mm
Tamanho eixo y: 1.2 m = 1200 mm
Tamanho eixo z: 20 cm = 200 mm 
Cálculo velocidade: rpm = (frequencia x 60)/200*(nº de divisão de passo)
Sentido: 0 -> horário
	 1 -> anti-horário	
As variáveis que serão passadas para o ATMega serão: freq_x,freq_y,freq_z e sentido_x, sentido_y, sentido_z*/

#define freq_max 300
#define rpm_max 90

int main()
{
	double x[3] = {123.00, 120.00, 243.00}, y[3] = {10.00, 1000.00, 920.00}, z[3] = {40.00, 40.00, 40.00}, tempo, rpm_x, rpm_y, rpm_z, freq_x, freq_y, freq_z;
	double tempo_x, tempo_y, tempo_z;
	int sentido_x=0, sentido_y=0, sentido_z=0;

	for(int i=0; i < 3; i++)
	{
		if (i == 0)
		{
			tempo_x = x[i]/rpm_max;
			tempo_y = y[i]/rpm_max;
			tempo_z = z[i]/rpm_max;
		}
		else
		{	
			sentido_x = sentido_y = sentido_z = 0;		
			tempo_x = (x[i]-x[i-1])/rpm_max;
			tempo_y = (y[i]-y[i-1])/rpm_max;
			tempo_z = (z[i]-z[i-1])/rpm_max;
		}
		if (tempo_x < 0)
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

		printf("Tempo em x: %f, Tempo em y: %f, Tempo em z:%f\n", tempo_x, tempo_y, tempo_z);

		if (tempo_x > tempo_y && tempo_x > tempo_z)
			tempo = tempo_x;
		if (tempo_y > tempo_x && tempo_y > tempo_z)
			tempo = tempo_y;
		if (tempo_z > tempo_x && tempo_z > tempo_y)
			tempo = tempo_z;
		printf("Tempo que será utilizado: %f\n", tempo);
		tempo += 0.1;

		if (i == 0)
		{
			rpm_x = x[i]/tempo;
			rpm_y = y[i]/tempo;
			rpm_z = z[i]/tempo;
		}
		else
		{
			rpm_x = (x[i] - x[i-1])/tempo;
			rpm_y = (y[i] - y[i-1])/tempo;
			rpm_z = (z[i] - z[i-1])/tempo;
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
		
		freq_x = (rpm_x * 200)/60;
		freq_y = (rpm_y * 200)/60;
		freq_z = (rpm_z * 200)/60;
		
		printf("Frequência em x: %f\n", freq_x);
		printf("Frequência em y: %f\n", freq_y);
		printf("Frequência em z: %f\n", freq_z);

		printf("Sentido que o motor vai girar em x: %d\n", sentido_x);
		printf("Sentido que o motor vai girar em y: %d\n", sentido_y);
		printf("Sentido que o motor vai girar em z: %d\n", sentido_z);
	}

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


int main(void) {
    get_freq_sentido();

    if(serial_init() == -1) {
        printf("error to initialize serial port\n");
        exit(1);
    }
	numberOfLines = 10;
    for(int n = 0; n < numberOfLines; n++) {
	printf("Entrei no for.\n");
	while(serial_read() != 100)
		printf("Esperando receber a tag do Arduino\n"); 
	if (n == 0)
		serial_write("ABC", 3 * sizeof(char));

	printf("Saí do ABC\n");	

	//serial_write((char *) &instrucao[n], sizeof(struct Instrucao));
	serial_write((char *) &freq_x[n], sizeof(float));
	serial_write((char *) &freq_y[n], sizeof(float));
	serial_write((char *) &freq_z[n], sizeof(float));
	serial_write((char *) &tempo[n], sizeof(float));
	serial_write((char *) &Xs[n], sizeof(float));
	serial_write((char *) &Ys[n], sizeof(float));
	serial_write((char *) &Zs[n], sizeof(float));
	serial_write((char *) &soma_rasp[n], sizeof(int));
	delay(700);
	//if (serial_read() == 'N')
	//{
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
			delay(700);
		}
	delay(tempo[n]*1000);
	//}
	printf("N: %d\n", n);
	printf("Tempo: %f\n", tempo[n]);
	/*printf("Frequencia x: %f\n", instrucao[n].motores[0].frequencia);
	printf("Frequencia y: %f\n", instrucao[n].motores[1].frequencia);
	printf("Frequencia z: %f\n", instrucao[n].motores[2].frequencia);
	printf("Soma_rasp: %f\n", instrucao[n].soma_rasp);
	printf("Tempo: %f\n", instrucao[n].tempo);
	printf("Posicao x: %f\n", instrucao[n].motores[0].posicao);
	printf("Posicao y: %f\n", instrucao[n].motores[1].posicao);
	printf("Posicao z: %f\n", instrucao[n].motores[2].posicao);*/

}
    serial_close();
}

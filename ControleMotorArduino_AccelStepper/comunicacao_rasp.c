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
    float freqx = 0, freqy = 0, freqz = 0, sentx = 0, senty = 0, sentz = 0, temp = 0, x = 0, y = 0, z = 0;

    if(serial_init() == -1) {
        printf("error to initialize serial port\n");
        exit(1);
    }
	
	while(serial_read() == -1) // Essa primeira vez é só para mandar zero pois as informações estavam se perdendo de primeira.
		printf("Esperando receber a tag do Arduino\n"); 
	printf("Sai do while.\n");
	serial_write("ABC", 3 * sizeof(char));

	printf("Saí do ABC\n");	
        serial_write((char *) &freqx, sizeof(float));
	serial_write((char *) &freqy, sizeof(float));
	serial_write((char *) &freqz, sizeof(float));
	serial_write((char *) &sentx, sizeof(char));
	serial_write((char *) &senty, sizeof(char));
	serial_write((char *) &sentz, sizeof(char));
        serial_write((char *) &temp, sizeof(float));
	serial_write((char *) &x, sizeof(float));
	serial_write((char *) &y, sizeof(float));
	serial_write((char *) &z, sizeof(float));
 
    for(int n = 0; n < numberOfLines; n++) {
	printf("Entrei no for.\n");
	while(serial_read() == -1)
		printf("Esperando receber a tag do Arduino\n"); 
	printf("Sai do while.\n");
	serial_write("ABC", 3 * sizeof(char));

	printf("Saí do ABC\n");	
        serial_write((char *) &freq_x[n], sizeof(float));
	serial_write((char *) &freq_y[n], sizeof(float));
	serial_write((char *) &freq_z[n], sizeof(float));
	serial_write((char *) &sentido_x[n], sizeof(char));
	serial_write((char *) &sentido_y[n], sizeof(char));
	serial_write((char *) &sentido_z[n], sizeof(char));
        serial_write((char *) &tempo[n], sizeof(float));
	serial_write((char *) &Xs[n], sizeof(float));
	serial_write((char *) &Ys[n], sizeof(float));
	serial_write((char *) &Zs[n], sizeof(float));

	printf("n: %d\n", n);
	printf("Tempo: %f\n", tempo[n]);
}
    serial_close();
}

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

#define send_var 2

int main(void) {
    get_freq_sentido();

    if(serial_init() == -1) {
        printf("error to initialize serial port\n");
        exit(1);
    }
    numberOfLines = 3;
    for(int n = 0; n < send_var; n++) {
        if (n == 0) {
            serial_write("N", sizeof(char));
            serial_write((char *) &numberOfLines, sizeof(int));
        }
        if (n == 1) {
            serial_write("X", sizeof(char));
	    serial_write((char *) freq_x, numberOfLines * sizeof(freq_x[0]));
        }
        /*if (n == 2) {
             serial_write("Y", sizeof(char));
             serial_write((char *) freq_y, numberOfLines * sizeof(freq_y[0]));
         }
         if (n == 3) {
             serial_write("Z", sizeof(char));
             serial_write((char *) freq_z, numberOfLines * sizeof(freq_z[0]));
         }
         if (n == 4) {
             serial_write("A", sizeof(char));
             serial_write((char *) sentido_x, numberOfLines * sizeof(sentido_x[0]));
         }
         if (n == 5) {
             serial_write("B", sizeof(char));
             serial_write((char *) sentido_y, numberOfLines * sizeof(sentido_y[0]));
         }
         if (n == 6) {
             serial_write("C", sizeof(char));
             serial_write((char *) sentido_z, numberOfLines * sizeof(sentido_z[0]));
         }
         if (n == 7) {
             serial_write("T", sizeof(char));
             serial_write((char *) tempo, numberOfLines * sizeof(tempo[0]));
         }*/
    }
	for (int j = 0; j < numberOfLines; j++){
		printf("Frequência em x: %f\n", freq_x[j]);
		printf("Linhas: %d\n", numberOfLines);
	}
    serial_close();
}

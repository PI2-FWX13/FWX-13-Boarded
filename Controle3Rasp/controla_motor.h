#ifndef CONTROLA_MOTOR  // guardas de cabeçalho, impedem inclusões cíclicas
#define CONTROLA_MOTOR

// Bibliotecas
#include "read_gcode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#include <linux/socket.h>
#include <time.h>
#include <sys/time.h>

// Definicoes
#define HIGH 1
#define LOW 0

// Variáveis externas
extern float tempo_rest_x, tempo_tot_x, freq_atual_x, tempo_atual_x, tempo_rest_y, tempo_tot_y, freq_atual_y, tempo_atual_y, tempo_rest_z, tempo_tot_z, freq_atual_z, tempo_atual_z, tempo_freq_atual_x, tempo_freq_atual_y, tempo_freq_atual_z;
extern int tag, ledState1, ledState2, ledState3, ledState4, ledState5, ledState6, ledState7, ledState8, ledState9, ledState10, ledState11, ledState12, m, n, o, p, q, r, tag_x, tag_y, tag_z;
extern char sentido_atual_x, sentido_atual_y, sentido_atual_z;

// Protótipos
int calculos_x(float freq_x, float sentido_x, float tempo);
void controla_motor_x();
void sentido_horario_x();
void sentido_antihorario_x();
void escrever_saidas_x(int estado1, int estado2, int estado3, int estado4);
int calculos_y(float freq_y, float sentido_y, float tempo);
void controla_motor_y();
void sentido_horario_y();
void sentido_antihorario_y();
void escrever_saidas_y(int estado5, int estado6, int estado7, int estado8);
int calculos_z(float freq_z, float sentido_z, float tempo);
void controla_motor_z();
void sentido_horario_z();
void sentido_antihorario_z();
void escrever_saidas_z(int estado9, int estado10, int estado11, int estado12);


#endif

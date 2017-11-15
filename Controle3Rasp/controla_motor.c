#include "controla_motor.h"
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

float tempo_rest_x, freq_atual_x, tempo_atual_x, tempo_rest_y, freq_atual_y, tempo_atual_y, tempo_rest_z, freq_atual_z, tempo_atual_z, tempo_freq_atual_x, tempo_freq_atual_y, tempo_freq_atual_z;
char sentido_atual_x, sentido_atual_y, sentido_atual_z;
float tempo_tot_x = 0, tempo_tot_y = 0, tempo_tot_z = 0;
int tag, ledState1 = LOW, ledState2 = LOW, ledState3 = LOW, ledState4 = LOW, ledState5 = LOW, ledState6 = LOW, ledState7 = LOW, ledState8 = LOW, ledState9 = LOW, ledState10 = LOW, ledState11 = LOW, ledState12 = LOW, m = -1 , n = -1, o = -1, p = -1, q = -1, r = -1, tag_x = 0, tag_y = 0, tag_z = 0;




int calculos_x(float freq_x, float sentido_x, float tempo) 
{ 
	int divisao_int_x;
	float restante_x;
       	tempo_tot_x = 0;
	tag_x = 0;
	tempo_atual_x = tempo;
	freq_atual_x = freq_x;
	sentido_atual_x = sentido_x;
	if (freq_x == 0)
	{
		tempo_tot_x = tempo_atual_x + 1;
		//delay (tempo);
		if (tag_x == 0)
		{
			tag += 1;
			tag_x = 1;
			tempo_freq_atual_x = 0;
		}
		
		return 0;  
	}
	tempo_freq_atual_x = 1/freq_x;
	divisao_int_x = tempo/tempo_freq_atual_x;
	restante_x = tempo - (divisao_int_x * tempo_freq_atual_x);
	tempo_rest_x = restante_x/divisao_int_x;
	return 0;
}



void controla_motor_x()
{
  if (tempo_tot_x >= tempo_atual_x)
{
	escrever_saidas_x(LOW, LOW, LOW, LOW);
        if (tag_x == 0)
	{
		tag += 1;
		tag_x = 1;
	}
        return;
} 
 
  if (sentido_atual_x == 0)   
      sentido_horario_x();
  if (sentido_atual_x == 1) 
      sentido_antihorario_x();
  
  tempo_tot_x += tempo_freq_atual_x + tempo_rest_x;
}

void sentido_horario_x()
{
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
    escrever_saidas_x (ledState1, ledState2, ledState3, ledState4);
}

void sentido_antihorario_x()
{
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
  escrever_saidas_x(ledState1, ledState2, ledState3, ledState4);
}

void escrever_saidas_x(int estado1, int estado2, int estado3, int estado4)
{
   //digitalWrite(8, estado1);
   //digitalWrite(9, estado2); 
   //digitalWrite(7, estado3); 
   //digitalWrite(0, estado4);
} 

int calculos_y(float freq_y, float sentido_y, float tempo)
{ 
	int divisao_int_y;
	float restante_y;
       	tempo_tot_y = 0;
	tag_y = 0;
	tempo_atual_y = tempo;
	freq_atual_y = freq_y;
	sentido_atual_y = sentido_y;
	if (freq_y == 0)
	{
		tempo_tot_y = tempo_atual_y + 1;
		//delay (tempo);
		if (tag_y == 0)
		{
			tag += 1;
			tag_y = 1;
		}
		return 0;  
	}
	tempo_freq_atual_y = 1/freq_y;
	divisao_int_y = tempo/tempo_freq_atual_y;
	restante_y = tempo - (divisao_int_y * tempo_freq_atual_y);
	tempo_rest_y = restante_y/divisao_int_y;
	return 0;
}



void controla_motor_y()
{
  if (tempo_tot_y >= tempo_atual_y)
  {
        escrever_saidas_y(LOW, LOW, LOW, LOW);
        if (tag_y == 0)
	{
		tag += 1;
		tag_y = 1;
	}
        return;
  } 
 
  if (sentido_atual_y == 0)   
      sentido_horario_y();
  if (sentido_atual_y == 1) 
      sentido_antihorario_y();
  
  tempo_tot_y += tempo_freq_atual_y + tempo_rest_y;
}

void sentido_horario_y()
{
   if (o >= 3)
      o = 0;
   else o++;
   if (o == 0)
      ledState5 = LOW;
    else
       ledState5 = HIGH;
    if (o == 1)
      ledState6 = LOW;
    else
       ledState6 = HIGH;
    if (o == 2)
      ledState7 = LOW;
    else
       ledState7 = HIGH;
    if (o == 3)
      ledState8 = LOW;
    else
       ledState8 = HIGH;
    escrever_saidas_y(ledState5, ledState6, ledState7, ledState8);
}

void sentido_antihorario_y()
{
   if (p >= 3)
   	p = 0;
   else p++;
   if (p == 0)
      ledState8 = LOW;
    else
       ledState8 = HIGH;
    if (p == 1)
      ledState7 = LOW;
    else
       ledState7 = HIGH;
    if (p == 2)
      ledState6 = LOW;
    else
       ledState6 = HIGH;
    if (p == 3)
      ledState5 = LOW;
    else
       ledState5 = HIGH;
  escrever_saidas_y(ledState5, ledState6, ledState7, ledState8);
}

void escrever_saidas_y(int estado5, int estado6, int estado7, int estado8)
{
   //digitalWrite(8, estado1);
   //digitalWrite(9, estado2); 
   //digitalWrite(7, estado3); 
   //digitalWrite(0, estado4);
}

int calculos_z(float freq_z, float sentido_z, float tempo)
{ 
	int divisao_int_z;
	float restante_z;
       	tempo_tot_z = 0;
	tag_z = 0;
	tempo_atual_z = tempo;
	freq_atual_z = freq_z;
	sentido_atual_z = sentido_z;
	if (freq_z == 0)
	{
		tempo_tot_z = tempo_atual_z + 1;
		//delay (tempo);
		if (tag_z == 0)
		{
			tag += 1;
			tag_z = 1;
		}
		return 0;  
	}
	tempo_freq_atual_z = 1/freq_z;
	divisao_int_z = tempo/tempo_freq_atual_z;
	restante_z = tempo - (divisao_int_z * tempo_freq_atual_z);
	tempo_rest_z = restante_z/divisao_int_z;
	return 0;
}



void controla_motor_z()
{
  if (tempo_tot_z >= tempo_atual_z)
  {
        escrever_saidas_z(LOW, LOW, LOW, LOW);
        if (tag_z == 0)
	{
		tag += 1;
		tag_z = 1;
	}
        return;
  } 
 
  if (sentido_atual_z == 0)   
      sentido_horario_z();
  if (sentido_atual_z == 1) 
      sentido_antihorario_z();
  
  tempo_tot_z += tempo_freq_atual_z + tempo_rest_z;
}

void sentido_horario_z()
{
   if (q >= 3)
      q = 0;
   else q++;
   if (q == 0)
      ledState9 = LOW;
    else
       ledState9 = HIGH;
    if (q == 1)
      ledState10 = LOW;
    else
       ledState10 = HIGH;
    if (q == 2)
      ledState11 = LOW;
    else
       ledState11 = HIGH;
    if (q == 3)
      ledState12 = LOW;
    else
       ledState12 = HIGH;
    escrever_saidas_z(ledState9, ledState10, ledState11, ledState12);
}

void sentido_antihorario_z()
{
   if (r >= 3)
      r = 0;
   else r++;
   if (r == 0)
      ledState12 = LOW;
    else
       ledState12 = HIGH;
    if (r == 1)
      ledState11 = LOW;
    else
       ledState11 = HIGH;
    if (r == 2)
      ledState10 = LOW;
    else
       ledState10 = HIGH;
    if (r == 3)
      ledState9 = LOW;
    else
       ledState9 = HIGH;  
    escrever_saidas_z(ledState9, ledState10, ledState11, ledState12);
}

void escrever_saidas_z(int estado9, int estado10, int estado11, int estado12)
{
   //digitalWrite(8, estado1);
   //digitalWrite(9, estado2); 
   //digitalWrite(7, estado3); 
   //digitalWrite(0, estado4);
}

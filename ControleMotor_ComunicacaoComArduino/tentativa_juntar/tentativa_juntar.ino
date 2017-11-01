// Bibliotecas
#include <TimerOne.h>
#include<SoftwareSerial.h>
SoftwareSerial serial1(6, 7); // RX, TX

// Structs
struct Motor {
  float frequencia;
  char sentido;
};

struct Instrucao {
  float tempo;
  struct Motor motores[3];
};
struct Instrucao instrucao = {};

//Definicoes
#define X 0
#define Y 1
#define Z 2

//Variaveis globais
char chave_mestre[] = "ABC";
char mandar_byte;
float tempo_rest, time = 0;
int tag, ledState1 = LOW, ledState2 = LOW, ledState3 = LOW, ledState4 = LOW, m = 0, n = 0, ack_bit = 1;
long interval, previousMillis = 0;
int numberOfLines;

// Prototipos
void encontrar_chave();
int eh_igual(char *chave);
void ler_instrucao();
float ler_float();
char ler_char();
int calculos(float freq_x, float sentido_x, float tempo);
void blink1();
void sentido_horario();
void sentido_antihorario();
void escrever_saidas(int estado1, int estado2, int estado3, int estado4);


// Setup
void setup()
{
  serial1.begin(9600);
  Serial.begin(9600);  
  Timer1.initialize();
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  delay(3000);
    
}

// Loop
void loop()
{
    if(ack_bit) {
        //  Serial.println("Entrei no if.");
          ler_instrucao();
    }
    else
    {
      calculos(instrucao.motores[X].frequencia, instrucao.motores[X].sentido, instrucao.tempo);
      ack_bit = 1;
    }
}

void ler_instrucao()
{
    //Serial.println("Entrei na funcao.");
    while(!serial1.available())
          serial1.write(5);
    
    encontrar_chave();
    instrucao.motores[X].frequencia = ler_float();
    instrucao.motores[Y].frequencia = ler_float();
    instrucao.motores[Z].frequencia = ler_float();
    instrucao.motores[X].sentido = ler_char();
    instrucao.motores[Y].sentido = ler_char();
    instrucao.motores[Z].sentido = ler_char();
    instrucao.tempo = ler_float();
    ack_bit = 0;    
     
    Serial.println("Dados");
    Serial.println(instrucao.motores[X].frequencia);
    Serial.println(instrucao.motores[Y].frequencia);
    Serial.println(instrucao.motores[Z].frequencia);
    Serial.println((int)instrucao.motores[X].sentido);
    Serial.println((int)instrucao.motores[Y].sentido);
    Serial.println((int)instrucao.motores[Z].sentido);
    Serial.println(instrucao.tempo);
    
}

void encontrar_chave()
{
  char chave[3];
  while(!serial1.available());
  for (int i = 0; i < 3; i++) 
  {
      chave[i] = serial1.read();
      //Serial.println(chave[i]);
  }
  while(!eh_igual(chave))
  {
     for (int i = 0; i < 2; i++)
       chave[i] = chave[i+1];
     chave[2] = serial1.read();
     //Serial.println("Encontrando chave...");
  }
  //Serial.println("Chave encontrada.");
}
  
int eh_igual(char *chave)
{
  for (int i = 0; i < 3; i++)
  {
    if(chave[i] != chave_mestre[i])
        return 0;
  }
  return 1;
}

float ler_float()
{
  float dado_f;
  char c_pointer[sizeof(float)];
  for(int i = 0; i < sizeof(float); i++)
      *(c_pointer + i) = serial1.read();
  dado_f = *((float *) c_pointer);
  return dado_f;
}

char ler_char()
{
  char dado_c;
  dado_c = serial1.read();
  return dado_c;
}

int calculos(float freq_x, int sentido_x, float tempo)
{ 
  int divisao_int;
  float restante;  
  //Serial.println("Entrei no for");
  tag = 0; 
  time = 0;
  if (freq_x == 0)
  {
      tag = 1;
      time = tempo + 1;
      delay (tempo);
      return 0;  
  }
  divisao_int = tempo/freq_x;
  restante = tempo - (divisao_int * freq_x);
  tempo_rest = restante/divisao_int;
  while (tag == 0)      
      Timer1.attachInterrupt(blink1, freq_x*1000);
  return 0;
}

  
void blink1()
{
  float time;
  interval = instrucao.motores[X].frequencia;
  if (time >= instrucao.tempo)
{
        Serial.println("Tempo esgotado");
        escrever_saidas(LOW, LOW, LOW, LOW);
        tag = 1;
        Timer1.stop();
        ack_bit = 1;
        return;
} 
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) 
    previousMillis = currentMillis;   
  
  if (instrucao.motores[X].sentido == 0)   
      sentido_horario();
  if (instrucao.motores[X].sentido == 1) 
      sentido_antihorario();
  
  time += instrucao.motores[X].frequencia + tempo_rest;
}

void sentido_horario()
{
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
    if (m > 2)
      m = 0;
    else m++;
}

void sentido_antihorario()
{
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
  if (n > 2)
      n = 0;
    else n++;
}

void escrever_saidas(int estado1, int estado2, int estado3, int estado4)
{
   digitalWrite(3, estado1);
   digitalWrite(4, estado2); 
   digitalWrite(5, estado3); 
   digitalWrite(8, estado4);
} 


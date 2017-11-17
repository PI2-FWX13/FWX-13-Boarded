// Bibliotecas
#include <AccelStepper.h>
#include <MultiStepper.h>
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

AccelStepper stepperX(AccelStepper::DRIVER,1,2);
AccelStepper stepperY(AccelStepper::DRIVER,4,5);
AccelStepper stepperZ(AccelStepper::DRIVER,9,10);

//Definicoes
#define X 0
#define Y 1
#define Z 2


//Variaveis globais
char chave_mestre[] = "ABC";
char mandar_byte;
int tag, ack_bit = 1;
long interval;


// Prototipos
void encontrar_chave();
int eh_igual(char *chave);
void ler_instrucao();
float ler_float();
char ler_char();
int myDelay(long interval);


// Setup
void setup()
{
  serial1.begin(9600);
  Serial.begin(9600);  
  stepperX.setEnablePin(3);
  stepperY.setEnablePin(8);
  stepperZ.setEnablePin(11);

  stepperX.setMaxSpeed(250); // Freq (passo/s) maximo
  stepperY.setMaxSpeed(250);
  stepperZ.setMaxSpeed(250);
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
       stepperX.setSpeed(instrucao.motores[X].frequencia);
       stepperY.setSpeed(instrucao.motores[Y].frequencia);
       stepperZ.setSpeed(instrucao.motores[Z].frequencia);
       while(myDelay(instrucao.tempo));
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

int myDelay(long interval)
{
    long init = millis();
    while ((millis() - init) <= interval)
    {
        stepperX.runSpeed();
        stepperY.runSpeed();
        stepperZ.runSpeed();
    }
    return 0;    
}

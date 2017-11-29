#include <AccelStepper.h>
#include <MultiStepper.h>

#include <MultiStepper.h>

// Bibliotecas
#include <MultiStepper.h>
#include <SoftwareSerial.h>
#include <string.h>
#include <math.h>
SoftwareSerial serial1(2, 3); // RX, TX

// Structs
struct Motor {
  float frequencia;
  float posicao;
};

struct Instrucao {
  float tempo;
  struct Motor motores[3];
};
struct Instrucao instrucao = {};

AccelStepper stepperX(AccelStepper::FULL4WIRE, 4, 5, 6, 7); 
AccelStepper stepperY(AccelStepper::FULL4WIRE, 8, 9, 10, 11);
//AccelStepper stepperZ(AccelStepper::FULL4WIRE, 10, 11, 12, 13);

//Definicoes
#define X 0
#define Y 1
#define Z 2



//Variaveis globais
char chave_mestre[] = "ABC";
char mandar_byte;
int tag, ack_bit = 1, n = 0, p = 0;
long interval;
int soma_arduino, soma_rasp = 0;
int comp;


// Prototipos
void ler_variaveis();
void encontrar_chave();
int eh_igual(char *chave);
void ler_instrucao();
float ler_float();
int ler_int();
int myDelay(float interval);


// Setup
void setup()
{
  serial1.begin(9600);
  Serial.begin(9600);  
  //stepperX.setEnablePin(14); // Foi colocado os pinos de enable no mesmo pino ja que os tres vao estar habilitados ao mesmo tempo (e por falta de portas)
  //stepperY.setEnablePin(14); // 14 eh a porta A0 do arduino
  //stepperZ.setEnablePin(14);

  stepperX.setMaxSpeed(350); // Freq (passo/s) maximo
  stepperX.setAcceleration(1000);
  stepperX.setCurrentPosition(0);
  stepperY.setAcceleration(1000);
  stepperY.setMaxSpeed(350);
  stepperY.setCurrentPosition(0);
  //stepperZ.setMaxSpeed(250);
}

// Loop
void loop()
{
  
    if(ack_bit) {
          serial1.write(100);
          Serial.println("Entrei no ackbit.");
          //Serial.println(soma_rasp);
          ler_instrucao();
    }
    else
    {
       Serial.println("Estou no else\n");
       //Serial.println(instrucao.tempo);
       //Serial.println(stepperY.distanceToGo());
       //Serial.println(instrucao.motores[Y].posicao);
       //Serial.println(stepperY.currentPosition());
       stepperY.moveTo(instrucao.motores[Y].posicao);
       // PARTE QUE EU MODIFIQUEI
       //while(stepperY.isRunning());
       stepperX.moveTo(instrucao.motores[X].posicao);
       //Serial.println(stepperY.distanceToGo());
       //stepperX.setSpeed(+instrucao.motores[X].frequencia);
       //Serial.println(instrucao.motores[X].posicao - stepperX.currentPosition());
       if(instrucao.motores[X].posicao - stepperX.currentPosition() < 0)
           stepperX.setSpeed(-instrucao.motores[X].frequencia);
       else stepperX.setSpeed(instrucao.motores[X].frequencia);
       if(instrucao.motores[Y].posicao - stepperY.currentPosition() < 0)
            stepperY.setSpeed(-instrucao.motores[Y].frequencia);
       else stepperY.setSpeed(instrucao.motores[Y].frequencia);
       //Serial.println(instrucao.motores[X].posicao);   
       //Serial.println(instrucao.motores[Y].posicao);
       comp = 0;
       if (stepperY.distanceToGo() == 0)
           comp = 20000;
       else comp = abs(stepperX.distanceToGo()/stepperY.distanceToGo());
       Serial.println(comp);
       //stepperX.setSpeed(+instrucao.motores[X].frequencia);
       p = 0;
       if (stepperX.distanceToGo() == 0)
       {
         while (stepperY.distanceToGo() != 0)
         {
             Serial.println(stepperY.distanceToGo());     
             stepperY.runSpeed();
         }
       }
       else
       {
           while(stepperX.distanceToGo() != 0 && stepperY.distanceToGo() != 0)
           {
               Serial.println(stepperX.distanceToGo());   
               Serial.println(stepperY.distanceToGo());
               stepperX.runSpeed();
               p++;
               if (p == (comp+1)) //(comp + 1)
               {
                   stepperY.runSpeed();
                   p = 0;
               }
           }
       }
       Serial.println(stepperX.distanceToGo());   
       Serial.println(stepperY.distanceToGo());
       stepperX.setCurrentPosition(instrucao.motores[X].posicao);
       //Serial.println(stepperX.distanceToGo()); 
       //Serial.println(stepperY.distanceToGo());
       //stepperX.stop();
       //stepperY.stop();
       /*stepperY.setSpeed(instrucao.motores[Y].frequencia);
       while(stepperY.runSpeedToPosition());*/
       //stepperY.setSpeed(instrucao.motores[Y].frequencia);
       //stepperZ.moveTo(instrucao.motores[Z].posicao);
       //stepperX.setSpeed(instrucao.motores[X].frequencia);
       //stepperY.setSpeed(instrucao.motores[Y].frequencia);
       //stepperZ.setSpeed(instrucao.motores[Z].frequencia);
       //stepperZ.setAcceleration(1000.0);
       //stepperZ.run();
       //Serial.println(stepperY.isRunning());
       //Serial.println(stepperY.currentPosition());
       //while(myDelay(instrucao.tempo));
       //Serial.println(stepperX.isRunning());
       //stepperY.setCurrentPosition(instrucao.motores[Y].posicao);
       ack_bit = 1;  
       serial1.write(100);
       //Serial.println("Escrevi o numero na rasp");       
    }
}

void ler_instrucao()
{
    Serial.println("Entrei na funcao.");
    if (n == 0)
    {
      Serial.flush();
      while(!serial1.available())
          serial1.write(100);
      encontrar_chave();
      n = 1;
    }
    else
        serial1.write(100);
    
    Serial.println("Chamar leitura de variaveis");
    ler_variaveis();
        
    soma_arduino = instrucao.motores[X].frequencia + instrucao.motores[Y].frequencia + instrucao.motores[Z].frequencia;
    
    
    while(soma_arduino != soma_rasp)
    {
        serial1.write('N');
        ler_variaveis();
        soma_arduino = instrucao.motores[X].frequencia + instrucao.motores[Y].frequencia + instrucao.motores[Z].frequencia;
        myDelay(0.3);
        /*Serial.println("Variaveis:");
        Serial.println(instrucao.motores[X].frequencia);
    Serial.println(instrucao.motores[Y].frequencia);
    Serial.println(instrucao.motores[Z].frequencia);
    //Serial.println(instrucao.tempo);
    Serial.println(instrucao.motores[X].posicao);
    Serial.println(instrucao.motores[Y].posicao);
    Serial.println(instrucao.motores[Z].posicao);
        Serial.println(soma_rasp);
        Serial.println("Arduino:");
        Serial.println(soma_arduino);*/
        //delay(1000);
    }
    serial1.write('M');    
    ack_bit = 0;
     
     
    //Serial.println("Dados ok");
    /*Serial.println(instrucao.motores[X].frequencia);
    Serial.println(instrucao.motores[Y].frequencia);
    Serial.println(instrucao.motores[Z].frequencia);
    Serial.println(instrucao.tempo);
    Serial.println(instrucao.motores[X].posicao);
    Serial.println(instrucao.motores[Y].posicao);
    Serial.println(instrucao.motores[Z].posicao);*/
    Serial.print("Estou saindo de ler instrucao");
    //Serial.flush();
    
    
    
}

void ler_variaveis()
{
    instrucao.motores[X].frequencia = ler_float();
    instrucao.motores[Y].frequencia = ler_float();
    instrucao.motores[Z].frequencia = ler_float();
    instrucao.motores[X].posicao = ler_float();
    instrucao.motores[Y].posicao = ler_float();
    instrucao.motores[Z].posicao = ler_float();
    soma_rasp = ler_int();
}

void encontrar_chave()
{
  char chave[3];
  while(!serial1.available());
  for (int i = 0; i < 3; i++) 
  {
      chave[i] = serial1.read();
      Serial.println(chave[i]);
  }
  while(!eh_igual(chave))
  {
     for (int i = 0; i < 2; i++)
       chave[i] = chave[i+1];
     chave[2] = serial1.read();
     //Serial.println("Encontrando chave...");
  }
  Serial.println("Chave encontrada.");
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

int ler_int()
{
  int dado;
  char c_pointer[sizeof(int)];
  for(int i = 0; i < sizeof(int); i++)
      *(c_pointer + i) = serial1.read();
  dado = *((int *) c_pointer);
  return dado;
}

int myDelay(float interval)
{
    long init = millis();
    while ((millis() - init) <= interval*1000);
    return 0;    
}

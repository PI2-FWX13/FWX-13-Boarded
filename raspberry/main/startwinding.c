#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>


static int *glob_var;

void processoPrincipal(){
  while(*glob_var == 0){
    printf("Outras coisas sendo feitas\n");
    sleep(2);
  }
}
void get_temperature(){
  sleep(1);
  while(*glob_var == 0){
    printf("Temperatura fazendo coisas\n");
    sleep(2);
  }
}
void motor_controll(){

  while(*glob_var == 0){
    printf("Motor fazendo coisas\n");
    sleep(2);

  }
}


int main() {

  int i, j;
  glob_var = mmap(NULL, sizeof *glob_var, PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  *glob_var = 0;
  //Criando processo de obtenção da temperatura
  pid_t thread_temperature;
  thread_temperature = fork();

  if(thread_temperature != 0){
    printf("filho preguiçoso id: %d\n",thread_temperature);
    get_temperature();
    return 0;
  }else{
    printf("Failed to create temperature thread.\n");
  }
  //Criando processo do controle do motor
  pid_t thread_motor_controll;
  thread_motor_controll = fork();

  if(thread_motor_controll != 0){
    printf("filho ativo id: %d\n",thread_motor_controll);
    motor_controll();
    return 0;
  }else{
    printf("Failed to create motor controll thread.\n");
  }

  //
  processoPrincipal();

  return 0;
}

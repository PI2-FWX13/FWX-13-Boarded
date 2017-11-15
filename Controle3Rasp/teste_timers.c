// Bibliotecas
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#include <linux/socket.h>
#include <time.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "read_gcode.h"
#include "controla_motor.h" 
#include <math.h>

/* Informações para não esquecer:
Tamanho eixo x: 2*pi*r = 2*3.1415*100 = 628.3 mm
Tamanho eixo y: 1.2 m = 1200 mm
Tamanho eixo z: 20 cm = 200 mm
Cálculo velocidade: rpm = (frequencia x 60)/200*(nº de divisão de passo)
Sentido: 0 -> horário
     1 -> anti-horário
*/

// Definições
#define SIGTIMER (SIGRTMAX)
#define SIG SIGUSR1
#define SIG1 SIGUSR2
#define HIGH 1
#define LOW 0

//Variáveis globais
/*float freq_x[] = {3};
char sentido_x[] = {1};
float freq_y[] = {1};
char sentido_y[] = {1};
float freq_z[] = {2};
char sentido_z[] = {1.5};
float tempo[] = {1};
int numberOfLines = 1;*/
float tempo_freq_atual;
static timer_t     tid;
static timer_t     tid2;
static timer_t     tid3;
static struct itimerspec itval;


// Protótipos
void SignalHandler(int, siginfo_t*, void* );
timer_t SetTimer(int, float, int);
void configurar_sinal();

int main(int argc, char *argv[]) {

    get_freq_sentido();

    numberOfLines = 10;
    
    for (int i = 0; i < numberOfLines; i++) { 
	itval.it_value.tv_sec =   0; // Garante que o timer comece com zero.
	itval.it_value.tv_nsec =   0;
	itval.it_interval = itval.it_value;
	printf("TAG: %d\n", tag);
	printf("TEMPO: %f\n", tempo[i]);
	printf("FREQ X: %f\n", freq_x[i]);
	printf("FREQ Y: %f\n", freq_y[i]);
	printf("FREQ Z: %f\n", freq_z[i]);
	tag = 0;
	calculos_x(freq_x[i], sentido_x[i], tempo[i]); // Chama as funções para cálculo
	calculos_y(freq_y[i], sentido_y[i], tempo[i]);
	calculos_z(freq_z[i], sentido_z[i], tempo[i]);
	configurar_sinal();
	while(tag < 3); // Espera todos as funções serem chamadas
	timer_delete(tid); // Deleta os timers para garantir que eles comecem com zero
	timer_delete(tid2);
	timer_delete(tid3);
		
   }
	printf("Controle terminado\n");
    
    
    
    
    return 0;
}

void configurar_sinal() { // Essa função configura os três timers - usando sinais - 
    
    struct sigaction sigact;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = SA_SIGINFO;
    sigact.sa_sigaction = SignalHandler;
    if (sigaction(SIGTIMER, &sigact, NULL) == -1) {
        perror("sigaction failed");
        exit( EXIT_FAILURE );
    }

    // Primeiro sinal
    sigaction(SIGINT, &sigact, NULL);
    tid=SetTimer(SIGTIMER, tempo_freq_atual_x, 1);

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = SignalHandler;
    if (sigaction(SIG, &sa, NULL) == -1) {
        perror("sa failed");
        exit( EXIT_FAILURE );
    }

    // Segundo sinal e também sinal do crtl c. 
    sigaction(SIGINT, &sa, NULL);
    tid2=SetTimer(SIG, tempo_freq_atual_y, 4);
    if (sigaction(SIG1, &sa, NULL) == -1) {
        perror("ssignal failed");
        exit( EXIT_FAILURE );
    }

    // Terceiro sinal e também sinal do crtl c.
    sigaction(SIGINT, &sa, NULL);
    tid3=SetTimer(SIG1, tempo_freq_atual_z, 6);
}

void SignalHandler(int signo, siginfo_t* info, void* context) { // Quando o tempo expira, o sinal é chamado e consequentemente chama a função

    if (signo == SIGTIMER) {
	controla_motor_x();

    }else if (signo == SIG) {
	controla_motor_y();

    }else if (signo == SIG1) {
	controla_motor_z();

    } else if (signo == SIGINT) {
        timer_delete(tid);
	timer_delete(tid2);
	timer_delete(tid3);
        perror("Crtl+c cached!");
        exit(1);  // Termina o código
    }
}

timer_t SetTimer(int signo, float sec, int mode){ // Seta os tempos dos timers

    static struct sigevent sigev;
    static timer_t tid;
    
    static struct itimerspec oitval;
    
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = signo;
    sigev.sigev_value.sival_ptr = &tid;

    if (timer_create(CLOCK_REALTIME, &sigev, &tid) == 0) {
        if (mode == 1) {		
		itval.it_value.tv_sec =   sec;
		itval.it_value.tv_nsec =   sec * 1000000000;
		itval.it_interval = itval.it_value;
	}

        else if (mode == 4) {
            	itval.it_value.tv_sec =   sec;
		itval.it_value.tv_nsec =   sec * 1000000000;
		itval.it_interval = itval.it_value;
        }
	else {
	   	itval.it_value.tv_sec =   sec;
		itval.it_value.tv_nsec =   sec * 1000000000;
		itval.it_interval = itval.it_value;
	}

        if (timer_settime(tid, 0, &itval, &oitval) != 0) {
            perror("time_settime erro!");
        }
    }
    else {
        perror("timer_create erro!");
        return NULL;
    }
    return tid;
}


	
	

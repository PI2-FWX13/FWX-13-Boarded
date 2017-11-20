#ifndef READ_G_CODE  // guardas de cabeçalho, impedem inclusões cíclicas
#define READ_G_CODE

//https://pt.stackoverflow.com/questions/3690/criando-o-seu-pr%C3%B3prio-header-file
// arrays com os valores
#define MAX_LEN 500
extern const int rpm_max;
extern float Xs[MAX_LEN];
extern float Ys[MAX_LEN];
extern float Zs[MAX_LEN];
extern float tempo[MAX_LEN];
extern float freq_x[MAX_LEN];
extern float freq_y[MAX_LEN];
extern float freq_z[MAX_LEN];
extern int sentido_x[MAX_LEN];
extern int sentido_y[MAX_LEN];
extern int sentido_z[MAX_LEN];
extern int numberOfLines;

// Execute this function before accessing values
int get_freq_sentido();

#endif

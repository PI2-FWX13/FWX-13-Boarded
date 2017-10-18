#ifndef READ_G_CODE   // guardas de cabeçalho, impedem inclusões cíclicas
#define READ_G_CODE
  //https://pt.stackoverflow.com/questions/3690/criando-o-seu-pr%C3%B3prio-header-file
  // arrays com os valores
  extern float Xs[1000];
  extern float Ys[1000];
  extern float Zs[1000];
  extern int numberOfLines;
  // Execute this function before accessing values
  void readGCode();
  int getCoordinates(char * line);

#endif

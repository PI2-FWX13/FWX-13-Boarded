#ifndef READ_G_CODE   // guardas de cabeçalho, impedem inclusões cíclicas
#define READ_G_CODE

  // arrays com os valores
  extern float Xs[1000];
  extern float Ys[1000];
  extern float Zs[1000];

  // Execute this function before accessing values
  void readGCode();
  int getCoordinates(char * line);

#endif

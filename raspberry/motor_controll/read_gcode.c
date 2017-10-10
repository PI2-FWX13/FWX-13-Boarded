#include "read_gcode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// arrays com os valores
float Xs[1000];
float Ys[1000];
float Zs[1000];

// same position for each value
int count = 0;

//http://man7.org/linux/man-pages/man3/strtol.3.html
  int getCoordinates(char * line)
  {
    char *token;
    /* get the first token */
    token = strtok(line, " ");

    /* walk through other tokens */
    while( token != NULL ){
      //printf( "%s\n", token );
      if(*token == 'X'){
        token = strtok(NULL, " ");
        float x = atof(token);

        Xs[count] = x;
        //printf("X = %f\n",x);
      } else if(*token == 'Y'){
        token = strtok(NULL, " ");
        float y = atof(token);

        Ys[count] = y;
        //printf("Y = %f\n",y);
      }else if(*token == 'Z'){
        token = strtok(NULL, " ");
        float z = atof(token);

        Zs[count] = z;
        //printf("Z = %f\n",z);
      }

      token = strtok(NULL, " ");
    }

    count++;
  }


void readGCode()
{
  //https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
  //https://stackoverflow.com/questions/13399594/how-to-extract-numbers-from-string-in-c
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen("gcode", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // First value is 0
  Xs[count] = 0;
  Ys[count] = 0;
  Zs[count] = 0;

  while ((read = getline(&line, &len, fp)) != -1) {

    getCoordinates(line);

    // Set Next values so that it will not be null
    Xs[count] = Xs[count-1];
    Ys[count] = Ys[count-1];
    Zs[count] = Zs[count-1];

    //printf("Read X = %f Y = %f Z = %f\n",Xs[count],Ys[count],Zs[count]);
  }

  fclose(fp);
  if (line)
      free(line);
    return;
}

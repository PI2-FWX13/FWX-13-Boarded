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


int main(void)
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

  while ((read = getline(&line, &len, fp)) != -1) {
    //printf("Retrieved line of length %zu :\n", read);
    //printf("%s", line);
    getCoordinates(line);
  }

  fclose(fp);
  if (line)
      free(line);
  exit(EXIT_SUCCESS);

}

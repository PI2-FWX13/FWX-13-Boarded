#include <stdio.h>
#include <stdlib.h>
//http://man7.org/linux/man-pages/man3/strtol.3.html


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
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);

}

#include <mirim/io.h>
#include <stdio.h>
#include <stdlib.h>
char*
mr_readfile(const char* filename, long* nchars, Error** error) {
  char* text;

  // Open file
  FILE* fp = fopen(filename, "r");
  if(!fp){
    *error = mr_error_new("Could not open file");
    return NULL;
  }

  // Get total bytes
  fseek(fp, 0, SEEK_END);
  *nchars = ftell(fp);
  fseek(fp, 0, SEEK_SET);  //same as rewind(f);

  // Allocate all bytes
  text = malloc((*nchars) + 1);

  // Read file
  fread(text, *nchars, 1, fp);

  // Close file
  fclose(fp);

  // \0 at end
  text[*nchars] = 0;
  return text;
}

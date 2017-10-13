#include <mirim/mirim.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
  Error* error = NULL;
  char* text;
  long nchars;
  mr_parsefile("teste.mr", &text, &nchars, &error);
  if(error){
    fprintf(stderr, "Could not parse the file: %s", error->message);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

#include <mirim/mirim.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
  Error* error = NULL;
  parseFile("teste.mr", &error);
  if(error){
    fprintf(stderr, "Could not parse the file: %s", error->message);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

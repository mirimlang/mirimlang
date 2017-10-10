#include <mirim/mirim.h>
#include <stdio.h>
#include <stdlib.h>

static char* fileText;

static void
readFile(const char* filename, char** text) {
  // Open file
  FILE* fp = fopen(filename, "r");

  // Get total bytes
  fseek(fp, 0, SEEK_END);
  long fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);  //same as rewind(f);

  // Allocate all bytes
  *text = malloc(fsize + 1);

  // Read file
  fread(*text, fsize, 1, fp);

  // Close file
  fclose(fp);

  // \0 at end
  (*text)[fsize] = 0;
}

void
scan(const char* text) {

}

void
parseFile(const char *filename){
  // Read file
  readFile(filename, &fileText);

  // Generate tokens
  scan(fileText);
}

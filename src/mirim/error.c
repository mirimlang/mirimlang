#include <mirim/error.h>

Error*
mr_error_new(char type, const char* message) {
  return malloc();
}

void
mr_error_destroy(Error** error) {
  free(*error);
  *error = NULL;
}
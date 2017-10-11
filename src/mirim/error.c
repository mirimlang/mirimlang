#include <mirim/error.h>
#include <stdlib.h>

Error*
mr_error_new(const char* message) {
  Error* error = malloc(sizeof(Error));
  error->message = message;
  return error;
}

void
mr_error_destroy(Error** error) {
  free(*error);
  *error = NULL;
}

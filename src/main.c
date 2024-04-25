#include "contacts.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  contacts = calloc(size, sizeof(Contact));
  if (contacts == NULL) {
    printf("Memory not allocated.\n");
    exit(0);
  }

  run_menu();

  return 0;
}
#include "utils.h"
#include "contacts.h"

// Save input to a string
void read_string_input(char *msg, char *str) {
  printf("%s: ", msg);
  scanf("%[^\n]", str);
  getchar();
}

// Operations to file
void save_contacts_to_file() {
  if (size == 0) {
    return;
  } else {
    FILE *file;
    file = fopen("contacts", "w");

    for (int i = 0; i < size; i++) {
      fprintf(file, "%s\n", contacts[i].name);
      fprintf(file, "%s\n", contacts[i].phone_number);
      fprintf(file, "%s\n", contacts[i].address);
    }
    fclose(file);
  }
}

void load_contacts_from_file() {
  if (access("contacts", F_OK) == 0) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    int counter = 0;
    ssize_t read;
    file = fopen("contacts", "r");
    Contact temp_contact;
    temp_contact.name = NULL;
    temp_contact.phone_number = NULL;
    temp_contact.address = NULL;

    while ((read = getline(&line, &len, file)) != -1) {
      line[strcspn(line, "\n")] = 0;
      if (counter % 3 == 0) {
        temp_contact.name = malloc(50 * sizeof(char));
        strncpy(temp_contact.name, line, 50);
      }
      if (counter % 3 == 1) {
        temp_contact.phone_number = malloc(20 * sizeof(char));
        strncpy(temp_contact.phone_number, line, 20);
      }
      if (counter % 3 == 2) {
        temp_contact.address = malloc(100 * sizeof(char));
        strncpy(temp_contact.address, line, 100);
        size++;
        contacts = realloc(contacts, size * sizeof(Contact));
        contacts[size - 1] = temp_contact;
      }
      counter++;
    }
    free(line);
  }
}

// Avoid memory leaks
void free_contacts() {
  for (int i = 0; i < size; i++) {
    free(contacts[i].name);
    free(contacts[i].phone_number);
    free(contacts[i].address);
  }
  free(contacts);
}
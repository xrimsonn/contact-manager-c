#include "contacts.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Contact *contacts = NULL;
int size = 0;

void run_menu() {
  load_contacts_from_file();
  int opt = -1;
  do {
    printf("-------Menu-------\n");
    printf("1. Contact list\n");
    printf("2. Add contact\n");
    printf("3. Search contact\n");
    printf("4. Delete contact\n");
    printf("0. Exit\n");
    printf("Enter an option: ");
    scanf("%d", &opt);
    getchar();

#ifdef _WIN32
    system("cls");
#elif __APPLE__ || __linux__
    system("clear");
#endif

    switch (opt) {
    default:
    case 0:
      save_contacts_to_file();
      free_contacts();
      exit(0);
      break;

    case 1:
      print_contacts();
      break;

    case 2:
      add_contact();
      break;

    case 3:
      search_contact();
      break;

    case 4:
      delete_contact();
      break;
    }

  } while (opt != 0);
}

void add_contact() {
  printf("--------Add-------\n");
  char *new_name = malloc(50 * sizeof(char));
  read_string_input("Enter the name of the new contact", new_name);

  for (int i = 0; new_name[i]; i++) {
    new_name[i] = tolower(new_name[i]);
  }

  for (int i = 0; i < size; i++) {
    char *to_lower_name = strdup(contacts[i].name);
    for (int j = 0; to_lower_name[j]; j++) {
      to_lower_name[j] = tolower(to_lower_name[j]);
    }

    if (strcmp(to_lower_name, new_name) == 0) {
      printf("A contact with the same name already exists\n");
      free(to_lower_name);
      free(new_name);
      return;
    }

    free(to_lower_name);
  }

  size++;
  Contact new_contact;
  new_contact.name = malloc(50 * sizeof(char));
  strncpy(new_contact.name, new_name, 50);
  new_contact.phone_number = malloc(20 * sizeof(char));
  new_contact.address = malloc(100 * sizeof(char));

  read_string_input("Enter full name", new_contact.name);
  read_string_input("Enter phone number", new_contact.phone_number);
  read_string_input("Enter address", new_contact.address);

  contacts = realloc(contacts, size * sizeof(Contact));
  contacts[size - 1] = new_contact;
}

void read_string_input(char *msg, char *str) {
  printf("%s: ", msg);
  scanf("%[^\n]", str);
  getchar();
}

void print_contacts() {
  if (size == 0) {
    printf("No contacts found");
  } else {
    printf("-------List-------\n");
    for (int i = 0; i < size; i++) {
      if (i > 0)
        printf("--------\n");
      printf("%s\n", contacts[i].name);
      printf("%s\n", contacts[i].phone_number);
      printf("%s\n", contacts[i].address);
    }
    printf("\n");
  }
}

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

void search_contact() {
  printf("------Search------\n");
  char *search_input = malloc(50 * sizeof(char));
  bool not_found = TRUE;
  read_string_input("Search for a contact", search_input);
  for (int i = 0; search_input[i]; i++) {
    search_input[i] = tolower(search_input[i]);
  }

  for (int i = 0; i < size; i++) {
    char *to_lower_name = strdup(contacts[i].name);
    for (int i = 0; to_lower_name[i]; i++) {
      to_lower_name[i] = tolower(to_lower_name[i]);
    }

    if (strstr(to_lower_name, search_input) != NULL) {
      printf("--------\n");
      printf("%s\n", contacts[i].name);
      printf("%s\n", contacts[i].phone_number);
      printf("%s\n", contacts[i].address);
      not_found = FALSE;
    }
    free(to_lower_name);
  }

  if (not_found) {
    printf("No results for %s.\n", search_input);
  }

  printf("\n");

  free(search_input);
}

void delete_contact() {
  printf("------Delete------\n");
  char *search_input = malloc(50 * sizeof(char));
  read_string_input("Enter the name of the contact to delete (case sensitive)",
                    search_input);
  int index_to_delete = -1;

  for (int i = 0; i < size; i++) {
    char *name = strdup(contacts[i].name);

    if (strcmp(name, search_input) == 0) {
      index_to_delete = i;
      break;
    }
    free(name);
  }

  if (index_to_delete != -1) {
    free(contacts[index_to_delete].name);
    free(contacts[index_to_delete].phone_number);
    free(contacts[index_to_delete].address);

    for (int i = index_to_delete; i < size - 1; i++) {
      contacts[i] = contacts[i + 1];
    }

    size--;
    contacts = realloc(contacts, size * sizeof(Contact));
    printf("Contact deleted successfully\n");
  } else {
    printf("Contact not found\n");
  }
  printf("\n");
  free(search_input);
}

void free_contacts() {
  for (int i = 0; i < size; i++) {
    free(contacts[i].name);
    free(contacts[i].phone_number);
    free(contacts[i].address);
  }
  free(contacts);
}
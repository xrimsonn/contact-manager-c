#include "contacts.h"
#include "utils.h"

Contact *contacts = NULL;
int size = 0;

// Main menu of the application
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

void print_contacts() {
  if (size == 0) {
    printf("No contacts found\n");
  } else {
    printf("-------List-------\n");
    for (int i = 0; i < size; i++) {
      if (i > 0)
        printf("--------\n");
      printf("%s\n", contacts[i].name);
      printf("%s\n", contacts[i].phone_number);
      printf("%s\n", contacts[i].address);
    }
  }
  printf("\n");
}

// Contacts operations
void add_contact() {
  printf("--------Add-------\n");
  char *new_name = malloc(50 * sizeof(char));
  read_string_input("Enter the name of the new contact", new_name);

  char *original_name = strdup(new_name);

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
      printf("\n");
      free(to_lower_name);
      free(new_name);
      free(original_name);
      return;
    }

    free(to_lower_name);
  }

  size++;
  Contact new_contact;
  new_contact.name = original_name;
  new_contact.phone_number = malloc(20 * sizeof(char));
  new_contact.address = malloc(100 * sizeof(char));

  read_string_input("Enter phone number", new_contact.phone_number);
  read_string_input("Enter address", new_contact.address);

  contacts = realloc(contacts, size * sizeof(Contact));
  contacts[size - 1] = new_contact;

  printf("\n");
  free(new_name);
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

#ifndef CONTACTS_H
#define CONTACTS_H
#define bool short
#define TRUE 1
#define FALSE 0

typedef struct {
  char *name;
  char *phone_number;
  char *address;
} Contact;

extern Contact *contacts;
extern int size;

void run_menu();
void print_contacts();
void add_contact();
void search_contact();
void delete_contact();

void save_contacts_to_file();
void load_contacts_from_file();
void free_contacts();

void read_string_input(char *msg, char *str);

#endif // CONTACTS_H
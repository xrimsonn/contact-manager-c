#ifndef CONTACTS_H
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

#endif // CONTACTS_H
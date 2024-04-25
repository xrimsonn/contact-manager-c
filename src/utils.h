#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void read_string_input(char *msg, char *str);
void save_contacts_to_file();
void load_contacts_from_file();
void free_contacts();

#endif // UTILS_H
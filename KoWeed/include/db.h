#ifndef DB_H
#define DB_H
#include <sqlite3.h>
#include <stdio.h>

sqlite3 *db;

int connect_db(char *file);
int get_last_id();
#endif
#ifndef APP_H
#define APP_H
#include "data.h"

typedef struct _session
{
    User user;
    Owner owner;
    Person person;
} Session;
Session session;

int sign_up_user(char *username, char *password, char *re_password, int type);
int sign_up_person(int user_id, char *firstname, char *lastname, char *idcode, char *email, char *blood, int weight, int height);
int save_record_person(Person p, int code, int time);
int reset_password(char *email, char *username, char *idcode, char *password, char *re_password);
int save_meeting_person(Person p, char *idcode, long int time);
int edit_person(Person person, char *username, char *firstname, char *lastname, char *idcode, char *email, char *blood, int weight, int height);
int save_visit(Person p, char *place_name, long int time, int status);
int edit_owner(Owner owner, char *username, char *place_name, int district, char *idcode, char *email, char *city);
int handle_sick_meets(Person p, int code, long int time);
#endif
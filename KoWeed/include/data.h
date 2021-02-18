#ifndef DATA_H
#define DATA_H

typedef struct _user
{
    int id;
    char *username;
    char *pass;
    int type; // 1 is admin 2 person 3 is owner

} User;

int user_add(User u);
User user_get(User u);
int user_update(User u);

typedef struct _person
{
    User user;
    int id;
    char *firstname;
    char *lastname;
    char *idcode;
    char *email;
    char *blood;
    int height;
    int weight;
    int status;
} Person;

int person_add(Person p);
Person person_get(Person p);
int person_update(Person p);
Person *person_list();


typedef struct _owner
{
    User user;
    int id;
    char *idcode;
    char *place_name;
    char *email;
    int district;
    int status;
    char *city;
} Owner;

int owner_add(Owner o);
Owner owner_get(Owner o);
int owner_update(Owner o);
Owner *owner_list();



typedef struct _health_record
{
    User user;
    int id;
    int code;
    long int time;
} Health_record;

int health_record_add(Health_record hr);
Health_record *health_record_list(int user_id);

typedef struct _meet
{
    User user_a;
    User user_b;
    int id;
    int code_a;
    int code_b;
    long int time;
} Meet;

int meet_add(Meet m);
Meet *meet_list(int user_id);

typedef struct _hospital
{
    int id;
    char *city;
    int district;
    char *name;
} Hospital;

int hospital_add(Hospital h);
Hospital *hospital_list(char *city, int district);

typedef struct _visit
{
    int id;
    User user;
    char *place_name;
    long int time;
    int status;
} Visit;

int visit_add(Visit v);
Visit *visit_list(int user_id);


typedef struct _message
{
    int id;
    User user_a;
    User user_b;
    long int time;
    char *message;

} Message;

int message_add(Message m);
Message *message_list(int user_id);
#endif
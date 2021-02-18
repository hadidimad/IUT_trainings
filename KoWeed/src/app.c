#include "../include/app.h"
#include "../include/data.h"
#include <string.h>
#include <stdio.h>
int sign_up_user(char *username, char *password, char *re_password, int type)
{
    User user;
    user.username = strdup(username);
    user.pass = strdup(password);
    if (strcmp(user.pass, re_password))
    {
        return -1; ///diff passes
    }
    user.type = type;
    int rc = user_add(user);
    if (rc != 0)
    {
        return -2; //same username
    }
    return 0;
}

int sign_up_person(int user_id, char *firstname, char *lastname, char *idcode, char *email, char *blood, int weight, int height)
{

    printf("person signinig man\n");
    printf("%i  %s   %s   %s   %s   %i  %i\n", user_id, firstname, lastname, idcode, blood, weight, height);
    User user;
    user.id = user_id;
    Person person;
    person.firstname = firstname;
    person.lastname = lastname;
    person.idcode = idcode;
    person.email = email;
    person.blood = blood;
    person.weight = weight;
    person.height = height;
    person.user = user;
    person.status = -1;
    int rc = person_add(person);
    return rc;
}
int sign_up_owner(int user_id, char *place_name, char *city, char *idcode, char *email, int district)
{

    printf("owner signinig man\n");
    printf("%i  %s   %s   %s   %s   %i\n", user_id, place_name, city, idcode, email, district);
    User user;
    user.id = user_id;
    Owner owner;
    owner.place_name = place_name;
    owner.city = city;
    owner.idcode = idcode;
    owner.email = email;
    owner.district = district;
    owner.user = user;
    owner.status = -1;
    int rc = owner_add(owner);
    return rc;
}

int reset_password(char *email, char *username, char *idcode, char *password, char *re_password)
{
    if (strcmp(password, re_password))
    {
        return -1; ///password not matching
    }
    User u;
    u.id = 0;
    u.pass = "nopassword";
    u.username = username;
    u = user_get(u);
    printf("the id is :%i ", u.id);
    Person person;
    Owner owner;
    person.id = 0;
    owner.id = 0;
    person.user = u;
    owner.user = u;
    person = person_get(person);
    owner = owner_get(owner);
    if (person.id != -1)
    {
        if (!strcmp(person.email, email) && !strcmp(person.idcode, idcode))
        {
            u.pass = password;
            user_update(u);
            return 0;
        }
    }
    if (owner.id != -1)
    {
        if (!strcmp(owner.email, email) && !strcmp(owner.idcode, idcode))
        {
            u.pass = password;
            user_update(u);
            return 0;
        }
    }
    return -2;
}

int save_record_person(Person p, int code, int time)
{

    Health_record h;
    h.code = code;
    h.time = time;
    h.user = p.user;
    health_record_add(h);
}

int save_meeting_person(Person p, char *idcode, long int time)
{
    Person b;
    b.id = 0;
    b.user.id = 0;
    b.idcode = idcode;
    b = person_get(b);
    if (b.id == -1)
    {
        return -1;
    }
    Meet m;
    m.user_a = p.user;
    m.user_b = b.user;
    m.time = time;
    m.code_a = p.status;
    m.code_b = b.status;
    int rc = meet_add(m);
    return rc;

    g_print("\n \n%s \n", b.firstname);
}

int edit_person(Person person, char *username, char *firstname, char *lastname, char *idcode, char *email, char *blood, int weight, int height)
{
    printf("person editing \n");
    printf("  %s   %s   %s   %s   %i  %i\n", firstname, lastname, idcode, blood, weight, height);

    session.user.username = username;
    user_update(session.user);
    person.firstname = firstname;
    person.lastname = lastname;
    person.idcode = idcode;
    person.email = email;
    person.blood = blood;
    person.weight = weight;
    person.height = height;

    int rc = person_update(person);

    session.user = user_get(session.user);
    session.person = person_get(session.person);

    return rc;
}

int edit_owner(Owner owner, char *username, char *place_name, int district, char *idcode, char *email, char *city)
{
    printf("owner editing \n");
    printf("  %s   %s   %s   %s   %i  %i\n", username, place_name, idcode, email, district, city);

    session.user.username = username;
    user_update(session.user);
    owner.place_name = place_name;
    owner.idcode = idcode;
    owner.email = email;
    owner.city = city;
    owner.district = district;

    int rc = owner_update(owner);

    session.user = user_get(session.user);
    session.owner = owner_get(session.owner);

    return rc;
}

int save_visit(Person p, char *place_name, long int time, int status)
{
    Visit v;
    v.place_name = place_name;
    v.time = time;
    v.status = status;
    v.user = p.user;
    int rc = visit_add(v);
    if (rc == 0)
    {
        if (session.person.status == 1 && status == 1)
        {
            session.person.status = 2;
            person_update(session.person);
        }
        return 0;
    }
}

int handle_sick_meets(Person p, int code, long int time)
{
    Meet *m = meet_list(p.user.id);
    while (m->id != -1)
    {
        g_print("time is   %i \n", m->time);

        if ((time - m->time) < 604800)
        {
            g_print("%s   %s \n", m->user_a.username, m->user_b.username);
            if (m->user_a.id == p.user.id)
            {
                Person temp;
                temp.id = 0;
                temp.user.id = m->user_b.id;
                temp = person_get(temp);
                g_print("\nperson: %s   %i\n", temp.firstname,temp.status);

                if (code == 4)
                {
                    if (temp.status < 3)
                    {
                        temp.status = 3;
                        person_update(temp);
                    }
                }
                else if (code == 3)
                {
                    if (temp.status < 2)
                    {
                        temp.status = 2;
                        person_update(temp);
                    }
                }
            }
            else if (m->user_b.id == p.user.id)
            {
                Person temp;
                temp.id = 0;
                temp.user.id = m->user_a.id;
                temp = person_get(temp);
                g_print("\nperson: %s   %i\n", temp.firstname,temp.status);

                if (code == 4)
                {
                    if (temp.status < 3)
                    {
                        temp.status = 3;
                        person_update(temp);
                    }
                }
                else if (code == 3)
                {
                    if (temp.status < 2)
                    {
                        temp.status = 2;
                        person_update(temp);
                    }
                }
            }
        }
        m++;
    }
    g_print("meets handleed \n \n");
}

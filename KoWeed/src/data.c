#include "../include/data.h"
#include "../include/db.h"
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int user_add(User u)
{
    sqlite3_stmt *res;
    char *err_msg = 0;

    char query[256];
    sprintf(query, "INSERT INTO users (username,password,type) VALUES('%s','%s',%i)", u.username, u.pass, u.type);
    printf("%s", query);
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        return 1;
    }
    return 0;
}

User user_get(User u)
{
    char *err_msg = 0;
    sqlite3_stmt *res;
    int rc;
    char sql[256];

    if (u.id != 0)
    {
        sprintf(sql, "SELECT * FROM users WHERE id = %i", u.id);
        printf("%s", sql);
    }
    else if (!strcmp(u.pass, "nopassword"))
    {
        sprintf(sql, "SELECT * FROM users WHERE username = '%s' ", u.username);
        printf("%s", sql);
    }
    else
    {
        sprintf(sql, "SELECT * FROM users WHERE username = '%s' AND password = '%s'", u.username, u.pass);
        printf("%s", sql);
    }
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        u.id = -1;
        return u;
    }
    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {
        u.id = sqlite3_column_int(res, 0);
        u.username = strdup(sqlite3_column_text(res, 1));
        u.pass = strdup(sqlite3_column_text(res, 2));
        u.type = sqlite3_column_int(res, 3);
        return u;
    }
    else
    {
        u.id = -1;
        return u;
    }
}

int user_update(User u)
{
    sqlite3_stmt *res;
    char *err_msg = 0;

    char query[256];
    sprintf(query, "UPDATE users set username = '%s', password = '%s', type = %i WHERE id=%i", u.username, u.pass, u.type, u.id);
    printf("%s", query);
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        return 1;
    }
    return 0;
}
int person_add(Person p)
{
    sqlite3_stmt *res;
    char *err_msg = 0;

    char query[256];
    sprintf(query, "INSERT INTO persons (user_id,firstname,lastname,idcode,email,blood,height,weight,status) VALUES(%i,'%s','%s','%s','%s','%s',%i,%i,%i)", p.user.id, p.firstname, p.lastname, p.idcode, p.email, p.blood, p.height, p.weight, p.status);
    printf("%s", query);
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        return 1;
    }
    return 0;
}

Person person_get(Person p)
{
    char *err_msg = 0;
    sqlite3_stmt *res;
    int rc;
    char sql[256];
    if (p.id != 0)
    {
        sprintf(sql, "SELECT * FROM persons WHERE id = %i", p.id);
        printf("%s", sql);
    }
    else if (p.user.id != 0)
    {
        sprintf(sql, "SELECT * FROM persons WHERE user_id = %i", p.user.id);
        printf("%s", sql);
    }
    else if (strlen(p.idcode) > 2)
    {
        sprintf(sql, "SELECT * FROM persons WHERE idcode = '%s'", p.idcode);
        printf("%s", sql);
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        p.id = -1;
        return p;
    }
    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {
        User u;
        u.id = sqlite3_column_int(res, 0);
        u = user_get(u);
        p.user = u;
        p.firstname = strdup(sqlite3_column_text(res, 1));
        p.lastname = strdup(sqlite3_column_text(res, 2));
        p.idcode = strdup(sqlite3_column_text(res, 3));
        p.email = strdup(sqlite3_column_text(res, 4));
        p.blood = strdup(sqlite3_column_text(res, 5));
        p.height = sqlite3_column_int(res, 6);
        p.weight = sqlite3_column_int(res, 7);
        p.status = sqlite3_column_int(res, 8);
        p.id = sqlite3_column_int(res, 9);

        return p;
    }
    else
    {
        p.id = -1;
        return p;
    }
}
int person_update(Person p)
{
    sqlite3_stmt *res;
    char *err_msg = 0;

    char query[256];
    sprintf(query, "UPDATE persons SET  firstname='%s',lastname='%s',idcode='%s',email='%s',blood='%s',height = %i,weight = %i,status =%i WHERE id = %i", p.firstname, p.lastname, p.idcode, p.email, p.blood, p.height, p.weight, p.status, p.id);
    printf("%s", query);
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        return 1;
    }
    return 0;
}

Person *person_list()
{
    sqlite3_stmt *res;
    char *err_msg = 0;
    int rc;
    int count = 0;
    Person *records = malloc(sizeof(Person) * 100);

    char query[256];

    sprintf(query, "SELECT * FROM persons");

    printf("%s", query);
    rc = sqlite3_prepare_v2(db, query, -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        records[0].id = -1;
        return records;
    }
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        records[count].firstname = strdup(sqlite3_column_text(res, 1));
        records[count].lastname = strdup(sqlite3_column_text(res, 2));
        records[count].idcode = strdup(sqlite3_column_text(res, 3));
        records[count].email = strdup(sqlite3_column_text(res, 4));
        records[count].blood = strdup(sqlite3_column_text(res, 5));
        records[count].height = sqlite3_column_int(res, 6);
        records[count].weight = sqlite3_column_int(res, 7);
        records[count].status = sqlite3_column_int(res, 8);
        records[count].id = sqlite3_column_int(res, 9);
        count++;
    }
    records[count].id = -1;
    return records;
}

int owner_add(Owner o)
{
    sqlite3_stmt *res;
    char *err_msg = 0;

    char query[256];
    sprintf(query, "INSERT INTO owners (user_id,idcode,email,place_name,district,status,city) VALUES(%i,'%s','%s','%s',%i,%i,'%s')", o.user.id, o.idcode, o.email, o.place_name, o.district, o.status, o.city);
    printf("%s", query);
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        return 1;
    }
}

Owner owner_get(Owner o)
{
    char *err_msg = 0;
    sqlite3_stmt *res;
    int rc;
    char sql[256];
    if (o.id != 0)
    {
        sprintf(sql, "SELECT * FROM owners WHERE id = %i", o.id);
        printf("%s", sql);
    }
    else if (o.user.id != 0)
    {
        sprintf(sql, "SELECT * FROM owners WHERE user_id = %i", o.user.id);
        printf("%s", sql);
    }
    else if (strlen(o.place_name) > 2)
    {
        sprintf(sql, "SELECT * FROM owners WHERE place_name = '%s'", o.place_name);
        printf("%s", sql);
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        o.id = -1;
        return o;
    }
    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {
        User u;
        u.id = sqlite3_column_int(res, 0);
        u = user_get(u);
        o.user = u;
        o.idcode = strdup(sqlite3_column_text(res, 1));
        o.email = strdup(sqlite3_column_text(res, 2));
        o.place_name = strdup(sqlite3_column_text(res, 3));
        o.district = sqlite3_column_int(res, 4);
        o.status = sqlite3_column_int(res, 5);
        o.city = strdup(sqlite3_column_text(res, 6));
        o.id = sqlite3_column_int(res, 7);

        return o;
    }
    else
    {
        o.id = -1;
        return o;
    }
}

int owner_update(Owner o)
{
    sqlite3_stmt *res;
    char *err_msg = 0;

    char query[256];
    sprintf(query, "UPDATE  owners SET idcode='%s' , email = '%s' , place_name='%s' , district=%i , status=%i , city = '%s' WHERE id=%i", o.idcode, o.email, o.place_name, o.district, o.status, o.city, o.id);
    printf("%s", query);
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        return 1;
    }
}
Owner *owner_list()
{
    sqlite3_stmt *res;
    char *err_msg = 0;
    int rc;
    int count = 0;
    Owner *records = malloc(sizeof(Owner) * 100);

    char query[256];

    sprintf(query, "SELECT * FROM owners");

    printf("%s", query);
    rc = sqlite3_prepare_v2(db, query, -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        records[0].id = -1;
        return records;
    }
    while (sqlite3_step(res) == SQLITE_ROW)
    {

        records[count].idcode = strdup(sqlite3_column_text(res, 1));
        records[count].email = strdup(sqlite3_column_text(res, 2));
        records[count].place_name = strdup(sqlite3_column_text(res, 3));
        records[count].district = sqlite3_column_int(res, 4);
        records[count].status = sqlite3_column_int(res, 5);
        records[count].city = strdup(sqlite3_column_text(res, 6));
        records[count].id = sqlite3_column_int(res, 7);
        count++;
    }
    records[count].id = -1;
    return records;
}

int health_record_add(Health_record hr)
{
    sqlite3_stmt *res;
    char *err_msg = 0;

    char query[256];
    sprintf(query, "INSERT INTO health_records (user_id,code,time) VALUES(%i,%i,%li)", hr.user.id, hr.code, hr.time);
    printf("%s", query);
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        return 1;
    }
}

Health_record *health_record_list(int user_id)
{
    sqlite3_stmt *res;
    char *err_msg = 0;
    int rc;
    int count = 0;
    Health_record *records = malloc(sizeof(Health_record) * 10);

    char query[256];
    if (user_id != 0)
    {
        sprintf(query, "SELECT * FROM health_records  WHERE user_id = %i ORDER BY id DESC LIMIT 10", user_id);
    }
    else
    {
        sprintf(query, "SELECT * FROM health_records ORDER BY id DESC LIMIT 10");
    }
    printf("%s", query);
    rc = sqlite3_prepare_v2(db, query, -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        records[0].id = -1;
        return records;
    }
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        records[count].id = sqlite3_column_int(res, 0);
        records[count].user.id = sqlite3_column_int(res, 1);
        records[count].user = user_get(records[count].user);
        records[count].time = sqlite3_column_int(res, 2);
        records[count].code = sqlite3_column_int(res, 3);
        count++;
    }
    records[count].id = -1;
    return records;
}

int meet_add(Meet m)
{
    sqlite3_stmt *res;
    char *err_msg = 0;

    char query[256];
    sprintf(query, "INSERT INTO meets (user_a,user_b,time,code_a,code_b) VALUES(%i,%i,%li,%i,%i)", m.user_a.id, m.user_b.id, m.time, m.code_a, m.code_b);
    printf("%s", query);
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        return 1;
    }
}

Meet *meet_list(int user_id)
{
    sqlite3_stmt *res;
    char *err_msg = 0;
    int rc;
    int count = 0;
    Meet *meets = malloc(sizeof(Meet) * 10);

    char query[256];
    if (user_id != 0)
    {
        sprintf(query, "SELECT * FROM meets  WHERE user_a = %i OR user_b = %i LIMIT 10", user_id, user_id);
    }
    else
    {
        sprintf(query, "SELECT * FROM meets LIMIT 10");
    }
    printf("%s", query);
    rc = sqlite3_prepare_v2(db, query, -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        meets[0].id = -1;
        return meets;
    }
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        meets[count].id = sqlite3_column_int(res, 0);
        meets[count].user_a.id = sqlite3_column_int(res, 1);
        meets[count].user_a = user_get(meets[count].user_a);

        meets[count].user_b.id = sqlite3_column_int(res, 2);
        meets[count].user_b = user_get(meets[count].user_b);

        meets[count].time = sqlite3_column_int(res, 3);

        meets[count].code_a = sqlite3_column_int(res, 4);
        meets[count].code_b = sqlite3_column_int(res, 5);

        count++;
    }
    meets[count].id = -1;
    return meets;
}

int hospital_add(Hospital h)
{
    sqlite3_stmt *res;
    char *err_msg = 0;

    char query[256];
    sprintf(query, "INSERT INTO hospitals (city,district,name) VALUES('%s',%i,'%s')", h.city, h.district, h.name);
    printf("%s", query);
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        return 1;
    }
}

Hospital *hospital_list(char *city, int district)
{
    sqlite3_stmt *res;
    char *err_msg = 0;
    int rc;
    int count = 0;
    Hospital *hospitals = malloc(sizeof(Hospital) * 20);

    char query[256];
    if (district == -1)
    {
        sprintf(query, "SELECT * FROM hospitals");
        printf("%s", query);
    }
    else
    {

        sprintf(query, "SELECT * FROM hospitals  WHERE city = '%s' AND district = %i LIMIT 10", city, district);
        printf("%s", query);
    }
    rc = sqlite3_prepare_v2(db, query, -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        hospitals[0].id = -1;
        return hospitals;
    }
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        hospitals[count].id = sqlite3_column_int(res, 0);
        hospitals[count].city = strdup(sqlite3_column_text(res, 1));
        hospitals[count].district = sqlite3_column_int(res, 2);
        hospitals[count].name = strdup(sqlite3_column_text(res, 3));
        count++;
    }
    hospitals[count].id = -1;
    return hospitals;
}

int visit_add(Visit v)
{
    sqlite3_stmt *res;
    char *err_msg = 0;

    char query[256];
    sprintf(query, "INSERT INTO visits (user_id,place_name,time,status) VALUES(%i,'%s',%li,%i)", v.user.id, v.place_name, v.time, v.status);
    printf("%s", query);
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        return 1;
    }
}

Visit *visit_list(int user_id)
{
    sqlite3_stmt *res;
    char *err_msg = 0;
    int rc;
    int count = 0;
    Visit *visits = malloc(sizeof(Visit) * 100);

    char query[256];
    if (user_id != 0)
    {
        sprintf(query, "SELECT * FROM visits WHERE user_id=%i", user_id);
    }
    else
    {
        sprintf(query, "SELECT * FROM visits");
    }
    printf("%s", query);
    rc = sqlite3_prepare_v2(db, query, -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        visits[0].id = -1;
        return visits;
    }
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        visits[count].id = sqlite3_column_int(res, 0);
        visits[count].user.id = sqlite3_column_int(res, 1);
        visits[count].user = user_get(visits[count].user);
        visits[count].place_name = strdup(sqlite3_column_text(res, 2));
        visits[count].time = sqlite3_column_int(res, 3);
        visits[count].status = sqlite3_column_int(res, 4);
        count++;
    }
    visits[count].id = -1;
    return visits;
}

int message_add(Message m)
{
    sqlite3_stmt *res;
    char *err_msg = 0;

    char query[256];
    sprintf(query, "INSERT INTO messages (user_a,user_b,message,time) VALUES(%i,%i,'%s',%li)", m.user_a.id, m.user_b.id, m.message, m.time);
    printf("%s", query);
    int rc = sqlite3_exec(db, query, 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        return 1;
    }
}

Message *message_list(int user_id)
{
    sqlite3_stmt *res;
    char *err_msg = 0;
    int rc;
    int count = 0;
    Message *messages = malloc(sizeof(Message) * 10);

    char query[256];
    if (user_id != 0)
    {
        sprintf(query, "SELECT * FROM messages  WHERE user_a = %i OR user_b = %i LIMIT 10", user_id, user_id);
    }
    else
    {
        sprintf(query, "SELECT * FROM messages LIMIT 10");
    }
    printf("%s", query);
    rc = sqlite3_prepare_v2(db, query, -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        //sqlite3_close(db);
        messages[0].id = -1;
        return messages;
    }
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        messages[count].id = sqlite3_column_int(res, 0);
        messages[count].message = strdup(sqlite3_column_text(res, 1));

        messages[count].user_a.id = sqlite3_column_int(res, 2);
        messages[count].user_a = user_get(messages[count].user_a);

        messages[count].user_b.id = sqlite3_column_int(res, 3);
        messages[count].user_b = user_get(messages[count].user_b);

        messages[count].time = sqlite3_column_int(res, 4);

        count++;
    }
    messages[count].id = -1;
    return messages;
}

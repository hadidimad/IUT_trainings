#include "../include/db.h"
#include <sqlite3.h>

int connect_db(char *file)
{
    int rc = sqlite3_open("KoWeed.sqlite", &db);

    if (rc != SQLITE_OK)
    {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }
    return 0;
}
int get_last_id()
{
    return sqlite3_last_insert_rowid(db);
}

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address
{
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database
{
    struct Address rows[MAX_ROWS];
};

struct Connection
{
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn)
{
    if(conn)
    {
        if(conn->file)
            fclose(conn->file);
        
        if(conn->db)
            free(conn->db);
        
        free(conn);
    }
}

void die(struct Connection *conn,const char *message)
{
    if(errno)
    {
        perror(message);
    }
    else
    {
        printf("ERROR: %s\n",message);
    }

    Database_close(conn);
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",addr->id,addr->name,addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db,sizeof(struct Database),1,conn->file);

    if(rc != 1)
        die(conn,"Failed to load database.");
}

struct Connection* Database_open(const char *filename,char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));

    if(!conn)
        die(conn,"Memory error");

    conn->db = malloc(sizeof(struct Database));

    if(!conn->db)
        die(conn,"Memory error");

    if(mode == 'c')
    {
        conn->file = fopen(filename,"w");
    }
    else
    {
        conn->file = fopen(filename,"r+");

        if(conn->file)
        {
            Database_load(conn);
        }
    }

    if(!conn->file)
        die(conn,"Failed to open the file");

    return conn;
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);

    int rc = fwrite(conn->db,sizeof(struct Database),1,conn->file);

    if(rc != 1)
        die(conn,"Failed to write database.");

    rc = fflush(conn->file);

    if(rc == -1)
        die(conn,"Cannot flush database.");
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for(;i < MAX_ROWS;i++)
    {
        // Make a prototype to initialize it
        struct Address addr = {.id = i,.set = 0};

        // Then just assign it.
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn,int id,const char *name,const char *email)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set)
        die(conn,"Already set, delete it first");
    
    addr->set = 1;

    // WARNING: Bug, read the "How To Break It" and fix this.
    char *res = strncpy(addr->name,name,MAX_DATA - 1);
    addr->name[MAX_DATA - 1] = '\0';

    // Demonstrate the strncpy bug.
    if(!res)
        die(conn,"Name copy failed");

    res = strncpy(addr->email,email,MAX_DATA - 1);
    addr->email[MAX_DATA - 1] = '\0';

    if(!res)
        die(conn,"Email copy failed");
}

void Database_get(struct Connection *conn,int id)
{
    // Note: In the line below, you have to take the address of
    // conn->db->rows[id] since addr is a POINTER to a struct 
    // Address type and pointers point to addresses in memory.
    // Alternatively, you can write: struct Address addr =
    // conn->db->rows[id], followed by addr.set instead of
    // addr-> set, etc.
    struct Address *addr = &conn->db->rows[id];

    if(addr->set)
    {
        Address_print(addr);
    }
    else
    {
        die(conn,"ID is not set");
    }
}

void Database_delete(struct Connection *conn,int id)
{
    struct Address addr = {.id = id,.set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for(;i < MAX_ROWS;i++)
    {
        struct Address *cur = &db->rows[i];

        if(cur->set)
        {
            Address_print(cur);
        }
    }
}

void Database_sizeof(struct Connection *conn)
{
    printf("The size of struct Connection *conn is: %lu\n",sizeof(conn)); // 8 because a pointer is size 8
    printf("The size of struct Connection is: %lu\n",sizeof(struct Connection)); // 16 because struct Connection contains two pointers
    printf("The size of struct Address is: %lu\n",sizeof(conn->db->rows[1])); // 1032
    printf("The size of struct Database is: %lu\n",sizeof(conn->db->rows)); // 103,200 because struct Database contains 100 struct Address
}

void Database_find(struct Connection *conn,int field,char *keyword)
{
    int i = 0;
    
    switch(field)
    {
        case 1:
        {
            int id = atoi(keyword);

            for(;i < MAX_ROWS;i++)
            {
                if(conn->db->rows[i].id == id)
                {
                    printf("The information for id '%d' is: set = %d, name = %s, email = %s.\n",id,conn->db->rows[i].set,conn->db->rows[i].name,conn->db->rows[i].email);
                    break;
                }
            }

            break;
        }
    }
}

int main(int argc,char *argv[])
{
    if(argc < 3)
    {
        printf("USAGE: ex17 <dbfile> <action> [action params]");
        exit(1);
    }

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename,action);
    int id = 0;

    if(argc > 3 && action != 'f')
    {    
        id = atoi(argv[3]);
        
        if(id >= MAX_ROWS)
            die(conn,"There's not that many records.");
    }

    if(action == 'f' && argc != 5)
    {
        die(conn,"Find argument requires exactly 5 arguments.");
    }
;
    switch(action)
    {
        case 'f':
            if(strcasecmp(argv[3],"id") == 0)
            {
                Database_find(conn,1,argv[4]);
            }
            else if(strcasecmp(argv[3],"set") == 0)
                Database_find(conn,2,argv[4]);
            else if(strcasecmp(argv[3],"name") == 0)
                Database_find(conn,3,argv[4]);
            else if(strcasecmp(argv[3],"email") == 0)
                Database_find(conn,4,argv[4]);
            else
                die(conn,"Invalid search field");

            break;
        case'a':
            Database_sizeof(conn);
            break;
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4)
                die(conn,"Need an id to get");

            Database_get(conn,id);
            break;

        case 's':
            if(argc != 6)
                die(conn,"Need id, name, email to set");

            Database_set(conn,id,argv[4],argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4)
                die(conn,"Need id to delete");

            Database_delete(conn,id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die(conn,"Invalid action: a = print size of, f = find,c = create,g = get,s = set,d = del,l = list");
    }

    Database_close(conn);
    
    return 0;
}

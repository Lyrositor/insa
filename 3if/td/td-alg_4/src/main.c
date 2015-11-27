#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ht_table ht_table;
typedef struct ht_cell ht_cell;
typedef enum ht_cell_status ht_cell_status;

ht_table * ht_init(int size);
void ht_insert(ht_table * hash_table, char key[100], char value[100]);
void ht_delete(ht_table * hash_table, char key[100]);
ht_cell * ht_query(ht_table * hash_table, char key[100]);
void ht_stats(ht_table * hash_table);
void ht_destroy(ht_table * hash_table);

unsigned int shift_rotate(unsigned int val, unsigned int n);
unsigned int hash(char chaine[100], int m);
void error(void);

struct ht_table {
    int size;
    ht_cell * cells;
};

enum ht_cell_status {
    EMPTY,
    USED,
    DELETED
};

struct ht_cell {
    ht_cell_status status;
    char key[100];
    char value[100];
};

int main(void)
{
    int size;
    char lecture[100];
    char key[100];
    char val[100];
    ht_table * hash_table;

    if (fscanf(stdin, "%99s", lecture) != 1)
        error();
    while (strcmp(lecture, "bye") != 0)
    {
        if (strcmp(lecture, "init") == 0)
        {
            if (fscanf(stdin, "%99s", lecture) != 1)
                error();
            size = atoi(lecture);
            hash_table = ht_init(size);
        }
        else if (strcmp(lecture, "insert") == 0)
        {
            if (fscanf(stdin, "%99s", lecture) != 1)
                error();
            strcpy(key, lecture);
            if (fscanf(stdin, "%99s", lecture) != 1)
                error();
            strcpy(val, lecture);
            ht_insert(hash_table, key, val);
        }
        else if (strcmp(lecture, "delete") == 0)
        {
            if (fscanf(stdin, "%99s", lecture) != 1)
                error();
            strcpy(key, lecture);
            ht_delete(hash_table, key);
        }
        else if (strcmp(lecture, "query") == 0)
        {
            if (fscanf(stdin, "%99s", lecture) != 1)
                error();
            strcpy(key, lecture);
            ht_cell * q = ht_query(hash_table, key);
            if (q == NULL || q->status == DELETED)
            {
                printf("Not found\r\n");
            }
            else
            {
                printf("%s\r\n", q->value);
            }

        }
        else if (strcmp(lecture, "destroy") == 0)
        {
            ht_destroy(hash_table);
        }
        else if (strcmp(lecture, "stats") == 0)
        {
            ht_stats(hash_table);
        }

        if (fscanf(stdin, "%99s", lecture) != 1)
            error();
    }
    return 0;
}

ht_table * ht_init(int size)
{
    int i;
    ht_table * hash_table = malloc(sizeof(ht_table));
    hash_table->size = size;
    hash_table->cells = (ht_cell *) malloc(size*sizeof(ht_cell));
    for (i = 0; i < size; i++)
    {
        hash_table->cells[i].status = EMPTY;
    }
    return hash_table;
}

void ht_insert(ht_table * hash_table, char key[100], char value[100])
{
    unsigned int h_key = hash(key, hash_table->size);
    unsigned int i = h_key;
    ht_cell * q = ht_query(hash_table, key);
    for (;;)
    {
        if (hash_table->cells[i].status == EMPTY)
        {
            hash_table->cells[i].status = USED;
            strcpy(hash_table->cells[i].key, key);
            strcpy(hash_table->cells[i].value, value);
            break;
        }
        else if (hash_table->cells[i].status == USED &&
                    strcmp(hash_table->cells[i].key, key) == 0)
        {
            strcpy(hash_table->cells[i].value, value);
            break;
        }
        else if (hash_table->cells[i].status == DELETED)
        {
            if (q != NULL && (q->status == USED || q->status == DELETED))
            {
                q->status = USED;
                strcpy(q->key, key);
                strcpy(q->value, value);
                break;
            }
            else
            {
                hash_table->cells[i].status = USED;
                strcpy(hash_table->cells[i].key, key);
                strcpy(hash_table->cells[i].value, value);
                break;
            }
        }
        i = (i + 1) % hash_table->size;
        if (i == h_key)
        {
            break;
        }
    }
}

void ht_delete(ht_table * hash_table, char key[100])
{
    ht_cell * q = ht_query(hash_table, key);
    if (q != NULL)
    {
        q->status = DELETED;
    }
}

ht_cell * ht_query(ht_table * hash_table, char key[100])
{
    unsigned int h_key = hash(key, hash_table->size);
    unsigned int i = h_key;
    for (;;)
    {
        if ((hash_table->cells[i].status == USED ||
                hash_table->cells[i].status == DELETED) &&
                strcmp(hash_table->cells[i].key, key) == 0)
        {
            return &hash_table->cells[i];
        }
        i = (i + 1) % hash_table->size;
        if (i == h_key)
        {
            return NULL;
        }
    }
}

void ht_stats(ht_table * hash_table)
{
    int empty = 0, deleted = 0, used = 0;
    int i;
    for (i = 0; i < hash_table->size; i++)
    {
        if (hash_table->cells[i].status == EMPTY)
        {
            empty++;
        }
        else if (hash_table->cells[i].status == USED)
        {
            used++;
        }
        else
        {
            deleted++;
        }
    }
    printf("size    : %d\r\n", hash_table->size);
    printf("empty   : %d\r\n", empty);
    printf("deleted : %d\r\n", deleted);
    printf("used    : %d\r\n", used);
}

void ht_destroy(ht_table * hash_table)
{
    free(hash_table->cells);
    free(hash_table);
}

/* encodage d'une chaine de caracteres sous la forme d'un entier non signe */
unsigned int shift_rotate(unsigned int val, unsigned int n)
{
    n = n % (sizeof(unsigned int)*8);
    return (val << n) | (val >> (sizeof(unsigned int)*8 - n));
}

/* fonction de hachage d'une chaine de caracteres */
unsigned int hash(char chaine[100], int m)
{
    int i;
    unsigned int h = 0;
    for (i = 0; i < strlen(chaine); i++)
    {
        h = h + shift_rotate(chaine[i], i*7);
    }
    return h % m;
}

void error(void)
{
    printf("input error\r\n");
    exit(0);
}
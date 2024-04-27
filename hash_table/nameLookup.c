#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct KeyValuePair
{
    int rollNumber;
    char *name;
    struct KeyValuePair *next;
} KeyValuePair;

typedef struct HashTable
{
    KeyValuePair *table[TABLE_SIZE];
} HashTable;

int hash(int rollNumber)
{
    return rollNumber % TABLE_SIZE;
}

KeyValuePair *create_pair(int rollNumber, const char *name)
{
    KeyValuePair *pair = (KeyValuePair *)malloc(sizeof(KeyValuePair));
    pair->rollNumber = rollNumber;
    pair->name = strdup(name);
    pair->next = NULL;
    return pair;
}

void insert(HashTable *ht, int rollNumner, const char *name)
{
    int index = hash(rollNumner);
    KeyValuePair *new_pair = create_pair(rollNumner, name);

    if (ht->table[index] == NULL)
    {
        ht->table[index] = new_pair;
    }
    else
    {
        KeyValuePair *current = ht->table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_pair;
    }
}

const char* lookup(HashTable *ht, int rollNumber){
    int index = hash(rollNumber);
    KeyValuePair *current = ht->table[index];

    while (current != NULL)
    {
        if(current->rollNumber == rollNumber){
            return current->name;
        }
        current = current->next;
    }
    return "";
}

void free_table(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValuePair *current = ht->table[i];
        while (current != NULL)
        {
            KeyValuePair *temp = current;
            current = current->next;
            free(temp->name);
            free(temp);
        }
    }
}

int main()
{
    HashTable ht;
    memset(&ht, 0, sizeof(HashTable));

    int N;
    printf("Enter the number of colleagues: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        int rollNumber;
        char name[50];
        printf("Enter roll number and name of colleague %d: ", i + 1);
        scanf("%d %s", &rollNumber, name);
        insert(&ht, rollNumber, name);
    }

    int q;
    printf("Enter the number of queries: ");
    scanf("%d", &q);

    for (int i = 0; i < q; i++)
    {
        int rollNumber;
        printf("Enter roll number for query %d: ", i + 1);
        scanf("%d", &rollNumber);
        const char *name = lookup(&ht, rollNumber);
        printf("Name for roll number %d: %s\n", rollNumber, name);
    }

    free_table(&ht);

    return 0;
}

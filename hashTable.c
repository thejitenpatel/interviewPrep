#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Define the structure for a key-value pair
typedef struct KeyValuePair
{
    char *key;
    int value;
    struct KeyValuePair *next;
} KeyValuePair;

// Define the structure for the hash table
typedef struct HashTable
{
    KeyValuePair *table[TABLE_SIZE];
} HashTable;

// Hash function to calculate the index for a given key
unsigned int hash(const char *key)
{
    unsigned int hash_value = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash_value = 31 * hash_value + key[i];
    }
    return hash_value % TABLE_SIZE;
}

// Create a new key-value pair
KeyValuePair *create_pair(const char *key, int value)
{
    KeyValuePair *pair = (KeyValuePair *)malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = value;
    pair->next = NULL;
    return pair;
}

// Insert a key-value pair into the hash table
void insert(HashTable *ht, const char *key, int value)
{
    unsigned int index = hash(key);
    KeyValuePair *new_pair = create_pair(key, value);

    // Check if the slot is empty
    if (ht->table[index] == NULL)
    {
        ht->table[index] = new_pair;
    }
    else
    {
        // Handle collision by chaining
        KeyValuePair *current = ht->table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_pair;
    }
}

// Lookup the value associated with a key in the hash table
int lookup(HashTable *ht, const char *key)
{
    unsigned int index = hash(key);
    KeyValuePair *current = ht->table[index];

    // Traverse the linked list at the index
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }

    // Key not found
    return -1;
}

// Free the memory allocated for the hash table
void free_table(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        KeyValuePair *current = ht->table[i];
        while (current != NULL)
        {
            KeyValuePair *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
}

int main()
{
    HashTable ht;
    memset(&ht, 0, sizeof(HashTable));

    insert(&ht, "apple", 10);
    insert(&ht, "banana", 20);
    insert(&ht, "cherry", 30);

    printf("Value for key 'apple': %d\n", lookup(&ht, "apple"));
    printf("Value for key 'banana': %d\n", lookup(&ht, "banana"));
    printf("Value for key 'cherry': %d\n", lookup(&ht, "cherry"));
    printf("Value for key 'grape': %d\n", lookup(&ht, "grape"));

    free_table(&ht);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringBuffer
{
    char *data;
    size_t length;
    size_t capacity;
} StringBuffer;

void StringBufferInit(StringBuffer *buffer)
{
    buffer->data = NULL;
    buffer->length = 0;
    buffer->capacity = 0;
}

void append(StringBuffer *buffer, const char *str)
{
    size_t str_len = strlen(str);
    size_t new_len = buffer->length + str_len;

    if (new_len >= buffer->capacity)
    {
        size_t new_capacity = (buffer->capacity == 0) ? 1 : 2 * buffer->capacity;

        while (new_capacity <= new_len)
        {
            new_capacity *= 2;
        }
        char *new_data = realloc(buffer->data, new_capacity);
        if (new_data == NULL)
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return;
        }

        buffer->data = new_data;
        buffer->capacity = new_capacity;
    }

    memcpy(buffer->data + buffer->length, str, str_len);
    buffer->length = new_len;
    buffer->data[buffer->length] = '\0';
}

void freeStringBuffer(StringBuffer *buffer)
{
    free(buffer->data);
    buffer->data = NULL;
    buffer->length = 0;
    buffer->capacity = 0;
}

int main()
{
    StringBuffer buffer;
    StringBufferInit(&buffer);

    append(&buffer, "Hello, ");
    append(&buffer, "World!");

    printf("Buffer content: %s\n", buffer.data);

    freeStringBuffer(&buffer);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *array;
    int capactiy;
    int size;
} ArrayList;

ArrayList *create_array_list(int initialCapacity)
{
    ArrayList *list = (ArrayList *)malloc(sizeof(ArrayList));

    if (list == NULL)
    {
        fprintf(stderr, "Memory allocation failed \n");
        exit(EXIT_FAILURE);
    }

    list->array = (int *)malloc(initialCapacity * sizeof(int));
    if (list->array == NULL)
    {
        fprintf(stderr, "Memory allocation failed \n");
        free(list);
        exit(EXIT_FAILURE);
    }

    list->capactiy = initialCapacity;
    list->size = 0;
    return list;
}

void add_element(ArrayList *list, int element)
{
    if (list->size >= list->capactiy)
    {
        list->capactiy *= 2;
        list->array = (int *)realloc(list->array, list->capactiy * sizeof(int));
        if (list->array == NULL)
        {
            fprintf(stderr, "Memory allocation failed \n");
            exit(EXIT_FAILURE);
        }
    }

    list->array[list->size++] = element;
}

void printArrayList(ArrayList *list)
{
    printf("ArrayList elements: ");
    for (int i = 0; i < list->size; i++)
    {
        printf("%d ", list->array[i]);
    }
    printf("\n");
}

void freeArrayList(ArrayList *list)
{
    free(list->array);
    free(list);
}

int main()
{
    ArrayList *list = create_array_list(1);
    add_element(list, 10);
    add_element(list, 20);
    add_element(list, 30);
    add_element(list, 40);

    printArrayList(list);

    freeArrayList(list);
    return 0;
}

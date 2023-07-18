#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_LENGTH 256

typedef struct {
    int **data;
    char **vertices;
    int size;
} AdjMatrix;

AdjMatrix *blank_matrix(int size)
{
    AdjMatrix *matrix = (AdjMatrix *)malloc(sizeof(AdjMatrix));
    int **data = (int **)malloc(sizeof(int *) * size);
    char **vertices = (char **) malloc(sizeof(char*) * size);

    // Malloc memory for data array
    for (int i = 0; i < size; i++) {
        data[i] = (int *)malloc(sizeof(int) * size);
        for (int j = 0; j < size; j++) {
            data[i][j] = 0;
        }
    }

    // Malloc memory for vertices
    for (int i = 0; i < size; i++) {
        vertices[i] = (char *)malloc(sizeof(char) * MAX_LENGTH);
        vertices[i][0] = '\0';
    }

    matrix->data = data;
    matrix->size = size;
    matrix -> vertices = vertices;
    return matrix;
}

void free_matrix(AdjMatrix *matrix)
{
    for (int i = 0; i < matrix->size; i++) {
        free(matrix->data[i]);
        free(matrix -> vertices[i]);
    }
    free(matrix->data);
    free(matrix->vertices);
    free(matrix);
}

void print_matrix(AdjMatrix *matrix)
{
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < matrix->size; i++)
    {
        for (int j = 0; j < matrix->size; j++)
        {
            printf("%d ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

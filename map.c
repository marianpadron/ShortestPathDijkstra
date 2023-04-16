/**
* CS 5008
* Spring 2023
* Marian Padron
* HW 11 shortest path
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adj_matrix.c"


#define MAX_VERTICES 100
#define MAX_LENGTH 256
#define MAX_VERTICES 100
#define MAX_LENGTH 256


void add_vertices(const char* vertices_file, AdjMatrix* matrix) {
    // Open file
    FILE *file = fopen(vertices_file, "r");
    if (file == NULL) {
        printf("Error opening vertices file.\n");
        return;
    }

    char buffer[MAX_LENGTH];
    int num_lines = 0;

    while (fgets(buffer, MAX_LENGTH, file) != NULL) {
        strcpy(matrix -> vertices[num_lines], buffer); // copy line to array
        num_lines++;
    }
    
    for(int i = 0; i < matrix -> size; i++) printf("%s\n", matrix->vertices[i]);
    fclose(file);

}

/**
* Counts how many vertices are within the vertices file to get the size of the array.
*/
int count_vertices(const char* vertices_file) {
    // Open file
    FILE *file = fopen(vertices_file, "r");
    if (file == NULL) {
        printf("Error opening vertices file.\n");
        return 0;
    }

    // Count non-empty lines of text
    int count = 0;
    char c;
    int has_text = 0;  // flag to track whether lines has text
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            if (has_text) {
                count++;
            }
            has_text = 0;
        } else if (c != ' ' && c != '\t' && c != '\r') { // check if the character is not a whitespace
            has_text = 1;
        }
    }
    // Increment count if last line has text
    if (has_text) {
        count++;
    }

    fclose(file);
    return count;
}

/**
* Main to run shortest distance program.
*/
int main(int argc, char const *argv[]) {
    // Check files passed
    if (argc < 3) {
        printf("Error: Please load vertices file and distances file.\n");
        return 1;
    }

    // Read files
    const char* vertices_file = argv[1]; 
    const char* distances_file = argv[2];

    // Get size of matrix
    int size = count_vertices(vertices_file);
    
    // Create matrix
    AdjMatrix* matrix = blank_matrix(size);
    add_vertices(vertices_file, matrix);



    //print_matrix(matrix);
    //for (int i = 0; i < size; i++) printf("%s\n", matrix->vertices[i]);

    

    free_matrix(matrix);

}
/**
* CS 5008
* Spring 2023
* Marian Padron
* HW 11 shortest path
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "adj_matrix.c"


#define MAX_VERTICES 100
#define MAX_LENGTH 256
#define MAX_VERTICES 100
#define MAX_LENGTH 256

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
* Reads vertices files and adds vertices into matrix vertices array.
*/
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
        // Remove new line char
        buffer[strcspn(buffer, "\n")] = '\0';
        // Copy string to vertices array and null-terminate it
        strncpy(matrix->vertices[num_lines], buffer, MAX_LENGTH - 1);
        matrix->vertices[num_lines][MAX_LENGTH - 1] = '\0';
        num_lines++;
    }
    
    //for(int i = 0; i < matrix -> size; i++) printf("%s\n", matrix->vertices[i]);
    fclose(file);

}

/**
* Finds the index of a vertex within the matrix vertices array.
*/
int find_index(char* vertex, AdjMatrix* matrix) {
    for (int i = 0; i < matrix -> size; i++) {
        if(strcmp(vertex, matrix -> vertices[i]) == 0) {
            return i;
        }
    }
    printf("Vertex was not found.\n");
    return -1;

}

/**
* Reads distances file and adds distances to adjacency matrix.
*/
void add_distances(const char* distances_file, AdjMatrix* matrix) {
     // Open file
    FILE *file = fopen(distances_file, "r");
    if (file == NULL) {
        printf("Error opening distances file.\n");
        return;
    }

    char buffer[MAX_LENGTH];
    //int num_lines = 0;

    while (fgets(buffer, MAX_LENGTH, file) != NULL) {
        // Initialize varibles for cities and distance
        char from_city[MAX_LENGTH];
        char to_city[MAX_LENGTH];
        int distance;
        
        // Get index locations for the cities
        if (sscanf(buffer, "%s %s %d", from_city, to_city, &distance) == 3) {
            int from_index = find_index(from_city, matrix);
            int to_index = find_index(to_city, matrix);

            // If found valid index for both add to adjacency matrix
            if (from_index != -1 && to_index != -1) {
                matrix -> data[from_index][to_index] = distance;
                matrix -> data[to_index][from_index] = distance;
            }
        }
        // // Remove new line char
        // buffer[strcspn(buffer, "\n")] = '\0';
        // // Copy string to vertices array and null-terminate it
        // strncpy(matrix->vertices[num_lines], buffer, MAX_LENGTH - 1);
        // matrix->vertices[num_lines][MAX_LENGTH - 1] = '\0';
        // num_lines++;
    }
    
    //for(int i = 0; i < matrix -> size; i++) printf("%s\n", matrix->vertices[i]);
    fclose(file);
}

/**
* Prints valid commands to user.
*/
void print_commands() {
    printf("Commands:\n");
    printf("\tlist - list all cities\n");
    printf("\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\thelp - print this help message\n");
    printf("\texit - exit the program\n");
}

/**
* Prints vertices in matrix -> vertices to user.
*/
void print_vertices(AdjMatrix* matrix) {
    for (int i = 0; i < matrix -> size; i++) {
        printf("%s\n", matrix -> vertices[i]);
    }
}

void print_path(int* previous, int from_index, int to_index) {
    if (previous[to_index] == -1) {
        printf("%d", to_index);
        return;
    }
    print_path(previous, from_index, previous[to_index]);
    printf(" -> %d", to_index);
}

/**
* Prints the shortest path found between vertices to the user.
*/
void print_shortest_path(int from_index, int to_index, AdjMatrix* matrix, int* prev) {
    
    int path[matrix -> size];
    int path_len = 0;
    int curr = to_index;

    // Print if path not found
    if(prev[curr] == -1) {
        fprintf(stderr, "Path Not Found.\n");
        return;
    }

    // Iterate through prev indexes to find path to to_index
    printf("Path was found...\n");
    while(curr != -1) {
        path[path_len] = curr;
        path_len++;
        curr = prev[curr];
    }

    // Go through index list
    for (int i = path_len - 1; i >= 0; i--) {
        printf("%s\n", matrix -> vertices[path[i]]);
    }
    printf("\n");

}

/**
* Finds the shortest path given two vetices and a adjacency matrix.
* Returns -1 if unable to find path.
*/
int shortest_path(int from_index, int to_index, AdjMatrix* matrix) {
    // Initialize arrays for algorithm
    int visited [matrix -> size];
    int prev [matrix -> size];
    int dist [matrix -> size];

    // Give place holder values
    for(int i = 0; i < matrix -> size; i++) {
        visited[i] = 0;
        prev[i] = -1;
        dist[i] = INT_MAX;
    }

    // Set distance of current location to 0
    dist[from_index] = 0;

    // Find shortest path 
    for (int i = 0; i < matrix -> size; i++) {
        // Find vertex with minimum distance
        int min_dist = INT_MAX;
        int min_index = -1;
        for (int j = 0; j < matrix -> size; j++) {
            if(visited[j] == 0 && dist[j] < min_dist) {
                min_dist = dist[j];
                min_index = j;
            }
        }

        if (min_dist == INT_MAX) break;

        visited[min_index] = 1;

        // Update distances
        for (int j = 0; j < matrix -> size; j++) {
            if (matrix -> data[min_index][j] != 0) {
                int other_dist = dist[min_index] + matrix -> data[min_index][j];
                if (visited[j] == 0 && other_dist < dist[j]) {
                    dist[j] = other_dist;
                    prev[j] = min_index;
                }
            }
        }
    }

    // Print shortest path to user
    print_shortest_path(from_index, to_index, matrix, prev);
    return dist[to_index];

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

    // Hold files
    const char* vertices_file = argv[1]; 
    const char* distances_file = argv[2];

    // Get size of matrix
    int size = count_vertices(vertices_file);
    
    // Create matrix
    AdjMatrix* matrix = blank_matrix(size);
    add_vertices(vertices_file, matrix);
    add_distances(distances_file, matrix);
    //printf("%d\n", find_index("b", matrix));
    print_matrix(matrix);

    // Initialize splash
    printf("******* Welcome to the shortest path finder! *******\n");
    print_commands();
    printf("********************************************************\n");

    // Get user commands
    while (1) {
        // Get input
        printf("Where do you want to go today? ");
        char input[MAX_LENGTH];
        fgets(input, MAX_LENGTH, stdin);
        char* from_city = strtok(input, " \n");
        char* to_city = strtok(NULL, " \n");

        // Loop through commands
        // Exit
        if(strcmp(from_city, "exit") == 0) {
            printf("You have exited. Goodbye!\n");
            break;
        
        // List
        } else if (strcmp(from_city, "list") == 0) {
            printf("Available cities: \n");
            print_vertices(matrix);

        // Help
        } else if (strcmp(from_city, "help") == 0) {
            print_commands();

        // If empty
        } else if (from_city == NULL || to_city == NULL) {
            printf("Invalid Command\n");
            print_commands();

        // If provides two cities
        } else {
            // Find city indexes
            int from_index = find_index(from_city, matrix);
            int to_index = find_index(to_city, matrix);

            // Check valid cities
            if (from_index == -1 || to_index == -1) {
                printf("Invalid cities\n");

            // If valid find shortest path
            } else {
                int length = shortest_path(from_index, to_index, matrix);
                if (length != INT_MAX) printf("Total Distance: %d.\n", length);
            }
        }
    }
    
    free_matrix(matrix);

}
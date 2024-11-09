#include <stdio.h>
#include <string.h>

int find_movie(FILE *movies, char find[]) {

    char buffer[256];
    int lineCount = 1;

    while (fgets(buffer, sizeof(buffer), movies)) {

        for (int i = 0; i < sizeof(buffer); i++) {
            if (buffer[i] == find[0]) {
                int found = 1;
                for (int j = 1; j < strlen(find); j++) {
                    if (buffer[i+j] != find[j]) found = 0;
                }
                if (found) {
                    // TODO rewind pointer to file start
                    return lineCount/5+1; // Return the movie number
                }
            }
        }

        lineCount++;

    }

    return -1;

}
    
void print_movie(FILE *movies, int movieNum) {

}




int main(void) {

FILE *movies = fopen("movies", "r");

char find[32];
printf("Enter movie to find: ");
fgets(find, 32, stdin);
find[strcspn(find, "\n")] = '\0';  // Remove newline from find[]

if (movies == NULL) {
    perror("Error opening file\n");
    return 1;
}

printf("Movie Number: %d", find_movie(movies, find));
fclose(movies);
}
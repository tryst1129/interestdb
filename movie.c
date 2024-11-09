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
                if (found) return lineCount;
            }
        }

        lineCount++;

    }

    return -1;

}
    

    
int main(void) {

FILE *movies = fopen("movies", "r");
char find[32];
printf("Enter movie to find: ");
fgets(find, 32, stdin);
// for (int i = 0; i < strlen(find); i++) {
//     if (find[i] == '\n') find[i] = '\0';
// }
find[strcspn(find, "\n")] = '\0';  // Remove newline from find[]

if (movies == NULL) {
    perror("Error opening file\n");
    return 1;
}

printf("line: %d", find_movie(movies, find));
fclose(movies);
}
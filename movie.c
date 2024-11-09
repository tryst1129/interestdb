#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON.h>



int main(void) {

char title[20];
char watchdates[11];
char status[11];
int score;
char comments[256];

// open file
FILE *fp = fopen("data.json", "a+");
if (fp == NULL) {
    printf("Error: unable to open fp.json\n");
    return 1;
}

// get file size
fseek(fp, 0, SEEK_END);
long file_size = ftell(fp);
fseek(fp, 0, SEEK_SET);

// allocate buffer with file size
char *buffer = (char *)malloc(file_size + 1); // + 1 for \0
if (buffer == NULL) {
    printf("Error: memory allocation failed");
    fclose(fp);
    return 1;
}

// put file into buffer
fread(buffer, 1, file_size, fp); // 1 = 1 byte per character
fclose (fp);

// add null terminator (\0)
buffer[file_size] = '\0';

// parse into cJSON object
cJSON *json = cJSON_Parse(buffer);
if (json == NULL) { // TODO this would be a good place to use cJSON_GetErrorPtr()
    printf("Error: parsing buffer failed");
    return 1;
} 

// get movies object
cJSON *movies = cJSON_GetObjectItemCaseSensitive(json, "movies");
if (!cJSON_IsArray(movies)) {
    printf("Error: \"movies\" is not an array");
    return 1;
}

int movie_count = cJSON_GetArraySize(movies);
for (int i = 0; i < movie_count; i++) {
    cJSON *movie = cJSON_GetArrayItem(movies, i);
    cJSON *title = cJSON_GetObjectItemCaseSensitive(movie, "title");
    printf("Movie %d: %s\n", i+1, cJSON_GetStringValue(title));
}

cJSON_Delete(json);
free(buffer);
// fclose(fp);
}
#ifndef STRUCT_MOVIE_H
#define STRUCT_MOVIE_H

#define MOVIE_TITLE_LEN 26
#define SURNAME_DIRECTOR_LEN 26

typedef struct {
    char title[MOVIE_TITLE_LEN];
    char director[SURNAME_DIRECTOR_LEN];
    int year;
} movie_t; 

#endif 

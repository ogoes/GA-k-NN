#ifndef FILE_H
#define FILE_H


int get_line_size (FILE *);
long get_lines_number (FILE *);
long get_features_number(char []);
char * get_line (FILE *, int);
void write_line (FILE * file);
double * parse_line (char [], int);


#endif

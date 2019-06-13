#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_line_size (FILE *);
long get_lines_number (FILE *);
long get_features_number(char []);
char * get_line (FILE *, int);
void write_line (FILE * file);
double * parse_line (char [], int);


int get_line_size (FILE * file) {
  if (!file) return -1;

  int counter = 0;
  int charc = fgetc(file);
  while (charc != '\n') {
    ++counter;
    charc = fgetc(file);
  }

  fseek(file, 0, SEEK_SET);

  return ++counter;
}

long get_lines_number (FILE * file) {
  if (!file) return -1;

  long counter = 0;
  int charc = fgetc(file);
  while (!feof(file)) {
    if (charc == '\n') ++counter;
    charc = fgetc(file);
  }

  fseek(file, 0, SEEK_SET);

  return counter;
}

long get_features_number(char line[]) {
  long counter = 0;
  char * parsed;

  char delimiters[] = " ";

  parsed = strtok(line, delimiters);
  while (parsed != NULL) {
    counter += 1;
    parsed = strtok(NULL, delimiters);
  }

  return counter;
}

char * get_line (FILE * file, int back) {
  if (!file) return NULL;
  
  long len = get_line_size(file);

  char * line = (char *) calloc (len + 1, sizeof (char));
  fgets(line, len + 2, file);

  if (back == 0) fseek(file, 0, SEEK_SET);

  return line;
}


double * parse_line (char line[], int features_number) {

  double * values = (double *) calloc(features_number + 1, sizeof (double));

  char * value_parsed = strtok(line, " ");
  int value_index = 0;
  while (value_parsed != NULL) {
    values[value_index++] = atof(value_parsed);
    value_parsed = strtok(NULL, " ");
  }

  return values;

}




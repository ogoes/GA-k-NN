#ifndef STRUCTS_H
#define STRUCTS_H

typedef int function_t(int);


typedef struct element {
  long id;
  double * features;
  double norm;
} Element;

typedef struct classes {
  long id;
  int n_element;
  int size;
  int size_scale;
  Element ** elements;
} Class;

int LINE_SIZE = 0;
int LINES_NUMBER = 0;
int FEATURE_NUMBER = 0;

int initialize (Class *, long);
int insert_element (Class *, Element *);
Element * create_element(double *);
double get_norm (const Element *);
int compare (const void *, const void *);
void sort_by_norm (Element **);
int get_assert (Element **, int);
double calculate_norm (Element *, Element *, int *);


#endif


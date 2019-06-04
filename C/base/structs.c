#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structs.h"


int N_ELEMENTS = 0;

int initialize (Class * number, long id) {

  number->size = 10;
  number->size_scale = 1;  
  number->n_element = 0;
  number->id = id;

  number->elements = (Element **) calloc (number->size, sizeof (Element *));
  if (!number->elements) return -1;

  return 0;
}
int insert_element (Class * number, Element * element) {
  if (!element || !number) return -1;

  if (!number->elements) {
    number->elements = (Element **) calloc (number->size, sizeof (Element *));
    if (!number->elements) return -1;
  }

  number->elements[number->n_element++] = element;

  if (number->n_element == number->size) {
    number->size *= (++number->size_scale);
    Element ** aux = number->elements;

    number->elements = (Element **) calloc (number->size, sizeof (Element *));
    if (!number->elements) return -1;

    for (unsigned int i = 0; i < number->n_element; ++i) 
      number->elements[i] = aux[i];
  }

  return 0;
}
Element * create_element(double * features) {
  Element * E = (Element *) malloc (sizeof (Element));
  if (!E) return NULL;

  E->id = (int)features[FEATURE_NUMBER];
  E->features = features;

  return E;
}

double get_norm (const Element * E) {
  return E->norm;
}
int compare (const void * a, const void * b) {

  const void ** asa = (const void **) a;
  const void ** aba = (const void **) b;


  const double f = get_norm((const Element *) *asa);
  const double s = get_norm((const Element *) *aba);


  if (f > s) return  1;
  if (f < s) return -1;
  return 0;
}
void sort_by_norm (Element ** norms) {
  qsort (norms, N_ELEMENTS, sizeof (Element *), compare);
}

int get_assert (Element ** elements, int length) {
  int eles_l = 0;
  int counter[length];
  int moda;

  for (int i = 0; i < length; ++i) {
    for (int j = i + 1; j < length; ++j) {
      if (elements[i]->id == elements[j]->id) {
        counter[i]++;
        if (counter[i] > eles_l) {
          eles_l = counter[i];
          moda = i;
        }
      }
      counter[i] = 0;
    }
  }


  return elements[moda]->id;
}

double calculate_norm (Element * A, Element * B, function_t * calculate) {
  double norm = 0.0;

  for (unsigned int i = 0; i < FEATURE_NUMBER; ++i) {
    if ((*calculate)(i) == 0) {
      norm += pow(A->features[i] - B->features[i], 2);
    }
  }

  return sqrt(norm);
}

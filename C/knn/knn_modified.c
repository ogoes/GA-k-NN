#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "../base/structs.h"
#include "../base/file.h"


typedef struct cases {
  Element ** elements;
  long n_element;
  long size;
  int size_scale;
  long asserts;
} Case;



int LENGTH = 0;

Case TRAINING;

void init (const char filename[]) {
  TRAINING.asserts = 0;
  TRAINING.n_element = 0;
  TRAINING.size = 10;
  TRAINING.size_scale = 1;

  FILE * file = fopen(filename, "r");

  LINE_SIZE = get_line_size(file);
  LINES_NUMBER = get_lines_number(file);
  FEATURE_NUMBER = get_features_number(get_line(file, 0)) - 1;

  fclose(file);

}

int initialize (Class * number, long id) {

  number->size = 10;
  number->size_scale = 1;  
  number->n_element = 0;
  number->id = id;

  number->elements = (Element **) calloc (number->size, sizeof (Element *));
  if (!number->elements) return -1;

  return 0;
}

Element * create_element(double * values) {
  Element * E = (Element *) malloc (sizeof (Element));
  if (!E) return NULL;

  E->id = (int)values[FEATURE_NUMBER];
  E->features = values;

  if (!TRAINING.elements) {
    TRAINING.elements = (Element **) calloc (TRAINING.size, sizeof (Element *));
  }

  TRAINING.elements[TRAINING.n_element++] = E;

  if (TRAINING.n_element == TRAINING.size) {
    TRAINING.size *= (++TRAINING.size_scale);
    Element ** aux = TRAINING.elements;
    TRAINING.elements = (Element **) calloc (TRAINING.size, sizeof (Element *));

    for (unsigned int i = 0; i < TRAINING.n_element; ++i)
      TRAINING.elements[i] = aux[i];
  }

  return E;
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





double calculate_norm (Element * A, Element * B, function_t * calculate) {
  double norm = 0.0;

  for (unsigned int i = 0; i < FEATURE_NUMBER; ++i) {
    if ((*calculate)(i) == 0)
      norm += pow(A->features[i] - B->features[i], 2);
  }

  return sqrt(norm);
}

int calculate (int index) {
  return 0;
}



void sort_by_norm (Class * _class, Element ** norms) {
  qsort (norms, _class->n_element, sizeof (Element *), compare);
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

double get_norm (const Element * E) {
  return E->norm;
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


int training (const char * filename) {


  init(filename);

  Class numbers[10];
  for (int i = 0; i < 10; ++i) {
    if (initialize(&numbers[i], i) < 0) {
      return -1;
    }
  }


  FILE * file = fopen(filename, "r");

  char string[LINE_SIZE + 1];
  double * values;

  while (!feof(file)) {
    if (fgets(string, LINE_SIZE + 2, file) != NULL) {
      create_element(parse_line(string, FEATURE_NUMBER));
    }
  }

  fclose(file);
  return 0;
}
void teste (Element * E) {
  Element ** norms = TRAINING.elements;

  for (unsigned int i = 0; i < TRAINING.n_element; ++i) {
    norms[i]->norm = calculate_norm(E, norms[i], calculate);
  }

  sort_by_norm(&TRAINING, norms);

  if (get_assert(norms, LENGTH) == E->id) TRAINING.asserts++;
}

int testing (const char * filename, int length) {

  LENGTH = length;

  FILE * file = fopen(filename, "r");
  if (!file) return -1;

  char string[LINE_SIZE + 1];
  double * values;


  int ids = 0;
  while (!feof(file)) {
    if (fgets(string, LINE_SIZE + 2, file) != NULL) {

      Element * E = (Element *) malloc(sizeof(Element));
      values = parse_line(string, FEATURE_NUMBER);

      ids = (int)values[FEATURE_NUMBER];
      E->features = values;
      E->id = ids;
      teste(E);
      free(E->features);
      free(E);
      // return -1;
    }
  }



  printf("\n --- Para distância %i: %lu acertos -> %.3lf%%\n", LENGTH,TRAINING.asserts, 100*((double)TRAINING.asserts/(double)TRAINING.n_element));

  fclose(file);
  return 0;
}

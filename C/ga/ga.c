#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "../knn/knn.h"

int POPULATION_SIZE = 10;


typedef struct {
  int * features;
  double fitness;
} Gene;

typedef struct {
  int * features;
  double * fitness;
  const char * filename;
  int distance;
} Params;

void print_features(int * features) {
  for (int i = 0; i < FEATURE_NUMBER; ++i) {
    printf("%i ", features[i]);
  }
  printf("\n");
}

Gene * begin_population() {
  Gene * population = (Gene *) calloc (POPULATION_SIZE, sizeof (Gene));

  srand(time(NULL));  
  for (int i = 0; i < POPULATION_SIZE; ++i) {
    population[i].features = (int *) calloc(FEATURE_NUMBER, sizeof(int));

    for (int j = 0; j < FEATURE_NUMBER; ++j) {
      population[i].features[j] = rand() % 2;
      usleep(15);
    }

    population[i].fitness = (rand() % 1000) / 1000;
  }
  return population;
}


int compare_fitness (const void * left, const void * right) {

  Gene * a = (Gene *) left;
  Gene * b = (Gene *) right;


  const double f = a->fitness;
  const double s = b->fitness;


  if (f > s) return -1;
  if (f < s) return 1;
  return 0;
}

void sort (Gene * population) {
  qsort(population, POPULATION_SIZE, sizeof (Gene), compare_fitness);
}

void cross (int * g_features_a, int *  g_features_b) {

  int begin, end;

  int first_random_value = rand() % FEATURE_NUMBER;
  usleep(15);
  int second_random_value = rand() % FEATURE_NUMBER;
  usleep(15);

  if (first_random_value > second_random_value) {
    end = first_random_value;
    begin = second_random_value;
  } else if (first_random_value < second_random_value) {
    begin = first_random_value;
    end = second_random_value;
  } else {
    begin = first_random_value;
    end = begin + 1;
  }

  for (int j = begin; j < end; ++j) {
    int aux =  g_features_a[j];
    g_features_a[j] =  g_features_b[j];
    g_features_b[j] = aux;
  }
}

void crossing (Gene * population) {
  sort(population); // ordena por fitness

  int copy_length = 0.4 * POPULATION_SIZE;

  for (int i = 0; i < copy_length; ++i) {
    for (int j = 0; j < FEATURE_NUMBER; ++j) {
      population[i+copy_length].features[j] = population[i].features[j];
    }
  }

  for (int i = copy_length; i < POPULATION_SIZE; ++i) {
    if (i % 2 == 0) {
      cross(population[i].features, population[i+1].features);
    }
  }

}

void mutation (Gene * population, double mutation_probability) {
  int features_total_number = POPULATION_SIZE * FEATURE_NUMBER;
  int mutation_number = (mutation_probability * features_total_number);

  for (int i = 0; i < mutation_number; ++i) {
    int random_chromossomo = rand() % features_total_number;

    int counter = 0;
    for (int j = 0; j < POPULATION_SIZE; ++j) {
      for (int k = 0; k < FEATURE_NUMBER; ++k) {
        if (counter == random_chromossomo) {
          population[j].features[k] = (population[j].features[k] + 1) % 2;
        }
        ++counter;
      }
    }
  }
}

void * thread_f (void * args) {
  Params * dados = (Params*) args;
  *(dados->fitness) = testingGA(dados->filename, dados->distance, dados->features);
  pthread_exit (NULL);
}

void evaluate (Gene * population, const char * test_filename, const int distance) {

  for (int i = 0; i < POPULATION_SIZE; ++i) {
    population[i].fitness = testingGA(test_filename, distance, population[i].features);
  }
}

Gene best_fit(Gene * population) {
  sort(population);
  return population[0];
}






int main (int argc, char * argv[]) {

  // if (argc != 3) {
  //   errno = EBADF;
  //   perror("ERRO: Deve haver três argumentos [programa arquivo_de_treinamento arquivo_de_teste]");
  //   return EXIT_FAILURE;
  // }

  int distance = 1;

  if (training(argv[1]) < 0) return EXIT_FAILURE;

  double best = testing(argv[2], distance); 


  int * enabled = (int *) calloc (FEATURE_NUMBER, sizeof(int));
  for (int i = 0; i < FEATURE_NUMBER; ++i) enabled[i] = 1;

  printf("k: %i - Default Accuracy %.2lf%%\n", distance, best);

  free(enabled);

  Gene * pop = begin_population();
  int generation = 1;
  while (generation < 100) {
    clock_t start = clock();
    crossing(pop);
    mutation(pop, 0.01);
    evaluate(pop, argv[2], distance);
    Gene bestGen = best_fit(pop);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;


    printf("\033[0;32m %.2lfs \033[0m ", time_spent);



    if (bestGen.fitness > best) {
      printf("New best fitness - %.2lf%% - Gen %i\n", bestGen.fitness, generation);
      printf("FEATURES -> [");
      for (int i = 0; i < FEATURE_NUMBER; ++i) {
        printf("\033[0;36m%i\033[0m", bestGen.features[i]);
        if (i < FEATURE_NUMBER-1) printf(", ");
      }
      printf("]\n");
      best = bestGen.fitness;
    } else {
      printf("Gen %3i > Fitness %.2lf%%\n", generation, best);
    }
    ++generation;
  }
  for (int i = 0; i < POPULATION_SIZE; ++i) {
    free(pop[i].features);
  }
  free(pop);


  // sort(pop);
  //   // print_features(pop[i].features);
  //   // printf("%lf\n", pop[i].fitness);
  //   free(pop[i].features);
  // }



  // printf("accuracy: %lf%%\n", testing(argv[2], 1));

  return EXIT_SUCCESS;
}

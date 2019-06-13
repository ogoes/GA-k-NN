#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <getopt.h>
#include "../knn/knn.h"
#include "../base/argparse.h"

int POPULATION_SIZE = 10;


typedef struct {
  int * features;
  double fitness;
} Gene;


static int verbose_flag = 0;
static int best_fitness = 0;




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


void selection(Gene * population) {
  sort(population); // ordena por fitness

  int copy_length = 0.4 * POPULATION_SIZE;

  for (int i = 0; i < copy_length; ++i) {
    for (int j = 0; j < FEATURE_NUMBER; ++j) {
      population[i+copy_length].features[j] = population[i].features[j];
    }
  }
}

void crossing (Gene * population) {

  int copy_length = 0.4 * POPULATION_SIZE;

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

  // if (argc < 3) {
  //   errno = EBADF;
  //   perror("ERRO: Deve haver três argumentos [programa arquivo_de_treinamento arquivo_de_teste]");
  //   return EXIT_FAILURE;
  // }

  struct flag flags;

  flags.distance = 1;
  flags.mutation_p = 0.01;
  flags.test_filename = flags.train_filename = NULL;  

  parse(argc, argv, &flags);


  printf("mutation %lf\nbest %i\nverbose %i\ndistance %i\n", flags.mutation_p, best_fitness, verbose_flag, flags.distance);
  return 0;


  if (helper == 1) {
    printf("\"Escolha\" das melhores features aplicadas no k-NN -- Uso de algoritmos genéticos \n\
para definir quais características devem ser usadas para se obter uma acurácia maior \n\n\
\t [-h|--help]              Mostra esse manual\n\
\t [-b|--best]              Use uma string de bits a partir de um arquivo, salve os melhores resultados no arquivo\n\
\t [-v|--verbose]           Mostre os resultados das gerações\n\
\t [-k|--distance] INT      Valor do K usado no k-NN\n\
\t [-p|--porcent] INT       Porcentagem de mutação do algoritmo genético\n\
\t -f|--train-file FILE     Arquivo com as instâncias de treinamento (obrigatório)\n\
\t -t|--test-file FILE      Arquivo com as instâncias de teste (obrigatório)\n\
Este trabalho foi desenvolvido por Otávio Goes e Thais Zorawski. \n\
Para a matéria de Inteligência Artificial \n\
do 5º período do Curso de Bachareado em Ciência da Computação, pela UTFPR campus Campo Mourão\n");
    return 0;
  }

  if (!flags.train_filename || !flags.test_filename) {
    errno = EBADF;
    perror("Os dois arquivos são requeridos");
  }


  POPULATION_SIZE = 10;
  int distance = flags.distance;

  if (training(flags.train_filename) < 0) return EXIT_FAILURE;

  double best = testing(flags.test_filename, distance); 


  int * enabled = (int *) calloc (FEATURE_NUMBER, sizeof(int));
  for (int i = 0; i < FEATURE_NUMBER; ++i) enabled[i] = 1;

  if (verbose_flag)
    printf("k: %i - Default Accuracy %.2lf%%\n", distance, best);

  free(enabled);

  Gene * pop = begin_population();

  FILE * file;
  if (best_fitness) {
    char filename[] = {'b', 'e', 's', 't', flags.distance + 48, '.', 't', 'x', 't'};
    file = fopen(filename, "r");
    if (file) {
      double * feat = parse_line(get_line(file, 0), FEATURE_NUMBER);
      fclose(file);

      for (int i = 0; i < FEATURE_NUMBER; ++i) {
        pop[0].features[i] = (int) feat[i];
      }
      free(feat);
    }
  }



  int generation = 1;
  while (generation <= 100) {
    clock_t start = clock();
    selection(pop);
    crossing(pop);
    mutation(pop, flags.mutation_p);
    evaluate(pop, argv[2], distance);
    Gene bestGen = best_fit(pop);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    if (verbose_flag)
      printf("\033[0;32m %.2lfs \033[0m ", time_spent);
      
    if (bestGen.fitness > best) {

      if (best_fitness) {
        char filename[] = {'b', 'e', 's', 't', flags.distance + 48, '.', 't', 'x', 't'};
        file = fopen(filename, "a");
        for (int i = 0; i < FEATURE_NUMBER; ++i) {
            fprintf(file, "%i ", bestGen.features[i]);
        }
        fprintf(file, "\n%.2lf%%\n", bestGen.fitness);
        fclose(file);
      }
      if (verbose_flag) {
        printf("New best fitness - %.2lf%% - Gen %i\n", bestGen.fitness, generation);
        printf("FEATURES -> [");
        for (int i = 0; i < FEATURE_NUMBER; ++i) {
          printf("\033[0;36m%i\033[0m", bestGen.features[i]);
          if (i < FEATURE_NUMBER-1) printf(", ");
        }
        printf("]\n");
      }
      best = bestGen.fitness;
    } else {
      if (verbose_flag)
        printf("Gen %3i > Fitness %.2lf%%\n", generation, best);
    }
    ++generation;
  }
  for (int i = 0; i < POPULATION_SIZE; ++i) {
    free(pop[i].features);
  }
  free(pop);


  return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static int verbose_flag;
static int best_fitness;
static int helper;

struct flag {
  char * test_filename;
  char * train_filename;
  double mutation_p;
  int distance;
};

void parse (int argc, char ** argv, struct flag * flags){

  int c, k;
  static struct option long_options[] ={
    /* These options set a flag. */
    {"verbose", no_argument,       &verbose_flag, 1},
    {"best",   no_argument,       &best_fitness, 1},
    {"help",   no_argument,       &best_fitness, 1},
    /* These options don’t set a flag.
        We distinguish them by their indices. */
    {"train-file",  required_argument, 0, 'f'},
    {"test-file",  required_argument, 0, 't'},
    {"distance",  optional_argument, 0, 'k'},
    {"porcent",  optional_argument, 0, 'p'},
    {"h",  no_argument, 0, 'h'},
    {"v",  no_argument, 0, 'v'},
    {"b",  no_argument, 0, 'b'},

    {0, 0, 0, 0}
  };



  for (int i = 0; i < argc; ++i) {
    /* getopt_long stores the option index here. */
    int option_index = 0;

    c = getopt_long (argc, argv, "hvbp:t:f:k:",
                    long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1)
      break;

    switch (c) {
      case 0:
        if (long_options[option_index].flag != 0)
          break;
        break;

      case 'k':
        k = atoi(optarg);
        flags->distance = k > 0? k: 1;
        break;

      case 'p':
        k = atoi(optarg);
        flags->mutation_p = k/100.0;
        break;

      case 'f':
        flags->train_filename = optarg;
        break;

      case 't':
        flags->test_filename = optarg;
        break;

      case 'v':
        verbose_flag = 1;
        break;

      case 'b':
        best_fitness = 1;
        break;

      case 'h':
        helper = 1;
        break;

      case '?':
        /* getopt_long already printed an error message. */
        break;

      default:
        abort ();
    }
  }
}

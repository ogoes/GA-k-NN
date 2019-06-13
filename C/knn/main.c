
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "knn.h"


int main (int argc, char * argv[]) {

  if (argc != 3) {
    errno = EBADF;
    perror("ERRO: Deve haver três argumentos [programa arquivo_de_treinamento arquivo_de_teste]");
    return EXIT_FAILURE;
  }



  if (training(argv[1]) < 0) return EXIT_FAILURE;

  int enabled[] = {1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1};

  printf("Accuracy: %.2lf%%\n", testing(argv[2], 1));
  printf("Accuracy: %.2lf%%\n", testingGA(argv[2], 1, enabled));


  return EXIT_SUCCESS;
}

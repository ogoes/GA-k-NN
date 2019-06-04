
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
  if (testing(argv[2], 1) < 0) return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

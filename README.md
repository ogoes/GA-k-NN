# Projeto-IA

#### Escolha das melhores features aplicadas no k-NN -- Uso de algoritmos genéticos para definir quais características devem ser usadas para se obter uma acurácia maior.
## Este trabalho foi desenvolvido por Otávio Goes e Thais Zorawski. Para a matéria de Inteligência Artificial do 5º período do Curso de Bachareado em Ciência da Computação, pela UTFPR campus Campo Mourão

#### Como usar (only linux ); ) 

## Algoritmo Genético


Compilação:

    make GA

Para ver informações sobre o programa e execução e demais opções de configuração:

    ./ga -h
    ./ga --help

Para executar o programa, na pasta raíz execute a seguinte linha:\
  
  Quantidade de gerações = 10\
  Tamanho da população = 10\
  Probabilidade de mutação = 1%\
  Distância K = 1

    ./ga -f TRAIN_FILE_DIR -t TEST_FILE_DIR -v




## k-NN: Execução do k-NN para os 7 melhores resultados obtidos a partir do AG

  Distância K = 1

Compilação:
  
    make KNN

Execução:

    ./knn TRAIN_FILE_DIR TEST_FILE_DIR

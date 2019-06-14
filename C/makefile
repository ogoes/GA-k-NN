libs = -lm
compiler = gcc


GA:
	$(compiler) algoritmo_genetico/ga.c $(libs) -o ga

KNN:
	$(compiler) k-nn/main.c $(libs) -o knn

clean:
	[[ -f ga ]] && rm ga || 2> /dev/null
	[[ -f knn ]] && rm knn || 2> /dev/null 


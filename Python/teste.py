from pprint import pprint
from copy import deepcopy

def teste(population):
  copy = deepcopy(population[:1])
  cross = deepcopy(population[:1])

  cross[0]["c"][1] = 1

  pass
  return copy + cross




pop = teste([{"nome": "a", "c": [1, 0, 1, 1]}, {"nome": "b", "c": [1, 1, 1, 0]}])

pprint(pop)

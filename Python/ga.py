import argparse
import random
from pprint import pprint
import knn
import math
import time
f_x = lambda x: round(math.sin((math.pi * x)/256), 4) 

def bin_list_to_int (bin_list=[]): # 1 0 0
  reverse_list = bin_list[::-1] # 0 0 1
  integer = 0
  for (i, _) in enumerate(bin_list):
    integer += (reverse_list[i]) * (2**i)
    pass  
  pass
  return integer

def begin_population (size=10, chroms_size=10):
  population = []
  
  for i in range(size):
    chromossomos = [random.randint(0,1) for _ in range(chroms_size)]
    value = bin_list_to_int(chromossomos)
    gene = {
      "value": value,
      "chromossomos": chromossomos,
      "fitness": f_x(value)
    }
    population.append(gene)
    pass
  pass
  return population

def select (population=[]):
  number = [round(random.uniform(0, 1), 4) for _ in population]
  selected = []
  for ran in number:
    pre_acm = 0
    for gene in population:

      if pre_acm < ran < gene["f_acm"]:
        selected.append(gene)
      pre_acm = gene["f_acm"]

      pass
    pass
  pass
  return selected

def selection (popolation=[]):
  normal = sum([pop["fitness"] for pop in popolation])
  acm = 0.0
  for gene in popolation:
    gene["f_norm"] = round(gene["fitness"] / normal, 4)
    acm += gene["f_norm"]
    gene["f_acm"] = acm
    pass
  pass
  return select(popolation)

def cross (population=[]):
  cross_list = population[:-2]
  copy_list = population[-2:]

  for i in range(len(cross_list)):
    if i % 2 == 0:
      pair_a = cross_list[i]
      pair_b = cross_list[i+1]

      begin = random.randint(0, len(pair_a["chromossomos"])-1)
      end = random.randint(begin, len(pair_a["chromossomos"]))
      for j in range(begin, end):
        aux = pair_a["chromossomos"][j]
        pair_a["chromossomos"][j] = pair_b["chromossomos"][j]
        pair_b["chromossomos"][j] = aux
        pass
      pass
    pass

  pass
  return cross_list + copy_list

def mutation (population=[], mutation_p=0.01):
  n_chrom = len(population) * len(population[0]["chromossomos"])
  mutate_n = n_chrom * mutation_p

  if mutate_n - int(mutate_n) != 0:
    mutate_n = int(mutate_n + 1)

  for _ in range(mutate_n):
    chrom = random.randint(0, n_chrom)

    counter = 0
    for gene in population:
      for (i, _) in enumerate(gene["chromossomos"]):
        if counter == chrom:
          gene["chromossomos"][i] = (gene["chromossomos"][i] + 1) % 2
          pass
        counter += 1
    pass
  pass

def evaluate (population=[]):
  for gene in population:
    gene["fitness"] = f_x(bin_list_to_int(gene["chromossomos"]))
    pass
  pass

def bestFit (population=[]):
  list_c = population
  list_c.sort(key = lambda x: x["fitness"])
  return list_c[0]["fitness"]

if __name__ == "__main__":
  population = begin_population(8,8)
  t = 0
  while True:
    t += 1
    print("geração %i" %t, "Melhor fitness %f" %(bestFit(population)))
    population = selection(population)
    population = cross(population)
    mutation(population)
    evaluate(population)
    time.sleep(1)
    pass

  pass



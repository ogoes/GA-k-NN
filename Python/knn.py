#!/usr/bin/python3
from pprint import pprint
import argparse
from math import sqrt, pow



def parse_line(line):

  line_splitted = line.split(' ')

  values = {
    "features": [float(value) for value in line_splitted[:-1]],
    "class": int(line_splitted[-1])
  }

  return values

def get_values_from_file(filename):
  file = open(filename, 'r')
  lines = file.readlines()

  values = [parse_line(line) for line in lines]
  file.close()

  return values

def get_assert(norms):
  eles_l = 0
  counter = [0 for i in norms]
  moda = 0

  for i in range(len(norms)):
    for j in range(i+1, len(norms)):
      if norms[i]["class"] == norms[j]["class"]:
        counter[i] += 1
        if counter[i] > eles_l:
          eles_l = counter[i]
          moda = i
          pass
        pass
        counter[i] = 0
      pass
    pass

  return norms[moda]["class"]

def get_norms (train_value, test_value, enabled_features):
  norm = 0.0
  for (i, feature) in enumerate(test_value['features']):
    if enabled_features[i] == 1:
      norm += ((train_value["features"][i] - feature)**2)

  return sqrt(norm)

def test (training_filename, test_filename, enabled_features, k):
  _assert = 0
  training_values = get_values_from_file(training_filename)
  testing_values = get_values_from_file(test_filename)


  for test_value in testing_values:
    norms = []
    for train_value in training_values:
      norms.append({
        "norm": get_norms(test_value, train_value, enabled_features),
        "class": train_value["class"]
      })

    norms.sort(key = lambda x: x["norm"])
    # print(get_assert(norms[:k]))
    if get_assert(norms[:k]) == test_value["class"]:
      _assert += 1

    pass

  return 100 * _assert / len(testing_values)


enabled = [1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1]
print(sum(enabled))
# for i in range(1, 10):
#   print(i, test("../data/teste.txt", "../data/treinamento.txt", [1 for _ in range(133)] ,i))


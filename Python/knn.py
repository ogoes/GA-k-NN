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

def get_norms (train_value, test_value, k = 1):
  norm = 0.0
  for (i, feature) in enumerate(test_value['features']):
    norm += ((train_value["features"][i] - feature)**2)

  return sqrt(norm)

def test (training_filename, test_filename, k):
  _assert = 0
  training_values = get_values_from_file(training_filename)
  testing_values = get_values_from_file(test_filename)


  for test_value in testing_values:
    norms = []
    for train_value in training_values:
      norms.append({
        "norm": get_norms(test_value, train_value),
        "class": train_value["class"]
      })

    norms.sort(key = lambda x: x["norm"])
    # print(get_assert(norms[:k]))
    if get_assert(norms[:k]) == test_value["class"]:
      _assert += 1

    pass

  return 100 * _assert / len(testing_values)


if __name__ == "__main__":
  parser = argparse.ArgumentParser()

  parser.add_argument("-t", "--train", help = "Training filename", required = True, type = str)

  parser.add_argument("-p", "--test", help = "Testing filename", required = True, type = str)

  parser.add_argument("-k", "--distance", help = "Distance of k-NN", type = int)

  args = parser.parse_args()

  if args.distance != None:
    print("\n --- Para distância %i: %.1f%%" %(args.distance, test(args.train, args.test, args.distance)))
  else:
    print(test(args.train, args.test, 1))


  pass

import argparse
import random
from pprint import pprint
import knn
import math
import time
from math import sqrt, pow
f_x = lambda x: round(math.sin((math.pi * x)/256), 4)









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
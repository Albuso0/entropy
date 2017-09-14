#!/usr/bin/env python3
"""
Main file for running entropy estimators
"""

import argparse
from entropy import *

parser = argparse.ArgumentParser()
parser.add_argument("-k", type=int,
                    help="Alphabet size")
parser.add_argument("-L", type=int,
                    help="Polynoimal degree. Default c0*log(k)")
parser.add_argument("-M", type=int,
                    help="M/n is the right-end of approximation interval. Default c1*log(k)")
parser.add_argument("-N", type=int,
                    help="Threshold to apply polynomial estimator. Default c2*log(k)")
parser.add_argument("-fin", type=str,
                    help="fingerprint data file")
parser.add_argument("-hist", type=str,
                    help="histogram data file")
args = parser.parse_args()


if args.k is None:
    raise Exception('Please input k!')


entropy = Entropy(k=args.k)
if args.L is not None:
    entropy.degree = args.L
if args.M is not None:
    entropy.ratio = args.M
if args.N is not None:
    entropy.n_threhold = args.N


if args.fin is not None:
    fin = np.loadtxt(args.fin, dtype=int)
elif args.hist is not None:
    hist = np.loadtxt(args.hist, dtype=int)
    fin = hist_to_fin(hist)
else:
    raise Exception('Please input fingerprint or histogram!')

print("")
print("Parameters:")
print("Alphabet size\t\t=%d" % entropy.k)
print("Polynoimal degree\t=%d" % entropy.degree)
print("Approximation interval\t=[0,%.2f/n]" % entropy.ratio)
print("Plug-in threshold\t=%d" % (entropy.n_threhold+1))
print("")
print("Results:")
print("Sample size\t=%d" % get_sample_size(fin))
print("Plug in\t\t=%.6f bits" % entropy.estimate_plug(fin))
print("Miller Madow\t=%.6f bits" % entropy.estimate_Miller_Madow(fin))
print("Polynomial\t=%.6f bits" % entropy.estimate(fin))
print("")

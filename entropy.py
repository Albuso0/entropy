#!/usr/bin/env python3
"""
Main libraray for entropy estimation
"""

import linecache
from math import log, floor
import numpy as np

# def estimate():




class Entropy():
    """
    Entropy estimator
    """
    def __init__(self, k, L=None, M=None, N=None):
        """
        Args:
        k: int, required
        alphabet size

        L: int
        Polynoimal degree. Default c0*log(k)

        M: float
        M/n is the right-end of approximation interval. Default c1*log(k)

        N: int
        Threshold to apply polynomial estimator. Default c2*log(k)
        
        """
        self.k = k
        self.degree = L if L != None else floor(1.6*log(k))
        self.ratio = M if M != None else 3.5*log(k)
        self.n_threhold = N if N != None else floor(1.6*log(k))
        
    def estimate(self, fin):
        """
        Polynomial estimator form a given fingerprint

        Args:
        fin: list of tuples (frequency, count)
        fingerprint (profile) of samples, fin[i] is the number of symbols that appeared exactly i times
        """
        # get total sample size
        num = 0
        for freq, cnt in fin:
            num += freq * cnt

        # get linear estimator coefficients
        a_coeffs = read_coeffs(self.degree)
        g_coeffs = np.empty(self.n_threhold+1)
        for j in range(self.n_threhold+1):
            start = self.degree if j > self.degree else j
            g_coeffs[j] = a_coeffs[start]
            for i in range(start, 0, -1):
                g_coeffs[j] = a_coeffs[i-1] + g_coeffs[j] * (j-i+1) / self.ratio
            g_coeffs[j] = (g_coeffs[j] * self.ratio + log(num/self.ratio) * j)/num

        # get estimate
        h_estimate = 0
        sym_num = 0
        for freq, cnt in fin:
            sym_num += cnt
            if freq > self.n_threhold: # plug-in
                p_hat = 1.*freq/num
                h_estimate += (-p_hat*log(p_hat)+0.5/num)*cnt
            else: # polynomial
                h_estimate += g_coeffs[freq]*cnt
        
        h_estimate += 1.0*g_coeffs[0] * (self.k-sym_num)
        h_estimate = h_estimate if h_estimate > 0 else 0
        return h_estimate/log(2)

    # def estimator_Miller_Madow(self, fin): 

def read_coeffs(L):
    """
    read the coefficients from a given degree L
    """
    line = linecache.getline("coeffs.txt", L)
    return np.asarray(line.split()[1:]).astype(np.float)


def sample_to_fin(samples):
    """
    Return a fingerprint from samples
    """
    return hist_to_fin(sample_to_hist(samples))


def hist_to_fin(hist):
    """
    Return a fingerprint from histogram
    """
    freq = Counter()
    for x in hist:
        freq[x] += 1
    return freq.items()

def sample_to_hist(samples):
    """
    Return a histogram of samples
    """
    freq = Counter()
    for x in samples:
        freq[x] += 1
    return np.asarray(list(freq.values()))


class Counter(dict):
    """
    Class for counting items
    """
    def __missing__(self, key):
        return 0

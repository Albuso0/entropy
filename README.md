Entropy estimators
=================
We provide implementation of our [rate-optimal estimators](http://ieeexplore.ieee.org/abstract/document/7444171/) and some classical estimators in both Python and C++. 
This is a tutorial for both software users and developers who want to use entropy estimators! 



Table of contents
=================
* [Table of contents](#table-of-contents)
* [Python](#python)
* [C++](#c++)
* [References](#references)


Python
=====
This Python code works on Python3, and uses [Numpy](http://www.numpy.org), the fundamental package for scientific computing with Python.
Make sure Python3 and Numpy are properly installed before using this code. 

* [Instruction for installing Python3](https://docs.python.org/3/using/index.html)
* [Instruction for installing Numpy](https://www.scipy.org/install.html)

Basic script
-------
Here is an example on how to write a script to use entropy estimators:
```python
>>> from entropy import *
>>> entropy = Entropy(k=100000)
>>> fin = [[1,2910],[2,45]]
>>> entropy.estimate(fin)
15.794990467501666
```
The entropy estimate output ```15.794990``` is in bits.

* ```from entropy import *``` imports all functions from *entropy.py*;
* ```entropy = Entropy(k=100000)``` initializes an entropy estimator with alphabet size 100,000, an upper bound on the support size. We can use a conservative upper bound and the estimator is insensitive to that. In the case no upper bound is unavailable, an alternative option is to use the sample size. 
* ```fin = [[1,2910],[2,45]]``` is the fingerprint, represented by a list of tuples. This means 2910 symobols appeared exactly once, and 45 symbols appeared exactly twice. 
* ```entropy.estimate(fin)``` produces the entropy estimate using our rate-optimal estimator. The unit of output is bits. 

Functions
------
### Samples statistics
The entropy estimator requires an input of fingerprint. 
In case of raw data, we have functions for this statistics:
* ```sample_to_fin(sample)``` returns fingerprints of samples
  * input: a list of samples 
  * output: a list of tuples (fingerprints)
* ```hist_to_fin(hist)``` returns fingerprints from histogram (number of appearances/frequency counts)
  * input: a list of frequencies
  * output: a list of tuples (fingerprints)

### Other estimators
We implemented classical entropy estimators, and outputs are all in bits:  

* ```entropy.estimate_plug(fin)```: plug-in estimator
* ```entropy.estimate__Miller_Madow(fin)```: Miller-Madow estimator

Comprehensive script
---------
We provide ```main.py``` as an example script that can be used directly on data files.  
Type ```python3 main.py -k 100000 -fin fin_sample.txt``` or ```python3 main.py -k 100000 -hist hist_sample.txt``` to experiment on the fingerprint "fin\_sample.txt" or histogram "hist\_sample.txt" respectively, which are both the statistic of 3,000 samples generated by the uniform distribution over 100,000 symbols. 

### Program arguments

#### Main arguments:

* ```-k int```: set alphabet size. 
* ```-fin str```: set fingerprint input file. 
  Each line of file consists of two numbers: frequency *j*, the number of symbols that appears exactly *j* times.
* ```-hist str```: set histogram input file. 
  Each line of file consists of only one number: frequency *j*. Symbols are not needed.
* *k* must be provided. 
  Either *fin* or *hist* must be provided.
  If both *fin* and *hist* are provided, only *fin* will be read.
  
#### Optional arguments:

* ```-L int```: set polynomial degree. Default *L=1.6 log k*.
* ```-M float```: set the right endpoint of approximation interval. Default *M=3.5 log k*.
* ```-N int```: set the threshold to apply the polynomial estimator. Default *N=1.6 log k*.
* The parameters above can be combined, e.g., ```./entropy -k 100000 -fin fin_sample.txt -L 18 -M 40 -N 18```.
* ``` --help``` or ```-h```: see the list of arguments.





C++
=====
Compile and run
---------
Check out all source code, including the Makefile and .txt files.

Type ```make``` to compile the sources, you will get executable file *"entropy"*.

Type ```./entropy -k=100000 -fin=fin_sample.txt``` or ```./entropy -k=100000 -hist=hist_sample.txt``` to experiment on the fingerprint "fin\_sample.txt" or histogram "hist\_sample.txt" respectively, which are both the statistic of 3,000 samples generated by the uniform distribution over 100,000 symbols. 

### Program arguments

#### Main arguments:

* ```-k=number```: set alphabet size. 
* ```-fin=filename```: set fingerprint input file. 
  Each line of file consists of two numbers: frequency *j*, the number of symbols that appears exactly *j* times.
* ```-hist=filename```: set histogram input file. 
  Each line of file consists of only one number: frequency *j*. Symbols are not needed.
* *k* must be provided. 
  Either *fin* or *hist* must be provided.
  If both *fin* and *hist* are provided, only *fin* will be read.
  
#### Optional arguments:

* ```-L=number```: set polynomial degree. Default *L=1.6 log k*.
* ```-M=number```: set the right endpoint of approximation interval. Default *M=3.5 log k*.
* ```-N=number```: set the threshold to apply the polynomial estimator. Default *N=1.6 log k*.
* The parameters above can be combined, e.g., ```./entropy -k=100000 -fin=fin_sample.txt -L=18 -M=40 -N=18```.
* Type ```./entropy -help``` or ```./entropy -h``` to see the list of arguments.



## More for developers
For developer who want to write a new test scratch to test the entropy estimator, follow the example *main_test.cpp*.
After ```make``` you will also see the executable file *"test"*.

### Entropy estimator class: *Entropy*
Work flow: 

1. Set alphabet size *k* and several parameters: 
  * **setDegree(int L)**: the degree of polynomial is L.
  * **setInterval(int M)**: the approximation interval is [0,M/n], where n is the sample size.
  * **setThreshold(int N)**: the threshold to use polynomial estimator is when the histogram is at most N.
2. Input fingerprint or histogram. Use one of the following: 
  * **setFin( filename )**: each line of file consists of two numbers: frequency *j*, the number of symbols that appears exactly *j* times.
  * **setFin( freq, count )**: input two vectors of the same length: *freq[i]* represents frequency, and *count[i]* counts the number of symbols that appear exactly *freq[i]* times. 
  * **setHist( filename )**: each line of file consists of one number: frequency *j*. Symbols are not needed.
  * **setHist( freq )**: input one vector with frequencies.
3. Output various estimates: 
  * **estimate()**: our polynomial estimator
  * **estimate_plug()**: plug-in estimator
  * **estimate\_Miller\_Madow()**: Miller-Madow estimator



### Synthetic data experiments
For those who want to generate synthetic samples within C++, you can refer to the standard [random number generator facilities](http://www.cplusplus.com/reference/random/).
There are examples to generate random numbers according to different types of distributions.
If the distribution is not yet provided, you can use the general [discrete distribution](http://www.cplusplus.com/reference/random/discrete\_distribution/).
There are several ways to [construct discrete distributions](http://www.cplusplus.com/reference/random/discrete\_distribution/discrete\_distribution/).


Reference
===================
For detailed explanation of parameters, please refer to our paper [Minimax Rates of Entropy Estimation on Large Alphabets via Best Polynomial Approximation](http://ieeexplore.ieee.org/abstract/document/7444171/).
The parameters described in the paper are: *L=c<sub>0</sub> log k, M=c<sub>1</sub> log k, N=c<sub>2</sub> log k*.
As in the paper, the default values are *L=1.6 log k, M=3.5 log k, N=1.6 log k*.


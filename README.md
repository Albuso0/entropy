#Tutorial

##Compile
Check out all source code, including the Makefile.

Type *make*, we are done!

## Entropy estimator: *Entropy* class
Workflow: 

1. Set alphabet size *k* and several parameters: 
  * **setDegree(int L)**: the degree of polynomial is L.
  * **setInterval(int M)**: the approximation interval is [0,M/n], where n is the sample size.
  * **setThreshold(int N)**: the threshold to use polynomial estimator is when the histogram is at most N.
2. Input fingerprint with **setFin( std::string filename )**. 
  * Each line of file consists of two numbers: frequency *j*, the number of symbols that appears exactly *j* times.
3. Output various estimates: 
  * **estimate()**: our polynomial estimator
  * **estimate_plug()**: plug-in estimator
  * **estimate\_Miller\_Madow()**: Miller-Madow estimator


### Sample code *main_test.cpp*
In the sample code, we read fingerprint from "fin_sample.txt", which is the fingerprint of 3,000 samples generated from uniform distribution over 100,000 symbols.


### Synthetic data experiments
If you want to generate random samples within C++, you can refer to the internal [random number generator facilities](http://www.cplusplus.com/reference/random/).
There are sample codes to generate random numbers according to different types of distributions.
For general purpose, you can use [discrete distribution](http://www.cplusplus.com/reference/random/discrete_distribution/).


## Reference
For detailed explanation of parameters, please refer to the paper [Minimax rates of entropy estimation on large alphabets via best polynomial approximation, arXiv:1407.0381](http://arxiv.org/abs/1407.0381).
The paramters described in the paper are: *L=c<sub>0</sub> log k, M=c<sub>1</sub> log k, N=c<sub>2</sub> log k*.
As in the paper, the default values are *L=1.6 log k, M=3.5 log k, N=1.6 log k*.

#Tutorial

##Compile
Check out all source code, including the Makefile.

Type *$make*, we are done!

## Entropy estimator: *Entropy* class
Workflow: 

1. Set alphabet size *k* and several parameters: 
  * *setDegree(int L)*: the degree of polynomial is L.
  * *setInterval(int M)*: the approximation interval is [0,M/n], where n is the sample size.
  * *setThreshold(int N)*: the threshold to use polynomial estimator is when the histogram is at most N.
2. Input fingerprint with *entropy.setFin( std::string filename )*. 
  * Each line of file consists of two numbers: *frequency*, the number of symbols that appears exactly *frequency* number of times.
3. Output various estimates: 
  * entropy.estimate(): our polynomial estimator
  * entropy.estimate_plug(): plug-in estimator
  * entropy.estimate\_Miller\_Madow(): Miller-Madow estimator


## Sample code *mainentropy.cpp*
In the sample code, we read fingerprint from "fin_sample.txt", which is the fingerprint of 3000 samples generated from uniform distribution over 100,000 symbols.



## Reference
For detailed explanation of parameters, please refer to the paper *"Minimax rates of entropy estimation on large alphabets via best polynomial approximation, arXiv:1407.0381"*.
The paramters described in the paper are: *L=c<sub>0</sub> log k, M=c<sub>1</sub> log k, N=c<sub>2</sub> log k*.
As in the paper, the default values are *L=1.6 log k, M=3.5 log k, N=1.6 log k*.

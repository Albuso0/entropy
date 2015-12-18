#Tutorial

##Compile
Check out all source code, including the Makefile.

Type *$make*, we are done!


## Usage
Follow the code in *mainentropy.cpp*.


1. Setup entropy estimator *Entropy* with given alphabet size *k*: 
  * *setDegree(L)*: the degree of polynomial is L.
  * *setInterval(M)*: the approximation interval is [0,M/n], where n is the sample size.
  * *setThreshold(N)*: the threshold to use polynomial estimator is when the histogram is at most N.
2. Create a distribution vector *p* with alphabet size *k*.
Several distributions is wrapped up in *distvec.h*.
You can create other vectors as input distribution.
3. Create sample generator *SampleGen* to generate samples by *gen.discrete( n, &p )*.
4. Put the fingerprint of those samples to the entropy estimator by *entropy.setFin( gen.getFin() )*.
5. Output your estimate!

### SampleGen
gen.setSeed( seed ): set seed for random number generator.

gen.reset(): clear previous samples.

gen.discrete( n, &p ): create n more samples with distribution p, old samples are all kept.


### Entropy
entropy.estimate_plug(): plug-in estimator

entropy.estimate\_Miller\_Madow(): Miller-Madow estimator

entropy.estimate(): our polynomial estimator



## Reference
For detailed explanation of parameters, please refer to the paper *"Minimax rates of entropy estimation on large alphabets via best polynomial approximation, arXiv:1407.0381"*.
The paramters described in the paper are: *L=c<sub>0</sub> log k, M=c<sub>1</sub> log k, N=c<sub>2</sub> log k*
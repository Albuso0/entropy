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
2. Input fingerprint with *entropy.setFin( std::shared_ptr\< const std::map\<int, int\> \> fin )*. Here *fin* is a [shared pointer](http://www.cplusplus.com/reference/memory/shared_ptr/) of [map container](http://www.cplusplus.com/reference/map/map/), (*fin)[j] counts the number of symbols that appear j times; 
3. Output various estimates: 
  * entropy.estimate(): our polynomial estimator
  * entropy.estimate_plug(): plug-in estimator
  * entropy.estimate\_Miller\_Madow(): Miller-Madow estimator


## Sample code *mainentropy.cpp*
Here we create synthetic data with *SampleGen* class. 

1. Create entropy estimator *Entropy* with alphabet size *k*. Set degree, interval, threshold.
2. Create uniform distribution vector *p* with alphabet size *k*. Several distributions is wrapped up in *distvec.h*.
3. Create sample generator *SampleGen* to generate samples by *gen.discrete( n, &p )*.
4. Put the fingerprint of those samples to the entropy estimator by *entropy.setFin( gen.getFin() )*.
5. Output your estimate!

### SampleGen
gen.setSeed( seed ): set seed for random number generator.

gen.reset(): clear previous samples.

gen.discrete( n, &p ): create n more samples with distribution p, old samples are all kept.



## Reference
For detailed explanation of parameters, please refer to the paper *"Minimax rates of entropy estimation on large alphabets via best polynomial approximation, arXiv:1407.0381"*.
The paramters described in the paper are: *L=c<sub>0</sub> log k, M=c<sub>1</sub> log k, N=c<sub>2</sub> log k*.
As in the paper, the default values are *L=1.6 log k, M=3.5 log k, N=1.6 log k*.

#include "entropy.h"
#include <iostream>
#include <algorithm>
#include "samplegen.h"
#include <vector>
#include "distvec.h"

typedef std::map<int, int> Fingerprint;

double true_entropy(std::vector<double> &p);

int main(int argc, char *argv[])
{
    int k = 100000;
    // double c0 = 2, c1 = 3, c2 = 1;
    // double c0 = 1.3, c1 = 8, c2 = 1.5;

    // Set estimator
    Entropy entropy( k );
    entropy.setDegree( 18 );
    entropy.setInterval( 40 );
    entropy.setThreshold( 18 ); 
    printf("Alphabet size=%d.\n", entropy.getAlphabetSize());
    printf("Polynoimal degree=%d.\n", entropy.getDegree());
    printf("Approximation interval=[0,%.2f/n].\n", entropy.getInterval());
    printf("Plug-in threshold=%d.\n",(int)floor(entropy.getThreshold())+1);
    printf("Unit: bits\n");

    
    // Set distribution for test
    std::vector<double> p;
    p = uniform(k);    

    SampleGen gen;
    gen.reset();
    gen.setSeed( 0 );
    gen.discrete( 3000, &p );
    entropy.setFin( gen.getFin() );
    printf("true entropy=%.6f\n",true_entropy(p));
    printf("Plug in=%.6f\n",entropy.estimate_plug());
    printf("Miller Madow=%.6f\n",entropy.estimate_Miller_Madow());
    printf("Polynomial=%.6f\n",entropy.estimate());
    
    return 0;
}


double true_entropy(std::vector<double> &p)
{
    double truth = 0;
    double norm = 0;
    for (const auto &mass : p)
        norm += mass;
    for (const auto &mass : p)
        if (mass > 0)
            truth += ( -mass/norm*log(mass/norm) );
    truth /= log(2);
    return truth;
}





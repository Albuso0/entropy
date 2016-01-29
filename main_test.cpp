#include "entropy.h"
#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
    int k = 100000;

    // Set estimator
    Entropy entropy( k );
    entropy.setDegree( 18 ); // L = 1.6 log k
    entropy.setInterval( 40 ); // M = 3.5 log k
    entropy.setThreshold( 18 ); // N = 1.6 log k
    printf("Parameters:\n");
    printf("Alphabet size\t\t=%d\n", entropy.getAlphabetSize());
    printf("Polynoimal degree\t=%d\n", entropy.getDegree());
    printf("Approximation interval\t=[0,%.2f/n]\n", entropy.getInterval());
    printf("Plug-in threshold\t=%d\n",(int)floor(entropy.getThreshold())+1);

    // Input fingerprint from file
    entropy.setFin("fin_sample.txt"); // fingerprint of 3000 samples generated from uniform[100000]

    printf("\nResults:\n");
    printf("sample size\t=%d\n",entropy.getSampleSize());
    printf("true entropy\t=%.6f bits\n",log(k)/log(2));
    printf("Plug in\t\t=%.6f bits\n",entropy.estimate_plug());
    printf("Miller Madow\t=%.6f bits\n",entropy.estimate_Miller_Madow());
    printf("Polynomial\t=%.6f bits\n",entropy.estimate());
    printf("\n");
    
    return 0;
}





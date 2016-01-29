#include "entropy.h"
#include <iostream>
#include <algorithm>
#include "samplegen.h"
#include <vector>
#include "distvec.h"
#include <fstream>

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
    printf("Parameters:\n");
    printf("Alphabet size\t\t=%d.\n", entropy.getAlphabetSize());
    printf("Polynoimal degree\t=%d.\n", entropy.getDegree());
    printf("Approximation interval\t=[0,%.2f/n].\n", entropy.getInterval());
    printf("Plug-in threshold\t=%d.\n",(int)floor(entropy.getThreshold())+1);
    printf("Unit: bits\n");

    // Input fingerprint from file
    entropy.setFin("fin_sample.txt"); // fingerprint of 3000 samples generated from uniform[100000]

    printf("\nResults:\n");
    printf("sample size\t=%d\n",entropy.getSampleSize());
    printf("true entropy\t=%.6f\n",log(k)/log(2));
    printf("Plug in\t\t=%.6f\n",entropy.estimate_plug());
    printf("Miller Madow\t=%.6f\n",entropy.estimate_Miller_Madow());
    printf("Polynomial\t=%.6f\n",entropy.estimate());
    
    return 0;
}





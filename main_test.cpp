#include "entropy.h"
#include <iostream>
#include <cmath>

void print_param(const Entropy &entropy);
void print_results(const Entropy &entropy);

int main(int argc, char *argv[])
{
    int k = 100000;

    // Set estimator
    Entropy entropy( k );
    entropy.setDegree( 18 ); // L = 1.6 log k
    entropy.setInterval( 40 ); // M = 3.5 log k
    entropy.setThreshold( 18 ); // N = 1.6 log k
    print_param(entropy); // print parameters

    // Input fingerprint from file
    entropy.setFin("fin_sample.txt"); // fingerprint of 3000 samples generated from uniform[100000]
    print_results(entropy); // print estimation results

    // Input fingerprint inline
    std::vector<int> freq, cnt;
    freq.push_back(1); cnt.push_back(2910); 
    freq.push_back(2); cnt.push_back(45);
    entropy.setFin(freq, cnt);
    print_results(entropy);

    // Input histogram from file
    entropy.setHist("hist_sample.txt"); // histogram of 3000 samples generated from uniform[100000]
    print_results(entropy);
    
    // Input histogram inline
    std::vector<int> hist;
    for (int i = 0; i < 2910; i++) hist.push_back(1);
    for (int i = 0; i < 45; i++) hist.push_back(2);
    entropy.setHist(hist);
    print_results(entropy);

    return 0;
}

void print_param(const Entropy &entropy)
{
    printf("Parameters:\n");
    printf("Alphabet size\t\t=%d\n", entropy.getAlphabetSize());
    printf("Polynoimal degree\t=%d\n", entropy.getDegree());
    printf("Approximation interval\t=[0,%.2f/n]\n", entropy.getInterval());
    printf("Plug-in threshold\t=%d\n",(int)floor(entropy.getThreshold())+1);
    printf("\n");
}


void print_results(const Entropy &entropy)
{
    printf("Results:\n");
    printf("Sample size\t=%d\n",entropy.getSampleSize());
    printf("Plug in\t\t=%.6f bits\n",entropy.estimate_plug());
    printf("Miller Madow\t=%.6f bits\n",entropy.estimate_Miller_Madow());
    printf("Polynomial\t=%.6f bits\n",entropy.estimate());
    printf("\n");
}


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <string>
#include "entropy.h"
#include "commandline.h"

void print_param(const Entropy &entropy);
void print_results(const Entropy &entropy);

int main(int argc, char *argv[])
{
    int k =0 , L = 0, N = 0;
    double M = 0;
    std::string fin = "", hist = "";
    
    std::CommandLine cmd;
    cmd.AddValue ("k",  "Alphabet size", k);
    cmd.AddValue ("L",  "Polynoimal degree. Default c0*log(k)", L);
    cmd.AddValue ("M",  "M/n is the right-end of approximation interval. Default c1*log(k)", M);
    cmd.AddValue ("N",  "Threshold to apply polynomial estimator. Default c2*log(k)", N);
    cmd.AddValue ("fin",  "fingerprint data file", fin);
    cmd.AddValue ("hist",  "histogram data file", hist);
    cmd.Parse (argc, argv);
    if( k == 0 ) { std::cerr<<"Please input k!\n"; std::exit(1); }
    if( L == 0 ) L = 1.6*log(k); // Default value
    if( M == 0 ) M = 3.5*log(k); // Default value
    if( N == 0 ) N = 1.6*log(k); // Default value
    if( (hist=="") && (fin=="") ) { std::cerr<<"Please input fingerprint or histogram!\n"; std::exit(1); }

    printf("\n");
    // Set estimator
    Entropy entropy( k );
    entropy.setDegree( L ); 
    entropy.setInterval( M ); 
    entropy.setThreshold( N ); 
    print_param(entropy);

    // Input fingerprint from file
    if ( fin!="")
        entropy.setFin(fin);
    else
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


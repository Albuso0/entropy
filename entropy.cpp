#include "entropy.h"
#include <fstream>
#include <iostream>


double Entropy::estimate()
{
    double HEsti = 0;
    int symbolnumber = 0;
    for ( const auto & pair : *mpFin )
    {
        int N = pair.first;
        symbolnumber += pair.second;
        if ( N > N_thr) // plug-in
        {
            double x = (double)N / (double)n;
            HEsti += (-x*log(x)+0.5/n) * (pair.second);
        }
        else // polynomial
        {
            HEsti += getCoeff(N) * (pair.second);
        }
    }
    HEsti += 1.0*getCoeff(0) * (k-symbolnumber);
    
    HEsti = (HEsti > 0)? HEsti:0;
    // HEsti = (HEsti < log(k))?HEsti:log(k);

    return HEsti/log(2); // return the estimated entropy (bits)
}

double Entropy::estimate_non_zero() // Only use fingerprint f_j for j>=1. In other words, g(0)=0.
{
    double HEsti = 0;
    for ( const auto & pair : *mpFin )
    {
        int N = pair.first;
        if ( N > N_thr) // plug-in
        {
            double x = (double)N / (double)n;
            HEsti += (-x*log(x)+0.5/n) * (pair.second);
        }
        else // polynomial
        {
            HEsti += getCoeff(N) * (pair.second);
        }
    }
    
    HEsti = (HEsti > 0)? HEsti:0;
    // HEsti = (HEsti < log(k))?HEsti:log(k);

    return HEsti/log(2); // return the estimated entropy (bits)
}

double Entropy::estimate_Miller_Madow()
{
    double HEsti = 0;
    int symbolnumber = 0;
    for ( const auto & pair : *mpFin )
    {
        int N = pair.first;
        symbolnumber += pair.second;
        if ( N>0 )
        {
            double x = (double)N / (double)n;
            HEsti += (-x*log(x)) * (pair.second);
        }
    }
    return (HEsti+1.0*(symbolnumber-1)/n/2)/log(2); // return the bias-corrected empirical entropy (bits)
}


double Entropy::estimate_plug()
{
    double HEsti = 0;
    for ( const auto & pair : *mpFin )
    {
        int N = pair.first;
        if ( N>0 )
        {
            double x = (double)N / (double)n;
            HEsti += (-x*log(x)) * (pair.second);
        }
    }
    return HEsti/log(2); // return the empirical entropy (bits)
}


double Entropy::getCoeff( int N )
{
    if ( N < 0 )
    {
        std::cerr<<"Compute g(N) for negative N!!"<<std::endl;
        exit(1);
    }
    int L0 = ( N > L )? L:N;
    double gL = a[L0];
    for (int i = L0; i>0; i--) 
        gL = a[i-1] + gL * (N-i+1) / Ratio;
    gL = (gL * Ratio + log(n/Ratio) * N)/n;
    return gL;
}


void Entropy::setFin(std::shared_ptr< const std::map<int, int> > fin) 
{
    mpFin = fin;
    n = 0;
    for ( std::map<int,int>::const_iterator it = mpFin->begin(); it != mpFin->end(); ++it )
        n += it->first * it->second;
}


void Entropy::setDegree( int deg )
{
    L = deg;
    a = boost::shared_array<double>(new double[L+1]);
    std::fstream fd_coeffs("coeffs.txt");
    // ignore the first L-1 lines
    fd_coeffs.seekg(std::ios::beg);
    for( int i = 0; i < L-1; ++i )
        fd_coeffs.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    // Read line L
    int test_L;
    fd_coeffs >> test_L;
    if ( L != test_L )
    {
        std::cerr<<"Read the wrong line!!"<<std::endl;
        exit(1);
    }
    for (int i = 0; i <= L; i++)
        fd_coeffs >> a[i];
    fd_coeffs.close();
}



Entropy::Entropy()
{
}

Entropy::Entropy(int alphabet_size)
    :Entropy()
{
    k = alphabet_size;
}

#include "entropy.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>

double Entropy::estimate() const 
{
    double HEsti = 0;
    int symbolnumber = 0;
    for ( const auto & pair : fin )
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

double Entropy::estimate_non_zero() const // Only use fingerprint f_j for j>=1. In other words, g(0)=0.
{
    double HEsti = 0;
    for ( const auto & pair : fin )
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

double Entropy::estimate_Miller_Madow() const
{
    double HEsti = 0;
    int symbolnumber = 0;
    for ( const auto & pair : fin )
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


double Entropy::estimate_plug() const
{
    double HEsti = 0;
    for ( const auto & pair : fin )
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


double Entropy::getCoeff( int N ) const
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


void Entropy::setFin(std::shared_ptr< const std::map<int, int> > ptr_fin_map) 
{
    fin.clear();
    n = 0;
    for ( auto it = ptr_fin_map->begin(); it != ptr_fin_map->end(); ++it )
    {
        int freq = it->first, cnt = it->second;
        fin.push_back( std::make_pair( freq, cnt ) );
        n += (freq * cnt);
    }
}

void Entropy::setFin(const std::string filename) 
{
    fin.clear();
    n = 0;
    std::ifstream infile;
    infile.open( filename.c_str() );
    int freq, cnt;
    while ( (infile>>freq).good() )
    {
        infile >> cnt;
        fin.push_back( std::make_pair( freq, cnt ) );
        n += (freq * cnt);
    }
    infile.close();
}

void Entropy::setFin(const std::vector<int> &freq_in, const std::vector<int> &cnt_in)
{
    fin.clear();
    n = 0;
    for ( int i = 0; i < freq_in.size(); i++)
    {
        int freq = freq_in[i], cnt = cnt_in[i];
        fin.push_back( std::make_pair( freq, cnt ) );
        n += (freq * cnt);
    }
}

void Entropy::setHist( const std::vector<int> &hist )
{
    fin.clear();
    n = 0;
    
    std::map<int, int> fin_map;
    for ( const auto & freq : hist )
    {
        auto iter = fin_map.find( freq );
        if ( iter == fin_map.end() )
            fin_map.insert( std::make_pair( freq,1 ) );
        else
            ++(iter->second);
    }
    
    for ( auto it = fin_map.begin(); it != fin_map.end(); ++it )
    {
        int freq = it->first, cnt = it->second;
        fin.push_back( std::make_pair( freq, cnt ) );
        n += (freq * cnt);
    }
}

void Entropy::setHist(const std::string filename) 
{
    fin.clear();
    n = 0;
    std::map<int, int> fin_map;
    
    std::ifstream infile;
    infile.open( filename.c_str() );
    int freq;
    while ( (infile>>freq).good() )
    {
        if ( freq == 0)
            continue;

        auto iter = fin_map.find( freq );
        if ( iter == fin_map.end() )
            fin_map.insert( std::make_pair( freq,1 ) );
        else
            ++(iter->second);
    }
    infile.close();

    for ( auto it = fin_map.begin(); it != fin_map.end(); ++it )
    {
        int freq = it->first, cnt = it->second;
        fin.push_back( std::make_pair( freq, cnt ) );
        n += (freq * cnt);
    }
}

void Entropy::setDegree( int deg )
{
    L = deg;
    a.clear();
    
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
    double coeff;
    for (int i = 0; i <= L; i++)
    {
        fd_coeffs >> coeff;
        a.push_back(coeff);
    }
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

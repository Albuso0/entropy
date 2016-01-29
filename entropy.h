#ifndef ENTROPY_H
#define ENTROPY_H

#include <map>
#include <memory>
#include <vector>
#include <string>

class Entropy
{
public:
    Entropy();
    Entropy( int alphabet_size );
    virtual ~Entropy(){}

    double getCoeff( int N ); // compute g(N). 
    // Without the sample splitting required by theory
    double estimate(); // Hist must be given
    double estimate_non_zero(); // Only use fingerprint f_j for j>=1. In other words, g(0)=0.
    double estimate_plug();
    double estimate_Miller_Madow();

    void setAlphabetSize( int alphabet_size ) { k = alphabet_size; }
    void setThreshold( double N_threshold ){ N_thr = N_threshold; }
    void setInterval( double rEnd ){ Ratio = rEnd; }
    void setDegree( int deg ); // also update the coefficients array
    // set fingerprint, also update sample size
    void setFin(std::shared_ptr< const std::map<int, int> > fin); 
    void setFin(std::string filename);
    void setFin(const std::vector<int> &freq, const std::vector<int> &cnt);
    
    int getAlphabetSize() const{ return k; }
    int getSampleSize() const{ return n; }
    int getDegree() const{ return L; }
    double getThreshold() const{ return N_thr; }
    double getInterval() const{ return Ratio; }
private:
    double N_thr; // =c2*log(k). Plug-in threshold
    double Ratio; // =c1*log(k). Approximation over [0,c1*log(k)/n]
    int L; // =c0*log(k). Degree of polynomial
    int n; // Sample size
    int k; // Alphabet size
    std::vector< std::pair<int, int> > fin; // Fingerprint(profile)
    std::vector<double> a; // polynomial coefficients
	
	
};


#endif



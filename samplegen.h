#ifndef SAMPLEGEN_H
#define SAMPLEGEN_H
#include <random>
#include <map>
#include <memory>
#include <vector>


class SampleGen // Random sample generator and counter for DISCRETE distributions
{
public:
    typedef std::shared_ptr<std::map<int, int> >  HistPtr;
    typedef std::shared_ptr<const std::map<int, int> >  const_HistPtr;
    SampleGen();
    virtual ~SampleGen(){}
	
    void reset(){ mpHist->clear(); }
    void setSeed(int _seed){ generator.seed( _seed ); }
	
    void uniform(int n, int k);  // generate n samples from Uniform[0:k-1] and update histogram
    void Poisson_truncated(int n, double lamdba, int min, int max);  // generate n samples from truncated Poi(lambda) and update histogram
    void discrete(int n, std::vector<double>* p);
    void negative_binomial(int n, int k, double p);
    
    const_HistPtr getHist() const{ return mpHist; }
    const_HistPtr getFin() const;

private:
    std::default_random_engine generator;
    HistPtr mpHist;
	
    void addSample(int sample); // add the sample to histogram
    template <typename T>
    void sampling( T distribution, int n );
    template <typename T>
    void sampling_truncate( T distribution, int n , int min, int max);
};

template <typename T>
void SampleGen::sampling( T distribution, int n )
{
    for (int i=0; i<n; ++i)
        addSample( distribution(generator) );
}
template <typename T>
void SampleGen::sampling_truncate( T distribution, int n , int min, int max)
{
    for (int i=0; i<n; ++i)
    {
        int sample = distribution(generator);
        while ( ( sample > max ) || ( sample < min ) )
            sample = distribution(generator);
        addSample( sample );
    }
}


#endif 

#ifndef DISTVEC_H
#define DISTVEC_H

#include <vector>

std::vector<double> uniform(int k)
{
    std::vector<double> p( k );
    for (int i = 0; i < k; ++i)
        p[i] = 1.0;
    printf("Uniform distribution.\n");
    return p;
}


std::vector<double> uniformhalf(int k)
{
    int supp = k/2;
    std::vector<double> p( k );
    for (int i = 0; i < supp; ++i)
        p[i] = 1.0;
    printf("Uniform distributed on half of alphabet.\n");
    return p;
}


std::vector<double> mix(int k)
{
    std::vector<double> p( k );
    for (int i = 0; i < k; i++)
        p[i] = 1;
    p[0] += k;
    printf("Mixture by half uniform and half point mass.\n");
    return p;
}


std::vector<double> zipf(int k)
{
    std::vector<double> p( k );
    for (int i = 0; i < k; ++i)
        p[i] = 1.0/(i+1);
    printf("Zipf(1) distribution.\n");
    return p;
}

std::vector<double> zipfd5(int k)
{
    std::vector<double> p( k );
    for (int i = 0; i < k; ++i)
        p[i] = 1.0/sqrt(i+1);
    printf("Zipf(0.5) distribution.\n");
    return p;
}


std::vector<double> mixgeozipf(int k)
{
    std::vector<double> p( k );
    double norm1 = 0.0;
    int mid = floor(k/2);
    for (int i = 0; i < mid; ++i)
    {
        p[i] = 1.0/(i+1);
        norm1 += p[i];
    }
    for (int i = 0; i < mid; ++i)
        p[i] /= (2*norm1);
    double norm2 = 0;
    p[mid] = 2.0/k;
    norm2 += p[mid];
    for (int i = mid+1; i < k; ++i)
    {
        p[i] = p[i-1] * (1-2.0/k);
        norm2 += p[i];
    }
    for (int i = mid; i < k; ++i)
        p[i] /= (2*norm2);
    printf("Half Zipf(1) distribution and Half Geo(2/k).\n");
    return p;
}


#endif




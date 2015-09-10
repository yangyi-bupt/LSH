// Implement Locality-Sensitive Binary Codesfrom Shift-Invariant Kernels NIPS(2009)
// http://www.robots.ox.ac.uk/~vgg/rg/papers/binarycodes.pdf
// cos(w*x + b) + t
// Author: Yi Yang (yangyi_bupt@126.com)
// 

#ifndef KERNEL_LSH_H
#define KERNEL_LSH_H
#pragma once

#include <stdint.h>
#include <random>
#include "base/scoped_ptr.h"

struct feature_node {
    int32_t index;
    double value;
};

class KLSH {
public:
    KLSH(const uint32_t& max_feat_num, const int& hash_bit_num, const float& sigma);
    uint64_t GetHashValue(const feature_node* pfeat);

private:
    std::default_random_engine eng;
    scoped_ptr<std::normal_distribution<double> > m_normal;
    scoped_ptr<std::uniform_real_distribution<double> > m_uniform_1;
    scoped_ptr<std::uniform_real_distribution<double> > m_uniform_pi;

    // std::vector is not used because operator "=" is not allowed in scoped_array
    scoped_array<scoped_array<feature_node> > m_project_w;
    scoped_array<double> m_project_t;
    scoped_array<double> m_project_b;

    uint32_t m_max_feat_num;
    uint32_t m_hash_bit_num;
};

#endif // KERNEL_LSH_H

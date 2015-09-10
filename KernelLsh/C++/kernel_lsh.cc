// Implement Locality-Sensitive Binary Codesfrom Shift-Invariant Kernels NIPS(2009)
// http://www.robots.ox.ac.uk/~vgg/rg/papers/binarycodes.pdf
// cos(w*x + b) + t
// Author: Yi Yang (yangyi_bupt@126.com)
//

#include "kernel_lsh.h"

#include <cmath>

namespace {
template<class T>
inline int32_t sign(T val) {
    return val >= 0 ? 1:0;
}

double Dot(const feature_node *px, const feature_node *py) {
    double sum = 0;
    while (px->index != -1 && py->index != -1) {
        if (px->index == py->index) {
            sum += px->value * py->value;
            ++px;
            ++py;
        } else {
            px->index > py->index ? ++py:++px;
        }
    }
    return sum;
}

} // namespace

KLSH::KLSH(const uint32_t& max_feat_num, const int& hash_bit_num, const float& sigma)
        : m_max_feat_num(max_feat_num), m_hash_bit_num(hash_bit_num) {

    m_normal.reset(new std::normal_distribution<double>(0.0, sigma * sigma));
    m_uniform_1.reset(new std::uniform_real_distribution<double>(-1.0, 1.0));
    m_uniform_pi.reset(new std::uniform_real_distribution<double>(0.0, 2.0 * M_PI));

    m_project_w.reset(new scoped_array<feature_node>[m_hash_bit_num]);
    m_project_t.reset(new double[m_hash_bit_num]);
    m_project_b.reset(new double[m_hash_bit_num]);

    for (uint32_t i = 0; i < m_hash_bit_num; ++i) {
        // init project_t, project_b
        m_project_t[i] = (*m_uniform_1)(eng);
        m_project_b[i] = (*m_uniform_pi)(eng);
        // init project_w (m_max_feat_num + 1, 1 more space for index -1)
        m_project_w[i].reset(new feature_node[m_max_feat_num + 1]);
        for (uint32_t j = 0; j < m_max_feat_num; ++j) {
            // svm index begin from 1
            m_project_w[i][j].index = j + 1;
            m_project_w[i][j].value = (*m_normal)(eng);
        }
        m_project_w[i][m_max_feat_num].index = -1;
    }
}

uint64_t KLSH::GetHashValue(const feature_node* pfeat) {
    float sum = 0;
    uint64_t hash_value = 0;
    for (uint32_t i = 0; i < m_hash_bit_num; ++i) {
        sum = static_cast<float>(Dot(pfeat, m_project_w[i].get()) + m_project_b[i]);
        hash_value |= static_cast<uint64_t>(sign(std::cos(sum) + m_project_t[i])) << i;
    }
    return hash_value;
}

#include "kernel_lsh.h"

int32_t main() {
    int32_t feature_size = 10;
    int32_t bit_num = 64;
    float sigma = 0.2f;
    // need 1 feature_node->index=-1 to mark end
    scoped_array<feature_node> p1(new feature_node[feature_size + 1]);
    scoped_array<feature_node> p2(new feature_node[feature_size + 1]);
    for (int32_t i = 1; i < feature_size; ++i) {
        p1[i].index = i;
        p2[i].index = i;
        p1[i].value = 1.0;
        p2[i].value = 1.0;
    }
    p1[feature_size - 1].index = feature_size;
    p1[feature_size - 1].value = 3.0;
    p2[feature_size - 1].index = feature_size;
    p2[feature_size - 1].value = 0.2;
    p1[feature_size].index = -1;
    p2[feature_size].index = -1;

    KLSH klsh_low(feature_size, bit_num, sigma);
    KLSH klsh_high(feature_size, bit_num, sigma * 1.5);
    printf("klsh_low: p1=%lx\n", klsh_low.GetHashValue(p1.get()));
    printf("klsh_low: p2=%lx\n", klsh_low.GetHashValue(p2.get()));
    printf("---------------------------------\n");
    printf("klsh_high: p1=%lx\n", klsh_high.GetHashValue(p1.get()));
    printf("klsh_high: p2=%lx\n", klsh_high.GetHashValue(p2.get()));
}
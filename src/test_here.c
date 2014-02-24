#include "include/seatest.h"
#define LEN 1024
#define LEN2 268435456

void psumLEN_1(){
    int a[LEN];
    int i;
    for(i = 0; i<LEN2; a[i++] = 1);
    assert_int_equal(LEN, parallel_sum(a, LEN));
}

void psumLEN2_1(){
    int a[LEN2];
    int i;
    for(i = 0; i<LEN2; a[i++] = 1);
    assert_int_equal(LEN2, parallel_sum2(a));
}

void test_fixture_sum(){
    test_fixture_start();
    run_test(psumLEN_1);
    run_test(psumLEN2_1);
    test_fixture_end();
}

void all_tests(){
    test_fixture_sum();
}

int main(void){
    run_tests(all_tests);
    return 0;
}

/*
assert_true
assert_false
assert_int_equal
assert_ulong_equal
assert_string_equal
assert_n_array_equal
assert_bit_set
assert_bit_not_set
assert_bit_mask_matches
assert_fail
assert_float_equal
assert_double_equal
assert_string_contains
assert_string_doesnt_contain
assert_string_starts_with
assert_string_ends_with
*/

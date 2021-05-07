//
// Created by henri on 07/05/21.
//

#ifndef STATE_MACHINE_CPP_TEST_TRANSITION_OVERRIDE_H
#define STATE_MACHINE_CPP_TEST_TRANSITION_OVERRIDE_H

TEST(transition_override, should_throw_if_override_non_existing) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);

        transitions.override(A, B);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

TEST(transition_override, should_override) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);

        transitions.create(A, B);
        transitions.override(A, B);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);
    TEST_UTIL_ASSERT_DIRECT_TRANSITION(algorithm.transitions()[A], A, B);
}

TEST(transition_override, should_override_if) {

    TEST_UTIL_CREATE_HANDLER_IF(test, f, { return true; });

    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        states.create(C);

        transitions.create_if(A, B, C, test::f);
        transitions.override_if(A, B, C, test::f);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);
    TEST_UTIL_ASSERT_CONDITIONAL_TRANSITION(algorithm.transitions()[A], A, B, C);
}

TEST(transition_override, should_override_parallelized) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        states.create(C);
        states.create(D);

        transitions.create(B, D);
        transitions.create(C, D);
        transitions.create_parallelized(A, { B, C }, D);
        transitions.override_parallelized(A, { B, C }, D);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);
    TEST_UTIL_ASSERT_PARALLELIZED_TRANSITION_2(algorithm.transitions()[A], A, B, C, D);
}

TEST(transition_override, should_override_change) {
    TEST_UTIL_CREATE_HANDLER_IF(test, f, { return true; });

    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        states.create(C);

        transitions.create(A, B);
        transitions.override_if(A, B, C, test::f);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);
    TEST_UTIL_ASSERT_CONDITIONAL_TRANSITION(algorithm.transitions()[A], A, B, C);
}

TEST(transition_override, should_throw_if_override_final) {
    TEST_UTIL_CREATE_HANDLER_IF(test, f, { return true; });

    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        states.create(C);

        transitions.create_if(A, B, C, test::f);
        transitions.declare_as_final(A);
        transitions.override_if(A, B, C, test::f);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

// Same functions with virtual

TEST(transition_override, should_override_virtual) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);

        transitions.create_virtual(A, B);
        transitions.override(A, B);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);
    TEST_UTIL_ASSERT_DIRECT_TRANSITION(algorithm.transitions()[A], A, B);
}

TEST(transition_override, should_override_virtual_if) {

    TEST_UTIL_CREATE_HANDLER_IF(test, f, { return true; });

    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        states.create(C);

        transitions.create_if_virtual(A, B, C);
        transitions.override_if(A, B, C, test::f);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);
    TEST_UTIL_ASSERT_CONDITIONAL_TRANSITION(algorithm.transitions()[A], A, B, C);
}

TEST(transition_override, should_override_virtual_change) {
    TEST_UTIL_CREATE_HANDLER_IF(test, f, { return true; });

    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        states.create(C);

        transitions.create_virtual(A, B);
        transitions.override_if(A, B, C, test::f);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);
    TEST_UTIL_ASSERT_CONDITIONAL_TRANSITION(algorithm.transitions()[A], A, B, C);
}

#endif //STATE_MACHINE_CPP_TEST_TRANSITION_OVERRIDE_H

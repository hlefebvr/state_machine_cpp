//
// Created by henri on 07/05/21.
//

#ifndef STATE_MACHINE_CPP_TEST_TRANSITION_CREATE_TWICE_H
#define STATE_MACHINE_CPP_TEST_TRANSITION_CREATE_TWICE_H


TEST(transition_create_twice, should_throw_if_create_twice) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);

        transitions.create(A, B);
        transitions.create(A, B);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

TEST(transition_create_twice, should_throw_if_create_twice_if) {
    TEST_UTIL_CREATE_HANDLER_IF(test, f, { return true; })

    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        states.create(C);

        transitions.create_if(A, B, C, test::f);
        transitions.create_if(A, B, C, test::f);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

TEST(transition_create_twice, should_throw_if_create_twice_parallelized) {

    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        states.create(C);
        states.create(D);

        transitions.create_parallelized(A, { B, C }, D);
        transitions.create(B, D);
        transitions.create(C, D);
        transitions.create_parallelized(A, { B, C }, D);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

TEST(transition_create_twice, should_throw_if_create_twice_change) {

    TEST_UTIL_CREATE_HANDLER_IF(test, f, { return true; })

    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        states.create(C);

        transitions.create(A, B);
        transitions.create_if(A, B, C, test::f);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));

}

TEST(transition_create, should_throw_if_create_existing_virtual) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        transitions.create_virtual(A, B);
        transitions.create(A, B);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

TEST(transition_create, should_throw_if_create_existing_final) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        transitions.create(A, B);
        transitions.declare_as_final(A);
        transitions.create(A, B);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

#endif //STATE_MACHINE_CPP_TEST_TRANSITION_CREATE_TWICE_H

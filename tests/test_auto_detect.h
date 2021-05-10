//
// Created by henri on 07/05/21.
//

#ifndef STATE_MACHINE_CPP_TEST_AUTO_DETECT_H
#define STATE_MACHINE_CPP_TEST_AUTO_DETECT_H

namespace test::auto_detect {

    class AlgorithmWithINITIAL_STATE final : public Algorithm::Builder {
    public:
        static const State::Id& INITIAL_STATE;
        void build(Algorithm::Builder::States &states, Algorithm::Builder::Transitions &transitions,
                   Algorithm::Builder::Layers &layers) override {
            states.create(INITIAL_STATE);
        }
    };
    const State::Id& AlgorithmWithINITIAL_STATE::INITIAL_STATE = A;

    class AlgorithmWithFINAL_STATE final : public Algorithm::Builder {
    public:
        static const State::Id& FINAL_STATE;
        void build(Algorithm::Builder::States &states, Algorithm::Builder::Transitions &transitions,
                   Algorithm::Builder::Layers &layers) override {
            states.create(FINAL_STATE);
        }
    };
    const State::Id& AlgorithmWithFINAL_STATE::FINAL_STATE = A;

    class AlgorithmWithNonExistingINITIAL_STATE final : public Algorithm::Builder {
    public:
        static const State::Id& INITIAL_STATE;
        void build(Algorithm::Builder::States &states, Algorithm::Builder::Transitions &transitions,
                   Algorithm::Builder::Layers &layers) override {}
    };
    const State::Id& AlgorithmWithNonExistingINITIAL_STATE::INITIAL_STATE = A;

    class AlgorithmWithNonExistingFINAL_STATE final : public Algorithm::Builder {
    public:
        static const State::Id& FINAL_STATE;
        void build(Algorithm::Builder::States &states, Algorithm::Builder::Transitions &transitions,
                   Algorithm::Builder::Layers &layers) override {}
    };
    const State::Id& AlgorithmWithNonExistingFINAL_STATE::FINAL_STATE = A;

    class AlgorithmWithTIME_LIMIT_REACHED final : public Algorithm::Builder {
    public:
        static const State::Id& TIME_LIMIT_REACHED;
        void build(Algorithm::Builder::States &states, Algorithm::Builder::Transitions &transitions,
                   Algorithm::Builder::Layers &layers) override {
            states.create(TIME_LIMIT_REACHED);
        }
    };
    const State::Id& AlgorithmWithTIME_LIMIT_REACHED::TIME_LIMIT_REACHED = B;

    class AlgorithmWithNonExistingTIME_LIMIT_REACHED final : public Algorithm::Builder {
    public:
        static const State::Id& TIME_LIMIT_REACHED;
        void build(Algorithm::Builder::States &states, Algorithm::Builder::Transitions &transitions,
                   Algorithm::Builder::Layers &layers) override {}
    };
    const State::Id& AlgorithmWithNonExistingTIME_LIMIT_REACHED::TIME_LIMIT_REACHED = A;
}

TEST(auto_detect, should_detect_INITIAL_STATE) {
    Algorithm::Instance algorithm;
    Algorithm::build<test::auto_detect::AlgorithmWithINITIAL_STATE>(algorithm);

    ASSERT_EQ(algorithm.initial_state(), A);
    ASSERT_FALSE(algorithm.is_final_state_set());
}

TEST(auto_detect, should_detect_FINAL_STATE) {
    Algorithm::Instance algorithm;
    Algorithm::build<test::auto_detect::AlgorithmWithFINAL_STATE>(algorithm);

    ASSERT_EQ(algorithm.final_state(), A);
    ASSERT_FALSE(algorithm.is_initial_state_set());
}

TEST(auto_detect, should_detect_TIME_LIMIT_REACHED) {
    Algorithm::Instance algorithm;
    Algorithm::build<test::auto_detect::AlgorithmWithTIME_LIMIT_REACHED>(algorithm);

    ASSERT_EQ(algorithm.time_limit_reached_state(), B);
}

TEST(auto_detect, should_throw_if_INITIAL_STATE_is_detected_but_non_existing) {
    Algorithm::Instance algorithm;

    ASSERT_ANY_THROW(Algorithm::build<test::auto_detect::AlgorithmWithNonExistingINITIAL_STATE>(algorithm));
}

TEST(auto_detect, should_throw_if_FINAL_STATE_is_detected_but_non_existing) {
    Algorithm::Instance algorithm;

    ASSERT_ANY_THROW(Algorithm::build<test::auto_detect::AlgorithmWithNonExistingFINAL_STATE>(algorithm));
}

TEST(auto_detect, should_throw_if_TIME_LIMIT_REACHED_is_detected_but_non_existing) {
    Algorithm::Instance algorithm;

    ASSERT_ANY_THROW(Algorithm::build<test::auto_detect::AlgorithmWithNonExistingTIME_LIMIT_REACHED>(algorithm));
}

TEST(auto_detect, should_detect_FINAL_STATE_and_use_it_as_TIME_LIMIT_REACHED) {
    Algorithm::Instance algorithm;
    Algorithm::build<test::auto_detect::AlgorithmWithFINAL_STATE>(algorithm);

    ASSERT_EQ(algorithm.final_state(), A);
    ASSERT_EQ(algorithm.time_limit_reached_state(), A);
}

#endif //STATE_MACHINE_CPP_TEST_AUTO_DETECT_H

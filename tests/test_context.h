//
// Created by henri on 10/11/21.
//

#ifndef STATE_MACHINE_CPP_TEST_CONTEXT_H
#define STATE_MACHINE_CPP_TEST_CONTEXT_H

// (1) + (1) = (2)
TEST(context, should_add__1__and__1__) {

    ContextTree<Layer<int>> tree_a(new Layer(new int(0)));
    ContextTree<Layer<double>> tree_b(new Layer(new double(.0)));

    auto tree = Context::join(std::move(tree_a), std::move(tree_b));
    Context ctx(tree);

    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_FLOAT_EQ(ctx.get<double>(), .0);

}


// (2,1) + (1) = (3, 1)
TEST(context, should_add__2_1__and__1__) {

    ContextTree<Layer<int, float>, Layer<int>> ctx_a(
            new Layer(new int(0), new float(.0)),
            new Layer(new int(1))
    );

    ContextTree<Layer<double>> ctx_b(new Layer(new double(.0)));

    auto tree = Context::join(std::move(ctx_a), std::move(ctx_b));

    Context ctx0(tree);
    const Context& ctx(ctx0);

    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_FLOAT_EQ(ctx.get<float>(), .0);
    ASSERT_FLOAT_EQ(ctx.get<double>(), .0);
    ASSERT_EQ(ctx.get<int>(1), 1);

}

// (1) + (2,1) = (3, 1)
TEST(context, should_add__1__and__2_1__) {

    ContextTree<Layer<double>> ctx_a(new Layer(new double(.0)));

    ContextTree<Layer<int, float>, Layer<int>> ctx_b(
            new Layer(new int(0), new float(.0)),
            new Layer(new int(1))
    );

    auto tree = Context::join(std::move(ctx_a), std::move(ctx_b));

    Context ctx0(tree);
    const Context& ctx(ctx0);

    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_FLOAT_EQ(ctx.get<float>(), .0);
    ASSERT_FLOAT_EQ(ctx.get<double>(), .0);
    ASSERT_EQ(ctx.get<int>(1), 1);

}

// (2, 2) + (2, 2) = (4, 4)
TEST(context, should_add__2_2__and__2_2__) {

    ContextTree<Layer<int, double>, Layer<int, double>> ctx_a(
            new Layer(new int(0), new double(.0)),
            new Layer(new int(1), new double(.1))
    );

    ContextTree<Layer<std::string, float>, Layer<std::string, float>> ctx_b(
            new Layer(new std::string("0"), new float(.0)),
            new Layer(new std::string("1"), new float(.1))
    );

    auto tree = Context::join(std::move(ctx_a), std::move(ctx_b));

    Context ctx0(tree);
    const Context& ctx(ctx0);

    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_FLOAT_EQ(ctx.get<float>(), .0);
    ASSERT_FLOAT_EQ(ctx.get<double>(), .0);
    ASSERT_EQ(ctx.get<std::string>(),"0");
    ASSERT_EQ(ctx.get<int>(1), 1);
    ASSERT_FLOAT_EQ(ctx.get<float>(1), .1);
    ASSERT_FLOAT_EQ(ctx.get<double>(1), .1);
    ASSERT_EQ(ctx.get<std::string>(1),"1");

}

// (3, 3) + (3, 3) = (6, 6)
TEST(context, should_add__3_3__and__3_3__) {

    ContextTree<Layer<bool, int, double>, Layer<bool, int, double>> ctx_a(
            new Layer(new bool(false), new int(0), new double(.0)),
            new Layer(new bool(true), new int(1), new double(.1))
    );

    ContextTree<Layer<unsigned int, std::string, float>, Layer<unsigned int, std::string, float>> ctx_b(
            new Layer(new unsigned int(0), new std::string("0"), new float(.0)),
            new Layer(new unsigned int (1), new std::string("1"), new float(.1))
    );

    auto tree = Context::join(std::move(ctx_a), std::move(ctx_b));

    Context ctx0(tree);
    const Context& ctx(ctx0);

    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_FLOAT_EQ(ctx.get<float>(), .0);
    ASSERT_FLOAT_EQ(ctx.get<double>(), .0);
    ASSERT_FLOAT_EQ(ctx.get<bool>(), false);
    ASSERT_EQ(ctx.get<int>(1), 1);
    ASSERT_FLOAT_EQ(ctx.get<float>(1), .1);
    ASSERT_FLOAT_EQ(ctx.get<double>(1), .1);
    ASSERT_FLOAT_EQ(ctx.get<bool>(1), true);

}

// (3) + (2, 3) = (5, 3)
TEST(context, should_add__3__and__2_3__) {

    ContextTree<Layer<bool, int, double>> tree_a(
            new Layer(new bool(false), new int(0), new double(.0))
    );
    ContextTree<Layer<unsigned int, float>, Layer<bool, int, double>> tree_b(
            new Layer(new unsigned int(0), new float(.0)),
            new Layer(new bool(true), new int(1), new double(.1))
    );

    auto tree = Context::join(std::move(tree_a), std::move(tree_b));
    Context ctx(tree);

    ASSERT_FLOAT_EQ(ctx.get<bool>(), false);
    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_FLOAT_EQ(ctx.get<double>(), .0);
    ASSERT_FLOAT_EQ(ctx.get<unsigned int>(), 0);
    ASSERT_FLOAT_EQ(ctx.get<float>(), .0);
    ASSERT_FLOAT_EQ(ctx.get<bool>(1), true);
    ASSERT_EQ(ctx.get<int>(1), 1);
    ASSERT_FLOAT_EQ(ctx.get<double>(1), .1);

}

// (1, 1, 1) + (1, 1, 1) = (2, 2, 2)
TEST(context, should_add__1_1_1__and__1_1_1__) {

    ContextTree<Layer<int>, Layer<int>, Layer<int>> tree_a(
            new Layer(new int(0)),
            new Layer(new int(1)),
            new Layer(new int(2))
    );
    ContextTree<Layer<double>, Layer<double>, Layer<double>> tree_b(
            new Layer(new double(.0)),
            new Layer(new double(.1)),
            new Layer(new double(.2))
    );

    auto tree = Context::join(std::move(tree_a), std::move(tree_b));
    Context ctx(tree);

    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_FLOAT_EQ(ctx.get<double>(), .0);
    ASSERT_EQ(ctx.get<int>(1), 1);
    ASSERT_FLOAT_EQ(ctx.get<double>(1), .1);
    ASSERT_EQ(ctx.get<int>(2), 2);
    ASSERT_FLOAT_EQ(ctx.get<double>(2), .2);
}

// (1, 2, 3) + (1) = (2, 2, 3)
TEST(context, should_add__1_2_3__and__1__) {

    ContextTree<Layer<int>, Layer<int, double>, Layer<int, double, float>> tree_a(
            new Layer(new int(0)),
            new Layer(new int(1), new double(.1)),
            new Layer(new int(2), new double(.2), new float(.2))
    );
    ContextTree<Layer<double>> tree_b(
            new Layer(new double(.0))
    );

    auto tree = Context::join(std::move(tree_a), std::move(tree_b));
    Context ctx(tree);

    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_FLOAT_EQ(ctx.get<double>(), .0);
    ASSERT_EQ(ctx.get<int>(1), 1);
    ASSERT_FLOAT_EQ(ctx.get<double>(1), .1);
    ASSERT_EQ(ctx.get<int>(2), 2);
    ASSERT_FLOAT_EQ(ctx.get<double>(2), .2);
    ASSERT_FLOAT_EQ(ctx.get<float>(2), .2);
}

// (1) + (1, 2, 3) = (2, 2, 3)
TEST(context, should_add__1__and__1_2_3__) {

    ContextTree<Layer<double>> tree_a(
            new Layer(new double(.0))
    );

    ContextTree<Layer<int>, Layer<int, double>, Layer<int, double, float>> tree_b(
            new Layer(new int(0)),
            new Layer(new int(1), new double(.1)),
            new Layer(new int(2), new double(.2), new float(.2))
    );

    auto tree = Context::join(std::move(tree_a), std::move(tree_b));
    Context ctx(tree);

    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_FLOAT_EQ(ctx.get<double>(), .0);
    ASSERT_EQ(ctx.get<int>(1), 1);
    ASSERT_FLOAT_EQ(ctx.get<double>(1), .1);
    ASSERT_EQ(ctx.get<int>(2), 2);
    ASSERT_FLOAT_EQ(ctx.get<double>(2), .2);
    ASSERT_FLOAT_EQ(ctx.get<float>(2), .2);
}

// (1) + (0, 1) = (1, 1)
TEST(context, should_add__1__and__0_1__) {

    ContextTree<Layer<int>> tree_a(
            new Layer(new int(0))
    );

    ContextTree<Layer<>, Layer<int>> tree_b(
            nullptr,
            new Layer(new int(1))
    );

    auto tree = Context::join(std::move(tree_a), std::move(tree_b));
    Context ctx(tree);

    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_EQ(ctx.get<int>(1), 1);
}

// (0, 1) + 1 = (1, 1)
TEST(context, should_add__0_1__and__1__) {

    ContextTree<Layer<>, Layer<int>> tree_a(
            nullptr,
            new Layer(new int(1))
    );

    ContextTree<Layer<int>> tree_b(
            new Layer(new int(0))
    );

    auto tree = Context::join(std::move(tree_a), std::move(tree_b));
    Context ctx(tree);

    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_EQ(ctx.get<int>(1), 1);
}

// (1, 0, 1) + (0, 1) = (1, 0)
TEST(context, should_add__1_0_1__and__0_1__) {

    ContextTree<Layer<int>, Layer<>, Layer<int>> tree_a(
            new Layer(new int(0)),
            nullptr,
            new Layer(new int(2))
    );

    ContextTree<Layer<>, Layer<int>> tree_b(
            nullptr,
            new Layer(new int(1))
    );

    auto tree = Context::join(std::move(tree_a), std::move(tree_b));
    Context ctx(tree);

    ASSERT_EQ(ctx.get<int>(), 0);
    ASSERT_EQ(ctx.get<int>(1), 1);
    ASSERT_EQ(ctx.get<int>(2), 2);
}


#endif //STATE_MACHINE_CPP_TEST_CONTEXT_H

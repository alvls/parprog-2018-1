#ifndef TALAMANOV_AE_TEST_VERSION_GENERATOR_GENERATOR_H
#define TALAMANOV_AE_TEST_VERSION_GENERATOR_GENERATOR_H

#include <vector>

class Generator {
public:
  enum class TestType {
    FILL_CONSTANT_VAL     = 0,
    FILL_IN_ORDER         = 1,
    FILL_IN_REORDER       = 2,
    FILL_RANDOM           = 3,
    FILL_POSITIVE_RANDOM  = 4,
    FILL_NEGATIVE_RANDOM  = 5
  };

  std::vector<int> generate(TestType type, int size_array);
};

#endif //TALAMANOV_AE_TEST_VERSION_GENERATOR_GENERATOR_H

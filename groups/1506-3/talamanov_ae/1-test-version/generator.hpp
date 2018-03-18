#ifndef GROUPS_1506_3_TALAMANOV_AE_1_TEST_VERSION_GENERATOR_H_
#define GROUPS_1506_3_TALAMANOV_AE_1_TEST_VERSION_GENERATOR_H_

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

#endif  // GROUPS_1506_3_TALAMANOV_AE_1_TEST_VERSION_GENERATOR_H_

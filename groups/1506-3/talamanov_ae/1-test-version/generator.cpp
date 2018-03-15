#include <random>
#include <algorithm>
#include <stdexcept>
#include "generator.h"

std::vector<int> Generator::generate(TestType type, int size_array) {
  std::vector<int> array(size_array);
  std::uniform_int_distribution<int> distribution;
  std::mt19937 num_generator{std::random_device()()};

  const int fill_val = 5;

  switch(type){
    case TestType::FILL_CONSTANT_VAL:
      std::fill(array.begin(), array.end(), fill_val);
      break;
    case TestType::FILL_IN_ORDER:
      std::iota(array.begin(), array.end(), 0);
      break;
    case TestType::FILL_IN_REORDER:
      std::iota(array.rbegin(), array.rend(), 0);
      break;
    case TestType::FILL_RANDOM:
      std::generate(array.begin(), array.end(), [&distribution, &num_generator]{
          return distribution(num_generator);
          });
      break;
    case TestType::FILL_POSITIVE_RANDOM:
      std::generate(array.begin(), array.end(), [&distribution, &num_generator]{
          return std::abs(distribution(num_generator));
          });
      break;
    case TestType::FILL_NEGATIVE_RANDOM:
      std::generate(array.begin(), array.end(), [&distribution, &num_generator]{
          return -1 * std::abs(distribution(num_generator));
          });
      break;
    default:
      throw std::invalid_argument("Test with this type doesn't exist");
  }

  return array;
}

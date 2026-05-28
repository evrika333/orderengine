#pragma once
#include <cstdint>
#include <unistd.h>

class Order {
public:
  unsigned int Id;
  unsigned long long TimeStamps;
  uint8_t side; // 1 is buying 0 is selling
  unsigned int Price;
};

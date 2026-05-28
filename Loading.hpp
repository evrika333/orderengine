#pragma once
#include "Order.hpp"
#include <cstdint>
#include <fcntl.h>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

// Reads a CSV file of orders into memory using mmap.
// Returns 1 on success, 0 on failure.
// CSV format per line: id,timestamp,side,price
uint8_t ReadingFile(std::string &filename, std::vector<Order> &orders);

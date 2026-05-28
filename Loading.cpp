#include "Loading.hpp"
#include <cstdlib>

// Opens the file using mmap to map it directly into memory without copying.
// Parses each line as a CSV row into an Order object and appends to orders
// vector. CSV format: id,timestamp,side,price Returns 1 on success, 0 on any
// failure (file not found, mmap failed).
uint8_t ReadingFile(std::string &filename, std::vector<Order> &orders) {
  int fd = open(filename.c_str(), O_RDONLY);
  if (fd == -1)
    return 0;

  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    close(fd);
    return 0;
  }
  size_t size = sb.st_size;

  char *data = (char *)mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
  close(fd);
  if (data == MAP_FAILED)
    return 0;

  char *ptr = data;
  char *end = data + size;

  while (ptr < end) {
    Order o;
    o.Id = (unsigned int)atoi(ptr);
    while (ptr < end && *ptr != ',')
      ptr++;
    ptr++;
    o.TimeStamps = (unsigned long long)atoll(ptr);
    while (ptr < end && *ptr != ',')
      ptr++;
    ptr++;
    o.side = (uint8_t)atoi(ptr);
    while (ptr < end && *ptr != ',')
      ptr++;
    ptr++;
    o.Price = (unsigned int)atoi(ptr);
    while (ptr < end && *ptr != '\n')
      ptr++;
    if (ptr < end)
      ptr++;

    orders.push_back(o);
  }

  munmap(data, size);
  return 1;
}

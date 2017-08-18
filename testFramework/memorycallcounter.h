#ifndef MEMORYCALLCOUNTER_H
#define MEMORYCALLCOUNTER_H
#include <memory>

namespace MemoryCallCounter{
  bool verifyMemoryCallCounter();
  void resetMemoryCallCounter();
  int getArrayAllocDifference();
  int getAllocDifference();
}

void * operator new (std::size_t size);
void * operator new[] (std::size_t size);
void operator delete(void* to_deallocate) noexcept;
void operator delete [] (void * p) noexcept;
#endif // MEMORYCALLCOUNTER_H

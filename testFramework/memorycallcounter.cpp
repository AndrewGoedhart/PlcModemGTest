#include "memorycallcounter.h"

namespace MemoryCallCounter{
  static int newCallTotal = 0;
  static int deleteCallTotal = 0;
  static int newArrayCallTotal = 0;
  static int deleteArrayCallTotal = 0;

  bool verifyMemoryCallCounter() {
    return (newCallTotal == deleteCallTotal && newArrayCallTotal == deleteArrayCallTotal);
  }

  void resetMemoryCallCounter() {
    newCallTotal = 0;
    deleteCallTotal = 0;
    newArrayCallTotal = 0;
    deleteArrayCallTotal = 0;
  }

  int getArrayAllocDifference(){
    return newArrayCallTotal - deleteArrayCallTotal;
  }

  int getAllocDifference(){
    return newCallTotal - deleteCallTotal;
  }
}

void * operator new (std::size_t size) {
  void * allocated = std::malloc(size);
  MemoryCallCounter::newCallTotal++;
  return allocated;
}

void * operator new[] (std::size_t size){
  void * allocated = malloc(size);
  MemoryCallCounter::newArrayCallTotal++;
  return allocated;
}

void operator delete(void* to_deallocate) noexcept{
  std::free(to_deallocate);
  MemoryCallCounter::deleteCallTotal++;
}

void operator delete [] (void * p) noexcept {
  free(p);
  MemoryCallCounter::deleteArrayCallTotal++;
}


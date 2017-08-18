#include <cstdint>
#include <SolexOs/ByteArray.hpp>
#include <SolexOs/elements.hpp>
#include <gtest/gtest.h>
#include <testFramework/memorycallcounter.h>

using SolexOs::ByteArray;


TEST(ByteArrayTest, copyAllocate){
  MemoryCallCounter::resetMemoryCallCounter();
  {
    ByteArray test1(256);
    {
      ByteArray test2 = test1;
      ByteArray test3 = test2;
      EXPECT_EQ(MemoryCallCounter::getArrayAllocDifference(), 1);

      for( int i=0; i < 256; i++){
        test3[i] = static_cast<uint8_t>(i);

      }

    }
    EXPECT_EQ(MemoryCallCounter::getArrayAllocDifference(), 1);

  }
  EXPECT_TRUE(MemoryCallCounter::verifyMemoryCallCounter());
}




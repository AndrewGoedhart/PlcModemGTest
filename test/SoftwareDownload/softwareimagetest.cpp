#include <cstdint>
#include <SolexOs/ByteArray.hpp>
#include <gtest/gtest.h>
#include <SoftwareDownload/SoftwareImage.hpp>

using SolexOs::ByteArray;


constexpr auto path = "../PlcModemGTest/testData/";
constexpr auto validFile = "STCOMET_G3_FCC_RT_FW_r20_CometAB.img";
constexpr auto invalidFile = "Abc.img";
constexpr auto invalidImage = "invalid.img";

TEST(SoftwareImageTest, open){
  SoftwareImage image(256);
  EXPECT_TRUE(image.openFile(QString(path)+validFile));
  EXPECT_EQ(image.getFailureReason(), QString(""));

  EXPECT_FALSE(image.openFile(QString(path)+invalidFile) );
  EXPECT_EQ(image.getFailureReason(),QString("File does not exist"));

  EXPECT_FALSE(image.openFile(QString(path)+invalidImage) );
  EXPECT_EQ(image.getFailureReason(),QString("Invalid Image File"));
}

TEST(SoftwareImageTest, getDataSegment){
  SoftwareImage image(256);
  image.openFile(QString(path)+validFile);

  auto segment = image.getDataSegment(0, 48);
  EXPECT_EQ(segment.isValid(), true);
  EXPECT_EQ(segment.getLength(), 48);
}

TEST(SoftwareImageTest, getDataSegmentPastEndOfImage){
  SoftwareImage image(256);
  image.openFile(QString(path)+validFile);

  ByteArray segment = image.getDataSegment(92648, 48);
  EXPECT_EQ(segment.isValid(), false);
  EXPECT_EQ(segment.getLength(), 0);
}

TEST(SoftwareImageTest, getDataSegmentPageBoundary){
  SoftwareImage image(256);
  image.openFile(QString(path)+validFile);

  auto segment = image.getDataSegment(250, 48);
  EXPECT_EQ(segment.isValid(), true);
  EXPECT_EQ(segment.getLength(), 6);
}

TEST(SoftwareImageTest, getDataSegmentData){
  SoftwareImage image(256);
  image.openFile(QString(path)+validFile);

  uint8_t expectedData[]= { 0xBF, 0xA1,0x30,0x97,0x77,0xBF};
  auto expected = ByteArray(expectedData, 6);
  auto segment = image.getDataSegment(250, 48);
  EXPECT_TRUE(segment == expected);
}

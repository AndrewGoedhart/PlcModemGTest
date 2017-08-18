#include <gtest/gtest.h>

#include <SolexOs/SerialMessage.hpp>

namespace SolexOs {

  // constants used for packet delinearation
  static constexpr uint8_t STX = 0x2;
  static constexpr uint8_t ETX = 0x3;

  static constexpr uint8_t expectedBytes[2][13] = {{0x02, 0x0a, 0xff,0x00,0xab, 0x00, 0x01, 0x74, 0x00,0x00,0x46,0xc8,0x03},
                                                   {0x02, 0x0a, 0x3b,0xff, 0xab, 0x3b, 0x01,0x03, 0x4b,0x8a,0xd4,0x58,0x03}};
  static constexpr uint8_t payloadBytes[2][8] = {{0xff,0x00,0xab, 0x00, 0x01, 0x74, 0x00,0x00},
                                                  {0x3b,0xff, 0xab, 0x3b, 0x01, 0x03, 0x4b,0x8a}};


 /**
   * Test that the message expands to the following format
   *    STX|LEN|PAYLOAD|CRC|ETX
   */
  TEST(SerialMessageTest, testNetworkBytesEncode) {

    for( int i =0; i < 2; i++){
      ByteArray payload(payloadBytes[i], 8);
      SerialMessage msg = SerialMessage(8);
      msg.getPayload() = payload;
      auto result = msg.getNetworkBytes();
      ByteArray expected(expectedBytes[i], 13);
      EXPECT_EQ(result , expected);
    }
  }


  /**
    * Test that the message expands to the following format
    *    STX|LEN|PAYLOAD|CRC|ETX
    */
   TEST(SerialMessageTest, testNetworkBytesDecode) {

     for( int i =0; i < 2; i++){
       ByteArray rawMessage(expectedBytes[i], 13);
       ByteArray expectedPayload(payloadBytes[i], 8);
       auto stream = rawMessage.getReadStream();
       SerialMessage msg = SerialMessage::convertNetworkBytes(stream);
       EXPECT_TRUE(msg.isValid());
       EXPECT_EQ(msg.getPayload() , expectedPayload);
     }
   }


   /**
     * Test that the message expands to the following format
     *    STX|LEN|PAYLOAD|CRC|ETX
     */
    TEST(SerialMessageTest, testNetworkDecodeShortPacket) {
      static constexpr uint8_t expectedBytes[12] = {0x02, 0x0a, 0xff,0x00,0xab, 0x00, 0x01, 0x74, 0x00,0x00,0x46,0xc8 };

      ByteArray rawMessage(expectedBytes, 12);
      auto stream = rawMessage.getReadStream();
      SerialMessage msg = SerialMessage::convertNetworkBytes(stream);
      EXPECT_TRUE(!msg.isValid());
      EXPECT_EQ( stream.bytesLeft(), 12U);
    }

}

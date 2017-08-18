GOOGLETEST_DIR = /home/andrew/tools/gtest
include(gtest_dependency.pri)
TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread

INCLUDEPATH += ../PlcModemGui/include
INCLUDEPATH += test

HEADERS +=     tst_messagetest.h \
    ../PlcModemGui/include/SolexOs/TaskId.hpp \
    ../PlcModemGui/include/SolexOs/Stream.hpp \
    ../PlcModemGui/include/SolexOs/Registers.hpp \
    ../PlcModemGui/include/SolexOs/NodeId.hpp \
    ../PlcModemGui/include/SolexOs/MessageId.hpp \
    ../PlcModemGui/include/SolexOs/Message.hpp \
    ../PlcModemGui/include/SolexOs/MemoryStream.hpp \
    ../PlcModemGui/include/SolexOs/elements.hpp \
    ../PlcModemGui/include/SolexOs/CrcDriver.hpp \
    ../PlcModemGui/include/SolexOs/Crc32.hpp \
    ../PlcModemGui/include/SolexOs/ByteArray.hpp \
    ../PlcModemGui/include/SolexOs/ArrayInstanceData.hpp \
    ../PlcModemGui/include/SolexOs/Address.hpp \
    testFramework/memorycallcounter.h \
    ../PlcModemGui/include/SolexOs/Crc16.hpp \
    ../PlcModemGui/include/SolexOs/SerialMessage.hpp
SOURCES +=     main.cpp \
    ../PlcModemGui/src/SolexOs/messageid.cpp \
    ../PlcModemGui/src/SolexOs/message.cpp \
    ../PlcModemGui/src/SolexOs/crc.cpp \
    testFramework/memorycallcounter.cpp \
    test/SolexOs/ByteArrayTest.cpp \
    test/SolexOs/MessageTest.cpp \
    ../PlcModemGui/src/SoftwareDownload/softwareimage.cpp \
    test/SoftwareDownload/softwareimagetest.cpp \
    test/SolexOs/serialmessagetest.cpp

/*
 * =====================================================================================
 *
 *       Filename:  HardwareKnowledge.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yt (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <cassert>
#include <iostream>
#include <endian.h>




#pragma pack(push)
#pragma pack(1)
struct IPHeader {
  // we are little endian so becareful
  struct {
    uint8_t version : 4;
    uint8_t headerLength : 4;
  } byte0;

  struct {
    uint8_t dscp : 6;
    uint8_t ecn : 2;
  } byte1;

	// byte 2 & 3
  uint16_t totalLength;     // 注意啊，我们假设是little endian
	// byte 4 & 5
  uint16_t identification;  // above
  struct {
    uint16_t flag : 3;
    uint16_t fragmentOffset : 13;
  } byte6and7;
	// byte 8
  uint8_t timeToLive;
	// byte 9
  uint8_t protocal;
	// byte 10 11
  uint16_t checksum;
	// byte 12 13 14 15
  uint32_t sourceAddress;
	// byte 16 17 18 19
  uint32_t targetAddress;
  // no option part
	void fillToData(uint8_t* buffer, size_t bufferSize) {
		assert(bufferSize >= 20);
	}
};

#pragma pack(pop)



























// 一个32位四字节的整数值，例如 1， 实际的计算机编码表示 是 0x00000001
// 小端系统中在内存中的表示是 01 00 00 00
// 大端系统中在内存中的表示是 00 00 00 01
union EndianTest {
	int8_t u[4];
	int32_t i;
};

static bool isLittleEndianSystem() {
	EndianTest et;
	et.i = 1;
	return et.u[0] == 1;
}

















static bool isLittleEndianOs() {
	return __BYTE_ORDER == __LITTLE_ENDIAN;
}

int main(int argc, char **argv) {
  if (isLittleEndianSystem())
    std::cout << "This system is little endian\n";
  else
    std::cout << "This system is big endian\n";
}



#ifndef CPU_HPP_
#define CPU_HPP_

#include <avr/io.h>
#include <stdint.h>

namespace cpu
{
   static constexpr auto NOP  = 0x00;
   static constexpr auto LDI  = 0x01;
   static constexpr auto MOV  = 0x02;
   static constexpr auto OUT  = 0x03;
   static constexpr auto IN   = 0x04;
   static constexpr auto ST   = 0x05;
   static constexpr auto LD   = 0x06;
   static constexpr auto CLR  = 0x07;
   static constexpr auto LSL  = 0x08;
   static constexpr auto LSR  = 0x09;
   static constexpr auto ORI  = 0x0A;
   static constexpr auto ANDI = 0x0B;
   static constexpr auto XORI = 0x0C;
   static constexpr auto OR   = 0x0D;
   static constexpr auto AND  = 0x0E;
   static constexpr auto XOR  = 0x0F;

   static constexpr auto ADDI = 0x10;
   static constexpr auto SUBI = 0x11;
   static constexpr auto ADD  = 0x12;
   static constexpr auto SUB  = 0x13;
   static constexpr auto INC  = 0x14;
   static constexpr auto DEC  = 0x15;
   static constexpr auto CMPI = 0x16;
   static constexpr auto CMP  = 0x17;
   static constexpr auto PUSH = 0x18;
   static constexpr auto POP  = 0x19;
   static constexpr auto CALL = 0x1A;
   static constexpr auto RET  = 0x1B;
   static constexpr auto RETI = 0x1C;
   static constexpr auto JMP  = 0x1D;
   static constexpr auto JE   = 0x1E;
   static constexpr auto JNE  = 0x1F;

   static constexpr auto JGE  = 0x20;
   static constexpr auto JGT  = 0x21;
   static constexpr auto JLE  = 0x22;
   static constexpr auto JLO  = 0x23;
   static constexpr auto SEI  = 0x24;
   static constexpr auto CLI  = 0x25;

   static constexpr auto I = 5;
   static constexpr auto S = 4;
   static constexpr auto N = 3;
   static constexpr auto Z = 2;
   static constexpr auto V = 1;
   static constexpr auto C = 0;

   static constexpr auto DDRA  = 0x00;
   static constexpr auto PORTA = 0x01;
   static constexpr auto PINA  = 0x02;
   static constexpr auto ICR   = 0x03;
   static constexpr auto IFR   = 0x04;
   static constexpr auto PCMSK = 0x05;

   static constexpr auto PCIEA = 0;
   static constexpr auto PCIFA = 0;

   static constexpr auto R0  = 0x00;
   static constexpr auto R1  = 0x01;
   static constexpr auto R2  = 0x02;
   static constexpr auto R3  = 0x03;
   static constexpr auto R4  = 0x04;
   static constexpr auto R5  = 0x05;
   static constexpr auto R6  = 0x06;
   static constexpr auto R7  = 0x07;
   static constexpr auto R8  = 0x08;
   static constexpr auto R9  = 0x09;
   static constexpr auto R10 = 0x0A;
   static constexpr auto R11 = 0x0B;
   static constexpr auto R12 = 0x0C;
   static constexpr auto R13 = 0x0D;
   static constexpr auto R14 = 0x0E;
   static constexpr auto R15 = 0x0F;

   static constexpr auto R16 = 0x10;
   static constexpr auto R17 = 0x11;
   static constexpr auto R18 = 0x12;
   static constexpr auto R19 = 0x13;
   static constexpr auto R20 = 0x14;
   static constexpr auto R21 = 0x15;
   static constexpr auto R22 = 0x16;
   static constexpr auto R23 = 0x17;
   static constexpr auto R24 = 0x18;
   static constexpr auto R25 = 0x19;
   static constexpr auto R26 = 0x1A;
   static constexpr auto R27 = 0x1B;
   static constexpr auto R28 = 0x1C;
   static constexpr auto R29 = 0x1D;
   static constexpr auto R30 = 0x1E;
   static constexpr auto R31 = 0x1F;

   static constexpr auto XL = R26;
   static constexpr auto XH = R27;
   static constexpr auto YL = R28;
   static constexpr auto YH = R29;
   static constexpr auto ZL = R30;
   static constexpr auto ZH = R31;

   static constexpr auto XPTR = XL;
   static constexpr auto YPTR = YL;
   static constexpr auto ZPTR = ZL;

   static constexpr auto RESET_vect = 0x00;
   static constexpr auto PCINT_vect = 0x02;

   static constexpr auto PORTA0  = 0x00;
   static constexpr auto PORTA1  = 0x01;
   static constexpr auto PORTA2  = 0x02;
   static constexpr auto PORTA3  = 0x03;
   static constexpr auto PORTA4  = 0x04;
   static constexpr auto PORTA5  = 0x05;
   static constexpr auto PORTA6  = 0x06;
   static constexpr auto PORTA7  = 0x07;
   static constexpr auto PORTA8  = 0x08;
   static constexpr auto PORTA9  = 0x09;
   static constexpr auto PORTA10 = 0x0A;
   static constexpr auto PORTA11 = 0x0B;
   static constexpr auto PORTA12 = 0x0C;
   static constexpr auto PORTA13 = 0x0D;
   static constexpr auto PORTA14 = 0x0E;
   static constexpr auto PORTA15 = 0x0F;

   static constexpr auto PORTA16 = 0x10;
   static constexpr auto PORTA17 = 0x11;
   static constexpr auto PORTA18 = 0x12;
   static constexpr auto PORTA19 = 0x13;
   static constexpr auto PORTA20 = 0x14;
   static constexpr auto PORTA21 = 0x15;
   static constexpr auto PORTA22 = 0x16;
   static constexpr auto PORTA23 = 0x17;
   static constexpr auto PORTA24 = 0x18;
   static constexpr auto PORTA25 = 0x19;
   static constexpr auto PORTA26 = 0x1A;
   static constexpr auto PORTA27 = 0x1B;
   static constexpr auto PORTA28 = 0x1C;
   static constexpr auto PORTA29 = 0x1D;
   static constexpr auto PORTA30 = 0x1E;
   static constexpr auto PORTA31 = 0x1F;

   static constexpr auto REGISTER_ADDRESS_WIDTH = 32;

   enum class state
   {
      fetch,
      decode,
      execute
   };

   template<class T = uint8_t>
   static inline void set(T& reg, const uint8_t bit)
   {
      reg |= (1 << bit);
      return;
   }

   template<class T = uint8_t>
   static inline void clr(T& reg, const uint8_t bit)
   {
      reg &= ~(1 << bit);
      return;
   }

   template<class T = uint8_t>
   static inline bool read(const T& reg, const uint8_t bit)
   {
      return static_cast<bool>(reg & (1 << bit));
   }

   auto high = [](const uint16_t value)
   {
      return static_cast<uint8_t>(value >> 8);
   };

   auto low = [](const uint16_t value)
   {
      return static_cast<uint8_t>(value);
   };

   template<class T = uint32_t>
   static uint8_t byte(const T& value)
   {
      return static_cast<uint8_t>(value);
   }

   template<class T = uint32_t>
   static uint16_t word(const T& value)
   {
      return static_cast<uint16_t>(value);
   }

   template<class T = uint64_t>
   static uint32_t dword(const T& value)
   {
      return static_cast<uint32_t>(value);
   }

   template<class T = uint32_t>
   static uint64_t ddword(const T& value)
   {
      return static_cast<uint64_t>(value);
   }
}



#endif /* CPU_HPP_ */

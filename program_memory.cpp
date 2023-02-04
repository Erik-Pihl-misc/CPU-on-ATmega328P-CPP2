#include "program_memory.hpp"

namespace cpu
{
   static constexpr auto main          = 4;
   static constexpr auto main_loop     = 5;
   static constexpr auto setup         = 6;
   static constexpr auto ISR_PCINT     = 15;
   static constexpr auto ISR_PCINT_end = 19;

   static constexpr auto LED1    = PORTA8;
   static constexpr auto BUTTON1 = PORTA13;

   static inline uint64_t join(const uint16_t op_code,
                               const uint16_t op1 = 0x00,
                               const uint32_t op2 = 0x00);

   static uint64_t program_memory[PROGRAM_MEMORY_ADDRESS_WIDTH];
}

void cpu::program_memory_write(void)
{
   static auto program_memory_initialized = false;
   if (program_memory_initialized) return;

   program_memory[0]  = join(JMP, main);
   program_memory[1]  = join(NOP);
   program_memory[2]  = join(JMP, ISR_PCINT);
   program_memory[3]  = join(NOP);

   program_memory[4]  = join(CALL, setup);
   program_memory[5]  = join(JMP, main_loop);

   program_memory[6]  = join(LDI, R16, (1 << LED1));
   program_memory[7]  = join(OUT, DDRA, R16);
   program_memory[8]  = join(LDI, R17, (1 << BUTTON1));
   program_memory[9]  = join(OUT, PORTA, R17);
   program_memory[10] = join(SEI);
   program_memory[11] = join(LDI, R24, (1 << PCIEA));
   program_memory[12] = join(OUT, ICR, R24);
   program_memory[13] = join(OUT, PCMSK, R17);
   program_memory[14] = join(RET);

   program_memory[15] = join(IN, R24, PINA);
   program_memory[16] = join(ANDI, R24, (1 << BUTTON1));
   program_memory[17] = join(JE, ISR_PCINT_end);
   program_memory[18] = join(OUT, PINA, R16);
   program_memory[19] = join(RETI);

   program_memory_initialized = true;
   return;
}

uint64_t cpu::program_memory_read(const uint16_t address)
{
   if (address < PROGRAM_MEMORY_ADDRESS_WIDTH)
   {
      return program_memory[address];
   }
   else
   {
      return 0x00;
   }
}

static inline uint64_t cpu::join(const uint16_t op_code,
                                 const uint16_t op1,
                                 const uint32_t op2)
{
   const uint64_t instruction = static_cast<uint64_t>((ddword(op_code) << 48) | (ddword(op1) << 32) | op2);
   return instruction;
}
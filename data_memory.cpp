#include "data_memory.hpp"

namespace cpu
{
   static uint32_t data_memory[DATA_MEMORY_ADDRESS_WIDTH];
}

void cpu::data_memory_reset(void)
{
   for (auto i = data_memory; i < data_memory + DATA_MEMORY_ADDRESS_WIDTH; ++i)
   {
      *i = 0x00;
   }
   return;
}

int cpu::data_memory_write(const uint16_t address,
                           const uint32_t value)
{
   if (address < DATA_MEMORY_ADDRESS_WIDTH)
   {
      data_memory[address] = value;
      return 0;
   }
   else
   {
      return 1;
   }
}

uint32_t cpu::data_memory_read(const uint16_t address)
{
   if (address < DATA_MEMORY_ADDRESS_WIDTH)
   {
      return data_memory[address];
   }
   else
   {
      return 0x00;
   }
}
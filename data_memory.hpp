
#ifndef DATA_MEMORY_HPP_
#define DATA_MEMORY_HPP_

#include "cpu.hpp"

namespace cpu
{
   static constexpr auto DATA_MEMORY_ADDRESS_WIDTH = 300;

   void data_memory_reset(void);
   int data_memory_write(const uint16_t address,
                         const uint32_t value);
   uint32_t data_memory_read(const uint16_t address);
}

#endif /* DATA_MEMORY_HPP_ */
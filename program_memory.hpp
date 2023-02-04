
#ifndef PROGRAM_MEMORY_HPP_
#define PROGRAM_MEMORY_HPP_

#include "cpu.hpp"

namespace cpu
{
   static constexpr auto PROGRAM_MEMORY_ADDRESS_WIDTH = 25;
   void program_memory_write(void);
   uint64_t program_memory_read(const uint16_t address);
}

#endif /* PROGRAM_MEMORY_HPP_ */
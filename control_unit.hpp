
#ifndef CONTROL_UNIT_HPP_
#define CONTROL_UNIT_HPP_

#include "cpu.hpp"
#include "program_memory.hpp"
#include "data_memory.hpp"
#include "stack.hpp"
#include "alu.hpp"

namespace cpu
{
   void reset(void);
   void run(void);
}

#endif /* CONTROL_UNIT_HPP_ */
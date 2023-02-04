
#ifndef STACK_HPP_
#define STACK_HPP_

#include "cpu.hpp"

namespace cpu
{
   static constexpr auto STACK_ADDRESS_WIDTH = 100;

   void stack_reset(void);
   int stack_push(const uint32_t value);
   uint32_t stack_pop(void);
}

#endif /* STACK_HPP_ */
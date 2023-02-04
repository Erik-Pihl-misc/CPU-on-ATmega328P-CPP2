#include "stack.hpp"

namespace cpu
{
   static uint32_t stack[STACK_ADDRESS_WIDTH];
   uint16_t sp;
   bool stack_empty;
}

void cpu::stack_reset(void)
{
   for (auto i = stack; i < stack + STACK_ADDRESS_WIDTH; ++i)
   {
      *i = 0x00;
   }

   sp = STACK_ADDRESS_WIDTH - 1;
   stack_empty = true;
   return;
}

int cpu::stack_push(const uint32_t value)
{
   if (sp == 0)
   {
      return 1;
   }
   else
   {
      if (stack_empty)
      {
         stack[sp] = value;
         stack_empty = false;
      }
      else
      {
         stack[sp--] = value;
      }
      return 0;
   }
}

uint32_t cpu::stack_pop(void)
{
   if (stack_empty)
   {
      return 0;
   }
   else
   {
      if (sp < STACK_ADDRESS_WIDTH - 1)
      {
         return stack[sp++];
      }
      else
      {
         stack_empty = true;
         return stack[sp];
      }
   }
}
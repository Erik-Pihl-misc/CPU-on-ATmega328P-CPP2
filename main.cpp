#include "control_unit.hpp"

int main(void)
{
   cpu::reset();
   
   while (1)
   {
      cpu::run();
   }

   return 0;
}


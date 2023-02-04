#include "control_unit.hpp"

namespace cpu
{
   static void io_reset(void);
   static void io_update(void);
   static inline void cpu_registers_clear(void);

   static inline void monitor_interrupts(void);
   static inline void check_for_interrupt_requests(void);
   static inline void generate_interrupt(const uint16_t interrupt_vector);
   static inline void return_from_interrupt(void);

   static uint16_t pc;
   static uint64_t ir;
   static uint8_t sr;

   static uint16_t op_code;
   static uint16_t op1;
   static uint32_t op2;

   static cpu::state current_state;
   static volatile uint32_t pina_last_value;
   static uint32_t reg[REGISTER_ADDRESS_WIDTH];
}

void cpu::reset(void)
{
   pc = 0x00;
   ir = 0x00;
   sr = 0x00;

   op_code = 0x00;
   op1 = 0x00;
   op2 = 0x00;

   current_state = state::fetch;
   pina_last_value = 0x00;

   cpu_registers_clear();
   program_memory_write();
   data_memory_reset();
   stack_reset();
   io_reset();
   return;
}

void cpu::run(void)
{
   switch (current_state)
   {
      case state::fetch:
      {
         ir = program_memory_read(pc++);
         current_state = state::decode;
         break;
      }
      case state::decode:
      {
         op_code = static_cast<uint16_t>(ir >> 48);
         op1     = static_cast<uint16_t>(ir >> 32);
         op2     = static_cast<uint32_t>(ir);
         current_state = state::execute;
         break;
      }
      case state::execute:
      {
         switch (op_code)
         {
            case NOP:
            {
               break;
            }
            case LDI:
            {
               reg[byte(op1)] = op2;
               break;
            }
            case MOV:
            {
               reg[(byte)(op1)] = reg[byte(op2)];
               break;
            }
            case OUT:
            {
               if (op1 == PINA)
               {
                  const auto porta = data_memory_read(PORTA) ^ reg[byte(op2)];
                  data_memory_write(PORTA, porta);
               }
               else
               {
                  data_memory_write(op1, reg[byte(op2)]);
               }
               break;
            }
            case IN:
            {
               reg[byte(op1)] = data_memory_read(word(op2));
               break;
            }
            case ST:
            {
               data_memory_write(reg[byte(op1)], reg[byte(op2)]);
               break;
            }
            case LD:
            {
               reg[byte(op1)] = data_memory_read(reg[byte(op2)]);
               break;
            }
            case CLR:
            {
               reg[byte(op1)] = 0x00;
               break;
            }
            case LSL:
            {
               reg[byte(op1)] = reg[byte(op1)] << 1;
               break;
            }
            case LSR:
            {
               reg[byte(op1)] = reg[byte(op1)] >> 1;
               break;
            }
            case ORI:
            {
               reg[byte(op1)] = alu(OR, reg[byte(op1)], op2, sr);
               break;
            }
            case ANDI:
            {
               reg[byte(op1)] = alu(AND, reg[byte(op1)], op2, sr);
               break;
            }
            case XORI:
            {
               reg[byte(op1)] = alu(XOR, reg[byte(op1)], op2, sr);
               break;
            }
            case OR:
            {
               reg[byte(op1)] = alu(OR, reg[byte(op1)], reg[byte(op2)], sr);
               break;
            }
            case AND:
            {
               reg[byte(op1)] = alu(AND, reg[byte(op1)], reg[byte(op2)], sr);
               break;
            }
            case XOR:
            {
               reg[byte(op1)] = alu(XOR, reg[byte(op1)], reg[byte(op2)], sr);
               break;
            }
            case ADDI:
            {
               reg[byte(op1)] = alu(ADD, reg[byte(op1)], op2, sr);
               break;
            }
            case SUBI:
            {
               reg[byte(op1)] = alu(SUB, reg[byte(op1)], op2, sr);
               break;
            }
            case ADD:
            {
               reg[byte(op1)] = alu(ADD, reg[byte(op1)], reg[byte(op2)], sr);
               break;
            }
            case SUB:
            {
               reg[byte(op1)] = alu(SUB, reg[byte(op1)], reg[byte(op2)], sr);
               break;
            }
            case INC:
            {
               reg[byte(op1)] = alu(ADD, reg[byte(op1)], 1, sr);
               break;
            }
            case DEC:
            {
               reg[byte(op1)] = alu(SUB, reg[byte(op1)], 1, sr);
               break;
            }
            case CMPI:
            {
               static_cast<void>(alu(SUB, reg[byte(op1)], op2, sr));
               break;
            }
            case CMP:
            {
               static_cast<void>(alu(SUB, reg[byte(op1)], reg[byte(op2)], sr));
               break;
            }
            case CALL:
            {
               stack_push(pc);
               pc = op1;
               break;
            }
            case RET:
            {
               pc = stack_pop();
               break;
            }
            case RETI:
            {
               return_from_interrupt();
               break;
            }
            case PUSH:
            {
               stack_push(reg[byte(op1)]);
               break;
            }
            case POP:
            {
               reg[byte(op1)] = stack_pop();
               break;
            }
            case JMP:
            {
               pc = word(op1);
               break;
            }
            case JE:
            {
               if (read(sr, Z)) pc = op1;
               break;
            }
            case JNE:
            {
               if (!read(sr, Z)) pc = op1;
               break;
            }
            case JGE:
            {
               if (!read(sr, S)) pc = op1;
               break;
            }
            case JGT:
            {
               if (!read(sr, S) && !read(sr, Z)) pc = op1;
               break;
            }
            case JLE:
            {
               if (read(sr, S) || read(sr, Z)) pc = op1;
               break;
            }
            case JLO:
            {
               if (read(sr, S)) pc = op1;
               break;
            }
            case SEI:
            {
               set(sr, I);
               break;
            }
            case CLI:
            {
               clr(sr, I);
               break;
            }
            default:
            {
               reset();
               break;
            }
         }

         check_for_interrupt_requests();
         current_state = state::fetch;
         break;
      }
      default:
      {
         reset();
         break;
      }
   }

   io_update();
   monitor_interrupts();
   return;
}

static void cpu::io_reset(void)
{
   DDRB = 0x00;
   DDRC = 0x00;
   DDRD = 0x00;

   PORTB = 0x00;
   PORTC = 0x00;
   PORTD = 0x00;

   return;
}

static void cpu::io_update(void)
{
  const auto ddra = data_memory_read(DDRA);
  const auto porta = data_memory_read(PORTA);
  const auto pina = dword((dword(PINC) << 16) | (word(PINB) << 8) | PIND);
  
  data_memory_write(PINA, pina); 

  DDRB = byte(ddra >> 8);
  DDRC = byte(ddra >> 16);
  DDRD = byte(ddra);

  PORTB = byte(porta >> 8);
  PORTC = byte(porta >> 16);
  PORTD = byte(porta);
  return;
}

static inline void cpu::cpu_registers_clear(void)
{
   for (auto i = reg; i < reg + REGISTER_ADDRESS_WIDTH; ++i)
   {
      *i = 0x00;
   }
   return;
}

static inline void cpu::monitor_interrupts(void)
{
   const auto pina = data_memory_read(PINA);

   for (uint8_t i = 0; i < REGISTER_ADDRESS_WIDTH; ++i)
   {
      if (read(pina, i) != read(pina_last_value, i))
      {
         const auto pcmsk = data_memory_read(PCMSK);

         if (read(pcmsk, i))
         {
            auto ifr = data_memory_read(IFR);
            set(ifr, PCIFA);
            data_memory_write(IFR, ifr);
            break;
         }
      }
   }

   pina_last_value = pina;
   return;
}

static inline void cpu::check_for_interrupt_requests(void)
{
   if (read(sr, I))
   {
      auto ifr = data_memory_read(IFR);
      const auto icr = data_memory_read(ICR);

      if (read(ifr, PCIFA) && read(icr, PCIEA))
      {
         clr(ifr, PCIFA);
         data_memory_write(IFR, ifr);
         generate_interrupt(PCINT_vect);
      }
   }
   return;
}

static inline void cpu::generate_interrupt(const uint16_t interrupt_vector)
{
   stack_push(pc);
   pc = interrupt_vector;
   clr(sr, I);
   return;
}

static inline void cpu::return_from_interrupt(void)
{
   pc = stack_pop();
   set(sr, I);
   return;
}
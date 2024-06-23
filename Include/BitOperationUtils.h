#include <stdint.h>

#define TRUE  (1U)
#define FALSE (0U)

#define BITFIELD_SET(variable, bitfield, type)                      ((variable) |= (bitfield))
#define BITFIELD_CLEAR(variable, bitfield, type)                    ((variable) &= (type)(~(bitfield)))
#define BITFIELD_INVERT(variable, bitfield, type)                   ((variable) ^= (bitfield))
#define BITFIELD_MODIFY(variable, clearbitfield, setbitfield, type) ((variable) = (type)(((variable) & (~(clearbitfield))) | (setbitfield)))
#define BITFIELD_TOGGLE(var, bitfield)  ((var) ^=  (bitfield))

/* Bit field set */
#define BFS(type, variable, bitfield)                   ((variable) |= (type)(bitfield))
#define BFS32(variable, bitfield)                       ((variable) |= (uint32_t)(bitfield))
/* Bit field clear */
#define BFC(type, variable, bitfield)                   ((variable) &= (type)(~(bitfield)))
#define BFC32(variable, bitfield)                       ((variable) &= (uint32_t)(~(bitfield)))
/* Bit field invert */
#define BFI(type, variable, bitfield)                   ((variable) ^= (type)(bitfield))
/* Bit field modify */
#define BFM(type, variable, clearbitfield, setbitfield) ((variable)  = (type)(((variable) & (~(clearbitfield))) | (setbitfield)))

#define BFT(type, var, bitfield)  ((var) ^=  (type)(bitfield))

#define BFM8(variable, clearbitfield, setbitfield)  BFM(uint8_t, variable, clearbitfield, setbitfield)
#define BFM16(variable, clearbitfield, setbitfield) BFM(uint16_t, variable, clearbitfield, setbitfield)
#define BFM32(variable, clearbitfield, setbitfield) BFM(uint32_t, variable, clearbitfield, setbitfield)

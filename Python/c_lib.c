#include <stdint.h>

uint8_t square(uint8_t i)
{
	return i * i;
}

uint32_t uint32_to_float_interpreter(uint32_t num)
{
	return (uint32_t)(*(float *)(void *)&num);
}
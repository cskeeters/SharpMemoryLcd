#include "checker.h"
#include <avr/pgmspace.h>

Checker::Checker(int width, int height)
  : MonoImage(width, height, 0)
{
}

//value of x is a multiple of 8
unsigned char Checker::byte(int x, int y) const
{
  if (y % 2 == 0) {
    return 0x55;
  }
  return 0xAA;
}

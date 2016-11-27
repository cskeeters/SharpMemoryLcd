#ifndef CHECKER_H
#define CHECKER_H 1

#include <mono_image.h>

class Checker : public MonoImage
{
  public:
    Checker(int width, int height);
    unsigned char byte(int x, int y) const;
};

#endif

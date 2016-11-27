#include "mono_image.h"
#include <avr/pgmspace.h>

MonoImage::MonoImage(int width, int height, const unsigned char *data)
{
  width_ = width;
  height_ = height;
  data_ = data;

  width_in_bytes_ = width_ / 8;
  if (width_ % 8 != 0) width_in_bytes_++;
}

MonoImage::~MonoImage()
{
}


int MonoImage::width() const
{
  return width_;
}

int MonoImage::height() const
{
  return height_;
}

bool MonoImage::on(int x, int y) const
{
  unsigned char temp = byte(x, y);

  int to_shift = 7 - (x % 8);
  for (int i=0; i< to_shift; i++) {
    temp = temp >> 1;
  }
  return temp & 1;
}

//value of x is a multiple of 8
unsigned char MonoImage::byte(int x, int y) const
{
  if (x >= width_) return 0xff;
  if (y >= height_) return 0xff;

  int byte_index = y*width_in_bytes_ + x/8;
  return pgm_read_byte(data_+byte_index);
}

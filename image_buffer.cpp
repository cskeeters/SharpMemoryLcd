#include "image_buffer.h"
#include <stdlib.h>
#include "Arduino.h"

ImageBuffer::ImageBuffer(int width, int height, unsigned char *data, int line_offset)
  : MonoImage(width, height, NULL), Adafruit_GFX(width, height)
{
  width_ = width;
  height_ = height;
  line_offset_ = line_offset;

  buffer_ = data;

  width_in_bytes_ = width_ / 8;
  if (width_ % 8 != 0) width_in_bytes_++;

  clear();

  //Adafruit_GFX init method
  //constructor(width, height);
}

ImageBuffer::~ImageBuffer()
{
  buffer_ = NULL;
}

//value of x is a multiple of 8
unsigned char ImageBuffer::byte(int x, int y) const
{
  //Serial.print("Y:");
  //Serial.println(y);

  if (x < 0) return 0xff;
  if (y < 0) return 0xff;
  if (x >= width_) return 0xff;
  if (y >= height_) return 0xff;

  int byte_index = y*width_in_bytes_ + x/8;
  return *(buffer_+byte_index);
}

void ImageBuffer::set_byte(int x, int y, int data)
{
  //should I throw an exception here?
  if (x >= width_) return;
  if (y >= height_) return;

  int byte_index = y*width_in_bytes_ + x/8;
  *(buffer_+byte_index) = data;
}


void ImageBuffer::set_bit(int x, int y, bool data)
{
  if (x < 0) return;
  if (y < 0) return;
  if (x >= width_) return;
  if (y >= height_) return;

  int byte_index = y*width_in_bytes_ + x/8;
  unsigned char current = *(buffer_+byte_index);
  int newval = 1 << x%8;
  if (data) {
    *(buffer_+byte_index) |= newval;
  } else {
    *(buffer_+byte_index) &= ~newval;
  }
}

void ImageBuffer::clear() {
  for (int i=0; i<width_/8*height_; i++) {
    *(buffer_+i) = 0xFF;
  }
}

void ImageBuffer::set_line_offset(int line_offset)
{
  line_offset_ = line_offset;
  _height = height_+line_offset;
}

void ImageBuffer::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  //Serial.print("Asked to draw on ");
  //Serial.print(y);
  //Serial.print(". Drawing on ");
  //Serial.println(y-line_offset_);
  set_bit((int) x, (int) y-line_offset_, color&0x01);
}

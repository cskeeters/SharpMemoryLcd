#ifndef IMAGE_BUFFER_H
#define IMAGE_BUFFER_H 1

#include <mono_image.h>
#include <Adafruit_GFX.h>

class ImageBuffer : public MonoImage, public Adafruit_GFX
{
  public:
    ImageBuffer(int width, int height, unsigned char *data, int line_offset=0);
    virtual ~ImageBuffer();

    unsigned char byte(int x, int y) const;

    void clear();
    void set_bit(int x, int y, bool data);
    void set_byte(int x, int y, int data);


    //Adafruit_GFX
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    //So that GFX can use this buffer but only update a portion of the lines
    void set_line_offset(int line_offset);

  private:
    unsigned char *buffer_;
    int line_offset_;
};

#endif

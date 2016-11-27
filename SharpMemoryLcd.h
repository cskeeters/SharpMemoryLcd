#ifndef SHARPMEMORYLCD_H
#define SHARPMEMORYLCD_H

#include "Arduino.h"
#include <Adafruit_GFX.h>

#include "mono_image.h"


class SharpMemoryLcd {
  public:
    SharpMemoryLcd();
    ~SharpMemoryLcd();

    void init(int disp, int si, int scs, int sclk);
    void clear();
    void send(const MonoImage &img, int line_offset=0);
    void send_interlaced(const MonoImage &img, int line_offset=0);


  private:
    int DISP; //High to turn the display on

    int SI;   //Standard SPI
    int SCS;
    int SCLK;

    void post(int delayTime);
    void send_byte(char byteToSend);
    void send_pixels(int num, int state);

    void set_mode(int M0, int M2);
    void set_line_address(int line);
};

#endif

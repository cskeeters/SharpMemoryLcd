#include <Adafruit_GFX.h>
#include <SharpMemoryLcd.h>
#include <chad.h>
#include <arduino_data.h>
#include <checker.h>
#include <image_buffer.h>

#define DISP 2
#define SI 11
#define SCS 12
#define SCLK 13

SharpMemoryLcd *lcd;

// CONST1: Not enough memory if I use 128 for HEIGHT
#define WIDTH 128
#define HEIGHT 64

unsigned char image_buffer[WIDTH/8*HEIGHT];

void setup() {
  Serial.begin(9600);
  lcd = new SharpMemoryLcd();
  lcd->init(DISP, SI, SCS, SCLK);
}

void text(ImageBuffer &buffer) {
  buffer.setCursor(1,32);
  buffer.setTextColor(0, 1);
  buffer.setTextSize(1);
  buffer.setTextWrap(1);
  buffer.println("Craftycoder's");
  buffer.println("Sharp Memory");
  buffer.println("LCD Library"); 
  buffer.println("Extends"); 
  buffer.println("Adafruit GFX");
  buffer.println("Sharp Memory");
  buffer.println("LCD Library"); 
  buffer.println("Extends"); 
  buffer.println("Adafruit GFX");
}

void graphics(ImageBuffer &buffer) {
  buffer.drawLine(0, 0, 127, 127, 0);
  buffer.fillRect(4, 4, 17, 17, 0);
  buffer.fillCircle(12, 12, 8, 1);
}

void do_draw(void (*draw)(ImageBuffer &buffer)) {
  ImageBuffer buffer(128, 64, image_buffer, 0);
  buffer.clear();
  draw(buffer);
  lcd->send(buffer, 0);

  // Given CONST1, we have to draw this again into the same buffer
  // that will now represent the lower half of the display
  // You can see a slight delay when draw is text since it takes 
  // more time to draw
  buffer.set_line_offset(64);
  buffer.clear();
  draw(buffer);
  lcd->send(buffer, 64);
}

void loop() {
  MonoImage chad(128, 128, chad_data);
  lcd->clear();
  lcd->send(chad);
  delay(1000);

  MonoImage arduino(96, 96, arduino_data);
  lcd->clear();
  lcd->send(arduino);
  delay(1000);

  Checker checker(128, 128);
  lcd->send(checker);
  delay(1000);

  do_draw(&text);
  delay(1000);

  do_draw(&graphics);
  delay(1000);
}


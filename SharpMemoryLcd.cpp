#include "SharpMemoryLcd.h"
#include "mono_image.h"
#include <avr/pgmspace.h>

#define ARRAYSIZE 1152

SharpMemoryLcd::SharpMemoryLcd() {
  //constructor(128, 64);
}

SharpMemoryLcd::~SharpMemoryLcd()
{
}

void SharpMemoryLcd::init(int disp, int si, int scs, int sclk) {
  DISP = disp;
  SI = si;
  SCS = scs;
  SCLK = sclk;

  pinMode(DISP, OUTPUT);
  //pinMode(EXTC, OUTPUT);
  //pinMode(EXTM, OUTPUT); //this can be ignored and you can just pull the pin high on your PCB
  pinMode(SI, OUTPUT);
  pinMode(SCS, OUTPUT);
  pinMode(SCLK, OUTPUT);
  //TCCR2B = TCCR2B & 0b11111000 | 0x07; //this sets the EXTC timer on pin 3. you need to change this to move pins

  //digitalWrite(EXTM,HIGH);
  digitalWrite(DISP,HIGH);
  delayMicroseconds(50);
}

void SharpMemoryLcd::clear() {
  int i;

  digitalWrite(SCS,HIGH);

  set_mode(LOW, HIGH);

  for(i = 0; i < 14; i++){ //Send 14 bits of dummy data
    digitalWrite(SI,LOW);
    delayMicroseconds(3);
    post(-2);
  }

  digitalWrite(SCS,LOW);
}

void SharpMemoryLcd::send(const MonoImage &img, int line_offset)
{
  digitalWrite(SCS,HIGH);
  set_mode(HIGH,LOW);

  int end_line = min(img.height()+line_offset, 128);
  for(int y=line_offset; y<end_line; y++) {
    set_line_address(y+1);
    for(int x=0; x<128; x+=8) {
      unsigned char temp = img.byte(x, y-line_offset);
      send_byte(temp);
    }
    send_pixels(8,0);
  }
  delayMicroseconds(1);
  digitalWrite(SCS,LOW);
}

void SharpMemoryLcd::send_interlaced(const MonoImage &img, int line_offset)
{
  digitalWrite(SCS,HIGH);
  set_mode(HIGH,LOW);

  int end_line = min(img.height()+line_offset, 128);
  for(int y=line_offset; y<end_line; y+=2) {
    set_line_address(y+1);
    for(int x=0; x<128; x+=8) {
      unsigned char temp = img.byte(x, y-line_offset);
      send_byte(temp);
    }
    send_pixels(8,0);
  }

  for(int y=line_offset+1; y<end_line; y+=2) {
    set_line_address(y+1);
    for(int x=0; x<128; x+=8) {
      unsigned char temp = img.byte(x, y-line_offset);
      send_byte(temp);
    }
    send_pixels(8,0);
  }
  delayMicroseconds(1);
  digitalWrite(SCS,LOW);
}
void SharpMemoryLcd::set_mode(int M0, int M2) {
  int i;
  digitalWrite(SI,M0);
  post(0);
  digitalWrite(SI,HIGH);
  post(0);
  digitalWrite(SI,M2);
  post(0);
  for(i = 0; i < 5; i++){ //Send 5 bits of dummy data
    digitalWrite(SI,LOW);
    post(0);
  }
}

void SharpMemoryLcd::send_pixels(int num, int state) {
  int i;
  for(i = 0; i < num; i++){
      digitalWrite(SI,state);
      post(0);
  }
}
void SharpMemoryLcd::set_line_address(int line) {
  unsigned char tmp;

  for (int i = 0; i < 8; i++){
    tmp = (line & 1);
    if (tmp == 1){
      digitalWrite(SI,HIGH);
      post(0);
    } else {
    digitalWrite(SI,LOW);
      post(0);
    }
    line = line >> 1;
  }
}


void SharpMemoryLcd::post(int delay_time) {
  digitalWrite(SCLK,HIGH);
  if (delay_time > 0) {
    delay(delay_time);
  }
  if (delay_time < 0) {
    delayMicroseconds(-delay_time);
  }
  digitalWrite(SCLK,LOW);
}

void SharpMemoryLcd::send_byte(char byteToSend) {
  for(int b = 0; b < 8; b++){
    if(byteToSend & 1){
      digitalWrite(SI,HIGH);
      delayMicroseconds(1);
      post(0);
    } else {
      digitalWrite(SI,LOW);
      delayMicroseconds(1);
      post(0);
    }
    byteToSend = byteToSend >> 1;
  }
}

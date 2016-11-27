#ifndef MONO_IMAGE_H
#define MONO_IMAGE_H 1

class MonoImage
{
  public:
    MonoImage(int width, int height, const unsigned char *data);
    virtual ~MonoImage();

    int width() const;
    int height() const;
    virtual bool on(int x, int y) const;
    virtual unsigned char byte(int x, int y) const;

  protected:
    int width_;
    int height_;
    const unsigned char *data_;
    int width_in_bytes_;
};

#endif

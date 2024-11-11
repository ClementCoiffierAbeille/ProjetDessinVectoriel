#ifndef SQUARE_H_
#define SQUARE_H_

#include "../Image/CPixel.h"
#include "../Image/CImage.h"

class Square {
protected:
    int x;
    int y;
    int length;
    CPixel color;
    int transparency;

public:
    Square(int xPos, int yPos, int length, int r, int g, int b, int t);

    virtual void draw(CImage &image);

    int getX() const { return x; }
    int getY() const { return y; }
    int getLength() const { return length; }
    CPixel getColor() const { return color; }
    int getTransparency() const { return transparency; }

    void scale(float factor);
};

#endif /* SQUARE_H_ */
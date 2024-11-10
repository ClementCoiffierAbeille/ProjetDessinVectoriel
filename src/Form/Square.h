#ifndef SQUARE_H_
#define SQUARE_H_

#include "../Image/CPixel.h"   // Include CPixel for color
#include "../Image/CImage.h"   // Include CImage for drawing

class Square {
protected:
    int x;            // X coordinate of the bottom-left corner
    int y;            // Y coordinate of the bottom-left corner
    int length;       // Length of the square (width and height are the same)
    CPixel color;     // Color of the square
    int transparency; // Transparency (0 to 100)

public:
    // Constructor with position, length, color, and transparency
    Square(int xPos, int yPos, int length, int r, int g, int b, int t);

    // Method to draw the square on an image
    virtual void draw(CImage &image);

    // Accesseurs
    int getX() const { return x; }
    int getY() const { return y; }
    int getLength() const { return length; }
    CPixel getColor() const { return color; }
    int getTransparency() const { return transparency; }

    // Method to scale the square by a factor
    void scale(float factor);
};

#endif /* SQUARE_H_ */
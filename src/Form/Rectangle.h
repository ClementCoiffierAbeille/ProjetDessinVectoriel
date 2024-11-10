#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "../Image/CPixel.h"   // Include CPixel for color
#include "../Image/CImage.h"   // Include CImage for drawing

class Rectangle {
private:
    int x;            // X coordinate of the bottom-left corner
    int y;            // Y coordinate of the bottom-left corner
    int length;       // Width of the rectangle
    int height;       // Height of the rectangle
    CPixel color;     // Color of the rectangle
    int transparency; // Transparency (0 to 100)

public:
    // Constructor with position, dimensions, color, and transparency
    Rectangle(int xPos, int yPos, int length, int height, int r, int g, int b, int t);

    // Method to draw the rectangle on an image
    void draw(CImage &image);

    // Déclaration de la méthode scale
    void scale(float factor);
};

#endif /* RECTANGLE_H_ */
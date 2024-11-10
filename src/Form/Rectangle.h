#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "../Image/CPixel.h"   // Include CPixel for color
#include "../Image/CImage.h"   // Include CImage for drawing

class Rectangle {
protected:
    int x, y, length, height;  // Position et dimensions du rectangle
    CPixel color;               // Couleur du rectangle
    int transparency;           // Transparence du rectangle (0-100)

public:
    // Constructeur
    Rectangle(int xPos, int yPos, int l, int h, int r, int g, int b, int t);

    // Méthode de dessin du rectangle
    virtual void draw(CImage &image);

    // Accesseurs
    int getX() const { return x; }
    int getY() const { return y; }
    int getLength() const { return length; }
    int getHeight() const { return height; }
    CPixel getColor() const { return color; }
    int getTransparency() const { return transparency; }

    // Méthode pour mettre à l'échelle le rectangle
    void scale(float factor);
};

#endif // RECTANGLE_H
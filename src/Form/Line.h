#ifndef LIGNE_H_
#define LIGNE_H_

#include "../Image/CPixel.h"   // Include CPixel for color
#include "../Image/CImage.h"    // Include CImage for drawing

class Ligne {
private:
    int x1;           // Start point x-coordinate
    int y1;           // Start point y-coordinate
    int x2;           // End point x-coordinate
    int y2;           // End point y-coordinate
    CPixel color;     // Color of the line
    int transparency; // Transparency of the line (0 to 255)

public:
    // Constructor with coordinates, color, and transparency
    Ligne(int x1Pos, int y1Pos, int x2Pos, int y2Pos, int r, int g, int b, int t);

    // Method to draw the line on an image
    void draw(CImage &image);

    // Déclaration de la méthode scale
    void scale(float factor);
};

#endif /* LIGNE_H_ */
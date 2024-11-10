//
// Created by Clément Coiffier Abeille on 10/11/2024.
//

#ifndef RECTANGLE_S_H
#define RECTANGLE_S_H

#include "Rectangle.h"

class RectangleS : public Rectangle {
private:
    CPixel fillColor;  // Couleur de remplissage pour l'intérieur du rectangle

public:
    // Constructeur
    RectangleS(int xPos, int yPos, int l, int h, int r, int g, int b, int fr, int fg, int fb, int t);

    // Méthode de dessin du rectangleS (contour et remplissage)
    void draw(CImage &image) override;

    // Méthode pour mettre à l'échelle le rectangleS
    void scale(float factor);
};

#endif // RECTANGLE_S_H
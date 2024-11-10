//
// Created by Clément Coiffier Abeille on 10/11/2024.
//
#ifndef SQUARES_H
#define SQUARES_H

#include "Square.h"


class SquareS : public Square {
private:
    CPixel fillColor;  // Couleur de remplissage du carré
public:
    SquareS(int xPos, int yPos, int len, int r, int g, int b, int fr, int fg, int fb, int t);

    // Méthode de dessin du rectangleS (contour et remplissage)
    void draw(CImage &image) override;

    // Méthode pour mettre à l'échelle le rectangleS
    void scale(float factor);
};

#endif // SQUARES_H
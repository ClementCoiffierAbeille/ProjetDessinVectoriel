//
// Created by Clément Coiffier Abeille on 10/11/2024.
//
#ifndef CIRCLES_H_
#define CIRCLES_H_

#include "Circle.h"

class CircleS : public Circle {
private:
    CPixel fillColor;  // Couleur de remplissage du cercle

public:
    // Constructeur prenant en compte la couleur de remplissage en plus des attributs de Circle
    CircleS(int xPos, int yPos, int radius, int r, int g, int b, int fr, int fg, int fb, int t);

    // Méthode pour dessiner le cercle avec remplissage sur une image
    void draw(CImage &image) override;

    // Méthode pour redimensionner le cercle
    void scale(float factor);
};

#endif /* CIRCLES_H_ */

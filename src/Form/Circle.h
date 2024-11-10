#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "../Image/CPixel.h"
#include "../Image/CImage.h"

class Circle {
protected:
    int x;               // Coordonnée X du centre
    int y;               // Coordonnée Y du centre
    int radius;          // Rayon du cercle
    CPixel color;        // Couleur du contour du cercle
    int transparency;    // Transparence du contour du cercle (0 à 255)

public:
    // Constructeur avec position, rayon, couleur du contour et transparence
    Circle(int xPos, int yPos, int radius, int r, int g, int b, int t);

    // Méthode pour dessiner uniquement le contour du cercle sur une image
    virtual void draw(CImage &image);

    // Méthode pour redimensionner le cercle
    void scale(float factor);

    // Getters pour les propriétés du cercle
    int getX() const { return x; }
    int getY() const { return y; }
    int getRadius() const { return radius; }
    int getTransparency() const { return transparency; }
};

#endif /* CIRCLE_H_ */
#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "../Image/CPixel.h"
#include "../Image/CImage.h"

class Circle {
private:
    int x;               // Coordonnée X du centre
    int y;               // Coordonnée Y du centre
    int radius;          // Rayon du cercle
    CPixel color;        // Couleur du contour du cercle
    CPixel fillColor;    // Couleur de remplissage du cercle
    int transparency;    // Transparence du cercle (0 à 255)

public:
    // Constructeur avec position, rayon, couleur du contour, couleur de remplissage et transparence
    Circle(int xPos, int yPos, int radius, int r, int g, int b, int fr, int fg, int fb, int t);

    // Méthode pour dessiner le cercle sur une image
    void draw(CImage &image);

    // Déclaration de la méthode scale
    void scale(float factor);
};

#endif /* CIRCLE_H_ */
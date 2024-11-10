#ifndef CPOINT_H_
#define CPOINT_H_

#include "../Image/CPixel.h"   // Inclusion de CPixel pour la couleur
#include "../Image/CImage.h"   // Inclusion de CImage pour l'affichage

class CPoint {
private:
    int x;           // Position x du point
    int y;           // Position y du point
    CPixel color;    // Couleur du point
    int transparency; // Transparence du point (0 à 255)

public:
    int getX() const { return x; }
    int getY() const { return y; }
    // Constructeur avec position, couleur et transparence
    CPoint(int xPos, int yPos, int r, int g, int b, int t);

    // Méthode pour dessiner le point sur une image
    void draw(CImage &image);
};

#endif /* CPOINT_H_ */
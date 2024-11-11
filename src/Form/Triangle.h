//
// Created by Clément Coiffier Abeille on 10/11/2024.
//
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "../Image/CPixel.h"   // Inclure CPixel pour la couleur
#include "../Image/CImage.h"   // Inclure CImage pour le dessin

class Triangle {
protected:
    int x1, y1;    // Coordonnée du premier sommet
    int x2, y2;    // Coordonnée du deuxième sommet
    int x3, y3;    // Coordonnée du troisième sommet
    CPixel color;  // Couleur du triangle
    int transparency; // Transparence (0 à 100)

public:
    // Constructeur avec les coordonnées des trois sommets, couleur et transparence
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int t);

    // Méthode pour dessiner le triangle sur une image
    virtual void draw(CImage &image);

    // Accesseurs pour obtenir les coordonnées des sommets
    int getX1() const { return x1; }
    int getY1() const { return y1; }
    int getX2() const { return x2; }
    int getY2() const { return y2; }
    int getX3() const { return x3; }
    int getY3() const { return y3; }

    CPixel getColor() const { return color; }
    int getTransparency() const { return transparency; }

    // Méthode pour mettre à l'échelle le triangle avec un facteur
    void scale(float factor);
};

#endif /* TRIANGLE_H_ */
//
// Created by Clément Coiffier Abeille on 10/11/2024.
//

#ifndef TRIANGLE_S_H_
#define TRIANGLE_S_H_

#include "Triangle.h"    // Inclure la classe Triangle pour l'héritage

class TriangleS : public Triangle {
private:
    CPixel fillColor;  // Couleur de remplissage du carré
public:
    // Constructeur de TriangleS qui utilise le constructeur de la classe de base (Triangle)
    TriangleS(int x1, int y1, int x2, int y2, int x3, int y3,
              int r, int g, int b, int fr, int fg, int fb, int t);

    // Méthode pour dessiner le triangle avec contour et remplissage
    void draw(CImage &image) override;

    // Méthode pour mettre à l'échelle le rectangleS
    void scale(float factor);
};

#endif /* TRIANGLE_S_H_ */
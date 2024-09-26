#include "Point.h"
#include <iostream>

// Constructeur de la classe Point
Point::Point(int x, int y, const std::string& color, int transparency)
    : Form(x, y, color, transparency) {}

// Méthode pour dessiner le point
void Point::DrawForm() const {
    std::cout << "Dessiner un point à (" << x << ", " << y 
              << ") avec la couleur " << color 
              << " et une transparence de " << transparency << "%" << std::endl;
}
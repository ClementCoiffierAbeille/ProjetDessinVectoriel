#include "Circle.h"
#include <iostream>

// Constructeur de la classe Circle
Circle::Circle(int x, int y, int radius, const std::string& color, int transparency)
    : Form(x, y, color, transparency), radius(radius) {}

// Méthode pour dessiner le cercle
void Circle::DrawForm() const {
    std::cout << "Dessiner un cercle à (" << x << ", " << y 
              << ") avec un rayon de " << radius 
              << ", couleur " << color 
              << " et une transparence de " << transparency << "%" << std::endl;
}
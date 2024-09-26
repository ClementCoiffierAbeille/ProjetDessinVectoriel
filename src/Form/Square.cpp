#include "Square.h"
#include <iostream>

// Constructeur de la classe Square
Square::Square(int x, int y, int length, const std::string& color, int transparency)
    : Form(x, y, color, transparency), length(length) {}

// Méthode pour dessiner le carré
void Square::DrawForm() const {
    std::cout << "Dessiner un carré à (" << x << ", " << y 
              << ") avec une longueur de " << length 
              << ", couleur " << color 
              << " et une transparence de " << transparency << "%" << std::endl;
}
#include "Rectangle.h"
#include <iostream>

// Constructeur de la classe Rectangle
Rectangle::Rectangle(int x, int y, int length, int height, const std::string& color, int transparency)
    : Form(x, y, color, transparency), length(length), height(height) {}

// Méthode pour dessiner le rectangle
void Rectangle::DrawForm() const {
    std::cout << "Dessiner un rectangle à (" << x << ", " << y 
              << ") avec une longueur de " << length 
              << " et une hauteur de " << height 
              << ", couleur " << color 
              << " et une transparence de " << transparency << "%" << std::endl;
}
#include "Line.h"
#include <iostream>

// Constructeur de la classe Line
Line::Line(int x, int y, int x2, int y2, const std::string& color, int transparency)
    : Form(x, y, color, transparency), x2(x2), y2(y2) {}

// Méthode pour dessiner la ligne
void Line::DrawForm() const {
    std::cout << "Dessiner une ligne de (" << x << ", " << y 
              << ") à (" << x2 << ", " << y2 
              << ") avec la couleur " << color 
              << " et une transparence de " << transparency << "%" << std::endl;
}
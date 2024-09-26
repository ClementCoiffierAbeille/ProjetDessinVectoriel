#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Form.h"

class Rectangle : public Form {
protected:
    int length;  // Longueur du rectangle
    int height;  // Hauteur du rectangle

public:
    // Constructeur de la classe Rectangle
    Rectangle(int x, int y, int length, int height, const std::string& color, int transparency);

    // Implémentation de la méthode DrawForm pour dessiner un rectangle
    void DrawForm() const override;
};

#endif // RECTANGLE_H
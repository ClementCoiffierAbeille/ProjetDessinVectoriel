#ifndef CIRCLE_H
#define CIRCLE_H

#include "Form.h"

class Circle : public Form {
protected:
    int radius;  // Rayon du cercle

public:
    // Constructeur de la classe Circle
    Circle(int x, int y, int radius, const std::string& color, int transparency);

    // Implémentation de la méthode DrawForm pour dessiner un cercle
    void DrawForm() const override;
};

#endif // CIRCLE_H
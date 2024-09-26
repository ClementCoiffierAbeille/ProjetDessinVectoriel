#ifndef POINT_H
#define POINT_H

#include "Form.h"

class Point : public Form {
public:
    // Constructeur de la classe Point
    Point(int x, int y, const std::string& color, int transparency);

    // Implémentation de la méthode DrawForm pour afficher un point
    void DrawForm() const override;
};

#endif // POINT_H
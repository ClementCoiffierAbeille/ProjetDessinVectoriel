#ifndef LINE_H
#define LINE_H

#include "Form.h"

class Line : public Form {
private:
    int x2, y2;  // Coordonnées de fin de la ligne

public:
    // Constructeur de la classe Line
    Line(int x, int y, int x2, int y2, const std::string& color, int transparency);

    // Implémentation de la méthode DrawForm pour afficher une ligne
    void DrawForm() const override;
};

#endif // LINE_H
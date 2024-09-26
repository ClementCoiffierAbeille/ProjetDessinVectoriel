#ifndef FORM_H
#define FORM_H

#include <string>

class Form {
protected:
    int x, y;  // Position
    std::string color;  // Couleur en tant que string
    int transparency;  // Transparence (0-100%)

public:
    // Constructeur de la classe Form
    Form(int x, int y, const std::string& color, int transparency);

    // Méthode virtuelle pour dessiner la forme (sera redéfinie par les classes dérivées)
    virtual void DrawForm() const = 0;

    // Destructeur virtuel
    virtual ~Form() {}
};

#endif // FORM_H
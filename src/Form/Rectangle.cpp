#include "Rectangle.h"

Rectangle::Rectangle(int xPos, int yPos, int l, int h, int r, int g, int b, int t)
        : x(xPos), y(yPos), length(l), height(h), color(r, g, b), transparency(t) {
}

void Rectangle::draw(CImage &image) {
    // Conversion de la transparence de 0-100% en 0-255
    int transparency255 = static_cast<int>(transparency * 2.55);

    // Récupérer la hauteur de l'image
    int imageHeight = image.size();

    // Inverser l'axe Y pour le rectangle
    int invertedY = imageHeight - y - height;  // Calcul de la position inversée du bas du rectangle

    for (int i = x; i < x + length; i++) {
        for (int j = invertedY; j < invertedY + height; j++) {
            CPixel* pixel = image.getPixel(i, j);
            if (pixel) {
                if (transparency == 100) { // Pas de transparence
                    pixel->RGB(color.Red(), color.Green(), color.Blue());
                } else {
                    // Mélange de la couleur avec l'arrière-plan en fonction de la transparence
                    int newRed = (pixel->Red() * (255 - transparency255) + color.Red() * transparency255) / 255;
                    int newGreen = (pixel->Green() * (255 - transparency255) + color.Green() * transparency255) / 255;
                    int newBlue = (pixel->Blue() * (255 - transparency255) + color.Blue() * transparency255) / 255;
                    pixel->RGB(newRed, newGreen, newBlue);
                }
            } else {
                std::cout << "Rectangle::draw => Position out of bounds (" << i << ", " << j << ")" << std::endl;
            }
        }
    }
}

// Définition de la méthode scale
void Rectangle::scale(float factor) {
    // Modifie la position du rectangle et ses dimensions en fonction du facteur d'échelle
    x = static_cast<int>(x * factor);
    y = static_cast<int>(y * factor);
    length = static_cast<int>(length * factor);
    height = static_cast<int>(height * factor);
}
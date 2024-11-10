#include "Square.h"
#include <iostream>

Square::Square(int xPos, int yPos, int len, int r, int g, int b, int t)
        : x(xPos), y(yPos), length(len), color(r, g, b), transparency(t) {}

void Square::draw(CImage &image) {
    // Conversion de la transparence de 0-100% en 0-255
    int transparency255 = static_cast<int>(transparency * 2.55);

    // Récupérer la hauteur de l'image
    int imageHeight = image.size();

    // Inverser l'axe Y pour le carré
    int invertedY = imageHeight - y - length;  // Calcul de la position inversée du bas du carré

    // Dessiner le contour du carré
    for (int i = x; i < x + length; i++) {
        for (int j = invertedY; j < invertedY + length; j++) {  // Utilisez 'length' pour la hauteur également
            if (i == x || i == x + length - 1 || j == invertedY || j == invertedY + length - 1) {
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
                }
            }
        }
    }
}

// Définition de la méthode scale
void Square::scale(float factor) {
    // Modifie la position du carré et sa dimension (longueur) en fonction du facteur d'échelle
    x = static_cast<int>(x * factor);
    y = static_cast<int>(y * factor);
    length = static_cast<int>(length * factor);  // On modifie uniquement 'length', pas de 'height' à ajuster
}
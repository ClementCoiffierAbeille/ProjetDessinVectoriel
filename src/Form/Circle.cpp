#include "Circle.h"
#include <cmath>
#include <iostream>

Circle::Circle(int xPos, int yPos, int radius, int r, int g, int b, int t)
        : x(xPos), y(yPos), radius(radius), color(r, g, b), transparency(t) {}

void Circle::draw(CImage &image) {
    int imageHeight = image.size();  // Hauteur de l'image
    int imageWidth = 0;

    // On obtient la largeur à partir de la première ligne, si elle existe
    if (imageHeight > 0) {
        CLigne* firstLine = image.getLigne(0);
        if (firstLine != nullptr) {
            imageWidth = firstLine->size();  // Largeur de l'image
        }
    }

    // Conversion de la transparence de 0-100% en 0-255
    int transparency255 = static_cast<int>(transparency * 2.55);

    // Contour du cercle
    for (int dy = -radius; dy <= radius; dy++) {
        int dx = static_cast<int>(sqrt(radius * radius - dy * dy));
        int px1 = x + dx;
        int px2 = x - dx;
        int py = y + dy;

        // Inverser Y pour correspondre à la disposition de l'image
        py = imageHeight - py - 1;

        // Vérification des limites pour le contour
        if (px1 >= 0 && px1 < imageWidth && py >= 0 && py < imageHeight) {
            CPixel* pixel1 = image.getPixel(px1, py);
            if (pixel1) {
                int newRed = (pixel1->Red() * (255 - transparency255) + color.Red() * transparency255) / 255;
                int newGreen = (pixel1->Green() * (255 - transparency255) + color.Green() * transparency255) / 255;
                int newBlue = (pixel1->Blue() * (255 - transparency255) + color.Blue() * transparency255) / 255;
                pixel1->RGB(newRed, newGreen, newBlue);
            }
        }

        if (px2 >= 0 && px2 < imageWidth && py >= 0 && py < imageHeight) {
            CPixel* pixel2 = image.getPixel(px2, py);
            if (pixel2) {
                int newRed = (pixel2->Red() * (255 - transparency255) + color.Red() * transparency255) / 255;
                int newGreen = (pixel2->Green() * (255 - transparency255) + color.Green() * transparency255) / 255;
                int newBlue = (pixel2->Blue() * (255 - transparency255) + color.Blue() * transparency255) / 255;
                pixel2->RGB(newRed, newGreen, newBlue);
            }
        }
    }
}

// Ajout de la méthode scale
void Circle::scale(float factor) {
    // Modifie les coordonnées et le rayon en fonction du facteur d'échelle
    x = static_cast<int>(x * factor);
    y = static_cast<int>(y * factor);
    radius = static_cast<int>(radius * factor);
}
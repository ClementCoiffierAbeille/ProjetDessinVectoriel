#include "Circle.h"
#include <cmath>
#include <iostream>

Circle::Circle(int xPos, int yPos, int radius, int r, int g, int b, int fr, int fg, int fb, int t)
        : x(xPos), y(yPos), radius(radius), color(r, g, b), fillColor(fr, fg, fb), transparency(t) {}

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

    // Algorithme de tracé de cercle pour le remplissage et le contour
    for (int dy = -radius; dy <= radius; dy++) {
        int dx = static_cast<int>(sqrt(radius * radius - dy * dy));

        // Remplissage
        for (int i = -dx; i <= dx; i++) {
            int px = x + i;
            int py = y + dy;

            // Inverser Y : l'image est inversée sur l'axe Y
            py = imageHeight - py - 1;

            // Vérification des limites
            if (px >= 0 && px < imageWidth && py >= 0 && py < imageHeight) {
                CPixel* pixel = image.getPixel(px, py);
                if (pixel) {
                    int newRed, newGreen, newBlue;

                    // Appliquer la couleur de remplissage en fonction de la transparence
                    if (transparency == 100) {
                        newRed = fillColor.Red();
                        newGreen = fillColor.Green();
                        newBlue = fillColor.Blue();
                    } else {
                        // Mélange de couleur de remplissage avec l'arrière-plan
                        newRed = (pixel->Red() * (255 - transparency255) + fillColor.Red() * transparency255) / 255;
                        newGreen = (pixel->Green() * (255 - transparency255) + fillColor.Green() * transparency255) / 255;
                        newBlue = (pixel->Blue() * (255 - transparency255) + fillColor.Blue() * transparency255) / 255;
                    }
                    pixel->RGB(newRed, newGreen, newBlue);
                }
            } else {
                std::cout << "Circle::draw => Position out of bounds (" << px << ", " << py << ")" << std::endl;
            }
        }
    }

    // Contour
    for (int dy = -radius; dy <= radius; dy++) {
        int dx = static_cast<int>(sqrt(radius * radius - dy * dy));
        int px1 = x + dx;
        int px2 = x - dx;
        int py = y + dy;

        // Inverser Y pour les contours
        py = imageHeight - py - 1;

        // Vérification des limites pour le contour
        if (px1 >= 0 && px1 < imageWidth && py >= 0 && py < imageHeight) {
            CPixel* pixel1 = image.getPixel(px1, py);
            if (pixel1) {
                pixel1->RGB(color.Red(), color.Green(), color.Blue());
            }
        }

        if (px2 >= 0 && px2 < imageWidth && py >= 0 && py < imageHeight) {
            CPixel* pixel2 = image.getPixel(px2, py);
            if (pixel2) {
                pixel2->RGB(color.Red(), color.Green(), color.Blue());
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
#include "Line.h"
#include <cmath>

Ligne::Ligne(int x1Pos, int y1Pos, int x2Pos, int y2Pos, int r, int g, int b, int t)
        : x1(x1Pos), y1(y1Pos), x2(x2Pos), y2(y2Pos), color(r, g, b), transparency(t) {
}

void Ligne::draw(CImage &image) {
    // Conversion de la transparence de 0-100% en 0-255
    int transparency255 = static_cast<int>(transparency * 2.55);

    // Inverser l'axe Y (en fonction de la hauteur de l'image)
    int imageHeight = image.size();
    y1 = imageHeight - y1;
    y2 = imageHeight - y2;

    // Utilisation de l'algorithme de Bresenham pour dessiner la ligne
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        CPixel* pixel = image.getPixel(x1, y1);
        if (pixel) {
            // Appliquer la couleur et la transparence
            if (transparency == 100) {
                pixel->RGB(color.Red(), color.Green(), color.Blue());
            } else {
                // Mélange de la couleur avec l'arrière-plan en fonction de la transparence
                int newRed = (pixel->Red() * (255 - transparency255) + color.Red() * transparency255) / 255;
                int newGreen = (pixel->Green() * (255 - transparency255) + color.Green() * transparency255) / 255;
                int newBlue = (pixel->Blue() * (255 - transparency255) + color.Blue() * transparency255) / 255;
                pixel->RGB(newRed, newGreen, newBlue);
            }
        }

        if (x1 == x2 && y1 == y2) break;
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Définition de la méthode scale
void Ligne::scale(float factor) {

    x1 = static_cast<int>(x1 * factor);
    y1 = static_cast<int>(y1 * factor);
    x2 = static_cast<int>(x2 * factor);
    y2 = static_cast<int>(y2 * factor);
}
#include "Triangle.h"
#include <iostream>
#include <cmath> // Pour les calculs géométriques (par exemple, la distance)

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int t)
        : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), color(r, g, b), transparency(t) {}

void Triangle::draw(CImage &image) {
    // Conversion de la transparence de 0-100% en 0-255
    int transparency255 = static_cast<int>(transparency * 2.55);

    // Récupérer la hauteur de l'image
    int imageHeight = image.size();

    // Inverser l'axe Y pour le triangle (si nécessaire)
    int invertedY1 = imageHeight - y1;
    int invertedY2 = imageHeight - y2;
    int invertedY3 = imageHeight - y3;

    // Fonction pour dessiner une ligne entre deux points
    auto drawLine = [&](int x1, int y1, int x2, int y2) {
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = x1 < x2 ? 1 : -1;
        int sy = y1 < y2 ? 1 : -1;
        int err = dx - dy;

        while (true) {
            CPixel* pixel = image.getPixel(x1, y1);
            if (pixel != nullptr) {
                int newRed = (pixel->Red() * (255 - transparency255) + color.Red() * transparency255) / 255;
                int newGreen = (pixel->Green() * (255 - transparency255) + color.Green() * transparency255) / 255;
                int newBlue = (pixel->Blue() * (255 - transparency255) + color.Blue() * transparency255) / 255;
                pixel->RGB(newRed, newGreen, newBlue);
            }

            if (x1 == x2 && y1 == y2) break;
            int e2 = err * 2;
            if (e2 > -dy) { err -= dy; x1 += sx; }
            if (e2 < dx) { err += dx; y1 += sy; }
        }
    };

    // Dessiner les trois côtés du triangle
    drawLine(x1, invertedY1, x2, invertedY2);
    drawLine(x2, invertedY2, x3, invertedY3);
    drawLine(x3, invertedY3, x1, invertedY1);
}

// Définition de la méthode scale
void Triangle::scale(float factor) {
    // Modifie la position du triangle et ses dimensions (coordonnées des sommets) en fonction du facteur d'échelle
    x1 = static_cast<int>(x1 * factor);
    y1 = static_cast<int>(y1 * factor);
    x2 = static_cast<int>(x2 * factor);
    y2 = static_cast<int>(y2 * factor);
    x3 = static_cast<int>(x3 * factor);
    y3 = static_cast<int>(y3 * factor);
}
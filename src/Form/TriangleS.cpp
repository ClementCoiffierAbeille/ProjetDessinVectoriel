// TriangleS.cpp
#include "TriangleS.h"
#include <cmath>

TriangleS::TriangleS(int x1, int y1, int x2, int y2, int x3, int y3,
                     int r, int g, int b, int fr, int fg, int fb,  int t)
        : Triangle(x1, y1, x2, y2, x3, y3, r, g, b, t), fillColor(fr, fg, fb) {}

void TriangleS::draw(CImage &image) {
    int transparency255 = static_cast<int>(transparency * 2.55);
    int imageHeight = image.size();

    int invertedY1 = imageHeight - y1;
    int invertedY2 = imageHeight - y2;
    int invertedY3 = imageHeight - y3;

    // Fonction de dessin de ligne
    auto drawLine = [&](int x1, int y1, int x2, int y2) {

    };

    // Dessiner les trois côtés du triangle
    drawLine(x1, invertedY1, x2, invertedY2);
    drawLine(x2, invertedY2, x3, invertedY3);
    drawLine(x3, invertedY3, x1, invertedY1);

    // Remplir l'intérieur du triangle
    if (invertedY1 > invertedY2) std::swap(x1, x2), std::swap(invertedY1, invertedY2);
    if (invertedY2 > invertedY3) std::swap(x2, x3), std::swap(invertedY2, invertedY3);
    if (invertedY1 > invertedY2) std::swap(x1, x2), std::swap(invertedY1, invertedY2);

    for (int y = invertedY1; y <= invertedY2; y++) {
        int startX = x1 + (x2 - x1) * (y - invertedY1) / (invertedY2 - invertedY1);
        int endX = x1 + (x3 - x1) * (y - invertedY1) / (invertedY3 - invertedY1);

        if (startX > endX) std::swap(startX, endX);

        for (int x = startX; x <= endX; x++) {
            CPixel* pixel = image.getPixel(x, y);
            if (pixel) {
                int newRed = (pixel->Red() * (255 - transparency255) + fillColor.Red() * transparency255) / 255;
                int newGreen = (pixel->Green() * (255 - transparency255) + fillColor.Green() * transparency255) / 255;
                int newBlue = (pixel->Blue() * (255 - transparency255) + fillColor.Blue() * transparency255) / 255;
                pixel->RGB(newRed, newGreen, newBlue);
            }
        }
    }

    for (int y = invertedY2 + 1; y <= invertedY3; y++) {
        int startX = x2 + (x3 - x2) * (y - invertedY2) / (invertedY3 - invertedY2);
        int endX = x1 + (x3 - x1) * (y - invertedY1) / (invertedY3 - invertedY1);

        if (startX > endX) std::swap(startX, endX);

        for (int x = startX; x <= endX; x++) {
            CPixel* pixel = image.getPixel(x, y);
            if (pixel) {
                int newRed = (pixel->Red() * (255 - transparency255) + fillColor.Red() * transparency255) / 255;
                int newGreen = (pixel->Green() * (255 - transparency255) + fillColor.Green() * transparency255) / 255;
                int newBlue = (pixel->Blue() * (255 - transparency255) + fillColor.Blue() * transparency255) / 255;
                pixel->RGB(newRed, newGreen, newBlue);
            }
        }
    }
}

// Définition de la méthode scale
void TriangleS::scale(float factor) {
    // Redimensionner le triangle en multipliant les coordonnées par le facteur
    x1 = static_cast<int>(x1 * factor);
    y1 = static_cast<int>(y1 * factor);
    x2 = static_cast<int>(x2 * factor);
    y2 = static_cast<int>(y2 * factor);
    x3 = static_cast<int>(x3 * factor);
    y3 = static_cast<int>(y3 * factor);
}
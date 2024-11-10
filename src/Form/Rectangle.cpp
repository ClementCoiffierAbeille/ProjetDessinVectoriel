#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(int xPos, int yPos, int l, int h, int r, int g, int b, int t)
        : x(xPos), y(yPos), length(l), height(h), color(r, g, b), transparency(t) {
}

void Rectangle::draw(CImage &image) {
    int transparency255 = static_cast<int>(transparency * 2.55);
    int imageHeight = image.size();
    int invertedY = imageHeight - y - height;

    // Dessiner le contour (lignes horizontales en haut et en bas)
    for (int i = x; i < x + length; i++) {
        // Ligne du haut
        CPixel* topPixel = image.getPixel(i, invertedY);
        if (topPixel) {
            int newRed = (topPixel->Red() * (255 - transparency255) + color.Red() * transparency255) / 255;
            int newGreen = (topPixel->Green() * (255 - transparency255) + color.Green() * transparency255) / 255;
            int newBlue = (topPixel->Blue() * (255 - transparency255) + color.Blue() * transparency255) / 255;
            topPixel->RGB(newRed, newGreen, newBlue);
        }

        // Ligne du bas
        CPixel* bottomPixel = image.getPixel(i, invertedY + height - 1);
        if (bottomPixel) {
            int newRed = (bottomPixel->Red() * (255 - transparency255) + color.Red() * transparency255) / 255;
            int newGreen = (bottomPixel->Green() * (255 - transparency255) + color.Green() * transparency255) / 255;
            int newBlue = (bottomPixel->Blue() * (255 - transparency255) + color.Blue() * transparency255) / 255;
            bottomPixel->RGB(newRed, newGreen, newBlue);
        }
    }

    // Dessiner les côtés gauche et droit
    for (int j = invertedY; j < invertedY + height; j++) {
        // Côté gauche
        CPixel* leftPixel = image.getPixel(x, j);
        if (leftPixel) {
            int newRed = (leftPixel->Red() * (255 - transparency255) + color.Red() * transparency255) / 255;
            int newGreen = (leftPixel->Green() * (255 - transparency255) + color.Green() * transparency255) / 255;
            int newBlue = (leftPixel->Blue() * (255 - transparency255) + color.Blue() * transparency255) / 255;
            leftPixel->RGB(newRed, newGreen, newBlue);
        }

        // Côté droit
        CPixel* rightPixel = image.getPixel(x + length - 1, j);
        if (rightPixel) {
            int newRed = (rightPixel->Red() * (255 - transparency255) + color.Red() * transparency255) / 255;
            int newGreen = (rightPixel->Green() * (255 - transparency255) + color.Green() * transparency255) / 255;
            int newBlue = (rightPixel->Blue() * (255 - transparency255) + color.Blue() * transparency255) / 255;
            rightPixel->RGB(newRed, newGreen, newBlue);
        }
    }
}

void Rectangle::scale(float factor) {
    x = static_cast<int>(x * factor);
    y = static_cast<int>(y * factor);
    length = static_cast<int>(length * factor);
    height = static_cast<int>(height * factor);
}
#include "Circle.h"
#include <cmath>


Circle::Circle(int xPos, int yPos, int radius, int r, int g, int b, int t)
        : x(xPos), y(yPos), radius(radius), color(r, g, b), transparency(t) {}

void Circle::draw(CImage &image) {
    int imageHeight = image.size();
    int imageWidth = 0;


    if (imageHeight > 0) {
        CLigne* firstLine = image.getLigne(0);
        if (firstLine != nullptr) {
            imageWidth = firstLine->size();
        }
    }

    // Conversion de la transparence de 0-100% en 0-255
    int transparency255 = static_cast<int>(transparency * 2.55);

    // Contour du cercle
    for (int angle = 0; angle < 360; angle++) {
        float rad = angle * (M_PI / 180.0);
        int px = getX() + static_cast<int>(getRadius() * cos(rad));
        int py = getY() + static_cast<int>(getRadius() * sin(rad));
        py = imageHeight - py - 1;

        if (px >= 0 && px < imageWidth && py >= 0 && py < imageHeight) {
            CPixel* pixel = image.getPixel(px, py);
            if (pixel) {
                int newRed = (pixel->Red() * (255 - transparency255) + color.Red() * transparency255) / 255;
                int newGreen = (pixel->Green() * (255 - transparency255) + color.Green() * transparency255) / 255;
                int newBlue = (pixel->Blue() * (255 - transparency255) + color.Blue() * transparency255) / 255;
                pixel->RGB(newRed, newGreen, newBlue);
            }
        }
    }
}

// Ajout de la méthode scale
void Circle::scale(float factor) {

    x = static_cast<int>(x * factor);
    y = static_cast<int>(y * factor);
    radius = static_cast<int>(radius * factor);
}
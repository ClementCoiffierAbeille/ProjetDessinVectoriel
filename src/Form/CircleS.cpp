#include "CircleS.h"
#include <cmath>
#include <iostream>

CircleS::CircleS(int xPos, int yPos, int radius, int r, int g, int b, int fr, int fg, int fb, int t)
        : Circle(xPos, yPos, radius, r, g, b, t), fillColor(fr, fg, fb) {}

void CircleS::draw(CImage &image) {
    int imageHeight = image.size();
    int imageWidth = 0;

    if (imageHeight > 0) {
        CLigne* firstLine = image.getLigne(0);
        if (firstLine != nullptr) {
            imageWidth = firstLine->size();
        }
    }

    int transparency255 = static_cast<int>(getTransparency() * 2.55);

    // Remplissage intérieur du cercle
    for (int dy = -getRadius(); dy <= getRadius(); dy++) {
        int dx = static_cast<int>(sqrt(getRadius() * getRadius() - dy * dy));
        for (int i = -dx; i <= dx; i++) {
            int px = getX() + i;
            int py = getY() + dy;

            py = imageHeight - py - 1;

            if (px >= 0 && px < imageWidth && py >= 0 && py < imageHeight) {
                CPixel* pixel = image.getPixel(px, py);
                if (pixel) {
                    int newRed = (pixel->Red() * (255 - transparency255) + fillColor.Red() * transparency255) / 255;
                    int newGreen = (pixel->Green() * (255 - transparency255) + fillColor.Green() * transparency255) / 255;
                    int newBlue = (pixel->Blue() * (255 - transparency255) + fillColor.Blue() * transparency255) / 255;
                    pixel->RGB(newRed, newGreen, newBlue);
                }
            }
        }
    }

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

void CircleS::scale(float factor) {
    x = static_cast<int>(x * factor);
    y = static_cast<int>(y * factor);
    radius = static_cast<int>(radius * factor);
}
#include "Point.h"

CPoint::CPoint(int xPos, int yPos, int r, int g, int b, int t)
        : x(xPos), y(yPos), color(r, g, b), transparency(t) {
}

void CPoint::draw(CImage &image) {
    // Conversion de la transparence de 0-100% en 0-255
    int transparency255 = static_cast<int>(transparency * 2.55);

    CPixel* pixel = image.getPixel(x, y);
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
    } else {
        cout << "CPoint::draw => Position out of bounds (" << x << ", " << y << ")" << endl;
    }
}
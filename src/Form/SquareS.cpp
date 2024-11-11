#include "SquareS.h"

SquareS::SquareS(int xPos, int yPos, int len, int r, int g, int b, int fr, int fg, int fb, int t)
        : Square(xPos, yPos, len, r, g, b, t), fillColor(fr, fg, fb) {}

void SquareS::draw(CImage &image) {
    // Conversion de la transparence de 0-100% en 0-255
    int transparency255 = static_cast<int>(getTransparency() * 2.55);

    // Récupérer la hauteur de l'image
    int imageHeight = image.size();

    // Inverser l'axe Y pour le carré
    int invertedY = imageHeight - getY() - getLength();  // Calcul de la position inversée du bas du carré

    // Dessiner le contour du carré
    for (int i = getX(); i < getX() + getLength(); i++) {
        for (int j = invertedY; j < invertedY + getLength(); j++) {  // Utilisez 'length' pour la hauteur également
            if (i == getX() || i == getX() + getLength() - 1 || j == invertedY || j == invertedY + getLength() - 1) {
                CPixel* pixel = image.getPixel(i, j);
                if (pixel) {
                    if (getTransparency() == 100) { // Pas de transparence
                        pixel->RGB(getColor().Red(), getColor().Green(), getColor().Blue());
                    } else {
                        // Mélange de la couleur avec l'arrière-plan en fonction de la transparence
                        int newRed = (pixel->Red() * (255 - transparency255) + getColor().Red() * transparency255) / 255;
                        int newGreen = (pixel->Green() * (255 - transparency255) + getColor().Green() * transparency255) / 255;
                        int newBlue = (pixel->Blue() * (255 - transparency255) + getColor().Blue() * transparency255) / 255;
                        pixel->RGB(newRed, newGreen, newBlue);
                    }
                }
            }
        }
    }

    // Remplir l'intérieur du carré
    for (int i = getX() + 1; i < getX() + getLength() - 1; i++) {
        for (int j = invertedY + 1; j < invertedY + getLength() - 1; j++) {
            CPixel* pixel = image.getPixel(i, j);
            if (pixel) {
                if (getTransparency() == 100) {
                    pixel->RGB(fillColor.Red(), fillColor.Green(), fillColor.Blue());
                } else {
                    // Mélange de la couleur de remplissage avec l'arrière-plan en fonction de la transparence
                    int newRed = (pixel->Red() * (255 - transparency255) + fillColor.Red() * transparency255) / 255;
                    int newGreen = (pixel->Green() * (255 - transparency255) + fillColor.Green() * transparency255) / 255;
                    int newBlue = (pixel->Blue() * (255 - transparency255) + fillColor.Blue() * transparency255) / 255;
                    pixel->RGB(newRed, newGreen, newBlue);
                }
            }
        }
    }
}

void SquareS::scale(float factor) {
    // Modifie la position du carré et sa dimension (longueur) en fonction du facteur d'échelle
    x = static_cast<int>(x * factor);
    y = static_cast<int>(y * factor);
    length = static_cast<int>(length * factor);
}
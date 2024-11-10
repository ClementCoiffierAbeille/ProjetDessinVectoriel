#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "./Format/CBitmap.h"
#include "./Form/Point.h"
#include "./Form/Line.h"
#include "./Form/Rectangle.h"
#include "./Form/Circle.h"
#include "./Form/Square.h"

using namespace std;

// Dictionnaire des couleurs
unordered_map<string, tuple<int, int, int>> colors = {
        {"BLUE", {0, 0, 255}},
        {"RED", {255, 0, 0}},
        {"GREEN", {0, 255, 0}},
        {"YELLOW", {255, 255, 0}},
        {"PURPLE", {128, 0, 128}},
        {"BROWN", {165, 42, 42}},
        {"BLACK", {0, 0, 0}},
        {"WHITE", {255, 255, 255}},
        {"GREY", {128, 128, 128}},
        {"GOLD", {255, 215, 0}},
        {"PINK", {234, 115, 128}}
};

struct Drawable {
    int order;
    Drawable(int ord) : order(ord) {}
    virtual void draw(CImage& img) = 0;
    virtual ~Drawable() = default;
};

struct DrawableCircle : public Drawable {
    Circle circle;
    DrawableCircle(int order, const Circle& circle) : Drawable(order), circle(circle) {}
    void draw(CImage& img) override {
        circle.draw(img);
    }
};

struct DrawableLine : public Drawable {
    Ligne line;
    DrawableLine(int order, const Ligne& line) : Drawable(order), line(line) {}
    void draw(CImage& img) override {
        line.draw(img);
    }
};

struct DrawableRectangle : public Drawable {
    Rectangle rectangle;
    DrawableRectangle(int order, const Rectangle& rectangle) : Drawable(order), rectangle(rectangle) {}
    void draw(CImage& img) override {
        rectangle.draw(img);
    }
};

struct DrawableSquare : public Drawable {
    Square square;
    DrawableSquare(int order, const Square& square) : Drawable(order), square(square) {}
    void draw(CImage& img) override {
        square.draw(img);
    }
};

void drawShapesInOrder(vector<Drawable*>& shapes, CImage& img, float scaleFactor) {
    // Tri des formes en fonction de l'ordre
    sort(shapes.begin(), shapes.end(), [](Drawable* a, Drawable* b) {
        return a->order < b->order;
    });

    // Appliquer l'échelle à chaque forme avant de la dessiner
    for (Drawable* shape : shapes) {
        if (auto drawableCircle = dynamic_cast<DrawableCircle*>(shape)) {
            drawableCircle->circle.scale(scaleFactor);
        } else if (auto drawableLine = dynamic_cast<DrawableLine*>(shape)) {
            drawableLine->line.scale(scaleFactor);
        } else if (auto drawableRectangle = dynamic_cast<DrawableRectangle*>(shape)) {
            drawableRectangle->rectangle.scale(scaleFactor);
        } else if (auto drawableSquare = dynamic_cast<DrawableSquare*>(shape)) {
            drawableSquare->square.scale(scaleFactor);
        }
        shape->draw(img);
    }
}

void parseFileAndLoadShapes(const string& filename, vector<Drawable*>& shapes) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string shapeType;
        getline(iss, shapeType, ':');

        if (shapeType == "CERCLE" || shapeType == "CERCLES") {
            int x, y, radius, transparency, order;
            string colorStr, fillColorStr;
            char comma;

            if (shapeType == "CERCLE") {
                // For CERCLE, only one color and no fill color
                if (iss >> x >> comma >> y >> comma >> radius >> comma
                    && getline(iss, colorStr, ',')
                    && (iss >> transparency >> comma >> order)) {
                    auto [r, g, b] = colors[colorStr];
                    shapes.push_back(new DrawableCircle(order, Circle(x, y, radius, r, g, b, r, g, b, transparency)));
                } else {
                    cerr << "Erreur de lecture de la ligne CERCLE: " << line << endl;
                }
            } else if (shapeType == "CERCLES") {
                // For CERCLES, there are two colors (border and fill)
                if (iss >> x >> comma >> y >> comma >> radius >> comma
                    && getline(iss, colorStr, ',')
                    && getline(iss, fillColorStr, ',')
                    && (iss >> transparency >> comma >> order)) {
                    auto [r, g, b] = colors[colorStr];
                    auto [fr, fg, fb] = colors[fillColorStr];
                    shapes.push_back(
                            new DrawableCircle(order, Circle(x, y, radius, r, g, b, fr, fg, fb, transparency)));
                } else {
                    cerr << "Erreur de lecture de la ligne CERCLES: " << line << endl;
                }
            }
        } else if (shapeType == "LIGNE") {
            int x1, y1, x2, y2, transparency, order;
            string colorStr;
            char comma;

            if (iss >> x1 >> comma >> y1 >> comma >> x2 >> comma >> y2 >> comma
                && getline(iss, colorStr, ',')
                && (iss >> transparency >> comma >> order)) {
                auto [r, g, b] = colors[colorStr];
                shapes.push_back(new DrawableLine(order, Ligne(x1, y1, x2, y2, r, g, b, transparency)));
            } else {
                cerr << "Erreur de lecture de la ligne LIGNE: " << line << endl;
            }
        } else if (shapeType == "RECTANGLE" || shapeType == "RECTANGLES") {
            int x, y, width, height, transparency, order;
            string colorStr, fillColorStr;
            char comma;

            if (shapeType == "RECTANGLE") {
                // For RECTANGLE, only one color and no fill color
                if (iss >> x >> comma >> y >> comma >> width >> comma >> height >> comma
                    && getline(iss, colorStr, ',')
                    && (iss >> transparency >> comma >> order)) {
                    auto [r, g, b] = colors[colorStr];
                    shapes.push_back(
                            new DrawableRectangle(order, Rectangle(x, y, width, height, r, g, b, transparency)));
                } else {
                    cerr << "Erreur de lecture de la ligne RECTANGLE: " << line << endl;
                }
            } else if (shapeType == "RECTANGLES") {
                // For RECTANGLES, there are two colors (border and fill)
                if (iss >> x >> comma >> y >> comma >> width >> comma >> height >> comma
                    && getline(iss, colorStr, ',')
                    && getline(iss, fillColorStr, ',')
                    && (iss >> transparency >> comma >> order)) {
                    auto [r, g, b] = colors[colorStr];
                    auto [fr, fg, fb] = colors[fillColorStr];
                    shapes.push_back(
                            new DrawableRectangle(order, Rectangle(x, y, width, height, r, g, b, transparency)));
                } else {
                    cerr << "Erreur de lecture de la ligne RECTANGLES: " << line << endl;
                }
            }
        } else if (shapeType == "SQUARE" || shapeType == "SQUARES") {
            int x, y, side, transparency, order;
            string colorStr, fillColorStr;
            char comma;

            if (shapeType == "SQUARE") {
                // For SQUARE, only one color and no fill color
                if (iss >> x >> comma >> y >> comma >> side >> comma
                    && getline(iss, colorStr, ',')
                    && (iss >> transparency >> comma >> order)) {
                    auto [r, g, b] = colors[colorStr];
                    shapes.push_back(new DrawableSquare(order, Square(x, y, side, r, g, b, transparency)));
                } else {
                    cerr << "Erreur de lecture de la ligne SQUARE: " << line << endl;
                }
            } else if (shapeType == "SQUARES") {
                // For SQUARES, there are two colors (border and fill)
                if (iss >> x >> comma >> y >> comma >> side >> comma
                    && getline(iss, colorStr, ',')
                    && getline(iss, fillColorStr, ',')
                    && (iss >> transparency >> comma >> order)) {
                    auto [r, g, b] = colors[colorStr];
                    auto [fr, fg, fb] = colors[fillColorStr];
                    shapes.push_back(new DrawableSquare(order, Square(x, y, side, r, g, b, transparency)));
                } else {
                    cerr << "Erreur de lecture de la ligne SQUARES: " << line << endl;
                }
            }
        }
    }
}
int main(int argc, char* argv[]) {
    cout << "(II) P_Bitmap execution start (" << __DATE__ << " - " << __TIME__ << ")" << endl;

    CBitmap* image = new CBitmap();
    string outputFilename = "Sortie.bmp";

    // Appliquer le facteur d'échelle pour redimensionner l'image
    float scaleFactor = 2.0;
    int newWidth = static_cast<int>(304 * scaleFactor);
    int newHeight = static_cast<int>(304 * scaleFactor);

    // Créer l'image avec la nouvelle taille
    CImage* img = new CImage(newWidth, newHeight);

    // Remplir l'image avec du blanc
    for (int i = 0; i < newWidth; i++) {
        for (int j = 0; j < newHeight; j++) {
            CPixel* p = img->getPixel(i, j);
            p->RGB(255, 255, 255); // Set pixel to white
        }
    }

    vector<Drawable*> shapes;
    parseFileAndLoadShapes("Entree.vec", shapes);

    // Appliquer le facteur d'échelle aux formes
    drawShapesInOrder(shapes, *img, scaleFactor);

    // Sauvegarder l'image sous un fichier BMP
    image->setImage(img);
    image->SaveBMP(outputFilename);

    // Nettoyage de la mémoire
    for (Drawable* shape : shapes) {
        delete shape;
    }
    delete image;
    delete img;

    return 0;
}
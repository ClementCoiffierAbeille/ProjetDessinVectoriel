#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include "./Format/CBitmap.h"
#include "./Form/Point.h"
#include "./Form/Line.h"
#include "./Form/Rectangle.h"
#include "./Form/Circle.h"
#include "./Form/Square.h"
#include "./Form/CircleS.h"
#include "./Form/RectangleS.h"
#include "./Form/SquareS.h"
#include "./Form/Triangle.h"
#include "./Form/TriangleS.h"

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

struct DrawableCircleS : public Drawable {
    CircleS circleS;
    DrawableCircleS(int order, const CircleS& circleS) : Drawable(order), circleS(circleS) {}
    void draw(CImage& img) override {
        circleS.draw(img);
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

struct DrawableRectangleS : public Drawable {
    RectangleS rectangleS;
    DrawableRectangleS(int order, const RectangleS& rectangleS) : Drawable(order), rectangleS(rectangleS) {}
    void draw(CImage& img) override {
        rectangleS.draw(img);
    }
};

struct DrawableSquare : public Drawable {
    Square square;
    DrawableSquare(int order, const Square& square) : Drawable(order), square(square) {}
    void draw(CImage& img) override {
        square.draw(img);
    }
};

struct DrawableSquareS : public Drawable {
    SquareS squareS;
    DrawableSquareS(int order, const SquareS& squareS) : Drawable(order), squareS(squareS) {}
    void draw(CImage& img) override {
        squareS.draw(img);
    }
};

struct DrawableTriangle : public Drawable {
    Triangle triangle;
    DrawableTriangle(int order, const Triangle& triangle) : Drawable(order), triangle(triangle) {}
    void draw(CImage& img) override {
        triangle.draw(img);
    }
};

struct DrawableTriangleS : public Drawable {  // Structure pour DrawableTriangleS
    TriangleS triangleS;
    DrawableTriangleS(int order, const TriangleS& triangleS) : Drawable(order), triangleS(triangleS) {}
    void draw(CImage& img) override {
        triangleS.draw(img);
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
        } else if (auto drawableCircleS = dynamic_cast<DrawableCircleS*>(shape)) {
            drawableCircleS->circleS.scale(scaleFactor);
        } else if (auto drawableLine = dynamic_cast<DrawableLine*>(shape)) {
            drawableLine->line.scale(scaleFactor);
        } else if (auto drawableRectangle = dynamic_cast<DrawableRectangle*>(shape)) {
            drawableRectangle->rectangle.scale(scaleFactor);
        } else if (auto drawableRectangleS = dynamic_cast<DrawableRectangleS*>(shape)) {
            drawableRectangleS->rectangleS.scale(scaleFactor);
        } else if (auto drawableSquare = dynamic_cast<DrawableSquare*>(shape)) {
            drawableSquare->square.scale(scaleFactor);
        } else if (auto drawableSquareS = dynamic_cast<DrawableSquareS*>(shape)) {
            drawableSquareS->squareS.scale(scaleFactor);
        } else if (auto drawableTriangle = dynamic_cast<DrawableTriangle*>(shape)) {
            drawableTriangle->triangle.scale(scaleFactor);
        } else if (auto drawableTriangleS = dynamic_cast<DrawableTriangleS*>(shape)) {  // Ajout du triangleS
            drawableTriangleS->triangleS.scale(scaleFactor);
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
                // Pour CERCLE, on utilise uniquement une couleur de contour
                if (iss >> x >> comma >> y >> comma >> radius >> comma
                    && getline(iss, colorStr, ',')
                    && (iss >> transparency >> comma >> order)) {
                    auto [r, g, b] = colors[colorStr];
                    shapes.push_back(new DrawableCircle(order, Circle(x, y, radius, r, g, b, transparency)));
                } else {
                    cerr << "Erreur de lecture de la ligne CERCLE: " << line << endl;
                }
            } else if (shapeType == "CERCLES") {
                // Pour CERCLES, on utilise deux couleurs (contour et remplissage)
                if (iss >> x >> comma >> y >> comma >> radius >> comma
                    && getline(iss, colorStr, ',')
                    && getline(iss, fillColorStr, ',')
                    && (iss >> transparency >> comma >> order)) {
                    auto [r, g, b] = colors[colorStr];
                    auto [fr, fg, fb] = colors[fillColorStr];
                    shapes.push_back(new DrawableCircleS(order, CircleS(x, y, radius, r, g, b, fr, fg, fb, transparency)));
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
        } else if (shapeType == "RECTANGLE") {
            int x, y, width, height, transparency, order;
            string colorStr;
            char comma;

            if (iss >> x >> comma >> y >> comma >> width >> comma >> height >> comma
                && getline(iss, colorStr, ',')
                && (iss >> transparency >> comma >> order)) {
                auto [r, g, b] = colors[colorStr];
                shapes.push_back(new DrawableRectangle(order, Rectangle(x, y, width, height, r, g, b, transparency)));
            } else {
                cerr << "Erreur de lecture de la ligne RECTANGLE: " << line << endl;
            }
        } else if (shapeType == "RECTANGLES") {
            int x, y, width, height, transparency, order;
            std::string colorStr, fillColorStr;
            char comma;

            if (iss >> x >> comma >> y >> comma >> width >> comma >> height >> comma
                && getline(iss, colorStr, ',')  // Lire la première couleur (contour)
                && getline(iss, fillColorStr, ',') // Lire la deuxième couleur (remplissage)
                && (iss >> transparency >> comma >> order)) {

                // Utiliser les couleurs pour récupérer les valeurs RGB
                auto [r, g, b] = colors[colorStr];   // Couleur de contour
                auto [fr, fg, fb] = colors[fillColorStr];  // Couleur de remplissage

                // Ajouter la forme à la collection
                shapes.push_back(new DrawableRectangleS(order, RectangleS(x, y, width, height, r, g, b, fr, fg, fb, transparency)));
            } else {
                cerr << "Erreur de lecture de la ligne RECTANGLES: " << line << endl;
            }
        } else if (shapeType == "SQUARE") {
            int x, y, side, transparency, order;
            string colorStr;
            char comma;

            if (iss >> x >> comma >> y >> comma >> side >> comma
                && getline(iss, colorStr, ',')  // Lire la couleur
                && (iss >> transparency >> comma >> order)) {  // Lire la transparence et l'ordre
                auto [r, g, b] = colors[colorStr];  // Conversion de la couleur
                shapes.push_back(new DrawableSquare(order, Square(x, y, side, r, g, b, transparency)));
            } else {
                cerr << "Erreur de lecture de la ligne SQUARE: " << line << endl;
            }
        } else if (shapeType == "SQUARES") {
            int x, y, side, transparency, order;
            string colorStr, fillColorStr;
            char comma;

            if (iss >> x >> comma >> y >> comma >> side >> comma
                && getline(iss, colorStr, ',')  // Lire la couleur de la bordure
                && getline(iss, fillColorStr, ',')  // Lire la couleur de remplissage
                && (iss >> transparency >> comma >> order)) {  // Lire la transparence et l'ordre
                auto [r, g, b] = colors[colorStr];  // Conversion de la couleur de bordure
                auto [fr, fg, fb] = colors[fillColorStr];  // Conversion de la couleur de remplissage
                shapes.push_back(new DrawableSquareS(order, SquareS(x, y, side, r, g, b, fr, fg, fb, transparency)));
            } else {
                cerr << "Erreur de lecture de la ligne SQUARES: " << line << endl;
            }
        }
        else if (shapeType == "TRIANGLE") {
            int x1, y1, x2, y2, x3, y3, transparency, order;
            string colorStr;
            char comma;

            if (iss >> x1 >> comma >> y1 >> comma >> x2 >> comma >> y2 >> comma >> x3 >> comma >> y3 >> comma
                && getline(iss, colorStr, ',')  // Lecture de la couleur
                && (iss >> transparency >> comma >> order)) {

                // Vérification des valeurs de couleur
                cout << "Couleur lue: " << colorStr << endl;

                auto [r, g, b] = colors[colorStr];  // Récupération des composantes RGB à partir du dictionnaire
                shapes.push_back(new DrawableTriangle(order, Triangle(x1, y1, x2, y2, x3, y3, r, g, b, transparency)));
            } else {
                cerr << "Erreur de lecture de la ligne TRIANGLE: " << line << endl;
            }
        } else if (shapeType == "TRIANGLES") {  // Ajout pour TRIANGLE
            int x1, y1, x2, y2, x3, y3, transparency, order;
            string colorStr, fillColorStr;
            char comma;

            if (iss >> x1 >> comma >> y1 >> comma >> x2 >> comma >> y2 >> comma >> x3 >> comma >> y3 >> comma
                && getline(iss, colorStr, ',')
                && getline(iss, fillColorStr, ',')
                && (iss >> transparency >> comma >> order)) {
                auto [r, g, b] = colors[colorStr];
                auto [fr, fg, fb] = colors[fillColorStr];
                shapes.push_back(new DrawableTriangleS(order, TriangleS(x1, y1, x2, y2, x3, y3, r, g, b, fr, fg, fb, transparency)));
            } else {
                cerr << "Erreur de lecture de la ligne TRIANGLES: " << line << endl;
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
    int newWidth = static_cast<int>(1200 * scaleFactor);
    int newHeight = static_cast<int>(1200 * scaleFactor);

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
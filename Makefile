CC=g++

CFLAGS=-Ofast -march=native -mtune=native -std=c++14

LDFLAGS=

EXEC=main

SRC=./src/Format/CBitmap.cpp \
    ./src/Image/CImage.cpp   \
    ./src/Image/CLigne.cpp   \
    ./src/Image/CPixel.cpp   \
    ./src/Form/Point.cpp     \
    ./src/Form/Line.cpp     \
    ./src/Form/Rectangle.cpp \
    ./src/Form/Circle.cpp    \
    ./src/Form/Square.cpp	\
    ./src/Form/CircleS.cpp	\
    ./src/Form/RectangleS.cpp	\
    ./src/Form/SquareS.cpp	\
    ./src/Form/Triangle.cpp	\
    ./src/Form/TriangleS.cpp	\
    ./src/main.cpp

OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

main: $(OBJ)
	$(CC) $(CFLAGS) -o ./bin/$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean mrproper

# Règle pour nettoyer les fichiers compilés
clean:
	@echo "Cleaning up..."
	@rm -f ./bin/main  # Utiliser -f pour éviter les erreurs si le fichier n'existe pas
	@rm -f ./src/*.o    # Utiliser -f pour éviter les erreurs

# Règle pour un nettoyage complet
mrproper: clean
	@echo "Removing all generated files..."
	@rm -f ./bin/$(EXEC)  # Utiliser -f pour éviter les erreurs
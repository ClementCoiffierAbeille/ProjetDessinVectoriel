/*
 *  CImage.h
 *  P_Bitmap
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

#include "CLigne.h"

#ifndef CIMAGE_H_
#define CIMAGE_H_

class CImage{
private:
    CLigne** liste;
    int taille;

public:
    CImage(int hauteur, int largeur);

    ~CImage();

    int size();

    CLigne* getLigne(int position);

    CPixel* getPixel(int posX, int posY);
};

#endif /*CIMAGE_H_*/

/*
 *  CLigne.h
 *  P_Bitmap
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

#include "CPixel.h"

#ifndef CLIGNE_H_
#define CLIGNE_H_

class CLigne{
private:
    CPixel** ligne;
    int taille;

public:
    CLigne(int _taille);

    CLigne();

    ~CLigne();

    int size();

    CPixel* getPixel(int position);
};

#endif /*CLIGNE_H_*/

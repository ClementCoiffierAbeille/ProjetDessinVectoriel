/*
 *  CImage.cpp
 *  P_Bitmap
 */

#include "CImage.h"

CImage::CImage(int hauteur, int largeur){
    //cout << "Instanciation des lignes... " << taille << endl;
    taille = hauteur;
    liste = (CLigne**)new CLigne**[taille];
    for(int i=0; i<taille; i++){
        liste[i] = new CLigne(largeur);
    }
}

CImage::~CImage(){
    for(int i=0; i<taille; i++)
        delete liste[i];
    delete liste;
}

int CImage::size(){
    return taille;
}

CLigne* CImage::getLigne(int position){
    if( (position >= taille) ){
        cout << "CImage::getLigne => trying to access " << position << " but the line has only " << taille << " data" << endl;
    }
    return (position < taille)?liste[position]:NULL;
}

CPixel* CImage::getPixel(int posX, int posY){
    CLigne* ligne =  getLigne( posY );
    if( ligne == NULL) return NULL;
    return ligne->getPixel(posX);
}

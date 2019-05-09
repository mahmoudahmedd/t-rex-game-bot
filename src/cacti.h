/**
 *  @file    cacti.h
 *  @author  Mahmoud Ahmed Tawfik (mahmoudahmedd)
 *  @date    09/05/2019
 *  @version 1.0
 *
 *  @brief   Cacti is an object an instance of a creature.
 */

#pragma once

#ifndef CACTI_H_INCLUDED
#define CACTI_H_INCLUDED

#include "creature.h"

class Cacti: public Creature
{
public:
    Cacti()
    {
        this->color = RGB(83, 83, 83);
    }

    bool isCacti(Bitmap24 _img)
    {
        RGB tempColor1, tempColor2, tempColor3, tempColor4;

        for(unsigned int i = 0 ; i <= 60 ; i += 2)
        {
            this->p1    = Pixel(540 - i, 235);
            this->p2    = Pixel(540 - i, 200);

            this->p3    = Pixel(540 - i, 215);
            this->p4    = Pixel(540 - i, 235);

            _img.getPixel(this->p1.XCoordinate, this->p1.YCoordinate, tempColor1);
            _img.getPixel(this->p2.XCoordinate, this->p2.YCoordinate, tempColor2);

            _img.getPixel(this->p3.XCoordinate, this->p3.YCoordinate, tempColor3);
            _img.getPixel(this->p4.XCoordinate, this->p4.YCoordinate, tempColor4);

            if((tempColor1 == this->color && tempColor2 == this->color) ||
                    (tempColor3 == this->color && tempColor4 == this->color))
                return true;

        }

        return false;
    }

    ~Cacti() {}
};

#endif // CACTI_H_INCLUDED

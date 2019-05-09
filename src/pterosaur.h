/**
 *  @file    pterosaur.h
 *  @author  Mahmoud Ahmed Tawfik (mahmoudahmedd)
 *  @date    09/05/2019
 *  @version 1.0
 *
 *  @brief   Pterosaur is an object an instance of a creature.
 */

#pragma once

#ifndef PTEROSAUR_H_INCLUDED
#define PTEROSAUR_H_INCLUDED

#include "creature.h"

class Pterosaur: public Creature
{
public:
    Pterosaur()
    {
        this->color = RGB(83, 83, 83);
    }

    int isPterosaur(Bitmap24 _img)
    {
        RGB tempColor1, tempColor2, tempColor3, tempColor4, tempColor5, tempColor6;

        for(unsigned int i = 0 ; i <= 60 ; i += 2)
        {
            this->p1    = Pixel(540 - i, 201);
            this->p2    = Pixel(540 - i - 25, 201);
            this->p3    = Pixel(540 - i - 15, 198);

            this->p4    = Pixel(540 - i, 227);
            this->p5    = Pixel(540 - i - 25, 227);
            this->p6    = Pixel(540 - i - 15, 224);

            _img.getPixel(this->p1.XCoordinate, this->p1.YCoordinate, tempColor1);
            _img.getPixel(this->p2.XCoordinate, this->p2.YCoordinate, tempColor2);
            _img.getPixel(this->p3.XCoordinate, this->p3.YCoordinate, tempColor3);

            _img.getPixel(this->p4.XCoordinate, this->p4.YCoordinate, tempColor4);
            _img.getPixel(this->p5.XCoordinate, this->p5.YCoordinate, tempColor5);
            _img.getPixel(this->p6.XCoordinate, this->p6.YCoordinate, tempColor6);

            if(tempColor1 == this->color && tempColor2 == this->color && tempColor3 == this->color)
                return 1;

            if(tempColor4 == this->color && tempColor5 == this->color && tempColor6 == this->color)
                return 2;
        }

        return 0;
    }

    ~Pterosaur() {}
};

#endif // PTEROSAUR_H_INCLUDED

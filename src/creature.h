/**
 *  @file    creature.h
 *  @author  Mahmoud Ahmed Tawfik (mahmoudahmedd)
 *  @date    09/05/2019
 *  @version 1.0
 *
 *  @brief   Creature contain information about himself including color, etc.
 */

#pragma once

#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED

#include "rgb.h"
#include "bitmap24.h"
#include "pixel.h"

class Creature
{
protected:
    RGB color;

    Pixel p1;
    Pixel p2;
    Pixel p3;
    Pixel p4;
    Pixel p5;
    Pixel p6;
public:
    Creature() {}
    ~Creature() {}
};

#endif // CREATURE_H_INCLUDED

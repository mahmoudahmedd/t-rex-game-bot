/**
 *  @file    pixel.h
 *  @author  Mahmoud Ahmed Tawfik (mahmoudahmedd)
 *  @date    09/05/2019
 *  @version 1.0
 *
 *  @brief   Pixel is a single point in a graphic image.
 */

#pragma once

#ifndef PIXEL_H_INCLUDED
#define PIXEL_H_INCLUDED

class Pixel
{
public:
    unsigned int XCoordinate;
    unsigned int YCoordinate;

    Pixel() {}

    Pixel(unsigned int _XCoordinate, unsigned int _YCoordinate)
    {
        this->XCoordinate = _XCoordinate;
        this->YCoordinate = _YCoordinate;
    }

    Pixel& operator=(const Pixel& _pixel)
    {
        this->XCoordinate = _pixel.XCoordinate;
        this->YCoordinate = _pixel.YCoordinate;

        return *this;
    }

    ~Pixel() {}
};

#endif // RGB_H_INCLUDED

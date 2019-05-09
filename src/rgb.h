/**
 *  @file    rgb.h
 *  @author  Mahmoud Ahmed Tawfik (mahmoudahmedd)
 *  @date    09/05/2019
 *  @version 1.0
 *
 *  @brief   The RGB color model is an additive color model in which red(R), green(G) and blue(B).
 */

#pragma once

#ifndef RGB_H_INCLUDED
#define RGB_H_INCLUDED

#undef RGB

class RGB
{
public:
    unsigned char   red;
    unsigned char green;
    unsigned char  blue;

    RGB() {}

    RGB(unsigned char _red, unsigned char _green, unsigned char _blue)
    {
        this->red   = _red;
        this->green = _green;
        this->blue  = _blue;
    }

    RGB& operator=(const RGB& _color)
    {
        this->red   = _color.red;
        this->green = _color.green;
        this-> blue = _color.blue;

        return *this;
    }

    bool operator==(const RGB& _color)
    {
        if(this->red == _color.red && this->green == _color.green && this->blue == _color.blue)
            return true;
        else
            return false;
    }
};

#endif // RGB_H_INCLUDED

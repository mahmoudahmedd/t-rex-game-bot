/**
 *  @file    bitmap24.h
 *  @author  Mahmoud Ahmed Tawfik (mahmoudahmedd)
 *  @date    09/05/2019
 *  @version 1.1
 *
 *  @brief   Bitmap24 Image Library.
 */

#pragma once

#ifndef BITMAP24_H_INCLUDED
#define BITMAP24_H_INCLUDED

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>
#include "rgb.h"

enum ChannelMode
{
    rgbMode = 0, bgrMode = 1
};

struct BitmapFileHeader
{
    unsigned short type;
    unsigned int   size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int   off_bits;

    unsigned int structSize() const
    {
        return sizeof(type     ) +
               sizeof(size     ) +
               sizeof(reserved1) +
               sizeof(reserved2) +
               sizeof(off_bits ) ;
    }

    void clear()
    {
        std::memset(this, 0x00, sizeof(BitmapFileHeader));
    }
};

struct BitmapInformationHeader
{
    unsigned int   size;
    unsigned int   width;
    unsigned int   height;
    unsigned short planes;
    unsigned short bit_count;
    unsigned int   compression;
    unsigned int   size_image;
    unsigned int   x_pels_per_meter;
    unsigned int   y_pels_per_meter;
    unsigned int   clr_used;
    unsigned int   clr_important;

    unsigned int structSize() const
    {
        return sizeof(size             ) +
               sizeof(width           ) +
               sizeof(height          ) +
               sizeof(planes          ) +
               sizeof(bit_count       ) +
               sizeof(compression     ) +
               sizeof(size_image      ) +
               sizeof(x_pels_per_meter) +
               sizeof(y_pels_per_meter) +
               sizeof(clr_used        ) +
               sizeof(clr_important   ) ;
    }

    void clear()
    {
        std::memset(this, 0x00, sizeof(BitmapInformationHeader));
    }
};

class Bitmap24
{
private:
    std::vector<unsigned char> data;
    std::string  fileName;
    unsigned int width;
    unsigned int height;
    unsigned int rowIncrement;
    unsigned int bytesPerPixel;
    ChannelMode  channelMode;

    template <typename T>
    void writeToStream(std::ofstream& stream,const T& t) const
    {
        stream.write(reinterpret_cast<const char*>(&t), sizeof(T));
    }

    template <typename T>
    void readFromStream(std::ifstream& stream,T& t)
    {
        stream.read(reinterpret_cast<char*>(&t),sizeof(T));
    }

    void writeBfh(std::ofstream& stream, const BitmapFileHeader& bfh) const
    {
        if (bigEndian())
        {
            writeToStream(stream,flip(bfh.type     ));
            writeToStream(stream,flip(bfh.size     ));
            writeToStream(stream,flip(bfh.reserved1));
            writeToStream(stream,flip(bfh.reserved2));
            writeToStream(stream,flip(bfh.off_bits ));
        }
        else
        {
            writeToStream(stream,bfh.type     );
            writeToStream(stream,bfh.size     );
            writeToStream(stream,bfh.reserved1);
            writeToStream(stream,bfh.reserved2);
            writeToStream(stream,bfh.off_bits );
        }
    }

    void writeBih(std::ofstream& stream, const BitmapInformationHeader& bih) const
    {
        if (bigEndian())
        {
            writeToStream(stream,flip(bih.size            ));
            writeToStream(stream,flip(bih.width           ));
            writeToStream(stream,flip(bih.height          ));
            writeToStream(stream,flip(bih.planes          ));
            writeToStream(stream,flip(bih.bit_count       ));
            writeToStream(stream,flip(bih.compression     ));
            writeToStream(stream,flip(bih.size_image      ));
            writeToStream(stream,flip(bih.x_pels_per_meter));
            writeToStream(stream,flip(bih.y_pels_per_meter));
            writeToStream(stream,flip(bih.clr_used        ));
            writeToStream(stream,flip(bih.clr_important   ));
        }
        else
        {
            writeToStream(stream,bih.size            );
            writeToStream(stream,bih.width           );
            writeToStream(stream,bih.height          );
            writeToStream(stream,bih.planes          );
            writeToStream(stream,bih.bit_count       );
            writeToStream(stream,bih.compression     );
            writeToStream(stream,bih.size_image      );
            writeToStream(stream,bih.x_pels_per_meter);
            writeToStream(stream,bih.y_pels_per_meter);
            writeToStream(stream,bih.clr_used        );
            writeToStream(stream,bih.clr_important   );
        }
    }

    void readBfh(std::ifstream& stream, BitmapFileHeader& bfh)
    {
        readFromStream(stream,bfh.type     );
        readFromStream(stream,bfh.size     );
        readFromStream(stream,bfh.reserved1);
        readFromStream(stream,bfh.reserved2);
        readFromStream(stream,bfh.off_bits );

        if (bigEndian())
        {
            bfh.type      = flip(bfh.type     );
            bfh.size      = flip(bfh.size     );
            bfh.reserved1 = flip(bfh.reserved1);
            bfh.reserved2 = flip(bfh.reserved2);
            bfh.off_bits  = flip(bfh.off_bits );
        }
    }

    void readBih(std::ifstream& stream, BitmapInformationHeader& bih)
    {
        readFromStream(stream,bih.size            );
        readFromStream(stream,bih.width           );
        readFromStream(stream,bih.height          );
        readFromStream(stream,bih.planes          );
        readFromStream(stream,bih.bit_count       );
        readFromStream(stream,bih.compression     );
        readFromStream(stream,bih.size_image      );
        readFromStream(stream,bih.x_pels_per_meter);
        readFromStream(stream,bih.y_pels_per_meter);
        readFromStream(stream,bih.clr_used        );
        readFromStream(stream,bih.clr_important   );

        if (bigEndian())
        {
            bih.size          = flip(bih.size               );
            bih.width         = flip(bih.width              );
            bih.height        = flip(bih.height             );
            bih.planes        = flip(bih.planes             );
            bih.bit_count     = flip(bih.bit_count          );
            bih.compression   = flip(bih.compression        );
            bih.size_image    = flip(bih.size_image         );
            bih.x_pels_per_meter = flip(bih.x_pels_per_meter);
            bih.y_pels_per_meter = flip(bih.y_pels_per_meter);
            bih.clr_used      = flip(bih.clr_used           );
            bih.clr_important = flip(bih.clr_important      );
        }
    }

    bool bigEndian() const
    {
        unsigned int v = 0x01;

        return (1 != reinterpret_cast<char*>(&v)[0]);
    }

    unsigned short flip(const unsigned short& v) const
    {
        return ((v >> 8) | (v << 8));
    }

    unsigned int flip(const unsigned int& v) const
    {
        return (
                   ((v & 0xFF000000) >> 0x18) |
                   ((v & 0x000000FF) << 0x18) |
                   ((v & 0x00FF0000) >> 0x08) |
                   ((v & 0x0000FF00) << 0x08)
               );
    }

    void loadBitmap()
    {
        std::ifstream stream(fileName.c_str(), std::ios::binary);

        if (!stream)
        {
            std::cerr << "Bitmap24::load_bitmap() ERROR: Bitmap24 - file " << fileName << " not found!" << std::endl;
            return;
        }

        width  = 0;
        height = 0;

        BitmapFileHeader bfh;
        BitmapInformationHeader bih;

        bfh.clear();
        bih.clear();

        readBfh(stream, bfh);
        readBih(stream, bih);

        if (bfh.type != 19778)
        {
            bfh.clear();
            bih.clear();

            stream.close();

            std::cerr << "Bitmap24::load_bitmap() ERROR: Bitmap24 - Invalid type value " << bfh.type << " expected 19778." << std::endl;
            return;
        }

        if (bih.bit_count != 24)
        {
            bfh.clear();
            bih.clear();

            stream.close();

            std::cerr << "Bitmap24::load_bitmap() ERROR: Bitmap24 - Invalid bit depth " << bih.bit_count << " expected 24." << std::endl;

            return;
        }

        if (bih.size != bih.structSize())
        {
            bfh.clear();
            bih.clear();

            stream.close();

            std::cerr << "Bitmap24::load_bitmap() ERROR: Bitmap24 - Invalid BIH size " << bih.size << " expected " << bih.structSize() << std::endl;

            return;
        }

        width  = bih.width;
        height = bih.height;

        bytesPerPixel = bih.bit_count >> 3;

        unsigned int padding = (4 - ((3 * width) % 4)) % 4;
        char padding_data[4] = {0, 0, 0, 0};

        std::size_t bitmap_file_size = fileSize(fileName);

        std::size_t bitmap_logical_size = (height * width * bytesPerPixel) +
                                          (height * padding)               +
                                          bih.structSize()                 +
                                          bfh.structSize();

        if (bitmap_file_size != bitmap_logical_size)
        {
            bfh.clear();
            bih.clear();

            stream.close();

            std::cerr << "Bitmap24::load_bitmap() ERROR: Bitmap24 - Mismatch between logical and physical sizes of bitmap. "
                      << "Logical: "
                      << bitmap_logical_size
                      << " "
                      << "Physical: "
                      << bitmap_file_size
                      << std::endl;
            return;
        }

        createBitmap();

        for (unsigned int i = 0; i < height; ++i)
        {
            unsigned char* data_ptr = row(height - i - 1); // read in inverted row order

            stream.read(reinterpret_cast<char*>(data_ptr), sizeof(char) * bytesPerPixel * width);
            stream.read(padding_data,padding);
        }
    }

    void createBitmap()
    {
        rowIncrement = width * bytesPerPixel;
        data.resize(height * rowIncrement);
    }

    size_t fileSize(const std::string& _fileName) const
    {
        std::ifstream file(_fileName.c_str(),std::ios::in | std::ios::binary);
        if (!file)
            return 0;

        file.seekg (0, std::ios::end);

        return static_cast<std::size_t>(file.tellg());
    }

    unsigned char* row(unsigned int row_index) const
    {
        return const_cast<unsigned char*>(&data[(row_index * rowIncrement)]);
    }

public:
    Bitmap24()
        :
        fileName(""),
        width(0),
        height(0),
        rowIncrement(0),
        bytesPerPixel(3)
    {}

    Bitmap24(const std::string& _filename)
        :
        fileName(_filename),
        width          (0),
        height         (0),
        rowIncrement  (0),
        bytesPerPixel(0),
        channelMode(bgrMode)
    {
        loadBitmap();
    }

    Bitmap24(const unsigned int _width, const unsigned int _height)
        :
        fileName(""),
        width (width ),
        height(height),
        rowIncrement (0),
        bytesPerPixel(3),
        channelMode(bgrMode)
    {
        createBitmap();
    }

    Bitmap24(const Bitmap24& _image)
        :
        fileName(_image.fileName),
        width    (_image.width  ),
        height   (_image.height ),
        rowIncrement  (0),
        bytesPerPixel(3),
        channelMode(bgrMode)
    {
        createBitmap();
        data = _image.data;
    }

    bool operator!()
    {
        return (data.size()  == 0) ||
               (width        == 0) ||
               (height       == 0) ||
               (rowIncrement == 0);
    }

    operator bool()
    {
        return (data.size()  != 0) &&
               (width        != 0) &&
               (height       != 0) &&
               (rowIncrement != 0);
    }

    Bitmap24& operator=(const Bitmap24& _image)
    {
        if (this != &_image)
        {
            fileName      = _image.fileName;
            bytesPerPixel = _image.bytesPerPixel;
            width         = _image.width;
            height        = _image.height;
            rowIncrement  = 0;
            channelMode   = _image.channelMode;
            createBitmap();
            data          = _image.data;
        }

        return *this;
    }

    void setImage(std::string _fileName)
    {
        fileName      =  _fileName;
        width         =	0;
        height        =	0;
        rowIncrement  =	0;
        bytesPerPixel =	0;
        channelMode   =	bgrMode;
        loadBitmap();
    }

    void saveImage(const std::string& _fileName) const
    {
        std::ofstream stream(_fileName.c_str(), std::ios::binary);

        if (!stream)
        {
            std::cerr << "Bitmap24::save_image(): Error - Could not open file "  << _fileName << " for writing!" << std::endl;
            return;
        }

        BitmapInformationHeader bih;

        bih.width            = width;
        bih.height           = height;
        bih.bit_count        = static_cast<unsigned short>(bytesPerPixel << 3);
        bih.clr_important    = 0;
        bih.clr_used         = 0;
        bih.compression      = 0;
        bih.planes           = 1;
        bih.size             = bih.structSize();
        bih.x_pels_per_meter = 0;
        bih.y_pels_per_meter = 0;
        bih.size_image       = (((bih.width * bytesPerPixel) + 3) & 0x0000FFFC) * bih.height;

        BitmapFileHeader bfh;

        bfh.type             = 19778;
        bfh.size             = bfh.structSize() + bih.structSize() + bih.size_image;
        bfh.reserved1        = 0;
        bfh.reserved2        = 0;
        bfh.off_bits         = bih.structSize() + bfh.structSize();

        writeBfh(stream, bfh);
        writeBih(stream, bih);

        unsigned int padding = (4 - ((3 * width) % 4)) % 4;
        char padding_data[4] = { 0x00, 0x00, 0x00, 0x00 };

        for (unsigned int i = 0; i < height; ++i)
        {
            const unsigned char* data_ptr = &data[(rowIncrement * (height - i - 1))];

            stream.write(reinterpret_cast<const char*>(data_ptr), sizeof(unsigned char) * bytesPerPixel * width);
            stream.write(padding_data,padding);
        }

        stream.close();
    }

    void getPixel(const unsigned int _x, const unsigned int _y,
                  unsigned char& _red,
                  unsigned char& _green,
                  unsigned char& _blue) const
    {
        const unsigned int y_offset = _y * rowIncrement;
        const unsigned int x_offset = _x * bytesPerPixel;
        const unsigned int offset   = y_offset + x_offset;

        _blue  = data[offset + 0];
        _green = data[offset + 1];
        _red   = data[offset + 2];
    }

    template <typename RGB>
    void getPixel(const unsigned int _x, const unsigned int _y, RGB& _colour) const
    {
        getPixel(_x, _y, _colour.red, _colour.green, _colour.blue);
    }

    RGB getPixel(const unsigned int _x, const unsigned int _y) const
    {
        RGB colour;
        getPixel(_x, _y, colour.red, colour.green, colour.blue);
        return colour;
    }

    void setPixel(const unsigned int _x, const unsigned int _y,
                  const unsigned char _red,
                  const unsigned char _green,
                  const unsigned char _blue)
    {
        const unsigned int y_offset = _y * rowIncrement;
        const unsigned int x_offset = _x * bytesPerPixel;
        const unsigned int offset   = y_offset + x_offset;

        data[offset + 0] = _blue;
        data[offset + 1] = _green;
        data[offset + 2] = _red;
    }

    void setPixel(const unsigned int _x, const unsigned int _y,RGB _color)
    {
        setPixel(_x, _y, _color.red, _color.green, _color.blue);
    }

    unsigned int pixelCount() const
    {
        return width * height;
    }

    unsigned int getWidth() const
    {
        return width;
    }

    unsigned int getHeight() const
    {
        return height;
    }

    unsigned int getSize() const
    {
        return pixelCount() * bytesPerPixel;
    }
};

#endif // BITMAP24_H_INCLUDED

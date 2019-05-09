/**
 *  @file    t_bot.h
 *  @author  Mahmoud Ahmed Tawfik (mahmoudahmedd)
 *  @date    09/05/2019
 *  @version 1.0
 *
 *  @brief   T-rex game bot.
 */

#pragma once

#ifndef TBOT_H_INCLUDED
#define TBOT_H_INCLUDED

#include <windows.h>
#include <iostream>
#include <string>
#include "pterosaur.h"
#include "cacti.h"

enum
{
    BLACK       = 0,
    DARK_BLUE   = 1,
    DARK_GREEN  = 2,
    TEAL        = 3,
    DARK_RED    = 4,
    DARK_PURPLE = 5,
    GOLD        = 6,
    GREY        = 7,
    DARK_WHITE  = 8,
    BLUE        = 9,
    GREEN       = 10,
    CYAN        = 11,
    RED         = 12,
    PURPLE      = 13,
    YELLOW      = 14,
    WHITE       = 15
};

class TBot
{
private:
    int x1;
    int y1;
    int sWidth;
    int sHeight;
    Bitmap24 img;
    Cacti c;
    Pterosaur p;
    wchar_t *tempPathWchar;
    std::string tempPathStr;

public:
    TBot(wchar_t *_tempPathWchar)
    {
        this->tempPathWchar = _tempPathWchar;
        std::wstring ws(_tempPathWchar);
        this->tempPathStr.assign(ws.begin(), ws.end());

        // Get screen dimensions
        this->getScreenDimensions();

        // Dispaly Hello
        placeCursor(23, 11);
        setColor(YELLOW, BLACK);
        std::cout << "Hello!" << std::endl;
        placeCursor(23, 11);
    }

    void run()
    {
        std::cout << "Running!... PRESS ESC TO EXIT." << std::endl;
        placeCursor(23, 11);

        while(true)
        {
            HWND hwnd = GetConsoleWindow();
            ShowWindow(hwnd, SW_SHOWNORMAL);

            // Copy screen to bitmap
            HDC     hScreen = GetDC(NULL);
            HDC     hDC     = CreateCompatibleDC(hScreen);
            HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, sWidth, sHeight);
            HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
            BOOL    bRet    = BitBlt(hDC, 0, 0, sWidth, sHeight, hScreen, x1, y1, SRCCOPY);

            // GetClientRect(hwnd, &rc);
            OpenClipboard(NULL);
            EmptyClipboard();
            SetClipboardData(CF_BITMAP, hBitmap);
            CloseClipboard();

            // Copy to clipboard
            OpenClipboard(NULL);
            EmptyClipboard();
            SetClipboardData(CF_BITMAP, hBitmap);
            CloseClipboard();

            PBITMAPINFO pBitmapInfo = CreateBitmapInfoStruct(hBitmap);
            CreateBMPFilea(this->tempPathWchar, pBitmapInfo, hBitmap, hDC);

            img.setImage(this->tempPathStr);

            if(c.isCacti(img))
                keybd_event(VK_UP, 0, 0, 0);


            int x = p.isPterosaur(img);

            if(x)
            {
                if(x == 1)
                    keybd_event(VK_DOWN, 0, 0, 0);
                else if(x == 2)
                    keybd_event(VK_UP, 0, 0, 0);
            }


            SelectObject(hDC, old_obj);
            DeleteDC(hDC);
            ReleaseDC(NULL, hScreen);
            DeleteObject(hBitmap);

            if (GetAsyncKeyState(VK_ESCAPE))
                exit(0);
        }
    }

    PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp)
    {
        BITMAP bmp;
        PBITMAPINFO pbmi;
        WORD    cClrBits;
        // Retrieve the bitmap color format, width, and height.
        if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
            return NULL;

        // Convert the color format to a count of bits.
        cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
        if (cClrBits == 1)
            cClrBits = 1;
        else if (cClrBits <= 4)
            cClrBits = 4;
        else if (cClrBits <= 8)
            cClrBits = 8;
        else if (cClrBits <= 16)
            cClrBits = 16;
        else if (cClrBits <= 24)
            cClrBits = 24;
        else
            cClrBits = 32;

        cClrBits = 24; // ?

        // Allocate memory for the BITMAPINFO structure. (This structure
        // contains a BITMAPINFOHEADER structure and an array of RGBQUAD
        // data structures.)

        if (cClrBits != 24)
            pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
                                           sizeof(BITMAPINFOHEADER) +
                                           sizeof(RGBQUAD) * (1 << cClrBits));

        // There is no RGBQUAD array for the 24-bit-per-pixel format.

        else
            pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
                                           sizeof(BITMAPINFOHEADER));

        // Initialize the fields in the BITMAPINFO structure.

        pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        pbmi->bmiHeader.biWidth = bmp.bmWidth;
        pbmi->bmiHeader.biHeight = bmp.bmHeight;
        pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
        pbmi->bmiHeader.biBitCount = 24; // ?
        if (cClrBits < 24)
            pbmi->bmiHeader.biClrUsed = (1 << cClrBits);

        // If the bitmap is not compressed, set the BI_RGB flag.
        pbmi->bmiHeader.biCompression = BI_RGB;

        // Compute the number of bytes in the array of color
        // indices and store the result in biSizeImage.
        // For Windows NT, the width must be DWORD aligned unless
        // the bitmap is RLE compressed. This example shows this.
        // For Windows 95/98/Me, the width must be WORD aligned unless the
        // bitmap is RLE compressed.
        pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
                                      * pbmi->bmiHeader.biHeight;
        // Set biClrImportant to 0, indicating that all of the
        // device colors are important.
        pbmi->bmiHeader.biClrImportant = 0;
        return pbmi;
    }

    void CreateBMPFilea(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC)
    {
        HANDLE hf;                 // file handle
        BITMAPFILEHEADER hdr;       // bitmap file-header
        PBITMAPINFOHEADER pbih;     // bitmap info-header
        LPBYTE lpBits;              // memory pointer
        DWORD dwTotal;              // total count of bytes
        DWORD cb;                   // incremental count of bytes
        BYTE *hp;                   // byte pointer
        DWORD dwTmp;

        pbih = (PBITMAPINFOHEADER)pbi;
        lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

        if (!lpBits)
            return;

        // Retrieve the color table (RGBQUAD array) and the bits
        // (array of palette indices) from the DIB.
        if (!GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi,
                       DIB_RGB_COLORS))
        {
            return;
        }

        // Create the .BMP file.
        hf = CreateFile(pszFile,
                        GENERIC_READ | GENERIC_WRITE,
                        (DWORD)0,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        (HANDLE)NULL);
        if (hf == INVALID_HANDLE_VALUE)
            return;
        hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"
        // Compute the size of the entire file.
        hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
                             pbih->biSize + pbih->biClrUsed
                             * sizeof(RGBQUAD) + pbih->biSizeImage);
        hdr.bfReserved1 = 0;
        hdr.bfReserved2 = 0;

        // Compute the offset to the array of color indices.
        hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
                        pbih->biSize + pbih->biClrUsed
                        * sizeof(RGBQUAD);

        // Copy the BITMAPFILEHEADER into the .BMP file.
        if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
                       (LPDWORD)&dwTmp, NULL))
        {
            return;
        }

        // Copy the BITMAPINFOHEADER and RGBQUAD array into the file.
        if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
                       + pbih->biClrUsed * sizeof(RGBQUAD),
                       (LPDWORD)&dwTmp, (NULL)))
            return;

        // Copy the array of color indices into the .BMP file.
        dwTotal = cb = pbih->biSizeImage;
        hp = lpBits;
        if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL))
            return;

        // Close the .BMP file.
        if (!CloseHandle(hf))
            return;

        // Free memory.
        GlobalFree((HGLOBAL)lpBits);
    }

    // Get screen dimensions
    void getScreenDimensions()
    {
        int x2, y2;
        x1		= GetSystemMetrics(SM_XVIRTUALSCREEN);
        y1		= GetSystemMetrics(SM_YVIRTUALSCREEN);
        x2		= GetSystemMetrics(SM_CXVIRTUALSCREEN);
        y2		= GetSystemMetrics(SM_CYVIRTUALSCREEN);
        sWidth  = x2 - x1;
        sHeight = y2 - y1;
    }

    void setColor(const int foreground, const int background)
    {
        int Color = foreground + (background * 16);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, Color);

        return;
    }

    void placeCursor(const int x, const int y)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        COORD PlaceCursorHere;
        PlaceCursorHere.X = x;
        PlaceCursorHere.Y = y;

        SetConsoleCursorPosition(hConsole, PlaceCursorHere);

        return;
    }

    ~TBot() {}
};

#endif // TBOT_H_INCLUDED




// https://github.com/Relintai/sfw


/*
Copyright (c) 2023-present Péter Magyar.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// TODO gather all licenses to here


#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <ctime>
#include <wchar.h>
#include <cstdint>
#include <memory.h>

#ifndef SFWL_H
#include "sfwl.h"
#endif

//===================  CORE SECTION  ===================

#line 1 "sfwl/core/ucaps.h"
#ifndef UCAPS_H
#define UCAPS_H

/*************************************************************************/
/*  ucaps.h                                                              */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//satan invented unicode?
#define CAPS_LEN 666

static const int caps_table[CAPS_LEN][2] = {
	{ 0x0061, 0x0041 },
	{ 0x0062, 0x0042 },
	{ 0x0063, 0x0043 },
	{ 0x0064, 0x0044 },
	{ 0x0065, 0x0045 },
	{ 0x0066, 0x0046 },
	{ 0x0067, 0x0047 },
	{ 0x0068, 0x0048 },
	{ 0x0069, 0x0049 },
	{ 0x006A, 0x004A },
	{ 0x006B, 0x004B },
	{ 0x006C, 0x004C },
	{ 0x006D, 0x004D },
	{ 0x006E, 0x004E },
	{ 0x006F, 0x004F },
	{ 0x0070, 0x0050 },
	{ 0x0071, 0x0051 },
	{ 0x0072, 0x0052 },
	{ 0x0073, 0x0053 },
	{ 0x0074, 0x0054 },
	{ 0x0075, 0x0055 },
	{ 0x0076, 0x0056 },
	{ 0x0077, 0x0057 },
	{ 0x0078, 0x0058 },
	{ 0x0079, 0x0059 },
	{ 0x007A, 0x005A },
	{ 0x00E0, 0x00C0 },
	{ 0x00E1, 0x00C1 },
	{ 0x00E2, 0x00C2 },
	{ 0x00E3, 0x00C3 },
	{ 0x00E4, 0x00C4 },
	{ 0x00E5, 0x00C5 },
	{ 0x00E6, 0x00C6 },
	{ 0x00E7, 0x00C7 },
	{ 0x00E8, 0x00C8 },
	{ 0x00E9, 0x00C9 },
	{ 0x00EA, 0x00CA },
	{ 0x00EB, 0x00CB },
	{ 0x00EC, 0x00CC },
	{ 0x00ED, 0x00CD },
	{ 0x00EE, 0x00CE },
	{ 0x00EF, 0x00CF },
	{ 0x00F0, 0x00D0 },
	{ 0x00F1, 0x00D1 },
	{ 0x00F2, 0x00D2 },
	{ 0x00F3, 0x00D3 },
	{ 0x00F4, 0x00D4 },
	{ 0x00F5, 0x00D5 },
	{ 0x00F6, 0x00D6 },
	{ 0x00F8, 0x00D8 },
	{ 0x00F9, 0x00D9 },
	{ 0x00FA, 0x00DA },
	{ 0x00FB, 0x00DB },
	{ 0x00FC, 0x00DC },
	{ 0x00FD, 0x00DD },
	{ 0x00FE, 0x00DE },
	{ 0x00FF, 0x0178 },
	{ 0x0101, 0x0100 },
	{ 0x0103, 0x0102 },
	{ 0x0105, 0x0104 },
	{ 0x0107, 0x0106 },
	{ 0x0109, 0x0108 },
	{ 0x010B, 0x010A },
	{ 0x010D, 0x010C },
	{ 0x010F, 0x010E },
	{ 0x0111, 0x0110 },
	{ 0x0113, 0x0112 },
	{ 0x0115, 0x0114 },
	{ 0x0117, 0x0116 },
	{ 0x0119, 0x0118 },
	{ 0x011B, 0x011A },
	{ 0x011D, 0x011C },
	{ 0x011F, 0x011E },
	{ 0x0121, 0x0120 },
	{ 0x0123, 0x0122 },
	{ 0x0125, 0x0124 },
	{ 0x0127, 0x0126 },
	{ 0x0129, 0x0128 },
	{ 0x012B, 0x012A },
	{ 0x012D, 0x012C },
	{ 0x012F, 0x012E },
	{ 0x0131, 0x0049 },
	{ 0x0133, 0x0132 },
	{ 0x0135, 0x0134 },
	{ 0x0137, 0x0136 },
	{ 0x013A, 0x0139 },
	{ 0x013C, 0x013B },
	{ 0x013E, 0x013D },
	{ 0x0140, 0x013F },
	{ 0x0142, 0x0141 },
	{ 0x0144, 0x0143 },
	{ 0x0146, 0x0145 },
	{ 0x0148, 0x0147 },
	{ 0x014B, 0x014A },
	{ 0x014D, 0x014C },
	{ 0x014F, 0x014E },
	{ 0x0151, 0x0150 },
	{ 0x0153, 0x0152 },
	{ 0x0155, 0x0154 },
	{ 0x0157, 0x0156 },
	{ 0x0159, 0x0158 },
	{ 0x015B, 0x015A },
	{ 0x015D, 0x015C },
	{ 0x015F, 0x015E },
	{ 0x0161, 0x0160 },
	{ 0x0163, 0x0162 },
	{ 0x0165, 0x0164 },
	{ 0x0167, 0x0166 },
	{ 0x0169, 0x0168 },
	{ 0x016B, 0x016A },
	{ 0x016D, 0x016C },
	{ 0x016F, 0x016E },
	{ 0x0171, 0x0170 },
	{ 0x0173, 0x0172 },
	{ 0x0175, 0x0174 },
	{ 0x0177, 0x0176 },
	{ 0x017A, 0x0179 },
	{ 0x017C, 0x017B },
	{ 0x017E, 0x017D },
	{ 0x0183, 0x0182 },
	{ 0x0185, 0x0184 },
	{ 0x0188, 0x0187 },
	{ 0x018C, 0x018B },
	{ 0x0192, 0x0191 },
	{ 0x0199, 0x0198 },
	{ 0x01A1, 0x01A0 },
	{ 0x01A3, 0x01A2 },
	{ 0x01A5, 0x01A4 },
	{ 0x01A8, 0x01A7 },
	{ 0x01AD, 0x01AC },
	{ 0x01B0, 0x01AF },
	{ 0x01B4, 0x01B3 },
	{ 0x01B6, 0x01B5 },
	{ 0x01B9, 0x01B8 },
	{ 0x01BD, 0x01BC },
	{ 0x01C6, 0x01C4 },
	{ 0x01C9, 0x01C7 },
	{ 0x01CC, 0x01CA },
	{ 0x01CE, 0x01CD },
	{ 0x01D0, 0x01CF },
	{ 0x01D2, 0x01D1 },
	{ 0x01D4, 0x01D3 },
	{ 0x01D6, 0x01D5 },
	{ 0x01D8, 0x01D7 },
	{ 0x01DA, 0x01D9 },
	{ 0x01DC, 0x01DB },
	{ 0x01DF, 0x01DE },
	{ 0x01E1, 0x01E0 },
	{ 0x01E3, 0x01E2 },
	{ 0x01E5, 0x01E4 },
	{ 0x01E7, 0x01E6 },
	{ 0x01E9, 0x01E8 },
	{ 0x01EB, 0x01EA },
	{ 0x01ED, 0x01EC },
	{ 0x01EF, 0x01EE },
	{ 0x01F3, 0x01F1 },
	{ 0x01F5, 0x01F4 },
	{ 0x01FB, 0x01FA },
	{ 0x01FD, 0x01FC },
	{ 0x01FF, 0x01FE },
	{ 0x0201, 0x0200 },
	{ 0x0203, 0x0202 },
	{ 0x0205, 0x0204 },
	{ 0x0207, 0x0206 },
	{ 0x0209, 0x0208 },
	{ 0x020B, 0x020A },
	{ 0x020D, 0x020C },
	{ 0x020F, 0x020E },
	{ 0x0211, 0x0210 },
	{ 0x0213, 0x0212 },
	{ 0x0215, 0x0214 },
	{ 0x0217, 0x0216 },
	{ 0x0253, 0x0181 },
	{ 0x0254, 0x0186 },
	{ 0x0257, 0x018A },
	{ 0x0258, 0x018E },
	{ 0x0259, 0x018F },
	{ 0x025B, 0x0190 },
	{ 0x0260, 0x0193 },
	{ 0x0263, 0x0194 },
	{ 0x0268, 0x0197 },
	{ 0x0269, 0x0196 },
	{ 0x026F, 0x019C },
	{ 0x0272, 0x019D },
	{ 0x0275, 0x019F },
	{ 0x0283, 0x01A9 },
	{ 0x0288, 0x01AE },
	{ 0x028A, 0x01B1 },
	{ 0x028B, 0x01B2 },
	{ 0x0292, 0x01B7 },
	{ 0x03AC, 0x0386 },
	{ 0x03AD, 0x0388 },
	{ 0x03AE, 0x0389 },
	{ 0x03AF, 0x038A },
	{ 0x03B1, 0x0391 },
	{ 0x03B2, 0x0392 },
	{ 0x03B3, 0x0393 },
	{ 0x03B4, 0x0394 },
	{ 0x03B5, 0x0395 },
	{ 0x03B6, 0x0396 },
	{ 0x03B7, 0x0397 },
	{ 0x03B8, 0x0398 },
	{ 0x03B9, 0x0399 },
	{ 0x03BA, 0x039A },
	{ 0x03BB, 0x039B },
	{ 0x03BC, 0x039C },
	{ 0x03BD, 0x039D },
	{ 0x03BE, 0x039E },
	{ 0x03BF, 0x039F },
	{ 0x03C0, 0x03A0 },
	{ 0x03C1, 0x03A1 },
	{ 0x03C3, 0x03A3 },
	{ 0x03C4, 0x03A4 },
	{ 0x03C5, 0x03A5 },
	{ 0x03C6, 0x03A6 },
	{ 0x03C7, 0x03A7 },
	{ 0x03C8, 0x03A8 },
	{ 0x03C9, 0x03A9 },
	{ 0x03CA, 0x03AA },
	{ 0x03CB, 0x03AB },
	{ 0x03CC, 0x038C },
	{ 0x03CD, 0x038E },
	{ 0x03CE, 0x038F },
	{ 0x03E3, 0x03E2 },
	{ 0x03E5, 0x03E4 },
	{ 0x03E7, 0x03E6 },
	{ 0x03E9, 0x03E8 },
	{ 0x03EB, 0x03EA },
	{ 0x03ED, 0x03EC },
	{ 0x03EF, 0x03EE },
	{ 0x0430, 0x0410 },
	{ 0x0431, 0x0411 },
	{ 0x0432, 0x0412 },
	{ 0x0433, 0x0413 },
	{ 0x0434, 0x0414 },
	{ 0x0435, 0x0415 },
	{ 0x0436, 0x0416 },
	{ 0x0437, 0x0417 },
	{ 0x0438, 0x0418 },
	{ 0x0439, 0x0419 },
	{ 0x043A, 0x041A },
	{ 0x043B, 0x041B },
	{ 0x043C, 0x041C },
	{ 0x043D, 0x041D },
	{ 0x043E, 0x041E },
	{ 0x043F, 0x041F },
	{ 0x0440, 0x0420 },
	{ 0x0441, 0x0421 },
	{ 0x0442, 0x0422 },
	{ 0x0443, 0x0423 },
	{ 0x0444, 0x0424 },
	{ 0x0445, 0x0425 },
	{ 0x0446, 0x0426 },
	{ 0x0447, 0x0427 },
	{ 0x0448, 0x0428 },
	{ 0x0449, 0x0429 },
	{ 0x044A, 0x042A },
	{ 0x044B, 0x042B },
	{ 0x044C, 0x042C },
	{ 0x044D, 0x042D },
	{ 0x044E, 0x042E },
	{ 0x044F, 0x042F },
	{ 0x0451, 0x0401 },
	{ 0x0452, 0x0402 },
	{ 0x0453, 0x0403 },
	{ 0x0454, 0x0404 },
	{ 0x0455, 0x0405 },
	{ 0x0456, 0x0406 },
	{ 0x0457, 0x0407 },
	{ 0x0458, 0x0408 },
	{ 0x0459, 0x0409 },
	{ 0x045A, 0x040A },
	{ 0x045B, 0x040B },
	{ 0x045C, 0x040C },
	{ 0x045E, 0x040E },
	{ 0x045F, 0x040F },
	{ 0x0461, 0x0460 },
	{ 0x0463, 0x0462 },
	{ 0x0465, 0x0464 },
	{ 0x0467, 0x0466 },
	{ 0x0469, 0x0468 },
	{ 0x046B, 0x046A },
	{ 0x046D, 0x046C },
	{ 0x046F, 0x046E },
	{ 0x0471, 0x0470 },
	{ 0x0473, 0x0472 },
	{ 0x0475, 0x0474 },
	{ 0x0477, 0x0476 },
	{ 0x0479, 0x0478 },
	{ 0x047B, 0x047A },
	{ 0x047D, 0x047C },
	{ 0x047F, 0x047E },
	{ 0x0481, 0x0480 },
	{ 0x0491, 0x0490 },
	{ 0x0493, 0x0492 },
	{ 0x0495, 0x0494 },
	{ 0x0497, 0x0496 },
	{ 0x0499, 0x0498 },
	{ 0x049B, 0x049A },
	{ 0x049D, 0x049C },
	{ 0x049F, 0x049E },
	{ 0x04A1, 0x04A0 },
	{ 0x04A3, 0x04A2 },
	{ 0x04A5, 0x04A4 },
	{ 0x04A7, 0x04A6 },
	{ 0x04A9, 0x04A8 },
	{ 0x04AB, 0x04AA },
	{ 0x04AD, 0x04AC },
	{ 0x04AF, 0x04AE },
	{ 0x04B1, 0x04B0 },
	{ 0x04B3, 0x04B2 },
	{ 0x04B5, 0x04B4 },
	{ 0x04B7, 0x04B6 },
	{ 0x04B9, 0x04B8 },
	{ 0x04BB, 0x04BA },
	{ 0x04BD, 0x04BC },
	{ 0x04BF, 0x04BE },
	{ 0x04C2, 0x04C1 },
	{ 0x04C4, 0x04C3 },
	{ 0x04C8, 0x04C7 },
	{ 0x04CC, 0x04CB },
	{ 0x04D1, 0x04D0 },
	{ 0x04D3, 0x04D2 },
	{ 0x04D5, 0x04D4 },
	{ 0x04D7, 0x04D6 },
	{ 0x04D9, 0x04D8 },
	{ 0x04DB, 0x04DA },
	{ 0x04DD, 0x04DC },
	{ 0x04DF, 0x04DE },
	{ 0x04E1, 0x04E0 },
	{ 0x04E3, 0x04E2 },
	{ 0x04E5, 0x04E4 },
	{ 0x04E7, 0x04E6 },
	{ 0x04E9, 0x04E8 },
	{ 0x04EB, 0x04EA },
	{ 0x04EF, 0x04EE },
	{ 0x04F1, 0x04F0 },
	{ 0x04F3, 0x04F2 },
	{ 0x04F5, 0x04F4 },
	{ 0x04F9, 0x04F8 },
	{ 0x0561, 0x0531 },
	{ 0x0562, 0x0532 },
	{ 0x0563, 0x0533 },
	{ 0x0564, 0x0534 },
	{ 0x0565, 0x0535 },
	{ 0x0566, 0x0536 },
	{ 0x0567, 0x0537 },
	{ 0x0568, 0x0538 },
	{ 0x0569, 0x0539 },
	{ 0x056A, 0x053A },
	{ 0x056B, 0x053B },
	{ 0x056C, 0x053C },
	{ 0x056D, 0x053D },
	{ 0x056E, 0x053E },
	{ 0x056F, 0x053F },
	{ 0x0570, 0x0540 },
	{ 0x0571, 0x0541 },
	{ 0x0572, 0x0542 },
	{ 0x0573, 0x0543 },
	{ 0x0574, 0x0544 },
	{ 0x0575, 0x0545 },
	{ 0x0576, 0x0546 },
	{ 0x0577, 0x0547 },
	{ 0x0578, 0x0548 },
	{ 0x0579, 0x0549 },
	{ 0x057A, 0x054A },
	{ 0x057B, 0x054B },
	{ 0x057C, 0x054C },
	{ 0x057D, 0x054D },
	{ 0x057E, 0x054E },
	{ 0x057F, 0x054F },
	{ 0x0580, 0x0550 },
	{ 0x0581, 0x0551 },
	{ 0x0582, 0x0552 },
	{ 0x0583, 0x0553 },
	{ 0x0584, 0x0554 },
	{ 0x0585, 0x0555 },
	{ 0x0586, 0x0556 },
	{ 0x10D0, 0x10A0 },
	{ 0x10D1, 0x10A1 },
	{ 0x10D2, 0x10A2 },
	{ 0x10D3, 0x10A3 },
	{ 0x10D4, 0x10A4 },
	{ 0x10D5, 0x10A5 },
	{ 0x10D6, 0x10A6 },
	{ 0x10D7, 0x10A7 },
	{ 0x10D8, 0x10A8 },
	{ 0x10D9, 0x10A9 },
	{ 0x10DA, 0x10AA },
	{ 0x10DB, 0x10AB },
	{ 0x10DC, 0x10AC },
	{ 0x10DD, 0x10AD },
	{ 0x10DE, 0x10AE },
	{ 0x10DF, 0x10AF },
	{ 0x10E0, 0x10B0 },
	{ 0x10E1, 0x10B1 },
	{ 0x10E2, 0x10B2 },
	{ 0x10E3, 0x10B3 },
	{ 0x10E4, 0x10B4 },
	{ 0x10E5, 0x10B5 },
	{ 0x10E6, 0x10B6 },
	{ 0x10E7, 0x10B7 },
	{ 0x10E8, 0x10B8 },
	{ 0x10E9, 0x10B9 },
	{ 0x10EA, 0x10BA },
	{ 0x10EB, 0x10BB },
	{ 0x10EC, 0x10BC },
	{ 0x10ED, 0x10BD },
	{ 0x10EE, 0x10BE },
	{ 0x10EF, 0x10BF },
	{ 0x10F0, 0x10C0 },
	{ 0x10F1, 0x10C1 },
	{ 0x10F2, 0x10C2 },
	{ 0x10F3, 0x10C3 },
	{ 0x10F4, 0x10C4 },
	{ 0x10F5, 0x10C5 },
	{ 0x1E01, 0x1E00 },
	{ 0x1E03, 0x1E02 },
	{ 0x1E05, 0x1E04 },
	{ 0x1E07, 0x1E06 },
	{ 0x1E09, 0x1E08 },
	{ 0x1E0B, 0x1E0A },
	{ 0x1E0D, 0x1E0C },
	{ 0x1E0F, 0x1E0E },
	{ 0x1E11, 0x1E10 },
	{ 0x1E13, 0x1E12 },
	{ 0x1E15, 0x1E14 },
	{ 0x1E17, 0x1E16 },
	{ 0x1E19, 0x1E18 },
	{ 0x1E1B, 0x1E1A },
	{ 0x1E1D, 0x1E1C },
	{ 0x1E1F, 0x1E1E },
	{ 0x1E21, 0x1E20 },
	{ 0x1E23, 0x1E22 },
	{ 0x1E25, 0x1E24 },
	{ 0x1E27, 0x1E26 },
	{ 0x1E29, 0x1E28 },
	{ 0x1E2B, 0x1E2A },
	{ 0x1E2D, 0x1E2C },
	{ 0x1E2F, 0x1E2E },
	{ 0x1E31, 0x1E30 },
	{ 0x1E33, 0x1E32 },
	{ 0x1E35, 0x1E34 },
	{ 0x1E37, 0x1E36 },
	{ 0x1E39, 0x1E38 },
	{ 0x1E3B, 0x1E3A },
	{ 0x1E3D, 0x1E3C },
	{ 0x1E3F, 0x1E3E },
	{ 0x1E41, 0x1E40 },
	{ 0x1E43, 0x1E42 },
	{ 0x1E45, 0x1E44 },
	{ 0x1E47, 0x1E46 },
	{ 0x1E49, 0x1E48 },
	{ 0x1E4B, 0x1E4A },
	{ 0x1E4D, 0x1E4C },
	{ 0x1E4F, 0x1E4E },
	{ 0x1E51, 0x1E50 },
	{ 0x1E53, 0x1E52 },
	{ 0x1E55, 0x1E54 },
	{ 0x1E57, 0x1E56 },
	{ 0x1E59, 0x1E58 },
	{ 0x1E5B, 0x1E5A },
	{ 0x1E5D, 0x1E5C },
	{ 0x1E5F, 0x1E5E },
	{ 0x1E61, 0x1E60 },
	{ 0x1E63, 0x1E62 },
	{ 0x1E65, 0x1E64 },
	{ 0x1E67, 0x1E66 },
	{ 0x1E69, 0x1E68 },
	{ 0x1E6B, 0x1E6A },
	{ 0x1E6D, 0x1E6C },
	{ 0x1E6F, 0x1E6E },
	{ 0x1E71, 0x1E70 },
	{ 0x1E73, 0x1E72 },
	{ 0x1E75, 0x1E74 },
	{ 0x1E77, 0x1E76 },
	{ 0x1E79, 0x1E78 },
	{ 0x1E7B, 0x1E7A },
	{ 0x1E7D, 0x1E7C },
	{ 0x1E7F, 0x1E7E },
	{ 0x1E81, 0x1E80 },
	{ 0x1E83, 0x1E82 },
	{ 0x1E85, 0x1E84 },
	{ 0x1E87, 0x1E86 },
	{ 0x1E89, 0x1E88 },
	{ 0x1E8B, 0x1E8A },
	{ 0x1E8D, 0x1E8C },
	{ 0x1E8F, 0x1E8E },
	{ 0x1E91, 0x1E90 },
	{ 0x1E93, 0x1E92 },
	{ 0x1E95, 0x1E94 },
	{ 0x1EA1, 0x1EA0 },
	{ 0x1EA3, 0x1EA2 },
	{ 0x1EA5, 0x1EA4 },
	{ 0x1EA7, 0x1EA6 },
	{ 0x1EA9, 0x1EA8 },
	{ 0x1EAB, 0x1EAA },
	{ 0x1EAD, 0x1EAC },
	{ 0x1EAF, 0x1EAE },
	{ 0x1EB1, 0x1EB0 },
	{ 0x1EB3, 0x1EB2 },
	{ 0x1EB5, 0x1EB4 },
	{ 0x1EB7, 0x1EB6 },
	{ 0x1EB9, 0x1EB8 },
	{ 0x1EBB, 0x1EBA },
	{ 0x1EBD, 0x1EBC },
	{ 0x1EBF, 0x1EBE },
	{ 0x1EC1, 0x1EC0 },
	{ 0x1EC3, 0x1EC2 },
	{ 0x1EC5, 0x1EC4 },
	{ 0x1EC7, 0x1EC6 },
	{ 0x1EC9, 0x1EC8 },
	{ 0x1ECB, 0x1ECA },
	{ 0x1ECD, 0x1ECC },
	{ 0x1ECF, 0x1ECE },
	{ 0x1ED1, 0x1ED0 },
	{ 0x1ED3, 0x1ED2 },
	{ 0x1ED5, 0x1ED4 },
	{ 0x1ED7, 0x1ED6 },
	{ 0x1ED9, 0x1ED8 },
	{ 0x1EDB, 0x1EDA },
	{ 0x1EDD, 0x1EDC },
	{ 0x1EDF, 0x1EDE },
	{ 0x1EE1, 0x1EE0 },
	{ 0x1EE3, 0x1EE2 },
	{ 0x1EE5, 0x1EE4 },
	{ 0x1EE7, 0x1EE6 },
	{ 0x1EE9, 0x1EE8 },
	{ 0x1EEB, 0x1EEA },
	{ 0x1EED, 0x1EEC },
	{ 0x1EEF, 0x1EEE },
	{ 0x1EF1, 0x1EF0 },
	{ 0x1EF3, 0x1EF2 },
	{ 0x1EF5, 0x1EF4 },
	{ 0x1EF7, 0x1EF6 },
	{ 0x1EF9, 0x1EF8 },
	{ 0x1F00, 0x1F08 },
	{ 0x1F01, 0x1F09 },
	{ 0x1F02, 0x1F0A },
	{ 0x1F03, 0x1F0B },
	{ 0x1F04, 0x1F0C },
	{ 0x1F05, 0x1F0D },
	{ 0x1F06, 0x1F0E },
	{ 0x1F07, 0x1F0F },
	{ 0x1F10, 0x1F18 },
	{ 0x1F11, 0x1F19 },
	{ 0x1F12, 0x1F1A },
	{ 0x1F13, 0x1F1B },
	{ 0x1F14, 0x1F1C },
	{ 0x1F15, 0x1F1D },
	{ 0x1F20, 0x1F28 },
	{ 0x1F21, 0x1F29 },
	{ 0x1F22, 0x1F2A },
	{ 0x1F23, 0x1F2B },
	{ 0x1F24, 0x1F2C },
	{ 0x1F25, 0x1F2D },
	{ 0x1F26, 0x1F2E },
	{ 0x1F27, 0x1F2F },
	{ 0x1F30, 0x1F38 },
	{ 0x1F31, 0x1F39 },
	{ 0x1F32, 0x1F3A },
	{ 0x1F33, 0x1F3B },
	{ 0x1F34, 0x1F3C },
	{ 0x1F35, 0x1F3D },
	{ 0x1F36, 0x1F3E },
	{ 0x1F37, 0x1F3F },
	{ 0x1F40, 0x1F48 },
	{ 0x1F41, 0x1F49 },
	{ 0x1F42, 0x1F4A },
	{ 0x1F43, 0x1F4B },
	{ 0x1F44, 0x1F4C },
	{ 0x1F45, 0x1F4D },
	{ 0x1F51, 0x1F59 },
	{ 0x1F53, 0x1F5B },
	{ 0x1F55, 0x1F5D },
	{ 0x1F57, 0x1F5F },
	{ 0x1F60, 0x1F68 },
	{ 0x1F61, 0x1F69 },
	{ 0x1F62, 0x1F6A },
	{ 0x1F63, 0x1F6B },
	{ 0x1F64, 0x1F6C },
	{ 0x1F65, 0x1F6D },
	{ 0x1F66, 0x1F6E },
	{ 0x1F67, 0x1F6F },
	{ 0x1F80, 0x1F88 },
	{ 0x1F81, 0x1F89 },
	{ 0x1F82, 0x1F8A },
	{ 0x1F83, 0x1F8B },
	{ 0x1F84, 0x1F8C },
	{ 0x1F85, 0x1F8D },
	{ 0x1F86, 0x1F8E },
	{ 0x1F87, 0x1F8F },
	{ 0x1F90, 0x1F98 },
	{ 0x1F91, 0x1F99 },
	{ 0x1F92, 0x1F9A },
	{ 0x1F93, 0x1F9B },
	{ 0x1F94, 0x1F9C },
	{ 0x1F95, 0x1F9D },
	{ 0x1F96, 0x1F9E },
	{ 0x1F97, 0x1F9F },
	{ 0x1FA0, 0x1FA8 },
	{ 0x1FA1, 0x1FA9 },
	{ 0x1FA2, 0x1FAA },
	{ 0x1FA3, 0x1FAB },
	{ 0x1FA4, 0x1FAC },
	{ 0x1FA5, 0x1FAD },
	{ 0x1FA6, 0x1FAE },
	{ 0x1FA7, 0x1FAF },
	{ 0x1FB0, 0x1FB8 },
	{ 0x1FB1, 0x1FB9 },
	{ 0x1FD0, 0x1FD8 },
	{ 0x1FD1, 0x1FD9 },
	{ 0x1FE0, 0x1FE8 },
	{ 0x1FE1, 0x1FE9 },
	{ 0x24D0, 0x24B6 },
	{ 0x24D1, 0x24B7 },
	{ 0x24D2, 0x24B8 },
	{ 0x24D3, 0x24B9 },
	{ 0x24D4, 0x24BA },
	{ 0x24D5, 0x24BB },
	{ 0x24D6, 0x24BC },
	{ 0x24D7, 0x24BD },
	{ 0x24D8, 0x24BE },
	{ 0x24D9, 0x24BF },
	{ 0x24DA, 0x24C0 },
	{ 0x24DB, 0x24C1 },
	{ 0x24DC, 0x24C2 },
	{ 0x24DD, 0x24C3 },
	{ 0x24DE, 0x24C4 },
	{ 0x24DF, 0x24C5 },
	{ 0x24E0, 0x24C6 },
	{ 0x24E1, 0x24C7 },
	{ 0x24E2, 0x24C8 },
	{ 0x24E3, 0x24C9 },
	{ 0x24E4, 0x24CA },
	{ 0x24E5, 0x24CB },
	{ 0x24E6, 0x24CC },
	{ 0x24E7, 0x24CD },
	{ 0x24E8, 0x24CE },
	{ 0x24E9, 0x24CF },
	{ 0xFF41, 0xFF21 },
	{ 0xFF42, 0xFF22 },
	{ 0xFF43, 0xFF23 },
	{ 0xFF44, 0xFF24 },
	{ 0xFF45, 0xFF25 },
	{ 0xFF46, 0xFF26 },
	{ 0xFF47, 0xFF27 },
	{ 0xFF48, 0xFF28 },
	{ 0xFF49, 0xFF29 },
	{ 0xFF4A, 0xFF2A },
	{ 0xFF4B, 0xFF2B },
	{ 0xFF4C, 0xFF2C },
	{ 0xFF4D, 0xFF2D },
	{ 0xFF4E, 0xFF2E },
	{ 0xFF4F, 0xFF2F },
	{ 0xFF50, 0xFF30 },
	{ 0xFF51, 0xFF31 },
	{ 0xFF52, 0xFF32 },
	{ 0xFF53, 0xFF33 },
	{ 0xFF54, 0xFF34 },
	{ 0xFF55, 0xFF35 },
	{ 0xFF56, 0xFF36 },
	{ 0xFF57, 0xFF37 },
	{ 0xFF58, 0xFF38 },
	{ 0xFF59, 0xFF39 },
	{ 0xFF5A, 0xFF3A },
};

static const int reverse_caps_table[CAPS_LEN - 1][2] = {
	{ 0x0041, 0x0061 },
	{ 0x0042, 0x0062 },
	{ 0x0043, 0x0063 },
	{ 0x0044, 0x0064 },
	{ 0x0045, 0x0065 },
	{ 0x0046, 0x0066 },
	{ 0x0047, 0x0067 },
	{ 0x0048, 0x0068 },
	{ 0x0049, 0x0069 },
	// { 0x0049, 0x0131 }, // dotless I
	{ 0x004A, 0x006A },
	{ 0x004B, 0x006B },
	{ 0x004C, 0x006C },
	{ 0x004D, 0x006D },
	{ 0x004E, 0x006E },
	{ 0x004F, 0x006F },
	{ 0x0050, 0x0070 },
	{ 0x0051, 0x0071 },
	{ 0x0052, 0x0072 },
	{ 0x0053, 0x0073 },
	{ 0x0054, 0x0074 },
	{ 0x0055, 0x0075 },
	{ 0x0056, 0x0076 },
	{ 0x0057, 0x0077 },
	{ 0x0058, 0x0078 },
	{ 0x0059, 0x0079 },
	{ 0x005A, 0x007A },
	{ 0x00C0, 0x00E0 },
	{ 0x00C1, 0x00E1 },
	{ 0x00C2, 0x00E2 },
	{ 0x00C3, 0x00E3 },
	{ 0x00C4, 0x00E4 },
	{ 0x00C5, 0x00E5 },
	{ 0x00C6, 0x00E6 },
	{ 0x00C7, 0x00E7 },
	{ 0x00C8, 0x00E8 },
	{ 0x00C9, 0x00E9 },
	{ 0x00CA, 0x00EA },
	{ 0x00CB, 0x00EB },
	{ 0x00CC, 0x00EC },
	{ 0x00CD, 0x00ED },
	{ 0x00CE, 0x00EE },
	{ 0x00CF, 0x00EF },
	{ 0x00D0, 0x00F0 },
	{ 0x00D1, 0x00F1 },
	{ 0x00D2, 0x00F2 },
	{ 0x00D3, 0x00F3 },
	{ 0x00D4, 0x00F4 },
	{ 0x00D5, 0x00F5 },
	{ 0x00D6, 0x00F6 },
	{ 0x00D8, 0x00F8 },
	{ 0x00D9, 0x00F9 },
	{ 0x00DA, 0x00FA },
	{ 0x00DB, 0x00FB },
	{ 0x00DC, 0x00FC },
	{ 0x00DD, 0x00FD },
	{ 0x00DE, 0x00FE },
	{ 0x0100, 0x0101 },
	{ 0x0102, 0x0103 },
	{ 0x0104, 0x0105 },
	{ 0x0106, 0x0107 },
	{ 0x0108, 0x0109 },
	{ 0x010A, 0x010B },
	{ 0x010C, 0x010D },
	{ 0x010E, 0x010F },
	{ 0x0110, 0x0111 },
	{ 0x0112, 0x0113 },
	{ 0x0114, 0x0115 },
	{ 0x0116, 0x0117 },
	{ 0x0118, 0x0119 },
	{ 0x011A, 0x011B },
	{ 0x011C, 0x011D },
	{ 0x011E, 0x011F },
	{ 0x0120, 0x0121 },
	{ 0x0122, 0x0123 },
	{ 0x0124, 0x0125 },
	{ 0x0126, 0x0127 },
	{ 0x0128, 0x0129 },
	{ 0x012A, 0x012B },
	{ 0x012C, 0x012D },
	{ 0x012E, 0x012F },
	{ 0x0132, 0x0133 },
	{ 0x0134, 0x0135 },
	{ 0x0136, 0x0137 },
	{ 0x0139, 0x013A },
	{ 0x013B, 0x013C },
	{ 0x013D, 0x013E },
	{ 0x013F, 0x0140 },
	{ 0x0141, 0x0142 },
	{ 0x0143, 0x0144 },
	{ 0x0145, 0x0146 },
	{ 0x0147, 0x0148 },
	{ 0x014A, 0x014B },
	{ 0x014C, 0x014D },
	{ 0x014E, 0x014F },
	{ 0x0150, 0x0151 },
	{ 0x0152, 0x0153 },
	{ 0x0154, 0x0155 },
	{ 0x0156, 0x0157 },
	{ 0x0158, 0x0159 },
	{ 0x015A, 0x015B },
	{ 0x015C, 0x015D },
	{ 0x015E, 0x015F },
	{ 0x0160, 0x0161 },
	{ 0x0162, 0x0163 },
	{ 0x0164, 0x0165 },
	{ 0x0166, 0x0167 },
	{ 0x0168, 0x0169 },
	{ 0x016A, 0x016B },
	{ 0x016C, 0x016D },
	{ 0x016E, 0x016F },
	{ 0x0170, 0x0171 },
	{ 0x0172, 0x0173 },
	{ 0x0174, 0x0175 },
	{ 0x0176, 0x0177 },
	{ 0x0178, 0x00FF },
	{ 0x0179, 0x017A },
	{ 0x017B, 0x017C },
	{ 0x017D, 0x017E },
	{ 0x0181, 0x0253 },
	{ 0x0182, 0x0183 },
	{ 0x0184, 0x0185 },
	{ 0x0186, 0x0254 },
	{ 0x0187, 0x0188 },
	{ 0x018A, 0x0257 },
	{ 0x018B, 0x018C },
	{ 0x018E, 0x0258 },
	{ 0x018F, 0x0259 },
	{ 0x0190, 0x025B },
	{ 0x0191, 0x0192 },
	{ 0x0193, 0x0260 },
	{ 0x0194, 0x0263 },
	{ 0x0196, 0x0269 },
	{ 0x0197, 0x0268 },
	{ 0x0198, 0x0199 },
	{ 0x019C, 0x026F },
	{ 0x019D, 0x0272 },
	{ 0x019F, 0x0275 },
	{ 0x01A0, 0x01A1 },
	{ 0x01A2, 0x01A3 },
	{ 0x01A4, 0x01A5 },
	{ 0x01A7, 0x01A8 },
	{ 0x01A9, 0x0283 },
	{ 0x01AC, 0x01AD },
	{ 0x01AE, 0x0288 },
	{ 0x01AF, 0x01B0 },
	{ 0x01B1, 0x028A },
	{ 0x01B2, 0x028B },
	{ 0x01B3, 0x01B4 },
	{ 0x01B5, 0x01B6 },
	{ 0x01B7, 0x0292 },
	{ 0x01B8, 0x01B9 },
	{ 0x01BC, 0x01BD },
	{ 0x01C4, 0x01C6 },
	{ 0x01C7, 0x01C9 },
	{ 0x01CA, 0x01CC },
	{ 0x01CD, 0x01CE },
	{ 0x01CF, 0x01D0 },
	{ 0x01D1, 0x01D2 },
	{ 0x01D3, 0x01D4 },
	{ 0x01D5, 0x01D6 },
	{ 0x01D7, 0x01D8 },
	{ 0x01D9, 0x01DA },
	{ 0x01DB, 0x01DC },
	{ 0x01DE, 0x01DF },
	{ 0x01E0, 0x01E1 },
	{ 0x01E2, 0x01E3 },
	{ 0x01E4, 0x01E5 },
	{ 0x01E6, 0x01E7 },
	{ 0x01E8, 0x01E9 },
	{ 0x01EA, 0x01EB },
	{ 0x01EC, 0x01ED },
	{ 0x01EE, 0x01EF },
	{ 0x01F1, 0x01F3 },
	{ 0x01F4, 0x01F5 },
	{ 0x01FA, 0x01FB },
	{ 0x01FC, 0x01FD },
	{ 0x01FE, 0x01FF },
	{ 0x0200, 0x0201 },
	{ 0x0202, 0x0203 },
	{ 0x0204, 0x0205 },
	{ 0x0206, 0x0207 },
	{ 0x0208, 0x0209 },
	{ 0x020A, 0x020B },
	{ 0x020C, 0x020D },
	{ 0x020E, 0x020F },
	{ 0x0210, 0x0211 },
	{ 0x0212, 0x0213 },
	{ 0x0214, 0x0215 },
	{ 0x0216, 0x0217 },
	{ 0x0386, 0x03AC },
	{ 0x0388, 0x03AD },
	{ 0x0389, 0x03AE },
	{ 0x038A, 0x03AF },
	{ 0x038C, 0x03CC },
	{ 0x038E, 0x03CD },
	{ 0x038F, 0x03CE },
	{ 0x0391, 0x03B1 },
	{ 0x0392, 0x03B2 },
	{ 0x0393, 0x03B3 },
	{ 0x0394, 0x03B4 },
	{ 0x0395, 0x03B5 },
	{ 0x0396, 0x03B6 },
	{ 0x0397, 0x03B7 },
	{ 0x0398, 0x03B8 },
	{ 0x0399, 0x03B9 },
	{ 0x039A, 0x03BA },
	{ 0x039B, 0x03BB },
	{ 0x039C, 0x03BC },
	{ 0x039D, 0x03BD },
	{ 0x039E, 0x03BE },
	{ 0x039F, 0x03BF },
	{ 0x03A0, 0x03C0 },
	{ 0x03A1, 0x03C1 },
	{ 0x03A3, 0x03C3 },
	{ 0x03A4, 0x03C4 },
	{ 0x03A5, 0x03C5 },
	{ 0x03A6, 0x03C6 },
	{ 0x03A7, 0x03C7 },
	{ 0x03A8, 0x03C8 },
	{ 0x03A9, 0x03C9 },
	{ 0x03AA, 0x03CA },
	{ 0x03AB, 0x03CB },
	{ 0x03E2, 0x03E3 },
	{ 0x03E4, 0x03E5 },
	{ 0x03E6, 0x03E7 },
	{ 0x03E8, 0x03E9 },
	{ 0x03EA, 0x03EB },
	{ 0x03EC, 0x03ED },
	{ 0x03EE, 0x03EF },
	{ 0x0401, 0x0451 },
	{ 0x0402, 0x0452 },
	{ 0x0403, 0x0453 },
	{ 0x0404, 0x0454 },
	{ 0x0405, 0x0455 },
	{ 0x0406, 0x0456 },
	{ 0x0407, 0x0457 },
	{ 0x0408, 0x0458 },
	{ 0x0409, 0x0459 },
	{ 0x040A, 0x045A },
	{ 0x040B, 0x045B },
	{ 0x040C, 0x045C },
	{ 0x040E, 0x045E },
	{ 0x040F, 0x045F },
	{ 0x0410, 0x0430 },
	{ 0x0411, 0x0431 },
	{ 0x0412, 0x0432 },
	{ 0x0413, 0x0433 },
	{ 0x0414, 0x0434 },
	{ 0x0415, 0x0435 },
	{ 0x0416, 0x0436 },
	{ 0x0417, 0x0437 },
	{ 0x0418, 0x0438 },
	{ 0x0419, 0x0439 },
	{ 0x041A, 0x043A },
	{ 0x041B, 0x043B },
	{ 0x041C, 0x043C },
	{ 0x041D, 0x043D },
	{ 0x041E, 0x043E },
	{ 0x041F, 0x043F },
	{ 0x0420, 0x0440 },
	{ 0x0421, 0x0441 },
	{ 0x0422, 0x0442 },
	{ 0x0423, 0x0443 },
	{ 0x0424, 0x0444 },
	{ 0x0425, 0x0445 },
	{ 0x0426, 0x0446 },
	{ 0x0427, 0x0447 },
	{ 0x0428, 0x0448 },
	{ 0x0429, 0x0449 },
	{ 0x042A, 0x044A },
	{ 0x042B, 0x044B },
	{ 0x042C, 0x044C },
	{ 0x042D, 0x044D },
	{ 0x042E, 0x044E },
	{ 0x042F, 0x044F },
	{ 0x0460, 0x0461 },
	{ 0x0462, 0x0463 },
	{ 0x0464, 0x0465 },
	{ 0x0466, 0x0467 },
	{ 0x0468, 0x0469 },
	{ 0x046A, 0x046B },
	{ 0x046C, 0x046D },
	{ 0x046E, 0x046F },
	{ 0x0470, 0x0471 },
	{ 0x0472, 0x0473 },
	{ 0x0474, 0x0475 },
	{ 0x0476, 0x0477 },
	{ 0x0478, 0x0479 },
	{ 0x047A, 0x047B },
	{ 0x047C, 0x047D },
	{ 0x047E, 0x047F },
	{ 0x0480, 0x0481 },
	{ 0x0490, 0x0491 },
	{ 0x0492, 0x0493 },
	{ 0x0494, 0x0495 },
	{ 0x0496, 0x0497 },
	{ 0x0498, 0x0499 },
	{ 0x049A, 0x049B },
	{ 0x049C, 0x049D },
	{ 0x049E, 0x049F },
	{ 0x04A0, 0x04A1 },
	{ 0x04A2, 0x04A3 },
	{ 0x04A4, 0x04A5 },
	{ 0x04A6, 0x04A7 },
	{ 0x04A8, 0x04A9 },
	{ 0x04AA, 0x04AB },
	{ 0x04AC, 0x04AD },
	{ 0x04AE, 0x04AF },
	{ 0x04B0, 0x04B1 },
	{ 0x04B2, 0x04B3 },
	{ 0x04B4, 0x04B5 },
	{ 0x04B6, 0x04B7 },
	{ 0x04B8, 0x04B9 },
	{ 0x04BA, 0x04BB },
	{ 0x04BC, 0x04BD },
	{ 0x04BE, 0x04BF },
	{ 0x04C1, 0x04C2 },
	{ 0x04C3, 0x04C4 },
	{ 0x04C7, 0x04C8 },
	{ 0x04CB, 0x04CC },
	{ 0x04D0, 0x04D1 },
	{ 0x04D2, 0x04D3 },
	{ 0x04D4, 0x04D5 },
	{ 0x04D6, 0x04D7 },
	{ 0x04D8, 0x04D9 },
	{ 0x04DA, 0x04DB },
	{ 0x04DC, 0x04DD },
	{ 0x04DE, 0x04DF },
	{ 0x04E0, 0x04E1 },
	{ 0x04E2, 0x04E3 },
	{ 0x04E4, 0x04E5 },
	{ 0x04E6, 0x04E7 },
	{ 0x04E8, 0x04E9 },
	{ 0x04EA, 0x04EB },
	{ 0x04EE, 0x04EF },
	{ 0x04F0, 0x04F1 },
	{ 0x04F2, 0x04F3 },
	{ 0x04F4, 0x04F5 },
	{ 0x04F8, 0x04F9 },
	{ 0x0531, 0x0561 },
	{ 0x0532, 0x0562 },
	{ 0x0533, 0x0563 },
	{ 0x0534, 0x0564 },
	{ 0x0535, 0x0565 },
	{ 0x0536, 0x0566 },
	{ 0x0537, 0x0567 },
	{ 0x0538, 0x0568 },
	{ 0x0539, 0x0569 },
	{ 0x053A, 0x056A },
	{ 0x053B, 0x056B },
	{ 0x053C, 0x056C },
	{ 0x053D, 0x056D },
	{ 0x053E, 0x056E },
	{ 0x053F, 0x056F },
	{ 0x0540, 0x0570 },
	{ 0x0541, 0x0571 },
	{ 0x0542, 0x0572 },
	{ 0x0543, 0x0573 },
	{ 0x0544, 0x0574 },
	{ 0x0545, 0x0575 },
	{ 0x0546, 0x0576 },
	{ 0x0547, 0x0577 },
	{ 0x0548, 0x0578 },
	{ 0x0549, 0x0579 },
	{ 0x054A, 0x057A },
	{ 0x054B, 0x057B },
	{ 0x054C, 0x057C },
	{ 0x054D, 0x057D },
	{ 0x054E, 0x057E },
	{ 0x054F, 0x057F },
	{ 0x0550, 0x0580 },
	{ 0x0551, 0x0581 },
	{ 0x0552, 0x0582 },
	{ 0x0553, 0x0583 },
	{ 0x0554, 0x0584 },
	{ 0x0555, 0x0585 },
	{ 0x0556, 0x0586 },
	{ 0x10A0, 0x10D0 },
	{ 0x10A1, 0x10D1 },
	{ 0x10A2, 0x10D2 },
	{ 0x10A3, 0x10D3 },
	{ 0x10A4, 0x10D4 },
	{ 0x10A5, 0x10D5 },
	{ 0x10A6, 0x10D6 },
	{ 0x10A7, 0x10D7 },
	{ 0x10A8, 0x10D8 },
	{ 0x10A9, 0x10D9 },
	{ 0x10AA, 0x10DA },
	{ 0x10AB, 0x10DB },
	{ 0x10AC, 0x10DC },
	{ 0x10AD, 0x10DD },
	{ 0x10AE, 0x10DE },
	{ 0x10AF, 0x10DF },
	{ 0x10B0, 0x10E0 },
	{ 0x10B1, 0x10E1 },
	{ 0x10B2, 0x10E2 },
	{ 0x10B3, 0x10E3 },
	{ 0x10B4, 0x10E4 },
	{ 0x10B5, 0x10E5 },
	{ 0x10B6, 0x10E6 },
	{ 0x10B7, 0x10E7 },
	{ 0x10B8, 0x10E8 },
	{ 0x10B9, 0x10E9 },
	{ 0x10BA, 0x10EA },
	{ 0x10BB, 0x10EB },
	{ 0x10BC, 0x10EC },
	{ 0x10BD, 0x10ED },
	{ 0x10BE, 0x10EE },
	{ 0x10BF, 0x10EF },
	{ 0x10C0, 0x10F0 },
	{ 0x10C1, 0x10F1 },
	{ 0x10C2, 0x10F2 },
	{ 0x10C3, 0x10F3 },
	{ 0x10C4, 0x10F4 },
	{ 0x10C5, 0x10F5 },
	{ 0x1E00, 0x1E01 },
	{ 0x1E02, 0x1E03 },
	{ 0x1E04, 0x1E05 },
	{ 0x1E06, 0x1E07 },
	{ 0x1E08, 0x1E09 },
	{ 0x1E0A, 0x1E0B },
	{ 0x1E0C, 0x1E0D },
	{ 0x1E0E, 0x1E0F },
	{ 0x1E10, 0x1E11 },
	{ 0x1E12, 0x1E13 },
	{ 0x1E14, 0x1E15 },
	{ 0x1E16, 0x1E17 },
	{ 0x1E18, 0x1E19 },
	{ 0x1E1A, 0x1E1B },
	{ 0x1E1C, 0x1E1D },
	{ 0x1E1E, 0x1E1F },
	{ 0x1E20, 0x1E21 },
	{ 0x1E22, 0x1E23 },
	{ 0x1E24, 0x1E25 },
	{ 0x1E26, 0x1E27 },
	{ 0x1E28, 0x1E29 },
	{ 0x1E2A, 0x1E2B },
	{ 0x1E2C, 0x1E2D },
	{ 0x1E2E, 0x1E2F },
	{ 0x1E30, 0x1E31 },
	{ 0x1E32, 0x1E33 },
	{ 0x1E34, 0x1E35 },
	{ 0x1E36, 0x1E37 },
	{ 0x1E38, 0x1E39 },
	{ 0x1E3A, 0x1E3B },
	{ 0x1E3C, 0x1E3D },
	{ 0x1E3E, 0x1E3F },
	{ 0x1E40, 0x1E41 },
	{ 0x1E42, 0x1E43 },
	{ 0x1E44, 0x1E45 },
	{ 0x1E46, 0x1E47 },
	{ 0x1E48, 0x1E49 },
	{ 0x1E4A, 0x1E4B },
	{ 0x1E4C, 0x1E4D },
	{ 0x1E4E, 0x1E4F },
	{ 0x1E50, 0x1E51 },
	{ 0x1E52, 0x1E53 },
	{ 0x1E54, 0x1E55 },
	{ 0x1E56, 0x1E57 },
	{ 0x1E58, 0x1E59 },
	{ 0x1E5A, 0x1E5B },
	{ 0x1E5C, 0x1E5D },
	{ 0x1E5E, 0x1E5F },
	{ 0x1E60, 0x1E61 },
	{ 0x1E62, 0x1E63 },
	{ 0x1E64, 0x1E65 },
	{ 0x1E66, 0x1E67 },
	{ 0x1E68, 0x1E69 },
	{ 0x1E6A, 0x1E6B },
	{ 0x1E6C, 0x1E6D },
	{ 0x1E6E, 0x1E6F },
	{ 0x1E70, 0x1E71 },
	{ 0x1E72, 0x1E73 },
	{ 0x1E74, 0x1E75 },
	{ 0x1E76, 0x1E77 },
	{ 0x1E78, 0x1E79 },
	{ 0x1E7A, 0x1E7B },
	{ 0x1E7C, 0x1E7D },
	{ 0x1E7E, 0x1E7F },
	{ 0x1E80, 0x1E81 },
	{ 0x1E82, 0x1E83 },
	{ 0x1E84, 0x1E85 },
	{ 0x1E86, 0x1E87 },
	{ 0x1E88, 0x1E89 },
	{ 0x1E8A, 0x1E8B },
	{ 0x1E8C, 0x1E8D },
	{ 0x1E8E, 0x1E8F },
	{ 0x1E90, 0x1E91 },
	{ 0x1E92, 0x1E93 },
	{ 0x1E94, 0x1E95 },
	{ 0x1EA0, 0x1EA1 },
	{ 0x1EA2, 0x1EA3 },
	{ 0x1EA4, 0x1EA5 },
	{ 0x1EA6, 0x1EA7 },
	{ 0x1EA8, 0x1EA9 },
	{ 0x1EAA, 0x1EAB },
	{ 0x1EAC, 0x1EAD },
	{ 0x1EAE, 0x1EAF },
	{ 0x1EB0, 0x1EB1 },
	{ 0x1EB2, 0x1EB3 },
	{ 0x1EB4, 0x1EB5 },
	{ 0x1EB6, 0x1EB7 },
	{ 0x1EB8, 0x1EB9 },
	{ 0x1EBA, 0x1EBB },
	{ 0x1EBC, 0x1EBD },
	{ 0x1EBE, 0x1EBF },
	{ 0x1EC0, 0x1EC1 },
	{ 0x1EC2, 0x1EC3 },
	{ 0x1EC4, 0x1EC5 },
	{ 0x1EC6, 0x1EC7 },
	{ 0x1EC8, 0x1EC9 },
	{ 0x1ECA, 0x1ECB },
	{ 0x1ECC, 0x1ECD },
	{ 0x1ECE, 0x1ECF },
	{ 0x1ED0, 0x1ED1 },
	{ 0x1ED2, 0x1ED3 },
	{ 0x1ED4, 0x1ED5 },
	{ 0x1ED6, 0x1ED7 },
	{ 0x1ED8, 0x1ED9 },
	{ 0x1EDA, 0x1EDB },
	{ 0x1EDC, 0x1EDD },
	{ 0x1EDE, 0x1EDF },
	{ 0x1EE0, 0x1EE1 },
	{ 0x1EE2, 0x1EE3 },
	{ 0x1EE4, 0x1EE5 },
	{ 0x1EE6, 0x1EE7 },
	{ 0x1EE8, 0x1EE9 },
	{ 0x1EEA, 0x1EEB },
	{ 0x1EEC, 0x1EED },
	{ 0x1EEE, 0x1EEF },
	{ 0x1EF0, 0x1EF1 },
	{ 0x1EF2, 0x1EF3 },
	{ 0x1EF4, 0x1EF5 },
	{ 0x1EF6, 0x1EF7 },
	{ 0x1EF8, 0x1EF9 },
	{ 0x1F08, 0x1F00 },
	{ 0x1F09, 0x1F01 },
	{ 0x1F0A, 0x1F02 },
	{ 0x1F0B, 0x1F03 },
	{ 0x1F0C, 0x1F04 },
	{ 0x1F0D, 0x1F05 },
	{ 0x1F0E, 0x1F06 },
	{ 0x1F0F, 0x1F07 },
	{ 0x1F18, 0x1F10 },
	{ 0x1F19, 0x1F11 },
	{ 0x1F1A, 0x1F12 },
	{ 0x1F1B, 0x1F13 },
	{ 0x1F1C, 0x1F14 },
	{ 0x1F1D, 0x1F15 },
	{ 0x1F28, 0x1F20 },
	{ 0x1F29, 0x1F21 },
	{ 0x1F2A, 0x1F22 },
	{ 0x1F2B, 0x1F23 },
	{ 0x1F2C, 0x1F24 },
	{ 0x1F2D, 0x1F25 },
	{ 0x1F2E, 0x1F26 },
	{ 0x1F2F, 0x1F27 },
	{ 0x1F38, 0x1F30 },
	{ 0x1F39, 0x1F31 },
	{ 0x1F3A, 0x1F32 },
	{ 0x1F3B, 0x1F33 },
	{ 0x1F3C, 0x1F34 },
	{ 0x1F3D, 0x1F35 },
	{ 0x1F3E, 0x1F36 },
	{ 0x1F3F, 0x1F37 },
	{ 0x1F48, 0x1F40 },
	{ 0x1F49, 0x1F41 },
	{ 0x1F4A, 0x1F42 },
	{ 0x1F4B, 0x1F43 },
	{ 0x1F4C, 0x1F44 },
	{ 0x1F4D, 0x1F45 },
	{ 0x1F59, 0x1F51 },
	{ 0x1F5B, 0x1F53 },
	{ 0x1F5D, 0x1F55 },
	{ 0x1F5F, 0x1F57 },
	{ 0x1F68, 0x1F60 },
	{ 0x1F69, 0x1F61 },
	{ 0x1F6A, 0x1F62 },
	{ 0x1F6B, 0x1F63 },
	{ 0x1F6C, 0x1F64 },
	{ 0x1F6D, 0x1F65 },
	{ 0x1F6E, 0x1F66 },
	{ 0x1F6F, 0x1F67 },
	{ 0x1F88, 0x1F80 },
	{ 0x1F89, 0x1F81 },
	{ 0x1F8A, 0x1F82 },
	{ 0x1F8B, 0x1F83 },
	{ 0x1F8C, 0x1F84 },
	{ 0x1F8D, 0x1F85 },
	{ 0x1F8E, 0x1F86 },
	{ 0x1F8F, 0x1F87 },
	{ 0x1F98, 0x1F90 },
	{ 0x1F99, 0x1F91 },
	{ 0x1F9A, 0x1F92 },
	{ 0x1F9B, 0x1F93 },
	{ 0x1F9C, 0x1F94 },
	{ 0x1F9D, 0x1F95 },
	{ 0x1F9E, 0x1F96 },
	{ 0x1F9F, 0x1F97 },
	{ 0x1FA8, 0x1FA0 },
	{ 0x1FA9, 0x1FA1 },
	{ 0x1FAA, 0x1FA2 },
	{ 0x1FAB, 0x1FA3 },
	{ 0x1FAC, 0x1FA4 },
	{ 0x1FAD, 0x1FA5 },
	{ 0x1FAE, 0x1FA6 },
	{ 0x1FAF, 0x1FA7 },
	{ 0x1FB8, 0x1FB0 },
	{ 0x1FB9, 0x1FB1 },
	{ 0x1FD8, 0x1FD0 },
	{ 0x1FD9, 0x1FD1 },
	{ 0x1FE8, 0x1FE0 },
	{ 0x1FE9, 0x1FE1 },
	{ 0x24B6, 0x24D0 },
	{ 0x24B7, 0x24D1 },
	{ 0x24B8, 0x24D2 },
	{ 0x24B9, 0x24D3 },
	{ 0x24BA, 0x24D4 },
	{ 0x24BB, 0x24D5 },
	{ 0x24BC, 0x24D6 },
	{ 0x24BD, 0x24D7 },
	{ 0x24BE, 0x24D8 },
	{ 0x24BF, 0x24D9 },
	{ 0x24C0, 0x24DA },
	{ 0x24C1, 0x24DB },
	{ 0x24C2, 0x24DC },
	{ 0x24C3, 0x24DD },
	{ 0x24C4, 0x24DE },
	{ 0x24C5, 0x24DF },
	{ 0x24C6, 0x24E0 },
	{ 0x24C7, 0x24E1 },
	{ 0x24C8, 0x24E2 },
	{ 0x24C9, 0x24E3 },
	{ 0x24CA, 0x24E4 },
	{ 0x24CB, 0x24E5 },
	{ 0x24CC, 0x24E6 },
	{ 0x24CD, 0x24E7 },
	{ 0x24CE, 0x24E8 },
	{ 0x24CF, 0x24E9 },
	{ 0xFF21, 0xFF41 },
	{ 0xFF22, 0xFF42 },
	{ 0xFF23, 0xFF43 },
	{ 0xFF24, 0xFF44 },
	{ 0xFF25, 0xFF45 },
	{ 0xFF26, 0xFF46 },
	{ 0xFF27, 0xFF47 },
	{ 0xFF28, 0xFF48 },
	{ 0xFF29, 0xFF49 },
	{ 0xFF2A, 0xFF4A },
	{ 0xFF2B, 0xFF4B },
	{ 0xFF2C, 0xFF4C },
	{ 0xFF2D, 0xFF4D },
	{ 0xFF2E, 0xFF4E },
	{ 0xFF2F, 0xFF4F },
	{ 0xFF30, 0xFF50 },
	{ 0xFF31, 0xFF51 },
	{ 0xFF32, 0xFF52 },
	{ 0xFF33, 0xFF53 },
	{ 0xFF34, 0xFF54 },
	{ 0xFF35, 0xFF55 },
	{ 0xFF36, 0xFF56 },
	{ 0xFF37, 0xFF57 },
	{ 0xFF38, 0xFF58 },
	{ 0xFF39, 0xFF59 },
	{ 0xFF3A, 0xFF5A },
};

static int _find_upper(int ch) {
	int low = 0;
	int high = CAPS_LEN - 1;
	int middle;

	while (low <= high) {
		middle = (low + high) / 2;

		if (ch < caps_table[middle][0]) {
			high = middle - 1; //search low end of array
		} else if (caps_table[middle][0] < ch) {
			low = middle + 1; //search high end of array
		} else {
			return caps_table[middle][1];
		}
	}

	return ch;
}

static int _find_lower(int ch) {
	int low = 0;
	int high = CAPS_LEN - 2;
	int middle;

	while (low <= high) {
		middle = (low + high) / 2;

		if (ch < reverse_caps_table[middle][0]) {
			high = middle - 1; //search low end of array
		} else if (reverse_caps_table[middle][0] < ch) {
			low = middle + 1; //search high end of array
		} else {
			return reverse_caps_table[middle][1];
		}
	}

	return ch;
}
#endif
#line 0


#line 1 "sfwl/core/mutex.cpp"
/*************************************************************************/
/*  mutex.cpp                                                            */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



static Mutex _global_mutex;

void _global_lock() {
	_global_mutex.lock();
}

void _global_unlock() {
	_global_mutex.unlock();
}

#ifndef NO_THREADS

template class MutexImpl<std::recursive_mutex>;
template class MutexImpl<std::mutex>;

#endif
#line 0

#line 1 "sfwl/core/safe_refcount.cpp"
/*************************************************************************/
/*  safe_refcount.cpp                                                    */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#if defined(DEBUG_ENABLED) && !defined(NO_THREADS)



// On C++14 we don't have std::atomic::is_always_lockfree, so this is the best we can do
void check_lockless_atomics() {
	// Doing the check for the types we actually care about
	if (!std::atomic<uint32_t>{}.is_lock_free() || !std::atomic<uint64_t>{}.is_lock_free() || !std::atomic_bool{}.is_lock_free()) {
		WARN_PRINT("Your compiler doesn't seem to support lockless atomics. Performance will be degraded. Please consider upgrading to a different or newer compiler.");
	}
}

#endif
#line 0


#line 1 "sfwl/core/stime.cpp"
// ----------------------------------------------------------------------------
// time



#if 0
uint64_t STime::time_gpu() {
    GLint64 t = 123456789;
    glGetInteger64v(GL_TIMESTAMP, &t);
    return (uint64_t)t;
}
#endif
uint64_t STime::date() {
	//time_t epoch = time(0);
	//struct tm *ti = localtime(&epoch);
	//return atoi64(va("%04d%02d%02d%02d%02d%02d", ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec));
	return 0;
}
char *STime::date_string() {
	//time_t epoch = time(0);
	//struct tm *ti = localtime(&epoch);
	//return va("%04d-%02d-%02d %02d:%02d:%02d", ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec);
	return 0;
}
uint64_t STime::date_epoch() {
	time_t epoch = time(0);
	return epoch;
}
#if 0
double STime::time_ss() {
    return glfwGetTime();
}
double STime::time_ms() {
    return glfwGetTime() * 1000.0;
}
uint64_t STime::time_us() {
    return (uint64_t)(glfwGetTime() * 1000000.0); // @fixme: use a high resolution timer instead, or time_gpu below
}
uint64_t STime::sleep_us(uint64_t us) { // @fixme: use a high resolution sleeper instead
    return sleep_ms( us / 1000.0 );
}
double STime::sleep_ms(double ms) {
    double now = time_ms();
    if( ms <= 0 ) {
#if defined(_WIN64) || defined(_WIN32)
        Sleep(0); // yield
#else
        usleep(0);
#endif
    } else {
#if defined(_WIN64) || defined(_WIN32)
        Sleep(ms);
#else
        usleep(ms * 1000);
#endif
    }
    return time_ms() - now;
}
double sleep_ss(double ss) {
    return sleep_ms( ss * 1000 ) / 1000.0;
}
#endif

// high-perf functions

#define TIMER_E3 1000ULL
#define TIMER_E6 1000000ULL
#define TIMER_E9 1000000000ULL

#ifdef CLOCK_MONOTONIC_RAW
#define TIME_MONOTONIC CLOCK_MONOTONIC_RAW
#elif defined CLOCK_MONOTONIC
#define TIME_MONOTONIC CLOCK_MONOTONIC
#else
// #define TIME_MONOTONIC CLOCK_REALTIME // untested
#endif

static uint64_t nanotimer(uint64_t *out_freq) {
	if (out_freq) {
#if defined(_WIN64) || defined(_WIN32)
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		*out_freq = li.QuadPart;
//#elif is(ANDROID)
//      *out_freq = CLOCKS_PER_SEC;
#elif defined TIME_MONOTONIC
		*out_freq = TIMER_E9;
#else
		*out_freq = TIMER_E6;
#endif
	}
#if defined(_WIN64) || defined(_WIN32)
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return (uint64_t)li.QuadPart;
//#elif is(ANDROID)
//    return (uint64_t)clock();
#elif defined TIME_MONOTONIC
	struct timespec ts;
	clock_gettime(TIME_MONOTONIC, &ts);
	return (TIMER_E9 * (uint64_t)ts.tv_sec) + ts.tv_nsec;
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (TIMER_E6 * (uint64_t)tv.tv_sec) + tv.tv_usec;
#endif
}

uint64_t STime::time_ns() {
	static __thread uint64_t epoch = 0;
	static __thread uint64_t freq = 0;
	if (!freq) {
		epoch = nanotimer(&freq);
	}

	uint64_t a = nanotimer(NULL) - epoch;
	uint64_t b = TIMER_E9;
	uint64_t c = freq;

	// Computes (a*b)/c without overflow, as long as both (a*b) and the overall result fit into 64-bits.
	// [ref] https://github.com/rust-lang/rust/blob/3809bbf47c8557bd149b3e52ceb47434ca8378d5/src/libstd/sys_common/mod.rs#L124
	uint64_t q = a / c;
	uint64_t r = a % c;
	return q * b + r * b / c;
}
uint64_t STime::time_us() {
	return time_ns() / TIMER_E3;
}
uint64_t STime::time_ms() {
	return time_ns() / TIMER_E6;
}
double STime::time_ss() {
	return time_ns() / 1e9; // TIMER_E9;
}
double STime::time_mm() {
	return time_ss() / 60;
}
double STime::time_hh() {
	return time_mm() / 60;
}

void STime::sleep_ns(double ns) {
#if defined(_WIN64) || defined(_WIN32)
	if (ns >= 100) {
		LARGE_INTEGER li; // Windows sleep in 100ns units
		HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
		li.QuadPart = (LONGLONG)(__int64)(-ns / 100); // Negative for relative time
		SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE);
		WaitForSingleObject(timer, INFINITE);
		CloseHandle(timer);
#else
	if (ns > 0) {
		struct timespec wait = { 0 };
		wait.tv_sec = ns / 1e9;
		wait.tv_nsec = ns - wait.tv_sec * 1e9;
		nanosleep(&wait, NULL);
#endif
	} else {
#if defined(_WIN64) || defined(_WIN32)
		Sleep(0); // yield, Sleep(0), SwitchToThread
#else
		usleep(0);
#endif
	}
}
void STime::sleep_us(double us) {
	sleep_ns(us * 1e3);
}
void STime::sleep_ms(double ms) {
	sleep_ns(ms * 1e6);
}
void STime::sleep_ss(double ss) {
	sleep_ns(ss * 1e9);
}
#line 0


#line 1 "sfwl/core/memory.cpp"
/*************************************************************************/
/*  memory.cpp                                                           */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



void *operator new(size_t p_size, const char *p_description) {
	return Memory::alloc_static(p_size, false);
}

void *operator new(size_t p_size, void *(*p_allocfunc)(size_t p_size)) {
	return p_allocfunc(p_size);
}

#ifdef _MSC_VER
void operator delete(void *p_mem, const char *p_description) {
	CRASH_NOW_MSG("Call to placement delete should not happen.");
}

void operator delete(void *p_mem, void *(*p_allocfunc)(size_t p_size)) {
	CRASH_NOW_MSG("Call to placement delete should not happen.");
}

void operator delete(void *p_mem, void *p_pointer, size_t check, const char *p_description) {
	CRASH_NOW_MSG("Call to placement delete should not happen.");
}
#endif

#ifdef DEBUG_ENABLED
SafeNumeric<uint64_t> Memory::mem_usage;
SafeNumeric<uint64_t> Memory::max_usage;
#endif

SafeNumeric<uint64_t> Memory::alloc_count;

void *Memory::alloc_static(size_t p_bytes, bool p_pad_align) {
#ifdef DEBUG_ENABLED
	bool prepad = true;
#else
	bool prepad = p_pad_align;
#endif

	void *mem = malloc(p_bytes + (prepad ? PAD_ALIGN : 0));

	ERR_FAIL_COND_V(!mem, nullptr);

	alloc_count.increment();

	if (prepad) {
		uint64_t *s = (uint64_t *)mem;
		*s = p_bytes;

		uint8_t *s8 = (uint8_t *)mem;

#ifdef DEBUG_ENABLED
		uint64_t new_mem_usage = mem_usage.add(p_bytes);
		max_usage.exchange_if_greater(new_mem_usage);
#endif
		return s8 + PAD_ALIGN;
	} else {
		return mem;
	}
}

void *Memory::realloc_static(void *p_memory, size_t p_bytes, bool p_pad_align) {
	if (p_memory == nullptr) {
		return alloc_static(p_bytes, p_pad_align);
	}

	uint8_t *mem = (uint8_t *)p_memory;

#ifdef DEBUG_ENABLED
	bool prepad = true;
#else
	bool prepad = p_pad_align;
#endif

	if (prepad) {
		mem -= PAD_ALIGN;
		uint64_t *s = (uint64_t *)mem;

#ifdef DEBUG_ENABLED
		if (p_bytes > *s) {
			uint64_t new_mem_usage = mem_usage.add(p_bytes - *s);
			max_usage.exchange_if_greater(new_mem_usage);
		} else {
			mem_usage.sub(*s - p_bytes);
		}
#endif

		if (p_bytes == 0) {
			free(mem);
			return nullptr;
		} else {
			*s = p_bytes;

			mem = (uint8_t *)realloc(mem, p_bytes + PAD_ALIGN);
			ERR_FAIL_COND_V(!mem, nullptr);

			s = (uint64_t *)mem;

			*s = p_bytes;

			return mem + PAD_ALIGN;
		}
	} else {
		mem = (uint8_t *)realloc(mem, p_bytes);

		ERR_FAIL_COND_V(mem == nullptr && p_bytes > 0, nullptr);

		return mem;
	}
}

void Memory::free_static(void *p_ptr, bool p_pad_align) {
	ERR_FAIL_COND(p_ptr == nullptr);

	uint8_t *mem = (uint8_t *)p_ptr;

#ifdef DEBUG_ENABLED
	bool prepad = true;
#else
	bool prepad = p_pad_align;
#endif

	alloc_count.decrement();

	if (prepad) {
		mem -= PAD_ALIGN;

#ifdef DEBUG_ENABLED
		uint64_t *s = (uint64_t *)mem;
		mem_usage.sub(*s);
#endif

		free(mem);
	} else {
		free(mem);
	}
}

uint64_t Memory::get_mem_available() {
	return -1; // 0xFFFF...
}

uint64_t Memory::get_mem_usage() {
#ifdef DEBUG_ENABLED
	return mem_usage.get();
#else
	return 0;
#endif
}

uint64_t Memory::get_mem_max_usage() {
#ifdef DEBUG_ENABLED
	return max_usage.get();
#else
	return 0;
#endif
}

_GlobalNil::_GlobalNil() {
	color = 1;
	left = this;
	right = this;
	parent = this;
}

_GlobalNil _GlobalNilClass::_nil;
#line 0



#line 1 "sfwl/core/pool_vector.cpp"
/*************************************************************************/
/*  pool_vector.cpp                                                      */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



Mutex pool_vector_lock;

PoolAllocator *MemoryPool::memory_pool = nullptr;
uint8_t *MemoryPool::pool_memory = nullptr;
size_t *MemoryPool::pool_size = nullptr;

MemoryPool::Alloc *MemoryPool::allocs = nullptr;
MemoryPool::Alloc *MemoryPool::free_list = nullptr;
uint32_t MemoryPool::alloc_count = 0;
uint32_t MemoryPool::allocs_used = 0;
Mutex MemoryPool::alloc_mutex;

size_t MemoryPool::total_memory = 0;
size_t MemoryPool::max_memory = 0;

void MemoryPool::setup(uint32_t p_max_allocs) {
	allocs = memnew_arr(Alloc, p_max_allocs);
	alloc_count = p_max_allocs;
	allocs_used = 0;

	for (uint32_t i = 0; i < alloc_count - 1; i++) {
		allocs[i].free_list = &allocs[i + 1];
	}

	free_list = &allocs[0];
}

void MemoryPool::cleanup() {
	memdelete_arr(allocs);

	ERR_FAIL_COND_MSG(allocs_used > 0, "There are still MemoryPool allocs in use at exit!");
}
#line 0

#line 1 "sfwl/core/pool_allocator.cpp"
/*************************************************************************/
/*  pool_allocator.cpp                                                   */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



#define COMPACT_CHUNK(m_entry, m_to_pos)                      \
	do {                                                      \
		void *_dst = &((unsigned char *)pool)[m_to_pos];      \
		void *_src = &((unsigned char *)pool)[(m_entry).pos]; \
		memmove(_dst, _src, aligned((m_entry).len));          \
		(m_entry).pos = m_to_pos;                             \
	} while (0);

void PoolAllocator::mt_lock() const {
}

void PoolAllocator::mt_unlock() const {
}

bool PoolAllocator::get_free_entry(EntryArrayPos *p_pos) {
	if (entry_count == entry_max) {
		return false;
	}

	for (int i = 0; i < entry_max; i++) {
		if (entry_array[i].len == 0) {
			*p_pos = i;
			return true;
		}
	}

	ERR_PRINT("Out of memory Chunks!");

	return false; //
}

/**
 * Find a hole
 * @param p_pos The hole is behind the block pointed by this variable upon return. if pos==entry_count, then allocate at end
 * @param p_for_size hole size
 * @return false if hole found, true if no hole found
 */
bool PoolAllocator::find_hole(EntryArrayPos *p_pos, int p_for_size) {
	/* position where previous entry ends. Defaults to zero (begin of pool) */

	int prev_entry_end_pos = 0;

	for (int i = 0; i < entry_count; i++) {
		Entry &entry = entry_array[entry_indices[i]];

		/* determine hole size to previous entry */

		int hole_size = entry.pos - prev_entry_end_pos;

		/* determine if what we want fits in that hole */
		if (hole_size >= p_for_size) {
			*p_pos = i;
			return true;
		}

		/* prepare for next one */
		prev_entry_end_pos = entry_end(entry);
	}

	/* No holes between entries, check at the end..*/

	if ((pool_size - prev_entry_end_pos) >= p_for_size) {
		*p_pos = entry_count;
		return true;
	}

	return false;
}

void PoolAllocator::compact(int p_up_to) {
	uint32_t prev_entry_end_pos = 0;

	if (p_up_to < 0) {
		p_up_to = entry_count;
	}
	for (int i = 0; i < p_up_to; i++) {
		Entry &entry = entry_array[entry_indices[i]];

		/* determine hole size to previous entry */

		int hole_size = entry.pos - prev_entry_end_pos;

		/* if we can compact, do it */
		if (hole_size > 0 && !entry.lock) {
			COMPACT_CHUNK(entry, prev_entry_end_pos);
		}

		/* prepare for next one */
		prev_entry_end_pos = entry_end(entry);
	}
}

void PoolAllocator::compact_up(int p_from) {
	uint32_t next_entry_end_pos = pool_size; // - static_area_size;

	for (int i = entry_count - 1; i >= p_from; i--) {
		Entry &entry = entry_array[entry_indices[i]];

		/* determine hole size to nextious entry */

		int hole_size = next_entry_end_pos - (entry.pos + aligned(entry.len));

		/* if we can compact, do it */
		if (hole_size > 0 && !entry.lock) {
			COMPACT_CHUNK(entry, (next_entry_end_pos - aligned(entry.len)));
		}

		/* prepare for next one */
		next_entry_end_pos = entry.pos;
	}
}

bool PoolAllocator::find_entry_index(EntryIndicesPos *p_map_pos, Entry *p_entry) {
	EntryArrayPos entry_pos = entry_max;

	for (int i = 0; i < entry_count; i++) {
		if (&entry_array[entry_indices[i]] == p_entry) {
			entry_pos = i;
			break;
		}
	}

	if (entry_pos == entry_max) {
		return false;
	}

	*p_map_pos = entry_pos;
	return true;
}

PoolAllocator::ID PoolAllocator::alloc(int p_size) {
	ERR_FAIL_COND_V(p_size < 1, POOL_ALLOCATOR_INVALID_ID);
	ERR_FAIL_COND_V(p_size > free_mem, POOL_ALLOCATOR_INVALID_ID);

	mt_lock();

	if (entry_count == entry_max) {
		mt_unlock();
		ERR_PRINT("entry_count==entry_max");
		return POOL_ALLOCATOR_INVALID_ID;
	}

	int size_to_alloc = aligned(p_size);

	EntryIndicesPos new_entry_indices_pos;

	if (!find_hole(&new_entry_indices_pos, size_to_alloc)) {
		/* No hole could be found, try compacting mem */
		compact();
		/* Then search again */

		if (!find_hole(&new_entry_indices_pos, size_to_alloc)) {
			mt_unlock();
			ERR_FAIL_V_MSG(POOL_ALLOCATOR_INVALID_ID, "Memory can't be compacted further.");
		}
	}

	EntryArrayPos new_entry_array_pos;

	bool found_free_entry = get_free_entry(&new_entry_array_pos);

	if (!found_free_entry) {
		mt_unlock();
		ERR_FAIL_V_MSG(POOL_ALLOCATOR_INVALID_ID, "No free entry found in PoolAllocator.");
	}

	/* move all entry indices up, make room for this one */
	for (int i = entry_count; i > new_entry_indices_pos; i--) {
		entry_indices[i] = entry_indices[i - 1];
	}

	entry_indices[new_entry_indices_pos] = new_entry_array_pos;

	entry_count++;

	Entry &entry = entry_array[entry_indices[new_entry_indices_pos]];

	entry.len = p_size;
	entry.pos = (new_entry_indices_pos == 0) ? 0 : entry_end(entry_array[entry_indices[new_entry_indices_pos - 1]]); //alloc either at beginning or end of previous
	entry.lock = 0;
	entry.check = (check_count++) & CHECK_MASK;
	free_mem -= size_to_alloc;
	if (free_mem < free_mem_peak) {
		free_mem_peak = free_mem;
	}

	ID retval = (entry_indices[new_entry_indices_pos] << CHECK_BITS) | entry.check;
	mt_unlock();

	//ERR_FAIL_COND_V( (uintptr_t)get(retval)%align != 0, retval );

	return retval;
}

PoolAllocator::Entry *PoolAllocator::get_entry(ID p_mem) {
	unsigned int check = p_mem & CHECK_MASK;
	int entry = p_mem >> CHECK_BITS;
	ERR_FAIL_INDEX_V(entry, entry_max, nullptr);
	ERR_FAIL_COND_V(entry_array[entry].check != check, nullptr);
	ERR_FAIL_COND_V(entry_array[entry].len == 0, nullptr);

	return &entry_array[entry];
}

const PoolAllocator::Entry *PoolAllocator::get_entry(ID p_mem) const {
	unsigned int check = p_mem & CHECK_MASK;
	int entry = p_mem >> CHECK_BITS;
	ERR_FAIL_INDEX_V(entry, entry_max, nullptr);
	ERR_FAIL_COND_V(entry_array[entry].check != check, nullptr);
	ERR_FAIL_COND_V(entry_array[entry].len == 0, nullptr);

	return &entry_array[entry];
}

void PoolAllocator::free(ID p_mem) {
	mt_lock();
	Entry *e = get_entry(p_mem);
	if (!e) {
		mt_unlock();
		ERR_PRINT("!e");
		return;
	}
	if (e->lock) {
		mt_unlock();
		ERR_PRINT("e->lock");
		return;
	}

	EntryIndicesPos entry_indices_pos;

	bool index_found = find_entry_index(&entry_indices_pos, e);
	if (!index_found) {
		mt_unlock();
		ERR_FAIL_COND(!index_found);
	}

	for (int i = entry_indices_pos; i < (entry_count - 1); i++) {
		entry_indices[i] = entry_indices[i + 1];
	}

	entry_count--;
	free_mem += aligned(e->len);
	e->clear();
	mt_unlock();
}

int PoolAllocator::get_size(ID p_mem) const {
	int size;
	mt_lock();

	const Entry *e = get_entry(p_mem);
	if (!e) {
		mt_unlock();
		ERR_PRINT("!e");
		return 0;
	}

	size = e->len;

	mt_unlock();

	return size;
}

Error PoolAllocator::resize(ID p_mem, int p_new_size) {
	mt_lock();
	Entry *e = get_entry(p_mem);

	if (!e) {
		mt_unlock();
		ERR_FAIL_COND_V(!e, ERR_INVALID_PARAMETER);
	}

	if (needs_locking && e->lock) {
		mt_unlock();
		ERR_FAIL_COND_V(e->lock, ERR_ALREADY_IN_USE);
	}

	uint32_t alloc_size = aligned(p_new_size);

	if ((uint32_t)aligned(e->len) == alloc_size) {
		e->len = p_new_size;
		mt_unlock();
		return OK;
	} else if (e->len > (uint32_t)p_new_size) {
		free_mem += aligned(e->len);
		free_mem -= alloc_size;
		e->len = p_new_size;
		mt_unlock();
		return OK;
	}

	//p_new_size = align(p_new_size)
	int _free = free_mem; // - static_area_size;

	if (uint32_t(_free + aligned(e->len)) < alloc_size) {
		mt_unlock();
		ERR_FAIL_V(ERR_OUT_OF_MEMORY);
	};

	EntryIndicesPos entry_indices_pos;

	bool index_found = find_entry_index(&entry_indices_pos, e);

	if (!index_found) {
		mt_unlock();
		ERR_FAIL_COND_V(!index_found, ERR_BUG);
	}

	//no need to move stuff around, it fits before the next block
	uint32_t next_pos;
	if (entry_indices_pos + 1 == entry_count) {
		next_pos = pool_size; // - static_area_size;
	} else {
		next_pos = entry_array[entry_indices[entry_indices_pos + 1]].pos;
	};

	if ((next_pos - e->pos) > alloc_size) {
		free_mem += aligned(e->len);
		e->len = p_new_size;
		free_mem -= alloc_size;
		mt_unlock();
		return OK;
	}
	//it doesn't fit, compact around BEFORE current index (make room behind)

	compact(entry_indices_pos + 1);

	if ((next_pos - e->pos) > alloc_size) {
		//now fits! hooray!
		free_mem += aligned(e->len);
		e->len = p_new_size;
		free_mem -= alloc_size;
		mt_unlock();
		if (free_mem < free_mem_peak) {
			free_mem_peak = free_mem;
		}
		return OK;
	}

	//STILL doesn't fit, compact around AFTER current index (make room after)

	compact_up(entry_indices_pos + 1);

	if ((entry_array[entry_indices[entry_indices_pos + 1]].pos - e->pos) > alloc_size) {
		//now fits! hooray!
		free_mem += aligned(e->len);
		e->len = p_new_size;
		free_mem -= alloc_size;
		mt_unlock();
		if (free_mem < free_mem_peak) {
			free_mem_peak = free_mem;
		}
		return OK;
	}

	mt_unlock();
	ERR_FAIL_V(ERR_OUT_OF_MEMORY);
}

Error PoolAllocator::lock(ID p_mem) {
	if (!needs_locking) {
		return OK;
	}
	mt_lock();
	Entry *e = get_entry(p_mem);
	if (!e) {
		mt_unlock();
		ERR_PRINT("!e");
		return ERR_INVALID_PARAMETER;
	}
	e->lock++;
	mt_unlock();
	return OK;
}

bool PoolAllocator::is_locked(ID p_mem) const {
	if (!needs_locking) {
		return false;
	}

	mt_lock();
	const Entry *e = ((PoolAllocator *)(this))->get_entry(p_mem);
	if (!e) {
		mt_unlock();
		ERR_PRINT("!e");
		return false;
	}
	bool locked = e->lock;
	mt_unlock();
	return locked;
}

const void *PoolAllocator::get(ID p_mem) const {
	if (!needs_locking) {
		const Entry *e = get_entry(p_mem);
		ERR_FAIL_COND_V(!e, nullptr);
		return &pool[e->pos];
	}

	mt_lock();
	const Entry *e = get_entry(p_mem);

	if (!e) {
		mt_unlock();
		ERR_FAIL_COND_V(!e, nullptr);
	}
	if (e->lock == 0) {
		mt_unlock();
		ERR_PRINT("e->lock == 0");
		return nullptr;
	}

	if ((int)e->pos >= pool_size) {
		mt_unlock();
		ERR_PRINT("e->pos<0 || e->pos>=pool_size");
		return nullptr;
	}
	const void *ptr = &pool[e->pos];

	mt_unlock();

	return ptr;
}

void *PoolAllocator::get(ID p_mem) {
	if (!needs_locking) {
		Entry *e = get_entry(p_mem);
		ERR_FAIL_COND_V(!e, nullptr);
		return &pool[e->pos];
	}

	mt_lock();
	Entry *e = get_entry(p_mem);

	if (!e) {
		mt_unlock();
		ERR_FAIL_COND_V(!e, nullptr);
	}
	if (e->lock == 0) {
		mt_unlock();
		ERR_PRINT("e->lock == 0");
		return nullptr;
	}

	if ((int)e->pos >= pool_size) {
		mt_unlock();
		ERR_PRINT("e->pos<0 || e->pos>=pool_size");
		return nullptr;
	}
	void *ptr = &pool[e->pos];

	mt_unlock();

	return ptr;
}
void PoolAllocator::unlock(ID p_mem) {
	if (!needs_locking) {
		return;
	}
	mt_lock();
	Entry *e = get_entry(p_mem);
	if (!e) {
		mt_unlock();
		ERR_FAIL_COND(!e);
	}
	if (e->lock == 0) {
		mt_unlock();
		ERR_PRINT("e->lock == 0");
		return;
	}
	e->lock--;
	mt_unlock();
}

int PoolAllocator::get_used_mem() const {
	return pool_size - free_mem;
}

int PoolAllocator::get_free_peak() {
	return free_mem_peak;
}

int PoolAllocator::get_free_mem() {
	return free_mem;
}

void PoolAllocator::create_pool(void *p_mem, int p_size, int p_max_entries) {
	pool = (uint8_t *)p_mem;
	pool_size = p_size;

	entry_array = memnew_arr(Entry, p_max_entries);
	entry_indices = memnew_arr(int, p_max_entries);
	entry_max = p_max_entries;
	entry_count = 0;

	free_mem = p_size;
	free_mem_peak = p_size;

	check_count = 0;
}

PoolAllocator::PoolAllocator(int p_size, bool p_needs_locking, int p_max_entries) {
	mem_ptr = memalloc(p_size);
	ERR_FAIL_COND(!mem_ptr);
	align = 1;
	create_pool(mem_ptr, p_size, p_max_entries);
	needs_locking = p_needs_locking;
}

PoolAllocator::PoolAllocator(void *p_mem, int p_size, int p_align, bool p_needs_locking, int p_max_entries) {
	if (p_align > 1) {
		uint8_t *mem8 = (uint8_t *)p_mem;
		uint64_t ofs = (uint64_t)mem8;
		if (ofs % p_align) {
			int dif = p_align - (ofs % p_align);
			mem8 += p_align - (ofs % p_align);
			p_size -= dif;
			p_mem = (void *)mem8;
		};
	};

	create_pool(p_mem, p_size, p_max_entries);
	needs_locking = p_needs_locking;
	align = p_align;
	mem_ptr = nullptr;
}

PoolAllocator::PoolAllocator(int p_align, int p_size, bool p_needs_locking, int p_max_entries) {
	ERR_FAIL_COND(p_align < 1);
	mem_ptr = Memory::alloc_static(p_size + p_align, true);
	uint8_t *mem8 = (uint8_t *)mem_ptr;
	uint64_t ofs = (uint64_t)mem8;
	if (ofs % p_align) {
		mem8 += p_align - (ofs % p_align);
	}
	create_pool(mem8, p_size, p_max_entries);
	needs_locking = p_needs_locking;
	align = p_align;
}

PoolAllocator::~PoolAllocator() {
	if (mem_ptr) {
		memfree(mem_ptr);
	}

	memdelete_arr(entry_array);
	memdelete_arr(entry_indices);
}

#undef COMPACT_CHUNK
#line 0


#line 1 "sfwl/core/random_pcg.cpp"
/*************************************************************************/
/*  random_pcg.cpp                                                       */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



RandomPCG::RandomPCG(uint64_t p_seed, uint64_t p_inc) :
		pcg(),
		current_inc(p_inc) {
	seed(p_seed);
}

void RandomPCG::randomize() {
	seed((STime::date() + STime::time_us()) * pcg.state + PCG_DEFAULT_INC_64);
}

double RandomPCG::random(double p_from, double p_to) {
	return randd() * (p_to - p_from) + p_from;
}

float RandomPCG::random(float p_from, float p_to) {
	return randf() * (p_to - p_from) + p_from;
}

int RandomPCG::random(int p_from, int p_to) {
	if (p_from == p_to) {
		return p_from;
	}
	return rand(abs(p_from - p_to) + 1) + MIN(p_from, p_to);
}
#line 0


#line 1 "sfwl/core/math_funcs.cpp"
/*************************************************************************/
/*  math_funcs.cpp                                                       */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



RandomPCG Math::default_rand(RandomPCG::DEFAULT_SEED, RandomPCG::DEFAULT_INC);

#define PHI 0x9e3779b9

uint32_t Math::rand_from_seed(uint64_t *seed) {
	RandomPCG rng = RandomPCG(*seed, RandomPCG::DEFAULT_INC);
	uint32_t r = rng.rand();
	*seed = rng.get_seed();
	return r;
}

void Math::seed(uint64_t x) {
	default_rand.seed(x);
}

void Math::randomize() {
	default_rand.randomize();
}

uint32_t Math::rand() {
	return default_rand.rand();
}

double Math::randfn(double mean, double deviation) {
	return default_rand.randfn(mean, deviation);
}

int Math::step_decimals(double p_step) {
	static const int maxn = 10;
	static const double sd[maxn] = {
		0.9999, // somehow compensate for floating point error
		0.09999,
		0.009999,
		0.0009999,
		0.00009999,
		0.000009999,
		0.0000009999,
		0.00000009999,
		0.000000009999,
		0.0000000009999
	};

	double abs = Math::abs(p_step);
	double decs = abs - (int)abs; // Strip away integer part
	for (int i = 0; i < maxn; i++) {
		if (decs >= sd[i]) {
			return i;
		}
	}

	return 0;
}

// Only meant for editor usage in float ranges, where a step of 0
// means that decimal digits should not be limited in String::num.
int Math::range_step_decimals(double p_step) {
	if (p_step < 0.0000000000001) {
		return 16; // Max value hardcoded in String::num
	}
	return step_decimals(p_step);
}

double Math::dectime(double p_value, double p_amount, double p_step) {
	double sgn = p_value < 0 ? -1.0 : 1.0;
	double val = Math::abs(p_value);
	val -= p_amount * p_step;
	if (val < 0.0) {
		val = 0.0;
	}
	return val * sgn;
}

double Math::ease(double p_x, double p_c) {
	if (p_x < 0) {
		p_x = 0;
	} else if (p_x > 1.0) {
		p_x = 1.0;
	}
	if (p_c > 0) {
		if (p_c < 1.0) {
			return 1.0 - Math::pow(1.0 - p_x, 1.0 / p_c);
		} else {
			return Math::pow(p_x, p_c);
		}
	} else if (p_c < 0) {
		//inout ease

		if (p_x < 0.5) {
			return Math::pow(p_x * 2.0, -p_c) * 0.5;
		} else {
			return (1.0 - Math::pow(1.0 - (p_x - 0.5) * 2.0, -p_c)) * 0.5 + 0.5;
		}
	} else {
		return 0; // no ease (raw)
	}
}

double Math::stepify(double p_value, double p_step) {
	if (p_step != 0) {
		p_value = Math::floor(p_value / p_step + 0.5) * p_step;
	}
	return p_value;
}

uint32_t Math::larger_prime(uint32_t p_val) {
	static const uint32_t primes[] = {
		5,
		13,
		23,
		47,
		97,
		193,
		389,
		769,
		1543,
		3079,
		6151,
		12289,
		24593,
		49157,
		98317,
		196613,
		393241,
		786433,
		1572869,
		3145739,
		6291469,
		12582917,
		25165843,
		50331653,
		100663319,
		201326611,
		402653189,
		805306457,
		1610612741,
		0,
	};

	int idx = 0;
	while (true) {
		ERR_FAIL_COND_V(primes[idx] == 0, 0);
		if (primes[idx] > p_val) {
			return primes[idx];
		}
		idx++;
	}
}

double Math::random(double from, double to) {
	return default_rand.random(from, to);
}

float Math::random(float from, float to) {
	return default_rand.random(from, to);
}

real_t Math::randomr(real_t from, real_t to) {
	return default_rand.randomr(from, to);
}

int Math::random(int from, int to) {
	return default_rand.random(from, to);
}
#line 0


#line 1 "sfwl/core/ustring.cpp"
/*************************************************************************/
/*  ustring.cpp                                                          */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // to disable build-time warning which suggested to use strcpy_s instead strcpy
#endif



#if defined(MINGW_ENABLED) || defined(_MSC_VER)
#define snprintf _snprintf_s
#endif

#define MAX_DIGITS 6
#define UPPERCASE(m_c) (((m_c) >= 'a' && (m_c) <= 'z') ? ((m_c) - ('a' - 'A')) : (m_c))
#define LOWERCASE(m_c) (((m_c) >= 'A' && (m_c) <= 'Z') ? ((m_c) + ('a' - 'A')) : (m_c))
#define IS_DIGIT(m_d) ((m_d) >= '0' && (m_d) <= '9')
#define IS_HEX_DIGIT(m_d) (((m_d) >= '0' && (m_d) <= '9') || ((m_d) >= 'a' && (m_d) <= 'f') || ((m_d) >= 'A' && (m_d) <= 'F'))

#define READING_SIGN 0
#define READING_INT 1
#define READING_DEC 2
#define READING_EXP 3
#define READING_DONE 4

const char CharString::_null = 0;
const char16_t Char16String::_null = 0;
const CharType String::_null = 0;

static bool _wildcard_match(const CharType *p_pattern, const CharType *p_string, bool p_case_sensitive) {
	switch (*p_pattern) {
		case '\0':
			return !*p_string;
		case '*':
			return _wildcard_match(p_pattern + 1, p_string, p_case_sensitive) || (*p_string && _wildcard_match(p_pattern, p_string + 1, p_case_sensitive));
		case '?':
			return *p_string && (*p_string != '.') && _wildcard_match(p_pattern + 1, p_string + 1, p_case_sensitive);
		default:

			return (p_case_sensitive ? (*p_string == *p_pattern) : (_find_upper(*p_string) == _find_upper(*p_pattern))) && _wildcard_match(p_pattern + 1, p_string + 1, p_case_sensitive);
	}
}

static int _humanize_digits(int p_num) {
	if (p_num < 100) {
		return 2;
	} else if (p_num < 1024) {
		return 1;
	} else {
		return 0;
	}
}

bool select_word(const String &p_s, int p_col, int &r_beg, int &r_end) {
	const String &s = p_s;
	int beg = CLAMP(p_col, 0, s.length());
	int end = beg;

	if (s[beg] > 32 || beg == s.length()) {
		bool symbol = beg < s.length() && is_symbol(s[beg]);

		while (beg > 0 && s[beg - 1] > 32 && (symbol == is_symbol(s[beg - 1]))) {
			beg--;
		}
		while (end < s.length() && s[end + 1] > 32 && (symbol == is_symbol(s[end + 1]))) {
			end++;
		}

		if (end < s.length()) {
			end += 1;
		}

		r_beg = beg;
		r_end = end;

		return true;
	} else {
		return false;
	}
}

/*************************************************************************/
/*  Char16String                                                         */
/*************************************************************************/

bool Char16String::operator<(const Char16String &p_right) const {
	if (length() == 0) {
		return p_right.length() != 0;
	}

	return is_str_less(get_data(), p_right.get_data());
}

Char16String &Char16String::operator+=(char16_t p_char) {
	const int lhs_len = length();
	resize(lhs_len + 2);

	char16_t *dst = ptrw();
	dst[lhs_len] = p_char;
	dst[lhs_len + 1] = 0;

	return *this;
}

void Char16String::operator=(const char16_t *p_cstr) {
	copy_from(p_cstr);
}

const char16_t *Char16String::get_data() const {
	if (size()) {
		return &operator[](0);
	} else {
		return u"";
	}
}

void Char16String::copy_from(const char16_t *p_cstr) {
	if (!p_cstr) {
		resize(0);
		return;
	}

	const char16_t *s = p_cstr;
	for (; *s; s++) {
	}
	size_t len = s - p_cstr;

	if (len == 0) {
		resize(0);
		return;
	}

	Error err = resize(++len); // include terminating null char

	ERR_FAIL_COND_MSG(err != OK, "Failed to copy char16_t string.");

	memcpy(ptrw(), p_cstr, len * sizeof(char16_t));
}

/*************************************************************************/
/*  CharString                                                           */
/*************************************************************************/

bool CharString::operator<(const CharString &p_right) const {
	if (length() == 0) {
		return p_right.length() != 0;
	}

	return is_str_less(get_data(), p_right.get_data());
}

CharString &CharString::operator+=(char p_char) {
	const int lhs_len = length();
	resize(lhs_len + 2);

	char *dst = ptrw();
	dst[lhs_len] = p_char;
	dst[lhs_len + 1] = 0;

	return *this;
}

void CharString::operator=(const char *p_cstr) {
	copy_from(p_cstr);
}

const char *CharString::get_data() const {
	if (size()) {
		return &operator[](0);
	} else {
		return "";
	}
}

void CharString::copy_from(const char *p_cstr) {
	if (!p_cstr) {
		resize(0);
		return;
	}

	size_t len = strlen(p_cstr);

	if (len == 0) {
		resize(0);
		return;
	}

	Error err = resize(++len); // include terminating null char

	ERR_FAIL_COND_MSG(err != OK, "Failed to copy C-string.");

	memcpy(ptrw(), p_cstr, len);
}

/*************************************************************************/
/*  String                                                               */
/*************************************************************************/

void String::copy_from(const char *p_cstr) {
	// copy Latin-1 encoded c-string directly
	if (!p_cstr) {
		resize(0);
		return;
	}

	const size_t len = strlen(p_cstr);

	if (len == 0) {
		resize(0);
		return;
	}

	resize(len + 1); // include 0

	CharType *dst = this->ptrw();

	for (size_t i = 0; i <= len; i++) {
		uint8_t c = p_cstr[i] >= 0 ? p_cstr[i] : uint8_t(256 + p_cstr[i]);
		if (c == 0 && i < len) {
			print_unicode_error("NUL character", true);
			dst[i] = 0x20;
		} else {
			dst[i] = c;
		}
	}
}

void String::copy_from(const char *p_cstr, const int p_clip_to) {
	// copy Latin-1 encoded c-string directly
	if (!p_cstr) {
		resize(0);
		return;
	}

	int len = 0;
	const char *ptr = p_cstr;
	while ((p_clip_to < 0 || len < p_clip_to) && *(ptr++) != 0) {
		len++;
	}

	if (len == 0) {
		resize(0);
		return;
	}

	resize(len + 1); // include 0

	CharType *dst = this->ptrw();

	for (int i = 0; i < len; i++) {
		uint8_t c = p_cstr[i] >= 0 ? p_cstr[i] : uint8_t(256 + p_cstr[i]);
		if (c == 0) {
			print_unicode_error("NUL character", true);
			dst[i] = 0x20;
		} else {
			dst[i] = c;
		}
	}
	dst[len] = 0;
}

void String::copy_from(const wchar_t *p_cstr) {
#ifdef WINDOWS_ENABLED
	// wchar_t is 16-bit, parse as UTF-16
	parse_utf16((const char16_t *)p_cstr);
#else
	// wchar_t is 32-bit, copy directly
	copy_from((const CharType *)p_cstr);
#endif
}

void String::copy_from(const wchar_t *p_cstr, const int p_clip_to) {
#ifdef WINDOWS_ENABLED
	// wchar_t is 16-bit, parse as UTF-16
	parse_utf16((const char16_t *)p_cstr, p_clip_to);
#else
	// wchar_t is 32-bit, copy directly
	copy_from((const CharType *)p_cstr, p_clip_to);
#endif
}

void String::copy_from(const CharType &p_char) {
	if (p_char == 0) {
		print_unicode_error("NUL character", true);
		return;
	}
	/*
	if ((p_char & 0xfffff800) == 0xd800) {
		print_unicode_error(vformat("Unpaired surrogate (%x)", (uint32_t)p_char));
	}
	if (p_char > 0x10ffff) {
		print_unicode_error(vformat("Invalid unicode codepoint (%x)", (uint32_t)p_char));
	}
	*/

	resize(2);

	CharType *dst = ptrw();
	dst[0] = p_char;
	dst[1] = 0;
}

void String::copy_from(const CharType *p_cstr) {
	if (!p_cstr) {
		resize(0);
		return;
	}

	int len = 0;
	const CharType *ptr = p_cstr;
	while (*(ptr++) != 0) {
		len++;
	}

	if (len == 0) {
		resize(0);
		return;
	}

	copy_from_unchecked(p_cstr, len);
}

void String::copy_from(const CharType *p_cstr, const int p_clip_to) {
	if (!p_cstr) {
		resize(0);
		return;
	}

	int len = 0;
	const CharType *ptr = p_cstr;
	while ((p_clip_to < 0 || len < p_clip_to) && *(ptr++) != 0) {
		len++;
	}

	if (len == 0) {
		resize(0);
		return;
	}

	copy_from_unchecked(p_cstr, len);
}

// assumes the following have already been validated:
// p_char != nullptr
// p_length > 0
// p_length <= p_char strlen
void String::copy_from_unchecked(const CharType *p_char, const int p_length) {
	resize(p_length + 1);
	CharType *dst = ptrw();
	dst[p_length] = 0;

	for (int i = 0; i < p_length; i++) {
		if (p_char[i] == 0) {
			print_unicode_error("NUL character", true);
			dst[i] = 0x20;
			continue;
		}
		/*
		if ((p_char[i] & 0xfffff800) == 0xd800) {
			print_unicode_error(vformat("Unpaired surrogate (%x)", (uint32_t)p_char[i]));
		}
		if (p_char[i] > 0x10ffff) {
			print_unicode_error(vformat("Invalid unicode codepoint (%x)", (uint32_t)p_char[i]));
		}
		*/
		dst[i] = p_char[i];
	}
}

bool String::operator==(const String &p_str) const {
	if (length() != p_str.length()) {
		return false;
	}
	if (empty()) {
		return true;
	}

	int l = length();

	const CharType *src = get_data();
	const CharType *dst = p_str.get_data();

	/* Compare char by char */
	for (int i = 0; i < l; i++) {
		if (src[i] != dst[i]) {
			return false;
		}
	}

	return true;
}

bool String::operator!=(const String &p_str) const {
	return !((*this == p_str));
}

String String::operator+(const String &p_str) const {
	String res = *this;
	res += p_str;
	return res;
}

/*
String String::operator+(CharType p_char) const {
	String res = *this;
	res += p_char;
	return res;
}
*/

String &String::operator+=(const String &p_str) {
	const int lhs_len = length();
	if (lhs_len == 0) {
		*this = p_str;
		return *this;
	}

	const int rhs_len = p_str.length();
	if (rhs_len == 0) {
		return *this;
	}

	set_length(lhs_len + rhs_len);

	const CharType *src = p_str.get_data();
	CharType *dst = ptrw() + lhs_len;

	memcpy(dst, src, rhs_len * sizeof(CharType));

	return *this;
}

String &String::operator+=(CharType p_char) {
	if (p_char == 0) {
		print_unicode_error("NUL character", true);
		return *this;
	}
	/*
	if ((p_char & 0xfffff800) == 0xd800) {
		print_unicode_error(vformat("Unpaired surrogate (%x)", (uint32_t)p_char));
	}
	if (p_char > 0x10ffff) {
		print_unicode_error(vformat("Invalid unicode codepoint (%x)", (uint32_t)p_char));
	}
	*/

	const int lhs_len = length();
	set_length(lhs_len + 1);
	CharType *dst = ptrw();
	dst[lhs_len] = p_char;

	return *this;
}

String &String::operator+=(const char *p_str) {
	if (!p_str || p_str[0] == 0) {
		return *this;
	}

	const int lhs_len = length();
	const size_t rhs_len = strlen(p_str);

	set_length(lhs_len + rhs_len);

	CharType *dst = ptrw() + lhs_len;

	for (size_t i = 0; i <= rhs_len; i++) {
		uint8_t c = p_str[i] >= 0 ? p_str[i] : uint8_t(256 + p_str[i]);
		if (c == 0 && i < rhs_len) {
			print_unicode_error("NUL character", true);
			dst[i] = 0x20;
		} else {
			dst[i] = c;
		}
	}

	return *this;
}

String &String::operator+=(const wchar_t *p_str) {
#ifdef WINDOWS_ENABLED
	// wchar_t is 16-bit
	*this += String::utf16((const char16_t *)p_str);
#else
	// wchar_t is 32-bit
	*this += String((const CharType *)p_str);
#endif
	return *this;
}

String &String::operator+=(const CharType *p_str) {
	*this += String(p_str);
	return *this;
}

void String::operator=(const char *p_str) {
	copy_from(p_str);
}

void String::operator=(const CharType *p_str) {
	copy_from(p_str);
}

void String::operator=(const wchar_t *p_str) {
	copy_from(p_str);
}

bool String::operator==(const char *p_str) const {
	// compare Latin-1 encoded c-string
	int len = 0;
	const char *aux = p_str;

	while (*(aux++) != 0) {
		len++;
	}

	if (length() != len) {
		return false;
	}
	if (empty()) {
		return true;
	}

	int l = length();

	const CharType *dst = get_data();

	// Compare char by char
	for (int i = 0; i < l; i++) {
		if ((CharType)p_str[i] != dst[i]) {
			return false;
		}
	}

	return true;
}

bool String::operator==(const wchar_t *p_str) const {
#ifdef WINDOWS_ENABLED
	// wchar_t is 16-bit, parse as UTF-16
	return *this == String::utf16((const char16_t *)p_str);
#else
	// wchar_t is 32-bit, compare char by char
	return *this == (const CharType *)p_str;
#endif
}

bool String::operator==(const CharType *p_str) const {
	int len = 0;
	const CharType *aux = p_str;

	while (*(aux++) != 0) {
		len++;
	}

	if (length() != len) {
		return false;
	}
	if (empty()) {
		return true;
	}

	int l = length();

	const CharType *dst = get_data();

	/* Compare char by char */
	for (int i = 0; i < l; i++) {
		if (p_str[i] != dst[i]) {
			return false;
		}
	}

	return true;
}

bool String::operator==(const StrRange &p_str_range) const {
	int len = p_str_range.len;

	if (length() != len) {
		return false;
	}
	if (empty()) {
		return true;
	}

	const CharType *c_str = p_str_range.c_str;
	const CharType *dst = &operator[](0);

	/* Compare char by char */
	for (int i = 0; i < len; i++) {
		if (c_str[i] != dst[i]) {
			return false;
		}
	}

	return true;
}

bool String::operator!=(const char *p_str) const {
	return (!(*this == p_str));
}

bool String::operator!=(const wchar_t *p_str) const {
	return (!(*this == p_str));
}

bool String::operator!=(const CharType *p_str) const {
	return (!(*this == p_str));
}

bool String::operator<(const char *p_str) const {
	if (empty() && p_str[0] == 0) {
		return false;
	}
	if (empty()) {
		return true;
	}
	return is_str_less(get_data(), p_str);
}

bool String::operator<(const wchar_t *p_str) const {
	if (empty() && p_str[0] == 0) {
		return false;
	}
	if (empty()) {
		return true;
	}

#ifdef WINDOWS_ENABLED
	// wchar_t is 16-bit
	return is_str_less(get_data(), String::utf16((const char16_t *)p_str).get_data());
#else
	// wchar_t is 32-bit
	return is_str_less(get_data(), (const CharType *)p_str);
#endif
}

bool String::operator<(const CharType *p_str) const {
	if (empty() && p_str[0] == 0) {
		return false;
	}
	if (empty()) {
		return true;
	}

	return is_str_less(get_data(), p_str);
}

bool String::operator<(const String &p_str) const {
	return operator<(p_str.get_data());
}

bool String::operator<=(const String &p_str) const {
	return !(p_str < *this);
}

bool String::operator>(const String &p_str) const {
	return p_str < *this;
}

bool String::operator>=(const String &p_str) const {
	return !(*this < p_str);
}

signed char String::nocasecmp_to(const String &p_str) const {
	if (empty() && p_str.empty()) {
		return 0;
	}
	if (empty()) {
		return -1;
	}
	if (p_str.empty()) {
		return 1;
	}

	const CharType *that_str = p_str.get_data();
	const CharType *this_str = get_data();

	while (true) {
		if (*that_str == 0 && *this_str == 0) {
			return 0; //we're equal
		} else if (*this_str == 0) {
			return -1; //if this is empty, and the other one is not, then we're less.. I think?
		} else if (*that_str == 0) {
			return 1; //otherwise the other one is smaller..
		} else if (_find_upper(*this_str) < _find_upper(*that_str)) { //more than
			return -1;
		} else if (_find_upper(*this_str) > _find_upper(*that_str)) { //less than
			return 1;
		}

		this_str++;
		that_str++;
	}
}

signed char String::casecmp_to(const String &p_str) const {
	if (empty() && p_str.empty()) {
		return 0;
	}
	if (empty()) {
		return -1;
	}
	if (p_str.empty()) {
		return 1;
	}

	const CharType *that_str = p_str.get_data();
	const CharType *this_str = get_data();

	while (true) {
		if (*that_str == 0 && *this_str == 0) {
			return 0; //we're equal
		} else if (*this_str == 0) {
			return -1; //if this is empty, and the other one is not, then we're less.. I think?
		} else if (*that_str == 0) {
			return 1; //otherwise the other one is smaller..
		} else if (*this_str < *that_str) { //more than
			return -1;
		} else if (*this_str > *that_str) { //less than
			return 1;
		}

		this_str++;
		that_str++;
	}
}

signed char String::naturalnocasecmp_to(const String &p_str) const {
	const CharType *this_str = get_data();
	const CharType *that_str = p_str.get_data();

	if (this_str && that_str) {
		while (*this_str == '.' || *that_str == '.') {
			if (*this_str++ != '.') {
				return 1;
			}
			if (*that_str++ != '.') {
				return -1;
			}
			if (!*that_str) {
				return 1;
			}
			if (!*this_str) {
				return -1;
			}
		}

		while (*this_str) {
			if (!*that_str) {
				return 1;
			} else if (is_digit(*this_str)) {
				if (!is_digit(*that_str)) {
					return -1;
				}

				// Keep ptrs to start of numerical sequences
				const CharType *this_substr = this_str;
				const CharType *that_substr = that_str;

				// Compare lengths of both numerical sequences, ignoring leading zeros
				while (is_digit(*this_str)) {
					this_str++;
				}
				while (is_digit(*that_str)) {
					that_str++;
				}
				while (*this_substr == '0') {
					this_substr++;
				}
				while (*that_substr == '0') {
					that_substr++;
				}
				int this_len = this_str - this_substr;
				int that_len = that_str - that_substr;

				if (this_len < that_len) {
					return -1;
				} else if (this_len > that_len) {
					return 1;
				}

				// If lengths equal, compare lexicographically
				while (this_substr != this_str && that_substr != that_str) {
					if (*this_substr < *that_substr) {
						return -1;
					} else if (*this_substr > *that_substr) {
						return 1;
					}
					this_substr++;
					that_substr++;
				}
			} else if (is_digit(*that_str)) {
				return 1;
			} else {
				if (_find_upper(*this_str) < _find_upper(*that_str)) { //more than
					return -1;
				} else if (_find_upper(*this_str) > _find_upper(*that_str)) { //less than
					return 1;
				}

				this_str++;
				that_str++;
			}
		}
		if (*that_str) {
			return -1;
		}
	}

	return 0;
}

const CharType *String::get_data() const {
	static const CharType zero = 0;
	return size() ? &operator[](0) : &zero;
}

bool String::is_valid_string() const {
	int l = length();
	const CharType *src = get_data();
	bool valid = true;
	for (int i = 0; i < l; i++) {
		valid = valid && (src[i] < 0xd800 || (src[i] > 0xdfff && src[i] <= 0x10ffff));
	}
	return valid;
}

void String::print_unicode_error(const String &p_message, bool p_critical) const {
	/*
	if (p_critical) {
		print_error(vformat("Unicode parsing error, some characters were replaced with spaces: %s", p_message));
	} else {
		print_error(vformat("Unicode parsing error: %s", p_message));
	}
	*/
}

/* complex helpers */

String String::substr(int p_from, int p_chars) const {
	if (p_chars == -1) {
		p_chars = length() - p_from;
	}

	if (empty() || p_from < 0 || p_from >= length() || p_chars <= 0) {
		return "";
	}

	if ((p_from + p_chars) > length()) {
		p_chars = length() - p_from;
	}

	if (p_from == 0 && p_chars >= length()) {
		return String(*this);
	}

	String s = String();
	s.copy_from_unchecked(&get_data()[p_from], p_chars);
	return s;
}

String String::substr_index(const int start_index, const int end_index) const {
	int s = length();

	if (start_index < 0 || start_index >= s || end_index < 0) {
		return "";
	}

	if (start_index > end_index) {
		return "";
	}

	if (end_index >= s) {
		return substr(start_index, (s - 1) - start_index);
	}

	return substr(start_index, end_index - start_index);
}

int String::find(const String &p_str, int p_from) const {
	if (p_from < 0) {
		return -1;
	}

	const int src_len = p_str.length();

	const int len = length();

	if (src_len == 0 || len == 0) {
		return -1; // won't find anything!
	}

	const CharType *src = get_data();
	const CharType *str = p_str.get_data();

	for (int i = p_from; i <= (len - src_len); i++) {
		bool found = true;
		for (int j = 0; j < src_len; j++) {
			int read_pos = i + j;

			if (read_pos >= len) {
				ERR_PRINT("read_pos>=len");
				return -1;
			};

			if (src[read_pos] != str[j]) {
				found = false;
				break;
			}
		}

		if (found) {
			return i;
		}
	}

	return -1;
}

int String::find(const char *p_str, int p_from) const {
	if (p_from < 0) {
		return -1;
	}

	const int len = length();

	if (len == 0) {
		return -1; // won't find anything!
	}

	const CharType *src = get_data();

	int src_len = 0;
	while (p_str[src_len] != '\0') {
		src_len++;
	}

	if (src_len == 1) {
		const CharType needle = p_str[0];

		for (int i = p_from; i < len; i++) {
			if (src[i] == needle) {
				return i;
			}
		}

	} else {
		for (int i = p_from; i <= (len - src_len); i++) {
			bool found = true;
			for (int j = 0; j < src_len; j++) {
				int read_pos = i + j;

				if (read_pos >= len) {
					ERR_PRINT("read_pos>=len");
					return -1;
				};

				if (src[read_pos] != (CharType)p_str[j]) {
					found = false;
					break;
				}
			}

			if (found) {
				return i;
			}
		}
	}

	return -1;
}

int String::find_char(const CharType &p_char, int p_from) const {
	return _cowdata.find(p_char, p_from);
}

int String::find_last(const String &p_str) const {
	return rfind(p_str);
}

int String::findn(const String &p_str, int p_from) const {
	if (p_from < 0) {
		return -1;
	}

	int src_len = p_str.length();

	if (src_len == 0 || length() == 0) {
		return -1; // won't find anything!
	}

	const CharType *srcd = get_data();

	for (int i = p_from; i <= (length() - src_len); i++) {
		bool found = true;
		for (int j = 0; j < src_len; j++) {
			int read_pos = i + j;

			if (read_pos >= length()) {
				ERR_PRINT("read_pos>=length()");
				return -1;
			};

			CharType src = _find_lower(srcd[read_pos]);
			CharType dst = _find_lower(p_str[j]);

			if (src != dst) {
				found = false;
				break;
			}
		}

		if (found) {
			return i;
		}
	}

	return -1;
}

int String::rfind(const String &p_str, int p_from) const {
	// establish a limit
	int limit = length() - p_str.length();
	if (limit < 0) {
		return -1;
	}

	// establish a starting point
	if (p_from < 0) {
		p_from = limit;
	} else if (p_from > limit) {
		p_from = limit;
	}

	int src_len = p_str.length();
	int len = length();

	if (src_len == 0 || len == 0) {
		return -1; // won't find anything!
	}

	const CharType *src = get_data();

	for (int i = p_from; i >= 0; i--) {
		bool found = true;
		for (int j = 0; j < src_len; j++) {
			int read_pos = i + j;

			if (read_pos >= len) {
				ERR_PRINT("read_pos>=len");
				return -1;
			};

			if (src[read_pos] != p_str[j]) {
				found = false;
				break;
			}
		}

		if (found) {
			return i;
		}
	}

	return -1;
}

int String::rfindn(const String &p_str, int p_from) const {
	// establish a limit
	int limit = length() - p_str.length();
	if (limit < 0) {
		return -1;
	}

	// establish a starting point
	if (p_from < 0) {
		p_from = limit;
	} else if (p_from > limit) {
		p_from = limit;
	}

	int src_len = p_str.length();
	int len = length();

	if (src_len == 0 || len == 0) {
		return -1; // won't find anything!
	}

	const CharType *src = get_data();

	for (int i = p_from; i >= 0; i--) {
		bool found = true;
		for (int j = 0; j < src_len; j++) {
			int read_pos = i + j;

			if (read_pos >= len) {
				ERR_PRINT("read_pos>=len");
				return -1;
			};

			CharType srcc = _find_lower(src[read_pos]);
			CharType dstc = _find_lower(p_str[j]);

			if (srcc != dstc) {
				found = false;
				break;
			}
		}

		if (found) {
			return i;
		}
	}

	return -1;
}

int String::findmk(const Vector<String> &p_keys, int p_from, int *r_key) const {
	if (p_from < 0) {
		return -1;
	}
	if (p_keys.size() == 0) {
		return -1;
	}

	//int src_len=p_str.length();
	const String *keys = &p_keys[0];
	int key_count = p_keys.size();
	int len = length();

	if (len == 0) {
		return -1; // won't find anything!
	}

	const CharType *src = get_data();

	for (int i = p_from; i < len; i++) {
		bool found = true;
		for (int k = 0; k < key_count; k++) {
			found = true;
			if (r_key) {
				*r_key = k;
			}
			const CharType *cmp = keys[k].get_data();
			int l = keys[k].length();

			for (int j = 0; j < l; j++) {
				int read_pos = i + j;

				if (read_pos >= len) {
					found = false;
					break;
				};

				if (src[read_pos] != cmp[j]) {
					found = false;
					break;
				}
			}
			if (found) {
				break;
			}
		}

		if (found) {
			return i;
		}
	}

	return -1;
}

int String::find_first_difference_index(const String &p_str) const {
	const int olen = p_str.length();
	const int len = length();
	const int c = len < olen ? len : olen;

	const CharType *p = get_data();
	const CharType *op = p_str.get_data();

	for (int i = 0; i < c; ++i) {
		if (p[i] != op[i]) {
			return i;
		}
	}

	return c;
}

bool String::is_word_at(const int index, const char *p_str) const {
	int size = length();

	ERR_FAIL_INDEX_V(index, size, false);

	int i = 0;

	while (p_str[i] != '\0') {
		int iind = index + i;

		if (iind >= size) {
			return false;
		}

		if (operator[](iind) != (CharType)p_str[i]) {
			return false;
		}

		++i;
	}

	return true;
}
bool String::is_word_at(const int index, const String &p_str) const {
	int size = length();

	ERR_FAIL_INDEX_V(index, size, false);

	if (index + p_str.length() >= size) {
		return false;
	}

	for (int i = 0; i < p_str.length(); ++i) {
		int iind = index + i;

		if (operator[](iind) != p_str[i]) {
			return false;
		}
	}

	return true;
}

bool String::match(const String &p_wildcard) const {
	if (!p_wildcard.length() || !length()) {
		return false;
	}

	return _wildcard_match(p_wildcard.get_data(), get_data(), true);
}

bool String::matchn(const String &p_wildcard) const {
	if (!p_wildcard.length() || !length()) {
		return false;
	}
	return _wildcard_match(p_wildcard.get_data(), get_data(), false);
}

bool String::begins_with(const String &p_string) const {
	int l = p_string.length();
	if (l > length()) {
		return false;
	}

	if (l == 0) {
		return true;
	}

	const CharType *p = &p_string[0];
	const CharType *s = &operator[](0);

	for (int i = 0; i < l; i++) {
		if (p[i] != s[i]) {
			return false;
		}
	}

	return true;
}

bool String::begins_with(const char *p_string) const {
	int l = length();
	if (l == 0 || !p_string) {
		return false;
	}

	const CharType *str = &operator[](0);
	int i = 0;

	while (*p_string && i < l) {
		if ((CharType)(*p_string) != str[i]) {
			return false;
		}
		i++;
		p_string++;
	}

	return *p_string == 0;
}

bool String::ends_with(const String &p_string) const {
	int l = p_string.length();
	if (l > length()) {
		return false;
	}

	if (l == 0) {
		return true;
	}

	const CharType *p = &p_string[0];
	const CharType *s = &operator[](length() - l);

	for (int i = 0; i < l; i++) {
		if (p[i] != s[i]) {
			return false;
		}
	}

	return true;
}

bool String::is_enclosed_in(const String &p_string) const {
	return begins_with(p_string) && ends_with(p_string);
}

bool String::is_subsequence_of(const String &p_string) const {
	return _base_is_subsequence_of(p_string, false);
}

bool String::is_subsequence_ofi(const String &p_string) const {
	return _base_is_subsequence_of(p_string, true);
}

bool String::is_quoted() const {
	return is_enclosed_in("\"") || is_enclosed_in("'");
}

Vector<String> String::bigrams() const {
	int n_pairs = length() - 1;
	Vector<String> b;
	if (n_pairs <= 0) {
		return b;
	}
	b.resize(n_pairs);
	for (int i = 0; i < n_pairs; i++) {
		b.write[i] = substr(i, 2);
	}
	return b;
}

// Similarity according to Sorensen-Dice coefficient
float String::similarity(const String &p_string) const {
	if (operator==(p_string)) {
		// Equal strings are totally similar
		return 1.0f;
	}
	if (length() < 2 || p_string.length() < 2) {
		// No way to calculate similarity without a single bigram
		return 0.0f;
	}

	Vector<String> src_bigrams = bigrams();
	Vector<String> tgt_bigrams = p_string.bigrams();

	int src_size = src_bigrams.size();
	int tgt_size = tgt_bigrams.size();

	float sum = src_size + tgt_size;
	float inter = 0;
	for (int i = 0; i < src_size; i++) {
		for (int j = 0; j < tgt_size; j++) {
			if (src_bigrams[i] == tgt_bigrams[j]) {
				inter++;
				break;
			}
		}
	}

	return (2.0f * inter) / sum;
}

/*
String String::format(const Variant &values, String placeholder) const {
	String new_string = String(this->ptr());

	if (values.get_type() == Variant::ARRAY) {
		Array values_arr = values;

		for (int i = 0; i < values_arr.size(); i++) {
			String i_as_str = String::num_int64(i);

			if (values_arr[i].get_type() == Variant::ARRAY) { //Array in Array structure [["name","RobotGuy"],[0,"pandemonium"],["strength",9000.91]]
				Array value_arr = values_arr[i];

				if (value_arr.size() == 2) {
					Variant v_key = value_arr[0];
					String key = v_key;

					Variant v_val = value_arr[1];
					String val = v_val;

					new_string = new_string.replace(placeholder.replace("_", key), val);
				} else {
					ERR_PRINT(String("STRING.format Inner Array size != 2 ").ascii().get_data());
				}
			} else { //Array structure ["RobotGuy","Logis","rookie"]
				Variant v_val = values_arr[i];
				String val = v_val;

				if (placeholder.find("_") > -1) {
					new_string = new_string.replace(placeholder.replace("_", i_as_str), val);
				} else {
					new_string = new_string.replace_first(placeholder, val);
				}
			}
		}
	} else if (values.get_type() == Variant::DICTIONARY) {
		Dictionary d = values;
		List<Variant> keys;
		d.get_key_list(&keys);

		for (List<Variant>::Element *E = keys.front(); E; E = E->next()) {
			String key = E->get();
			String val = d[E->get()];

			new_string = new_string.replace(placeholder.replace("_", key), val);
		}
	} else {
		ERR_PRINT(String("Invalid type: use Array or Dictionary.").ascii().get_data());
	}

	return new_string;
}
*/

String String::replace_first(const String &p_key, const String &p_with) const {
	int pos = find(p_key);
	if (pos >= 0) {
		return substr(0, pos) + p_with + substr(pos + p_key.length(), length());
	}

	return *this;
}

String String::replace(const String &p_key, const String &p_with) const {
	String new_string;
	int search_from = 0;
	int result = 0;

	while ((result = find(p_key, search_from)) >= 0) {
		new_string += substr(search_from, result - search_from);
		new_string += p_with;
		search_from = result + p_key.length();
	}

	if (search_from == 0) {
		return *this;
	}

	new_string += substr(search_from, length() - search_from);

	return new_string;
}

String String::replace(const char *p_key, const char *p_with) const {
	String new_string;
	int search_from = 0;
	int result = 0;

	while ((result = find(p_key, search_from)) >= 0) {
		new_string += substr(search_from, result - search_from);
		new_string += p_with;
		int k = 0;
		while (p_key[k] != '\0') {
			k++;
		}
		search_from = result + k;
	}

	if (search_from == 0) {
		return *this;
	}

	new_string += substr(search_from, length() - search_from);

	return new_string;
}

String String::replacen(const String &p_key, const String &p_with) const {
	String new_string;
	int search_from = 0;
	int result = 0;

	while ((result = findn(p_key, search_from)) >= 0) {
		new_string += substr(search_from, result - search_from);
		new_string += p_with;
		search_from = result + p_key.length();
	}

	if (search_from == 0) {
		return *this;
	}

	new_string += substr(search_from, length() - search_from);
	return new_string;
}

String String::newline_to_br() const {
	String r = replace("\r\n", "<br>");
	return r.replace("\n", "<br>");
}

String String::repeat(int p_count) const {
	ERR_FAIL_COND_V_MSG(p_count < 0, "", "Parameter count should be a positive number.");

	int len = length();
	String new_string = *this;
	new_string.resize(p_count * len + 1);

	CharType *dst = new_string.ptrw();
	int offset = 1;
	int stride = 1;
	while (offset < p_count) {
		memcpy(dst + offset * len, dst, stride * len * sizeof(CharType));
		offset += stride;
		stride = MIN(stride * 2, p_count - offset);
	}
	dst[p_count * len] = _null;

	return new_string;
}

String String::insert(int p_at_pos, const String &p_string) const {
	if (p_at_pos < 0) {
		return *this;
	}

	if (p_at_pos > length()) {
		p_at_pos = length();
	}

	String pre;
	if (p_at_pos > 0) {
		pre = substr(0, p_at_pos);
	}

	String post;
	if (p_at_pos < length()) {
		post = substr(p_at_pos, length() - p_at_pos);
	}

	return pre + p_string + post;
}

String String::pad_decimals(int p_digits) const {
	String s = *this;
	int c = s.find(".");

	if (c == -1) {
		if (p_digits <= 0) {
			return s;
		}
		s += ".";
		c = s.length() - 1;
	} else {
		if (p_digits <= 0) {
			return s.substr(0, c);
		}
	}

	if (s.length() - (c + 1) > p_digits) {
		s = s.substr(0, c + p_digits + 1);
	} else {
		while (s.length() - (c + 1) < p_digits) {
			s += "0";
		}
	}
	return s;
}

String String::pad_zeros(int p_digits) const {
	String s = *this;
	int end = s.find(".");

	if (end == -1) {
		end = s.length();
	}

	if (end == 0) {
		return s;
	}

	int begin = 0;

	while (begin < end && (s[begin] < '0' || s[begin] > '9')) {
		begin++;
	}

	if (begin >= end) {
		return s;
	}

	while (end - begin < p_digits) {
		s = s.insert(begin, "0");
		end++;
	}

	return s;
}

String String::trim_prefix(const String &p_prefix) const {
	String s = *this;
	if (s.begins_with(p_prefix)) {
		return s.substr(p_prefix.length(), s.length() - p_prefix.length());
	}
	return s;
}

String String::trim_suffix(const String &p_suffix) const {
	String s = *this;
	if (s.ends_with(p_suffix)) {
		return s.substr(0, s.length() - p_suffix.length());
	}
	return s;
}

// Left-pad with a character.
String String::lpad(int min_length, const String &character) const {
	String s = *this;
	int padding = min_length - s.length();
	if (padding > 0) {
		for (int i = 0; i < padding; i++) {
			s = character + s;
		}
	}

	return s;
}

// Right-pad with a character.
String String::rpad(int min_length, const String &character) const {
	String s = *this;
	int padding = min_length - s.length();
	if (padding > 0) {
		for (int i = 0; i < padding; i++) {
			s = s + character;
		}
	}

	return s;
}

String String::quote(String quotechar) const {
	return quotechar + *this + quotechar;
}

String String::unquote() const {
	if (!is_quoted()) {
		return *this;
	}

	return substr(1, length() - 2);
}

String String::num(double p_num, int p_decimals) {
	if (Math::is_nan(p_num)) {
		return "nan";
	}

	if (Math::is_inf(p_num)) {
		if (signbit(p_num)) {
			return "-inf";
		} else {
			return "inf";
		}
	}

#ifndef NO_USE_STDLIB

	if (p_decimals > 16) {
		p_decimals = 16;
	}

	char fmt[7];
	fmt[0] = '%';
	fmt[1] = '.';

	if (p_decimals < 0) {
		fmt[1] = 'l';
		fmt[2] = 'f';
		fmt[3] = 0;

	} else if (p_decimals < 10) {
		fmt[2] = '0' + p_decimals;
		fmt[3] = 'l';
		fmt[4] = 'f';
		fmt[5] = 0;
	} else {
		fmt[2] = '0' + (p_decimals / 10);
		fmt[3] = '0' + (p_decimals % 10);
		fmt[4] = 'l';
		fmt[5] = 'f';
		fmt[6] = 0;
	}
	char buf[256];

#if defined(__GNUC__) || defined(_MSC_VER)
	snprintf(buf, 256, fmt, p_num);
#else
	sprintf(buf, fmt, p_num);
#endif

	buf[255] = 0;
	//destroy trailing zeroes
	{
		bool period = false;
		int z = 0;
		while (buf[z]) {
			if (buf[z] == '.') {
				period = true;
			}
			z++;
		}

		if (period) {
			z--;
			while (z > 0) {
				if (buf[z] == '0') {
					buf[z] = 0;
				} else if (buf[z] == '.') {
					buf[z] = 0;
					break;
				} else {
					break;
				}

				z--;
			}
		}
	}

	return buf;
#else

	String s;
	String sd;
	/* integer part */

	bool neg = p_num < 0;
	p_num = ABS(p_num);
	int intn = (int)p_num;

	/* decimal part */

	if (p_decimals > 0 || (p_decimals == -1 && (int)p_num != p_num)) {
		double dec = p_num - (double)((int)p_num);

		int digit = 0;
		if (p_decimals > MAX_DIGITS)
			p_decimals = MAX_DIGITS;

		int dec_int = 0;
		int dec_max = 0;

		while (true) {
			dec *= 10.0;
			dec_int = dec_int * 10 + (int)dec % 10;
			dec_max = dec_max * 10 + 9;
			digit++;

			if (p_decimals == -1) {
				if (digit == MAX_DIGITS) //no point in going to infinite
					break;

				if ((dec - (double)((int)dec)) < 1e-6)
					break;
			}

			if (digit == p_decimals)
				break;
		}
		dec *= 10;
		int last = (int)dec % 10;

		if (last > 5) {
			if (dec_int == dec_max) {
				dec_int = 0;
				intn++;
			} else {
				dec_int++;
			}
		}

		String decimal;
		for (int i = 0; i < digit; i++) {
			char num[2] = { 0, 0 };
			num[0] = '0' + dec_int % 10;
			decimal = num + decimal;
			dec_int /= 10;
		}
		sd = '.' + decimal;
	}

	if (intn == 0)

		s = "0";
	else {
		while (intn) {
			CharType num = '0' + (intn % 10);
			intn /= 10;
			s = num + s;
		}
	}

	s = s + sd;
	if (neg)
		s = "-" + s;
	return s;
#endif
}

String String::num_scientific(double p_num) {
	if (Math::is_nan(p_num)) {
		return "nan";
	}

	if (Math::is_inf(p_num)) {
		if (signbit(p_num)) {
			return "-inf";
		} else {
			return "inf";
		}
	}

#ifndef NO_USE_STDLIB

	char buf[256];

#if defined(__GNUC__) || defined(_MSC_VER)

#if defined(__MINGW32__) && defined(_TWO_DIGIT_EXPONENT) && !defined(_UCRT)
	// MinGW requires _set_output_format() to conform to C99 output for printf
	unsigned int old_exponent_format = _set_output_format(_TWO_DIGIT_EXPONENT);
#endif
	snprintf(buf, 256, "%lg", p_num);

#if defined(__MINGW32__) && defined(_TWO_DIGIT_EXPONENT) && !defined(_UCRT)
	_set_output_format(old_exponent_format);
#endif

#else
	sprintf(buf, "%.16lg", p_num);
#endif

	buf[255] = 0;

	return buf;
#else

	return String::num(p_num);
#endif
}

String String::num_real(double p_num) {
	if (Math::is_nan(p_num)) {
		return "nan";
	}

	if (Math::is_inf(p_num)) {
		if (signbit(p_num)) {
			return "-inf";
		} else {
			return "inf";
		}
	}

	String s;
	String sd;
	/* integer part */

	bool neg = p_num < 0;
	p_num = ABS(p_num);
	int intn = (int)p_num;

	/* decimal part */

	if ((int)p_num != p_num) {
		double dec = p_num - (double)((int)p_num);

		int digit = 0;
		int decimals = MAX_DIGITS;

		int dec_int = 0;
		int dec_max = 0;

		while (true) {
			dec *= 10.0;
			dec_int = dec_int * 10 + (int)dec % 10;
			dec_max = dec_max * 10 + 9;
			digit++;

			if ((dec - (double)((int)dec)) < 1e-6) {
				break;
			}

			if (digit == decimals) {
				break;
			}
		}

		dec *= 10;
		int last = (int)dec % 10;

		if (last > 5) {
			if (dec_int == dec_max) {
				dec_int = 0;
				intn++;
			} else {
				dec_int++;
			}
		}

		String decimal;
		for (int i = 0; i < digit; i++) {
			char num[2] = { 0, 0 };
			num[0] = '0' + dec_int % 10;
			decimal = num + decimal;
			dec_int /= 10;
		}
		sd = '.' + decimal;
	} else {
		sd = ".0";
	}

	if (intn == 0) {
		s = "0";
	} else {
		while (intn) {
			CharType num = '0' + (intn % 10);
			intn /= 10;
			s = num + s;
		}
	}

	s = s + sd;
	if (neg) {
		s = "-" + s;
	}
	return s;
}

String String::num_int64(int64_t p_num, int base, bool capitalize_hex) {
	bool sign = p_num < 0;

	int64_t n = p_num;

	int chars = 0;
	do {
		n /= base;
		chars++;
	} while (n);

	if (sign) {
		chars++;
	}
	String s;
	s.resize(chars + 1);
	CharType *c = s.ptrw();
	c[chars] = 0;
	n = p_num;
	do {
		int mod = ABS(n % base);
		if (mod >= 10) {
			char a = (capitalize_hex ? 'A' : 'a');
			c[--chars] = a + (mod - 10);
		} else {
			c[--chars] = '0' + mod;
		}

		n /= base;
	} while (n);

	if (sign) {
		c[0] = '-';
	}

	return s;
}

String String::num_uint64(uint64_t p_num, int base, bool capitalize_hex) {
	uint64_t n = p_num;

	int chars = 0;
	do {
		n /= base;
		chars++;
	} while (n);

	String s;
	s.resize(chars + 1);
	CharType *c = s.ptrw();
	c[chars] = 0;
	n = p_num;
	do {
		int mod = n % base;
		if (mod >= 10) {
			char a = (capitalize_hex ? 'A' : 'a');
			c[--chars] = a + (mod - 10);
		} else {
			c[--chars] = '0' + mod;
		}

		n /= base;
	} while (n);

	return s;
}

String String::chr(CharType p_char) {
	CharType c[2] = { p_char, 0 };
	return String(c);
}

String String::md5(const uint8_t *p_md5) {
	return String::hex_encode_buffer(p_md5, 16);
}

String String::hex_encode_buffer(const uint8_t *p_buffer, int p_len) {
	static const char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	String ret;
	char v[2] = { 0, 0 };

	for (int i = 0; i < p_len; i++) {
		v[0] = hex[p_buffer[i] >> 4];
		ret += v;
		v[0] = hex[p_buffer[i] & 0xF];
		ret += v;
	}

	return ret;
}

String String::bool_num(bool p_val) {
	if (p_val) {
		return "1";
	} else {
		return "0";
	}
}

String String::bool_str(bool p_val) {
	if (p_val) {
		return "true";
	} else {
		return "false";
	}
}

bool String::is_numeric() const {
	if (length() == 0) {
		return false;
	};

	int s = 0;
	if (operator[](0) == '-') {
		++s;
	}
	bool dot = false;
	for (int i = s; i < length(); i++) {
		CharType c = operator[](i);
		if (c == '.') {
			if (dot) {
				return false;
			};
			dot = true;
			continue;
		}
		if (c < '0' || c > '9') {
			return false;
		};
	};

	return true; // TODO: Use the parser below for this instead
};

bool String::is_zero() const {
	int size = length();

	if (size == 0) {
		return false;
	}

	int starti = 0;

	if (operator[](0) == '-') {
		starti += 1;
	}

	bool had_dot = false;
	for (int i = starti; i < size; ++i) {
		CharType c = operator[](i);

		if (c == '.') {
			if (!had_dot) {
				had_dot = true;
				continue;
			} else {
				return false;
			}
		}

		if (c != '0') {
			return false;
		}
	}

	return true;
}

String String::capitalize() const {
	String aux = this->camelcase_to_underscore(true).replace("_", " ").strip_edges();
	String cap;
	for (int i = 0; i < aux.get_slice_count(" "); i++) {
		String slice = aux.get_slicec(' ', i);
		if (slice.length() > 0) {
			slice[0] = _find_upper(slice[0]);
			if (i > 0) {
				cap += " ";
			}
			cap += slice;
		}
	}

	return cap;
}

String String::camelcase_to_underscore(bool lowercase) const {
	const CharType *cstr = get_data();
	String new_string;
	const char A = 'A', Z = 'Z';
	const char a = 'a', z = 'z';
	int start_index = 0;

	for (int i = 1; i < this->size(); i++) {
		bool is_upper = cstr[i] >= A && cstr[i] <= Z;
		bool is_number = cstr[i] >= '0' && cstr[i] <= '9';
		bool are_next_2_lower = false;
		bool is_next_lower = false;
		bool is_next_number = false;
		bool was_precedent_upper = cstr[i - 1] >= A && cstr[i - 1] <= Z;
		bool was_precedent_number = cstr[i - 1] >= '0' && cstr[i - 1] <= '9';

		if (i + 2 < this->size()) {
			are_next_2_lower = cstr[i + 1] >= a && cstr[i + 1] <= z && cstr[i + 2] >= a && cstr[i + 2] <= z;
		}

		if (i + 1 < this->size()) {
			is_next_lower = cstr[i + 1] >= a && cstr[i + 1] <= z;
			is_next_number = cstr[i + 1] >= '0' && cstr[i + 1] <= '9';
		}

		const bool cond_a = is_upper && !was_precedent_upper && !was_precedent_number;
		const bool cond_b = was_precedent_upper && is_upper && are_next_2_lower;
		const bool cond_c = is_number && !was_precedent_number;
		const bool can_break_number_letter = is_number && !was_precedent_number && is_next_lower;
		const bool can_break_letter_number = !is_number && was_precedent_number && (is_next_lower || is_next_number);

		bool should_split = cond_a || cond_b || cond_c || can_break_number_letter || can_break_letter_number;
		if (should_split) {
			new_string += this->substr(start_index, i - start_index) + "_";
			start_index = i;
		}
	}

	new_string += this->substr(start_index, this->size() - start_index);
	return lowercase ? new_string.to_lower() : new_string;
}

int String::get_slice_count(String p_splitter) const {
	if (empty()) {
		return 0;
	}
	if (p_splitter.empty()) {
		return 0;
	}

	int pos = 0;
	int slices = 1;

	while ((pos = find(p_splitter, pos)) >= 0) {
		slices++;
		pos += p_splitter.length();
	}

	return slices;
}

String String::get_slice(String p_splitter, int p_slice) const {
	if (empty() || p_splitter.empty()) {
		return "";
	}

	int pos = 0;
	int prev_pos = 0;
	//int slices=1;
	if (p_slice < 0) {
		return "";
	}
	if (find(p_splitter) == -1) {
		return *this;
	}

	int i = 0;
	while (true) {
		pos = find(p_splitter, pos);
		if (pos == -1) {
			pos = length(); //reached end
		}

		int from = prev_pos;
		//int to=pos;

		if (p_slice == i) {
			return substr(from, pos - from);
		}

		if (pos == length()) { //reached end and no find
			break;
		}
		pos += p_splitter.length();
		prev_pos = pos;
		i++;
	}

	return ""; //no find!
}

String String::get_slicec(CharType p_splitter, int p_slice) const {
	if (empty()) {
		return String();
	}

	if (p_slice < 0) {
		return String();
	}

	const CharType *c = this->ptr();
	int i = 0;
	int prev = 0;
	int count = 0;
	while (true) {
		if (c[i] == 0 || c[i] == p_splitter) {
			if (p_slice == count) {
				return substr(prev, i - prev);
			} else if (c[i] == 0) {
				return String();
			} else {
				count++;
				prev = i + 1;
			}
		}

		i++;
	}
}

Vector<String> String::split(const String &p_splitter, bool p_allow_empty, int p_maxsplit) const {
	Vector<String> ret;
	int from = 0;
	int len = length();

	while (true) {
		int end = find(p_splitter, from);
		if (end < 0) {
			end = len;
		}
		if (p_allow_empty || (end > from)) {
			if (p_maxsplit <= 0) {
				ret.push_back(substr(from, end - from));
			} else {
				// Put rest of the string and leave cycle.
				if (p_maxsplit == ret.size()) {
					ret.push_back(substr(from, len));
					break;
				}

				// Otherwise, push items until positive limit is reached.
				ret.push_back(substr(from, end - from));
			}
		}

		if (end == len) {
			break;
		}

		from = end + p_splitter.length();
	}

	return ret;
}

Vector<String> String::rsplit(const String &p_splitter, bool p_allow_empty, int p_maxsplit) const {
	Vector<String> ret;
	const int len = length();
	int remaining_len = len;

	while (true) {
		if (remaining_len < p_splitter.length() || (p_maxsplit > 0 && p_maxsplit == ret.size())) {
			// no room for another splitter or hit max splits, push what's left and we're done
			if (p_allow_empty || remaining_len > 0) {
				ret.push_back(substr(0, remaining_len));
			}
			break;
		}

		int left_edge = rfind(p_splitter, remaining_len - p_splitter.length());

		if (left_edge < 0) {
			// no more splitters, we're done
			ret.push_back(substr(0, remaining_len));
			break;
		}

		int substr_start = left_edge + p_splitter.length();
		if (p_allow_empty || substr_start < remaining_len) {
			ret.push_back(substr(substr_start, remaining_len - substr_start));
		}

		remaining_len = left_edge;
	}

	ret.invert();
	return ret;
}

Vector<String> String::split_spaces() const {
	Vector<String> ret;
	int from = 0;
	int i = 0;
	int len = length();
	if (len == 0) {
		return ret;
	}

	bool inside = false;

	while (true) {
		bool empty = operator[](i) < 33;

		if (i == 0) {
			inside = !empty;
		}

		if (!empty && !inside) {
			inside = true;
			from = i;
		}

		if (empty && inside) {
			ret.push_back(substr(from, i - from));
			inside = false;
		}

		if (i == len) {
			break;
		}
		i++;
	}

	return ret;
}

Vector<float> String::split_floats(const String &p_splitter, bool p_allow_empty) const {
	Vector<float> ret;
	int from = 0;
	int len = length();

	while (true) {
		int end = find(p_splitter, from);
		if (end < 0) {
			end = len;
		}
		if (p_allow_empty || (end > from)) {
			ret.push_back(String::to_double(&get_data()[from]));
		}

		if (end == len) {
			break;
		}

		from = end + p_splitter.length();
	}

	return ret;
}

Vector<float> String::split_floats_mk(const Vector<String> &p_splitters, bool p_allow_empty) const {
	Vector<float> ret;
	int from = 0;
	int len = length();

	while (true) {
		int idx;
		int end = findmk(p_splitters, from, &idx);
		int spl_len = 1;
		if (end < 0) {
			end = len;
		} else {
			spl_len = p_splitters[idx].length();
		}

		if (p_allow_empty || (end > from)) {
			ret.push_back(String::to_double(&get_data()[from]));
		}

		if (end == len) {
			break;
		}

		from = end + spl_len;
	}

	return ret;
}

Vector<int> String::split_ints(const String &p_splitter, bool p_allow_empty) const {
	Vector<int> ret;
	int from = 0;
	int len = length();

	while (true) {
		int end = find(p_splitter, from);
		if (end < 0) {
			end = len;
		}
		if (p_allow_empty || (end > from)) {
			ret.push_back(String::to_int(&get_data()[from], end - from));
		}

		if (end == len) {
			break;
		}

		from = end + p_splitter.length();
	}

	return ret;
}

Vector<int> String::split_ints_mk(const Vector<String> &p_splitters, bool p_allow_empty) const {
	Vector<int> ret;
	int from = 0;
	int len = length();

	while (true) {
		int idx;
		int end = findmk(p_splitters, from, &idx);
		int spl_len = 1;
		if (end < 0) {
			end = len;
		} else {
			spl_len = p_splitters[idx].length();
		}

		if (p_allow_empty || (end > from)) {
			ret.push_back(String::to_int(&get_data()[from], end - from));
		}

		if (end == len) {
			break;
		}

		from = end + spl_len;
	}

	return ret;
}

String String::join(const Vector<String> &parts) const {
	String ret;
	for (int i = 0; i < parts.size(); ++i) {
		if (i > 0) {
			ret += *this;
		}
		ret += parts[i];
	}
	return ret;
}

CharType String::char_uppercase(CharType p_char) {
	return _find_upper(p_char);
}

CharType String::char_lowercase(CharType p_char) {
	return _find_lower(p_char);
}

String String::to_lower() const {
	String lower = *this;

	for (int i = 0; i < lower.size(); i++) {
		const CharType s = lower[i];
		const CharType t = _find_lower(s);
		if (s != t) { // avoid copy on write
			lower[i] = t;
		}
	}

	return lower;
}

String String::to_upper() const {
	String upper = *this;

	for (int i = 0; i < upper.size(); i++) {
		const CharType s = upper[i];
		const CharType t = _find_upper(s);
		if (s != t) { // avoid copy on write
			upper[i] = t;
		}
	}

	return upper;
}

int String::_count(const String &p_string, int p_from, int p_to, bool p_case_insensitive) const {
	if (p_string.empty()) {
		return 0;
	}
	int len = length();
	int slen = p_string.length();
	if (len < slen) {
		return 0;
	}
	String str;
	if (p_from >= 0 && p_to >= 0) {
		if (p_to == 0) {
			p_to = len;
		} else if (p_from >= p_to) {
			return 0;
		}
		if (p_from == 0 && p_to == len) {
			str = String();
			str.copy_from_unchecked(&get_data()[0], len);
		} else {
			str = substr(p_from, p_to - p_from);
		}
	} else {
		return 0;
	}
	int c = 0;
	int idx = -1;
	do {
		idx = p_case_insensitive ? str.findn(p_string) : str.find(p_string);
		if (idx != -1) {
			str = str.substr(idx + slen, str.length() - slen);
			++c;
		}
	} while (idx != -1);
	return c;
}

int String::count(const String &p_string, int p_from, int p_to) const {
	return _count(p_string, p_from, p_to, false);
}

int String::countn(const String &p_string, int p_from, int p_to) const {
	return _count(p_string, p_from, p_to, true);
}

String String::left(int p_pos) const {
	if (p_pos <= 0) {
		return "";
	}

	if (p_pos >= length()) {
		return *this;
	}

	return substr(0, p_pos);
}

String String::right(int p_pos) const {
	if (p_pos >= length()) {
		return "";
	}

	if (p_pos <= 0) {
		return *this;
	}

	return substr(p_pos, (length() - p_pos));
}

String String::indent(const String &p_prefix) const {
	String new_string;
	int line_start = 0;

	for (int i = 0; i < length(); i++) {
		const CharType c = operator[](i);
		if (c == '\n') {
			if (i == line_start) {
				new_string += c; // Leave empty lines empty.
			} else {
				new_string += p_prefix + substr(line_start, i - line_start + 1);
			}
			line_start = i + 1;
		}
	}
	if (line_start != length()) {
		new_string += p_prefix + substr(line_start);
	}
	return new_string;
}

String String::dedent() const {
	String new_string;
	String indent;
	bool has_indent = false;
	bool has_text = false;
	int line_start = 0;
	int indent_stop = -1;

	for (int i = 0; i < length(); i++) {
		CharType c = operator[](i);
		if (c == '\n') {
			if (has_text) {
				new_string += substr(indent_stop, i - indent_stop);
			}
			new_string += "\n";
			has_text = false;
			line_start = i + 1;
			indent_stop = -1;
		} else if (!has_text) {
			if (c > 32) {
				has_text = true;
				if (!has_indent) {
					has_indent = true;
					indent = substr(line_start, i - line_start);
					indent_stop = i;
				}
			}
			if (has_indent && indent_stop < 0) {
				int j = i - line_start;
				if (j >= indent.length() || c != indent[j]) {
					indent_stop = i;
				}
			}
		}
	}

	if (has_text) {
		new_string += substr(indent_stop, length() - indent_stop);
	}

	return new_string;
}

String String::strip_edges(bool left, bool right) const {
	int len = length();
	int beg = 0, end = len;

	if (left) {
		for (int i = 0; i < len; i++) {
			if (operator[](i) <= 32) {
				beg++;
			} else {
				break;
			}
		}
	}

	if (right) {
		for (int i = (int)(len - 1); i >= 0; i--) {
			if (operator[](i) <= 32) {
				end--;
			} else {
				break;
			}
		}
	}

	if (beg == 0 && end == len) {
		return *this;
	}

	return substr(beg, end - beg);
}

String String::strip_escapes() const {
	String new_string;
	for (int i = 0; i < length(); i++) {
		// Escape characters on first page of the ASCII table, before 32 (Space).
		if (operator[](i) < 32) {
			continue;
		}
		new_string += operator[](i);
	}

	return new_string;
}

String String::lstrip(const String &p_chars) const {
	int len = length();
	int beg;

	for (beg = 0; beg < len; beg++) {
		if (p_chars.find_char(get(beg)) == -1) {
			break;
		}
	}

	if (beg == 0) {
		return *this;
	}

	return substr(beg, len - beg);
}

String String::rstrip(const String &p_chars) const {
	int len = length();
	int end;

	for (end = len - 1; end >= 0; end--) {
		if (p_chars.find_char(get(end)) == -1) {
			break;
		}
	}

	if (end == len - 1) {
		return *this;
	}

	return substr(0, end + 1);
}

String String::get_extension() const {
	int pos = rfind(".");
	if (pos < 0 || pos < MAX(rfind("/"), rfind("\\"))) {
		return "";
	}

	return substr(pos + 1, length());
}

String String::get_basename() const {
	int pos = rfind(".");
	if (pos < 0 || pos < MAX(rfind("/"), rfind("\\"))) {
		return *this;
	}

	return substr(0, pos);
}

String String::plus_file(const String &p_file) const {
	if (empty()) {
		return p_file;
	}
	if (operator[](length() - 1) == '/' || (p_file.size() > 0 && p_file.operator[](0) == '/')) {
		return *this + p_file;
	}
	return *this + "/" + p_file;
}

CharType String::unicode_at(int p_idx) const {
	ERR_FAIL_INDEX_V(p_idx, length(), 0);
	return operator[](p_idx);
}

CharType String::ord_at(int p_idx) const {
	ERR_FAIL_INDEX_V(p_idx, length(), 0);
	return operator[](p_idx);
}

void String::erase(int p_pos, int p_chars) {
	*this = left(p_pos) + substr(p_pos + p_chars, length() - ((p_pos + p_chars)));
}
CharString String::ascii(bool p_allow_extended) const {
	if (!length()) {
		return CharString();
	}

	CharString cs;
	cs.resize(size());

	for (int i = 0; i < size(); i++) {
		CharType c = operator[](i);
		if ((c <= 0x7f) || (c <= 0xff && p_allow_extended)) {
			cs[i] = c;
		} else {
			//print_unicode_error(vformat("Invalid unicode codepoint (%x), cannot represent as ASCII/Latin-1", (uint32_t)c));
			cs[i] = 0x20;
		}
	}

	return cs;
}

String String::utf8(const char *p_utf8, int p_len) {
	String ret;
	ret.parse_utf8(p_utf8, p_len);

	return ret;
}

Error String::parse_utf8(const char *p_utf8, int p_len, bool p_skip_cr) {
	if (!p_utf8) {
		return ERR_INVALID_DATA;
	}

	String aux;

	int cstr_size = 0;
	int str_size = 0;

	/* HANDLE BOM (Byte Order Mark) */
	if (p_len < 0 || p_len >= 3) {
		bool has_bom = uint8_t(p_utf8[0]) == 0xef && uint8_t(p_utf8[1]) == 0xbb && uint8_t(p_utf8[2]) == 0xbf;
		if (has_bom) {
			//8-bit encoding, byte order has no meaning in UTF-8, just skip it
			if (p_len >= 0) {
				p_len -= 3;
			}
			p_utf8 += 3;
		}
	}

	bool decode_error = false;
	bool decode_failed = false;
	{
		const char *ptrtmp = p_utf8;
		const char *ptrtmp_limit = &p_utf8[p_len];
		int skip = 0;
		uint8_t c_start = 0;
		while (ptrtmp != ptrtmp_limit && *ptrtmp) {
			uint8_t c = *ptrtmp >= 0 ? *ptrtmp : uint8_t(256 + *ptrtmp);

			if (skip == 0) {
				if (p_skip_cr && c == '\r') {
					ptrtmp++;
					continue;
				}
				/* Determine the number of characters in sequence */
				if ((c & 0x80) == 0) {
					skip = 0;
				} else if ((c & 0xe0) == 0xc0) {
					skip = 1;
				} else if ((c & 0xf0) == 0xe0) {
					skip = 2;
				} else if ((c & 0xf8) == 0xf0) {
					skip = 3;
				} else if ((c & 0xfc) == 0xf8) {
					skip = 4;
				} else if ((c & 0xfe) == 0xfc) {
					skip = 5;
				} else {
					skip = 0;
					//print_unicode_error(vformat("Invalid UTF-8 leading byte (%x)", c), true);
					decode_failed = true;
				}
				c_start = c;

				if (skip == 1 && (c & 0x1e) == 0) {
					//print_unicode_error(vformat("Overlong encoding (%x ...)", c));
					decode_error = true;
				}
				str_size++;
			} else {
				if ((c_start == 0xe0 && skip == 2 && c < 0xa0) || (c_start == 0xf0 && skip == 3 && c < 0x90) || (c_start == 0xf8 && skip == 4 && c < 0x88) || (c_start == 0xfc && skip == 5 && c < 0x84)) {
					//print_unicode_error(vformat("Overlong encoding (%x %x ...)", c_start, c));
					decode_error = true;
				}
				if (c < 0x80 || c > 0xbf) {
					//print_unicode_error(vformat("Invalid UTF-8 continuation byte (%x ... %x ...)", c_start, c), true);
					decode_failed = true;
					skip = 0;
				} else {
					--skip;
				}
			}

			cstr_size++;
			ptrtmp++;
		}

		if (skip) {
			//rrprint_unicode_error(vformat("Missing %d UTF-8 continuation byte(s)", skip), true);
			decode_failed = true;
		}
	}

	if (str_size == 0) {
		clear();
		return OK; // empty string
	}

	resize(str_size + 1);
	CharType *dst = ptrw();
	dst[str_size] = 0;

	int skip = 0;
	uint32_t unichar = 0;
	while (cstr_size) {
		uint8_t c = *p_utf8 >= 0 ? *p_utf8 : uint8_t(256 + *p_utf8);

		if (skip == 0) {
			if (p_skip_cr && c == '\r') {
				p_utf8++;
				continue;
			}
			/* Determine the number of characters in sequence */
			if ((c & 0x80) == 0) {
				*(dst++) = c;
				unichar = 0;
				skip = 0;
			} else if ((c & 0xe0) == 0xc0) {
				unichar = (0xff >> 3) & c;
				skip = 1;
			} else if ((c & 0xf0) == 0xe0) {
				unichar = (0xff >> 4) & c;
				skip = 2;
			} else if ((c & 0xf8) == 0xf0) {
				unichar = (0xff >> 5) & c;
				skip = 3;
			} else if ((c & 0xfc) == 0xf8) {
				unichar = (0xff >> 6) & c;
				skip = 4;
			} else if ((c & 0xfe) == 0xfc) {
				unichar = (0xff >> 7) & c;
				skip = 5;
			} else {
				*(dst++) = 0x20;
				unichar = 0;
				skip = 0;
			}
		} else {
			if (c < 0x80 || c > 0xbf) {
				*(dst++) = 0x20;
				skip = 0;
			} else {
				unichar = (unichar << 6) | (c & 0x3f);
				--skip;
				if (skip == 0) {
					if (unichar == 0) {
						//print_unicode_error("NUL character", true);
						decode_failed = true;
						unichar = 0x20;
					}
					if ((unichar & 0xfffff800) == 0xd800) {
						//print_unicode_error(vformat("Unpaired surrogate (%x)", unichar));
						decode_error = true;
					}
					if (unichar > 0x10ffff) {
						//print_unicode_error(vformat("Invalid unicode codepoint (%x)", unichar));
						decode_error = true;
					}
					*(dst++) = unichar;
				}
			}
		}

		cstr_size--;
		p_utf8++;
	}
	if (skip) {
		*(dst++) = 0x20;
	}

	if (decode_failed) {
		return ERR_INVALID_DATA;
	} else if (decode_error) {
		return ERR_PARSE_ERROR;
	} else {
		return OK;
	}
}

CharString String::utf8() const {
	int l = length();
	if (!l) {
		return CharString();
	}

	const CharType *d = &operator[](0);
	int fl = 0;
	for (int i = 0; i < l; i++) {
		uint32_t c = d[i];
		if (c <= 0x7f) { // 7 bits.
			fl += 1;
		} else if (c <= 0x7ff) { // 11 bits
			fl += 2;
		} else if (c <= 0xffff) { // 16 bits
			fl += 3;
		} else if (c <= 0x001fffff) { // 21 bits
			fl += 4;
		} else if (c <= 0x03ffffff) { // 26 bits
			fl += 5;
			//print_unicode_error(vformat("Invalid unicode codepoint (%x)", c));
		} else if (c <= 0x7fffffff) { // 31 bits
			fl += 6;
			//print_unicode_error(vformat("Invalid unicode codepoint (%x)", c));
		} else {
			fl += 1;
			//print_unicode_error(vformat("Invalid unicode codepoint (%x), cannot represent as UTF-8", c), true);
		}
	}

	CharString utf8s;
	if (fl == 0) {
		return utf8s;
	}

	utf8s.resize(fl + 1);
	uint8_t *cdst = (uint8_t *)utf8s.get_data();

#define APPEND_CHAR(m_c) *(cdst++) = m_c

	for (int i = 0; i < l; i++) {
		uint32_t c = d[i];

		if (c <= 0x7f) { // 7 bits.
			APPEND_CHAR(c);
		} else if (c <= 0x7ff) { // 11 bits
			APPEND_CHAR(uint32_t(0xc0 | ((c >> 6) & 0x1f))); // Top 5 bits.
			APPEND_CHAR(uint32_t(0x80 | (c & 0x3f))); // Bottom 6 bits.
		} else if (c <= 0xffff) { // 16 bits
			APPEND_CHAR(uint32_t(0xe0 | ((c >> 12) & 0x0f))); // Top 4 bits.
			APPEND_CHAR(uint32_t(0x80 | ((c >> 6) & 0x3f))); // Middle 6 bits.
			APPEND_CHAR(uint32_t(0x80 | (c & 0x3f))); // Bottom 6 bits.
		} else if (c <= 0x001fffff) { // 21 bits
			APPEND_CHAR(uint32_t(0xf0 | ((c >> 18) & 0x07))); // Top 3 bits.
			APPEND_CHAR(uint32_t(0x80 | ((c >> 12) & 0x3f))); // Upper middle 6 bits.
			APPEND_CHAR(uint32_t(0x80 | ((c >> 6) & 0x3f))); // Lower middle 6 bits.
			APPEND_CHAR(uint32_t(0x80 | (c & 0x3f))); // Bottom 6 bits.
		} else if (c <= 0x03ffffff) { // 26 bits
			APPEND_CHAR(uint32_t(0xf8 | ((c >> 24) & 0x03))); // Top 2 bits.
			APPEND_CHAR(uint32_t(0x80 | ((c >> 18) & 0x3f))); // Upper middle 6 bits.
			APPEND_CHAR(uint32_t(0x80 | ((c >> 12) & 0x3f))); // middle 6 bits.
			APPEND_CHAR(uint32_t(0x80 | ((c >> 6) & 0x3f))); // Lower middle 6 bits.
			APPEND_CHAR(uint32_t(0x80 | (c & 0x3f))); // Bottom 6 bits.
		} else if (c <= 0x7fffffff) { // 31 bits
			APPEND_CHAR(uint32_t(0xfc | ((c >> 30) & 0x01))); // Top 1 bit.
			APPEND_CHAR(uint32_t(0x80 | ((c >> 24) & 0x3f))); // Upper upper middle 6 bits.
			APPEND_CHAR(uint32_t(0x80 | ((c >> 18) & 0x3f))); // Lower upper middle 6 bits.
			APPEND_CHAR(uint32_t(0x80 | ((c >> 12) & 0x3f))); // Upper lower middle 6 bits.
			APPEND_CHAR(uint32_t(0x80 | ((c >> 6) & 0x3f))); // Lower lower middle 6 bits.
			APPEND_CHAR(uint32_t(0x80 | (c & 0x3f))); // Bottom 6 bits.
		} else {
			APPEND_CHAR(0x20);
		}
	}
#undef APPEND_CHAR
	*cdst = 0; //trailing zero

	return utf8s;
}

int String::utf8_byte_length() const {
	int l = length();
	if (!l) {
		return 0;
	}

	const CharType *d = &operator[](0);
	int fl = 0;
	for (int i = 0; i < l; i++) {
		uint32_t c = d[i];
		if (c <= 0x7f) { // 7 bits.
			fl += 1;
		} else if (c <= 0x7ff) { // 11 bits
			fl += 2;
		} else if (c <= 0xffff) { // 16 bits
			fl += 3;
		} else if (c <= 0x001fffff) { // 21 bits
			fl += 4;
		} else if (c <= 0x03ffffff) { // 26 bits
			fl += 5;
			//print_unicode_error(vformat("Invalid unicode codepoint (%x)", c));
		} else if (c <= 0x7fffffff) { // 31 bits
			fl += 6;
			//print_unicode_error(vformat("Invalid unicode codepoint (%x)", c));
		} else {
			fl += 1;
			//print_unicode_error(vformat("Invalid unicode codepoint (%x), cannot represent as UTF-8", c), true);
		}
	}

	return fl;
}

String String::utf16(const char16_t *p_utf16, int p_len) {
	String ret;
	ret.parse_utf16(p_utf16, p_len);

	return ret;
}

Error String::parse_utf16(const char16_t *p_utf16, int p_len) {
	if (!p_utf16) {
		return ERR_INVALID_DATA;
	}

	String aux;

	int cstr_size = 0;
	int str_size = 0;

	/* HANDLE BOM (Byte Order Mark) */
	bool byteswap = false; // assume correct endianness if no BOM found
	if (p_len < 0 || p_len >= 1) {
		bool has_bom = false;
		if (uint16_t(p_utf16[0]) == 0xfeff) { // correct BOM, read as is
			has_bom = true;
			byteswap = false;
		} else if (uint16_t(p_utf16[0]) == 0xfffe) { // backwards BOM, swap bytes
			has_bom = true;
			byteswap = true;
		}
		if (has_bom) {
			if (p_len >= 0) {
				p_len -= 1;
			}
			p_utf16 += 1;
		}
	}

	bool decode_error = false;
	{
		const char16_t *ptrtmp = p_utf16;
		const char16_t *ptrtmp_limit = &p_utf16[p_len];
		//uint32_t c_prev = 0;
		bool skip = false;
		while (ptrtmp != ptrtmp_limit && *ptrtmp) {
			uint32_t c = (byteswap) ? BSWAP16(*ptrtmp) : *ptrtmp;

			if ((c & 0xfffffc00) == 0xd800) { // lead surrogate
				if (skip) {
					//print_unicode_error(vformat("Unpaired lead surrogate (%x [trail?] %x)", c_prev, c));
					decode_error = true;
				}
				skip = true;
			} else if ((c & 0xfffffc00) == 0xdc00) { // trail surrogate
				if (skip) {
					str_size--;
				} else {
					//print_unicode_error(vformat("Unpaired trail surrogate (%x [lead?] %x)", c_prev, c));
					decode_error = true;
				}
				skip = false;
			} else {
				skip = false;
			}

			//c_prev = c;
			str_size++;
			cstr_size++;
			ptrtmp++;
		}

		if (skip) {
			//print_unicode_error(vformat("Unpaired lead surrogate (%x [eol])", c_prev));
			decode_error = true;
		}
	}

	if (str_size == 0) {
		clear();
		return OK; // empty string
	}

	resize(str_size + 1);
	CharType *dst = ptrw();
	dst[str_size] = 0;

	bool skip = false;
	uint32_t c_prev = 0;
	while (cstr_size) {
		uint32_t c = (byteswap) ? BSWAP16(*p_utf16) : *p_utf16;

		if ((c & 0xfffffc00) == 0xd800) { // lead surrogate
			if (skip) {
				*(dst++) = c_prev; // unpaired, store as is
			}
			skip = true;
		} else if ((c & 0xfffffc00) == 0xdc00) { // trail surrogate
			if (skip) {
				*(dst++) = (c_prev << 10UL) + c - ((0xd800 << 10UL) + 0xdc00 - 0x10000); // decode pair
			} else {
				*(dst++) = c; // unpaired, store as is
			}
			skip = false;
		} else {
			*(dst++) = c;
			skip = false;
		}

		cstr_size--;
		p_utf16++;
		c_prev = c;
	}

	if (skip) {
		*(dst++) = c_prev;
	}

	if (decode_error) {
		return ERR_PARSE_ERROR;
	} else {
		return OK;
	}
}

Char16String String::utf16() const {
	int l = length();
	if (!l) {
		return Char16String();
	}

	const CharType *d = &operator[](0);
	int fl = 0;
	for (int i = 0; i < l; i++) {
		uint32_t c = d[i];
		if (c <= 0xffff) { // 16 bits.
			fl += 1;
			if ((c & 0xfffff800) == 0xd800) {
				//print_unicode_error(vformat("Unpaired surrogate (%x)", c));
			}
		} else if (c <= 0x10ffff) { // 32 bits.
			fl += 2;
		} else {
			//print_unicode_error(vformat("Invalid unicode codepoint (%x), cannot represent as UTF-16", c), true);
			fl += 1;
		}
	}

	Char16String utf16s;
	if (fl == 0) {
		return utf16s;
	}

	utf16s.resize(fl + 1);
	uint16_t *cdst = (uint16_t *)utf16s.get_data();

#define APPEND_CHAR(m_c) *(cdst++) = m_c

	for (int i = 0; i < l; i++) {
		uint32_t c = d[i];

		if (c <= 0xffff) { // 16 bits.
			APPEND_CHAR(c);
		} else if (c <= 0x10ffff) { // 32 bits.
			APPEND_CHAR(uint32_t((c >> 10) + 0xd7c0)); // lead surrogate.
			APPEND_CHAR(uint32_t((c & 0x3ff) | 0xdc00)); // trail surrogate.
		} else {
			APPEND_CHAR(0x20);
		}
	}
#undef APPEND_CHAR
	*cdst = 0; //trailing zero

	return utf16s;
}

int String::utf16_byte_length() const {
	int l = length();
	if (!l) {
		return 0;
	}

	const CharType *d = &operator[](0);
	int fl = 0;
	for (int i = 0; i < l; i++) {
		uint32_t c = d[i];
		if (c <= 0xffff) { // 16 bits.
			fl += 1;
			if ((c & 0xfffff800) == 0xd800) {
				//print_unicode_error(vformat("Unpaired surrogate (%x)", c));
			}
		} else if (c <= 0x10ffff) { // 32 bits.
			fl += 2;
		} else {
			//print_unicode_error(vformat("Invalid unicode codepoint (%x), cannot represent as UTF-16", c), true);
			fl += 1;
		}
	}

	return fl;
}

uint32_t String::hash(const char *p_cstr) {
	uint32_t hashv = 5381;
	uint32_t c;

	while ((c = *p_cstr++)) {
		hashv = ((hashv << 5) + hashv) + c; /* hash * 33 + c */
	}

	return hashv;
}

uint32_t String::hash(const char *p_cstr, int p_len) {
	uint32_t hashv = 5381;
	for (int i = 0; i < p_len; i++) {
		hashv = ((hashv << 5) + hashv) + p_cstr[i]; /* hash * 33 + c */
	}

	return hashv;
}

uint32_t String::hash(const wchar_t *p_cstr) {
	uint32_t hashv = 5381;
	uint32_t c;

	while ((c = *p_cstr++)) {
		hashv = ((hashv << 5) + hashv) + c; /* hash * 33 + c */
	}

	return hashv;
}

uint32_t String::hash(const wchar_t *p_cstr, int p_len) {
	uint32_t hashv = 5381;
	for (int i = 0; i < p_len; i++) {
		hashv = ((hashv << 5) + hashv) + p_cstr[i]; /* hash * 33 + c */
	}

	return hashv;
}

uint32_t String::hash(const CharType *p_cstr) {
	uint32_t hashv = 5381;
	uint32_t c;

	while ((c = *p_cstr++)) {
		hashv = ((hashv << 5) + hashv) + c; /* hash * 33 + c */
	}

	return hashv;
}

uint32_t String::hash(const CharType *p_cstr, int p_len) {
	uint32_t hashv = 5381;
	for (int i = 0; i < p_len; i++) {
		hashv = ((hashv << 5) + hashv) + p_cstr[i]; /* hash * 33 + c */
	}

	return hashv;
}

uint32_t String::hash() const {
	/* simple djb2 hashing */

	const CharType *chr = get_data();
	uint32_t hashv = 5381;
	uint32_t c;

	while ((c = *chr++)) {
		hashv = ((hashv << 5) + hashv) + c; /* hash * 33 + c */
	}

	return hashv;
}

uint64_t String::hash64() const {
	/* simple djb2 hashing */

	const CharType *chr = get_data();
	uint64_t hashv = 5381;
	uint64_t c;

	while ((c = *chr++)) {
		hashv = ((hashv << 5) + hashv) + c; /* hash * 33 + c */
	}

	return hashv;
}

bool String::is_abs_path() const {
	if (length() > 1) {
		return (operator[](0) == '/' || operator[](0) == '\\' || find(":/") != -1 || find(":\\") != -1);
	} else if ((length()) == 1) {
		return (operator[](0) == '/' || operator[](0) == '\\');
	} else {
		return false;
	}
}

bool String::is_rel_path() const {
	return !is_abs_path();
}

bool String::is_resource_file() const {
	return begins_with("res://") && find("::") == -1;
}

String String::path_to(const String &p_path) const {
	String src = this->replace("\\", "/");
	String dst = p_path.replace("\\", "/");
	if (!src.ends_with("/")) {
		src += "/";
	}
	if (!dst.ends_with("/")) {
		dst += "/";
	}

	String base;

	if (src.begins_with("res://") && dst.begins_with("res://")) {
		base = "res:/";
		src = src.replace("res://", "/");
		dst = dst.replace("res://", "/");

	} else if (src.begins_with("user://") && dst.begins_with("user://")) {
		base = "user:/";
		src = src.replace("user://", "/");
		dst = dst.replace("user://", "/");

	} else if (src.begins_with("/") && dst.begins_with("/")) {
		//nothing
	} else {
		//dos style
		String src_begin = src.get_slicec('/', 0);
		String dst_begin = dst.get_slicec('/', 0);

		if (src_begin != dst_begin) {
			return p_path; //impossible to do this
		}

		base = src_begin;
		src = src.substr(src_begin.length(), src.length());
		dst = dst.substr(dst_begin.length(), dst.length());
	}

	//remove leading and trailing slash and split
	Vector<String> src_dirs = src.substr(1, src.length() - 2).split("/");
	Vector<String> dst_dirs = dst.substr(1, dst.length() - 2).split("/");

	//find common parent
	int common_parent = 0;

	while (true) {
		if (src_dirs.size() == common_parent) {
			break;
		}
		if (dst_dirs.size() == common_parent) {
			break;
		}
		if (src_dirs[common_parent] != dst_dirs[common_parent]) {
			break;
		}
		common_parent++;
	}

	common_parent--;

	String dir;

	for (int i = src_dirs.size() - 1; i > common_parent; i--) {
		dir += "../";
	}

	for (int i = common_parent + 1; i < dst_dirs.size(); i++) {
		dir += dst_dirs[i] + "/";
	}

	if (dir.length() == 0) {
		dir = "./";
	}
	return dir;
}

String String::path_to_file(const String &p_path) const {
	// Don't get base dir for src, this is expected to be a dir already.
	String src = this->replace("\\", "/");
	String dst = p_path.replace("\\", "/").get_base_dir();
	String rel = src.path_to(dst);
	if (rel == dst) { // failed
		return p_path;
	} else {
		return rel + p_path.get_file();
	}
}

String String::get_base_dir() const {
	int end = 0;

	// url scheme style base
	int basepos = find("://");
	if (basepos != -1) {
		end = basepos + 3;
	}

	// windows top level directory base
	if (end == 0) {
		basepos = find(":/");
		if (basepos == -1) {
			basepos = find(":\\");
		}
		if (basepos != -1) {
			end = basepos + 2;
		}
	}

	// Windows UNC network share path.
	if (end == 0) {
		if (is_network_share_path()) {
			basepos = find("/", 2);
			if (basepos == -1) {
				basepos = find("\\", 2);
			}
			int servpos = find("/", basepos + 1);
			if (servpos == -1) {
				servpos = find("\\", basepos + 1);
			}
			if (servpos != -1) {
				end = servpos + 1;
			}
		}
	}

	// unix root directory base
	if (end == 0) {
		if (begins_with("/")) {
			end = 1;
		}
	}

	String rs;
	String base;
	if (end != 0) {
		rs = substr(end, length());
		base = substr(0, end);
	} else {
		rs = *this;
	}

	int sep = MAX(rs.rfind("/"), rs.rfind("\\"));
	if (sep == -1) {
		return base;
	}

	return base + rs.substr(0, sep);
}

String String::get_file() const {
	int sep = MAX(rfind("/"), rfind("\\"));
	if (sep == -1) {
		return *this;
	}

	return substr(sep + 1, length());
}

String String::humanize_size(uint64_t p_size) {
	uint64_t _div = 1;
	Vector<String> prefixes;
	prefixes.push_back(RTR("B"));
	prefixes.push_back(RTR("KiB"));
	prefixes.push_back(RTR("MiB"));
	prefixes.push_back(RTR("GiB"));
	prefixes.push_back(RTR("TiB"));
	prefixes.push_back(RTR("PiB"));
	prefixes.push_back(RTR("EiB"));

	int prefix_idx = 0;

	while (prefix_idx < prefixes.size() - 1 && p_size > (_div * 1024)) {
		_div *= 1024;
		prefix_idx++;
	}

	const int digits = prefix_idx > 0 ? _humanize_digits(p_size / _div) : 0;
	const double divisor = prefix_idx > 0 ? _div : 1;

	return String::num(p_size / divisor).pad_decimals(digits) + " " + prefixes[prefix_idx];
}

String String::simplify_path() const {
	String s = *this;
	String drive;
	if (s.begins_with("local://")) {
		drive = "local://";
		s = s.substr(8, s.length());
	} else if (s.begins_with("res://")) {
		drive = "res://";
		s = s.substr(6, s.length());
	} else if (s.begins_with("user://")) {
		drive = "user://";
		s = s.substr(7, s.length());
	} else if (is_network_share_path()) {
		drive = s.substr(0, 2);
		s = s.substr(2, s.length() - 2);
	} else if (s.begins_with("/") || s.begins_with("\\")) {
		drive = s.substr(0, 1);
		s = s.substr(1, s.length() - 1);
	} else {
		int p = s.find(":/");
		if (p == -1) {
			p = s.find(":\\");
		}
		if (p != -1 && p < s.find("/")) {
			drive = s.substr(0, p + 2);
			s = s.substr(p + 2, s.length());
		}
	}

	s = s.replace("\\", "/");
	while (true) { // in case of using 2 or more slash
		String compare = s.replace("//", "/");
		if (s == compare) {
			break;
		} else {
			s = compare;
		}
	}
	Vector<String> dirs = s.split("/", false);

	for (int i = 0; i < dirs.size(); i++) {
		String d = dirs[i];
		if (d == ".") {
			dirs.remove(i);
			i--;
		} else if (d == "..") {
			if (i == 0) {
				dirs.remove(i);
				i--;
			} else {
				dirs.remove(i);
				dirs.remove(i - 1);
				i -= 2;
			}
		}
	}

	s = "";

	for (int i = 0; i < dirs.size(); i++) {
		if (i > 0) {
			s += "/";
		}
		s += dirs[i];
	}

	return drive + s;
}

bool String::is_network_share_path() const {
	return begins_with("//") || begins_with("\\\\");
}

String String::append_path(const char *path) const {
	if (path[0] == '\0') {
		return *this;
	}

	String ret = *this;
	int size = length();

	if (size == 0) {
		ret += path;
		return ret;
	}

	int sindex = 0;
	char ch = path[sindex];
	while (ch == '/' || ch == '\\') {
		if (ch == '\0') {
			return ret;
		}

		ch = path[++sindex];
	}

	// /////folder
	//      ^ (sindex)

	if (ret.ends_with("/") || ret.ends_with("\\")) {
		ret += &path[sindex];
	} else {
		if (sindex > 0) {
			ret += '/';
			ret += &path[sindex - 1];
		} else {
			ret += '/';
			ret += &path[sindex];
		}
	}

	return ret;
}

String String::append_path(const String &path) const {
	if (path.length() == 0) {
		return *this;
	}

	int size = length();

	if (size == 0) {
		return path;
	}

	int sindex = 0;
	int ts = path.size() - 1;
	char ch = path[sindex];
	while (ch == '/' || ch == '\\') {
		if (sindex == ts) {
			return *this;
		}

		ch = path[++sindex];
	}

	String ret = *this;

	// /////folder
	//      ^ (sindex)

	if (ret.ends_with("/") || ret.ends_with("\\")) {
		ret += &path[sindex];
	} else {
		if (sindex > 0) {
			ret += '/';
			ret += &path[sindex - 1];
		} else {
			ret += '/';
			ret += &path[sindex];
		}
	}

	return ret;
}

String String::path_clean_end_slash() const {
	// _size > 1, so if root is given ("/"), it will not be removed

	String ret = *this;

	int strip_to = ret.length() - 1;

	CharType c = ret[strip_to];

	while (strip_to > 1 && (c == '/' || c == '\\')) {
		--strip_to;
		c = ret[strip_to];
	}

	if (ret.length() != strip_to + 1) {
		ret.set_length(strip_to + 1);
	}

	return ret;
}
String String::path_ensure_end_slash() const {
	// Don't add if empty string, as it would make it root on linux, which can easily become a serious bug

	String ret = *this;

	if (ret.length() == 0) {
		return ret;
	}

	if (!(ret.ends_with("/") || ret.ends_with("\\"))) {
		ret += "/";
	}

	return ret;
}

String String::path_get_prev_dir() const {
	int size = length();

	if (size == 0) {
		return "/";
	}

	int seind = size - 1;
	while (seind > 0 && (operator[](seind) == '/' || operator[](seind) == '\\')) {
		--seind;
	}

	if (seind == 0) {
		// /////////
		// or
		// a///////
		// no prev dir

		return "/";
	}

	// fol/fol2/fol3//
	//             ^  (seind)

	while (seind > 0 && (operator[](seind) != '/' && operator[](seind) != '\\')) {
		--seind;
	}

	// fol/fol2/fol3//
	//         ^  (seind)

	//--seind;

	if (seind <= 0) {
		return "/";
	}

	return substr_index(0, seind);
}

String String::xml_escape(bool p_escape_quotes) const {
	String str = *this;
	str = str.replace("&", "&amp;");
	str = str.replace("<", "&lt;");
	str = str.replace(">", "&gt;");
	if (p_escape_quotes) {
		str = str.replace("'", "&apos;");
		str = str.replace("\"", "&quot;");
	}
	/*
	for (int i=1;i<32;i++) {

		char chr[2]={i,0};
		str=str.replace(chr,"&#"+String::num(i)+";");
	}*/
	return str;
}

static _FORCE_INLINE_ int _xml_unescape(const CharType *p_src, int p_src_len, CharType *p_dst) {
	int len = 0;
	while (p_src_len) {
		if (*p_src == '&') {
			int eat = 0;

			if (p_src_len >= 4 && p_src[1] == '#') {
				CharType c = 0;
				bool overflow = false;
				if (p_src[2] == 'x') {
					// Hex entity &#x<num>;
					for (int i = 3; i < p_src_len; i++) {
						eat = i + 1;
						CharType ct = p_src[i];
						if (ct == ';') {
							break;
						} else if (ct >= '0' && ct <= '9') {
							ct = ct - '0';
						} else if (ct >= 'a' && ct <= 'f') {
							ct = (ct - 'a') + 10;
						} else if (ct >= 'A' && ct <= 'F') {
							ct = (ct - 'A') + 10;
						} else {
							break;
						}
						if (c > (WCHAR_MAX >> 4)) {
							overflow = true;
							break;
						}
						c <<= 4;
						c |= ct;
					}
				} else {
					// Decimal entity &#<num>;
					for (int i = 2; i < p_src_len; i++) {
						eat = i + 1;
						CharType ct = p_src[i];
						if (ct == ';' || ct < '0' || ct > '9') {
							break;
						}
					}
					if (p_src[eat - 1] == ';') {
						int64_t val = String::to_int(p_src + 2, eat - 3);
						if (val > 0 && val <= WCHAR_MAX) {
							c = (CharType)val;
						} else {
							overflow = true;
						}
					}
				}

				// Value must be non-zero, in the range of CharType,
				// actually end with ';'. If invalid, leave the entity as-is
				if (c == '\0' || overflow || p_src[eat - 1] != ';') {
					eat = 1;
					c = *p_src;
				}
				if (p_dst) {
					*p_dst = c;
				}
			} else if (p_src_len >= 4 && p_src[1] == 'g' && p_src[2] == 't' && p_src[3] == ';') {
				if (p_dst) {
					*p_dst = '>';
				}
				eat = 4;
			} else if (p_src_len >= 4 && p_src[1] == 'l' && p_src[2] == 't' && p_src[3] == ';') {
				if (p_dst) {
					*p_dst = '<';
				}
				eat = 4;
			} else if (p_src_len >= 5 && p_src[1] == 'a' && p_src[2] == 'm' && p_src[3] == 'p' && p_src[4] == ';') {
				if (p_dst) {
					*p_dst = '&';
				}
				eat = 5;
			} else if (p_src_len >= 6 && p_src[1] == 'q' && p_src[2] == 'u' && p_src[3] == 'o' && p_src[4] == 't' && p_src[5] == ';') {
				if (p_dst) {
					*p_dst = '"';
				}
				eat = 6;
			} else if (p_src_len >= 6 && p_src[1] == 'a' && p_src[2] == 'p' && p_src[3] == 'o' && p_src[4] == 's' && p_src[5] == ';') {
				if (p_dst) {
					*p_dst = '\'';
				}
				eat = 6;
			} else {
				if (p_dst) {
					*p_dst = *p_src;
				}
				eat = 1;
			}

			if (p_dst) {
				p_dst++;
			}

			len++;
			p_src += eat;
			p_src_len -= eat;
		} else {
			if (p_dst) {
				*p_dst = *p_src;
				p_dst++;
			}
			len++;
			p_src++;
			p_src_len--;
		}
	}

	return len;
}

String String::xml_unescape() const {
	String str;
	int l = length();
	int len = _xml_unescape(get_data(), l, nullptr);
	if (len == 0) {
		return String();
	}
	str.resize(len + 1);
	_xml_unescape(get_data(), l, str.ptrw());
	str[len] = 0;
	return str;
}

String String::http_escape() const {
	const CharString temp = utf8();
	String res;
	for (int i = 0; i < temp.length(); ++i) {
		uint8_t ord = temp[i];
		if (ord == '.' || ord == '-' || ord == '_' || ord == '~' ||
				(ord >= 'a' && ord <= 'z') ||
				(ord >= 'A' && ord <= 'Z') ||
				(ord >= '0' && ord <= '9')) {
			res += ord;
		} else {
			char p[4] = { '%', 0, 0, 0 };
			static const char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

			p[1] = hex[ord >> 4];
			p[2] = hex[ord & 0xF];
			res += p;
		}
	}
	return res;
}

String String::http_unescape() const {
	String res;
	for (int i = 0; i < length(); ++i) {
		if (ord_at(i) == '%' && i + 2 < length()) {
			CharType ord1 = ord_at(i + 1);
			if ((ord1 >= '0' && ord1 <= '9') || (ord1 >= 'A' && ord1 <= 'Z')) {
				CharType ord2 = ord_at(i + 2);
				if ((ord2 >= '0' && ord2 <= '9') || (ord2 >= 'A' && ord2 <= 'Z')) {
					char bytes[3] = { (char)ord1, (char)ord2, 0 };
					res += (char)strtol(bytes, nullptr, 16);
					i += 2;
				}
			} else {
				res += ord_at(i);
			}
		} else {
			res += ord_at(i);
		}
	}
	return String::utf8(res.ascii());
}

String String::uri_encode() const {
	const CharString temp = utf8();
	String res;
	for (int i = 0; i < temp.length(); ++i) {
		uint8_t ord = temp[i];
		if (ord == '.' || ord == '-' || ord == '~' || is_ascii_identifier_char(ord)) {
			res += ord;
		} else {
			char p[4] = { '%', 0, 0, 0 };
			static const char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
			p[1] = hex[ord >> 4];
			p[2] = hex[ord & 0xF];
			res += p;
		}
	}
	return res;
}

String String::uri_decode() const {
	CharString src = utf8();
	CharString res;
	for (int i = 0; i < src.length(); ++i) {
		if (src[i] == '%' && i + 2 < src.length()) {
			char ord1 = src[i + 1];
			if (is_digit(ord1) || is_ascii_upper_case(ord1)) {
				char ord2 = src[i + 2];
				if (is_digit(ord2) || is_ascii_upper_case(ord2)) {
					char bytes[3] = { (char)ord1, (char)ord2, 0 };
					res += (char)strtol(bytes, nullptr, 16);
					i += 2;
				}
			} else {
				res += src[i];
			}
		} else if (src[i] == '+') {
			res += ' ';
		} else {
			res += src[i];
		}
	}
	return String::utf8(res);
}

String String::c_escape() const {
	String escaped = *this;
	escaped = escaped.replace("\\", "\\\\");
	escaped = escaped.replace("\a", "\\a");
	escaped = escaped.replace("\b", "\\b");
	escaped = escaped.replace("\f", "\\f");
	escaped = escaped.replace("\n", "\\n");
	escaped = escaped.replace("\r", "\\r");
	escaped = escaped.replace("\t", "\\t");
	escaped = escaped.replace("\v", "\\v");
	escaped = escaped.replace("\'", "\\'");
	escaped = escaped.replace("\?", "\\?");
	escaped = escaped.replace("\"", "\\\"");

	return escaped;
}

String String::c_escape_multiline() const {
	String escaped = *this;
	escaped = escaped.replace("\\", "\\\\");
	escaped = escaped.replace("\"", "\\\"");

	return escaped;
}

String String::c_unescape() const {
	String escaped = *this;
	escaped = escaped.replace("\\a", "\a");
	escaped = escaped.replace("\\b", "\b");
	escaped = escaped.replace("\\f", "\f");
	escaped = escaped.replace("\\n", "\n");
	escaped = escaped.replace("\\r", "\r");
	escaped = escaped.replace("\\t", "\t");
	escaped = escaped.replace("\\v", "\v");
	escaped = escaped.replace("\\'", "\'");
	escaped = escaped.replace("\\\"", "\"");
	escaped = escaped.replace("\\?", "\?");
	escaped = escaped.replace("\\\\", "\\");

	return escaped;
}

String String::json_escape() const {
	String escaped = *this;
	escaped = escaped.replace("\\", "\\\\");
	escaped = escaped.replace("\b", "\\b");
	escaped = escaped.replace("\f", "\\f");
	escaped = escaped.replace("\n", "\\n");
	escaped = escaped.replace("\r", "\\r");
	escaped = escaped.replace("\t", "\\t");
	escaped = escaped.replace("\v", "\\v");
	escaped = escaped.replace("\"", "\\\"");

	return escaped;
}

String String::word_wrap(int p_chars_per_line) const {
	String ret;

	int line_start = 0;
	int line_end = 0; // End of last word on current line.
	int word_start = 0; // -1 if no word encountered. Leading spaces are part of a word.
	int word_length = 0;

	for (int i = 0; i < length(); i++) {
		const CharType c = operator[](i);

		switch (c) {
			case '\n': {
				// Force newline.
				ret += substr(line_start, i - line_start + 1);
				line_start = i + 1;
				line_end = line_start;
				word_start = line_start;
				word_length = 0;
			} break;

			case ' ':
			case '\t': {
				// A whitespace ends current word.
				if (word_length > 0) {
					line_end = i - 1;
					word_start = -1;
					word_length = 0;
				}
			} break;

			default: {
				if (word_start == -1) {
					word_start = i;
				}
				word_length += 1;

				if (word_length > p_chars_per_line) {
					// Word too long: wrap before current character.
					ret += substr(line_start, i - line_start) + "\n";
					line_start = i;
					line_end = i;
					word_start = i;
					word_length = 1;
				} else if (i - line_start + 1 > p_chars_per_line) {
					// Line too long: wrap after the last word.
					ret += substr(line_start, line_end - line_start + 1) + "\n";
					line_start = word_start;
					line_end = line_start;
				}
			} break;
		}
	}

	const int remaining = length() - line_start;
	if (remaining) {
		ret += substr(line_start, remaining);
	}

	return ret;
}

Error String::parse_url(String &r_scheme, String &r_host, int &r_port, String &r_path) const {
	// Splits the URL into scheme, host, port, path. Strip credentials when present.
	String base = *this;
	r_scheme = "";
	r_host = "";
	r_port = 0;
	r_path = "";
	int pos = base.find("://");
	// Scheme
	if (pos != -1) {
		r_scheme = base.substr(0, pos + 3).to_lower();
		base = base.substr(pos + 3, base.length() - pos - 3);
	}
	pos = base.find("/");
	// Path
	if (pos != -1) {
		r_path = base.substr(pos, base.length() - pos);
		base = base.substr(0, pos);
	}
	// Host
	pos = base.find("@");
	if (pos != -1) {
		// Strip credentials
		base = base.substr(pos + 1, base.length() - pos - 1);
	}
	if (base.begins_with("[")) {
		// Literal IPv6
		pos = base.rfind("]");
		if (pos == -1) {
			return ERR_INVALID_PARAMETER;
		}
		r_host = base.substr(1, pos - 1);
		base = base.substr(pos + 1, base.length() - pos - 1);
	} else {
		// Anything else
		if (base.get_slice_count(":") > 2) {
			return ERR_INVALID_PARAMETER;
		}
		pos = base.rfind(":");
		if (pos == -1) {
			r_host = base;
			base = "";
		} else {
			r_host = base.substr(0, pos);
			base = base.substr(pos, base.length() - pos);
		}
	}
	if (r_host.empty()) {
		return ERR_INVALID_PARAMETER;
	}
	r_host = r_host.to_lower();
	// Port
	if (base.begins_with(":")) {
		base = base.substr(1, base.length() - 1);
		if (!base.is_valid_integer()) {
			return ERR_INVALID_PARAMETER;
		}
		r_port = base.to_int();
		if (r_port < 1 || r_port > 65535) {
			return ERR_INVALID_PARAMETER;
		}
	}
	return OK;
}

String String::percent_encode() const {
	CharString cs = utf8();
	String encoded;
	for (int i = 0; i < cs.length(); i++) {
		uint8_t c = cs[i];
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '~' || c == '.') {
			char p[2] = { (char)c, 0 };
			encoded += p;
		} else {
			char p[4] = { '%', 0, 0, 0 };
			static const char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

			p[1] = hex[c >> 4];
			p[2] = hex[c & 0xF];
			encoded += p;
		}
	}

	return encoded;
}
String String::percent_decode() const {
	CharString pe;

	CharString cs = utf8();
	for (int i = 0; i < cs.length(); i++) {
		uint8_t c = cs[i];
		if (c == '%' && i < length() - 2) {
			uint8_t a = LOWERCASE(cs[i + 1]);
			uint8_t b = LOWERCASE(cs[i + 2]);

			if (a >= '0' && a <= '9') {
				c = (a - '0') << 4;
			} else if (a >= 'a' && a <= 'f') {
				c = (a - 'a' + 10) << 4;
			} else {
				continue;
			}

			uint8_t d = 0;

			if (b >= '0' && b <= '9') {
				d = (b - '0');
			} else if (b >= 'a' && b <= 'f') {
				d = (b - 'a' + 10);
			} else {
				continue;
			}
			c += d;
			i += 2;
		}
		pe += c;
	}

	return String::utf8(pe.ptr());
}

String String::property_name_encode() const {
	// Escape and quote strings with extended ASCII or further Unicode characters
	// as well as '"', '=' or ' ' (32)
	const CharType *cstr = get_data();
	for (int i = 0; cstr[i]; i++) {
		if (cstr[i] == '=' || cstr[i] == '"' || cstr[i] == ';' || cstr[i] == '[' || cstr[i] == ']' || cstr[i] < 33 || cstr[i] > 126) {
			return "\"" + c_escape_multiline() + "\"";
		}
	}
	// Keep as is
	return *this;
}

// Changes made to the set of invalid characters must also be reflected in the String documentation.

static const char32_t invalid_node_name_characters[] = { '.', ':', '@', '/', '\"', '%', 0 };

String String::get_invalid_node_name_characters() {
	// Do not use this function for critical validation.
	String r;
	const char32_t *c = invalid_node_name_characters;
	while (*c) {
		if (c != invalid_node_name_characters) {
			r += " ";
		}
		r += String::chr(*c);
		c++;
	}
	return r;
}

String String::validate_node_name() const {
	// This is a critical validation in node addition, so it must be optimized.
	const char32_t *cn = ptr();
	if (cn == nullptr) {
		return String();
	}

	bool valid = true;
	uint32_t idx = 0;
	while (cn[idx]) {
		const char32_t *c = invalid_node_name_characters;
		while (*c) {
			if (cn[idx] == *c) {
				valid = false;
				break;
			}
			c++;
		}
		if (!valid) {
			break;
		}
		idx++;
	}

	if (valid) {
		return *this;
	}

	String validated = *this;
	char32_t *nn = validated.ptrw();
	while (nn[idx]) {
		const char32_t *c = invalid_node_name_characters;
		while (*c) {
			if (nn[idx] == *c) {
				nn[idx] = '_';
				break;
			}
			c++;
		}
		idx++;
	}

	return validated;
}

static _FORCE_INLINE_ bool _is_valid_identifier_bit(int p_index, char32_t p_char) {
	if (p_index == 0 && is_digit(p_char)) {
		return false; // No start with number plz.
	}
	return is_ascii_identifier_char(p_char);
}

String String::validate_identifier() const {
	if (empty()) {
		return "_"; // Empty string is not a valid identifier;
	}

	String result = *this;
	int len = result.length();
	char32_t *buffer = result.ptrw();

	for (int i = 0; i < len; i++) {
		if (!_is_valid_identifier_bit(i, buffer[i])) {
			buffer[i] = '_';
		}
	}

	return result;
}

bool String::is_valid_identifier() const {
	int len = length();

	if (len == 0) {
		return false;
	}

	const CharType *str = &operator[](0);

	for (int i = 0; i < len; i++) {
		if (i == 0) {
			if (str[0] >= '0' && str[0] <= '9') {
				return false; // no start with number plz
			}
		}

		bool valid_char = (str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_';

		if (!valid_char) {
			return false;
		}
	}

	return true;
}

bool String::is_valid_integer() const {
	int len = length();

	if (len == 0) {
		return false;
	}

	int from = 0;
	if (len != 1 && (operator[](0) == '+' || operator[](0) == '-')) {
		from++;
	}

	for (int i = from; i < len; i++) {
		if (operator[](i) < '0' || operator[](i) > '9') {
			return false; // no start with number plz
		}
	}

	return true;
}

bool String::is_valid_hex_number(bool p_with_prefix) const {
	int len = length();

	if (len == 0) {
		return false;
	}

	int from = 0;
	if (len != 1 && (operator[](0) == '+' || operator[](0) == '-')) {
		from++;
	}

	if (p_with_prefix) {
		if (len < 3) {
			return false;
		}
		if (operator[](from) != '0' || operator[](from + 1) != 'x') {
			return false;
		}
		from += 2;
	}

	for (int i = from; i < len; i++) {
		CharType c = operator[](i);
		if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
			continue;
		}
		return false;
	}

	return true;
};

bool String::is_valid_float() const {
	int len = length();

	if (len == 0) {
		return false;
	}

	int from = 0;
	if (operator[](0) == '+' || operator[](0) == '-') {
		from++;
	}

	bool exponent_found = false;
	bool period_found = false;
	bool sign_found = false;
	bool exponent_values_found = false;
	bool numbers_found = false;

	for (int i = from; i < len; i++) {
		if (operator[](i) >= '0' && operator[](i) <= '9') {
			if (exponent_found) {
				exponent_values_found = true;
			} else {
				numbers_found = true;
			}
		} else if (numbers_found && !exponent_found && operator[](i) == 'e') {
			exponent_found = true;
		} else if (!period_found && !exponent_found && operator[](i) == '.') {
			period_found = true;
		} else if ((operator[](i) == '-' || operator[](i) == '+') && exponent_found && !exponent_values_found && !sign_found) {
			sign_found = true;
		} else {
			return false; // no start with number plz
		}
	}

	return numbers_found;
}

bool String::is_valid_bool() const {
	int size = length();

	if (size == 1) {
		CharType c = ptr()[0];

		if (c == '0') {
			return true;
		} else if (c == '1') {
			return true;
		}

		return false;
	} else if (size == 4) {
		String l = to_lower();
		const CharType *p = l.ptr();

		if (p[0] == 't' && p[1] == 'r' && p[2] == 'u' && p[3] == 'e') {
			return true;
		} else {
			return false;
		}
	} else if (size == 5) {
		String l = to_lower();
		const CharType *p = l.ptr();

		if (p[0] == 'f' && p[1] == 'a' && p[2] == 'l' && p[3] == 's' && p[3] == 'e') {
			return true;
		} else {
			return false;
		}
	}

	return false;
}

bool String::is_valid_unsigned_integer() const {
	int len = length();

	if (len == 0) {
		return false;
	}

	int from = 0;
	if (len != 1 && (operator[](0) == '+')) {
		from++;
	}

	for (int i = from; i < len; i++) {
		if (operator[](i) < '0' || operator[](i) > '9') {
			return false; // no start with number plz
		}
	}

	return true;
}

bool String::is_valid_filename() const {
	String stripped = strip_edges();
	if (*this != stripped) {
		return false;
	}

	if (stripped == String()) {
		return false;
	}

	return !(find(":") != -1 || find("/") != -1 || find("\\") != -1 || find("?") != -1 || find("*") != -1 || find("\"") != -1 || find("|") != -1 || find("%") != -1 || find("<") != -1 || find(">") != -1);
}

bool String::is_valid_ip_address() const {
	if (find(":") >= 0) {
		Vector<String> ip = split(":");
		for (int i = 0; i < ip.size(); i++) {
			String n = ip[i];
			if (n.empty()) {
				continue;
			}
			if (n.is_valid_hex_number(false)) {
				int nint = n.hex_to_int(false);
				if (nint < 0 || nint > 0xffff) {
					return false;
				}
				continue;
			};
			if (!n.is_valid_ip_address()) {
				return false;
			}
		};

	} else {
		Vector<String> ip = split(".");
		if (ip.size() != 4) {
			return false;
		}
		for (int i = 0; i < ip.size(); i++) {
			String n = ip[i];
			if (!n.is_valid_integer()) {
				return false;
			}
			int val = n.to_int();
			if (val < 0 || val > 255) {
				return false;
			}
		}
	};

	return true;
}

Vector<uint8_t> String::to_ascii_buffer() const {
	const String *s = this;
	if (s->empty()) {
		return Vector<uint8_t>();
	}
	CharString charstr = s->ascii();

	Vector<uint8_t> retval;
	size_t len = charstr.length();
	retval.resize(len);
	uint8_t *w = retval.ptrw();
	memcpy(w, charstr.ptr(), len);

	return retval;
}

Vector<uint8_t> String::to_utf8_buffer() const {
	const String *s = this;
	if (s->empty()) {
		return Vector<uint8_t>();
	}
	CharString charstr = s->utf8();

	Vector<uint8_t> retval;
	size_t len = charstr.length();
	retval.resize(len);
	uint8_t *w = retval.ptrw();
	memcpy(w, charstr.ptr(), len);

	return retval;
}

Vector<uint8_t> String::to_utf16_buffer() const {
	const String *s = this;
	if (s->empty()) {
		return Vector<uint8_t>();
	}
	Char16String charstr = s->utf16();

	Vector<uint8_t> retval;
	size_t len = charstr.length() * sizeof(char16_t);
	retval.resize(len);
	uint8_t *w = retval.ptrw();
	memcpy(w, (const void *)charstr.ptr(), len);

	return retval;
}

Vector<uint8_t> String::to_utf32_buffer() const {
	const String *s = this;
	if (s->empty()) {
		return Vector<uint8_t>();
	}

	Vector<uint8_t> retval;
	size_t len = s->length() * sizeof(CharType);
	retval.resize(len);
	uint8_t *w = retval.ptrw();
	memcpy(w, (const void *)s->ptr(), len);

	return retval;
}

String::String(const char *p_str) {
	copy_from(p_str);
}

String::String(const wchar_t *p_str) {
	copy_from(p_str);
}

String::String(const CharType *p_str) {
	copy_from(p_str);
}

String::String(const char *p_str, int p_clip_to_len) {
	copy_from(p_str, p_clip_to_len);
}

String::String(const wchar_t *p_str, int p_clip_to_len) {
	copy_from(p_str, p_clip_to_len);
}

String::String(const CharType *p_str, int p_clip_to_len) {
	copy_from(p_str, p_clip_to_len);
}

String::String(const StrRange &p_range) {
	if (!p_range.c_str) {
		return;
	}
	copy_from(p_range.c_str, p_range.len);
}

// Other conversions

int String::hex_to_int(bool p_with_prefix) const {
	int len = length();
	ERR_FAIL_COND_V_MSG(p_with_prefix ? len < 3 : len == 0, 0, String("Invalid hexadecimal notation length in string ") + (p_with_prefix ? "with" : "without") + " prefix \"" + *this + "\".");

	const CharType *s = ptr();

	int sign = s[0] == '-' ? -1 : 1;

	if (sign < 0) {
		s++;
	}

	if (p_with_prefix) {
		ERR_FAIL_COND_V_MSG(s[0] != '0' || LOWERCASE(s[1]) != 'x', 0, "Invalid hexadecimal notation prefix in string \"" + *this + "\".");
		s += 2;
	}

	int hex = 0;

	while (*s) {
		CharType c = LOWERCASE(*s);
		int n;
		if (c >= '0' && c <= '9') {
			n = c - '0';
		} else if (c >= 'a' && c <= 'f') {
			n = (c - 'a') + 10;
		} else {
			ERR_FAIL_V_MSG(0, "Invalid hexadecimal notation character \"" + chr(*s) + "\" in string \"" + *this + "\".");
		}
		// Check for overflow/underflow, with special case to ensure INT32_MIN does not result in error
		bool overflow = ((hex > INT32_MAX / 16) && (sign == 1 || (sign == -1 && hex != (INT32_MAX >> 4) + 1))) || (sign == -1 && hex == (INT32_MAX >> 4) + 1 && c > '0');
		ERR_FAIL_COND_V_MSG(overflow, sign == 1 ? INT32_MAX : INT32_MIN, "Cannot represent " + *this + " as a 32-bit signed integer, since the value is " + (sign == 1 ? "too large." : "too small."));
		hex *= 16;
		hex += n;
		s++;
	}

	return hex * sign;
}

int64_t String::hex_to_int64(bool p_with_prefix) const {
	int len = length();
	ERR_FAIL_COND_V_MSG(p_with_prefix ? len < 3 : len == 0, 0, String("Invalid hexadecimal notation length in string ") + (p_with_prefix ? "with" : "without") + " prefix \"" + *this + "\".");

	const CharType *s = ptr();

	int64_t sign = s[0] == '-' ? -1 : 1;

	if (sign < 0) {
		s++;
	}

	if (p_with_prefix) {
		ERR_FAIL_COND_V_MSG(s[0] != '0' || LOWERCASE(s[1]) != 'x', 0, "Invalid hexadecimal notation prefix in string \"" + *this + "\".");
		s += 2;
	}

	int64_t hex = 0;

	while (*s) {
		CharType c = LOWERCASE(*s);
		int64_t n;
		if (c >= '0' && c <= '9') {
			n = c - '0';
		} else if (c >= 'a' && c <= 'f') {
			n = (c - 'a') + 10;
		} else {
			ERR_FAIL_V_MSG(0, "Invalid hexadecimal notation character \"" + chr(*s) + "\" in string \"" + *this + "\".");
		}
		bool overflow = ((hex > INT64_MAX / 16) && (sign == 1 || (sign == -1 && hex != (INT64_MAX >> 4) + 1))) || (sign == -1 && hex == (INT64_MAX >> 4) + 1 && c > '0');
		ERR_FAIL_COND_V_MSG(overflow, sign == 1 ? INT64_MAX : INT64_MIN, "Cannot represent " + *this + " as a 64-bit signed integer, since the value is " + (sign == 1 ? "too large." : "too small."));
		hex *= 16;
		hex += n;
		s++;
	}

	return hex * sign;
}

int64_t String::bin_to_int64(bool p_with_prefix) const {
	int len = length();
	ERR_FAIL_COND_V_MSG(p_with_prefix ? len < 3 : len == 0, 0, String("Invalid binary notation length in string ") + (p_with_prefix ? "with" : "without") + " prefix \"" + *this + "\".");

	const CharType *s = ptr();

	int64_t sign = s[0] == '-' ? -1 : 1;

	if (sign < 0) {
		s++;
	}

	if (p_with_prefix) {
		ERR_FAIL_COND_V_MSG(s[0] != '0' || LOWERCASE(s[1]) != 'b', 0, "Invalid binary notation prefix in string \"" + *this + "\".");
		s += 2;
	}

	int64_t binary = 0;

	while (*s) {
		CharType c = LOWERCASE(*s);
		int64_t n;
		if (c == '0' || c == '1') {
			n = c - '0';
		} else {
			ERR_FAIL_V_MSG(0, "Invalid binary notation character \"" + chr(*s) + "\" in string \"" + *this + "\".");
		}
		// Check for overflow/underflow, with special case to ensure INT64_MIN does not result in error
		bool overflow = ((binary > INT64_MAX / 2) && (sign == 1 || (sign == -1 && binary != (INT64_MAX >> 1) + 1))) || (sign == -1 && binary == (INT64_MAX >> 1) + 1 && c > '0');
		ERR_FAIL_COND_V_MSG(overflow, sign == 1 ? INT64_MAX : INT64_MIN, "Cannot represent " + *this + " as a 64-bit signed integer, since the value is " + (sign == 1 ? "too large." : "too small."));
		binary *= 2;
		binary += n;
		s++;
	}

	return binary * sign;
}

template <class C>
static double built_in_strtod(
		/* A decimal ASCII floating-point number,
		 * optionally preceded by white space. Must
		 * have form "-I.FE-X", where I is the integer
		 * part of the mantissa, F is the fractional
		 * part of the mantissa, and X is the
		 * exponent. Either of the signs may be "+",
		 * "-", or omitted. Either I or F may be
		 * omitted, or both. The decimal point isn't
		 * necessary unless F is present. The "E" may
		 * actually be an "e". E and X may both be
		 * omitted (but not just one). */
		const C *string,
		/* If non-nullptr, store terminating Cacter's
		 * address here. */
		C **endPtr = nullptr) {
	/* Largest possible base 10 exponent. Any
	 * exponent larger than this will already
	 * produce underflow or overflow, so there's
	 * no need to worry about additional digits. */
	static const int maxExponent = 511;
	/* Table giving binary powers of 10. Entry
	 * is 10^2^i. Used to convert decimal
	 * exponents into floating-point numbers. */
	static const double powersOf10[] = {
		10.,
		100.,
		1.0e4,
		1.0e8,
		1.0e16,
		1.0e32,
		1.0e64,
		1.0e128,
		1.0e256
	};

	bool sign, expSign = false;
	double fraction, dblExp;
	const double *d;
	const C *p;
	int c;
	/* Exponent read from "EX" field. */
	int exp = 0;
	/* Exponent that derives from the fractional
	 * part. Under normal circumstances, it is
	 * the negative of the number of digits in F.
	 * However, if I is very long, the last digits
	 * of I get dropped (otherwise a long I with a
	 * large negative exponent could cause an
	 * unnecessary overflow on I alone). In this
	 * case, fracExp is incremented one for each
	 * dropped digit. */
	int fracExp = 0;
	/* Number of digits in mantissa. */
	int mantSize;
	/* Number of mantissa digits BEFORE decimal point. */
	int decPt;
	/* Temporarily holds location of exponent in string. */
	const C *pExp;

	/*
	 * Strip off leading blanks and check for a sign.
	 */

	p = string;
	while (*p == ' ' || *p == '\t' || *p == '\n') {
		p += 1;
	}
	if (*p == '-') {
		sign = true;
		p += 1;
	} else {
		if (*p == '+') {
			p += 1;
		}
		sign = false;
	}

	/*
	 * Count the number of digits in the mantissa (including the decimal
	 * point), and also locate the decimal point.
	 */

	decPt = -1;
	for (mantSize = 0;; mantSize += 1) {
		c = *p;
		if (!IS_DIGIT(c)) {
			if ((c != '.') || (decPt >= 0)) {
				break;
			}
			decPt = mantSize;
		}
		p += 1;
	}

	/*
	 * Now suck up the digits in the mantissa. Use two integers to collect 9
	 * digits each (this is faster than using floating-point). If the mantissa
	 * has more than 18 digits, ignore the extras, since they can't affect the
	 * value anyway.
	 */

	pExp = p;
	p -= mantSize;
	if (decPt < 0) {
		decPt = mantSize;
	} else {
		mantSize -= 1; /* One of the digits was the point. */
	}
	if (mantSize > 18) {
		fracExp = decPt - 18;
		mantSize = 18;
	} else {
		fracExp = decPt - mantSize;
	}
	if (mantSize == 0) {
		fraction = 0.0;
		p = string;
		goto done;
	} else {
		int frac1, frac2;

		frac1 = 0;
		for (; mantSize > 9; mantSize -= 1) {
			c = *p;
			p += 1;
			if (c == '.') {
				c = *p;
				p += 1;
			}
			frac1 = 10 * frac1 + (c - '0');
		}
		frac2 = 0;
		for (; mantSize > 0; mantSize -= 1) {
			c = *p;
			p += 1;
			if (c == '.') {
				c = *p;
				p += 1;
			}
			frac2 = 10 * frac2 + (c - '0');
		}
		fraction = (1.0e9 * frac1) + frac2;
	}

	/*
	 * Skim off the exponent.
	 */

	p = pExp;
	if ((*p == 'E') || (*p == 'e')) {
		p += 1;
		if (*p == '-') {
			expSign = true;
			p += 1;
		} else {
			if (*p == '+') {
				p += 1;
			}
			expSign = false;
		}
		if (!IS_DIGIT(CharType(*p))) {
			p = pExp;
			goto done;
		}
		while (IS_DIGIT(CharType(*p))) {
			exp = exp * 10 + (*p - '0');
			p += 1;
		}
	}
	if (expSign) {
		exp = fracExp - exp;
	} else {
		exp = fracExp + exp;
	}

	/*
	 * Generate a floating-point number that represents the exponent. Do this
	 * by processing the exponent one bit at a time to combine many powers of
	 * 2 of 10. Then combine the exponent with the fraction.
	 */

	if (exp < 0) {
		expSign = true;
		exp = -exp;
	} else {
		expSign = false;
	}

	if (exp > maxExponent) {
		exp = maxExponent;
		//WARN_PRINT("Exponent too high");
	}
	dblExp = 1.0;
	for (d = powersOf10; exp != 0; exp >>= 1, ++d) {
		if (exp & 01) {
			dblExp *= *d;
		}
	}
	if (expSign) {
		fraction /= dblExp;
	} else {
		fraction *= dblExp;
	}

done:
	if (endPtr != nullptr) {
		*endPtr = (C *)p;
	}

	if (sign) {
		return -fraction;
	}
	return fraction;
}

double String::to_double() const {
	if (empty()) {
		return 0;
	}

	return built_in_strtod<CharType>(get_data());
}

float String::to_float() const {
	if (empty()) {
		return 0;
	}

	return built_in_strtod<CharType>(get_data());
}

int String::to_int() const {
	if (length() == 0) {
		return 0;
	}

	int to = (find(".") >= 0) ? find(".") : length();

	int integer = 0;
	int sign = 1;

	for (int i = 0; i < to; i++) {
		CharType c = operator[](i);
		if (c >= '0' && c <= '9') {
			bool overflow = (integer > INT32_MAX / 10) || (integer == INT32_MAX / 10 && ((sign == 1 && c > '7') || (sign == -1 && c > '8')));
			ERR_FAIL_COND_V_MSG(overflow, sign == 1 ? INT32_MAX : INT32_MIN, "Cannot represent " + *this + " as a 32-bit signed integer, since the value is " + (sign == 1 ? "too large." : "too small."));
			integer *= 10;
			integer += c - '0';

		} else if (integer == 0 && c == '-') {
			sign = -sign;
		}
	}

	return integer * sign;
}

bool String::to_bool() const {
	if (length() == 0) {
		return false;
	}

	if (is_numeric()) {
		return to_int() != 0;
	}

	return to_lower() == "true";
}

uint32_t String::to_uint() const {
	if (is_numeric()) {
		return static_cast<uint32_t>(to_int());
	}

	return 0;
}

int64_t String::to_int64() const {
	if (length() == 0) {
		return 0;
	}

	int to = (find(".") >= 0) ? find(".") : length();

	int64_t integer = 0;
	int64_t sign = 1;

	for (int i = 0; i < to; i++) {
		CharType c = operator[](i);
		if (c >= '0' && c <= '9') {
			bool overflow = (integer > INT64_MAX / 10) || (integer == INT64_MAX / 10 && ((sign == 1 && c > '7') || (sign == -1 && c > '8')));
			ERR_FAIL_COND_V_MSG(overflow, sign == 1 ? INT64_MAX : INT64_MIN, "Cannot represent " + *this + " as a 64-bit signed integer, since the value is " + (sign == 1 ? "too large." : "too small."));
			integer *= 10;
			integer += c - '0';

		} else if (integer == 0 && c == '-') {
			sign = -sign;
		}
	}

	return integer * sign;
}

int64_t String::to_int(const char *p_str, int p_len) {
	int to = 0;
	if (p_len >= 0) {
		to = p_len;
	} else {
		while (p_str[to] != 0 && p_str[to] != '.') {
			to++;
		}
	}

	int64_t integer = 0;
	int64_t sign = 1;

	for (int i = 0; i < to; i++) {
		char c = p_str[i];
		if (is_digit(c)) {
			bool overflow = (integer > INT64_MAX / 10) || (integer == INT64_MAX / 10 && ((sign == 1 && c > '7') || (sign == -1 && c > '8')));
			ERR_FAIL_COND_V_MSG(overflow, sign == 1 ? INT64_MAX : INT64_MIN, "Cannot represent " + String(p_str).substr(0, to) + " as a 64-bit signed integer, since the value is " + (sign == 1 ? "too large." : "too small."));
			integer *= 10;
			integer += c - '0';

		} else if (c == '-' && integer == 0) {
			sign = -sign;
		} else if (c != ' ') {
			break;
		}
	}

	return integer * sign;
}

int64_t String::to_int(const wchar_t *p_str, int p_len) {
	int to = 0;
	if (p_len >= 0) {
		to = p_len;
	} else {
		while (p_str[to] != 0 && p_str[to] != '.') {
			to++;
		}
	}

	int64_t integer = 0;
	int64_t sign = 1;

	for (int i = 0; i < to; i++) {
		wchar_t c = p_str[i];
		if (is_digit(c)) {
			bool overflow = (integer > INT64_MAX / 10) || (integer == INT64_MAX / 10 && ((sign == 1 && c > '7') || (sign == -1 && c > '8')));
			ERR_FAIL_COND_V_MSG(overflow, sign == 1 ? INT64_MAX : INT64_MIN, "Cannot represent " + String(p_str).substr(0, to) + " as a 64-bit signed integer, since the value is " + (sign == 1 ? "too large." : "too small."));
			integer *= 10;
			integer += c - '0';

		} else if (c == '-' && integer == 0) {
			sign = -sign;
		} else if (c != ' ') {
			break;
		}
	}

	return integer * sign;
}

int64_t String::to_int(const CharType *p_str, int p_len, bool p_clamp) {
	if (p_len == 0 || !p_str[0]) {
		return 0;
	}
	///@todo make more exact so saving and loading does not lose precision

	int64_t integer = 0;
	int64_t sign = 1;
	int reading = READING_SIGN;

	const CharType *str = p_str;
	const CharType *limit = &p_str[p_len];

	while (*str && reading != READING_DONE && str != limit) {
		CharType c = *(str++);
		switch (reading) {
			case READING_SIGN: {
				if (is_digit(c)) {
					reading = READING_INT;
					// let it fallthrough
				} else if (c == '-') {
					sign = -1;
					reading = READING_INT;
					break;
				} else if (c == '+') {
					sign = 1;
					reading = READING_INT;
					break;
				} else {
					break;
				}
				FALLTHROUGH;
			}
			case READING_INT: {
				if (is_digit(c)) {
					if (integer > INT64_MAX / 10) {
						String number("");
						str = p_str;
						while (*str && str != limit) {
							number += *(str++);
						}
						if (p_clamp) {
							if (sign == 1) {
								return INT64_MAX;
							} else {
								return INT64_MIN;
							}
						} else {
							ERR_FAIL_V_MSG(sign == 1 ? INT64_MAX : INT64_MIN, "Cannot represent " + number + " as a 64-bit signed integer, since the value is " + (sign == 1 ? "too large." : "too small."));
						}
					}
					integer *= 10;
					integer += c - '0';
				} else {
					reading = READING_DONE;
				}

			} break;
		}
	}

	return sign * integer;
}

double String::to_float(const char *p_str) {
	return built_in_strtod<char>(p_str);
}

double String::to_float(const wchar_t *p_str, const wchar_t **r_end) {
	return built_in_strtod<wchar_t>(p_str, (wchar_t **)r_end);
}
double String::to_float(const CharType *p_str, const CharType **r_end) {
	return built_in_strtod<CharType>(p_str, (CharType **)r_end);
}

double String::to_double(const char *p_str) {
	return built_in_strtod<char>(p_str);
}

double String::to_double(const wchar_t *p_str, const wchar_t **r_end) {
	return built_in_strtod<wchar_t>(p_str, (wchar_t **)r_end);
}
double String::to_double(const CharType *p_str, const CharType **r_end) {
	return built_in_strtod<CharType>(p_str, (CharType **)r_end);
}

uint32_t String::num_characters(int64_t p_int) {
	int r = 1;
	if (p_int < 0) {
		r += 1;
		if (p_int == INT64_MIN) {
			p_int = INT64_MAX;
		} else {
			p_int = -p_int;
		}
	}
	while (p_int >= 10) {
		p_int /= 10;
		r++;
	}
	return r;
}

bool String::_base_is_subsequence_of(const String &p_string, bool case_insensitive) const {
	int len = length();
	if (len == 0) {
		// Technically an empty string is subsequence of any string
		return true;
	}

	if (len > p_string.length()) {
		return false;
	}

	const CharType *src = &operator[](0);
	const CharType *tgt = &p_string[0];

	for (; *src && *tgt; tgt++) {
		bool match = false;
		if (case_insensitive) {
			CharType srcc = _find_lower(*src);
			CharType tgtc = _find_lower(*tgt);
			match = srcc == tgtc;
		} else {
			match = *src == *tgt;
		}
		if (match) {
			src++;
			if (!*src) {
				return true;
			}
		}
	}

	return false;
}

bool operator==(const char *p_chr, const String &p_str) {
	return p_str == p_chr;
}

bool operator==(const wchar_t *p_chr, const String &p_str) {
#ifdef WINDOWS_ENABLED
	// wchar_t is 16-bit
	return p_str == String::utf16((const char16_t *)p_chr);
#else
	// wchar_t is 32-bi
	return p_str == String((const CharType *)p_chr);
#endif
}

bool operator!=(const char *p_chr, const String &p_str) {
	return !(p_str == p_chr);
}

bool operator!=(const wchar_t *p_chr, const String &p_str) {
#ifdef WINDOWS_ENABLED
	// wchar_t is 16-bit
	return !(p_str == String::utf16((const char16_t *)p_chr));
#else
	// wchar_t is 32-bi
	return !(p_str == String((const CharType *)p_chr));
#endif
}

String operator+(const char *p_chr, const String &p_str) {
	String tmp = p_chr;
	tmp += p_str;
	return tmp;
}

String operator+(const wchar_t *p_chr, const String &p_str) {
#ifdef WINDOWS_ENABLED
	// wchar_t is 16-bit
	String tmp = String::utf16((const char16_t *)p_chr);
#else
	// wchar_t is 32-bit
	String tmp = (const CharType *)p_chr;
#endif
	tmp += p_str;
	return tmp;
}

String operator+(CharType p_chr, const String &p_str) {
	return (String::chr(p_chr) + p_str);
}

String itos(int64_t p_val) {
	return String::num_int64(p_val);
}

String uitos(uint64_t p_val) {
	return String::num_uint64(p_val);
}

String rtos(double p_val) {
	return String::num(p_val);
}

String rtoss(double p_val) {
	return String::num_scientific(p_val);
}

#ifdef TOOLS_ENABLED
String TTR(const String &p_text, const String &p_context) {
	return p_text;
}

/* DTR is used for the documentation, handling descriptions extracted from the XML.
 * It also replaces `$DOCS_URL` with the actual URL to the documentation's branch,
 * to allow dehardcoding it in the XML and doing proper substitutions everywhere.
 */
String DTR(const String &p_text) {
	// Comes straight from the XML, so remove indentation and any trailing whitespace.
	const String text = p_text.dedent().strip_edges();

	return text.replace("$DOCS_URL", VERSION_DOCS_URL);
}
#endif

String RTR(const String &p_text) {
	return p_text;
}
#line 0

#line 1 "sfwl/core/logger.cpp"



void RLogger::print_trace(const String &str) {
	print_trace(str.utf8().get_data());
}
void RLogger::print_trace(const char *str) {
	printf("T %s\n", str);
}
void RLogger::print_trace(const char *p_function, const char *p_file, int p_line, const char *str) {
	printf("T | %s::%s:%d | %s\n", p_file, p_function, p_line, str);
}
void RLogger::print_trace(const char *p_function, const char *p_file, int p_line, const String &str) {
	printf("T | %s::%s:%d | %s\n", p_file, p_function, p_line, str.utf8().get_data());
}

void RLogger::print_message(const String &str) {
	print_message(str.utf8().get_data());
}
void RLogger::print_message(const char *str) {
	printf("M %s\n", str);
}
void RLogger::print_message(const char *p_function, const char *p_file, int p_line, const char *str) {
	printf("M | %s::%s:%d | %s\n", p_file, p_function, p_line, str);
}
void RLogger::print_message(const char *p_function, const char *p_file, int p_line, const String &str) {
	printf("M | %s::%s:%d | %s\n", p_file, p_function, p_line, str.utf8().get_data());
}

void RLogger::print_warning(const String &str) {
	print_warning(str.utf8().get_data());
}
void RLogger::print_warning(const char *str) {
	printf("W %s\n", str);
}
void RLogger::print_warning(const char *p_function, const char *p_file, int p_line, const char *str) {
	printf("W | %s::%s:%d | %s\n", p_file, p_function, p_line, str);
}
void RLogger::print_warning(const char *p_function, const char *p_file, int p_line, const String &str) {
	printf("W | %s::%s:%d | %s\n", p_file, p_function, p_line, str.utf8().get_data());
}

void RLogger::print_error(const String &str) {
	print_error(str.utf8().get_data());
}
void RLogger::print_error(const char *str) {
	printf("E %s\n", str);
}

void RLogger::print_error(const char *p_function, const char *p_file, int p_line, const char *str) {
	printf("E | %s::%s:%d | %s\n", p_file, p_function, p_line, str);
}
void RLogger::print_error(const char *p_function, const char *p_file, int p_line, const String &str) {
	printf("E | %s::%s:%d | %s\n", p_file, p_function, p_line, str.utf8().get_data());
}
void RLogger::print_msg_error(const char *p_function, const char *p_file, int p_line, const char *p_msg, const char *str) {
	printf("E | %s::%s:%d | :: %s. %s\n", p_file, p_function, p_line, str, p_msg);
}
void RLogger::print_index_error(const char *p_function, const char *p_file, int p_line, const int index, const int size, const char *str) {
	printf("E (INDEX) | %s::%s:%d | :: index: %d/%d. %s\n", p_file, p_function, p_line, index, size, str);
}

void RLogger::log_trace(const String &str) {
	log_trace(str.utf8().get_data());
}
void RLogger::log_trace(const char *str) {
	printf("T %s\n", str);
}
void RLogger::log_trace(const char *p_function, const char *p_file, int p_line, const char *str) {
	printf("T | %s::%s:%d | %s\n", p_file, p_function, p_line, str);
}
void RLogger::log_trace(const char *p_function, const char *p_file, int p_line, const String &str) {
	printf("T | %s::%s:%d | %s\n", p_file, p_function, p_line, str.utf8().get_data());
}

void RLogger::log_message(const String &str) {
	log_message(str.utf8().get_data());
}
void RLogger::log_message(const char *str) {
	printf("M %s\n", str);
}
void RLogger::log_message(const char *p_function, const char *p_file, int p_line, const char *str) {
	printf("M | %s::%s:%d | %s\n", p_file, p_function, p_line, str);
}
void RLogger::log_message(const char *p_function, const char *p_file, int p_line, const String &str) {
	printf("M | %s::%s:%d | %s\n", p_file, p_function, p_line, str.utf8().get_data());
}

void RLogger::log_warning(const String &str) {
	log_warning(str.utf8().get_data());
}
void RLogger::log_warning(const char *str) {
	printf("W %s\n", str);
}
void RLogger::log_warning(const char *p_function, const char *p_file, int p_line, const char *str) {
	printf("W | %s::%s:%d | %s\n", p_file, p_function, p_line, str);
}
void RLogger::log_warning(const char *p_function, const char *p_file, int p_line, const String &str) {
	printf("W | %s::%s:%d | %s\n", p_file, p_function, p_line, str.utf8().get_data());
}

void RLogger::log_error(const String &str) {
	log_error(str.utf8().get_data());
}
void RLogger::log_error(const char *str) {
	printf("E %s\n", str);
}

void RLogger::log_error(const char *p_function, const char *p_file, int p_line, const char *str) {
	printf("E | %s::%s:%d | %s\n", p_file, p_function, p_line, str);
}
void RLogger::log_error(const char *p_function, const char *p_file, int p_line, const String &str) {
	printf("E | %s::%s:%d | %s\n", p_file, p_function, p_line, str.utf8().get_data());
}
void RLogger::log_msg_error(const char *p_function, const char *p_file, int p_line, const char *p_msg, const char *str) {
	printf("E | %s::%s:%d | :: %s. %s\n", p_file, p_function, p_line, str, p_msg);
}
void RLogger::log_index_error(const char *p_function, const char *p_file, int p_line, const int index, const int size, const char *str) {
	printf("E (INDEX) | %s::%s:%d | :: index: %d/%d. %s\n", p_file, p_function, p_line, index, size, str);
}
void RLogger::log_index_error(const char *p_function, const char *p_file, int p_line, const int index, const int size, const String &str) {
	printf("E (INDEX) | %s::%s:%d | :: index: %d/%d. %s\n", p_file, p_function, p_line, index, size, str.utf8().get_data());
}

String *RLogger::get_string_ptr(const int p_default_size) {
	return memnew(String());
}
String *RLogger::get_string_ptr(const char *p_function, const char *p_file, int p_line, const int p_default_size) {
	String *s = memnew(String());

	s->operator+=(p_function);
	s->operator+=("::");
	s->operator+=(p_file);
	s->operator+=(":");
	s->operator+=(String::num(p_line));
	s->operator+=(" | ");

	return s;
}
String *RLogger::get_string_ptr(const char *p_prefix, const char *p_function, const char *p_file, int p_line, const int p_default_size) {
	String *s = memnew(String());

	s->operator+=(p_prefix);
	s->operator+=(" | ");
	s->operator+=(p_function);
	s->operator+=("::");
	s->operator+=(p_file);
	s->operator+=(":");
	s->operator+=(String::num(p_line));
	s->operator+=(" | ");

	return s;
}
void RLogger::return_string_ptr(String *str) {
	delete str;
}

String *RLogger::get_trace_string_ptr(const int p_default_size) {
	String *str = get_string_ptr(p_default_size);
	str->operator+=("T ");
	return str;
}
String *RLogger::get_message_string_ptr(const int p_default_size) {
	String *str = get_string_ptr(p_default_size);
	str->operator+=("M ");
	return str;
}
String *RLogger::get_warning_string_ptr(const int p_default_size) {
	String *str = get_string_ptr(p_default_size);
	str->operator+=("W ");
	return str;
}
String *RLogger::get_error_string_ptr(const int p_default_size) {
	String *str = get_string_ptr(p_default_size);
	str->operator+=("E ");
	return str;
}

String *RLogger::get_trace_string_ptr(const char *p_function, const char *p_file, int p_line, const int p_default_size) {
	return get_string_ptr("T", p_function, p_file, p_line, p_default_size);
}
String *RLogger::get_message_string_ptr(const char *p_function, const char *p_file, int p_line, const int p_default_size) {
	return get_string_ptr("M", p_function, p_file, p_line, p_default_size);
}
String *RLogger::get_warning_string_ptr(const char *p_function, const char *p_file, int p_line, const int p_default_size) {
	return get_string_ptr("W", p_function, p_file, p_line, p_default_size);
}
String *RLogger::get_error_string_ptr(const char *p_function, const char *p_file, int p_line, const int p_default_size) {
	return get_string_ptr("E", p_function, p_file, p_line, p_default_size);
}

void RLogger::log_ptr(String *str) {
	printf("%s\n", str->utf8().get_data());
}

void RLogger::log_ret_ptr(String *str) {
	log_ptr(str);

	return_string_ptr(str);
}
#line 0

#line 1 "sfwl/core/string_name.cpp"
/*************************************************************************/
/*  string_name.cpp                                                      */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



StaticCString StaticCString::create(const char *p_ptr) {
	StaticCString scs;
	scs.ptr = p_ptr;
	return scs;
}

StringName::_Data *StringName::_table[STRING_TABLE_LEN];

StringName _scs_create(const char *p_chr, bool p_static) {
	return (p_chr[0] ? StringName(StaticCString::create(p_chr), p_static) : StringName());
}

bool StringName::configured = false;
Mutex StringName::lock;

#ifdef DEBUG_ENABLED
bool StringName::debug_stringname = false;
#endif

void StringName::setup() {
	ERR_FAIL_COND(configured);
	for (int i = 0; i < STRING_TABLE_LEN; i++) {
		_table[i] = nullptr;
	}
	configured = true;
}

void StringName::cleanup() {
	lock.lock();

#ifdef DEBUG_ENABLED
	if (unlikely(debug_stringname)) {
		Vector<_Data *> data;
		for (int i = 0; i < STRING_TABLE_LEN; i++) {
			_Data *d = _table[i];
			while (d) {
				data.push_back(d);
				d = d->next;
			}
		}

		print_line("\nStringName reference ranking (from most to least referenced):\n");

		data.sort_custom<DebugSortReferences>();
		int unreferenced_stringnames = 0;
		int rarely_referenced_stringnames = 0;
		for (int i = 0; i < data.size(); i++) {
			print_line(itos(i + 1) + ": " + data[i]->get_name() + " - " + itos(data[i]->debug_references));
			if (data[i]->debug_references == 0) {
				unreferenced_stringnames += 1;
			} else if (data[i]->debug_references < 5) {
				rarely_referenced_stringnames += 1;
			}
		}

		print_line(vformat("\nOut of %d StringNames, %d StringNames were never referenced during this run (0 times) (%.2f%%).", data.size(), unreferenced_stringnames, unreferenced_stringnames / float(data.size()) * 100));
		print_line(vformat("Out of %d StringNames, %d StringNames were rarely referenced during this run (1-4 times) (%.2f%%).", data.size(), rarely_referenced_stringnames, rarely_referenced_stringnames / float(data.size()) * 100));
	}
#endif

	//int lost_strings = 0;
	for (int i = 0; i < STRING_TABLE_LEN; i++) {
		while (_table[i]) {
			_Data *d = _table[i];

			/*
			if (d->static_count.get() != d->refcount.get()) {
				lost_strings++;
				if (OS::get_singleton()->is_stdout_verbose()) {
					if (d->cname) {
						print_line("Orphan StringName: " + String(d->cname));
					} else {
						print_line("Orphan StringName: " + String(d->name));
					}
				}
			}
			*/

			_table[i] = _table[i]->next;
			memdelete(d);
		}
	}

	/*
	if (lost_strings) {
		print_verbose("StringName: " + itos(lost_strings) + " unclaimed string names at exit.");
	}
	*/

	configured = false;

	lock.unlock();
}

void StringName::unref() {
	ERR_FAIL_COND(!configured);

	if (_data && _data->refcount.unref()) {
		lock.lock();

		if (_data->static_count.get() > 0) {
			if (_data->cname) {
				ERR_PRINT("BUG: Unreferenced static string to 0: " + String(_data->cname));
			} else {
				ERR_PRINT("BUG: Unreferenced static string to 0: " + String(_data->name));
			}
		}

		if (_data->prev) {
			_data->prev->next = _data->next;
		} else {
			if (_table[_data->idx] != _data) {
				ERR_PRINT("BUG!");
			}

			_table[_data->idx] = _data->next;
		}

		if (_data->next) {
			_data->next->prev = _data->prev;
		}

		memdelete(_data);
		lock.unlock();
	}

	_data = nullptr;
}

bool StringName::operator==(const String &p_name) const {
	if (!_data) {
		return (p_name.length() == 0);
	}

	return (_data->get_name() == p_name);
}

bool StringName::operator==(const char *p_name) const {
	if (!_data) {
		return (p_name[0] == 0);
	}

	return (_data->get_name() == p_name);
}

bool StringName::operator!=(const String &p_name) const {
	return !(operator==(p_name));
}

bool StringName::operator!=(const StringName &p_name) const {
	// the real magic of all this mess happens here.
	// this is why path comparisons are very fast
	return _data != p_name._data;
}

void StringName::operator=(const StringName &p_name) {
	if (this == &p_name) {
		return;
	}

	unref();

	if (p_name._data && p_name._data->refcount.ref()) {
		_data = p_name._data;
	}
}

StringName::StringName(const StringName &p_name) {
	_data = nullptr;

	ERR_FAIL_COND(!configured);

	if (p_name._data && p_name._data->refcount.ref()) {
		_data = p_name._data;
	}
}

StringName::StringName(const char *p_name, bool p_static) {
	_data = nullptr;

	ERR_FAIL_COND(!configured);

	if (!p_name || p_name[0] == 0) {
		return; //empty, ignore
	}

	lock.lock();

	uint32_t hash = String::hash(p_name);

	uint32_t idx = hash & STRING_TABLE_MASK;

	_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}
		_data = _data->next;
	}

	if (_data) {
		if (_data->refcount.ref()) {
			// exists
			if (p_static) {
				_data->static_count.increment();
			}

#ifdef DEBUG_ENABLED
			if (unlikely(debug_stringname)) {
				_data->debug_references++;
			}
#endif

			lock.unlock();
			return;
		}
	}

	_data = memnew(_Data);
	_data->name = p_name;
	_data->refcount.init();
	_data->static_count.set(p_static ? 1 : 0);
	_data->hash = hash;
	_data->idx = idx;
	_data->cname = NULL;
	_data->next = _table[idx];
	_data->prev = NULL;

#ifdef DEBUG_ENABLED
	if (unlikely(debug_stringname)) {
		// Keep in memory, force static.
		_data->refcount.ref();
		_data->static_count.increment();
	}
#endif

	if (_table[idx]) {
		_table[idx]->prev = _data;
	}

	_table[idx] = _data;

	lock.unlock();
}

StringName::StringName(const StaticCString &p_static_string, bool p_static) {
	_data = NULL;

	ERR_FAIL_COND(!configured);

	ERR_FAIL_COND(!p_static_string.ptr || !p_static_string.ptr[0]);

	lock.lock();

	uint32_t hash = String::hash(p_static_string.ptr);

	uint32_t idx = hash & STRING_TABLE_MASK;

	_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_static_string.ptr) {
			break;
		}
		_data = _data->next;
	}

	if (_data) {
		if (_data->refcount.ref()) {
			// exists
			if (p_static) {
				_data->static_count.increment();
			}

#ifdef DEBUG_ENABLED
			if (unlikely(debug_stringname)) {
				_data->debug_references++;
			}
#endif

			lock.unlock();
			return;
		}
	}

	_data = memnew(_Data);

	_data->refcount.init();
	_data->static_count.set(p_static ? 1 : 0);
	_data->hash = hash;
	_data->idx = idx;
	_data->cname = p_static_string.ptr;
	_data->next = _table[idx];
	_data->prev = NULL;

#ifdef DEBUG_ENABLED
	if (unlikely(debug_stringname)) {
		// Keep in memory, force static.
		_data->refcount.ref();
		_data->static_count.increment();
	}
#endif

	if (_table[idx]) {
		_table[idx]->prev = _data;
	}

	_table[idx] = _data;

	lock.unlock();
}

StringName::StringName(const String &p_name, bool p_static) {
	_data = nullptr;

	ERR_FAIL_COND(!configured);

	if (p_name.empty()) {
		return;
	}

	lock.lock();

	uint32_t hash = p_name.hash();

	uint32_t idx = hash & STRING_TABLE_MASK;

	_data = _table[idx];

	while (_data) {
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}

		_data = _data->next;
	}

	if (_data) {
		if (_data->refcount.ref()) {
			// exists
			if (p_static) {
				_data->static_count.increment();
			}

#ifdef DEBUG_ENABLED
			if (unlikely(debug_stringname)) {
				_data->debug_references++;
			}
#endif

			lock.unlock();
			return;
		}
	}

	_data = memnew(_Data);
	_data->name = p_name;
	_data->refcount.init();
	_data->static_count.set(p_static ? 1 : 0);
	_data->hash = hash;
	_data->idx = idx;
	_data->cname = NULL;
	_data->next = _table[idx];
	_data->prev = NULL;

#ifdef DEBUG_ENABLED
	if (unlikely(debug_stringname)) {
		// Keep in memory, force static.
		_data->refcount.ref();
		_data->static_count.increment();
	}
#endif

	if (_table[idx]) {
		_table[idx]->prev = _data;
	}

	_table[idx] = _data;

	lock.unlock();
}

StringName StringName::search(const char *p_name) {
	ERR_FAIL_COND_V(!configured, StringName());

	ERR_FAIL_COND_V(!p_name, StringName());
	if (!p_name[0]) {
		return StringName();
	}

	lock.lock();

	uint32_t hash = String::hash(p_name);

	uint32_t idx = hash & STRING_TABLE_MASK;

	_Data *_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}
		_data = _data->next;
	}

	if (_data && _data->refcount.ref()) {
#ifdef DEBUG_ENABLED
		if (unlikely(debug_stringname)) {
			_data->debug_references++;
		}
#endif

		lock.unlock();

		return StringName(_data);
	}

	lock.unlock();
	return StringName(); //does not exist
}

StringName StringName::search(const CharType *p_name) {
	ERR_FAIL_COND_V(!configured, StringName());

	ERR_FAIL_COND_V(!p_name, StringName());
	if (!p_name[0]) {
		return StringName();
	}

	lock.lock();

	uint32_t hash = String::hash(p_name);

	uint32_t idx = hash & STRING_TABLE_MASK;

	_Data *_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && _data->get_name() == p_name) {
			break;
		}

		_data = _data->next;
	}

	if (_data && _data->refcount.ref()) {
		lock.unlock();
		return StringName(_data);
	}

	lock.unlock();
	return StringName(); //does not exist
}
StringName StringName::search(const String &p_name) {
	ERR_FAIL_COND_V(p_name == "", StringName());

	lock.lock();

	uint32_t hash = p_name.hash();

	uint32_t idx = hash & STRING_TABLE_MASK;

	_Data *_data = _table[idx];

	while (_data) {
		// compare hash first
		if (_data->hash == hash && p_name == _data->get_name()) {
			break;
		}

		_data = _data->next;
	}

	if (_data && _data->refcount.ref()) {
#ifdef DEBUG_ENABLED
		if (unlikely(debug_stringname)) {
			_data->debug_references++;
		}
#endif
		lock.unlock();
		return StringName(_data);
	}

	lock.unlock();
	return StringName(); //does not exist
}

StringName::StringName() {
	_data = nullptr;
}

/*
bool operator==(const String &p_name, const StringName &p_string_name) {
	return p_name == p_string_name.operator String();
}
bool operator!=(const String &p_name, const StringName &p_string_name) {
	return p_name != p_string_name.operator String();
}

bool operator==(const char *p_name, const StringName &p_string_name) {
	return p_name == p_string_name.operator String();
}
bool operator!=(const char *p_name, const StringName &p_string_name) {
	return p_name != p_string_name.operator String();
}
*/
#line 0


#line 1 "sfwl/core/pcg.cpp"
// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)



uint32_t pcg32_random_r(pcg32_random_t* rng)
{
    uint64_t oldstate = rng->state;
    // Advance internal state
    rng->state = oldstate * 6364136223846793005ULL + (rng->inc|1);
    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

// Source from http://www.pcg-random.org/downloads/pcg-c-basic-0.9.zip
void pcg32_srandom_r(pcg32_random_t* rng, uint64_t initstate, uint64_t initseq)
{
    rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    pcg32_random_r(rng);
    rng->state += initstate;
    pcg32_random_r(rng);
}

// Source from https://github.com/imneme/pcg-c-basic/blob/master/pcg_basic.c
// pcg32_boundedrand_r(rng, bound):
//     Generate a uniformly distributed number, r, where 0 <= r < bound
uint32_t pcg32_boundedrand_r(pcg32_random_t *rng, uint32_t bound) {
	// To avoid bias, we need to make the range of the RNG a multiple of
	// bound, which we do by dropping output less than a threshold.
	// A naive scheme to calculate the threshold would be to do
	//
	//     uint32_t threshold = 0x100000000ull % bound;
	//
	// but 64-bit div/mod is slower than 32-bit div/mod (especially on
	// 32-bit platforms).  In essence, we do
	//
	//     uint32_t threshold = (0x100000000ull-bound) % bound;
	//
	// because this version will calculate the same modulus, but the LHS
	// value is less than 2^32.
	uint32_t threshold = -bound % bound;

	// Uniformity guarantees that this loop will terminate.  In practice, it
	// should usually terminate quickly; on average (assuming all bounds are
	// equally likely), 82.25% of the time, we can expect it to require just
	// one iteration.  In the worst case, someone passes a bound of 2^31 + 1
	// (i.e., 2147483649), which invalidates almost 50% of the range.  In
	// practice, bounds are typically small and only a tiny amount of the range
	// is eliminated.
	for (;;) {
		uint32_t r = pcg32_random_r(rng);
		if (r >= threshold)
			return r % bound;
	}
}
#line 0


#line 1 "sfwl/core/file_access.cpp"




String FileAccess::read_file(const String &path) {
	FILE *f = fopen(path.utf8().get_data(), "r");

	ERR_FAIL_COND_V_MSG(!f, String(), "Error opening file! " + path);

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); /* same as rewind(f); */

	CharString cs;
	cs.resize(fsize + 1); // +1 for the null terminator

	fread(cs.ptrw(), 1, fsize, f);
	fclose(f);

	return String::utf8(cs.ptr());
}

Vector<uint8_t> FileAccess::read_file_bin(const String &path) {
	FILE *f = fopen(path.utf8().get_data(), "rb");

	Vector<uint8_t> fd;

	ERR_FAIL_COND_V_MSG(!f, fd, "Error opening file! " + path);

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); /* same as rewind(f); */

	fd.resize(fsize);

	fread(fd.ptrw(), 1, fsize, f);
	fclose(f);

	return fd;
}

Error FileAccess::read_file_into_bin(const String &path, Vector<uint8_t> *data) {
	if (!data) {
		return ERR_PARAMETER_RANGE_ERROR;
	}

	FILE *f = fopen(path.utf8().get_data(), "rb");

	if (!f) {
		return ERR_FILE_CANT_OPEN;
	}

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); /* same as rewind(f); */

	data->resize(fsize);

	fread(data->ptrw(), 1, fsize, f);
	fclose(f);

	return OK;
}

Error FileAccess::write_file(const String &path, const String &str) {
	FILE *f = fopen(path.utf8().get_data(), "w");

	if (!f) {
		return ERR_FILE_CANT_OPEN;
	}

	fwrite(str.utf8().ptr(), sizeof(char), str.size(), f);
	fclose(f);

	return OK;
}

Error FileAccess::write_file_bin(const String &path, const Vector<uint8_t> &data) {
	FILE *f = fopen(path.utf8().get_data(), "wb");

	if (!f) {
		return ERR_FILE_CANT_OPEN;
	}

	fwrite(data.ptr(), sizeof(uint8_t), data.size(), f);
	fclose(f);

	return OK;
}

FileAccess::FileAccess() {
}
FileAccess::~FileAccess() {
}
#line 0

#line 1 "sfwl/core/3rd_tinydir.h"
/*
Copyright (c) 2013-2019, tinydir authors:
- Cong Xu
- Lautis Sun
- Baudouin Feildel
- Andargor <andargor@yahoo.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef TINYDIR_H
#define TINYDIR_H

#ifdef __cplusplus
extern "C" {
#endif

#if ((defined _UNICODE) && !(defined UNICODE))
#define UNICODE
#endif

#if ((defined UNICODE) && !(defined _UNICODE))
#define _UNICODE
#endif

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
# ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
# endif
# include <windows.h>
# include <tchar.h>
# pragma warning(push)
# pragma warning (disable : 4996)
#else
# include <dirent.h>
# include <libgen.h>
# include <sys/stat.h>
# include <stddef.h>
#endif
#ifdef __MINGW32__
# include <tchar.h>
#endif


/* types */

/* Windows UNICODE wide character support */
#if defined _MSC_VER || defined __MINGW32__
# define _tinydir_char_t TCHAR
# define TINYDIR_STRING(s) _TEXT(s)
# define _tinydir_strlen _tcslen
# define _tinydir_strcpy _tcscpy
# define _tinydir_strcat _tcscat
# define _tinydir_strcmp _tcscmp
# define _tinydir_strrchr _tcsrchr
# define _tinydir_strncmp _tcsncmp
#else
# define _tinydir_char_t char
# define TINYDIR_STRING(s) s
# define _tinydir_strlen strlen
# define _tinydir_strcpy strcpy
# define _tinydir_strcat strcat
# define _tinydir_strcmp strcmp
# define _tinydir_strrchr strrchr
# define _tinydir_strncmp strncmp
#endif

#if (defined _MSC_VER || defined __MINGW32__)
# include <windows.h>
# define _TINYDIR_PATH_MAX MAX_PATH
#elif defined  __linux__
# include <limits.h>
# ifdef PATH_MAX
#  define _TINYDIR_PATH_MAX PATH_MAX
# endif
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
# include <sys/param.h>
# if defined(BSD)
#  include <limits.h>
#  ifdef PATH_MAX
#   define _TINYDIR_PATH_MAX PATH_MAX
#  endif
# endif
#endif

#ifndef _TINYDIR_PATH_MAX
#define _TINYDIR_PATH_MAX 4096
#endif

#ifdef _MSC_VER
/* extra chars for the "\\*" mask */
# define _TINYDIR_PATH_EXTRA 2
#else
# define _TINYDIR_PATH_EXTRA 0
#endif

#define _TINYDIR_FILENAME_MAX 256

#if (defined _MSC_VER || defined __MINGW32__)
#define _TINYDIR_DRIVE_MAX 3
#endif

#ifdef _MSC_VER
# define _TINYDIR_FUNC static __inline
#elif !defined __STDC_VERSION__ || __STDC_VERSION__ < 199901L
# define _TINYDIR_FUNC static __inline__
#else
# define _TINYDIR_FUNC static inline
#endif

/* readdir_r usage; define TINYDIR_USE_READDIR_R to use it (if supported) */
#ifdef TINYDIR_USE_READDIR_R

/* readdir_r is a POSIX-only function, and may not be available under various
 * environments/settings, e.g. MinGW. Use readdir fallback */
#if _POSIX_C_SOURCE >= 1 || _XOPEN_SOURCE || _BSD_SOURCE || _SVID_SOURCE ||\
	_POSIX_SOURCE
# define _TINYDIR_HAS_READDIR_R
#endif
#if _POSIX_C_SOURCE >= 200112L
# define _TINYDIR_HAS_FPATHCONF
# include <unistd.h>
#endif
#if _BSD_SOURCE || _SVID_SOURCE || \
	(_POSIX_C_SOURCE >= 200809L || _XOPEN_SOURCE >= 700)
# define _TINYDIR_HAS_DIRFD
# include <sys/types.h>
#endif
#if defined _TINYDIR_HAS_FPATHCONF && defined _TINYDIR_HAS_DIRFD &&\
	defined _PC_NAME_MAX
# define _TINYDIR_USE_FPATHCONF
#endif
#if defined __MINGW32__ || !defined _TINYDIR_HAS_READDIR_R ||\
	!(defined _TINYDIR_USE_FPATHCONF || defined NAME_MAX)
# define _TINYDIR_USE_READDIR
#endif

/* Use readdir by default */
#else
# define _TINYDIR_USE_READDIR
#endif

/* MINGW32 has two versions of dirent, ASCII and UNICODE*/
#ifndef _MSC_VER
#if (defined __MINGW32__) && (defined _UNICODE)
#define _TINYDIR_DIR _WDIR
#define _tinydir_dirent _wdirent
#define _tinydir_opendir _wopendir
#define _tinydir_readdir _wreaddir
#define _tinydir_closedir _wclosedir
#else
#define _TINYDIR_DIR DIR
#define _tinydir_dirent dirent
#define _tinydir_opendir opendir
#define _tinydir_readdir readdir
#define _tinydir_closedir closedir
#endif
#endif

/* Allow user to use a custom allocator by defining _TINYDIR_MALLOC and _TINYDIR_FREE. */
#if    defined(_TINYDIR_MALLOC) &&  defined(_TINYDIR_FREE)
#elif !defined(_TINYDIR_MALLOC) && !defined(_TINYDIR_FREE)
#else
#error "Either define both alloc and free or none of them!"
#endif

#if !defined(_TINYDIR_MALLOC)
	#define _TINYDIR_MALLOC(_size) malloc(_size)
	#define _TINYDIR_FREE(_ptr)    free(_ptr)
#endif /* !defined(_TINYDIR_MALLOC) */

typedef struct tinydir_file
{
	_tinydir_char_t path[_TINYDIR_PATH_MAX];
	_tinydir_char_t name[_TINYDIR_FILENAME_MAX];
	_tinydir_char_t *extension;
	int is_dir;
	int is_reg;

#ifndef _MSC_VER
#ifdef __MINGW32__
	struct _stat _s;
#else
	struct stat _s;
#endif
#endif
} tinydir_file;

typedef struct tinydir_dir
{
	_tinydir_char_t path[_TINYDIR_PATH_MAX];
	int has_next;
	size_t n_files;

	tinydir_file *_files;
#ifdef _MSC_VER
	HANDLE _h;
	WIN32_FIND_DATA _f;
#else
	_TINYDIR_DIR *_d;
	struct _tinydir_dirent *_e;
#ifndef _TINYDIR_USE_READDIR
	struct _tinydir_dirent *_ep;
#endif
#endif
} tinydir_dir;


/* declarations */

_TINYDIR_FUNC
int tinydir_open(tinydir_dir *dir, const _tinydir_char_t *path);
_TINYDIR_FUNC
int tinydir_open_sorted(tinydir_dir *dir, const _tinydir_char_t *path);
_TINYDIR_FUNC
void tinydir_close(tinydir_dir *dir);

_TINYDIR_FUNC
int tinydir_next(tinydir_dir *dir);
_TINYDIR_FUNC
int tinydir_readfile(const tinydir_dir *dir, tinydir_file *file);
_TINYDIR_FUNC
int tinydir_readfile_n(const tinydir_dir *dir, tinydir_file *file, size_t i);
_TINYDIR_FUNC
int tinydir_open_subdir_n(tinydir_dir *dir, size_t i);

_TINYDIR_FUNC
int tinydir_file_open(tinydir_file *file, const _tinydir_char_t *path);
_TINYDIR_FUNC
void _tinydir_get_ext(tinydir_file *file);
_TINYDIR_FUNC
int _tinydir_file_cmp(const void *a, const void *b);
#ifndef _MSC_VER
#ifndef _TINYDIR_USE_READDIR
_TINYDIR_FUNC
size_t _tinydir_dirent_buf_size(_TINYDIR_DIR *dirp);
#endif
#endif


/* definitions*/

_TINYDIR_FUNC
int tinydir_open(tinydir_dir *dir, const _tinydir_char_t *path)
{
#ifndef _MSC_VER
#ifndef _TINYDIR_USE_READDIR
	int error;
	int size;	/* using int size */
#endif
#else
	_tinydir_char_t path_buf[_TINYDIR_PATH_MAX];
#endif
	_tinydir_char_t *pathp;

	if (dir == NULL || path == NULL || _tinydir_strlen(path) == 0)
	{
		errno = EINVAL;
		return -1;
	}
	if (_tinydir_strlen(path) + _TINYDIR_PATH_EXTRA >= _TINYDIR_PATH_MAX)
	{
		errno = ENAMETOOLONG;
		return -1;
	}

	/* initialise dir */
	dir->_files = NULL;
#ifdef _MSC_VER
	dir->_h = INVALID_HANDLE_VALUE;
#else
	dir->_d = NULL;
#ifndef _TINYDIR_USE_READDIR
	dir->_ep = NULL;
#endif
#endif
	tinydir_close(dir);

	_tinydir_strcpy(dir->path, path);
	/* Remove trailing slashes */
	pathp = &dir->path[_tinydir_strlen(dir->path) - 1];
	while (pathp != dir->path && (*pathp == TINYDIR_STRING('\\') || *pathp == TINYDIR_STRING('/')))
	{
		*pathp = TINYDIR_STRING('\0');
		pathp++;
	}
#ifdef _MSC_VER
	_tinydir_strcpy(path_buf, dir->path);
	_tinydir_strcat(path_buf, TINYDIR_STRING("\\*"));
#if (defined WINAPI_FAMILY) && (WINAPI_FAMILY != WINAPI_FAMILY_DESKTOP_APP)
	dir->_h = FindFirstFileEx(path_buf, FindExInfoStandard, &dir->_f, FindExSearchNameMatch, NULL, 0);
#else
	dir->_h = FindFirstFile(path_buf, &dir->_f);
#endif
	if (dir->_h == INVALID_HANDLE_VALUE)
	{
		errno = ENOENT;
#else
	dir->_d = _tinydir_opendir(path);
	if (dir->_d == NULL)
	{
#endif
		goto bail;
	}

	/* read first file */
	dir->has_next = 1;
#ifndef _MSC_VER
#ifdef _TINYDIR_USE_READDIR
	dir->_e = _tinydir_readdir(dir->_d);
#else
	/* allocate dirent buffer for readdir_r */
	size = _tinydir_dirent_buf_size(dir->_d); /* conversion to int */
	if (size == -1) return -1;
	dir->_ep = (struct _tinydir_dirent*)_TINYDIR_MALLOC(size);
	if (dir->_ep == NULL) return -1;

	error = readdir_r(dir->_d, dir->_ep, &dir->_e);
	if (error != 0) return -1;
#endif
	if (dir->_e == NULL)
	{
		dir->has_next = 0;
	}
#endif

	return 0;

bail:
	tinydir_close(dir);
	return -1;
}

_TINYDIR_FUNC
int tinydir_open_sorted(tinydir_dir *dir, const _tinydir_char_t *path)
{
	/* Count the number of files first, to pre-allocate the files array */
	size_t n_files = 0;
	if (tinydir_open(dir, path) == -1)
	{
		return -1;
	}
	while (dir->has_next)
	{
		n_files++;
		if (tinydir_next(dir) == -1)
		{
			goto bail;
		}
	}
	tinydir_close(dir);

	if (n_files == 0 || tinydir_open(dir, path) == -1)
	{
		return -1;
	}

	dir->n_files = 0;
	dir->_files = (tinydir_file *)_TINYDIR_MALLOC(sizeof *dir->_files * n_files);
	if (dir->_files == NULL)
	{
		goto bail;
	}
	while (dir->has_next)
	{
		tinydir_file *p_file;
		dir->n_files++;

		p_file = &dir->_files[dir->n_files - 1];
		if (tinydir_readfile(dir, p_file) == -1)
		{
			goto bail;
		}

		if (tinydir_next(dir) == -1)
		{
			goto bail;
		}

		/* Just in case the number of files has changed between the first and
		second reads, terminate without writing into unallocated memory */
		if (dir->n_files == n_files)
		{
			break;
		}
	}

	qsort(dir->_files, dir->n_files, sizeof(tinydir_file), _tinydir_file_cmp);

	return 0;

bail:
	tinydir_close(dir);
	return -1;
}

_TINYDIR_FUNC
void tinydir_close(tinydir_dir *dir)
{
	if (dir == NULL)
	{
		return;
	}

	memset(dir->path, 0, sizeof(dir->path));
	dir->has_next = 0;
	dir->n_files = 0;
	_TINYDIR_FREE(dir->_files);
	dir->_files = NULL;
#ifdef _MSC_VER
	if (dir->_h != INVALID_HANDLE_VALUE)
	{
		FindClose(dir->_h);
	}
	dir->_h = INVALID_HANDLE_VALUE;
#else
	if (dir->_d)
	{
		_tinydir_closedir(dir->_d);
	}
	dir->_d = NULL;
	dir->_e = NULL;
#ifndef _TINYDIR_USE_READDIR
	_TINYDIR_FREE(dir->_ep);
	dir->_ep = NULL;
#endif
#endif
}

_TINYDIR_FUNC
int tinydir_next(tinydir_dir *dir)
{
	if (dir == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	if (!dir->has_next)
	{
		errno = ENOENT;
		return -1;
	}

#ifdef _MSC_VER
	if (FindNextFile(dir->_h, &dir->_f) == 0)
#else
#ifdef _TINYDIR_USE_READDIR
	dir->_e = _tinydir_readdir(dir->_d);
#else
	if (dir->_ep == NULL)
	{
		return -1;
	}
	if (readdir_r(dir->_d, dir->_ep, &dir->_e) != 0)
	{
		return -1;
	}
#endif
	if (dir->_e == NULL)
#endif
	{
		dir->has_next = 0;
#ifdef _MSC_VER
		if (GetLastError() != ERROR_SUCCESS &&
			GetLastError() != ERROR_NO_MORE_FILES)
		{
			tinydir_close(dir);
			errno = EIO;
			return -1;
		}
#endif
	}

	return 0;
}

_TINYDIR_FUNC
int tinydir_readfile(const tinydir_dir *dir, tinydir_file *file)
{
	const _tinydir_char_t *filename;
	if (dir == NULL || file == NULL)
	{
		errno = EINVAL;
		return -1;
	}
#ifdef _MSC_VER
	if (dir->_h == INVALID_HANDLE_VALUE)
#else
	if (dir->_e == NULL)
#endif
	{
		errno = ENOENT;
		return -1;
	}
	filename =
#ifdef _MSC_VER
		dir->_f.cFileName;
#else
		dir->_e->d_name;
#endif
	if (_tinydir_strlen(dir->path) +
		_tinydir_strlen(filename) + 1 + _TINYDIR_PATH_EXTRA >=
		_TINYDIR_PATH_MAX)
	{
		/* the path for the file will be too long */
		errno = ENAMETOOLONG;
		return -1;
	}
	if (_tinydir_strlen(filename) >= _TINYDIR_FILENAME_MAX)
	{
		errno = ENAMETOOLONG;
		return -1;
	}

	_tinydir_strcpy(file->path, dir->path);
	if (_tinydir_strcmp(dir->path, TINYDIR_STRING("/")) != 0)
		_tinydir_strcat(file->path, TINYDIR_STRING("/"));
	_tinydir_strcpy(file->name, filename);
	_tinydir_strcat(file->path, filename);
#ifndef _MSC_VER
#ifdef __MINGW32__
	if (_tstat(
#elif (defined _BSD_SOURCE) || (defined _DEFAULT_SOURCE)	\
	|| ((defined _XOPEN_SOURCE) && (_XOPEN_SOURCE >= 500))	\
	|| ((defined _POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 200112L))
	if (lstat(
#else
	if (stat(
#endif
		file->path, &file->_s) == -1)
	{
		return -1;
	}
#endif
	_tinydir_get_ext(file);

	file->is_dir =
#ifdef _MSC_VER
		!!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
#else
		S_ISDIR(file->_s.st_mode);
#endif
	file->is_reg =
#ifdef _MSC_VER
		!!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) ||
		(
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_DEVICE) &&
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED) &&
#ifdef FILE_ATTRIBUTE_INTEGRITY_STREAM
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_INTEGRITY_STREAM) &&
#endif
#ifdef FILE_ATTRIBUTE_NO_SCRUB_DATA
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_NO_SCRUB_DATA) &&
#endif
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE) &&
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY));
#else
		S_ISREG(file->_s.st_mode);
#endif

	return 0;
}

_TINYDIR_FUNC
int tinydir_readfile_n(const tinydir_dir *dir, tinydir_file *file, size_t i)
{
	if (dir == NULL || file == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	if (i >= dir->n_files)
	{
		errno = ENOENT;
		return -1;
	}

	memcpy(file, &dir->_files[i], sizeof(tinydir_file));
	_tinydir_get_ext(file);

	return 0;
}

_TINYDIR_FUNC
int tinydir_open_subdir_n(tinydir_dir *dir, size_t i)
{
	_tinydir_char_t path[_TINYDIR_PATH_MAX];
	if (dir == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	if (i >= dir->n_files || !dir->_files[i].is_dir)
	{
		errno = ENOENT;
		return -1;
	}

	_tinydir_strcpy(path, dir->_files[i].path);
	tinydir_close(dir);
	if (tinydir_open_sorted(dir, path) == -1)
	{
		return -1;
	}

	return 0;
}

/* Open a single file given its path */
_TINYDIR_FUNC
int tinydir_file_open(tinydir_file *file, const _tinydir_char_t *path)
{
	tinydir_dir dir;
	int result = 0;
	int found = 0;
	_tinydir_char_t dir_name_buf[_TINYDIR_PATH_MAX];
	_tinydir_char_t file_name_buf[_TINYDIR_FILENAME_MAX];
	_tinydir_char_t *dir_name;
	_tinydir_char_t *base_name;
#if (defined _MSC_VER || defined __MINGW32__)
	_tinydir_char_t drive_buf[_TINYDIR_PATH_MAX];
	_tinydir_char_t ext_buf[_TINYDIR_FILENAME_MAX];
#endif

	if (file == NULL || path == NULL || _tinydir_strlen(path) == 0)
	{
		errno = EINVAL;
		return -1;
	}
	if (_tinydir_strlen(path) + _TINYDIR_PATH_EXTRA >= _TINYDIR_PATH_MAX)
	{
		errno = ENAMETOOLONG;
		return -1;
	}

	/* Get the parent path */
#if (defined _MSC_VER || defined __MINGW32__)
#if ((defined _MSC_VER) && (_MSC_VER >= 1400))
	errno = _tsplitpath_s(
		path,
		drive_buf, _TINYDIR_DRIVE_MAX,
		dir_name_buf, _TINYDIR_FILENAME_MAX,
		file_name_buf, _TINYDIR_FILENAME_MAX,
		ext_buf, _TINYDIR_FILENAME_MAX);
#else
	_tsplitpath(
		path,
		drive_buf,
		dir_name_buf,
		file_name_buf,
		ext_buf);
#endif

	if (errno)
	{
		return -1;
	}

/* _splitpath_s not work fine with only filename and widechar support */
#ifdef _UNICODE
	if (drive_buf[0] == L'\xFEFE')
		drive_buf[0] = '\0';
	if (dir_name_buf[0] == L'\xFEFE')
		dir_name_buf[0] = '\0';
#endif

	/* Emulate the behavior of dirname by returning "." for dir name if it's
	empty */
	if (drive_buf[0] == '\0' && dir_name_buf[0] == '\0')
	{
		_tinydir_strcpy(dir_name_buf, TINYDIR_STRING("."));
	}
	/* Concatenate the drive letter and dir name to form full dir name */
	_tinydir_strcat(drive_buf, dir_name_buf);
	dir_name = drive_buf;
	/* Concatenate the file name and extension to form base name */
	_tinydir_strcat(file_name_buf, ext_buf);
	base_name = file_name_buf;
#else
	_tinydir_strcpy(dir_name_buf, path);
	dir_name = dirname(dir_name_buf);
	_tinydir_strcpy(file_name_buf, path);
	base_name = basename(file_name_buf);
#endif

	/* Special case: if the path is a root dir, open the parent dir as the file */
#if (defined _MSC_VER || defined __MINGW32__)
	if (_tinydir_strlen(base_name) == 0)
#else
	if ((_tinydir_strcmp(base_name, TINYDIR_STRING("/"))) == 0)
#endif
	{
		memset(file, 0, sizeof * file);
		file->is_dir = 1;
		file->is_reg = 0;
		_tinydir_strcpy(file->path, dir_name);
		file->extension = file->path + _tinydir_strlen(file->path);
		return 0;
	}

	/* Open the parent directory */
	if (tinydir_open(&dir, dir_name) == -1)
	{
		return -1;
	}

	/* Read through the parent directory and look for the file */
	while (dir.has_next)
	{
		if (tinydir_readfile(&dir, file) == -1)
		{
			result = -1;
			goto bail;
		}
		if (_tinydir_strcmp(file->name, base_name) == 0)
		{
			/* File found */
			found = 1;
			break;
		}
		tinydir_next(&dir);
	}
	if (!found)
	{
		result = -1;
		errno = ENOENT;
	}

bail:
	tinydir_close(&dir);
	return result;
}

_TINYDIR_FUNC
void _tinydir_get_ext(tinydir_file *file)
{
	_tinydir_char_t *period = _tinydir_strrchr(file->name, TINYDIR_STRING('.'));
	if (period == NULL)
	{
		file->extension = &(file->name[_tinydir_strlen(file->name)]);
	}
	else
	{
		file->extension = period + 1;
	}
}

_TINYDIR_FUNC
int _tinydir_file_cmp(const void *a, const void *b)
{
	const tinydir_file *fa = (const tinydir_file *)a;
	const tinydir_file *fb = (const tinydir_file *)b;
	if (fa->is_dir != fb->is_dir)
	{
		return -(fa->is_dir - fb->is_dir);
	}
	return _tinydir_strncmp(fa->name, fb->name, _TINYDIR_FILENAME_MAX);
}

#ifndef _MSC_VER
#ifndef _TINYDIR_USE_READDIR
/*
The following authored by Ben Hutchings <ben@decadent.org.uk>
from https://womble.decadent.org.uk/readdir_r-advisory.html
*/
/* Calculate the required buffer size (in bytes) for directory      *
* entries read from the given directory handle.  Return -1 if this  *
* this cannot be done.                                              *
*                                                                   *
* This code does not trust values of NAME_MAX that are less than    *
* 255, since some systems (including at least HP-UX) incorrectly    *
* define it to be a smaller value.                                  */
_TINYDIR_FUNC
size_t _tinydir_dirent_buf_size(_TINYDIR_DIR *dirp)
{
	long name_max;
	size_t name_end;
	/* parameter may be unused */
	(void)dirp;

#if defined _TINYDIR_USE_FPATHCONF
	name_max = fpathconf(dirfd(dirp), _PC_NAME_MAX);
	if (name_max == -1)
#if defined(NAME_MAX)
		name_max = (NAME_MAX > 255) ? NAME_MAX : 255;
#else
		return (size_t)(-1);
#endif
#elif defined(NAME_MAX)
 	name_max = (NAME_MAX > 255) ? NAME_MAX : 255;
#else
#error "buffer size for readdir_r cannot be determined"
#endif
	name_end = (size_t)offsetof(struct _tinydir_dirent, d_name) + name_max + 1;
	return (name_end > sizeof(struct _tinydir_dirent) ?
		name_end : sizeof(struct _tinydir_dirent));
}
#endif
#endif

#ifdef __cplusplus
}
#endif

# if defined (_MSC_VER)
# pragma warning(pop)
# endif

#endif
#line 0


#line 1 "sfwl/core/dir_access.cpp"



Error DirAccess::open_dir(const String &path, bool skip_specials) {
	if (_dir_open) {
		return ERR_CANT_ACQUIRE_RESOURCE;
	}

	_skip_specials = skip_specials;

	if (tinydir_open(_dir, path.utf8().get_data()) == -1) {
		return FAILED;
	}

	_dir_open = true;

	return OK;
}

Error DirAccess::open_dir(const char *path, bool skip_specials) {
	if (_dir_open) {
		return ERR_CANT_ACQUIRE_RESOURCE;
	}

	_skip_specials = skip_specials;

	if (tinydir_open(_dir, path) == -1) {
		return FAILED;
	}

	_dir_open = true;

	return OK;
}

void DirAccess::close_dir() {
	if (!_dir_open) {
		return;
	}

	tinydir_close(_dir);

	_dir_open = false;
}

bool DirAccess::has_next() {
	if (!_dir) {
		return false;
	}

	return _dir->has_next;
}
bool DirAccess::read() {
	_read_file_result = tinydir_readfile(_dir, _file);

	return _read_file_result != -1;
}
bool DirAccess::next() {
	if (!_dir->has_next) {
		return false;
	}

	bool rres = read();
	while (!rres && _dir->has_next) {
		tinydir_next(_dir);
		rres = read();
	}

	if (!rres) {
		return false;
	}

	if (_dir->has_next) {
		tinydir_next(_dir);
	}

	if (_skip_specials && current_is_dir() && current_is_special_dir()) {
		return next();
	}

	return true;
}

bool DirAccess::current_is_ok() {
	return _read_file_result == 01;
}
String DirAccess::current_get_name() {
	return String(_file->name);
}
String DirAccess::current_get_path() {
	return String(_file->path);
}
String DirAccess::current_get_extension() {
	return String(_file->extension);
}
const char *DirAccess::current_get_name_cstr() {
	return _file->name;
}
const char *DirAccess::current_get_path_cstr() {
	return _file->path;
}
const char *DirAccess::current_get_extension_cstr() {
	return _file->extension;
}
bool DirAccess::current_is_file() {
	return !_file->is_dir;
}
bool DirAccess::current_is_dir() {
	return _file->is_dir;
}
bool DirAccess::current_is_special_dir() {
	if ((_file->name[0] == '.' && _file->name[1] == '\0') || (_file->name[0] == '.' && _file->name[1] == '.')) {
		return true;
	}

	return false;
}

bool DirAccess::is_dir_open() {
	return _dir_open;
}
bool DirAccess::is_dir_closed() {
	return !_dir_open;
}

DirAccess::DirAccess() {
	_skip_specials = true;
	_read_file_result = 0;
	_dir_open = false;
	_dir = memnew(tinydir_dir);
	_file = memnew(tinydir_file);
}
DirAccess::~DirAccess() {
	if (is_dir_open()) {
		close_dir();
	}

	memdelete(_dir);
	memdelete(_file);
}
#line 0


#line 1 "sfwl/core/sfw_core.cpp"



void SFWCore::setup() {
	if (_initialized) {
		return;
	}

	_initialized = true;

	StringName::setup();
	MemoryPool::setup();
}

void SFWCore::cleanup() {
	if (!_initialized) {
		return;
	}

	_initialized = false;

	StringName::cleanup();
	MemoryPool::cleanup();
}

bool SFWCore::_initialized = false;
#line 0


//===================  OBJECT SECTION  ===================


#line 1 "sfwl/object/resource.cpp"


void Resource::emit_changed() {
	changed.emit(this);
}

Error Resource::load(const String &path) {
	return ERR_UNAVAILABLE;
}
Error Resource::save(const String &path) {
	return ERR_UNAVAILABLE;
}

Resource::Resource() :
		Reference() {
}

Resource::~Resource() {
}
#line 0

#line 1 "sfwl/object/reference.cpp"


/*************************************************************************/
/*  reference.cpp                                                        */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

bool Reference::init_ref() {
	if (reference()) {
		if (!is_referenced() && refcount_init.unref()) {
			unreference(); // first referencing is already 1, so compensate for the ref above
		}

		return true;
	} else {
		return false;
	}
}

int Reference::reference_get_count() const {
	return refcount.get();
}

bool Reference::reference() {
	uint32_t rc_val = refcount.refval();
	bool success = rc_val != 0;

	return success;
}

bool Reference::unreference() {
	uint32_t rc_val = refcount.unrefval();
	bool die = rc_val == 0;

	return die;
}

Reference::Reference() :
		Object() {
	refcount.init();
	refcount_init.init();
}

Reference::~Reference() {
}

/*
void WeakRef::set_obj(Object *p_object) {
	//ref = p_object ? p_object->get_instance_id() : 0;
}

void WeakRef::set_ref(const REF &p_ref) {
	//ref = p_ref.is_valid() ? p_ref->get_instance_id() : 0;
}

WeakRef::WeakRef() :
		ref(0) {
}
*/#line 0

#line 1 "sfwl/object/object.cpp"


void Object::set(const StringName &p_name, const Variant &p_value, bool *r_valid) {
	if (p_name == CoreStringNames::get_singleton()->_meta) {
		//set_meta(p_name,p_value);
		metadata = p_value.duplicate();
		if (r_valid) {
			*r_valid = true;
		}
		return;
	}

	//something inside the object... :|
	bool success = _setv(p_name, p_value);
	if (success) {
		if (r_valid) {
			*r_valid = true;
		}
		return;
	}

	if (r_valid) {
		*r_valid = false;
	}
}

Variant Object::get(const StringName &p_name, bool *r_valid) const {
	Variant ret;

	if (p_name == CoreStringNames::get_singleton()->_meta) {
		ret = metadata;
		if (r_valid) {
			*r_valid = true;
		}
		return ret;

	} else {
		//something inside the object... :|
		bool success = _getv(p_name, ret);
		if (success) {
			if (r_valid) {
				*r_valid = true;
			}
			return ret;
		}

		if (r_valid) {
			*r_valid = false;
		}

		return Variant();
	}
}

bool Object::lt(const Variant &p_value_l, const Variant &p_value_r) {
	return p_value_l < p_value_r;
}

void Object::notification(int p_notification, bool p_reversed) {
	_notificationv(p_notification, p_reversed);
}

String Object::to_string() {
	return "[" + get_class() + ":" + itos(get_instance_id()) + "]";
}

bool Object::_predelete() {
	_predelete_ok = 1;
	notification(NOTIFICATION_PREDELETE, true);
	if (_predelete_ok) {
		_class_ptr = nullptr; //must restore so destructors can access class ptr correctly
	}
	return _predelete_ok;
}

void Object::_postinitialize() {
	_class_ptr = _get_class_namev();
	notification(NOTIFICATION_POSTINITIALIZE);
}

bool Object::has_meta(const String &p_name) const {
	return metadata.has(p_name);
}

void Object::set_meta(const String &p_name, const Variant &p_value) {
	if (p_value.get_type() == Variant::NIL) {
		metadata.erase(p_name);
		return;
	};

	metadata[p_name] = p_value;
}

Variant Object::get_meta(const String &p_name, const Variant &p_default) const {
	if (!metadata.has(p_name)) {
		return p_default;
	}
	return metadata[p_name];
}

void Object::remove_meta(const String &p_name) {
	metadata.erase(p_name);
}

void Object::cancel_free() {
	_predelete_ok = 0;
}

Object::Object() {
	_is_queued_for_deletion = false;
	_predelete_ok = 0;
	_instance_id = 0;
	_instance_id = ObjectDB::add_instance(this);
}

Object::~Object() {
}

ObjectRC *Object::_use_rc() {
	// The RC object is lazily created the first time it's requested;
	// that way, there's no need to allocate and release it at all if this Object
	// is not being referred by any Variant at all.

	// Although when dealing with Objects from multiple threads some locking
	// mechanism should be used, this at least makes safe the case of first
	// assignment.

	ObjectRC *rc = nullptr;
	ObjectRC *const creating = reinterpret_cast<ObjectRC *>(1);
	if (unlikely(_rc.compare_exchange_strong(rc, creating, std::memory_order_acq_rel))) {
		// Not created yet
		rc = memnew(ObjectRC(this));
		_rc.store(rc, std::memory_order_release);
		return rc;
	}

	// Spin-wait until we know it's created (or just return if it's already created)
	for (;;) {
		if (likely(rc != creating)) {
			rc->increment();
			return rc;
		}
		rc = _rc.load(std::memory_order_acquire);
	}
}

bool predelete_handler(Object *p_object) {
	return p_object->_predelete();
}

void postinitialize_handler(Object *p_object) {
	p_object->_postinitialize();
}

HashMap<ObjectID, Object *> ObjectDB::instances;
ObjectID ObjectDB::instance_counter = 1;
HashMap<Object *, ObjectID, ObjectDB::ObjectPtrHash> ObjectDB::instance_checks;
ObjectID ObjectDB::add_instance(Object *p_object) {
	ERR_FAIL_COND_V(p_object->get_instance_id() != 0, 0);

	rw_lock.write_lock();
	ObjectID instance_id = ++instance_counter;
	instances[instance_id] = p_object;
	instance_checks[p_object] = instance_id;

	rw_lock.write_unlock();

	return instance_id;
}

void ObjectDB::remove_instance(Object *p_object) {
	rw_lock.write_lock();

	instances.erase(p_object->get_instance_id());
	instance_checks.erase(p_object);

	rw_lock.write_unlock();
}
Object *ObjectDB::get_instance(ObjectID p_instance_id) {
	rw_lock.read_lock();
	Object **obj = instances.getptr(p_instance_id);
	rw_lock.read_unlock();

	if (!obj) {
		return nullptr;
	}
	return *obj;
}

void ObjectDB::debug_objects(DebugFunc p_func) {
	rw_lock.read_lock();

	const ObjectID *K = nullptr;
	while ((K = instances.next(K))) {
		p_func(instances[*K]);
	}

	rw_lock.read_unlock();
}

int ObjectDB::get_object_count() {
	rw_lock.read_lock();
	int count = instances.size();
	rw_lock.read_unlock();

	return count;
}

RWLock ObjectDB::rw_lock;

void ObjectDB::cleanup() {
	rw_lock.write_lock();
	if (instances.size()) {
		LOG_WARN("ObjectDB instances leaked at exit!");
	}
	instances.clear();
	instance_checks.clear();
	rw_lock.write_unlock();
}
#line 0

#line 1 "sfwl/object/ref_ptr.cpp"
/*************************************************************************/
/*  ref_ptr.cpp                                                          */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



void RefPtr::operator=(const RefPtr &p_other) {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	Ref<Reference> *ref_other = reinterpret_cast<Ref<Reference> *>(const_cast<char *>(&p_other.data[0]));

	*ref = *ref_other;
}

bool RefPtr::operator==(const RefPtr &p_other) const {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	Ref<Reference> *ref_other = reinterpret_cast<Ref<Reference> *>(const_cast<char *>(&p_other.data[0]));

	return *ref == *ref_other;
}

bool RefPtr::operator!=(const RefPtr &p_other) const {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	Ref<Reference> *ref_other = reinterpret_cast<Ref<Reference> *>(const_cast<char *>(&p_other.data[0]));

	return *ref != *ref_other;
}

RefPtr::RefPtr(const RefPtr &p_other) {
	memnew_placement(&data[0], Ref<Reference>);

	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	Ref<Reference> *ref_other = reinterpret_cast<Ref<Reference> *>(const_cast<char *>(&p_other.data[0]));

	*ref = *ref_other;
}

bool RefPtr::is_null() const {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	return ref->is_null();
}

void RefPtr::unref() {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	ref->unref();
}

RefPtr::RefPtr() {
	ERR_FAIL_COND(sizeof(Ref<Reference>) > DATASIZE);
	memnew_placement(&data[0], Ref<Reference>);
}

RefPtr::~RefPtr() {
	Ref<Reference> *ref = reinterpret_cast<Ref<Reference> *>(&data[0]);
	ref->~Ref<Reference>();
}
#line 0

#line 1 "sfwl/object/core_string_names.cpp"
/*************************************************************************/
/*  core_string_names.cpp                                                */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



CoreStringNames *CoreStringNames::singleton = nullptr;

CoreStringNames::CoreStringNames() :
		_free(StaticCString::create("free")),
		changed(StaticCString::create("changed")),
		_meta(StaticCString::create("__meta__")),
		_script(StaticCString::create("script")),
		script_changed(StaticCString::create("script_changed")),
		___pdcdata(StaticCString::create("___pdcdata")),
		__getvar(StaticCString::create("__getvar")),
		_iter_init(StaticCString::create("_iter_init")),
		_iter_next(StaticCString::create("_iter_next")),
		_iter_get(StaticCString::create("_iter_get")),
		get_rid(StaticCString::create("get_rid")),
		_to_string(StaticCString::create("_to_string")),
#ifdef TOOLS_ENABLED
		_sections_unfolded(StaticCString::create("_sections_unfolded")),
#endif
		_custom_features(StaticCString::create("_custom_features")),
		x(StaticCString::create("x")),
		y(StaticCString::create("y")),
		z(StaticCString::create("z")),
		w(StaticCString::create("w")),
		r(StaticCString::create("r")),
		g(StaticCString::create("g")),
		b(StaticCString::create("b")),
		a(StaticCString::create("a")),
		position(StaticCString::create("position")),
		size(StaticCString::create("size")),
		end(StaticCString::create("end")),
		basis(StaticCString::create("basis")),
		origin(StaticCString::create("origin")),
		normal(StaticCString::create("normal")),
		d(StaticCString::create("d")),
		h(StaticCString::create("h")),
		s(StaticCString::create("s")),
		v(StaticCString::create("v")),
		r8(StaticCString::create("r8")),
		g8(StaticCString::create("g8")),
		b8(StaticCString::create("b8")),
		a8(StaticCString::create("a8")) {
}
#line 0

#line 1 "sfwl/object/dictionary.cpp"
/*************************************************************************/
/*  dictionary.cpp                                                       */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



struct DictionaryPrivate {
	SafeRefCount refcount;
	OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator> variant_map;
};

void Dictionary::get_key_list(List<Variant> *p_keys) const {
	if (_p->variant_map.empty()) {
		return;
	}

	for (OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element E = _p->variant_map.front(); E; E = E.next()) {
		p_keys->push_back(E.key());
	}
}

Variant Dictionary::get_key_at_index(int p_index) const {
	int index = 0;
	for (OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element E = _p->variant_map.front(); E; E = E.next()) {
		if (index == p_index) {
			return E.key();
		}
		index++;
	}

	return Variant();
}

Variant Dictionary::get_value_at_index(int p_index) const {
	int index = 0;
	for (OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element E = _p->variant_map.front(); E; E = E.next()) {
		if (index == p_index) {
			return E.value();
		}
		index++;
	}

	return Variant();
}

Variant &Dictionary::operator[](const Variant &p_key) {
	return _p->variant_map[p_key];
}

const Variant &Dictionary::operator[](const Variant &p_key) const {
	return _p->variant_map[p_key];
}
const Variant *Dictionary::getptr(const Variant &p_key) const {
	OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::ConstElement E = ((const OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator> *)&_p->variant_map)->find(p_key);

	if (!E) {
		return nullptr;
	}
	return &E.get();
}

Variant *Dictionary::getptr(const Variant &p_key) {
	OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element E = _p->variant_map.find(p_key);

	if (!E) {
		return nullptr;
	}
	return &E.get();
}

Variant Dictionary::get_valid(const Variant &p_key) const {
	OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::ConstElement E = ((const OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator> *)&_p->variant_map)->find(p_key);

	if (!E) {
		return Variant();
	}
	return E.get();
}

Variant Dictionary::get(const Variant &p_key, const Variant &p_default) const {
	const Variant *result = getptr(p_key);
	if (!result) {
		return p_default;
	}

	return *result;
}

int Dictionary::size() const {
	return _p->variant_map.size();
}
bool Dictionary::empty() const {
	return !_p->variant_map.size();
}

bool Dictionary::has(const Variant &p_key) const {
	return _p->variant_map.has(p_key);
}

bool Dictionary::has_all(const Array &p_keys) const {
	for (int i = 0; i < p_keys.size(); i++) {
		if (!has(p_keys[i])) {
			return false;
		}
	}
	return true;
}

Variant Dictionary::find_key(const Variant &p_value) const {
	for (OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element E = _p->variant_map.front(); E; E = E.next()) {
		if (E.value() == p_value) {
			return E.key();
		}
	}
	return Variant();
}

bool Dictionary::erase(const Variant &p_key) {
	return _p->variant_map.erase(p_key);
}

bool Dictionary::deep_equal(const Dictionary &p_dictionary, int p_recursion_count) const {
	// Cheap checks
	ERR_FAIL_COND_V_MSG(p_recursion_count > MAX_RECURSION, 0, "Max recursion reached");
	if (_p == p_dictionary._p) {
		return true;
	}
	if (_p->variant_map.size() != p_dictionary._p->variant_map.size()) {
		return false;
	}

	// Heavy O(n) check
	OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element this_E = _p->variant_map.front();
	OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element other_E = p_dictionary._p->variant_map.front();
	p_recursion_count++;
	while (this_E && other_E) {
		if (
				!this_E.key().deep_equal(other_E.key(), p_recursion_count) ||
				!this_E.value().deep_equal(other_E.value(), p_recursion_count)) {
			return false;
		}

		this_E = this_E.next();
		other_E = other_E.next();
	}

	return !this_E && !other_E;
}

bool Dictionary::operator==(const Dictionary &p_dictionary) const {
	return _p == p_dictionary._p;
}

bool Dictionary::operator!=(const Dictionary &p_dictionary) const {
	return _p != p_dictionary._p;
}

void Dictionary::_ref(const Dictionary &p_from) const {
	//make a copy first (thread safe)
	if (!p_from._p->refcount.ref()) {
		return; // couldn't copy
	}

	//if this is the same, unreference the other one
	if (p_from._p == _p) {
		_p->refcount.unref();
		return;
	}
	if (_p) {
		_unref();
	}
	_p = p_from._p;
}

void Dictionary::clear() {
	_p->variant_map.clear();
}

void Dictionary::merge(const Dictionary &p_dictionary, bool p_overwrite) {
	for (OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element E = p_dictionary._p->variant_map.front(); E; E = E.next()) {
		if (p_overwrite || !has(E.key())) {
			this->operator[](E.key()) = E.value();
		}
	}
}

void Dictionary::_unref() const {
	ERR_FAIL_COND(!_p);
	if (_p->refcount.unref()) {
		memdelete(_p);
	}
	_p = nullptr;
}

uint32_t Dictionary::hash() const {
	return recursive_hash(0);
}

uint32_t Dictionary::recursive_hash(int p_recursion_count) const {
	ERR_FAIL_COND_V_MSG(p_recursion_count > MAX_RECURSION, 0, "Max recursion reached");
	p_recursion_count++;

	uint32_t h = hash_murmur3_one_32(Variant::DICTIONARY);

	for (OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element E = _p->variant_map.front(); E; E = E.next()) {
		h = hash_murmur3_one_32(E.key().recursive_hash(p_recursion_count), h);
		h = hash_murmur3_one_32(E.value().recursive_hash(p_recursion_count), h);
	}

	return hash_fmix32(h);
}

Array Dictionary::keys() const {
	Array varr;
	if (_p->variant_map.empty()) {
		return varr;
	}

	varr.resize(size());

	int i = 0;
	for (OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element E = _p->variant_map.front(); E; E = E.next()) {
		varr[i] = E.key();
		i++;
	}

	return varr;
}

Array Dictionary::values() const {
	Array varr;
	if (_p->variant_map.empty()) {
		return varr;
	}

	varr.resize(size());

	int i = 0;
	for (OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element E = _p->variant_map.front(); E; E = E.next()) {
		varr[i] = E.get();
		i++;
	}

	return varr;
}

const Variant *Dictionary::next(const Variant *p_key) const {
	if (p_key == nullptr) {
		// caller wants to get the first element
		if (_p->variant_map.front()) {
			return &_p->variant_map.front().key();
		}
		return nullptr;
	}
	OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element E = _p->variant_map.find(*p_key);

	if (E && E.next()) {
		return &E.next().key();
	}
	return nullptr;
}

Dictionary Dictionary::duplicate(bool p_deep) const {
	Dictionary n;

	for (OrderedHashMap<Variant, Variant, VariantHasher, VariantComparator>::Element E = _p->variant_map.front(); E; E = E.next()) {
		n[E.key()] = p_deep ? E.value().duplicate(true) : E.value();
	}

	return n;
}

void Dictionary::operator=(const Dictionary &p_dictionary) {
	_ref(p_dictionary);
}

const void *Dictionary::id() const {
	return _p;
}

Dictionary::Dictionary(const Dictionary &p_from) {
	_p = nullptr;
	_ref(p_from);
}

Dictionary::Dictionary() {
	_p = memnew(DictionaryPrivate);
	_p->refcount.init();
}
Dictionary::~Dictionary() {
	_unref();
}
#line 0

#line 1 "sfwl/object/array.cpp"
/*************************************************************************/
/*  array.cpp                                                            */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



class ArrayPrivate {
public:
	SafeRefCount refcount;
	Vector<Variant> array;
};

void Array::_ref(const Array &p_from) const {
	ArrayPrivate *_fp = p_from._p;

	ERR_FAIL_COND(!_fp); // should NOT happen.

	if (_fp == _p) {
		return; // whatever it is, nothing to do here move along
	}

	bool success = _fp->refcount.ref();

	ERR_FAIL_COND(!success); // should really not happen either

	_unref();

	_p = p_from._p;
}

void Array::_unref() const {
	if (!_p) {
		return;
	}

	if (_p->refcount.unref()) {
		memdelete(_p);
	}
	_p = nullptr;
}

Variant &Array::operator[](int p_idx) {
	return _p->array.write[p_idx];
}

const Variant &Array::operator[](int p_idx) const {
	return _p->array[p_idx];
}

int Array::size() const {
	return _p->array.size();
}
bool Array::empty() const {
	return _p->array.empty();
}
void Array::clear() {
	_p->array.clear();
}

bool Array::deep_equal(const Array &p_array, int p_recursion_count) const {
	// Cheap checks
	ERR_FAIL_COND_V_MSG(p_recursion_count > MAX_RECURSION, true, "Max recursion reached");
	if (_p == p_array._p) {
		return true;
	}
	const Vector<Variant> &a1 = _p->array;
	const Vector<Variant> &a2 = p_array._p->array;
	const int size = a1.size();
	if (size != a2.size()) {
		return false;
	}

	// Heavy O(n) check
	p_recursion_count++;
	for (int i = 0; i < size; i++) {
		if (!a1[i].deep_equal(a2[i], p_recursion_count)) {
			return false;
		}
	}

	return true;
}

bool Array::operator==(const Array &p_array) const {
	return _p == p_array._p;
}

uint32_t Array::hash() const {
	return recursive_hash(0);
}

uint32_t Array::recursive_hash(int p_recursion_count) const {
	ERR_FAIL_COND_V_MSG(p_recursion_count > MAX_RECURSION, 0, "Max recursion reached");
	p_recursion_count++;

	uint32_t h = hash_murmur3_one_32(0);

	for (int i = 0; i < _p->array.size(); i++) {
		h = hash_murmur3_one_32(_p->array[i].recursive_hash(p_recursion_count), h);
	}
	return hash_fmix32(h);
}

void Array::operator=(const Array &p_array) {
	_ref(p_array);
}

void Array::push_back(const Variant &p_value) {
	_p->array.push_back(p_value);
}

void Array::append_array(const Array &p_array) {
	_p->array.append_array(p_array._p->array);
}

Error Array::resize(int p_new_size) {
	return _p->array.resize(p_new_size);
}

void Array::insert(int p_pos, const Variant &p_value) {
	_p->array.insert(p_pos, p_value);
}

void Array::fill(const Variant &p_value) {
	_p->array.fill(p_value);
}

void Array::erase(const Variant &p_value) {
	_p->array.erase(p_value);
}

Variant Array::front() const {
	ERR_FAIL_COND_V_MSG(_p->array.size() == 0, Variant(), "Can't take value from empty array.");
	return operator[](0);
}

Variant Array::back() const {
	ERR_FAIL_COND_V_MSG(_p->array.size() == 0, Variant(), "Can't take value from empty array.");
	return operator[](_p->array.size() - 1);
}

int Array::find(const Variant &p_value, int p_from) const {
	return _p->array.find(p_value, p_from);
}

int Array::rfind(const Variant &p_value, int p_from) const {
	if (_p->array.size() == 0) {
		return -1;
	}

	if (p_from < 0) {
		// Relative offset from the end
		p_from = _p->array.size() + p_from;
	}
	if (p_from < 0 || p_from >= _p->array.size()) {
		// Limit to array boundaries
		p_from = _p->array.size() - 1;
	}

	for (int i = p_from; i >= 0; i--) {
		if (_p->array[i] == p_value) {
			return i;
		}
	}

	return -1;
}

int Array::find_last(const Variant &p_value) const {
	return rfind(p_value);
}

int Array::count(const Variant &p_value) const {
	if (_p->array.size() == 0) {
		return 0;
	}

	int amount = 0;
	for (int i = 0; i < _p->array.size(); i++) {
		if (_p->array[i] == p_value) {
			amount++;
		}
	}

	return amount;
}

bool Array::has(const Variant &p_value) const {
	return _p->array.find(p_value, 0) != -1;
}

void Array::remove(int p_pos) {
	_p->array.remove(p_pos);
}

void Array::set(int p_idx, const Variant &p_value) {
	operator[](p_idx) = p_value;
}

const Variant &Array::get(int p_idx) const {
	return operator[](p_idx);
}

Array Array::duplicate(bool p_deep) const {
	Array new_arr;
	int element_count = size();
	new_arr.resize(element_count);
	for (int i = 0; i < element_count; i++) {
		new_arr[i] = p_deep ? get(i).duplicate(p_deep) : get(i);
	}

	return new_arr;
}

int Array::_clamp_slice_index(int p_index) const {
	int arr_size = size();
	int fixed_index = CLAMP(p_index, -arr_size, arr_size - 1);
	if (fixed_index < 0) {
		fixed_index = arr_size + fixed_index;
	}
	return fixed_index;
}

Array Array::slice(int p_begin, int p_end, int p_step, bool p_deep) const { // like python, but inclusive on upper bound

	Array new_arr;

	ERR_FAIL_COND_V_MSG(p_step == 0, new_arr, "Array slice step size cannot be zero.");

	if (empty()) { // Don't try to slice empty arrays.
		return new_arr;
	}
	if (p_step > 0) {
		if (p_begin >= size() || p_end < -size()) {
			return new_arr;
		}
	} else { // p_step < 0
		if (p_begin < -size() || p_end >= size()) {
			return new_arr;
		}
	}

	int begin = _clamp_slice_index(p_begin);
	int end = _clamp_slice_index(p_end);

	int new_arr_size = MAX(((end - begin + p_step) / p_step), 0);
	new_arr.resize(new_arr_size);

	if (p_step > 0) {
		int dest_idx = 0;
		for (int idx = begin; idx <= end; idx += p_step) {
			ERR_FAIL_COND_V_MSG(dest_idx < 0 || dest_idx >= new_arr_size, Array(), "Bug in Array slice()");
			new_arr[dest_idx++] = p_deep ? get(idx).duplicate(p_deep) : get(idx);
		}
	} else { // p_step < 0
		int dest_idx = 0;
		for (int idx = begin; idx >= end; idx += p_step) {
			ERR_FAIL_COND_V_MSG(dest_idx < 0 || dest_idx >= new_arr_size, Array(), "Bug in Array slice()");
			new_arr[dest_idx++] = p_deep ? get(idx).duplicate(p_deep) : get(idx);
		}
	}

	return new_arr;
}

struct _ArrayVariantSort {
	_FORCE_INLINE_ bool operator()(const Variant &p_l, const Variant &p_r) const {
		bool valid = false;
		Variant res;
		Variant::evaluate(Variant::OP_LESS, p_l, p_r, res, valid);
		if (!valid) {
			res = false;
		}
		return res;
	}
};

Array &Array::sort() {
	_p->array.sort_custom<_ArrayVariantSort>();
	return *this;
}

struct _ArrayVariantSortCustom {
	Object *obj;

	_FORCE_INLINE_ bool operator()(const Variant &p_l, const Variant &p_r) const {
		return obj->lt(p_l, p_r);
	}
};
Array &Array::sort_custom(Object *p_obj) {
	ERR_FAIL_COND_V(!p_obj, *this);

	SortArray<Variant, _ArrayVariantSortCustom, true> avs;
	avs.compare.obj = p_obj;
	avs.sort(_p->array.ptrw(), _p->array.size());
	return *this;
}

void Array::shuffle() {
	const int n = _p->array.size();
	if (n < 2) {
		return;
	}
	Variant *data = _p->array.ptrw();
	for (int i = n - 1; i >= 1; i--) {
		const int j = Math::rand() % (i + 1);
		const Variant tmp = data[j];
		data[j] = data[i];
		data[i] = tmp;
	}
}

template <typename Less>
_FORCE_INLINE_ int bisect(const Vector<Variant> &p_array, const Variant &p_value, bool p_before, const Less &p_less) {
	int lo = 0;
	int hi = p_array.size();
	if (p_before) {
		while (lo < hi) {
			const int mid = (lo + hi) / 2;
			if (p_less(p_array.get(mid), p_value)) {
				lo = mid + 1;
			} else {
				hi = mid;
			}
		}
	} else {
		while (lo < hi) {
			const int mid = (lo + hi) / 2;
			if (p_less(p_value, p_array.get(mid))) {
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}
	}
	return lo;
}

int Array::bsearch(const Variant &p_value, bool p_before) {
	return bisect(_p->array, p_value, p_before, _ArrayVariantSort());
}

int Array::bsearch_custom(const Variant &p_value, Object *p_obj, const StringName &p_function, bool p_before) {
	ERR_FAIL_COND_V(!p_obj, 0);

	_ArrayVariantSortCustom less;
	less.obj = p_obj;

	return bisect(_p->array, p_value, p_before, less);
}

Array &Array::invert() {
	_p->array.invert();
	return *this;
}

void Array::push_front(const Variant &p_value) {
	_p->array.insert(0, p_value);
}

Variant Array::pop_back() {
	if (!_p->array.empty()) {
		const int n = _p->array.size() - 1;
		const Variant ret = _p->array.get(n);
		_p->array.resize(n);
		return ret;
	}
	return Variant();
}

Variant Array::pop_front() {
	if (!_p->array.empty()) {
		const Variant ret = _p->array.get(0);
		_p->array.remove(0);
		return ret;
	}
	return Variant();
}

Variant Array::pop_at(int p_pos) {
	if (_p->array.empty()) {
		// Return `null` without printing an error to mimic `pop_back()` and `pop_front()` behavior.
		return Variant();
	}

	if (p_pos < 0) {
		// Relative offset from the end
		p_pos = _p->array.size() + p_pos;
	}

	ERR_FAIL_INDEX_V_MSG(
			p_pos,
			_p->array.size(),
			Variant(),
			vformat(
					"The calculated index %s is out of bounds (the array has %s elements). Leaving the array untouched and returning `null`.",
					p_pos,
					_p->array.size()));

	const Variant ret = _p->array.get(p_pos);
	_p->array.remove(p_pos);
	return ret;
}

Variant Array::min() const {
	Variant minval;
	for (int i = 0; i < size(); i++) {
		if (i == 0) {
			minval = get(i);
		} else {
			bool valid;
			Variant ret;
			Variant test = get(i);
			Variant::evaluate(Variant::OP_LESS, test, minval, ret, valid);
			if (!valid) {
				return Variant(); //not a valid comparison
			}
			if (bool(ret)) {
				//is less
				minval = test;
			}
		}
	}
	return minval;
}

Variant Array::max() const {
	Variant maxval;
	for (int i = 0; i < size(); i++) {
		if (i == 0) {
			maxval = get(i);
		} else {
			bool valid;
			Variant ret;
			Variant test = get(i);
			Variant::evaluate(Variant::OP_GREATER, test, maxval, ret, valid);
			if (!valid) {
				return Variant(); //not a valid comparison
			}
			if (bool(ret)) {
				//is less
				maxval = test;
			}
		}
	}
	return maxval;
}

const void *Array::id() const {
	return _p;
}

String Array::sprintf(const String &p_format, bool *error) const {
	String formatted;
	CharType *self = (CharType *)p_format.get_data();
	bool in_format = false;
	int value_index = 0;
	int min_chars = 0;
	int min_decimals = 0;
	bool in_decimals = false;
	bool pad_with_zeros = false;
	bool left_justified = false;
	bool show_sign = false;

	const Array &values = *this;

	if (error) {
		*error = true;
	}

	for (; *self; self++) {
		const CharType c = *self;

		if (in_format) { // We have % - let's see what else we get.
			switch (c) {
				case '%': { // Replace %% with %
					formatted += p_format.chr(c);
					in_format = false;
					break;
				}
				case 'd': // Integer (signed)
				case 'o': // Octal
				case 'x': // Hexadecimal (lowercase)
				case 'X': { // Hexadecimal (uppercase)
					if (value_index >= values.size()) {
						return "not enough arguments for format string";
					}

					if (!values[value_index].is_num()) {
						return "a number is required";
					}

					int64_t value = values[value_index];
					int base = 16;
					bool capitalize = false;
					switch (c) {
						case 'd':
							base = 10;
							break;
						case 'o':
							base = 8;
							break;
						case 'x':
							break;
						case 'X':
							base = 16;
							capitalize = true;
							break;
					}
					// Get basic number.
					String str = String::num_int64(ABS(value), base, capitalize);
					int number_len = str.length();

					// Padding.
					int pad_chars_count = (value < 0 || show_sign) ? min_chars - 1 : min_chars;
					String pad_char = pad_with_zeros ? String("0") : String(" ");
					if (left_justified) {
						str = str.rpad(pad_chars_count, pad_char);
					} else {
						str = str.lpad(pad_chars_count, pad_char);
					}

					// Sign.
					if (show_sign || value < 0) {
						String sign_char = value < 0 ? "-" : "+";
						if (left_justified) {
							str = str.insert(0, sign_char);
						} else {
							str = str.insert(pad_with_zeros ? 0 : str.length() - number_len, sign_char);
						}
					}

					formatted += str;
					++value_index;
					in_format = false;

					break;
				}
				case 'f': { // Float
					if (value_index >= values.size()) {
						return "not enough arguments for format string";
					}

					if (!values[value_index].is_num()) {
						return "a number is required";
					}

					double value = values[value_index];
					bool is_negative = (value < 0);
					String str = String::num(ABS(value), min_decimals);
					bool not_numeric = isinf(value) || isnan(value);

					// Pad decimals out.
					if (!not_numeric) {
						str = str.pad_decimals(min_decimals);
					}

					int initial_len = str.length();

					// Padding. Leave room for sign later if required.
					int pad_chars_count = (is_negative || show_sign) ? min_chars - 1 : min_chars;
					String pad_char = (pad_with_zeros && !not_numeric) ? String("0") : String(" "); // Never pad NaN or inf with zeros
					if (left_justified) {
						str = str.rpad(pad_chars_count, pad_char);
					} else {
						str = str.lpad(pad_chars_count, pad_char);
					}

					// Add sign if needed.
					if (show_sign || is_negative) {
						String sign_char = is_negative ? "-" : "+";
						if (left_justified) {
							str = str.insert(0, sign_char);
						} else {
							str = str.insert(pad_with_zeros ? 0 : str.length() - initial_len, sign_char);
						}
					}

					formatted += str;
					++value_index;
					in_format = false;
					break;
				}
				case 's': { // String
					if (value_index >= values.size()) {
						return "not enough arguments for format string";
					}

					String str = values[value_index];
					// Padding.
					if (left_justified) {
						str = str.rpad(min_chars);
					} else {
						str = str.lpad(min_chars);
					}

					formatted += str;
					++value_index;
					in_format = false;
					break;
				}
				case 'c': {
					if (value_index >= values.size()) {
						return "not enough arguments for format string";
					}

					// Convert to character.
					String str;
					if (values[value_index].is_num()) {
						int value = values[value_index];
						if (value < 0) {
							return "unsigned integer is lower than minimum";
						} else if (value >= 0xd800 && value <= 0xdfff) {
							return "unsigned integer is invalid Unicode character";
						} else if (value > 0x10ffff) {
							return "unsigned integer is greater than maximum";
						}
						str = p_format.chr(values[value_index]);
					} else if (values[value_index].get_type() == Variant::STRING) {
						str = values[value_index];
						if (str.length() != 1) {
							return "%c requires number or single-character string";
						}
					} else {
						return "%c requires number or single-character string";
					}

					// Padding.
					if (left_justified) {
						str = str.rpad(min_chars);
					} else {
						str = str.lpad(min_chars);
					}

					formatted += str;
					++value_index;
					in_format = false;
					break;
				}
				case '-': { // Left justify
					left_justified = true;
					break;
				}
				case '+': { // Show + if positive.
					show_sign = true;
					break;
				}
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9': {
					int n = c - '0';
					if (in_decimals) {
						min_decimals *= 10;
						min_decimals += n;
					} else {
						if (c == '0' && min_chars == 0) {
							if (left_justified) {
								LOG_WARN("'0' flag ignored with '-' flag in string format");
							} else {
								pad_with_zeros = true;
							}
						} else {
							min_chars *= 10;
							min_chars += n;
						}
					}
					break;
				}
				case '.': { // Float separator.
					if (in_decimals) {
						return "too many decimal points in format";
					}
					in_decimals = true;
					min_decimals = 0; // We want to add the value manually.
					break;
				}

				case '*': { // Dynamic width, based on value.
					if (value_index >= values.size()) {
						return "not enough arguments for format string";
					}

					if (!values[value_index].is_num()) {
						return "* wants number";
					}

					int size = values[value_index];

					if (in_decimals) {
						min_decimals = size;
					} else {
						min_chars = size;
					}

					++value_index;
					break;
				}

				default: {
					return "unsupported format character";
				}
			}
		} else { // Not in format string.
			switch (c) {
				case '%':
					in_format = true;
					// Back to defaults:
					min_chars = 0;
					min_decimals = 6;
					pad_with_zeros = false;
					left_justified = false;
					show_sign = false;
					in_decimals = false;
					break;
				default:
					formatted += p_format.chr(c);
			}
		}
	}

	if (in_format) {
		return "incomplete format";
	}

	if (value_index != values.size()) {
		return "not all arguments converted during string formatting";
	}

	if (error) {
		*error = false;
	}
	return formatted;
}

Array::Array(const Array &p_from) {
	_p = nullptr;
	_ref(p_from);
}

Array::Array() {
	_p = memnew(ArrayPrivate);
	_p->refcount.init();
}
Array::~Array() {
	_unref();
}
#line 0

#line 1 "sfwl/object/psignal.cpp"



void Signal::connect_static(void (*func)(Signal *)) {
	StaticSignalEntry *se = new StaticSignalEntry();
	se->func = func;

	entries.push_back(se);
}
void Signal::disconnect_static(void (*func)(Signal *)) {
	for (int i = 0; i < entries.size(); ++i) {
		SignalEntry *e = entries[i];

		if (e->type == SIGNAL_ENTRY_TYPE_STATIC) {
			StaticSignalEntry *se = static_cast<StaticSignalEntry *>(e);

			if (se->func == func) {
				entries.remove(i);
				return;
			}
		}
	}
}
bool Signal::is_connected_static(void (*func)(Signal *)) {
	for (int i = 0; i < entries.size(); ++i) {
		SignalEntry *e = entries[i];

		if (e->type == SIGNAL_ENTRY_TYPE_STATIC) {
			StaticSignalEntry *se = static_cast<StaticSignalEntry *>(e);

			if (se->func == func) {
				return true;
			}
		}
	}

	return false;
}

void Signal::emit(Object *p_emitter) {
	emitter = p_emitter;

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}
}

void Signal::emit(Object *p_emitter, const Variant &p1) {
	emitter = p_emitter;

	params.push_back(p1);

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}

	params.clear();
}
void Signal::emit(Object *p_emitter, const Variant &p1, const Variant &p2) {
	emitter = p_emitter;

	params.push_back(p1);
	params.push_back(p2);

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}

	params.clear();
}
void Signal::emit(Object *p_emitter, const Variant &p1, const Variant &p2, const Variant &p3) {
	emitter = p_emitter;

	params.push_back(p1);
	params.push_back(p2);
	params.push_back(p3);

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}

	params.clear();
}

void Signal::emit(Object *p_emitter, const Variant &p1, const Variant &p2, const Variant &p3, const Variant &p4) {
	emitter = p_emitter;

	params.push_back(p1);
	params.push_back(p2);
	params.push_back(p3);
	params.push_back(p4);

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}

	params.clear();
}

void Signal::emit(Object *p_emitter, const Variant &p1, const Variant &p2, const Variant &p3, const Variant &p4, const Variant &p5) {
	emitter = p_emitter;

	params.push_back(p1);
	params.push_back(p2);
	params.push_back(p3);
	params.push_back(p4);
	params.push_back(p5);

	for (int i = 0; i < entries.size(); ++i) {
		entries[i]->call(this);
	}

	params.clear();
}

Signal::Signal() {
}
Signal::~Signal() {
}
#line 0

#line 1 "sfwl/object/variant.cpp"
/*************************************************************************/
/*  variant.cpp                                                          */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



String Variant::get_type_name(Variant::Type p_type) {
	switch (p_type) {
		case NIL: {
			return "Nil";
		} break;

		// atomic types
		case BOOL: {
			return "bool";
		} break;
		case INT: {
			return "int";

		} break;
		case REAL: {
			return "float";

		} break;
		case STRING: {
			return "String";
		} break;

		case OBJECT: {
			return "Object";
		} break;
		case STRING_NAME: {
			return "StringName";
		} break;
		case DICTIONARY: {
			return "Dictionary";
		} break;
		case ARRAY: {
			return "Array";
		} break;

		// arrays
		case POOL_BYTE_ARRAY: {
			return "PoolByteArray";
		} break;
		case POOL_INT_ARRAY: {
			return "PoolIntArray";
		} break;
		case POOL_REAL_ARRAY: {
			return "PoolRealArray";
		} break;
		case POOL_STRING_ARRAY: {
			return "PoolStringArray";
		} break;
		default: {
		}
	}

	return "";
}

bool Variant::can_convert(Variant::Type p_type_from, Variant::Type p_type_to) {
	if (p_type_from == p_type_to) {
		return true;
	}
	if (p_type_to == NIL && p_type_from != NIL) { //nil can convert to anything
		return true;
	}

	if (p_type_from == NIL) {
		return (p_type_to == OBJECT);
	};

	const Type *valid_types = nullptr;
	const Type *invalid_types = nullptr;

	switch (p_type_to) {
		case NIL: {
			//can't
		} break;
		case BOOL: {
			static const Type valid[] = {
				INT,
				REAL,
				STRING,
				NIL,
			};

			valid_types = valid;
		} break;
		case INT: {
			static const Type valid[] = {
				BOOL,
				REAL,
				STRING,
				NIL,
			};

			valid_types = valid;
		} break;
		case REAL: {
			static const Type valid[] = {
				BOOL,
				INT,
				STRING,
				NIL,
			};

			valid_types = valid;
		} break;
		case STRING: {
			static const Type invalid[] = {
				OBJECT,
				NIL
			};

			invalid_types = invalid;
		} break;
		case OBJECT: {
			static const Type valid[] = {
				NIL
			};

			valid_types = valid;
		} break;
		case STRING_NAME: {
			static const Type valid[] = {
				STRING,
				NIL
			};

			valid_types = valid;
		} break;
		case DICTIONARY: {
			//can't
		} break;
		case ARRAY: {
			static const Type valid[] = {
				POOL_BYTE_ARRAY,
				POOL_INT_ARRAY,
				POOL_STRING_ARRAY,
				POOL_REAL_ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		// arrays
		case POOL_BYTE_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		case POOL_INT_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};
			valid_types = valid;
		} break;
		case POOL_REAL_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		case POOL_STRING_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};
			valid_types = valid;
		} break;
		default: {
		}
	}

	if (valid_types) {
		int i = 0;
		while (valid_types[i] != NIL) {
			if (p_type_from == valid_types[i]) {
				return true;
			}
			i++;
		}

	} else if (invalid_types) {
		int i = 0;
		while (invalid_types[i] != NIL) {
			if (p_type_from == invalid_types[i]) {
				return false;
			}
			i++;
		}

		return true;
	}

	return false;
}

bool Variant::can_convert_strict(Variant::Type p_type_from, Variant::Type p_type_to) {
	if (p_type_from == p_type_to) {
		return true;
	}
	if (p_type_to == NIL && p_type_from != NIL) { //nil can convert to anything
		return true;
	}

	if (p_type_from == NIL) {
		return (p_type_to == OBJECT);
	};

	const Type *valid_types = nullptr;

	switch (p_type_to) {
		case NIL: {
			//can't, also already handled
		} break;
		case BOOL: {
			static const Type valid[] = {
				INT,
				REAL,
				//STRING,
				NIL,
			};

			valid_types = valid;
		} break;
		case INT: {
			static const Type valid[] = {
				BOOL,
				REAL,
				//STRING,
				NIL,
			};

			valid_types = valid;

		} break;
		case REAL: {
			static const Type valid[] = {
				BOOL,
				INT,
				//STRING,
				NIL,
			};

			valid_types = valid;

		} break;
		case STRING: {
			static const Type valid[] = {
				STRING_NAME,
				NIL
			};

			valid_types = valid;
		} break;
		case OBJECT: {
			static const Type valid[] = {
				NIL
			};

			valid_types = valid;
		} break;
		case STRING_NAME: {
			static const Type valid[] = {
				STRING,
				NIL
			};

			valid_types = valid;
		} break;
		case DICTIONARY: {
			//Can't
		} break;
		case ARRAY: {
			static const Type valid[] = {
				POOL_BYTE_ARRAY,
				POOL_INT_ARRAY,
				POOL_STRING_ARRAY,
				POOL_REAL_ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		// arrays
		case POOL_BYTE_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		case POOL_INT_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};
			valid_types = valid;
		} break;
		case POOL_REAL_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		case POOL_STRING_ARRAY: {
			static const Type valid[] = {
				ARRAY,
				NIL
			};

			valid_types = valid;
		} break;
		default: {
		}
	}

	if (valid_types) {
		int i = 0;
		while (valid_types[i] != NIL) {
			if (p_type_from == valid_types[i]) {
				return true;
			}
			i++;
		}
	}

	return false;
}

bool Variant::deep_equal(const Variant &p_variant, int p_recursion_count) const {
	ERR_FAIL_COND_V_MSG(p_recursion_count > MAX_RECURSION, true, "Max recursion reached");

	// Containers must be handled with recursivity checks
	switch (type) {
		case Variant::Type::DICTIONARY: {
			if (p_variant.type != Variant::Type::DICTIONARY) {
				return false;
			}

			const Dictionary v1_as_d = Dictionary(*this);
			const Dictionary v2_as_d = Dictionary(p_variant);

			return v1_as_d.deep_equal(v2_as_d, p_recursion_count + 1);
		} break;
		case Variant::Type::ARRAY: {
			if (p_variant.type != Variant::Type::ARRAY) {
				return false;
			}

			const Array v1_as_a = Array(*this);
			const Array v2_as_a = Array(p_variant);

			return v1_as_a.deep_equal(v2_as_a, p_recursion_count + 1);
		} break;
		default: {
			return *this == p_variant;
		} break;
	}
}

bool Variant::operator==(const Variant &p_variant) const {
	if (type != p_variant.type) { //evaluation of operator== needs to be more strict
		return false;
	}
	bool v;
	Variant r;
	evaluate(OP_EQUAL, *this, p_variant, r, v);
	return r;
}

bool Variant::operator!=(const Variant &p_variant) const {
	if (type != p_variant.type) { //evaluation of operator== needs to be more strict
		return true;
	}
	bool v;
	Variant r;
	evaluate(OP_NOT_EQUAL, *this, p_variant, r, v);
	return r;
}

bool Variant::operator<(const Variant &p_variant) const {
	if (type != p_variant.type) { //if types differ, then order by type first
		return type < p_variant.type;
	}
	bool v;
	Variant r;
	evaluate(OP_LESS, *this, p_variant, r, v);
	return r;
}

bool Variant::is_zero() const {
	switch (type) {
		case NIL: {
			return true;
		} break;

		// atomic types
		case BOOL: {
			return !(_data._bool);
		} break;
		case INT: {
			return _data._int == 0;
		} break;
		case REAL: {
			return _data._real == 0;
		} break;
		case STRING: {
			return *reinterpret_cast<const String *>(_data._mem) == String();
		} break;

		case OBJECT: {
			return _UNSAFE_OBJ_PROXY_PTR(*this) == nullptr;
		} break;
		case STRING_NAME: {
			return *reinterpret_cast<const StringName *>(_data._mem) != StringName();
		} break;
		case DICTIONARY: {
			return reinterpret_cast<const Dictionary *>(_data._mem)->empty();
		} break;
		case ARRAY: {
			return reinterpret_cast<const Array *>(_data._mem)->empty();
		} break;

		// arrays
		case POOL_BYTE_ARRAY: {
			return reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem)->size() == 0;
		} break;
		case POOL_INT_ARRAY: {
			return reinterpret_cast<const PoolVector<int> *>(_data._mem)->size() == 0;
		} break;
		case POOL_REAL_ARRAY: {
			return reinterpret_cast<const PoolVector<real_t> *>(_data._mem)->size() == 0;
		} break;
		case POOL_STRING_ARRAY: {
			return reinterpret_cast<const PoolVector<String> *>(_data._mem)->size() == 0;
		} break;
		default: {
		}
	}

	return false;
}

bool Variant::is_one() const {
	switch (type) {
		case NIL: {
			return true;
		} break;

		// atomic types
		case BOOL: {
			return _data._bool;
		} break;
		case INT: {
			return _data._int == 1;
		} break;
		case REAL: {
			return _data._real == 1;
		} break;

		default: {
			return !is_zero();
		}
	}

	return false;
}

ObjectID Variant::get_object_instance_id() const {
	if (unlikely(type != OBJECT)) {
		return 0;
	} else if (likely(_get_obj().rc)) {
		return _get_obj().rc->instance_id;
	} else if (likely(!_get_obj().ref.is_null())) {
		return _REF_OBJ_PTR(*this)->get_instance_id();
	} else {
		return 0;
	}
}

bool Variant::is_invalid_object() const {
	return type == OBJECT && _get_obj().rc && !_get_obj().rc->get_ptr();
}

void Variant::reference(const Variant &p_variant) {
	switch (type) {
		case NIL:
		case BOOL:
		case INT:
		case REAL:
			break;
		default:
			clear();
	}

	type = p_variant.type;

	switch (p_variant.type) {
		case NIL: {
			// none
		} break;

		// atomic types
		case BOOL: {
			_data._bool = p_variant._data._bool;
		} break;
		case INT: {
			_data._int = p_variant._data._int;
		} break;
		case REAL: {
			_data._real = p_variant._data._real;
		} break;
		case STRING: {
			memnew_placement(_data._mem, String(*reinterpret_cast<const String *>(p_variant._data._mem)));
		} break;

		case OBJECT: {
			memnew_placement(_data._mem, ObjData(p_variant._get_obj()));
			if (likely(_get_obj().rc)) {
				_get_obj().rc->increment();
			}
		} break;
		case STRING_NAME: {
			memnew_placement(_data._mem, StringName(*reinterpret_cast<const StringName *>(p_variant._data._mem)));
		} break;
		case DICTIONARY: {
			memnew_placement(_data._mem, Dictionary(*reinterpret_cast<const Dictionary *>(p_variant._data._mem)));
		} break;
		case ARRAY: {
			memnew_placement(_data._mem, Array(*reinterpret_cast<const Array *>(p_variant._data._mem)));
		} break;

		// arrays
		case POOL_BYTE_ARRAY: {
			memnew_placement(_data._mem, PoolVector<uint8_t>(*reinterpret_cast<const PoolVector<uint8_t> *>(p_variant._data._mem)));
		} break;
		case POOL_INT_ARRAY: {
			memnew_placement(_data._mem, PoolVector<int>(*reinterpret_cast<const PoolVector<int> *>(p_variant._data._mem)));
		} break;
		case POOL_REAL_ARRAY: {
			memnew_placement(_data._mem, PoolVector<real_t>(*reinterpret_cast<const PoolVector<real_t> *>(p_variant._data._mem)));
		} break;
		case POOL_STRING_ARRAY: {
			memnew_placement(_data._mem, PoolVector<String>(*reinterpret_cast<const PoolVector<String> *>(p_variant._data._mem)));
		} break;
		default: {
		}
	}
}

void Variant::zero() {
	switch (type) {
		case NIL:
			break;
		case BOOL:
			this->_data._bool = false;
			break;
		case INT:
			this->_data._int = 0;
			break;
		case REAL:
			this->_data._real = 0;
			break;
		default:
			this->clear();
			break;
	}
}

void Variant::clear() {
	switch (type) {
		/*
		// no point, they don't allocate memory
		BOOL,
		INT,
		REAL,
		*/
		case STRING: {
			reinterpret_cast<String *>(_data._mem)->~String();
		} break;

		// misc types
		case OBJECT: {
			if (likely(_get_obj().rc)) {
				if (unlikely(_get_obj().rc->decrement())) {
					memdelete(_get_obj().rc);
				}
			} else {
				_get_obj().ref.unref();
			}
		} break;
		case STRING_NAME: {
			reinterpret_cast<StringName *>(_data._mem)->~StringName();
		} break;
		case DICTIONARY: {
			reinterpret_cast<Dictionary *>(_data._mem)->~Dictionary();
		} break;
		case ARRAY: {
			reinterpret_cast<Array *>(_data._mem)->~Array();
		} break;

		// arrays
		case POOL_BYTE_ARRAY: {
			reinterpret_cast<PoolVector<uint8_t> *>(_data._mem)->~PoolVector<uint8_t>();
		} break;
		case POOL_INT_ARRAY: {
			reinterpret_cast<PoolVector<int> *>(_data._mem)->~PoolVector<int>();
		} break;
		case POOL_REAL_ARRAY: {
			reinterpret_cast<PoolVector<real_t> *>(_data._mem)->~PoolVector<real_t>();
		} break;
		case POOL_STRING_ARRAY: {
			reinterpret_cast<PoolVector<String> *>(_data._mem)->~PoolVector<String>();
		} break;
		default: {
		} /* not needed */
	}

	type = NIL;
}

Variant::operator signed int() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}
Variant::operator unsigned int() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}

Variant::operator int64_t() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int64();
		default: {
			return 0;
		}
	}
}

/*
Variant::operator long unsigned int() const {

	switch( type ) {

		case NIL: return 0;
		case BOOL: return _data._bool ? 1 : 0;
		case INT: return _data._int;
		case REAL: return _data._real;
		case STRING: return operator String().to_int();
		default: {

			return 0;
		}
	}

	return 0;
};
*/

Variant::operator uint64_t() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}

#ifdef NEED_LONG_INT
Variant::operator signed long() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}

	return 0;
};

Variant::operator unsigned long() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}

	return 0;
};
#endif

Variant::operator signed short() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}
Variant::operator unsigned short() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}
Variant::operator signed char() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}
Variant::operator unsigned char() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1 : 0;
		case INT:
			return _data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_int();
		default: {
			return 0;
		}
	}
}

Variant::operator CharType() const {
	return operator unsigned int();
}

Variant::operator float() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1.0 : 0.0;
		case INT:
			return (float)_data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_double();
		default: {
			return 0;
		}
	}
}
Variant::operator double() const {
	switch (type) {
		case NIL:
			return 0;
		case BOOL:
			return _data._bool ? 1.0 : 0.0;
		case INT:
			return (double)_data._int;
		case REAL:
			return _data._real;
		case STRING:
			return operator String().to_double();
		default: {
			return 0;
		}
	}
}

Variant::operator StringName() const {
	if (type == STRING_NAME) {
		return *reinterpret_cast<const StringName *>(_data._mem);
	}

	return StringName(operator String());
}

struct _VariantStrPair {
	String key;
	String value;

	bool operator<(const _VariantStrPair &p) const {
		return key < p.key;
	}
};

Variant::operator String() const {
	List<const void *> stack;

	return stringify(stack);
}

template <class T>
String stringify_vector(const T &vec, List<const void *> &stack) {
	String str("[");
	for (int i = 0; i < vec.size(); i++) {
		if (i > 0) {
			str += ", ";
		}
		str = str + Variant(vec[i]).stringify(stack);
	}
	str += "]";
	return str;
}

String Variant::stringify(List<const void *> &stack) const {
	switch (type) {
		case NIL:
			return "Null";
		case BOOL:
			return _data._bool ? "True" : "False";
		case INT:
			return itos(_data._int);
		case REAL:
			return rtos(_data._real);
		case STRING:
			return *reinterpret_cast<const String *>(_data._mem);
		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (likely(obj)) {
				return obj->to_string();
			} else {
				if (_get_obj().rc) {
					return "[Deleted Object]";
				}
				return "[Object:null]";
			}
		} break;
		case STRING_NAME:
			return operator StringName();
		case DICTIONARY: {
			const Dictionary &d = *reinterpret_cast<const Dictionary *>(_data._mem);
			if (stack.find(d.id())) {
				return "{...}";
			}

			stack.push_back(d.id());

			//const String *K=NULL;
			String str("{");
			List<Variant> keys;
			d.get_key_list(&keys);

			Vector<_VariantStrPair> pairs;

			for (List<Variant>::Element *E = keys.front(); E; E = E->next()) {
				_VariantStrPair sp;
				sp.key = E->get().stringify(stack);
				sp.value = d[E->get()].stringify(stack);

				pairs.push_back(sp);
			}

			pairs.sort();

			for (int i = 0; i < pairs.size(); i++) {
				if (i > 0) {
					str += ", ";
				}
				str += pairs[i].key + ":" + pairs[i].value;
			}
			str += "}";

			stack.erase(d.id());
			return str;
		} break;
		case ARRAY: {
			Array arr = operator Array();
			if (stack.find(arr.id())) {
				return "[...]";
			}
			stack.push_back(arr.id());
			String str = stringify_vector(arr, stack);
			stack.erase(arr.id());
			return str;

		} break;

		case POOL_BYTE_ARRAY: {
			return stringify_vector(operator PoolVector<uint8_t>(), stack);
		} break;
		case POOL_INT_ARRAY: {
			return stringify_vector(operator PoolVector<int>(), stack);
		} break;
		case POOL_REAL_ARRAY: {
			return stringify_vector(operator PoolVector<real_t>(), stack);
		} break;
		case POOL_STRING_ARRAY: {
			return stringify_vector(operator PoolVector<String>(), stack);
		} break;

		default: {
			return "[" + get_type_name(type) + "]";
		}
	}

	return "";
}

Variant::operator RefPtr() const {
	if (type == OBJECT) {
		return _get_obj().ref;
	} else {
		return RefPtr();
	}
}

Variant::operator Object *() const {
	if (type == OBJECT) {
		return _OBJ_PTR(*this);
	} else {
		return nullptr;
	}
}

template <class DA, class SA>
inline DA _convert_array(const SA &p_array) {
	DA da;
	da.resize(p_array.size());

	for (int i = 0; i < p_array.size(); i++) {
		da.set(i, Variant(p_array.get(i)));
	}

	return da;
}

template <class DA>
inline DA _convert_array_from_variant(const Variant &p_variant) {
	switch (p_variant.get_type()) {
		case Variant::ARRAY: {
			return _convert_array<DA, Array>(p_variant.operator Array());
		}
		case Variant::POOL_BYTE_ARRAY: {
			return _convert_array<DA, PoolVector<uint8_t>>(p_variant.operator PoolVector<uint8_t>());
		}
		case Variant::POOL_INT_ARRAY: {
			return _convert_array<DA, PoolVector<int>>(p_variant.operator PoolVector<int>());
		}
		case Variant::POOL_REAL_ARRAY: {
			return _convert_array<DA, PoolVector<real_t>>(p_variant.operator PoolVector<real_t>());
		}
		case Variant::POOL_STRING_ARRAY: {
			return _convert_array<DA, PoolVector<String>>(p_variant.operator PoolVector<String>());
		}
		default: {
			return DA();
		}
	}
}

Variant::operator Dictionary() const {
	if (type == DICTIONARY) {
		return *reinterpret_cast<const Dictionary *>(_data._mem);
	} else {
		return Dictionary();
	}
}

Variant::operator Array() const {
	if (type == ARRAY) {
		return *reinterpret_cast<const Array *>(_data._mem);
	} else {
		return _convert_array_from_variant<Array>(*this);
	}
}

Variant::operator PoolVector<uint8_t>() const {
	if (type == POOL_BYTE_ARRAY) {
		return *reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
	} else {
		return _convert_array_from_variant<PoolVector<uint8_t>>(*this);
	}
}
Variant::operator PoolVector<int>() const {
	if (type == POOL_INT_ARRAY) {
		return *reinterpret_cast<const PoolVector<int> *>(_data._mem);
	} else {
		return _convert_array_from_variant<PoolVector<int>>(*this);
	}
}
Variant::operator PoolVector<real_t>() const {
	if (type == POOL_REAL_ARRAY) {
		return *reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
	} else {
		return _convert_array_from_variant<PoolVector<real_t>>(*this);
	}
}

Variant::operator PoolVector<String>() const {
	if (type == POOL_STRING_ARRAY) {
		return *reinterpret_cast<const PoolVector<String> *>(_data._mem);
	} else {
		return _convert_array_from_variant<PoolVector<String>>(*this);
	}
}

/* helpers */

Variant::operator Vector<Variant>() const {
	Array from = operator Array();
	Vector<Variant> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}

Variant::operator Vector<uint8_t>() const {
	PoolVector<uint8_t> from = operator PoolVector<uint8_t>();
	Vector<uint8_t> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}
Variant::operator Vector<int>() const {
	PoolVector<int> from = operator PoolVector<int>();
	Vector<int> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}
Variant::operator Vector<real_t>() const {
	PoolVector<real_t> from = operator PoolVector<real_t>();
	Vector<real_t> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}

Variant::operator Vector<String>() const {
	PoolVector<String> from = operator PoolVector<String>();
	Vector<String> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}
Variant::operator Vector<StringName>() const {
	PoolVector<String> from = operator PoolVector<String>();
	Vector<StringName> to;
	int len = from.size();
	to.resize(len);
	for (int i = 0; i < len; i++) {
		to.write[i] = from[i];
	}
	return to;
}

Variant::operator Margin() const {
	return (Margin) operator int();
}
Variant::operator Side() const {
	return (Side) operator int();
}
Variant::operator Orientation() const {
	return (Orientation) operator int();
}

Variant::Variant(bool p_bool) {
	type = BOOL;
	_data._bool = p_bool;
}

/*
Variant::Variant(long unsigned int p_long) {

	type=INT;
	_data._int=p_long;
};
*/

Variant::Variant(signed int p_int) {
	type = INT;
	_data._int = p_int;
}
Variant::Variant(unsigned int p_int) {
	type = INT;
	_data._int = p_int;
}

#ifdef NEED_LONG_INT

Variant::Variant(signed long p_int) {
	type = INT;
	_data._int = p_int;
}
Variant::Variant(unsigned long p_int) {
	type = INT;
	_data._int = p_int;
}
#endif

Variant::Variant(int64_t p_int) {
	type = INT;
	_data._int = p_int;
}

Variant::Variant(uint64_t p_int) {
	type = INT;
	_data._int = p_int;
}

Variant::Variant(signed short p_short) {
	type = INT;
	_data._int = p_short;
}
Variant::Variant(unsigned short p_short) {
	type = INT;
	_data._int = p_short;
}
Variant::Variant(signed char p_char) {
	type = INT;
	_data._int = p_char;
}
Variant::Variant(unsigned char p_char) {
	type = INT;
	_data._int = p_char;
}
Variant::Variant(float p_float) {
	type = REAL;
	_data._real = p_float;
}
Variant::Variant(double p_double) {
	type = REAL;
	_data._real = p_double;
}

Variant::Variant(const StringName &p_string) {
	type = STRING_NAME;
	memnew_placement(_data._mem, StringName(p_string));
}
Variant::Variant(const String &p_string) {
	type = STRING;
	memnew_placement(_data._mem, String(p_string));
}

Variant::Variant(const char *const p_cstring) {
	type = STRING;
	memnew_placement(_data._mem, String((const char *)p_cstring));
}

Variant::Variant(const CharType *p_wstring) {
	type = STRING;
	memnew_placement(_data._mem, String(p_wstring));
}

Variant::Variant(const RefPtr &p_resource) {
	type = OBJECT;
	memnew_placement(_data._mem, ObjData);
	_get_obj().rc = nullptr;
	_get_obj().ref = p_resource;
}

Variant::Variant(const Object *p_object) {
	type = OBJECT;
	Object *obj = const_cast<Object *>(p_object);

	memnew_placement(_data._mem, ObjData);
	Reference *ref = Object::cast_to<Reference>(obj);
	if (unlikely(ref)) {
		*reinterpret_cast<Ref<Reference> *>(_get_obj().ref.get_data()) = Ref<Reference>(ref);
		_get_obj().rc = nullptr;
	} else {
		_get_obj().rc = likely(obj) ? obj->_use_rc() : nullptr;
	}
}

Variant::Variant(const Dictionary &p_dictionary) {
	type = DICTIONARY;
	memnew_placement(_data._mem, Dictionary(p_dictionary));
}

Variant::Variant(const Array &p_array) {
	type = ARRAY;
	memnew_placement(_data._mem, Array(p_array));
}

Variant::Variant(const PoolVector<uint8_t> &p_raw_array) {
	type = POOL_BYTE_ARRAY;
	memnew_placement(_data._mem, PoolVector<uint8_t>(p_raw_array));
}
Variant::Variant(const PoolVector<int> &p_int_array) {
	type = POOL_INT_ARRAY;
	memnew_placement(_data._mem, PoolVector<int>(p_int_array));
}
Variant::Variant(const PoolVector<real_t> &p_real_array) {
	type = POOL_REAL_ARRAY;
	memnew_placement(_data._mem, PoolVector<real_t>(p_real_array));
}
Variant::Variant(const PoolVector<String> &p_string_array) {
	type = POOL_STRING_ARRAY;
	memnew_placement(_data._mem, PoolVector<String>(p_string_array));
}

/* helpers */

Variant::Variant(const Vector<Variant> &p_array) {
	type = NIL;
	Array v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

Variant::Variant(const Vector<uint8_t> &p_array) {
	type = NIL;
	PoolVector<uint8_t> v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

Variant::Variant(const Vector<int> &p_array) {
	type = NIL;
	PoolVector<int> v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

Variant::Variant(const Vector<real_t> &p_array) {
	type = NIL;
	PoolVector<real_t> v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

Variant::Variant(const Vector<String> &p_array) {
	type = NIL;
	PoolVector<String> v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

Variant::Variant(const Vector<StringName> &p_array) {
	type = NIL;
	PoolVector<String> v;
	int len = p_array.size();
	v.resize(len);
	for (int i = 0; i < len; i++) {
		v.set(i, p_array[i]);
	}
	*this = v;
}

void Variant::operator=(const Variant &p_variant) {
	if (unlikely(this == &p_variant)) {
		return;
	}

	if (unlikely(type != p_variant.type)) {
		reference(p_variant);
		return;
	}

	switch (p_variant.type) {
		case NIL: {
			// none
		} break;

		// atomic types
		case BOOL: {
			_data._bool = p_variant._data._bool;
		} break;
		case INT: {
			_data._int = p_variant._data._int;
		} break;
		case REAL: {
			_data._real = p_variant._data._real;
		} break;
		case STRING: {
			*reinterpret_cast<String *>(_data._mem) = *reinterpret_cast<const String *>(p_variant._data._mem);
		} break;
		case OBJECT: {
			if (likely(_get_obj().rc)) {
				if (unlikely(_get_obj().rc->decrement())) {
					memdelete(_get_obj().rc);
				}
			}
			*reinterpret_cast<ObjData *>(_data._mem) = p_variant._get_obj();
			if (likely(_get_obj().rc)) {
				_get_obj().rc->increment();
			}
		} break;
		case STRING_NAME: {
			*reinterpret_cast<StringName *>(_data._mem) = *reinterpret_cast<const StringName *>(p_variant._data._mem);
		} break;
		case DICTIONARY: {
			*reinterpret_cast<Dictionary *>(_data._mem) = *reinterpret_cast<const Dictionary *>(p_variant._data._mem);
		} break;
		case ARRAY: {
			*reinterpret_cast<Array *>(_data._mem) = *reinterpret_cast<const Array *>(p_variant._data._mem);
		} break;

		// arrays
		case POOL_BYTE_ARRAY: {
			*reinterpret_cast<PoolVector<uint8_t> *>(_data._mem) = *reinterpret_cast<const PoolVector<uint8_t> *>(p_variant._data._mem);
		} break;
		case POOL_INT_ARRAY: {
			*reinterpret_cast<PoolVector<int> *>(_data._mem) = *reinterpret_cast<const PoolVector<int> *>(p_variant._data._mem);
		} break;
		case POOL_REAL_ARRAY: {
			*reinterpret_cast<PoolVector<real_t> *>(_data._mem) = *reinterpret_cast<const PoolVector<real_t> *>(p_variant._data._mem);
		} break;
		case POOL_STRING_ARRAY: {
			*reinterpret_cast<PoolVector<String> *>(_data._mem) = *reinterpret_cast<const PoolVector<String> *>(p_variant._data._mem);
		} break;
		default: {
		}
	}
}

Variant::Variant(const Variant &p_variant) {
	type = NIL;
	reference(p_variant);
}

/*
Variant::~Variant() {

	clear();
}*/

uint32_t Variant::hash() const {
	return recursive_hash(0);
}

uint32_t Variant::recursive_hash(int p_recursion_count) const {
	switch (type) {
		case NIL: {
			return 0;
		} break;

		case BOOL: {
			return _data._bool ? 1 : 0;
		} break;
		case INT: {
			return hash_one_uint64((uint64_t)_data._int);
		} break;
		case REAL: {
			return hash_murmur3_one_float(_data._real);
		} break;
		case STRING: {
			return reinterpret_cast<const String *>(_data._mem)->hash();
		} break;
		case OBJECT: {
			return hash_one_uint64(hash_make_uint64_t(_UNSAFE_OBJ_PROXY_PTR(*this)));
		} break;
		case STRING_NAME: {
			return reinterpret_cast<const StringName *>(_data._mem)->hash();
		} break;
		case DICTIONARY: {
			return reinterpret_cast<const Dictionary *>(_data._mem)->recursive_hash(p_recursion_count);
		} break;
		case ARRAY: {
			const Array &arr = *reinterpret_cast<const Array *>(_data._mem);
			return arr.recursive_hash(p_recursion_count);
		} break;

		case POOL_BYTE_ARRAY: {
			const PoolVector<uint8_t> &arr = *reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
			int len = arr.size();
			if (likely(len)) {
				PoolVector<uint8_t>::Read r = arr.read();
				return hash_murmur3_buffer((uint8_t *)&r[0], len);
			} else {
				return hash_murmur3_one_64(0);
			}

		} break;
		case POOL_INT_ARRAY: {
			const PoolVector<int> &arr = *reinterpret_cast<const PoolVector<int> *>(_data._mem);
			int len = arr.size();
			if (likely(len)) {
				PoolVector<int>::Read r = arr.read();
				return hash_murmur3_buffer((uint8_t *)&r[0], len * sizeof(int));
			} else {
				return hash_murmur3_one_64(0);
			}

		} break;
		case POOL_REAL_ARRAY: {
			const PoolVector<real_t> &arr = *reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
			int len = arr.size();

			if (likely(len)) {
				PoolVector<real_t>::Read r = arr.read();
				uint32_t h = HASH_MURMUR3_SEED;

				for (int i = 0; i < len; i++) {
					h = hash_murmur3_one_real(r[i], h);
				}

				return hash_fmix32(h);
			} else {
				return hash_murmur3_one_real(0.0);
			}

		} break;
		case POOL_STRING_ARRAY: {
			uint32_t hash = HASH_MURMUR3_SEED;
			const PoolVector<String> &arr = *reinterpret_cast<const PoolVector<String> *>(_data._mem);
			int len = arr.size();

			if (likely(len)) {
				PoolVector<String>::Read r = arr.read();

				for (int i = 0; i < len; i++) {
					hash = hash_murmur3_one_32(r[i].hash(), hash);
				}

				hash = hash_fmix32(hash);
			}

			return hash;
		} break;
		default: {
		}
	}

	return 0;
}

#define hash_compare_scalar(p_lhs, p_rhs) \
	(((p_lhs) == (p_rhs)) || (Math::is_nan(p_lhs) && Math::is_nan(p_rhs)))

#define hash_compare_vector2(p_lhs, p_rhs)        \
	(hash_compare_scalar((p_lhs).x, (p_rhs).x) && \
			hash_compare_scalar((p_lhs).y, (p_rhs).y))

#define hash_compare_vector2i(p_lhs, p_rhs) \
	(((p_lhs).x == (p_rhs).x) &&            \
			((p_lhs).y == (p_rhs).y))

#define hash_compare_vector3(p_lhs, p_rhs)               \
	(hash_compare_scalar((p_lhs).x, (p_rhs).x) &&        \
			hash_compare_scalar((p_lhs).y, (p_rhs).y) && \
			hash_compare_scalar((p_lhs).z, (p_rhs).z))

#define hash_compare_vector3i(p_lhs, p_rhs) \
	(((p_lhs).x == (p_rhs).x) &&            \
			((p_lhs).y == (p_rhs).y) &&     \
			((p_lhs).z == (p_rhs).z))

#define hash_compare_vector4(p_lhs, p_rhs)               \
	(hash_compare_scalar((p_lhs).x, (p_rhs).x) &&        \
			hash_compare_scalar((p_lhs).y, (p_rhs).y) && \
			hash_compare_scalar((p_lhs).z, (p_rhs).z) && \
			hash_compare_scalar((p_lhs).w, (p_rhs).w))

#define hash_compare_vector4i(p_lhs, p_rhs) \
	(((p_lhs).x == (p_rhs).x) &&            \
			((p_lhs).y == (p_rhs).y) &&     \
			((p_lhs).z == (p_rhs).z) &&     \
			((p_lhs).w == (p_rhs).w))

#define hash_compare_quat(p_lhs, p_rhs)                  \
	(hash_compare_scalar((p_lhs).x, (p_rhs).x) &&        \
			hash_compare_scalar((p_lhs).y, (p_rhs).y) && \
			hash_compare_scalar((p_lhs).z, (p_rhs).z) && \
			hash_compare_scalar((p_lhs).w, (p_rhs).w))

#define hash_compare_color(p_lhs, p_rhs)                 \
	(hash_compare_scalar((p_lhs).r, (p_rhs).r) &&        \
			hash_compare_scalar((p_lhs).g, (p_rhs).g) && \
			hash_compare_scalar((p_lhs).b, (p_rhs).b) && \
			hash_compare_scalar((p_lhs).a, (p_rhs).a))

#define hash_compare_pool_array(p_lhs, p_rhs, p_type, p_compare_func)                   \
	const PoolVector<p_type> &l = *reinterpret_cast<const PoolVector<p_type> *>(p_lhs); \
	const PoolVector<p_type> &r = *reinterpret_cast<const PoolVector<p_type> *>(p_rhs); \
                                                                                        \
	if (l.size() != r.size())                                                           \
		return false;                                                                   \
                                                                                        \
	PoolVector<p_type>::Read lr = l.read();                                             \
	PoolVector<p_type>::Read rr = r.read();                                             \
                                                                                        \
	for (int i = 0; i < l.size(); ++i) {                                                \
		if (!p_compare_func((lr[i]), (rr[i])))                                          \
			return false;                                                               \
	}                                                                                   \
                                                                                        \
	return true

bool Variant::hash_compare(const Variant &p_variant) const {
	if (type != p_variant.type) {
		return false;
	}

	switch (type) {
		//BOOL
		case INT: {
			return _data._int == p_variant._data._int;
		} break;
		case REAL: {
			return hash_compare_scalar(_data._real, p_variant._data._real);
		} break;
		case STRING: {
			return *reinterpret_cast<const String *>(_data._mem) == *reinterpret_cast<const String *>(p_variant._data._mem);
		} break;
		case ARRAY: {
			const Array &l = *(reinterpret_cast<const Array *>(_data._mem));
			const Array &r = *(reinterpret_cast<const Array *>(p_variant._data._mem));

			if (l.size() != r.size()) {
				return false;
			}

			for (int i = 0; i < l.size(); ++i) {
				if (!l[i].hash_compare(r[i])) {
					return false;
				}
			}

			return true;
		} break;

		case POOL_REAL_ARRAY: {
			hash_compare_pool_array(_data._mem, p_variant._data._mem, real_t, hash_compare_scalar);
		} break;
		default:
			bool v;
			Variant r;
			evaluate(OP_EQUAL, *this, p_variant, r, v);
			return r;
	}

	return false;
}

bool Variant::is_ref() const {
	return type == OBJECT && !_get_obj().ref.is_null();
}

Vector<Variant> varray() {
	return Vector<Variant>();
}

Vector<Variant> varray(const Variant &p_arg1) {
	Vector<Variant> v;
	v.push_back(p_arg1);
	return v;
}
Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2) {
	Vector<Variant> v;
	v.push_back(p_arg1);
	v.push_back(p_arg2);
	return v;
}
Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2, const Variant &p_arg3) {
	Vector<Variant> v;
	v.push_back(p_arg1);
	v.push_back(p_arg2);
	v.push_back(p_arg3);
	return v;
}
Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2, const Variant &p_arg3, const Variant &p_arg4) {
	Vector<Variant> v;
	v.push_back(p_arg1);
	v.push_back(p_arg2);
	v.push_back(p_arg3);
	v.push_back(p_arg4);
	return v;
}

Vector<Variant> varray(const Variant &p_arg1, const Variant &p_arg2, const Variant &p_arg3, const Variant &p_arg4, const Variant &p_arg5) {
	Vector<Variant> v;
	v.push_back(p_arg1);
	v.push_back(p_arg2);
	v.push_back(p_arg3);
	v.push_back(p_arg4);
	v.push_back(p_arg5);
	return v;
}

bool Variant::is_shared() const {
	switch (type) {
		case OBJECT:
			return true;
		case ARRAY:
			return true;
		case DICTIONARY:
			return true;
		default: {
		}
	}

	return false;
}

String vformat(const String &p_text, const Variant &p1, const Variant &p2, const Variant &p3, const Variant &p4, const Variant &p5) {
	Array args;
	if (p1.get_type() != Variant::NIL) {
		args.push_back(p1);

		if (p2.get_type() != Variant::NIL) {
			args.push_back(p2);

			if (p3.get_type() != Variant::NIL) {
				args.push_back(p3);

				if (p4.get_type() != Variant::NIL) {
					args.push_back(p4);

					if (p5.get_type() != Variant::NIL) {
						args.push_back(p5);
					}
				}
			}
		}
	}

	bool error = false;
	String fmt = args.sprintf(p_text, &error);

	ERR_FAIL_COND_V_MSG(error, String(), fmt);

	return fmt;
}
#line 0

#line 1 "sfwl/object/variant_op.cpp"
/*************************************************************************/
/*  variant_op.cpp                                                       */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/



#define CASE_TYPE_ALL(PREFIX, OP) \
	CASE_TYPE(PREFIX, OP, INT)    \
	CASE_TYPE_ALL_BUT_INT(PREFIX, OP)

#define CASE_TYPE_ALL_BUT_INT(PREFIX, OP)      \
	CASE_TYPE(PREFIX, OP, NIL)                 \
	CASE_TYPE(PREFIX, OP, BOOL)                \
	CASE_TYPE(PREFIX, OP, REAL)                \
	CASE_TYPE(PREFIX, OP, STRING)              \
	CASE_TYPE(PREFIX, OP, OBJECT)              \
	CASE_TYPE(PREFIX, OP, STRING_NAME)         \
	CASE_TYPE(PREFIX, OP, DICTIONARY)          \
	CASE_TYPE(PREFIX, OP, ARRAY)               \
	CASE_TYPE(PREFIX, OP, POOL_BYTE_ARRAY)     \
	CASE_TYPE(PREFIX, OP, POOL_INT_ARRAY)      \
	CASE_TYPE(PREFIX, OP, POOL_REAL_ARRAY)     \
	CASE_TYPE(PREFIX, OP, POOL_STRING_ARRAY)   

#ifdef __GNUC__
#define TYPE(PREFIX, OP, TYPE) &&PREFIX##_##OP##_##TYPE

/* clang-format off */

#define TYPES(PREFIX, OP) {                    \
		TYPE(PREFIX, OP, NIL),                 \
		TYPE(PREFIX, OP, BOOL),                \
		TYPE(PREFIX, OP, INT),                 \
		TYPE(PREFIX, OP, REAL),                \
		TYPE(PREFIX, OP, STRING),              \
		TYPE(PREFIX, OP, OBJECT),              \
		TYPE(PREFIX, OP, STRING_NAME),         \
		TYPE(PREFIX, OP, DICTIONARY),          \
		TYPE(PREFIX, OP, ARRAY),               \
		TYPE(PREFIX, OP, POOL_BYTE_ARRAY),     \
		TYPE(PREFIX, OP, POOL_INT_ARRAY),      \
		TYPE(PREFIX, OP, POOL_REAL_ARRAY),     \
		TYPE(PREFIX, OP, POOL_STRING_ARRAY),   \
}

/* clang-format on */

#define CASES(PREFIX) static const void *switch_table_##PREFIX[25][38] = { \
	TYPES(PREFIX, OP_EQUAL),                                               \
	TYPES(PREFIX, OP_NOT_EQUAL),                                           \
	TYPES(PREFIX, OP_LESS),                                                \
	TYPES(PREFIX, OP_LESS_EQUAL),                                          \
	TYPES(PREFIX, OP_GREATER),                                             \
	TYPES(PREFIX, OP_GREATER_EQUAL),                                       \
	TYPES(PREFIX, OP_ADD),                                                 \
	TYPES(PREFIX, OP_SUBTRACT),                                            \
	TYPES(PREFIX, OP_MULTIPLY),                                            \
	TYPES(PREFIX, OP_DIVIDE),                                              \
	TYPES(PREFIX, OP_NEGATE),                                              \
	TYPES(PREFIX, OP_POSITIVE),                                            \
	TYPES(PREFIX, OP_MODULE),                                              \
	TYPES(PREFIX, OP_STRING_CONCAT),                                       \
	TYPES(PREFIX, OP_SHIFT_LEFT),                                          \
	TYPES(PREFIX, OP_SHIFT_RIGHT),                                         \
	TYPES(PREFIX, OP_BIT_AND),                                             \
	TYPES(PREFIX, OP_BIT_OR),                                              \
	TYPES(PREFIX, OP_BIT_XOR),                                             \
	TYPES(PREFIX, OP_BIT_NEGATE),                                          \
	TYPES(PREFIX, OP_AND),                                                 \
	TYPES(PREFIX, OP_OR),                                                  \
	TYPES(PREFIX, OP_XOR),                                                 \
	TYPES(PREFIX, OP_NOT),                                                 \
	TYPES(PREFIX, OP_IN),                                                  \
}

#define SWITCH(PREFIX, op, val) goto *switch_table_##PREFIX[op][val];
#define SWITCH_OP(PREFIX, OP, val)
#define CASE_TYPE(PREFIX, OP, TYPE) PREFIX##_##OP##_##TYPE:

#else
#define CASES(PREFIX)
#define SWITCH(PREFIX, op, val) switch (op)
#define SWITCH_OP(PREFIX, OP, val) \
	case OP:                       \
		switch (val)
#define CASE_TYPE(PREFIX, OP, TYPE) case TYPE:
#endif

Variant::operator bool() const {
	return booleanize();
}

// We consider all uninitialized or empty types to be false based on the type's
// zeroiness.
bool Variant::booleanize() const {
	return !is_zero();
}

#define _RETURN(m_what) \
	{                   \
		r_ret = m_what; \
		return;         \
	}

#define _RETURN_FAIL     \
	{                    \
		r_valid = false; \
		return;          \
	}

#define DEFAULT_OP_NUM(m_prefix, m_op_name, m_name, m_op, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                      \
		if (p_b.type == INT)                                      \
			_RETURN(p_a._data.m_type m_op p_b._data._int);        \
		if (p_b.type == REAL)                                     \
			_RETURN(p_a._data.m_type m_op p_b._data._real);       \
                                                                  \
		_RETURN_FAIL                                              \
	};

#define DEFAULT_OP_NUM_NULL(m_prefix, m_op_name, m_name, m_op, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                           \
		if (p_b.type == INT)                                           \
			_RETURN(p_a._data.m_type m_op p_b._data._int);             \
		if (p_b.type == REAL)                                          \
			_RETURN(p_a._data.m_type m_op p_b._data._real);            \
		if (p_b.type == NIL)                                           \
			_RETURN(!(p_b.type m_op NIL));                             \
                                                                       \
		_RETURN_FAIL                                                   \
	};

#ifdef DEBUG_ENABLED
#define DEFAULT_OP_NUM_DIV(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                    \
		if (p_b.type == INT) {                                  \
			if (p_b._data._int == 0) {                          \
				r_valid = false;                                \
				_RETURN("Division By Zero");                    \
			}                                                   \
			_RETURN(p_a._data.m_type / p_b._data._int);         \
		}                                                       \
		if (p_b.type == REAL) {                                 \
			if (p_b._data._real == 0) {                         \
				r_valid = false;                                \
				_RETURN("Division By Zero");                    \
			}                                                   \
			_RETURN(p_a._data.m_type / p_b._data._real);        \
		}                                                       \
                                                                \
		_RETURN_FAIL                                            \
	};
#else
#define DEFAULT_OP_NUM_DIV(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                    \
		if (p_b.type == INT)                                    \
			_RETURN(p_a._data.m_type / p_b._data._int);         \
		if (p_b.type == REAL)                                   \
			_RETURN(p_a._data.m_type / p_b._data._real);        \
                                                                \
		_RETURN_FAIL                                            \
	};
#endif

#define DEFAULT_OP_NUM_NEG(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                    \
		_RETURN(-p_a._data.m_type);                             \
	};

#define DEFAULT_OP_NUM_POS(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                    \
		_RETURN(p_a._data.m_type);                              \
	};

#define DEFAULT_OP_NUM_VEC(m_prefix, m_op_name, m_name, m_op, m_type)                           \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                    \
		if (p_b.type == INT)                                                                    \
			_RETURN(p_a._data.m_type m_op p_b._data._int);                                      \
		if (p_b.type == REAL)                                                                   \
			_RETURN(p_a._data.m_type m_op p_b._data._real);                                     \
                                                                                                \
		_RETURN_FAIL                                                                            \
	};

#define DEFAULT_OP_STR_REV(m_prefix, m_op_name, m_name, m_op, m_type)                                                              \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                       \
		if (p_b.type == STRING)                                                                                                    \
			_RETURN(*reinterpret_cast<const m_type *>(p_b._data._mem) m_op *reinterpret_cast<const String *>(p_a._data._mem));     \
		if (p_b.type == STRING_NAME)                                                                                               \
			_RETURN(*reinterpret_cast<const m_type *>(p_b._data._mem) m_op *reinterpret_cast<const StringName *>(p_a._data._mem)); \
                                                                                                                                   \
		_RETURN_FAIL                                                                                                               \
	};

#define DEFAULT_OP_STR(m_prefix, m_op_name, m_name, m_op, m_type)                                                                  \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                       \
		if (p_b.type == STRING)                                                                                                    \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const String *>(p_b._data._mem));     \
		if (p_b.type == STRING_NAME)                                                                                               \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const StringName *>(p_b._data._mem)); \
                                                                                                                                   \
		_RETURN_FAIL                                                                                                               \
	};

#define DEFAULT_OP_STR_NULL(m_prefix, m_op_name, m_name, m_op, m_type)                                                             \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                       \
		if (p_b.type == STRING)                                                                                                    \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const String *>(p_b._data._mem));     \
		if (p_b.type == STRING_NAME)                                                                                               \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const StringName *>(p_b._data._mem)); \
		if (p_b.type == NIL)                                                                                                       \
			_RETURN(!(p_b.type m_op NIL));                                                                                         \
                                                                                                                                   \
		_RETURN_FAIL                                                                                                               \
	};

#define DEFAULT_OP_STR_NULL_NP(m_prefix, m_op_name, m_name, m_op, m_type)                                                      \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                   \
		if (p_b.type == STRING)                                                                                                \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const String *>(p_b._data._mem)); \
		if (p_b.type == NIL)                                                                                                   \
			_RETURN(!(p_b.type m_op NIL));                                                                                     \
                                                                                                                               \
		_RETURN_FAIL                                                                                                           \
	};

#define DEFAULT_OP_STR_NULL_SN(m_prefix, m_op_name, m_name, m_op, m_type)                                                          \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                       \
		if (p_b.type == STRING)                                                                                                    \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const String *>(p_b._data._mem));     \
		if (p_b.type == STRING_NAME)                                                                                               \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const StringName *>(p_b._data._mem)); \
		if (p_b.type == NIL)                                                                                                       \
			_RETURN(!(p_b.type m_op NIL));                                                                                         \
                                                                                                                                   \
		_RETURN_FAIL                                                                                                               \
	};

#define DEFAULT_OP_LOCALMEM_REV(m_prefix, m_op_name, m_name, m_op, m_type)                                                     \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                   \
		if (p_b.type == m_name)                                                                                                \
			_RETURN(*reinterpret_cast<const m_type *>(p_b._data._mem) m_op *reinterpret_cast<const m_type *>(p_a._data._mem)); \
                                                                                                                               \
		_RETURN_FAIL                                                                                                           \
	};

#define DEFAULT_OP_LOCALMEM(m_prefix, m_op_name, m_name, m_op, m_type)                                                         \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                   \
		if (p_b.type == m_name)                                                                                                \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const m_type *>(p_b._data._mem)); \
                                                                                                                               \
		_RETURN_FAIL                                                                                                           \
	};

#define DEFAULT_OP_LOCALMEM_NULL(m_prefix, m_op_name, m_name, m_op, m_type)                                                    \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                   \
		if (p_b.type == m_name)                                                                                                \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const m_type *>(p_b._data._mem)); \
		if (p_b.type == NIL)                                                                                                   \
			_RETURN(!(p_b.type m_op NIL));                                                                                     \
                                                                                                                               \
		_RETURN_FAIL                                                                                                           \
	};

#define DEFAULT_OP_LOCALMEM_NEG(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                         \
		_RETURN(-*reinterpret_cast<const m_type *>(p_a._data._mem)); \
	}

#define DEFAULT_OP_LOCALMEM_POS(m_prefix, m_op_name, m_name, m_type) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                         \
		_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem));  \
	}

#define DEFAULT_OP_LOCALMEM_NUM(m_prefix, m_op_name, m_name, m_op, m_type)                                                     \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                                   \
		if (p_b.type == m_name)                                                                                                \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op *reinterpret_cast<const m_type *>(p_b._data._mem)); \
		if (p_b.type == INT)                                                                                                   \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op p_b._data._int);                                    \
		if (p_b.type == REAL)                                                                                                  \
			_RETURN(*reinterpret_cast<const m_type *>(p_a._data._mem) m_op p_b._data._real);                                   \
                                                                                                                               \
		_RETURN_FAIL                                                                                                           \
	}

#define DEFAULT_OP_PTR(m_op, m_name, m_sub)                \
	CASE_TYPE(m_prefix, m_op_name, m_name) {               \
		if (p_b.type == m_name)                            \
			_RETURN(p_a._data.m_sub m_op p_b._data.m_sub); \
                                                           \
		_RETURN_FAIL                                       \
	}

#define DEFAULT_OP_PTRREF(m_prefix, m_op_name, m_name, m_op, m_sub) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                        \
		if (p_b.type == m_name)                                     \
			_RETURN(*p_a._data.m_sub m_op *p_b._data.m_sub);        \
                                                                    \
		_RETURN_FAIL                                                \
	}

#define DEFAULT_OP_PTRREF_NULL(m_prefix, m_op_name, m_name, m_op, m_sub) \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                             \
		if (p_b.type == m_name)                                          \
			_RETURN(*p_a._data.m_sub m_op *p_b._data.m_sub);             \
		if (p_b.type == NIL)                                             \
			_RETURN(!(p_b.type m_op NIL));                               \
                                                                         \
		_RETURN_FAIL                                                     \
	}

#define DEFAULT_OP_ARRAY_EQ(m_prefix, m_op_name, m_name, m_type)                                  \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                      \
		if (p_b.type == NIL)                                                                      \
			_RETURN(false)                                                                        \
		DEFAULT_OP_ARRAY_OP_BODY(m_prefix, m_op_name, m_name, m_type, !=, !=, true, false, false) \
	}

#define DEFAULT_OP_ARRAY_NEQ(m_prefix, m_op_name, m_name, m_type)                                \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                     \
		if (p_b.type == NIL)                                                                     \
			_RETURN(true)                                                                        \
		DEFAULT_OP_ARRAY_OP_BODY(m_prefix, m_op_name, m_name, m_type, !=, !=, false, true, true) \
	}

#define DEFAULT_OP_ARRAY_LT(m_prefix, m_op_name, m_name, m_type) \
	DEFAULT_OP_ARRAY_OP(m_prefix, m_op_name, m_name, m_type, <, !=, false, a_len < array_b.size(), true)

#define DEFAULT_OP_ARRAY_GT(m_prefix, m_op_name, m_name, m_type) \
	DEFAULT_OP_ARRAY_OP(m_prefix, m_op_name, m_name, m_type, >, !=, false, a_len < array_b.size(), true)

#define DEFAULT_OP_ARRAY_OP(m_prefix, m_op_name, m_name, m_type, m_opa, m_opb, m_ret_def, m_ret_s, m_ret_f)      \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                                     \
		DEFAULT_OP_ARRAY_OP_BODY(m_prefix, m_op_name, m_name, m_type, m_opa, m_opb, m_ret_def, m_ret_s, m_ret_f) \
	}

#define DEFAULT_OP_ARRAY_OP_BODY(m_prefix, m_op_name, m_name, m_type, m_opa, m_opb, m_ret_def, m_ret_s, m_ret_f) \
	if (p_a.type != p_b.type)                                                                                    \
		_RETURN_FAIL                                                                                             \
                                                                                                                 \
	const PoolVector<m_type> &array_a = *reinterpret_cast<const PoolVector<m_type> *>(p_a._data._mem);           \
	const PoolVector<m_type> &array_b = *reinterpret_cast<const PoolVector<m_type> *>(p_b._data._mem);           \
                                                                                                                 \
	int a_len = array_a.size();                                                                                  \
	if (a_len m_opa array_b.size()) {                                                                            \
		_RETURN(m_ret_s);                                                                                        \
	} else {                                                                                                     \
		PoolVector<m_type>::Read ra = array_a.read();                                                            \
		PoolVector<m_type>::Read rb = array_b.read();                                                            \
                                                                                                                 \
		for (int i = 0; i < a_len; i++) {                                                                        \
			if (ra[i] m_opb rb[i])                                                                               \
				_RETURN(m_ret_f);                                                                                \
		}                                                                                                        \
                                                                                                                 \
		_RETURN(m_ret_def);                                                                                      \
	}

#define DEFAULT_OP_ARRAY_ADD(m_prefix, m_op_name, m_name, m_type)                                          \
	CASE_TYPE(m_prefix, m_op_name, m_name) {                                                               \
		if (p_a.type != p_b.type)                                                                          \
			_RETURN_FAIL;                                                                                  \
                                                                                                           \
		const PoolVector<m_type> &array_a = *reinterpret_cast<const PoolVector<m_type> *>(p_a._data._mem); \
		const PoolVector<m_type> &array_b = *reinterpret_cast<const PoolVector<m_type> *>(p_b._data._mem); \
		PoolVector<m_type> sum = array_a;                                                                  \
		sum.append_array(array_b);                                                                         \
		_RETURN(sum);                                                                                      \
	}

void Variant::evaluate(const Operator &p_op, const Variant &p_a,
		const Variant &p_b, Variant &r_ret, bool &r_valid) {
	CASES(math);
	r_valid = true;

	SWITCH(math, p_op, p_a.type) {
		SWITCH_OP(math, OP_EQUAL, p_a.type) {
			CASE_TYPE(math, OP_EQUAL, NIL) {
				if (p_b.type == NIL)
					_RETURN(true);
				if (p_b.type == OBJECT)
					_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_b) == nullptr);

				_RETURN(false);
			}

			CASE_TYPE(math, OP_EQUAL, BOOL) {
				if (p_b.type != BOOL) {
					if (p_b.type == NIL)
						_RETURN(false);
					_RETURN_FAIL;
				}

				_RETURN(p_a._data._bool == p_b._data._bool);
			}

			CASE_TYPE(math, OP_EQUAL, OBJECT) {
				if (p_b.type == OBJECT)
					_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) == _UNSAFE_OBJ_PROXY_PTR(p_b));
				if (p_b.type == NIL)
					_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) == nullptr);

				_RETURN_FAIL;
			}

			CASE_TYPE(math, OP_EQUAL, DICTIONARY) {
				if (p_b.type != DICTIONARY) {
					if (p_b.type == NIL)
						_RETURN(false);
					_RETURN_FAIL;
				}

				const Dictionary *arr_a = reinterpret_cast<const Dictionary *>(p_a._data._mem);
				const Dictionary *arr_b = reinterpret_cast<const Dictionary *>(p_b._data._mem);

				_RETURN(*arr_a == *arr_b);
			}

			CASE_TYPE(math, OP_EQUAL, ARRAY) {
				if (p_b.type != ARRAY) {
					if (p_b.type == NIL)
						_RETURN(false);
					_RETURN_FAIL;
				}
				const Array *arr_a = reinterpret_cast<const Array *>(p_a._data._mem);
				const Array *arr_b = reinterpret_cast<const Array *>(p_b._data._mem);

				int l = arr_a->size();
				if (arr_b->size() != l)
					_RETURN(false);
				for (int i = 0; i < l; i++) {
					if (!((*arr_a)[i] == (*arr_b)[i])) {
						_RETURN(false);
					}
				}

				_RETURN(true);
			}

			DEFAULT_OP_NUM_NULL(math, OP_EQUAL, INT, ==, _int);
			DEFAULT_OP_NUM_NULL(math, OP_EQUAL, REAL, ==, _real);
			DEFAULT_OP_STR_NULL(math, OP_EQUAL, STRING, ==, String);
			DEFAULT_OP_STR_NULL_SN(math, OP_EQUAL, STRING_NAME, ==, StringName);

			DEFAULT_OP_ARRAY_EQ(math, OP_EQUAL, POOL_BYTE_ARRAY, uint8_t);
			DEFAULT_OP_ARRAY_EQ(math, OP_EQUAL, POOL_INT_ARRAY, int);
			DEFAULT_OP_ARRAY_EQ(math, OP_EQUAL, POOL_REAL_ARRAY, real_t);
			DEFAULT_OP_ARRAY_EQ(math, OP_EQUAL, POOL_STRING_ARRAY, String);
		}

		SWITCH_OP(math, OP_NOT_EQUAL, p_a.type) {
			CASE_TYPE(math, OP_NOT_EQUAL, NIL) {
				if (p_b.type == NIL)
					_RETURN(false);
				if (p_b.type == OBJECT)
					_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_b) != nullptr);

				_RETURN(true);
			}

			CASE_TYPE(math, OP_NOT_EQUAL, BOOL) {
				if (p_b.type != BOOL) {
					if (p_b.type == NIL)
						_RETURN(true);

					_RETURN_FAIL;
				}

				_RETURN(p_a._data._bool != p_b._data._bool);
			}

			CASE_TYPE(math, OP_NOT_EQUAL, OBJECT) {
				if (p_b.type == OBJECT)
					_RETURN((_UNSAFE_OBJ_PROXY_PTR(p_a) != _UNSAFE_OBJ_PROXY_PTR(p_b)));
				if (p_b.type == NIL)
					_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) != nullptr);

				_RETURN_FAIL;
			}

			CASE_TYPE(math, OP_NOT_EQUAL, DICTIONARY) {
				if (p_b.type != DICTIONARY) {
					if (p_b.type == NIL)
						_RETURN(true);
					_RETURN_FAIL;
				}

				const Dictionary *arr_a = reinterpret_cast<const Dictionary *>(p_a._data._mem);
				const Dictionary *arr_b = reinterpret_cast<const Dictionary *>(p_b._data._mem);

				_RETURN(*arr_a != *arr_b);
			}

			CASE_TYPE(math, OP_NOT_EQUAL, ARRAY) {
				if (p_b.type != ARRAY) {
					if (p_b.type == NIL)
						_RETURN(true);

					_RETURN_FAIL;
				}

				const Array *arr_a = reinterpret_cast<const Array *>(p_a._data._mem);
				const Array *arr_b = reinterpret_cast<const Array *>(p_b._data._mem);

				int l = arr_a->size();
				if (arr_b->size() != l)
					_RETURN(true);
				for (int i = 0; i < l; i++) {
					if (((*arr_a)[i] != (*arr_b)[i])) {
						_RETURN(true);
					}
				}

				_RETURN(false);
			}

			DEFAULT_OP_NUM_NULL(math, OP_NOT_EQUAL, INT, !=, _int);
			DEFAULT_OP_NUM_NULL(math, OP_NOT_EQUAL, REAL, !=, _real);
			DEFAULT_OP_STR_NULL(math, OP_NOT_EQUAL, STRING, !=, String);
			DEFAULT_OP_STR_NULL_SN(math, OP_NOT_EQUAL, STRING_NAME, !=, StringName);

			DEFAULT_OP_ARRAY_NEQ(math, OP_NOT_EQUAL, POOL_BYTE_ARRAY, uint8_t);
			DEFAULT_OP_ARRAY_NEQ(math, OP_NOT_EQUAL, POOL_INT_ARRAY, int);
			DEFAULT_OP_ARRAY_NEQ(math, OP_NOT_EQUAL, POOL_REAL_ARRAY, real_t);
			DEFAULT_OP_ARRAY_NEQ(math, OP_NOT_EQUAL, POOL_STRING_ARRAY, String);
		}

		SWITCH_OP(math, OP_LESS, p_a.type) {
			CASE_TYPE(math, OP_LESS, BOOL) {
				if (p_b.type != BOOL)
					_RETURN_FAIL;

				if (p_a._data._bool == p_b._data._bool)
					_RETURN(false);

				if (p_a._data._bool && !p_b._data._bool)
					_RETURN(false);

				_RETURN(true);
			}

			CASE_TYPE(math, OP_LESS, OBJECT) {
				if (p_b.type != OBJECT)
					_RETURN_FAIL;
				_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) < _UNSAFE_OBJ_PROXY_PTR(p_b));
			}

			CASE_TYPE(math, OP_LESS, ARRAY) {
				if (p_b.type != ARRAY)
					_RETURN_FAIL;

				const Array *arr_a = reinterpret_cast<const Array *>(p_a._data._mem);
				const Array *arr_b = reinterpret_cast<const Array *>(p_b._data._mem);

				int l = arr_a->size();
				if (arr_b->size() < l)
					_RETURN(false);
				for (int i = 0; i < l; i++) {
					if (!((*arr_a)[i] < (*arr_b)[i])) {
						_RETURN(true);
					}
				}

				_RETURN(false);
			}

			DEFAULT_OP_NUM(math, OP_LESS, INT, <, _int);
			DEFAULT_OP_NUM(math, OP_LESS, REAL, <, _real);
			DEFAULT_OP_STR(math, OP_LESS, STRING, <, String);

			DEFAULT_OP_ARRAY_LT(math, OP_LESS, POOL_BYTE_ARRAY, uint8_t);
			DEFAULT_OP_ARRAY_LT(math, OP_LESS, POOL_INT_ARRAY, int);
			DEFAULT_OP_ARRAY_LT(math, OP_LESS, POOL_REAL_ARRAY, real_t);
			DEFAULT_OP_ARRAY_LT(math, OP_LESS, POOL_STRING_ARRAY, String);

			CASE_TYPE(math, OP_LESS, NIL)
			CASE_TYPE(math, OP_LESS, STRING_NAME)
			CASE_TYPE(math, OP_LESS, DICTIONARY)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_LESS_EQUAL, p_a.type) {
			CASE_TYPE(math, OP_LESS_EQUAL, OBJECT) {
				if (p_b.type != OBJECT)
					_RETURN_FAIL;
				_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) <= _UNSAFE_OBJ_PROXY_PTR(p_b));
			}

			DEFAULT_OP_NUM(math, OP_LESS_EQUAL, INT, <=, _int);
			DEFAULT_OP_NUM(math, OP_LESS_EQUAL, REAL, <=, _real);
			DEFAULT_OP_STR(math, OP_LESS_EQUAL, STRING, <=, String);

			CASE_TYPE(math, OP_LESS_EQUAL, NIL)
			CASE_TYPE(math, OP_LESS_EQUAL, BOOL)
			CASE_TYPE(math, OP_LESS_EQUAL, STRING_NAME)
			CASE_TYPE(math, OP_LESS_EQUAL, DICTIONARY)
			CASE_TYPE(math, OP_LESS_EQUAL, ARRAY)
			CASE_TYPE(math, OP_LESS_EQUAL, POOL_BYTE_ARRAY);
			CASE_TYPE(math, OP_LESS_EQUAL, POOL_INT_ARRAY);
			CASE_TYPE(math, OP_LESS_EQUAL, POOL_REAL_ARRAY);
			CASE_TYPE(math, OP_LESS_EQUAL, POOL_STRING_ARRAY);
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_GREATER, p_a.type) {
			CASE_TYPE(math, OP_GREATER, BOOL) {
				if (p_b.type != BOOL)
					_RETURN_FAIL;

				if (p_a._data._bool == p_b._data._bool)
					_RETURN(false);

				if (!p_a._data._bool && p_b._data._bool)
					_RETURN(false);

				_RETURN(true);
			}

			CASE_TYPE(math, OP_GREATER, OBJECT) {
				if (p_b.type != OBJECT)
					_RETURN_FAIL;
				_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) > _UNSAFE_OBJ_PROXY_PTR(p_b));
			}

			CASE_TYPE(math, OP_GREATER, ARRAY) {
				if (p_b.type != ARRAY)
					_RETURN_FAIL;

				const Array *arr_a = reinterpret_cast<const Array *>(p_a._data._mem);
				const Array *arr_b = reinterpret_cast<const Array *>(p_b._data._mem);

				int l = arr_a->size();
				if (arr_b->size() > l)
					_RETURN(false);
				for (int i = 0; i < l; i++) {
					if (((*arr_a)[i] < (*arr_b)[i])) {
						_RETURN(false);
					}
				}

				_RETURN(true);
			}

			DEFAULT_OP_NUM(math, OP_GREATER, INT, >, _int);
			DEFAULT_OP_NUM(math, OP_GREATER, REAL, >, _real);
			DEFAULT_OP_STR_REV(math, OP_GREATER, STRING, <, String);
			DEFAULT_OP_ARRAY_GT(math, OP_GREATER, POOL_BYTE_ARRAY, uint8_t);
			DEFAULT_OP_ARRAY_GT(math, OP_GREATER, POOL_INT_ARRAY, int);
			DEFAULT_OP_ARRAY_GT(math, OP_GREATER, POOL_REAL_ARRAY, real_t);
			DEFAULT_OP_ARRAY_GT(math, OP_GREATER, POOL_STRING_ARRAY, String);

			CASE_TYPE(math, OP_GREATER, NIL)
			CASE_TYPE(math, OP_GREATER, STRING_NAME)
			CASE_TYPE(math, OP_GREATER, DICTIONARY)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_GREATER_EQUAL, p_a.type) {
			CASE_TYPE(math, OP_GREATER_EQUAL, OBJECT) {
				if (p_b.type != OBJECT)
					_RETURN_FAIL;
				_RETURN(_UNSAFE_OBJ_PROXY_PTR(p_a) >= _UNSAFE_OBJ_PROXY_PTR(p_b));
			}

			DEFAULT_OP_NUM(math, OP_GREATER_EQUAL, INT, >=, _int);
			DEFAULT_OP_NUM(math, OP_GREATER_EQUAL, REAL, >=, _real);
			DEFAULT_OP_STR_REV(math, OP_GREATER_EQUAL, STRING, <=, String);

			CASE_TYPE(math, OP_GREATER_EQUAL, NIL)
			CASE_TYPE(math, OP_GREATER_EQUAL, BOOL)
			CASE_TYPE(math, OP_GREATER_EQUAL, DICTIONARY)
			CASE_TYPE(math, OP_GREATER_EQUAL, STRING_NAME)
			CASE_TYPE(math, OP_GREATER_EQUAL, ARRAY)
			CASE_TYPE(math, OP_GREATER_EQUAL, POOL_BYTE_ARRAY);
			CASE_TYPE(math, OP_GREATER_EQUAL, POOL_INT_ARRAY);
			CASE_TYPE(math, OP_GREATER_EQUAL, POOL_REAL_ARRAY);
			CASE_TYPE(math, OP_GREATER_EQUAL, POOL_STRING_ARRAY);
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_ADD, p_a.type) {
			CASE_TYPE(math, OP_ADD, ARRAY) {
				if (p_a.type != p_b.type)
					_RETURN_FAIL;

				const Array &array_a = *reinterpret_cast<const Array *>(p_a._data._mem);
				const Array &array_b = *reinterpret_cast<const Array *>(p_b._data._mem);
				Array sum;
				int asize = array_a.size();
				int bsize = array_b.size();
				sum.resize(asize + bsize);
				for (int i = 0; i < asize; i++) {
					sum[i] = array_a[i];
				}
				for (int i = 0; i < bsize; i++) {
					sum[i + asize] = array_b[i];
				}
				_RETURN(sum);
			}

			DEFAULT_OP_NUM(math, OP_ADD, INT, +, _int);
			DEFAULT_OP_NUM(math, OP_ADD, REAL, +, _real);
			DEFAULT_OP_STR(math, OP_ADD, STRING, +, String);

			DEFAULT_OP_ARRAY_ADD(math, OP_ADD, POOL_BYTE_ARRAY, uint8_t);
			DEFAULT_OP_ARRAY_ADD(math, OP_ADD, POOL_INT_ARRAY, int);
			DEFAULT_OP_ARRAY_ADD(math, OP_ADD, POOL_REAL_ARRAY, real_t);
			DEFAULT_OP_ARRAY_ADD(math, OP_ADD, POOL_STRING_ARRAY, String);

			CASE_TYPE(math, OP_ADD, NIL)
			CASE_TYPE(math, OP_ADD, BOOL)
			CASE_TYPE(math, OP_ADD, OBJECT)
			CASE_TYPE(math, OP_ADD, DICTIONARY)
			CASE_TYPE(math, OP_ADD, STRING_NAME)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_SUBTRACT, p_a.type) {
			DEFAULT_OP_NUM(math, OP_SUBTRACT, INT, -, _int);
			DEFAULT_OP_NUM(math, OP_SUBTRACT, REAL, -, _real);

			CASE_TYPE(math, OP_SUBTRACT, NIL)
			CASE_TYPE(math, OP_SUBTRACT, BOOL)
			CASE_TYPE(math, OP_SUBTRACT, STRING)
			CASE_TYPE(math, OP_SUBTRACT, OBJECT)
			CASE_TYPE(math, OP_SUBTRACT, STRING_NAME)
			CASE_TYPE(math, OP_SUBTRACT, DICTIONARY)
			CASE_TYPE(math, OP_SUBTRACT, ARRAY)
			CASE_TYPE(math, OP_SUBTRACT, POOL_BYTE_ARRAY);
			CASE_TYPE(math, OP_SUBTRACT, POOL_INT_ARRAY);
			CASE_TYPE(math, OP_SUBTRACT, POOL_REAL_ARRAY);
			CASE_TYPE(math, OP_SUBTRACT, POOL_STRING_ARRAY);
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_MULTIPLY, p_a.type) {
			DEFAULT_OP_NUM_VEC(math, OP_MULTIPLY, INT, *, _int);
			DEFAULT_OP_NUM_VEC(math, OP_MULTIPLY, REAL, *, _real);

			CASE_TYPE(math, OP_MULTIPLY, NIL)
			CASE_TYPE(math, OP_MULTIPLY, BOOL)
			CASE_TYPE(math, OP_MULTIPLY, STRING)
			CASE_TYPE(math, OP_MULTIPLY, OBJECT)
			CASE_TYPE(math, OP_MULTIPLY, STRING_NAME)
			CASE_TYPE(math, OP_MULTIPLY, DICTIONARY)
			CASE_TYPE(math, OP_MULTIPLY, ARRAY)
			CASE_TYPE(math, OP_MULTIPLY, POOL_BYTE_ARRAY);
			CASE_TYPE(math, OP_MULTIPLY, POOL_INT_ARRAY);
			CASE_TYPE(math, OP_MULTIPLY, POOL_REAL_ARRAY);
			CASE_TYPE(math, OP_MULTIPLY, POOL_STRING_ARRAY);
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_DIVIDE, p_a.type) {
			DEFAULT_OP_NUM_DIV(math, OP_DIVIDE, INT, _int);
			DEFAULT_OP_NUM_DIV(math, OP_DIVIDE, REAL, _real);

			CASE_TYPE(math, OP_DIVIDE, NIL)
			CASE_TYPE(math, OP_DIVIDE, BOOL)
			CASE_TYPE(math, OP_DIVIDE, STRING)
			CASE_TYPE(math, OP_DIVIDE, OBJECT)
			CASE_TYPE(math, OP_DIVIDE, STRING_NAME)
			CASE_TYPE(math, OP_DIVIDE, DICTIONARY)
			CASE_TYPE(math, OP_DIVIDE, ARRAY)
			CASE_TYPE(math, OP_DIVIDE, POOL_BYTE_ARRAY);
			CASE_TYPE(math, OP_DIVIDE, POOL_INT_ARRAY);
			CASE_TYPE(math, OP_DIVIDE, POOL_REAL_ARRAY);
			CASE_TYPE(math, OP_DIVIDE, POOL_STRING_ARRAY);
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_POSITIVE, p_a.type) {
			DEFAULT_OP_NUM_POS(math, OP_POSITIVE, INT, _int);
			DEFAULT_OP_NUM_POS(math, OP_POSITIVE, REAL, _real);

			CASE_TYPE(math, OP_POSITIVE, NIL)
			CASE_TYPE(math, OP_POSITIVE, BOOL)
			CASE_TYPE(math, OP_POSITIVE, STRING)
			CASE_TYPE(math, OP_POSITIVE, OBJECT)
			CASE_TYPE(math, OP_POSITIVE, STRING_NAME)
			CASE_TYPE(math, OP_POSITIVE, DICTIONARY)
			CASE_TYPE(math, OP_POSITIVE, ARRAY)
			CASE_TYPE(math, OP_POSITIVE, POOL_BYTE_ARRAY)
			CASE_TYPE(math, OP_POSITIVE, POOL_INT_ARRAY)
			CASE_TYPE(math, OP_POSITIVE, POOL_REAL_ARRAY)
			CASE_TYPE(math, OP_POSITIVE, POOL_STRING_ARRAY)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_NEGATE, p_a.type) {
			DEFAULT_OP_NUM_NEG(math, OP_NEGATE, INT, _int);
			DEFAULT_OP_NUM_NEG(math, OP_NEGATE, REAL, _real);

			CASE_TYPE(math, OP_NEGATE, NIL)
			CASE_TYPE(math, OP_NEGATE, BOOL)
			CASE_TYPE(math, OP_NEGATE, STRING)
			CASE_TYPE(math, OP_NEGATE, OBJECT)
			CASE_TYPE(math, OP_NEGATE, STRING_NAME)
			CASE_TYPE(math, OP_NEGATE, DICTIONARY)
			CASE_TYPE(math, OP_NEGATE, ARRAY)
			CASE_TYPE(math, OP_NEGATE, POOL_BYTE_ARRAY)
			CASE_TYPE(math, OP_NEGATE, POOL_INT_ARRAY)
			CASE_TYPE(math, OP_NEGATE, POOL_REAL_ARRAY)
			CASE_TYPE(math, OP_NEGATE, POOL_STRING_ARRAY)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_MODULE, p_a.type) {
			CASE_TYPE(math, OP_MODULE, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
#ifdef DEBUG_ENABLED
				if (p_b._data._int == 0) {
					r_valid = false;
					_RETURN("Division By Zero");
				}
#endif
				_RETURN(p_a._data._int % p_b._data._int);
			}

			CASE_TYPE(math, OP_MODULE, STRING) {
				const String *format = reinterpret_cast<const String *>(p_a._data._mem);

				String result;
				bool error;
				if (p_b.type == ARRAY) {
					// e.g. "frog %s %d" % ["fish", 12]
					const Array *args = reinterpret_cast<const Array *>(p_b._data._mem);
					result = args->sprintf(*format, &error);
				} else {
					// e.g. "frog %d" % 12
					Array args;
					args.push_back(p_b);
					result = args.sprintf(*format, &error);
				}
				r_valid = !error;
				_RETURN(result);
			}

			CASE_TYPE(math, OP_MODULE, NIL)
			CASE_TYPE(math, OP_MODULE, BOOL)
			CASE_TYPE(math, OP_MODULE, REAL)
			CASE_TYPE(math, OP_MODULE, OBJECT)
			CASE_TYPE(math, OP_MODULE, STRING_NAME)
			CASE_TYPE(math, OP_MODULE, DICTIONARY)
			CASE_TYPE(math, OP_MODULE, ARRAY)
			CASE_TYPE(math, OP_MODULE, POOL_BYTE_ARRAY)
			CASE_TYPE(math, OP_MODULE, POOL_INT_ARRAY)
			CASE_TYPE(math, OP_MODULE, POOL_REAL_ARRAY)
			CASE_TYPE(math, OP_MODULE, POOL_STRING_ARRAY)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_STRING_CONCAT, p_a.type) {
			CASE_TYPE_ALL(math, OP_STRING_CONCAT)

			_RETURN(p_a.operator String() + p_b.operator String());
		}

		SWITCH_OP(math, OP_SHIFT_LEFT, p_a.type) {
			CASE_TYPE(math, OP_SHIFT_LEFT, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
				if (p_b._data._int < 0 || p_b._data._int >= 64)
					_RETURN_FAIL;
				_RETURN(p_a._data._int << p_b._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_SHIFT_LEFT)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_SHIFT_RIGHT, p_a.type) {
			CASE_TYPE(math, OP_SHIFT_RIGHT, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
				if (p_b._data._int < 0 || p_b._data._int >= 64)
					_RETURN_FAIL;
				_RETURN(p_a._data._int >> p_b._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_SHIFT_RIGHT)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_BIT_AND, p_a.type) {
			CASE_TYPE(math, OP_BIT_AND, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
				_RETURN(p_a._data._int & p_b._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_BIT_AND)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_BIT_OR, p_a.type) {
			CASE_TYPE(math, OP_BIT_OR, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
				_RETURN(p_a._data._int | p_b._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_BIT_OR)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_BIT_XOR, p_a.type) {
			CASE_TYPE(math, OP_BIT_XOR, INT) {
				if (p_b.type != INT)
					_RETURN_FAIL;
				_RETURN(p_a._data._int ^ p_b._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_BIT_XOR)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_BIT_NEGATE, p_a.type) {
			CASE_TYPE(math, OP_BIT_NEGATE, INT) {
				_RETURN(~p_a._data._int);
			}

			CASE_TYPE_ALL_BUT_INT(math, OP_BIT_NEGATE)
			_RETURN_FAIL;
		}

		SWITCH_OP(math, OP_AND, p_a.type) {
			CASE_TYPE_ALL(math, OP_AND) {
				bool l = p_a.booleanize();
				bool r = p_b.booleanize();

				_RETURN(l && r);
			}
		}

		SWITCH_OP(math, OP_OR, p_a.type) {
			CASE_TYPE_ALL(math, OP_OR) {
				bool l = p_a.booleanize();
				bool r = p_b.booleanize();

				_RETURN(l || r);
			}
		}

		SWITCH_OP(math, OP_XOR, p_a.type) {
			CASE_TYPE_ALL(math, OP_XOR) {
				bool l = p_a.booleanize();
				bool r = p_b.booleanize();

				_RETURN((l || r) && !(l && r));
			}
		}

		SWITCH_OP(math, OP_NOT, p_a.type) {
			CASE_TYPE_ALL(math, OP_NOT) {
				bool l = p_a.booleanize();
				_RETURN(!l);
			}
		}

		SWITCH_OP(math, OP_IN, p_a.type) {
			CASE_TYPE_ALL(math, OP_IN)
			_RETURN(p_b.in(p_a, &r_valid));
		}
	}
}

void Variant::set_named(const StringName &p_index, const Variant &p_value, bool *r_valid) {
	bool valid = false;
	switch (type) {
		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (unlikely(!obj)) {
#ifdef DEBUG_ENABLED
				if (_get_obj().rc) {
					ERR_PRINT("Attempted set on a deleted object.");
				}
#endif
				break;
			}
			obj->set(p_index, p_value, &valid);

		} break;
		default: {
			set(p_index.operator String(), p_value, &valid);
		} break;
	}

	if (r_valid) {
		*r_valid = valid;
	}
}

Variant Variant::get_named(const StringName &p_index, bool *r_valid) const {
	if (r_valid) {
		*r_valid = true;
	}
	switch (type) {
		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (unlikely(!obj)) {
				if (r_valid) {
					*r_valid = false;
				}
#ifdef DEBUG_ENABLED
				if (_get_obj().rc) {
					ERR_PRINT("Attempted get on a deleted object.");
				}
#endif
				return Variant();
			}

			return obj->get(p_index, r_valid);

		} break;
		case DICTIONARY: {
			const Dictionary *dic = reinterpret_cast<const Dictionary *>(_data._mem);
			const Variant *res = dic->getptr(p_index);
			if (!res) {
				// Backwards compatibility for before variants supported stringnames.
				const Variant *res2 = dic->getptr(p_index.operator String());

				if (res2) {
					if (r_valid) {
						*r_valid = true;
					}
					return *res2;
				}
			} else {
				if (r_valid) {
					*r_valid = true;
				}
				return *res;
			}
		} break;
		default: {
			return get(p_index.operator String(), r_valid);
		}
	}

	if (r_valid) {
		*r_valid = false;
	}
	return Variant();
}

#define DEFAULT_OP_ARRAY_CMD(m_name, m_type, skip_test, cmd)                             \
	case m_name: {                                                                       \
		skip_test;                                                                       \
                                                                                         \
		if (p_index.get_type() == Variant::INT || p_index.get_type() == Variant::REAL) { \
			int index = p_index;                                                         \
			m_type *arr = reinterpret_cast<m_type *>(_data._mem);                        \
                                                                                         \
			if (index < 0)                                                               \
				index += arr->size();                                                    \
			if (index >= 0 && index < arr->size()) {                                     \
				valid = true;                                                            \
				cmd;                                                                     \
			}                                                                            \
		}                                                                                \
	} break;

// clang-format 14 wants to add a space after the last return,
// and clang-format 15 removes it...
/* clang-format off */
#define DEFAULT_OP_DVECTOR_SET(m_name, dv_type, skip_cond) \
	DEFAULT_OP_ARRAY_CMD(m_name, PoolVector<dv_type>, if (skip_cond) return;, arr->set(index, p_value); return)
/* clang-format on */

#define DEFAULT_OP_DVECTOR_GET(m_name, dv_type) \
	DEFAULT_OP_ARRAY_CMD(m_name, const PoolVector<dv_type>, ;, return arr->get(index))

void Variant::set(const Variant &p_index, const Variant &p_value, bool *r_valid) {
	static bool _dummy = false;

	bool &valid = r_valid ? *r_valid : _dummy;
	valid = false;

	switch (type) {
		case NIL: {
			return;
		} break;
		case BOOL: {
			return;
		} break;
		case INT: {
			return;
		} break;
		case REAL: {
			return;
		} break;
		case STRING: {
			if (p_index.type != Variant::INT && p_index.type != Variant::REAL) {
				return;
			}

			int idx = p_index;
			String *str = reinterpret_cast<String *>(_data._mem);
			int len = str->length();
			if (idx < 0) {
				idx += len;
			}
			if (idx < 0 || idx >= len) {
				return;
			}

			String chr;
			if (p_value.type == Variant::INT || p_value.type == Variant::REAL) {
				chr = String::chr(p_value);
			} else if (p_value.type == Variant::STRING) {
				chr = p_value;
			} else {
				return;
			}

			*str = str->substr(0, idx) + chr + str->substr(idx + 1, len);
			valid = true;
			return;

		} break;

		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (unlikely(!obj)) {
				valid = false;
#ifdef DEBUG_ENABLED
				if (_get_obj().rc) {
					ERR_PRINT("Attempted set on a deleted object.");
				}
#endif
				return;
			}

			obj->set(p_index, p_value, r_valid);
			return;
		} break;
		case STRING_NAME: {
		} break;
		case DICTIONARY: {
			Dictionary *dic = reinterpret_cast<Dictionary *>(_data._mem);
			dic->operator[](p_index) = p_value;
			valid = true; //always valid, i guess? should this really be ok?
			return;
		} break;
			// clang-format 14 wants to add a space after the last return,
			// and clang-format 15 removes it...
			/* clang-format off */
			DEFAULT_OP_ARRAY_CMD(ARRAY, Array, ;, (*arr)[index] = p_value; return) // 20
			/* clang-format on */
			DEFAULT_OP_DVECTOR_SET(POOL_BYTE_ARRAY, uint8_t, p_value.type != Variant::REAL && p_value.type != Variant::INT)
			DEFAULT_OP_DVECTOR_SET(POOL_INT_ARRAY, int, p_value.type != Variant::REAL && p_value.type != Variant::INT)
			DEFAULT_OP_DVECTOR_SET(POOL_REAL_ARRAY, real_t, p_value.type != Variant::REAL && p_value.type != Variant::INT)
			DEFAULT_OP_DVECTOR_SET(POOL_STRING_ARRAY, String, p_value.type != Variant::STRING)
		default:
			return;
	}
}

Variant Variant::get(const Variant &p_index, bool *r_valid) const {
	static bool _dummy = false;

	bool &valid = r_valid ? *r_valid : _dummy;

	valid = false;

	switch (type) {
		case NIL: {
			return Variant();
		} break;
		case BOOL: {
			return Variant();
		} break;
		case INT: {
			return Variant();
		} break;
		case REAL: {
			return Variant();
		} break;
		case STRING: {
			if (p_index.get_type() == Variant::INT || p_index.get_type() == Variant::REAL) {
				//string index

				int idx = p_index;
				const String *str = reinterpret_cast<const String *>(_data._mem);
				if (idx < 0) {
					idx += str->length();
				}
				if (idx >= 0 && idx < str->length()) {
					valid = true;
					return str->substr(idx, 1);
				}
			}

		} break;
	
		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (unlikely(!obj)) {
				valid = false;
#ifdef DEBUG_ENABLED
				if (_get_obj().rc) {
					ERR_PRINT("Attempted get on a deleted object.");
				}
#endif
				return Variant();
			}

			return obj->get(p_index, r_valid);

		} break;
		case STRING_NAME: {
		} break;
		case DICTIONARY: {
			const Dictionary *dic = reinterpret_cast<const Dictionary *>(_data._mem);
			const Variant *res = dic->getptr(p_index);
			if (res) {
				valid = true;
				return *res;
			}
		} break;
			DEFAULT_OP_ARRAY_CMD(ARRAY, const Array, ;, return (*arr)[index]) // 20
			DEFAULT_OP_DVECTOR_GET(POOL_BYTE_ARRAY, uint8_t)
			DEFAULT_OP_DVECTOR_GET(POOL_INT_ARRAY, int)
			DEFAULT_OP_DVECTOR_GET(POOL_REAL_ARRAY, real_t)
			DEFAULT_OP_DVECTOR_GET(POOL_STRING_ARRAY, String)
		default:
			return Variant();
	}

	return Variant();
}

bool Variant::in(const Variant &p_index, bool *r_valid) const {
	if (r_valid) {
		*r_valid = true;
	}

	switch (type) {
		case STRING: {
			if (p_index.get_type() == Variant::STRING) {
				//string index
				String idx = p_index;
				const String *str = reinterpret_cast<const String *>(_data._mem);

				return str->find(idx) != -1;
			}

		} break;
		case OBJECT: {
			Object *obj = _OBJ_PTR(*this);
			if (unlikely(!obj)) {
				if (r_valid) {
					*r_valid = false;
				}
#ifdef DEBUG_ENABLED
				if (_get_obj().rc) {
					ERR_PRINT("Attempted 'in' on a deleted object.");
				}
#endif
				return false;
			}

			bool result;
			obj->get(p_index, &result);
			return result;
		} break;
		case DICTIONARY: {
			const Dictionary *dic = reinterpret_cast<const Dictionary *>(_data._mem);
			return dic->has(p_index);

		} break; // 20
		case ARRAY: {
			const Array *arr = reinterpret_cast<const Array *>(_data._mem);
			int l = arr->size();
			if (l) {
				for (int i = 0; i < l; i++) {
					if (evaluate(OP_EQUAL, (*arr)[i], p_index)) {
						return true;
					}
				}
			}

			return false;

		} break;
		case POOL_BYTE_ARRAY: {
			if (p_index.get_type() == Variant::INT || p_index.get_type() == Variant::REAL) {
				int index = p_index;
				const PoolVector<uint8_t> *arr = reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
				int l = arr->size();
				if (l) {
					PoolVector<uint8_t>::Read r = arr->read();
					for (int i = 0; i < l; i++) {
						if (r[i] == index) {
							return true;
						}
					}
				}

				return false;
			}

		} break;
		case POOL_INT_ARRAY: {
			if (p_index.get_type() == Variant::INT || p_index.get_type() == Variant::REAL) {
				int index = p_index;
				const PoolVector<int> *arr = reinterpret_cast<const PoolVector<int> *>(_data._mem);
				int l = arr->size();
				if (l) {
					PoolVector<int>::Read r = arr->read();
					for (int i = 0; i < l; i++) {
						if (r[i] == index) {
							return true;
						}
					}
				}

				return false;
			}
		} break;
		case POOL_REAL_ARRAY: {
			if (p_index.get_type() == Variant::INT || p_index.get_type() == Variant::REAL) {
				real_t index = p_index;
				const PoolVector<real_t> *arr = reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
				int l = arr->size();
				if (l) {
					PoolVector<real_t>::Read r = arr->read();
					for (int i = 0; i < l; i++) {
						if (r[i] == index) {
							return true;
						}
					}
				}

				return false;
			}

		} break;
		case POOL_STRING_ARRAY: {
			if (p_index.get_type() == Variant::STRING) {
				String index = p_index;
				const PoolVector<String> *arr = reinterpret_cast<const PoolVector<String> *>(_data._mem);

				int l = arr->size();
				if (l) {
					PoolVector<String>::Read r = arr->read();
					for (int i = 0; i < l; i++) {
						if (r[i] == index) {
							return true;
						}
					}
				}

				return false;
			}

		} break; //25
	
		default: {
		}
	}

	if (r_valid) {
		*r_valid = false;
	}
	return false;
}

bool Variant::iter_init(Variant &r_iter, bool &valid) const {
	valid = true;
	switch (type) {
		case INT: {
			r_iter = 0;
			return _data._int > 0;
		} break;
		case REAL: {
			r_iter = 0;
			return _data._real > 0.0;
		} break;
		case STRING: {
			const String *str = reinterpret_cast<const String *>(_data._mem);
			if (str->empty()) {
				return false;
			}
			r_iter = 0;
			return true;
		} break;
		case DICTIONARY: {
			const Dictionary *dic = reinterpret_cast<const Dictionary *>(_data._mem);
			if (dic->empty()) {
				return false;
			}

			const Variant *next = dic->next(nullptr);
			r_iter = *next;
			return true;

		} break;
		case ARRAY: {
			const Array *arr = reinterpret_cast<const Array *>(_data._mem);
			if (arr->empty()) {
				return false;
			}
			r_iter = 0;
			return true;
		} break;
		case POOL_BYTE_ARRAY: {
			const PoolVector<uint8_t> *arr = reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
			if (arr->size() == 0) {
				return false;
			}
			r_iter = 0;
			return true;

		} break;
		case POOL_INT_ARRAY: {
			const PoolVector<int> *arr = reinterpret_cast<const PoolVector<int> *>(_data._mem);
			if (arr->size() == 0) {
				return false;
			}
			r_iter = 0;
			return true;

		} break;
		case POOL_REAL_ARRAY: {
			const PoolVector<real_t> *arr = reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
			if (arr->size() == 0) {
				return false;
			}
			r_iter = 0;
			return true;

		} break;
		case POOL_STRING_ARRAY: {
			const PoolVector<String> *arr = reinterpret_cast<const PoolVector<String> *>(_data._mem);
			if (arr->size() == 0) {
				return false;
			}
			r_iter = 0;
			return true;
		} break;
		default: {
		}
	}

	valid = false;
	return false;
}
bool Variant::iter_next(Variant &r_iter, bool &valid) const {
	valid = true;
	switch (type) {
		case INT: {
			int64_t idx = r_iter;
			idx++;
			if (idx >= _data._int) {
				return false;
			}
			r_iter = idx;
			return true;
		} break;
		case REAL: {
			int64_t idx = r_iter;
			idx++;
			if (idx >= _data._real) {
				return false;
			}
			r_iter = idx;
			return true;
		} break;
		case STRING: {
			const String *str = reinterpret_cast<const String *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= str->length()) {
				return false;
			}
			r_iter = idx;
			return true;
		} break;
		case DICTIONARY: {
			const Dictionary *dic = reinterpret_cast<const Dictionary *>(_data._mem);
			const Variant *next = dic->next(&r_iter);
			if (!next) {
				return false;
			}

			r_iter = *next;
			return true;

		} break;
		case ARRAY: {
			const Array *arr = reinterpret_cast<const Array *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= arr->size()) {
				return false;
			}
			r_iter = idx;
			return true;
		} break;
		case POOL_BYTE_ARRAY: {
			const PoolVector<uint8_t> *arr = reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= arr->size()) {
				return false;
			}
			r_iter = idx;
			return true;

		} break;
		case POOL_INT_ARRAY: {
			const PoolVector<int> *arr = reinterpret_cast<const PoolVector<int> *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= arr->size()) {
				return false;
			}
			r_iter = idx;
			return true;

		} break;
		case POOL_REAL_ARRAY: {
			const PoolVector<real_t> *arr = reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= arr->size()) {
				return false;
			}
			r_iter = idx;
			return true;

		} break;
		case POOL_STRING_ARRAY: {
			const PoolVector<String> *arr = reinterpret_cast<const PoolVector<String> *>(_data._mem);
			int idx = r_iter;
			idx++;
			if (idx >= arr->size()) {
				return false;
			}
			r_iter = idx;
			return true;
		} break;
		default: {
		}
	}

	valid = false;
	return false;
}

Variant Variant::iter_get(const Variant &r_iter, bool &r_valid) const {
	r_valid = true;
	switch (type) {
		case INT: {
			return r_iter;
		} break;
		case REAL: {
			return r_iter;
		} break;
		case STRING: {
			const String *str = reinterpret_cast<const String *>(_data._mem);
			return str->substr(r_iter, 1);
		} break;
		case DICTIONARY: {
			return r_iter; //iterator is the same as the key

		} break;
		case ARRAY: {
			const Array *arr = reinterpret_cast<const Array *>(_data._mem);
			int idx = r_iter;
#ifdef DEBUG_ENABLED
			if (idx < 0 || idx >= arr->size()) {
				r_valid = false;
				return Variant();
			}
#endif
			return arr->get(idx);
		} break;
		case POOL_BYTE_ARRAY: {
			const PoolVector<uint8_t> *arr = reinterpret_cast<const PoolVector<uint8_t> *>(_data._mem);
			int idx = r_iter;
#ifdef DEBUG_ENABLED
			if (idx < 0 || idx >= arr->size()) {
				r_valid = false;
				return Variant();
			}
#endif
			return arr->get(idx);
		} break;
		case POOL_INT_ARRAY: {
			const PoolVector<int> *arr = reinterpret_cast<const PoolVector<int> *>(_data._mem);
			int idx = r_iter;
#ifdef DEBUG_ENABLED
			if (idx < 0 || idx >= arr->size()) {
				r_valid = false;
				return Variant();
			}
#endif
			return arr->get(idx);
		} break;
		case POOL_REAL_ARRAY: {
			const PoolVector<real_t> *arr = reinterpret_cast<const PoolVector<real_t> *>(_data._mem);
			int idx = r_iter;
#ifdef DEBUG_ENABLED
			if (idx < 0 || idx >= arr->size()) {
				r_valid = false;
				return Variant();
			}
#endif
			return arr->get(idx);
		} break;
		case POOL_STRING_ARRAY: {
			const PoolVector<String> *arr = reinterpret_cast<const PoolVector<String> *>(_data._mem);
			int idx = r_iter;
#ifdef DEBUG_ENABLED
			if (idx < 0 || idx >= arr->size()) {
				r_valid = false;
				return Variant();
			}
#endif
			return arr->get(idx);
		} break;
		default: {
		}
	}

	r_valid = false;
	return Variant();
}

Variant Variant::duplicate(bool deep) const {
	switch (type) {
		case OBJECT: {
			/*  breaks stuff :(
			if (deep && !_get_obj().ref.is_null()) {
				Ref<Resource> resource = _get_obj().ref;
				if (resource.is_valid()) {
					return resource->duplicate(true);
				}
			}
			*/
			return *this;
		} break;
		case DICTIONARY:
			return operator Dictionary().duplicate(deep);
		case ARRAY:
			return operator Array().duplicate(deep);
		default:
			return *this;
	}
}

void Variant::sub(const Variant &a, const Variant &b, Variant &r_dst) {
	if (a.type != b.type) {
		return;
	}

	switch (a.type) {
		case NIL: {
			r_dst = Variant();
		}
			return;
		case INT: {
			int64_t va = a._data._int;
			int64_t vb = b._data._int;
			r_dst = int(va - vb);
		}
			return;
		case REAL: {
			real_t ra = a._data._real;
			real_t rb = b._data._real;
			r_dst = ra - rb;
		}
			return;
		default: {
			r_dst = a;
		}
			return;
	}
}

void Variant::blend(const Variant &a, const Variant &b, float c, Variant &r_dst) {
	if (a.type != b.type) {
		if (a.is_num() && b.is_num()) {
			real_t va = a;
			real_t vb = b;
			r_dst = va + vb * c;
		} else {
			r_dst = a;
		}
		return;
	}

	switch (a.type) {
		case NIL: {
			r_dst = Variant();
		}
			return;
		case INT: {
			int64_t va = a._data._int;
			int64_t vb = b._data._int;
			r_dst = int(va + vb * c + 0.5);
		}
			return;
		case REAL: {
			double ra = a._data._real;
			double rb = b._data._real;
			r_dst = ra + rb * c;
		}
			return;
		default: {
			r_dst = c < 0.5 ? a : b;
		}
			return;
	}
}

void Variant::interpolate(const Variant &a, const Variant &b, float c, Variant &r_dst) {
	if (a.type != b.type) {
		if (a.is_num() && b.is_num()) {
			//not as efficient but..
			real_t va = a;
			real_t vb = b;
			r_dst = va + (vb - va) * c;

		} else {
			r_dst = a;
		}
		return;
	}

	switch (a.type) {
		case NIL: {
			r_dst = Variant();
		}
			return;
		case BOOL: {
			r_dst = a;
		}
			return;
		case INT: {
			int64_t va = a._data._int;
			int64_t vb = b._data._int;
			r_dst = int(va + (vb - va) * c);
		}
			return;
		case REAL: {
			real_t va = a._data._real;
			real_t vb = b._data._real;
			r_dst = va + (vb - va) * c;
		}
			return;
		case STRING: {
			//this is pretty funny and bizarre, but artists like to use it for typewritter effects
			String sa = *reinterpret_cast<const String *>(a._data._mem);
			String sb = *reinterpret_cast<const String *>(b._data._mem);
			String dst;
			int sa_len = sa.length();
			int sb_len = sb.length();
			int csize = sa_len + (sb_len - sa_len) * c;
			if (csize == 0) {
				r_dst = "";
				return;
			}
			dst.resize(csize + 1);
			dst[csize] = 0;
			int split = csize / 2;

			for (int i = 0; i < csize; i++) {
				CharType chr = ' ';

				if (i < split) {
					if (i < sa.length()) {
						chr = sa[i];
					} else if (i < sb.length()) {
						chr = sb[i];
					}

				} else {
					if (i < sb.length()) {
						chr = sb[i];
					} else if (i < sa.length()) {
						chr = sa[i];
					}
				}

				dst[i] = chr;
			}

			r_dst = dst;
		}
			return;
		case OBJECT: {
			r_dst = a;
		}
			return;
		case STRING_NAME: {
			r_dst = a;
		}
			return;
		case DICTIONARY: {
		}
			return;
		case ARRAY: {
			r_dst = a;
		}
			return;
		case POOL_BYTE_ARRAY: {
			r_dst = a;
		}
			return;
		case POOL_INT_ARRAY: {
			const PoolVector<int> *arr_a = reinterpret_cast<const PoolVector<int> *>(a._data._mem);
			const PoolVector<int> *arr_b = reinterpret_cast<const PoolVector<int> *>(b._data._mem);
			int sz = arr_a->size();
			if (sz == 0 || arr_b->size() != sz) {
				r_dst = a;
			} else {
				PoolVector<int> v;
				v.resize(sz);
				{
					PoolVector<int>::Write vw = v.write();
					PoolVector<int>::Read ar = arr_a->read();
					PoolVector<int>::Read br = arr_b->read();

					Variant va;
					for (int i = 0; i < sz; i++) {
						Variant::interpolate(ar[i], br[i], c, va);
						vw[i] = va;
					}
				}
				r_dst = v;
			}
		}
			return;
		case POOL_REAL_ARRAY: {
			const PoolVector<real_t> *arr_a = reinterpret_cast<const PoolVector<real_t> *>(a._data._mem);
			const PoolVector<real_t> *arr_b = reinterpret_cast<const PoolVector<real_t> *>(b._data._mem);
			int sz = arr_a->size();
			if (sz == 0 || arr_b->size() != sz) {
				r_dst = a;
			} else {
				PoolVector<real_t> v;
				v.resize(sz);
				{
					PoolVector<real_t>::Write vw = v.write();
					PoolVector<real_t>::Read ar = arr_a->read();
					PoolVector<real_t>::Read br = arr_b->read();

					Variant va;
					for (int i = 0; i < sz; i++) {
						Variant::interpolate(ar[i], br[i], c, va);
						vw[i] = va;
					}
				}
				r_dst = v;
			}
		}
			return;
		case POOL_STRING_ARRAY: {
			r_dst = a;
		}
			return;
		default: {
			r_dst = a;
		}
	}
}

static const char *_op_names[Variant::OP_MAX] = {
	"==",
	"!=",
	"<",
	"<=",
	">",
	">=",
	"+",
	"-",
	"*",
	"/",
	"- (negation)",
	"+ (positive)",
	"%",
	"+ (concatenation)",
	"<<",
	">>",
	"&",
	"|",
	"^",
	"~",
	"and",
	"or",
	"xor",
	"not",
	"in"

};

String Variant::get_operator_name(Operator p_op) {
	ERR_FAIL_INDEX_V(p_op, OP_MAX, "");
	return _op_names[p_op];
}

#undef CASE_TYPE_ALL
#undef CASE_TYPE_ALL_BUT_INT
#undef TYPE
#undef TYPES
#undef CASES
#undef SWITCH
#undef SWITCH_OP
#undef CASE_TYPE
#undef CASES
#undef SWITCH
#undef SWITCH_OP
#undef CASE_TYPE
#undef _RETURN
#undef _RETURN_FAIL
#undef DEFAULT_OP_NUM
#undef DEFAULT_OP_NUM_NULL
#undef DEFAULT_OP_NUM_DIV
#undef DEFAULT_OP_NUM_DIV
#undef DEFAULT_OP_NUM_NEG
#undef DEFAULT_OP_NUM_POS
#undef DEFAULT_OP_NUM_VEC
#undef DEFAULT_OP_STR_REV
#undef DEFAULT_OP_STR
#undef DEFAULT_OP_STR_NULL
#undef DEFAULT_OP_STR_NULL_NP
#undef DEFAULT_OP_STR_NULL_SN
#undef DEFAULT_OP_LOCALMEM_REV
#undef DEFAULT_OP_LOCALMEM
#undef DEFAULT_OP_LOCALMEM_NULL
#undef DEFAULT_OP_LOCALMEM_NEG
#undef DEFAULT_OP_LOCALMEM_POS
#undef DEFAULT_OP_LOCALMEM_NUM
#undef DEFAULT_OP_PTR
#undef DEFAULT_OP_PTRREF
#undef DEFAULT_OP_PTRREF_NULL
#undef DEFAULT_OP_ARRAY_EQ
#undef DEFAULT_OP_ARRAY_NEQ
#undef DEFAULT_OP_ARRAY_LT
#undef DEFAULT_OP_ARRAY_GT
#undef DEFAULT_OP_ARRAY_OP
#undef DEFAULT_OP_ARRAY_OP_BODY
#undef DEFAULT_OP_ARRAY_ADD
#undef DEFAULT_OP_ARRAY_CMD
#undef DEFAULT_OP_DVECTOR_SET
#undef DEFAULT_OP_DVECTOR_GET
#line 0

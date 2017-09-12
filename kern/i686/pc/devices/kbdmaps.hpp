/*
kbdmaps.hpp

Copyright (c) 28 Yann BOUCHER (yann)

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
#ifndef KBDMAPS_HPP
#define KBDMAPS_HPP

#include <stdint.h>

static constexpr uint8_t kbdmap_us[] = {
    0x1B, 0x1B, 0x1B, 0x1B,	/*      esc     (0x01)  */
    '1', '!', '1', '1',
    '2', '@', '2', '2',
    '3', '#', '3', '3',
    '4', '$', '4', '4',
    '5', '%', '5', '5',
    '6', '^', '6', '6',
    '7', '&', '7', '7',
    '8', '*', '8', '8',
    '9', '(', '9', '9',
    '0', ')', '0', '0',
    '-', '_', '-', '-',
    '=', '+', '=', '=',
    0x08, 0x08, 0x7F, 0x08,	/*      backspace       */
    0x09, 0x09, 0x09, 0x09,	/*      tab     */
    'q', 'Q', 'q', 'q',
    'w', 'W', 'w', 'w',
    'e', 'E', 'e', 'e',
    'r', 'R', 'r', 'r',
    't', 'T', 't', 't',
    'y', 'Y', 'y', 'y',
    'u', 'U', 'u', 'u',
    'i', 'I', 'i', 'i',
    'o', 'O', 'o', 'o',
    'p', 'P', 'p', 'p',
    '[', '{', '[', '[',
    ']', '}', ']', ']',
    0x0A, 0x0A, 0x0A, 0x0A,	/*      enter   */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      ctrl    */
    'a', 'A', 'a', 'a',
    's', 'S', 's', 's',
    'd', 'D', 'd', 'd',
    'f', 'F', 'f', 'f',
    'g', 'G', 'g', 'g',
    'h', 'H', 'h', 'h',
    'j', 'J', 'j', 'j',
    'k', 'K', 'k', 'k',
    'l', 'L', 'l', 'l',
    ';', ':', ';', ';',
    0x27, 0x22, 0x27, 0x27,	/*      '"      */
    '`', '~', '`', '`',	/*      `~      */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      Lshift  (0x2a)  */
    '\\', '|', '\\', '\\',
    'z', 'Z', 'z', 'z',
    'x', 'X', 'x', 'x',
    'c', 'C', 'c', 'c',
    'v', 'V', 'v', 'v',
    'b', 'B', 'b', 'b',
    'n', 'N', 'n', 'n',
    'm', 'M', 'm', 'm',
    0x2C, 0x3C, 0x2C, 0x2C,	/*      ,<      */
    0x2E, 0x3E, 0x2E, 0x2E,	/*      .>      */
    0x2F, 0x3F, 0x2F, 0x2F,	/*      /?      */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      Rshift  (0x36)  */
    '*',  '*',  '*',  '*',	/*      (0x37)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x38)  */
    ' ',  ' ',  ' ',  ' ',	/*      space   */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3a)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3b)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3c)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3d)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3e)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3f)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x40)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x41)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x42)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x43)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x44)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x45)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x46)  */
    '7',  '7', 0xFF, 0xFF,	/*      (0x47)  */
    '8',  '8', 0xFF, 0xFF,	/*      (0x48)  */
    '9',  '9', 0xFF, 0xFF,	/*      (0x49)  */
    '-',  '-',  '-',  '-',	/*      (0x4a)  */
    '4',  '4', 0xFF, 0xFF,	/*      (0x4b)  */
    '5',  '5', 0xFF, 0xFF,	/*      (0x4c)  */
    '6',  '6', 0xFF, 0xFF,	/*      (0x4d)  */
    '+',  '+',  '+',  '+',	/*      (0x4e)  */
    '1',  '1', 0xFF, 0xFF,	/*      (0x4f)  */
    '2',  '2', 0xFF, 0xFF,	/*      (0x50)  */
    '3',  '3', 0xFF, 0xFF,	/*      (0x51)  */
    '0',  '0', 0xFF, 0xFF,	/*      (0x52)  */
    '.',  '.', 0xFF, 0xFF,	/*      (0x53)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x54)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x55)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x56)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x57)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x58)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x59)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5a)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5b)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5c)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5d)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5e)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5f)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x60)  */
    0xFF, 0xFF, 0xFF, 0xFF	/*      (0x61)  */
};

// normal, caps, alt, numlock
static constexpr uint8_t kbdmap_fr[] = {
    0x1B, 0x1B, 0x1B, 0x1B,	/*      esc     (0x01)  */
    '&', '1', 0xFB, '&',
    0x82, '2', '~',0x82,
    '"', '3', '#', '"',
    '\'', '4', '{', '\'',
    '(', '5', '[', '(',
    '-', '6', '|', '-',
    0x8A, '7', '`',0x8A,
    '_', '8', '\\', '_',
    0x87, '9', '^', 0x87,
    0x85, '0', '@', 0x85,
    ')',0xF8, ']', ')',
    '=', '+', '}', '=',
    0x08, 0x08, 0x7F, 0x08,	/*      backspace       */
    0x09, 0x09, 0x09, 0x09,	/*      tab     */
    'a', 'A', 'a', 'a',
    'z', 'Z', 'z', 'z',
    'e', 'E', 'e', 'e',
    'r', 'R', 'r', 'r',
    't', 'T', 't', 't',
    'y', 'Y', 'y', 'y',
    'u', 'U', 'u', 'u',
    'i', 'I', 'i', 'i',
    'o', 'O', 'o', 'o',
    'p', 'P', 'p', 'p',
    '^',0xF9, '^', '^',
    '$', 156, '$', '$',
    '\n', '\n', '\n','\n',	/*      enter   */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      ctrl    */
    'q', 'Q', 'q', 'q',
    's', 'S', 's', 's',
    'd', 'D', 'd', 'd',
    'f', 'F', 'f', 'f',
    'g', 'G', 'g', 'g',
    'h', 'H', 'h', 'h',
    'j', 'J', 'j', 'j',
    'k', 'K', 'k', 'k',
    'l', 'L', 'l', 'l',
    'm', 'M', 'm', 'm',
    0x97, '%',0x97,0x97,	/*      '"      */
    0xFD, '~',0xAA, '`',	/*      `~      */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      Lshift  (0x2a)  */
    '*',0xE6, '*', '*',
    'w', 'W', 'w', 'w',
    'x', 'X', 'x', 'x',
    'c', 'C', 'c', 'c',
    'v', 'V', 'v', 'v',
    'b', 'B', 'b', 'b',
    'n', 'N', 'n', 'n',
    ',', '?', ',', ',',
    ';', '.', ';', ';',	/*      ,<      */
    ':', '/', ':', ':',	/*      .>      */
    '!',0xF5, '!', '!',	/*      /?      */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      Rshift  (0x36)  */
    '*',  '*',  '*',  '*',	/*      (0x37)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x38)  */
    ' ',  ' ',  ' ',  ' ',	/*      space   */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3a)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3b)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3c)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3d)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3e)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x3f)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x40)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x41)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x42)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x43)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x44)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x45)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x46)  */
    '7',  '7', 0xFF, 0xFF,	/*      (0x47)  */
    '8',  '8', 0xFF, 0xFF,	/*      (0x48)  */
    '9',  '9', 0xFF, 0xFF,	/*      (0x49)  */
    '-',  '-',  '-',  '-',	/*      (0x4a)  */
    '4',  '4', 0xFF, 0xFF,	/*      (0x4b)  */
    '5',  '5', 0xFF, 0xFF,	/*      (0x4c)  */
    '6',  '6', 0xFF, 0xFF,	/*      (0x4d)  */
    '+',  '+',  '+',  '+',	/*      (0x4e)  */
    '1',  '1', 0xFF, 0xFF,	/*      (0x4f)  */
    '2',  '2', 0xFF, 0xFF,	/*      (0x50)  */
    '3',  '3', 0xFF, 0xFF,	/*      (0x51)  */
    '0',  '0', 0xFF, 0xFF,	/*      (0x52)  */
    '.',  '.', 0xFF, 0xFF,	/*      (0x53)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x54)  */
    0xFF, 0xFF, 0xFF, 0xFF,/*      (0x55)  */
    '<',   '>',  '|',  '<',	/*      (0x56)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x57)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x58)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x59)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5a)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5b)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5c)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5d)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5e)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x5f)  */
    0xFF, 0xFF, 0xFF, 0xFF,	/*      (0x60)  */
    0xFF, 0xFF, 0xFF, 0xFF	/*      (0x61)  */
};

#endif // KBDMAPS_HPP

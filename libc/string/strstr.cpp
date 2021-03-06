/*
strstr.cpp

Copyright (c) 24 Yann BOUCHER (yann)

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

#include <string.h>

const char* strstr( const char* s1, const char* s2 )
{
    int i, j;
    int flag = 0;

    if ((s2 == nullptr || s1 == nullptr)) return nullptr;

    for( i = 0; s2[i] != '\0'; i++)
    {
        if (s2[i] == s1[0])
        {
            for (j = i; ; j++)
            {
                if (s1[j-i] == '\0'){ flag = 1; break;}
                if (s2[j] == s1[j-i]) continue;
                else break;
            }
        }
        if (flag == 1) break;
    }

    if (flag) return (s2+i);
    else return nullptr;
}

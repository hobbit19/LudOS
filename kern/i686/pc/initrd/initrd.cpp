/*
get_initrd.cpp

Copyright (c) 04 Yann BOUCHER (yann)

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

#include "initrd/initrd.hpp"

#include "i686/pc/multiboot/multiboot_kern.hpp"
#include "drivers/storage/diskinterface.hpp"
#include "fs/vfs.hpp"

#include <string.hpp>

std::vector<uint8_t> initrd_buffer;

std::optional<size_t> get_initrd_disk()
{
    for (auto module : multiboot::get_modules())
    {
        auto str = std::string(reinterpret_cast<const char*>(module.cmdline));
        auto tokens = tokenize(str, " ", true);
        if (tokens.back() == "initrd")
        {
            return DiskInterface::add_memory_drive(reinterpret_cast<const void*>(module.mod_start),
                                                   (module.mod_end - module.mod_start));
        }
    }

    return {};
}

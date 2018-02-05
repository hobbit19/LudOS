
/*
messagebus.tpp

Copyright (c) 23 Yann BOUCHER (yann)

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

#include "messagebus.hpp"

#include "utils/vecutils.hpp"

template <typename T>
MessageBus::Handle MessageBus::register_handler(std::function<void(const T&)> handler, Priority prio)
{
    handlers[std::type_index(typeid(T))].push_back(Entry<T>{handler, prio});
    return {std::type_index(typeid(T)), --handlers[std::type_index(typeid(T))].end()};
}

template <typename T>
size_t MessageBus::send(const T& event)
{
    size_t counter { 0 };
    std::vector<std::any> late_callbacks;
    for (const auto& callback : handlers[std::type_index(typeid(T))])
    {
        ++counter;
        if (std::any_cast<Entry<T>>(callback).priority == Priority::Last)
        {
            late_callbacks.emplace_back(callback);
        }
        else
        {
            std::any_cast<Entry<T>>(callback).handler(event);
        }
    }

    for (const auto& late_callback : late_callbacks)
    {
        std::any_cast<Entry<T>>(late_callback).handler(event);
    }

    return counter;
}

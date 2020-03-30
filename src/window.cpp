//
// Created by bear on 3/29/20.
//

#include "window.h"

Window::Window(const std::shared_ptr<WL::Display> &display, int width, int height) :
    display(display), width(width), height(height)
{

}

/**
 * @file Window.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "YAE/Window.h"
#include "YAE/Application.h"

namespace YAE 
{
    Window::Window(const Rect& frameRect, Window::Style styleMask) 
    {
        ::Display* display = mDpy = Application::Current().display();
        int screen = Application::Current().defaultScreen();
        unsigned long foreground = BlackPixel(display, screen);
        unsigned long background = WhitePixel(display, screen);

        mHandle = XCreateSimpleWindow(display, RootWindow(display, screen), 
                                      frameRect.origin.x,
                                      frameRect.origin.y,
                                      frameRect.size.width,
                                      frameRect.size.height, 
                                      5, 
                                      foreground, background);
        
        mGC = XCreateGC(display, mHandle, 0, 0);
        XSetBackground(display, mGC, background);
        XSetForeground(display, mGC, foreground);

        XSelectInput(display, mHandle, ButtonPressMask|KeyPressMask|ExposureMask);
    }

    Window::~Window() 
    {
        XFreeGC(Application::Current().display(), mGC);
        XDestroyWindow(Application::Current().display(), mHandle);
    }

    void Window::show() 
    {
        XMapRaised(mDpy, mHandle);
    }

    void Window::close() 
    {
        Atom WM_DELETE_WINDOW = XInternAtom(mDpy, "WM_DELETE_WINDOW", False);

        XEvent event;
        event.xclient.display = mDpy;
        event.xclient.window = mHandle;
        event.xclient.type = ClientMessage;
        event.xclient.message_type = WM_DELETE_WINDOW;

        XSendEvent(mDpy, mHandle, True, NoEventMask, &event);
    }
}
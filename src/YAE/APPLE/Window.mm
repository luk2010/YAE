/**
 * @file APPLE/Window.h
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-11-09
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "YAE/Window.h"

@interface CustomWindow : NSWindow
@property (nonatomic, assign) YAE::Window* window;
@end

@interface WindowDel : NSObject < NSWindowDelegate >
@property (nonatomic, assign) YAE::Window* window;
@end

@implementation CustomWindow

@synthesize window;

@end

@implementation WindowDel

@synthesize window;

- (void)windowWillClose:(NSNotification *)notification
{
    self.window->beforeClose();
}

@end

namespace YAE
{
    Window::Window(const Rect& frameRect, Style style)
    {
        WindowDel* delegate = mDelegateHandle = [[WindowDel alloc] init];
        [delegate setWindow:this];
        
        CustomWindow* window = mHandle = [[CustomWindow alloc] initWithContentRect:Rect::ToCGRect(frameRect)
                                                                         styleMask:(NSWindowStyleMask)style
                                                                           backing:NSBackingStoreBuffered
                                                                             defer:NO];
        [window setWindow:this];
        [window setDelegate:delegate];
    }
    
    void Window::show()
    {
        [mHandle makeKeyAndOrderFront:nil];
    }
    
    void Window::close()
    {
        [mHandle performClose:nil];
    }
}

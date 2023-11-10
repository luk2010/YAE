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

- (void)windowDidResize:(NSNotification *)notification
{
    NSWindow* window = self.window->handle();
    NSSize size = window.frame.size;
    
    auto view = self.window->contentView();
    if (view)
        view->setFrame({ {}, YAE::Size::FromCGSize(window.contentLayoutRect.size) });
    
    self.window->resized(YAE::Size{ size.width, size.height });
}

- (void)windowDidUpdate:(NSNotification *)notification
{
    auto view = self.window->contentView();
    if (view)
        view->update();
}

@end

namespace YAE
{
    static NSWindowStyleMask StyleToNS(Window::Style rhs)
    {
        NSWindowStyleMask mask = 0;
        if (rhs & Window::Closable) mask |= NSWindowStyleMaskClosable;
        if (rhs & Window::Resizable) mask |= NSWindowStyleMaskResizable;
        if (rhs & Window::Titled) mask |= NSWindowStyleMaskTitled;
        return mask;
    }
    
    static Window::Style StyleFromNS(NSWindowStyleMask rhs)
    {
        int mask = (Window::Style) 0;
        if (rhs & NSWindowStyleMaskClosable) mask |= Window::Closable;
        if (rhs & NSWindowStyleMaskResizable) mask |= Window::Resizable;
        if (rhs & NSWindowStyleMaskTitled) mask |= Window::Titled;
        return (Window::Style) mask;
    }
    
    Window::Window(const Rect& frameRect, Style style)
    {
        WindowDel* delegate = mDelegateHandle = [[WindowDel alloc] init];
        [delegate setWindow:this];
        
        CustomWindow* window = (CustomWindow*)(
        mHandle = [[CustomWindow alloc] initWithContentRect:Rect::ToCGRect(frameRect)
                                                  styleMask:StyleToNS(style)
                                                    backing:NSBackingStoreBuffered
                                                      defer:NO]);
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
    
    Rect Window::frame() const
    {
        return Rect::FromCGRect(mHandle.frame);
    }
    
    void Window::setFrame(const Rect& rect)
    {
        [mHandle setFrame:Rect::ToCGRect(rect) display:YES animate:YES];
    }
    
    Size Window::contentSize() const
    {
        return Size::FromCGSize(mHandle.contentLayoutRect.size);
    }
    
    void Window::setContentSize(const Size& size)
    {
        [mHandle setContentSize:Size::ToCGSize(size)];
    }
    
    std::string_view Window::title() const
    {
        return mHandle.title.UTF8String;
    }
    
    void Window::setTitle(const std::string_view& title)
    {
        [mHandle setTitle:[NSString stringWithUTF8String:title.data()]];
    }
    
    void Window::setContentView(const Ref < View >& view)
    {
        mContentView = view;
        
        if (view) {
            mHandle.contentView = view->handle();
            mContentView->setFrame({ {}, contentSize() });
        }
        else
            mHandle.contentView = nil;
    }
}

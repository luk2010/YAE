/**
 * @file main.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include <YAE/YAE.h>

class HeaderView : public YAE::View
{
public:
    
    HeaderView()
    {
        setBackgroundColor({ 0.4, 0.3, 0.2, 1.0 });
    }
};

class ContentView : public YAE::View
{
public:
    
    ContentView()
    {
        setBackgroundColor({ 0.3, 0.2, 1.0, 1.0 });
    }
};

class MainView : public YAE::View
{
    YAE::Ref < HeaderView > mHeader;
    YAE::Ref < ContentView > mContent;
    
public:
    
    MainView(const YAE::Rect& frameRect = YAE::Rect()):
    YAE::View(frameRect)
    {
        setBackgroundColor({ 0.2, 0.3, 0.4, 1.0 });
    }
    
YAE_EVENTS:
    
    void layoutChildren()
    {
        std::cout << "MainView: layouting..." << std::endl;
        
        YAE::Rect frameRect = frame();
        frameRect.origin = {};
        
        YAE::Rect childFrame = frameRect;
        childFrame.size.height = 60;
        
        mHeader->setFrame(childFrame);
    
        childFrame.origin.y = 60;
        childFrame.size.height = frameRect.size.height - 60;
    
        mContent->setFrame(childFrame);
    }
    
    void didAttach()
    {
        mHeader = YAE::Make < HeaderView >();
        mContent = YAE::Make < ContentView >();
        
        addChild(mHeader);
        addChild(mContent);
    }
};

class MainWin : public YAE::Window
{
public:
    
    using YAE::Window::Window;
    
YAE_EVENTS:
    
    void beforeClose()
    {
        YAE::Application::Current().terminate();
    }
    
    void resized(const YAE::Size& size)
    {
        std::cout << "Window resized: " << size.width << "/" << size.height << std::endl;
    }
};

class App : public YAE::Application 
{
    YAE::Ref < YAE::Window > mWindow;
    
YAE_EVENTS:
    
    void ready()
    {
        mWindow = YAE::Make < MainWin >(YAE::Rect{
            {}, { 1024, 768 }
        });
        
        mWindow->setTitle("Window Title here!");
        mWindow->setContentView(YAE::Make < MainView >());
        mWindow->show();
    }
};

int main() 
{
    return App().run();
}

/**
 * @file View.mm
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-11-10
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "YAE/View.h"

@interface CustomView : NSView
@property (nonatomic, assign) YAE::View* view;
@end

@implementation CustomView

@synthesize view;

- (instancetype) initWithFrame:(NSRect)frameRect
{
    self = [super initWithFrame:frameRect];
    
    if (self) {
        self.wantsLayer = YES;
    }
    
    return self;
}

- (BOOL)isFlipped
{
    return YES;
}


@end

namespace YAE
{
    id View::setHandle(id handle)
    {
        NSView* old = mHandle;
        mHandle = (NSView*) handle;
        return old;
    }
    
    View::View(const Rect& frameRect):
    mHandle(nil)
    {
        CustomView* view = (CustomView*)(
        mHandle = [[CustomView alloc] initWithFrame:Rect::ToCGRect(frameRect)]);
        view.view = this;
    }
    
    View::~View()
    {
        mHandle = nil;
    }
    
    Rect View::frame() const
    {
        return Rect::FromCGRect(mHandle.frame);
    }
    
    void View::setFrame(const Rect& frameRect)
    {
        [mHandle setFrame:Rect::ToCGRect(frameRect)];
        setNeedsLayout(true);
    }
    
    Ref < View > View::addChild(const Ref < View >& child, const Ref < View >& beforeHint)
    {
        if (!child)
            return nullptr;
        
        if (!shouldAddChild(*child))
            return nullptr;
        
        [mHandle addSubview:child->handle()
                 positioned:NSWindowBelow
                 relativeTo:beforeHint ? beforeHint->handle() : nil];
        
        auto it = std::find(mChildren.begin(), mChildren.end(), beforeHint);
        mChildren.insert(it, child);
        
        child->mParent = shared_from_this();
        child->didAttach();
        
        didAddChild(*child);
        setNeedsLayout(true);

        return child;
    }
    
    void View::update()
    {
        if (mNeedsLayout.exchange(false))
            layoutChildren();
        
        for (auto& child : mChildren)
            child->update();
    }
    
    Color View::backgroundColor() const
    {
        return Color::FromNSColor([NSColor colorWithCGColor:mHandle.layer.backgroundColor]);
    }
    
    void View::setBackgroundColor(const Color& color)
    {
        mHandle.layer.backgroundColor = Color::ToNSColor(color).CGColor;
    }
}

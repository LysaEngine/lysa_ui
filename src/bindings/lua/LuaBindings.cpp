/*
* Copyright (c) 2025-present Henri Michelon
*
* This software is released under the MIT License.
* https://opensource.org/licenses/MIT
*/
module;
extern "C" {
    #define LUA_LIB
    #include "lua.h"
}
module lysa.ui.lua;

import std;
import lysa;
import lysa.ui;

namespace lysa::ui {

    void LuaBindings::_register(lua_State* L) {
        if (registered) return;
        registered = true;
        luabridge::getGlobalNamespace(L).beginNamespace("lysa")
        .beginClass<ResourcesRegistry>("ResourcesRegistry")
            .addProperty("window_manager",
               +[](const ResourcesRegistry* rl) -> WindowManager& {
               return rl->get<WindowManager>();
           })
        .endClass()

        .beginNamespace("ui")

        .beginNamespace("Alignment")
            .addVariable("NONE",              Alignment::NONE)
            .addVariable("FILL",              Alignment::FILL)
            .addVariable("CENTER",            Alignment::CENTER)
            .addVariable("HCENTER",           Alignment::HCENTER)
            .addVariable("VCENTER",           Alignment::VCENTER)
            .addVariable("TOP",               Alignment::TOP)
            .addVariable("BOTTOM",            Alignment::BOTTOM)
            .addVariable("LEFT",              Alignment::LEFT)
            .addVariable("RIGHT",             Alignment::RIGHT)
            .addVariable("TOPCENTER",         Alignment::TOPCENTER)
            .addVariable("BOTTOMCENTER",      Alignment::BOTTOMCENTER)
            .addVariable("LEFTCENTER",        Alignment::LEFTCENTER)
            .addVariable("RIGHTCENTER",       Alignment::RIGHTCENTER)
            .addVariable("TOPLEFT",           Alignment::TOPLEFT)
            .addVariable("BOTTOMLEFT",        Alignment::BOTTOMLEFT)
            .addVariable("BOTTOMRIGHT",       Alignment::BOTTOMRIGHT)
            .addVariable("TOPRIGHT",          Alignment::TOPRIGHT)
            .addVariable("LEFTTOP",           Alignment::LEFTTOP)
            .addVariable("LEFTBOTTOM",        Alignment::LEFTBOTTOM)
            .addVariable("RIGHTBOTTOM",       Alignment::RIGHTBOTTOM)
            .addVariable("RIGHTTOP",          Alignment::RIGHTTOP)
            .addVariable("CORNERTOPLEFT",     Alignment::CORNERTOPLEFT)
            .addVariable("CORNERTOPRIGHT",    Alignment::CORNERTOPRIGHT)
            .addVariable("CORNERBOTTOMLEFT",  Alignment::CORNERBOTTOMLEFT)
            .addVariable("CORNERBOTTOMRIGHT", Alignment::CORNERBOTTOMRIGHT)
        .endNamespace()

        .beginNamespace("WidgetType")
            .addVariable("WIDGET",       Widget::WIDGET)
            .addVariable("PANEL",        Widget::PANEL)
            .addVariable("BOX",          Widget::BOX)
            .addVariable("LINE",         Widget::LINE)
            .addVariable("FRAME",        Widget::FRAME)
            .addVariable("BUTTON",       Widget::BUTTON)
            .addVariable("TOGGLEBUTTON", Widget::TOGGLEBUTTON)
            .addVariable("TEXT",         Widget::TEXT)
            .addVariable("TEXTEDIT",     Widget::TEXTEDIT)
            .addVariable("SCROLLBAR",    Widget::SCROLLBAR)
            .addVariable("TREEVIEW",     Widget::TREEVIEW)
            .addVariable("IMAGE",        Widget::IMAGE)
        .endNamespace()

        .beginNamespace("CheckState")
            .addVariable("UNCHECK", CheckWidget::UNCHECK)
            .addVariable("CHECK",   CheckWidget::CHECK)
        .endNamespace()

        .beginNamespace("LineStyle")
            .addVariable("HORIZ", Line::HORIZ)
            .addVariable("VERT",  Line::VERT)
        .endNamespace()

        .beginNamespace("ScrollBarType")
            .addVariable("HORIZONTAL", ScrollBar::HORIZONTAL)
            .addVariable("VERTICAL",   ScrollBar::VERTICAL)
        .endNamespace()

        .beginNamespace("ResizeableBorder")
            .addVariable("NONE",   Window::RESIZEABLE_NONE)
            .addVariable("LEFT",   Window::RESIZEABLE_LEFT)
            .addVariable("RIGHT",  Window::RESIZEABLE_RIGHT)
            .addVariable("TOP",    Window::RESIZEABLE_TOP)
            .addVariable("BOTTOM", Window::RESIZEABLE_BOTTOM)
        .endNamespace()

        .beginNamespace("UIEvent")
            .addVariable("OnCreate",      &UIEvent::OnCreate)
            .addVariable("OnDestroy",     &UIEvent::OnDestroy)
            .addVariable("OnKeyDown",     &UIEvent::OnKeyDown)
            .addVariable("OnKeyUp",       &UIEvent::OnKeyUp)
            .addVariable("OnMouseDown",   &UIEvent::OnMouseDown)
            .addVariable("OnMouseUp",     &UIEvent::OnMouseUp)
            .addVariable("OnMouseMove",   &UIEvent::OnMouseMove)
            .addVariable("OnGotFocus",    &UIEvent::OnGotFocus)
            .addVariable("OnLostFocus",   &UIEvent::OnLostFocus)
            .addVariable("OnShow",        &UIEvent::OnShow)
            .addVariable("OnHide",        &UIEvent::OnHide)
            .addVariable("OnEnable",      &UIEvent::OnEnable)
            .addVariable("OnDisable",     &UIEvent::OnDisable)
            .addVariable("OnTextChange",  &UIEvent::OnTextChange)
            .addVariable("OnTextInput",   &UIEvent::OnTextInput)
            .addVariable("OnClick",       &UIEvent::OnClick)
            .addVariable("OnStateChange", &UIEvent::OnStateChange)
            .addVariable("OnValueChange", &UIEvent::OnValueChange)
            .addVariable("OnRangeChange", &UIEvent::OnRangeChange)
            .addVariable("OnResize",      &UIEvent::OnResize)
            .addVariable("OnMove",        &UIEvent::OnMove)
        .endNamespace()

        .beginClass<Widget>("Widget")
            .addProperty("type",                 &Widget::getType)
            .addFunction("is_visible",           &Widget::isVisible)
            .addFunction("show",
                +[](Widget* self, bool v = true){ self->show(v); })
            .addFunction("is_enabled",           &Widget::isEnabled)
            .addFunction("enable",
                +[](Widget* self, bool v = true){ self->enable(v); })
            .addFunction("set_pos",              &Widget::setPos)
            .addProperty("width",                &Widget::getWidth)
            .addProperty("height",               &Widget::getHeight)
            .addFunction("set_size",             &Widget::setSize)
            .addProperty("rect",
                &Widget::getRect,
                static_cast<void(Widget::*)(const Rect&)>(&Widget::setRect))
            .addFunction("set_rect",
                luabridge::overload<float, float, float, float>(&Widget::setRect))
            .addProperty("alignment",            &Widget::getAlignment, &Widget::setAlignment)
            .addProperty("font",                 &Widget::getFont, &Widget::setFont)
            .addProperty("font_scale",           &Widget::getFontScale, &Widget::setFontScale)
            .addProperty("is_focused",           &Widget::isFocused)
            .addProperty("parent",               &Widget::getParent)
            .addFunction("remove",               &Widget::remove)
            .addFunction("remove_all",           &Widget::removeAll)
            .addProperty("padding",              &Widget::getPadding, &Widget::setPadding)
            .addProperty("vborder",              &Widget::getVBorder, &Widget::setVBorder)
            .addProperty("hborder",              &Widget::getHBorder, &Widget::setHBorder)
            .addProperty("is_draw_background",   &Widget::isDrawBackground, &Widget::setDrawBackground)
            .addProperty("is_pushed",            &Widget::isPushed, &Widget::setPushed)
            .addProperty("is_pointed",           &Widget::isPointed)
            .addProperty("is_freezed",           &Widget::isFreezed, &Widget::setFreezed)
            .addProperty("is_overlapping",       &Widget::isOverlapping)
            .addProperty("children_rect",        &Widget::getChildrenRect)
            .addFunction("refresh",              &Widget::refresh)
            .addProperty("group_index",          &Widget::getGroupIndex, &Widget::setGroupIndex)
            .addProperty("transparency",         &Widget::getTransparency, &Widget::setTransparency)
            .addFunction("resize_children",      &Widget::resizeChildren)
            // add_child: expose the non-template path via a lambda taking a shared_ptr<Widget>
            .addFunction("add_child",
                +[](Widget* self,
                    const std::shared_ptr<Widget>& child,
                    Alignment alignment,
                    const std::string& resource = "") -> std::shared_ptr<Widget> {
                    return self->add(child, alignment, resource);
                })
        .endClass()

        .deriveClass<Panel, Widget>("Panel")
            .addConstructor<void()>()
        .endClass()

        .deriveClass<Box, Panel>("Box")
            .addConstructor<void()>()
        .endClass()

        .deriveClass<Button, Box>("Button")
            .addConstructor<void()>()
        .endClass()

        // -----------------------------------------------------------------
        // CheckWidget : Widget  (abstract – expose state methods)
        // -----------------------------------------------------------------
        .deriveClass<CheckWidget, Widget>("CheckWidget")
            .addProperty("state", &CheckWidget::getState, &CheckWidget::setState)
        .endClass()

        // -----------------------------------------------------------------
        // ToggleButton : CheckWidget
        // -----------------------------------------------------------------
        .deriveClass<ToggleButton, CheckWidget>("ToggleButton")
            .addConstructor<void()>()
        .endClass()

        // -----------------------------------------------------------------
        // Line : Widget
        // -----------------------------------------------------------------
        .deriveClass<Line, Widget>("Line")
            .addConstructor<void(Line::LineStyle)>()
            .addProperty("style", &Line::getStyle, &Line::setStyle)
        .endClass()

        .deriveClass<HLine, Line>("HLine")
            .addConstructor<void()>()
        .endClass()

        .deriveClass<VLine, Line>("VLine")
            .addConstructor<void()>()
        .endClass()

        // -----------------------------------------------------------------
        // Frame : Panel
        // -----------------------------------------------------------------
        .deriveClass<Frame, Panel>("Frame")
            .addConstructor<void(const std::string&)>()
            .addProperty("title",       &Frame::getTitle, &Frame::setTitle)
            .addProperty("title_color", &Frame::getTitleColor, &Frame::setTitleColor)
        .endClass()

        // -----------------------------------------------------------------
        // Text : Widget
        // -----------------------------------------------------------------
        .deriveClass<Text, Widget>("Text")
            .addConstructor<void(), void(const std::string&)>()
            .addProperty("text",       &Text::getText, &Text::setText)
            .addProperty("text_color", &Text::getTextColor, &Text::setTextColor)
            .addFunction("get_size",
                +[](const Text* self) -> std::pair<float, float> {
                    float w = 0, h = 0;
                    self->getSize(w, h);
                    return {w, h};
                })
        .endClass()

        // -----------------------------------------------------------------
        // TextEdit : Widget
        // -----------------------------------------------------------------
        .deriveClass<TextEdit, Widget>("TextEdit")
            .addConstructor<void(), void(const std::string&)>()
            .addProperty("is_read_only",             &TextEdit::isReadOnly, &TextEdit::setReadOnly)
            .addProperty("text",                     &TextEdit::getText, &TextEdit::setText)
            .addProperty("sel_start",                &TextEdit::getSelStart, &TextEdit::setSelStart)
            .addProperty("first_displayed_char",     &TextEdit::getFirstDisplayedChar)
            .addProperty("displayed_text",           &TextEdit::getDisplayedText)
            .addFunction("set_resources",            &TextEdit::setResources)
        .endClass()

        // -----------------------------------------------------------------
        // Image : Widget
        // -----------------------------------------------------------------
        .deriveClass<Image, Widget>("Image")
            .addConstructor<
                void(),
                void(bool),
                void(const lysa::Image&, bool)
            >()
            .addFunction("set_auto_size", &Image::setAutoSize)
            .addProperty("color",         &Image::getColor, &Image::setColor)
            .addProperty("image",         &Image::getImage, &Image::setImage)
        .endClass()

        // -----------------------------------------------------------------
        // ValueSelect : Widget  (abstract base)
        // -----------------------------------------------------------------
        .deriveClass<ValueSelect, Widget>("ValueSelect")
            .addProperty("min",   &ValueSelect::getMin, &ValueSelect::setMin)
            .addProperty("max",   &ValueSelect::getMax, &ValueSelect::setMax)
            .addProperty("value", &ValueSelect::getValue, &ValueSelect::setValue)
            .addProperty("step",  &ValueSelect::getStep, &ValueSelect::setStep)
        .endClass()

        // -----------------------------------------------------------------
        // ScrollBar : ValueSelect
        // -----------------------------------------------------------------
        .deriveClass<ScrollBar, ValueSelect>("ScrollBar")
            .addConstructor<
                void(),
                void(ScrollBar::Type, float, float, float, float)
            >()
            .addProperty("scroll_bar_type",     &ScrollBar::getScrollBarType)
            .addFunction("set_resources",       &ScrollBar::setResources)
        .endClass()

        .deriveClass<VScrollBar, ScrollBar>("VScrollBar")
            .addConstructor<void(), void(float, float, float, float)>()
        .endClass()

        .deriveClass<HScrollBar, ScrollBar>("HScrollBar")
            .addConstructor<void(), void(float, float, float, float)>()
        .endClass()

        // -----------------------------------------------------------------
        // TreeView::Item : Panel
        // -----------------------------------------------------------------
        .deriveClass<TreeView::Item, Panel>("TreeViewItem")
            .addProperty("item",     &TreeView::Item::item)
            .addProperty("level",    &TreeView::Item::level)
            .addProperty("selected", &TreeView::Item::selected)
            .addProperty("expanded", &TreeView::Item::expanded)
        .endClass()

        // -----------------------------------------------------------------
        // TreeView : Widget
        // -----------------------------------------------------------------
        .deriveClass<TreeView, Widget>("TreeView")
            .addConstructor<void()>()
            .addFunction("set_resources",   &TreeView::setResources)
            .addFunction("remove_all_items",&TreeView::removeAllItems)
            .addFunction("add_item",
                luabridge::overload<std::shared_ptr<Widget>>(&TreeView::addItem),
                luabridge::overload<const std::shared_ptr<TreeView::Item>&,
                                    std::shared_ptr<Widget>>(&TreeView::addItem)
            )
            .addFunction("expand",          &TreeView::expand)
        .endClass()

        // -----------------------------------------------------------------
        // Window
        // -----------------------------------------------------------------
        .beginClass<Window>("Window")
            .addConstructor<void(const Rect&)>()
            .addProperty("resizeable_borders",      &Window::getResizeableBorders, &Window::setResizeableBorders)
            .addProperty("widget",                  &Window::getWidget)
            .addProperty("style",                  &Window::getStyle, &Window::setStyle)
            .addFunction("set_widget",
                +[](Window* self,
                    const std::shared_ptr<Widget>& child = nullptr,
                    const std::string& resources = "",
                    float padding = 0.0f) {
                    self->setWidget(child, resources, padding);
                })
            .addFunction("set_focused_widget",  &Window::setFocusedWidget)
            .addProperty("width",               &Window::getWidth, &Window::setWidth)
            .addProperty("height",              &Window::getHeight, &Window::setHeight)
            .addProperty("rect",                &Window::getRect, &Window::setRect)
            .addFunction("set_pos",
                luabridge::overload<float, float>(&Window::setPos),
                luabridge::overload<const float2&>(&Window::setPos)
            )
            .addFunction("set_x",               &Window::setX)
            .addFunction("set_y",               &Window::setY)
            .addProperty("is_visible",          &Window::isVisible, &Window::setVisible)
            .addFunction("show",                &Window::show)
            .addFunction("hide",                &Window::hide)
            .addFunction("set_transparency",    &Window::setTransparency)
            .addFunction("set_minimum_size",    &Window::setMinimumSize)
            .addFunction("set_maximum_size",    &Window::setMaximumSize)
            .addProperty("minimum_width",        &Window::getMinimumWidth)
            .addProperty("minimum_height",       &Window::getMinimumHeight)
            .addProperty("maximum_width",        &Window::getMaximumWidth)
            .addProperty("maximum_height",       &Window::getMaximumHeight)
            .addProperty("font",                &Window::getFont, &Window::setFont)
            .addProperty("font_scale",          &Window::getFontScale, &Window::setFontScale)
            .addProperty("text_color",          &Window::getTextColor, &Window::setTextColor)
            .addFunction("refresh",             &Window::refresh)
            // add_child shortcut mirrors Window::add<Widget>
            .addFunction("add_child",
                +[](Window* self,
                    const std::shared_ptr<Widget>& child,
                    Alignment alignment,
                    const std::string& resource = "") -> std::shared_ptr<Widget> {
                    return self->add(child, alignment, resource);
                })
            .addFunction("remove_child",
                +[](Window* self, const std::shared_ptr<Widget>& child) {
                    self->remove(child);
                })
            .addFunction("create_text",
                +[](Window* self, const int alignment, const std::string& text) -> std::shared_ptr<Text> {
                    return self->create<Text>(static_cast<Alignment>(alignment), text);
                })
        .endClass()

        // -----------------------------------------------------------------
        // WindowManager
        // -----------------------------------------------------------------
        .beginClass<WindowManager>("WindowManager")
            .addConstructor<void(RenderingWindow&, const std::string&, float, const float4&)>()
            .addFunction("create",
                +[](WindowManager* self, const Rect& rect) -> std::shared_ptr<Window> {
                    return self->create(rect);
                })
            .addFunction("add",                     &WindowManager::add)
            .addFunction("remove",                  &WindowManager::remove)
            .addProperty("default_font",             &WindowManager::getDefaultFont)
            .addProperty("default_font_scale",       &WindowManager::getDefaultFontScale)
            .addProperty("default_text_color",       &WindowManager::getDefaultTextColor)
            .addProperty("aspect_ratio",             &WindowManager::getAspectRatio)
            .addFunction("refresh",                  &WindowManager::refresh)
            .addProperty("resize_delta",             &WindowManager::getResizeDelta)
            .addFunction("set_enable_window_resizing", &WindowManager::setEnableWindowResizing)
        .endClass()

        .endNamespace().endNamespace();
    }

}

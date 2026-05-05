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
            .addFunction("get_type",             &Widget::getType)
            .addFunction("is_visible",           &Widget::isVisible)
            .addFunction("show",
                +[](Widget* self, bool v = true){ self->show(v); })
            .addFunction("is_enabled",           &Widget::isEnabled)
            .addFunction("enable",
                +[](Widget* self, bool v = true){ self->enable(v); })
            .addFunction("set_pos",              &Widget::setPos)
            .addFunction("get_width",            &Widget::getWidth)
            .addFunction("get_height",           &Widget::getHeight)
            .addFunction("set_size",             &Widget::setSize)
            .addFunction("get_rect",             &Widget::getRect)
            .addFunction("set_rect",
                luabridge::overload<float, float, float, float>(&Widget::setRect),
                luabridge::overload<const Rect&>(&Widget::setRect)
            )
            .addFunction("get_alignment",        &Widget::getAlignment)
            .addFunction("set_alignment",        &Widget::setAlignment)
            .addFunction("get_font",             &Widget::getFont)
            .addFunction("set_font",             &Widget::setFont)
            .addFunction("get_font_scale",       &Widget::getFontScale)
            .addFunction("set_font_scale",       &Widget::setFontScale)
            .addFunction("is_focused",           &Widget::isFocused)
            .addFunction("get_parent",           &Widget::getParent)
            .addFunction("remove",               &Widget::remove)
            .addFunction("remove_all",           &Widget::removeAll)
            .addFunction("set_padding",          &Widget::setPadding)
            .addFunction("get_padding",          &Widget::getPadding)
            .addFunction("get_vborder",          &Widget::getVBorder)
            .addFunction("get_hborder",          &Widget::getHBorder)
            .addFunction("set_vborder",          &Widget::setVBorder)
            .addFunction("set_hborder",          &Widget::setHBorder)
            .addFunction("is_draw_background",   &Widget::isDrawBackground)
            .addFunction("set_draw_background",  &Widget::setDrawBackground)
            .addFunction("is_pushed",            &Widget::isPushed)
            .addFunction("is_pointed",           &Widget::isPointed)
            .addFunction("is_freezed",           &Widget::isFreezed)
            .addFunction("is_overlapping",       &Widget::isOverlapping)
            .addFunction("get_children_rect",    &Widget::getChildrenRect)
            .addFunction("set_freezed",          &Widget::setFreezed)
            .addFunction("set_pushed",           &Widget::setPushed)
            .addFunction("refresh",              &Widget::refresh)
            .addFunction("get_group_index",      &Widget::getGroupIndex)
            .addFunction("set_group_index",      &Widget::setGroupIndex)
            .addFunction("get_transparency",     &Widget::getTransparency)
            .addFunction("set_transparency",     &Widget::setTransparency)
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
            .addFunction("get_state", &CheckWidget::getState)
            .addFunction("set_state", &CheckWidget::setState)
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
            .addFunction("get_style", &Line::getStyle)
            .addFunction("set_style", &Line::setStyle)
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
            .addFunction("get_title",       &Frame::getTitle)
            .addFunction("set_title",       &Frame::setTitle)
            .addFunction("get_title_color", &Frame::getTitleColor)
            .addFunction("set_title_color", &Frame::setTitleColor)
        .endClass()

        // -----------------------------------------------------------------
        // Text : Widget
        // -----------------------------------------------------------------
        .deriveClass<Text, Widget>("Text")
            .addConstructor<void(), void(const std::string&)>()
            .addFunction("get_text",       &Text::getText)
            .addFunction("set_text",       &Text::setText)
            .addFunction("get_text_color", &Text::getTextColor)
            .addFunction("set_text_color", &Text::setTextColor)
            .addFunction("get_size",
                +[](Text* self) -> std::pair<float, float> {
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
            .addFunction("is_read_only",             &TextEdit::isReadOnly)
            .addFunction("set_read_only",            &TextEdit::setReadOnly)
            .addFunction("get_text",                 &TextEdit::getText)
            .addFunction("set_text",                 &TextEdit::setText)
            .addFunction("get_sel_start",            &TextEdit::getSelStart)
            .addFunction("set_sel_start",            &TextEdit::setSelStart)
            .addFunction("get_first_displayed_char", &TextEdit::getFirstDisplayedChar)
            .addFunction("get_displayed_text",       &TextEdit::getDisplayedText)
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
            .addFunction("get_color",     &Image::getColor)
            .addFunction("set_color",     &Image::setColor)
            .addFunction("set_image",     &Image::setImage)
            .addFunction("get_image",     &Image::getImage)
        .endClass()

        // -----------------------------------------------------------------
        // ValueSelect : Widget  (abstract base)
        // -----------------------------------------------------------------
        .deriveClass<ValueSelect, Widget>("ValueSelect")
            .addFunction("get_min",   &ValueSelect::getMin)
            .addFunction("get_max",   &ValueSelect::getMax)
            .addFunction("get_value", &ValueSelect::getValue)
            .addFunction("get_step",  &ValueSelect::getStep)
            .addFunction("set_min",   &ValueSelect::setMin)
            .addFunction("set_max",   &ValueSelect::setMax)
            .addFunction("set_value", &ValueSelect::setValue)
            .addFunction("set_step",  &ValueSelect::setStep)
        .endClass()

        // -----------------------------------------------------------------
        // ScrollBar : ValueSelect
        // -----------------------------------------------------------------
        .deriveClass<ScrollBar, ValueSelect>("ScrollBar")
            .addConstructor<
                void(),
                void(ScrollBar::Type, float, float, float, float)
            >()
            .addFunction("get_scroll_bar_type", &ScrollBar::getScrollBarType)
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
            .addFunction("get_resizeable_borders", &Window::getResizeableBorders)
            .addFunction("set_resizeable_borders", &Window::setResizeableBorders)
            .addFunction("get_style",              &Window::getStyle)
            .addFunction("set_style",              &Window::setStyle)
            .addFunction("set_widget",
                +[](Window* self,
                    const std::shared_ptr<Widget>& child = nullptr,
                    const std::string& resources = "",
                    float padding = 0.0f) {
                    self->setWidget(child, resources, padding);
                })
            .addFunction("set_focused_widget",  &Window::setFocusedWidget)
            .addFunction("get_width",           &Window::getWidth)
            .addFunction("get_height",          &Window::getHeight)
            .addFunction("get_rect",            &Window::getRect)
            .addFunction("set_rect",            &Window::setRect)
            .addFunction("set_width",           &Window::setWidth)
            .addFunction("set_height",          &Window::setHeight)
            .addFunction("set_pos",
                luabridge::overload<float, float>(&Window::setPos),
                luabridge::overload<const float2&>(&Window::setPos)
            )
            .addFunction("set_x",               &Window::setX)
            .addFunction("set_y",               &Window::setY)
            .addFunction("is_visible",          &Window::isVisible)
            .addFunction("set_visible",         &Window::setVisible)
            .addFunction("show",                &Window::show)
            .addFunction("hide",                &Window::hide)
            .addFunction("set_transparency",    &Window::setTransparency)
            .addFunction("set_minimum_size",    &Window::setMinimumSize)
            .addFunction("set_maximum_size",    &Window::setMaximumSize)
            .addFunction("get_minimum_width",   &Window::getMinimumWidth)
            .addFunction("get_minimum_height",  &Window::getMinimumHeight)
            .addFunction("get_maximum_width",   &Window::getMaximumWidth)
            .addFunction("get_maximum_height",  &Window::getMaximumHeight)
            .addFunction("get_font",            &Window::getFont)
            .addFunction("set_font",            &Window::setFont)
            .addFunction("get_font_scale",      &Window::getFontScale)
            .addFunction("set_font_scale",      &Window::setFontScale)
            .addFunction("get_text_color",      &Window::getTextColor)
            .addFunction("set_text_color",      &Window::setTextColor)
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
            .addFunction("get_default_font",        &WindowManager::getDefaultFont)
            .addFunction("get_default_font_scale",  &WindowManager::getDefaultFontScale)
            .addFunction("get_default_text_color",  &WindowManager::getDefaultTextColor)
            .addFunction("get_aspect_ratio",        &WindowManager::getAspectRatio)
            .addFunction("refresh",                 &WindowManager::refresh)
            .addFunction("get_resize_delta",        &WindowManager::getResizeDelta)
            .addFunction("set_enable_window_resizing", &WindowManager::setEnableWindowResizing)
        .endClass()

        .endNamespace().endNamespace();
    }

}

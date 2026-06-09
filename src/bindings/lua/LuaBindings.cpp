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
            .addVariable("NONE", Alignment::NONE)
            .addVariable("FILL", Alignment::FILL)
            .addVariable("CENTER", Alignment::CENTER)
            .addVariable("HCENTER", Alignment::HCENTER)
            .addVariable("VCENTER", Alignment::VCENTER)
            .addVariable("TOP", Alignment::TOP)
            .addVariable("BOTTOM", Alignment::BOTTOM)
            .addVariable("LEFT", Alignment::LEFT)
            .addVariable("RIGHT", Alignment::RIGHT)
            .addVariable("TOPCENTER", Alignment::TOPCENTER)
            .addVariable("BOTTOMCENTER", Alignment::BOTTOMCENTER)
            .addVariable("LEFTCENTER", Alignment::LEFTCENTER)
            .addVariable("RIGHTCENTER", Alignment::RIGHTCENTER)
            .addVariable("TOPLEFT", Alignment::TOPLEFT)
            .addVariable("BOTTOMLEFT", Alignment::BOTTOMLEFT)
            .addVariable("BOTTOMRIGHT", Alignment::BOTTOMRIGHT)
            .addVariable("TOPRIGHT", Alignment::TOPRIGHT)
            .addVariable("LEFTTOP", Alignment::LEFTTOP)
            .addVariable("LEFTBOTTOM", Alignment::LEFTBOTTOM)
            .addVariable("RIGHTBOTTOM", Alignment::RIGHTBOTTOM)
            .addVariable("RIGHTTOP", Alignment::RIGHTTOP)
            .addVariable("CORNERTOPLEFT", Alignment::CORNERTOPLEFT)
            .addVariable("CORNERTOPRIGHT", Alignment::CORNERTOPRIGHT)
            .addVariable("CORNERBOTTOMLEFT", Alignment::CORNERBOTTOMLEFT)
            .addVariable("CORNERBOTTOMRIGHT", Alignment::CORNERBOTTOMRIGHT)
        .endNamespace()

        .beginNamespace("WidgetType")
            .addVariable("WIDGET", Widget::WIDGET)
            .addVariable("PANEL", Widget::PANEL)
            .addVariable("BOX", Widget::BOX)
            .addVariable("LINE", Widget::LINE)
            .addVariable("FRAME", Widget::FRAME)
            .addVariable("BUTTON", Widget::BUTTON)
            .addVariable("TOGGLEBUTTON", Widget::TOGGLEBUTTON)
            .addVariable("TEXT", Widget::TEXT)
            .addVariable("TEXTEDIT", Widget::TEXTEDIT)
            .addVariable("SCROLLBAR", Widget::SCROLLBAR)
            .addVariable("TREEVIEW", Widget::TREEVIEW)
            .addVariable("IMAGE", Widget::IMAGE)
            .addVariable("POPUP", Widget::POPUP)
            .addVariable("LIST", Widget::LIST)
            .addVariable("LISTBOX", Widget::LISTBOX)
            .addVariable("SELECTION", Widget::SELECTION)
            .addVariable("PROGRESSBAR", Widget::PROGRESSBAR)
            .addVariable("SCROLLBOX", Widget::SCROLLBOX)
        .endNamespace()

        .beginNamespace("CheckState")
            .addVariable("UNCHECK", CheckWidget::UNCHECK)
            .addVariable("CHECK", CheckWidget::CHECK)
        .endNamespace()

        .beginNamespace("LineStyle")
            .addVariable("HORIZ", Line::HORIZ)
            .addVariable("VERT", Line::VERT)
        .endNamespace()

        .beginNamespace("ScrollBarType")
            .addVariable("HORIZONTAL", ScrollBar::HORIZONTAL)
            .addVariable("VERTICAL", ScrollBar::VERTICAL)
        .endNamespace()

        .beginNamespace("ProgressBarType")
            .addVariable("HORIZONTAL", ProgressBar::HORIZONTAL)
            .addVariable("VERTICAL", ProgressBar::VERTICAL)
        .endNamespace()

        .beginNamespace("ProgressBarDisplay")
            .addVariable("NONE", ProgressBar::NONE)
            .addVariable("PERCENT", ProgressBar::PERCENT)
            .addVariable("VALUE", ProgressBar::VALUE)
        .endNamespace()

        .beginNamespace("ResizeableBorder")
            .addVariable("NONE", Window::RESIZEABLE_NONE)
            .addVariable("LEFT", Window::RESIZEABLE_LEFT)
            .addVariable("RIGHT", Window::RESIZEABLE_RIGHT)
            .addVariable("TOP", Window::RESIZEABLE_TOP)
            .addVariable("BOTTOM", Window::RESIZEABLE_BOTTOM)
        .endNamespace()

        .beginNamespace("UIEvent")
            .addVariable("OnCreate", &UIEvent::OnCreate)
            .addVariable("OnDestroy", &UIEvent::OnDestroy)
            .addVariable("OnKeyDown", &UIEvent::OnKeyDown)
            .addVariable("OnKeyUp", &UIEvent::OnKeyUp)
            .addVariable("OnMouseDown", &UIEvent::OnMouseDown)
            .addVariable("OnMouseUp", &UIEvent::OnMouseUp)
            .addVariable("OnMouseMove", &UIEvent::OnMouseMove)
            .addVariable("OnGotFocus", &UIEvent::OnGotFocus)
            .addVariable("OnLostFocus", &UIEvent::OnLostFocus)
            .addVariable("OnShow", &UIEvent::OnShow)
            .addVariable("OnHide", &UIEvent::OnHide)
            .addVariable("OnEnable", &UIEvent::OnEnable)
            .addVariable("OnDisable", &UIEvent::OnDisable)
            .addVariable("OnTextChange", &UIEvent::OnTextChange)
            .addVariable("OnTextInput", &UIEvent::OnTextInput)
            .addVariable("OnClick", &UIEvent::OnClick)
            .addVariable("OnStateChange", &UIEvent::OnStateChange)
            .addVariable("OnValueChange", &UIEvent::OnValueChange)
            .addVariable("OnRangeChange", &UIEvent::OnRangeChange)
            .addVariable("OnResize", &UIEvent::OnResize)
            .addVariable("OnMove", &UIEvent::OnMove)
            .addVariable("OnInsertItem", &UIEvent::OnInsertItem)
            .addVariable("OnRemoveItem", &UIEvent::OnRemoveItem)
            .addVariable("OnSelectItem", &UIEvent::OnSelectItem)
        .endNamespace()

        .beginClass<Widget>("Widget")
            .addProperty("id", &Widget::id)
            .addProperty("type", &Widget::getType)
            .addProperty("children", &Widget::getChildren)
            .addProperty("visible", &Widget::isVisible, &Widget::setVisible)
            .addProperty("enabled", &Widget::isEnabled, &Widget::setEnabled)
            .addFunction("set_pos", &Widget::setPos)
            .addProperty("width", &Widget::getWidth, &Widget::setWidth)
            .addProperty("height", &Widget::getHeight, &Widget::setHeight)
            .addFunction("set_size", &Widget::setSize)
            .addProperty("rect",
                &Widget::getRect,
                static_cast<void(Widget::*)(const Rect&)>(&Widget::setRect))
            .addFunction("set_rect",
                luabridge::overload<float, float, float, float>(&Widget::setRect))
            .addProperty("alignment", &Widget::getAlignment, &Widget::setAlignment)
            .addProperty("font", &Widget::getFont, &Widget::setFont)
            .addProperty("font_scale", &Widget::getFontScale, &Widget::setFontScale)
            .addProperty("focused", &Widget::isFocused)
            .addProperty("parent", &Widget::getParent)
            .addFunction("remove", &Widget::remove)
            .addFunction("remove_all", &Widget::removeAll)
            .addProperty("padding", &Widget::getPadding, &Widget::setPadding)
            .addProperty("vborder", &Widget::getVBorder, &Widget::setVBorder)
            .addProperty("hborder", &Widget::getHBorder, &Widget::setHBorder)
            .addProperty("draw_background", &Widget::isDrawBackground, &Widget::setDrawBackground)
            .addProperty("pushed", &Widget::isPushed, &Widget::setPushed)
            .addProperty("pointed", &Widget::isPointed)
            .addProperty("freezed", &Widget::isFreezed, &Widget::setFreezed)
            .addProperty("overlapping", &Widget::isOverlapping)
            .addProperty("children_rect", &Widget::getChildrenRect)
            .addProperty("user_data", &Widget::getLuaUserData, &Widget::setLuaUserData)
            .addFunction("refresh", &Widget::refresh)
            .addProperty("group_index", &Widget::getGroupIndex, &Widget::setGroupIndex)
            .addProperty("transparency", &Widget::getTransparency, &Widget::setTransparency)
            .addFunction("resize_children", &Widget::resizeChildren)
            .addFunction("set_focus",
                +[](Widget* self, const bool focus = true) -> std::shared_ptr<Widget> {
                    return self->setFocus(focus);
                })
            .addProperty("consume_mouse_event", &Widget::getConsumeMouseEvent, &Widget::setConsumeMouseEvent)
            .addProperty("children_offset_x", &Widget::getChildrenOffsetX)
            .addProperty("children_offset_y", &Widget::getChildrenOffsetY)
            .addFunction("set_children_offset", &Widget::setChildrenOffset)
            .addFunction("create_text",
                +[](Widget* self, const int alignment, const std::string& text) -> std::shared_ptr<Text> {
                    return self->create<Text>(static_cast<Alignment>(alignment), text);
                },
                +[](Widget* self, const std::string& resource, const int alignment, const std::string& text) -> std::shared_ptr<Text> {
                    return self->create<Text>(resource, static_cast<Alignment>(alignment), text);
                })
            .addFunction("create_panel",
                +[](Widget* self, const int alignment) -> std::shared_ptr<Panel> {
                    return self->create<Panel>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<Panel> {
                    return self->create<Panel>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_popup",
                +[](Widget* self, const float x, const float y) -> std::shared_ptr<Popup> {
                    return self->add(std::make_shared<Popup>(x, y), Alignment::NONE, "", true);
                },
                +[](Widget* self, const std::string& resource, const float x, const float y) -> std::shared_ptr<Popup> {
                    return self->add(std::make_shared<Popup>(x, y), Alignment::NONE, resource, true);
                })
            .addFunction("create_box",
                +[](Widget* self, const int alignment) -> std::shared_ptr<Box> {
                    return self->create<Box>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<Box> {
                    return self->create<Box>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_button",
                +[](Widget* self, const int alignment) -> std::shared_ptr<Button> {
                    return self->create<Button>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<Button> {
                    return self->create<Button>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_toggle_button",
                +[](Widget* self, const int alignment) -> std::shared_ptr<ToggleButton> {
                    return self->create<ToggleButton>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<ToggleButton> {
                    return self->create<ToggleButton>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_hline",
                +[](Widget* self, const int alignment) -> std::shared_ptr<HLine> {
                    return self->create<HLine>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<HLine> {
                    return self->create<HLine>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_vline",
                +[](Widget* self, const int alignment) -> std::shared_ptr<VLine> {
                    return self->create<VLine>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<VLine> {
                    return self->create<VLine>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_frame",
                +[](Widget* self, const int alignment, const std::string& title) {
                    return self->create<Frame>(static_cast<Alignment>(alignment), title);
                },
                +[](Widget* self, const std::string& resource, const int alignment, const std::string& title) {
                    return self->create<Frame>(resource, static_cast<Alignment>(alignment), title);
                })
            .addFunction("create_text_edit",
                +[](Widget* self, const int alignment, const std::string& text = "") {
                    return self->create<TextEdit>(static_cast<Alignment>(alignment), text);
                },
                +[](Widget* self, const std::string& resource, const int alignment, const std::string& text = "") {
                    return self->create<TextEdit>(resource, static_cast<Alignment>(alignment), text);
                })
            .addFunction("create_image",
                +[](Widget* self, const int alignment) -> std::shared_ptr<Image> {
                    return self->create<Image>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<Image> {
                    return self->create<Image>(resource, static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment, const bool autoresize) -> std::shared_ptr<Image> {
                   return self->create<Image>(resource, static_cast<Alignment>(alignment), autoresize);
                },
                +[](Widget* self, const std::string& resource, const int alignment, const bool autoresize, const bool fixedSize) -> std::shared_ptr<Image> {
                  return self->create<Image>(resource, static_cast<Alignment>(alignment), autoresize, fixedSize);
                })
            .addFunction("create_vscrollbar",
                +[](Widget* self, const int alignment) -> std::shared_ptr<VScrollBar> {
                    return self->create<VScrollBar>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<VScrollBar> {
                    return self->create<VScrollBar>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_hscrollbar",
                +[](Widget* self, const int alignment) -> std::shared_ptr<HScrollBar> {
                    return self->create<HScrollBar>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<HScrollBar> {
                    return self->create<HScrollBar>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_tree_view",
                +[](Widget* self, const int alignment) -> std::shared_ptr<TreeView> {
                    return self->create<TreeView>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<TreeView> {
                    return self->create<TreeView>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_widget",
                +[](Widget* self, const int alignment) -> std::shared_ptr<Widget> {
                    return self->create<Widget>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<Widget> {
                    return self->create<Widget>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_list_box",
                +[](Widget* self, const int alignment) -> std::shared_ptr<ListBox> {
                    return self->create<ListBox>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<ListBox> {
                    return self->create<ListBox>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_progress_bar",
                +[](Widget* self, const int alignment) -> std::shared_ptr<ProgressBar> {
                    return self->create<ProgressBar>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<ProgressBar> {
                    return self->create<ProgressBar>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_vprogress_bar",
                +[](Widget* self, const int alignment) -> std::shared_ptr<VProgressBar> {
                    return self->create<VProgressBar>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<VProgressBar> {
                    return self->create<VProgressBar>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_hprogress_bar",
                +[](Widget* self, const int alignment) -> std::shared_ptr<HProgressBar> {
                    return self->create<HProgressBar>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<HProgressBar> {
                    return self->create<HProgressBar>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_scroll_box",
                +[](Widget* self, const int alignment) -> std::shared_ptr<ScrollBox> {
                    return self->create<ScrollBox>(static_cast<Alignment>(alignment));
                },
                +[](Widget* self, const std::string& resource, const int alignment) -> std::shared_ptr<ScrollBox> {
                    return self->create<ScrollBox>(resource, static_cast<Alignment>(alignment));
                })
            // add_child: expose the non-template path via a lambda taking a shared_ptr<Widget>
            .addFunction("add_child",
                +[](Widget* self,
                    const std::shared_ptr<Widget>& child,
                    const Alignment alignment,
                    const std::string& resource = "") -> std::shared_ptr<Widget> {
                    return self->add(child, alignment, resource);
                })
        .endClass()

        .deriveClass<Panel, Widget>("Panel")
            .addConstructor<void()>()
        .endClass()

        .deriveClass<Popup, Panel>("Popup")
            .addConstructor<void(float, float)>()
            .addProperty("x", &Popup::getX)
            .addProperty("y", &Popup::getY)
        .endClass()

        .deriveClass<Box, Panel>("Box")
            .addConstructor<void()>()
        .endClass()

        .deriveClass<Button, Box>("Button")
            .addConstructor<void()>()
        .endClass()

        .deriveClass<CheckWidget, Widget>("CheckWidget")
            .addProperty("state", &CheckWidget::getState, &CheckWidget::setState)
        .endClass()

        .deriveClass<ToggleButton, CheckWidget>("ToggleButton")
            .addConstructor<void()>()
        .endClass()

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

        .deriveClass<Frame, Panel>("Frame")
            .addConstructor<void(const std::string&)>()
            .addProperty("title", &Frame::getTitle, &Frame::setTitle)
            .addProperty("title_color", &Frame::getTitleColor, &Frame::setTitleColor)
        .endClass()

        .deriveClass<Text, Widget>("Text")
            .addConstructor<void(), void(const std::string&)>()
            .addProperty("text", &Text::getText, &Text::setText)
            .addProperty("text_color", &Text::getTextColor, &Text::setTextColor)
            .addFunction("get_size",
                +[](const Text* self) -> std::pair<float, float> {
                    float w = 0, h = 0;
                    self->getSize(w, h);
                    return {w, h};
                })
        .endClass()

        .deriveClass<TextEdit, Widget>("TextEdit")
            .addConstructor<void(), void(const std::string&)>()
            .addProperty("is_read_only", &TextEdit::isReadOnly, &TextEdit::setReadOnly)
            .addProperty("text", &TextEdit::getText, &TextEdit::setText)
            .addProperty("sel_start", &TextEdit::getSelStart, &TextEdit::setSelStart)
            .addProperty("first_displayed_char", &TextEdit::getFirstDisplayedChar)
            .addProperty("displayed_text", &TextEdit::getDisplayedText)
            .addFunction("set_resources", &TextEdit::setResources)
        .endClass()

        .deriveClass<Image, Widget>("Image")
            .addConstructor<
                void(),
                void(bool),
                void(const lysa::Image&, bool)
            >()
            .addFunction("set_auto_size", &Image::setAutoSize)
            .addProperty("color", &Image::getColor, &Image::setColor)
            .addProperty("image", &Image::getImage)
            .addFunction("set_image",
                luabridge::overload<const std::string&>(&Image::setImage),
                luabridge::overload<const lysa::Image&>(&Image::setImage)
            )
        .endClass()

        .deriveClass<ValueSelect, Widget>("ValueSelect")
            .addProperty("min", &ValueSelect::getMin, &ValueSelect::setMin)
            .addProperty("max", &ValueSelect::getMax, &ValueSelect::setMax)
            .addProperty("value", &ValueSelect::getValue, &ValueSelect::setValue)
            .addProperty("step", &ValueSelect::getStep, &ValueSelect::setStep)
        .endClass()

        .deriveClass<ScrollBar, ValueSelect>("ScrollBar")
            .addConstructor<
                void(),
                void(ScrollBar::Type, float, float, float, float)
            >()
            .addProperty("scroll_bar_type", &ScrollBar::getScrollBarType)
            .addFunction("set_resources", &ScrollBar::setResources)
        .endClass()

        .deriveClass<VScrollBar, ScrollBar>("VScrollBar")
            .addConstructor<void(), void(float, float, float, float)>()
        .endClass()

        .deriveClass<HScrollBar, ScrollBar>("HScrollBar")
            .addConstructor<void(), void(float, float, float, float)>()
        .endClass()

        .deriveClass<TreeView::Item, Panel>("TreeViewItem")
            .addProperty("item", &TreeView::Item::item)
            .addProperty("level", &TreeView::Item::level)
            .addProperty("selected", &TreeView::Item::selected)
            .addProperty("expanded", &TreeView::Item::expanded)
        .endClass()

        .deriveClass<TreeView, Widget>("TreeView")
            .addConstructor<void()>()
            .addFunction("set_resources", &TreeView::setResources)
            .addFunction("remove_all_items",&TreeView::removeAllItems)
            .addFunction("add_item",
                luabridge::overload<std::shared_ptr<Widget>>(&TreeView::addItem),
                luabridge::overload<const std::shared_ptr<TreeView::Item>&,
                                    std::shared_ptr<Widget>>(&TreeView::addItem)
            )
            .addFunction("expand", &TreeView::expand)
        .endClass()

        .deriveClass<List, Widget>("List")
            .addProperty("count", &List::getCount)
            .addProperty("selected_index", &List::getSelectedIndex)
            .addProperty("selected_item", &List::getSelectedItem)
            .addFunction("add_item",
                +[](List* self,
                    const std::shared_ptr<Widget>& item,
                    const int alignment,
                    const std::string& resource) -> int32 {
                    return self->addItem(item, static_cast<Alignment>(alignment), resource);
                })
            .addFunction("remove_item", &List::removeItem)
            .addFunction("remove_all_items", &List::removeAllItems)
            .addFunction("get_item", &List::getItem)
            .addFunction("select", &List::select)
        .endClass()

        .deriveClass<ListBox, List>("ListBox")
            .addConstructor<void()>()
            .addFunction("set_resources", &ListBox::setResources)
            .addProperty("selection_widget", &ListBox::getSelectionWidget)
        .endClass()

        .deriveClass<Selection, Panel>("Selection")
            .addConstructor<void()>()
        .endClass()

        .deriveClass<ProgressBar, ValueSelect>("ProgressBar")
            .addConstructor<
                void(),
                void(ProgressBar::Orientation, float, float, float, float)
            >()
            .addProperty("orientation", &ProgressBar::getOrientation, &ProgressBar::setOrientation)
            .addProperty("display", &ProgressBar::getDisplay, &ProgressBar::setDisplay)
            .addFunction("set_resources", &ProgressBar::setResources)
        .endClass()

        .deriveClass<VProgressBar, ProgressBar>("VProgressBar")
            .addConstructor<void(), void(float, float, float)>()
        .endClass()

        .deriveClass<HProgressBar, ProgressBar>("HProgressBar")
            .addConstructor<void(), void(float, float, float)>()
        .endClass()

        .deriveClass<ScrollBox, Box>("ScrollBox")
            .addConstructor<void()>()
            .addFunction("set_resources", &ScrollBox::setResources)
            .addFunction("add_content",
                +[](ScrollBox* self,
                    const std::shared_ptr<Widget>& child,
                    const int alignment,
                    const std::string& resource) -> std::shared_ptr<Widget> {
                    return self->addContent(child, static_cast<Alignment>(alignment), resource);
                })
            .addFunction("remove_content", &ScrollBox::removeContent)
            .addFunction("remove_all_content", &ScrollBox::removeAllContent)
            .addProperty("inner_box", &ScrollBox::getInnerBox)
        .endClass()

        .beginClass<Window>("Window")
            .addConstructor<void(const Rect&)>()
            .addProperty("resizeable_borders", &Window::getResizeableBorders, &Window::setResizeableBorders)
            .addProperty("widget", &Window::getWidget)
            .addProperty("style", &Window::getStyle, &Window::setStyle)
            .addFunction("set_widget",
                +[](Window* self,
                    const std::shared_ptr<Widget>& child = nullptr,
                    const std::string& resources = "",
                    const float padding = 0.0f) {
                    self->setWidget(child, resources, padding);
                })
            .addFunction("set_focused_widget", &Window::setFocusedWidget)
            .addProperty("width", &Window::getWidth, &Window::setWidth)
            .addProperty("height", &Window::getHeight, &Window::setHeight)
            .addProperty("rect", &Window::getRect, &Window::setRect)
            .addFunction("set_pos",
                luabridge::overload<float, float>(&Window::setPos),
                luabridge::overload<const float2&>(&Window::setPos)
            )
            .addProperty("x", &Window::getX, &Window::setX)
            .addProperty("y", &Window::getY, &Window::setY)
            .addProperty("visible", &Window::isVisible, &Window::setVisible)
            .addFunction("show", &Window::show)
            .addFunction("hide", &Window::hide)
            .addFunction("close", &Window::close)
            .addFunction("set_transparency", &Window::setTransparency)
            .addFunction("set_minimum_size", &Window::setMinimumSize)
            .addFunction("set_maximum_size", &Window::setMaximumSize)
            .addProperty("minimum_width", &Window::getMinimumWidth)
            .addProperty("minimum_height", &Window::getMinimumHeight)
            .addProperty("maximum_width", &Window::getMaximumWidth)
            .addProperty("maximum_height", &Window::getMaximumHeight)
            .addProperty("aspect_ratio", &Window::getAspectRatio)
            .addProperty("font", &Window::getFont, &Window::setFont)
            .addProperty("font_scale", &Window::getFontScale, &Window::setFontScale)
            .addProperty("text_color", &Window::getTextColor, &Window::setTextColor)
            .addFunction("refresh", &Window::refresh)
            // add_child shortcut mirrors Window::add<Widget>
            .addFunction("add_child",
                +[](const Window* self,
                    const std::shared_ptr<Widget>& child,
                    const Alignment alignment,
                    const std::string& resource = "") -> std::shared_ptr<Widget> {
                    return self->add(child, alignment, resource);
                })
            .addFunction("remove_child",
                +[](const Window* self, const std::shared_ptr<Widget>& child) {
                    self->remove(child);
                })
            .addFunction("create_text",
                +[](Window* self, const int alignment, const std::string& text) -> std::shared_ptr<Text> {
                    return self->create<Text>(static_cast<Alignment>(alignment), text);
                },
                +[](Window* self, const std::string& resource, const int alignment, const std::string& text) -> std::shared_ptr<Text> {
                    return self->create<Text>(resource, static_cast<Alignment>(alignment), text);
                })
            .addFunction("create_panel",
                +[](Window* self, const int alignment) -> std::shared_ptr<Panel> {
                    return self->create<Panel>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<Panel> {
                    return self->create<Panel>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_popup",
                +[](Window* self, const float x, const float y) -> std::shared_ptr<Popup> {
                    return self->add(std::make_shared<Popup>(x, y), Alignment::NONE, "", true);
                },
                +[](Window* self, const std::string& resource, const float x, const float y) -> std::shared_ptr<Popup> {
                    return self->add(std::make_shared<Popup>(x, y), Alignment::NONE, resource, true);
                })
            .addFunction("create_box",
                +[](Window* self, const int alignment) -> std::shared_ptr<Box> {
                    return self->create<Box>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<Box> {
                    return self->create<Box>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_button",
                +[](Window* self, const int alignment) -> std::shared_ptr<Button> {
                    return self->create<Button>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<Button> {
                    return self->create<Button>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_toggle_button",
                +[](Window* self, const int alignment) -> std::shared_ptr<ToggleButton> {
                    return self->create<ToggleButton>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<ToggleButton> {
                    return self->create<ToggleButton>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_hline",
                +[](Window* self, const int alignment) -> std::shared_ptr<HLine> {
                    return self->create<HLine>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<HLine> {
                    return self->create<HLine>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_vline",
                +[](Window* self, const int alignment) -> std::shared_ptr<VLine> {
                    return self->create<VLine>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<VLine> {
                    return self->create<VLine>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_frame",
                +[](Window* self, const int alignment, const std::string& title) -> std::shared_ptr<Frame> {
                    return self->create<Frame>(static_cast<Alignment>(alignment), title);
                },
                +[](Window* self, const std::string& resource, const int alignment, const std::string& title) -> std::shared_ptr<Frame> {
                    return self->create<Frame>(resource, static_cast<Alignment>(alignment), title);
                })
            .addFunction("create_text_edit",
                +[](Window* self, const int alignment, const std::string& text = "") -> std::shared_ptr<TextEdit> {
                    return self->create<TextEdit>(static_cast<Alignment>(alignment), text);
                },
                +[](Window* self, const std::string& resource, const int alignment, const std::string& text = "") -> std::shared_ptr<TextEdit> {
                    return self->create<TextEdit>(resource, static_cast<Alignment>(alignment), text);
                })
            .addFunction("create_image",
                +[](Window* self, const int alignment) -> std::shared_ptr<Image> {
                    return self->create<Image>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<Image> {
                    return self->create<Image>(resource, static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment, const bool autoresize, const bool fixedSize) -> std::shared_ptr<Image> {
                    return self->create<Image>(resource, static_cast<Alignment>(alignment), autoresize, fixedSize);
                })
            .addFunction("create_vscrollbar",
                +[](Window* self, const int alignment) -> std::shared_ptr<VScrollBar> {
                    return self->create<VScrollBar>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<VScrollBar> {
                    return self->create<VScrollBar>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_hscrollbar",
                +[](Window* self, const int alignment) -> std::shared_ptr<HScrollBar> {
                    return self->create<HScrollBar>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<HScrollBar> {
                    return self->create<HScrollBar>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_tree_view",
                +[](Window* self, const int alignment) -> std::shared_ptr<TreeView> {
                    return self->create<TreeView>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<TreeView> {
                    return self->create<TreeView>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_widget",
                +[](Window* self, const int alignment) -> std::shared_ptr<Widget> {
                    return self->create<Widget>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<Widget> {
                    return self->create<Widget>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_list_box",
                +[](Window* self, const int alignment) -> std::shared_ptr<ListBox> {
                    return self->create<ListBox>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<ListBox> {
                    return self->create<ListBox>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_progress_bar",
                +[](Window* self, const int alignment) -> std::shared_ptr<ProgressBar> {
                    return self->create<ProgressBar>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<ProgressBar> {
                    return self->create<ProgressBar>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_vprogress_bar",
                +[](Window* self, const int alignment) -> std::shared_ptr<VProgressBar> {
                    return self->create<VProgressBar>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<VProgressBar> {
                    return self->create<VProgressBar>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_hprogress_bar",
                +[](Window* self, const int alignment) -> std::shared_ptr<HProgressBar> {
                    return self->create<HProgressBar>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<HProgressBar> {
                    return self->create<HProgressBar>(resource, static_cast<Alignment>(alignment));
                })
            .addFunction("create_scroll_box",
                +[](Window* self, const int alignment) -> std::shared_ptr<ScrollBox> {
                    return self->create<ScrollBox>(static_cast<Alignment>(alignment));
                },
                +[](Window* self, const std::string& resource, const int alignment) -> std::shared_ptr<ScrollBox> {
                    return self->create<ScrollBox>(resource, static_cast<Alignment>(alignment));
                })
        .endClass()

        .beginClass<WindowManager>("WindowManager")
            .addConstructor<void(RenderingWindow&, const std::string&, float, const float4&)>()
            .addFunction("create",
                +[](WindowManager* self, const Rect& rect) -> std::shared_ptr<Window> {
                    return self->create(rect);
                })
            .addFunction("add", &WindowManager::add)
            .addFunction("remove", &WindowManager::remove)
            .addProperty("default_font", &WindowManager::getDefaultFont)
            .addProperty("default_font_scale", &WindowManager::getDefaultFontScale, &WindowManager::setDefaultFontScale)
            .addProperty("default_text_color", &WindowManager::getDefaultTextColor, &WindowManager::setDefaultTextColor)
            .addProperty("aspect_ratio", &WindowManager::getAspectRatio)
            .addProperty("resize_delta", &WindowManager::getResizeDelta)
            .addFunction("set_enable_window_resizing", &WindowManager::setEnableWindowResizing)
        .endClass()

        .endNamespace().endNamespace();
    }

}

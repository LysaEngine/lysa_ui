---@meta
---@diagnostic disable: missing-return, lowercase-global

------------------------------------------------------------------------
-- Enums (exposed as namespaces)
------------------------------------------------------------------------

---@class lysa.ui.Alignment
---@field NONE integer No alignment
---@field FILL integer Centered and resized to parent content size
---@field CENTER integer Centered (takes all parent content size)
---@field HCENTER integer Horizontally centered
---@field VCENTER integer Vertically centered
---@field TOP integer Stacked on the top
---@field BOTTOM integer Stacked on the bottom
---@field LEFT integer Stacked on the left
---@field RIGHT integer Stacked on the right
---@field TOPCENTER integer Stacked on the top and horizontally centered
---@field BOTTOMCENTER integer Stacked on the bottom and horizontally centered
---@field LEFTCENTER integer Stacked on the left and vertically centered
---@field RIGHTCENTER integer Stacked on the right and vertically centered
---@field TOPLEFT integer Stacked on the top and left aligned
---@field BOTTOMLEFT integer Stacked on the bottom and left aligned
---@field BOTTOMRIGHT integer Stacked on the bottom and right aligned
---@field TOPRIGHT integer Stacked on the top and right aligned
---@field LEFTTOP integer Stacked on the left then on the top
---@field LEFTBOTTOM integer Stacked on the left then on the bottom
---@field RIGHTBOTTOM integer Stacked on the right then on the bottom
---@field RIGHTTOP integer Stacked on the right then on the top
---@field CORNERTOPLEFT integer Stacked at top-left corner
---@field CORNERTOPRIGHT integer Stacked at top-right corner
---@field CORNERBOTTOMLEFT integer Stacked at bottom-left corner
---@field CORNERBOTTOMRIGHT integer Stacked at bottom-right corner

---@class lysa.ui.WidgetType
---@field WIDGET integer Transparent widget
---@field PANEL integer Rectangular widget with only a background
---@field BOX integer Rectangular widget with a border and a background
---@field LINE integer A horizontal or vertical line
---@field FRAME integer A box with a title
---@field BUTTON integer A push button
---@field TOGGLEBUTTON integer A two-states button
---@field TEXT integer A single line of text
---@field TEXTEDIT integer An editable single line of text
---@field SCROLLBAR integer A scroll bar with min, max & pos
---@field TREEVIEW integer Tree of widgets
---@field IMAGE integer 2D image widget

---@class lysa.ui.CheckState
---@field UNCHECK integer Unchecked / OFF state
---@field CHECK integer Checked / ON state

---@class lysa.ui.LineStyle
---@field HORIZ integer Horizontal line
---@field VERT integer Vertical line

---@class lysa.ui.ScrollBarType
---@field HORIZONTAL integer Horizontal scroll bar
---@field VERTICAL integer Vertical scroll bar

---@class lysa.ui.ResizeableBorder
---@field NONE integer No resizing
---@field LEFT integer Left border resizable
---@field RIGHT integer Right border resizable
---@field TOP integer Top border resizable
---@field BOTTOM integer Bottom border resizable

---@class lysa.ui.UIEvent
---@field OnCreate string Called after widget creation
---@field OnDestroy string Called before widget destruction
---@field OnKeyDown string Key pressed while widget has keyboard focus
---@field OnKeyUp string Key released while widget has keyboard focus
---@field OnMouseDown string Mouse button pressed above the widget
---@field OnMouseUp string Mouse button released above the widget
---@field OnMouseMove string Mouse moved above the widget
---@field OnGotFocus string Widget acquired keyboard focus
---@field OnLostFocus string Widget lost keyboard focus
---@field OnShow string Visibility changed to visible
---@field OnHide string Visibility changed to hidden
---@field OnEnable string State changed to enabled
---@field OnDisable string State changed to disabled
---@field OnTextChange string Text content changed
---@field OnTextInput string Text input from the user
---@field OnClick string Widget was clicked (buttons)
---@field OnStateChange string CheckWidget state changed
---@field OnValueChange string Value of a ValueSelect widget changed
---@field OnRangeChange string Range of a ValueSelect widget changed
---@field OnResize string Window size changed
---@field OnMove string Window position changed

------------------------------------------------------------------------
-- Classes
------------------------------------------------------------------------

---@class lysa.ui.Widget
---@field get_type fun(self:lysa.ui.Widget):integer Returns the widget type (see lysa.ui.WidgetType).
---@field is_visible fun(self:lysa.ui.Widget):boolean Returns true if the widget is visible.
---@field show fun(self:lysa.ui.Widget, visible:boolean|nil):nil Shows or hides the widget (default true).
---@field is_enabled fun(self:lysa.ui.Widget):boolean Returns true if the widget reacts to input.
---@field enable fun(self:lysa.ui.Widget, enabled:boolean|nil):nil Enables or disables the widget (default true).
---@field set_pos fun(self:lysa.ui.Widget, x:number, y:number):nil Moves the widget to (x, y).
---@field get_width fun(self:lysa.ui.Widget):number Returns the width in pixels.
---@field get_height fun(self:lysa.ui.Widget):number Returns the height in pixels.
---@field set_size fun(self:lysa.ui.Widget, width:number, height:number):nil Resizes the widget.
---@field get_rect fun(self:lysa.ui.Widget):any Returns the position and size rectangle.
---@field set_rect fun(self:lysa.ui.Widget, x:number, y:number, width:number, height:number):nil Sets position and size.
---@field get_alignment fun(self:lysa.ui.Widget):integer Returns the current alignment (see lysa.ui.Alignment).
---@field set_alignment fun(self:lysa.ui.Widget, alignment:integer):nil Sets the widget placement alignment.
---@field get_font fun(self:lysa.ui.Widget):any Returns the current font.
---@field set_font fun(self:lysa.ui.Widget, font:any):nil Sets the current font.
---@field get_font_scale fun(self:lysa.ui.Widget):number Returns the font scale.
---@field set_font_scale fun(self:lysa.ui.Widget, scale:number):nil Sets the font scale.
---@field is_focused fun(self:lysa.ui.Widget):boolean Returns true if the widget has keyboard focus.
---@field get_parent fun(self:lysa.ui.Widget):lysa.ui.Widget|nil Returns the parent widget, or nil.
---@field remove fun(self:lysa.ui.Widget, child:lysa.ui.Widget):nil Removes a child widget.
---@field remove_all fun(self:lysa.ui.Widget):nil Removes all children recursively.
---@field set_padding fun(self:lysa.ui.Widget, padding:number):nil Sets children padding.
---@field get_padding fun(self:lysa.ui.Widget):number Returns children padding.
---@field get_vborder fun(self:lysa.ui.Widget):number Returns vertical border size.
---@field get_hborder fun(self:lysa.ui.Widget):number Returns horizontal border size.
---@field set_vborder fun(self:lysa.ui.Widget, size:number):nil Sets vertical border size.
---@field set_hborder fun(self:lysa.ui.Widget, size:number):nil Sets horizontal border size.
---@field is_draw_background fun(self:lysa.ui.Widget):boolean Returns false if background is transparent.
---@field set_draw_background fun(self:lysa.ui.Widget, draw:boolean):nil Sets whether to draw the background.
---@field is_pushed fun(self:lysa.ui.Widget):boolean Returns true if the widget is currently pushed.
---@field is_pointed fun(self:lysa.ui.Widget):boolean Returns true if the mouse is over the widget.
---@field is_freezed fun(self:lysa.ui.Widget):boolean Returns true if the widget is not responding to events.
---@field is_overlapping fun(self:lysa.ui.Widget):boolean Returns true if the widget overlaps others.
---@field get_children_rect fun(self:lysa.ui.Widget):any Returns the bounding rectangle of all children.
---@field set_freezed fun(self:lysa.ui.Widget, freeze:boolean):nil Sets whether the widget is frozen.
---@field set_pushed fun(self:lysa.ui.Widget, pushed:boolean):nil Sets the pushed state of the widget.
---@field refresh fun(self:lysa.ui.Widget):nil Forces a full redraw of the widget.
---@field get_group_index fun(self:lysa.ui.Widget):integer Returns the user-defined group index.
---@field set_group_index fun(self:lysa.ui.Widget, index:integer):nil Sets the user-defined group index.
---@field get_transparency fun(self:lysa.ui.Widget):number Returns the transparency alpha value.
---@field set_transparency fun(self:lysa.ui.Widget, alpha:number):nil Sets the transparency alpha value.
---@field resize_children fun(self:lysa.ui.Widget):nil Resizes children widgets.
---@field add_child fun(self:lysa.ui.Widget, child:lysa.ui.Widget, alignment:integer, resource:string|nil):lysa.ui.Widget Adds a child widget with alignment and optional resource string.

---@class lysa.ui.Panel : lysa.ui.Widget

---@class lysa.ui.Box : lysa.ui.Panel

---@class lysa.ui.Button : lysa.ui.Box

---@class lysa.ui.CheckWidget : lysa.ui.Widget
---@field get_state fun(self:lysa.ui.CheckWidget):integer Returns the current state (see lysa.ui.CheckState).
---@field set_state fun(self:lysa.ui.CheckWidget, state:integer):nil Changes the widget state.

---@class lysa.ui.ToggleButton : lysa.ui.CheckWidget

---@class lysa.ui.Line : lysa.ui.Widget
---@field get_style fun(self:lysa.ui.Line):integer Returns the line orientation (see lysa.ui.LineStyle).
---@field set_style fun(self:lysa.ui.Line, style:integer):nil Sets the line orientation.

---@class lysa.ui.HLine : lysa.ui.Line

---@class lysa.ui.VLine : lysa.ui.Line

---@class lysa.ui.Frame : lysa.ui.Panel
---@field get_title fun(self:lysa.ui.Frame):string Returns the frame title.
---@field set_title fun(self:lysa.ui.Frame, title:string):nil Sets the frame title.
---@field get_title_color fun(self:lysa.ui.Frame):any Returns the title text color.
---@field set_title_color fun(self:lysa.ui.Frame, color:any):nil Sets the title text color.

---@class lysa.ui.Text : lysa.ui.Widget
---@field get_text fun(self:lysa.ui.Text):string Returns the displayed text.
---@field set_text fun(self:lysa.ui.Text, text:string):nil Sets the text to display.
---@field get_text_color fun(self:lysa.ui.Text):any Returns the text color.
---@field set_text_color fun(self:lysa.ui.Text, color:any):nil Sets the text color.
---@field get_size fun(self:lysa.ui.Text):{number, number} Returns the {width, height} of the text.

---@class lysa.ui.TextEdit : lysa.ui.Widget
---@field is_read_only fun(self:lysa.ui.TextEdit):boolean Returns true if the widget is read-only.
---@field set_read_only fun(self:lysa.ui.TextEdit, readonly:boolean):nil Sets whether the widget is read-only.
---@field get_text fun(self:lysa.ui.TextEdit):string Returns the current text.
---@field set_text fun(self:lysa.ui.TextEdit, text:string):nil Sets the text.
---@field get_sel_start fun(self:lysa.ui.TextEdit):integer Returns the selection start position.
---@field set_sel_start fun(self:lysa.ui.TextEdit, start:integer):nil Sets the selection start position.
---@field get_first_displayed_char fun(self:lysa.ui.TextEdit):integer Returns the index of the first displayed character.
---@field get_displayed_text fun(self:lysa.ui.TextEdit):string Returns the text currently displayed in the text box.
---@field set_resources fun(self:lysa.ui.TextEdit, resource:string):nil Sets the UI resources for the text edit.

---@class lysa.ui.Image : lysa.ui.Widget
---@field set_auto_size fun(self:lysa.ui.Image, autoSize:boolean):nil Sets whether to automatically resize to image size.
---@field get_color fun(self:lysa.ui.Image):any Returns the image color tint.
---@field set_color fun(self:lysa.ui.Image, color:any):nil Sets the image color tint.
---@field set_image fun(self:lysa.ui.Image, image:any):nil Sets the image to display.
---@field get_image fun(self:lysa.ui.Image):any Returns the currently displayed image, or nil.

---@class lysa.ui.ValueSelect : lysa.ui.Widget
---@field get_min fun(self:lysa.ui.ValueSelect):number Returns the minimum value.
---@field get_max fun(self:lysa.ui.ValueSelect):number Returns the maximum value.
---@field get_value fun(self:lysa.ui.ValueSelect):number Returns the current value.
---@field get_step fun(self:lysa.ui.ValueSelect):number Returns the step increment.
---@field set_min fun(self:lysa.ui.ValueSelect, min:number):nil Sets the minimum value.
---@field set_max fun(self:lysa.ui.ValueSelect, max:number):nil Sets the maximum value.
---@field set_value fun(self:lysa.ui.ValueSelect, value:number):nil Sets the current value.
---@field set_step fun(self:lysa.ui.ValueSelect, step:number):nil Sets the step increment.

---@class lysa.ui.ScrollBar : lysa.ui.ValueSelect
---@field get_scroll_bar_type fun(self:lysa.ui.ScrollBar):integer Returns the orientation (see lysa.ui.ScrollBarType).
---@field set_resources fun(self:lysa.ui.ScrollBar, area:string, cage:string):nil Sets the UI resources for the scroll bar.

---@class lysa.ui.VScrollBar : lysa.ui.ScrollBar

---@class lysa.ui.HScrollBar : lysa.ui.ScrollBar

---@class lysa.ui.TreeViewItem : lysa.ui.Panel
---@field item lysa.ui.Widget The widget displayed for this item.
---@field level integer Depth level in the tree.
---@field selected boolean Whether the item is selected.
---@field expanded boolean Whether the item is expanded.

---@class lysa.ui.TreeView : lysa.ui.Widget
---@field set_resources fun(self:lysa.ui.TreeView, resBox:string, resScroll:string, resHandle:string):nil Sets UI resources for the tree view.
---@field remove_all_items fun(self:lysa.ui.TreeView):nil Removes all items from the tree view.
---@field add_item fun(self:lysa.ui.TreeView, parent_or_widget:lysa.ui.TreeViewItem|lysa.ui.Widget, widget:lysa.ui.Widget|nil):lysa.ui.TreeViewItem Adds a root item or a child item. Pass only a widget to add a root item; pass a parent TreeViewItem and a widget to add a child.
---@field expand fun(self:lysa.ui.TreeView, item:lysa.ui.Widget):nil Expands the tree item associated with the given widget.

---@class lysa.ui.Window
---@field get_resizeable_borders fun(self:lysa.ui.Window):integer Returns the resizable borders bitmask (see lysa.ui.ResizeableBorder).
---@field set_resizeable_borders fun(self:lysa.ui.Window, borders:integer):nil Sets the resizable borders bitmask.
---@field get_widget fun(self:lysa.ui.Window):lysa.ui.Widget
---@field get_style fun(self:lysa.ui.Window):any Returns the current style, or nil.
---@field set_style fun(self:lysa.ui.Window, style:any):nil Sets the current style (pass nil to install the default).
---@field set_widget fun(self:lysa.ui.Window, child:lysa.ui.Widget|nil, resources:string|nil, padding:number|nil):nil Sets the root widget.
---@field set_focused_widget fun(self:lysa.ui.Window, widget:lysa.ui.Widget):nil Moves keyboard focus to the given widget.
---@field get_width fun(self:lysa.ui.Window):number Returns the client area width.
---@field get_height fun(self:lysa.ui.Window):number Returns the client area height.
---@field get_rect fun(self:lysa.ui.Window):any Returns the client area rectangle.
---@field set_rect fun(self:lysa.ui.Window, rect:any):nil Sets the client area position and size.
---@field set_width fun(self:lysa.ui.Window, width:number):nil Sets the client area width.
---@field set_height fun(self:lysa.ui.Window, height:number):nil Sets the client area height.
---@field set_pos fun(self:lysa.ui.Window, x:number, y:number):nil Sets the window position (bottom-left).
---@field set_x fun(self:lysa.ui.Window, x:number):nil Sets the X position.
---@field set_y fun(self:lysa.ui.Window, y:number):nil Sets the Y position.
---@field is_visible fun(self:lysa.ui.Window):boolean Returns true if the window is visible.
---@field set_visible fun(self:lysa.ui.Window, visible:boolean):nil Sets window visibility (effective next frame).
---@field show fun(self:lysa.ui.Window):nil Shows the window (effective next frame).
---@field hide fun(self:lysa.ui.Window):nil Hides the window (effective next frame).
---@field set_transparency fun(self:lysa.ui.Window, alpha:number):nil Sets the alpha transparency value.
---@field set_minimum_size fun(self:lysa.ui.Window, width:number, height:number):nil Sets the minimum window size.
---@field set_maximum_size fun(self:lysa.ui.Window, width:number, height:number):nil Sets the maximum window size.
---@field get_minimum_width fun(self:lysa.ui.Window):number Returns the minimum width.
---@field get_minimum_height fun(self:lysa.ui.Window):number Returns the minimum height.
---@field get_maximum_width fun(self:lysa.ui.Window):number Returns the maximum width.
---@field get_maximum_height fun(self:lysa.ui.Window):number Returns the maximum height.
---@field get_font fun(self:lysa.ui.Window):any Returns the default font.
---@field set_font fun(self:lysa.ui.Window, font:any):nil Sets the default font.
---@field get_font_scale fun(self:lysa.ui.Window):number Returns the default font scale.
---@field set_font_scale fun(self:lysa.ui.Window, scale:number):nil Sets the default font scale.
---@field get_text_color fun(self:lysa.ui.Window):any Returns the default text color.
---@field set_text_color fun(self:lysa.ui.Window, color:any):nil Sets the default text color.
---@field refresh fun(self:lysa.ui.Window):nil Forces a redraw of all the UI.
---@field add_child fun(self:lysa.ui.Window, child:lysa.ui.Widget, alignment:integer, resource:string|nil):lysa.ui.Widget Adds a child widget to the root widget.
---@field remove_child fun(self:lysa.ui.Window, child:lysa.ui.Widget):nil Removes a child widget from the root widget.

---@class lysa.ui.WindowManager
---@field create fun(self:lysa.ui.WindowManager, rect:any):lysa.ui.Window Creates and adds a new UI window with the given rectangle.
---@field add fun(self:lysa.ui.WindowManager, window:lysa.ui.Window):lysa.ui.Window Adds an existing UI window to the manager.
---@field remove fun(self:lysa.ui.WindowManager, window:lysa.ui.Window):nil Removes a UI window (effective next frame).
---@field get_default_font fun(self:lysa.ui.WindowManager):any Returns the default font.
---@field get_default_font_scale fun(self:lysa.ui.WindowManager):number Returns the default font scale.
---@field get_default_text_color fun(self:lysa.ui.WindowManager):any Returns the default text color.
---@field get_aspect_ratio fun(self:lysa.ui.WindowManager):number Returns the aspect ratio of the managed rendering window.
---@field refresh fun(self:lysa.ui.WindowManager):nil Forces a redraw of all UI at the start of the next frame.
---@field get_resize_delta fun(self:lysa.ui.WindowManager):number Returns the resize delta for window resizing.
---@field set_enable_window_resizing fun(self:lysa.ui.WindowManager, enable:boolean):nil Enables or disables user window resizing.

------------------------------------------------------------------------
-- Global namespace declaration
-- All lysa.ui.* classes above are accessible as fields of this global.
------------------------------------------------------------------------

---@class lysa.ui
---@field Alignment lysa.ui.Alignment
---@field WidgetType lysa.ui.WidgetType
---@field CheckState lysa.ui.CheckState
---@field LineStyle lysa.ui.LineStyle
---@field ScrollBarType lysa.ui.ScrollBarType
---@field ResizeableBorder lysa.ui.ResizeableBorder
---@field UIEvent lysa.ui.UIEvent
---@field Widget lysa.ui.Widget
---@field Panel lysa.ui.Panel
---@field Box lysa.ui.Box
---@field Button lysa.ui.Button
---@field CheckWidget lysa.ui.CheckWidget
---@field ToggleButton lysa.ui.ToggleButton
---@field Line lysa.ui.Line
---@field HLine lysa.ui.HLine
---@field VLine lysa.ui.VLine
---@field Frame lysa.ui.Frame
---@field Text lysa.ui.Text
---@field TextEdit lysa.ui.TextEdit
---@field Image lysa.ui.Image
---@field ValueSelect lysa.ui.ValueSelect
---@field ScrollBar lysa.ui.ScrollBar
---@field VScrollBar lysa.ui.VScrollBar
---@field HScrollBar lysa.ui.HScrollBar
---@field TreeViewItem lysa.ui.TreeViewItem
---@field TreeView lysa.ui.TreeView
---@field Window lysa.ui.Window
---@field WindowManager lysa.ui.WindowManager

---@type lysa.ui
lysa.ui = {}
---@meta
---@diagnostic disable: missing-return, lowercase-global

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

---@class lysa.ui.Widget
---@field type integer The widget type (see lysa.ui.WidgetType). (read-only)
---@field is_visible fun(self:lysa.ui.Widget):boolean Returns true if the widget is visible.
---@field show fun(self:lysa.ui.Widget, visible:boolean|nil):nil Shows or hides the widget (default true).
---@field is_enabled fun(self:lysa.ui.Widget):boolean Returns true if the widget is reactive to user action (mouse & keyboard).
---@field enable fun(self:lysa.ui.Widget, enabled:boolean|nil):nil Enables or disables widget reactions to input events (default true).
---@field set_pos fun(self:lysa.ui.Widget, x:number, y:number):nil Moves the widget to the given position.
---@field width number The widget width in pixels. (read-only)
---@field height number The widget height in pixels. (read-only)
---@field set_size fun(self:lysa.ui.Widget, width:number, height:number):nil Resizes the widget in pixels.
---@field rect any The size and position of the widget.
---@field set_rect fun(self:lysa.ui.Widget, x:number, y:number, width:number, height:number):nil Changes the size and position with x, y, width, height components.
---@field alignment integer The current widget placement alignment (see lysa.ui.Alignment).
---@field font any The current font of the widget.
---@field font_scale number The font scale.
---@field is_focused boolean True if the widget has keyboard focus. (read-only)
---@field parent lysa.ui.Widget|nil The parent widget, or nil. (read-only)
---@field remove fun(self:lysa.ui.Widget, child:lysa.ui.Widget):nil Removes a child widget.
---@field remove_all fun(self:lysa.ui.Widget):nil Removes all children widgets recursively.
---@field padding number Children padding (space between children).
---@field vborder number Vertical border size.
---@field hborder number Horizontal border size.
---@field is_draw_background boolean False if the background is transparent.
---@field is_pushed boolean True if the widget is currently pushed (e.g. mouse button down).
---@field is_pointed boolean True if the widget is currently pointed by the mouse. (read-only)
---@field is_freezed boolean True if the widget is not responding to events.
---@field is_overlapping boolean True if the widget overlaps other widgets. (read-only)
---@field children_rect any The rectangle enclosing all children. (read-only)
---@field refresh fun(self:lysa.ui.Widget):nil Forces a full redraw of the widget.
---@field group_index integer The user-defined group index.
---@field transparency number The transparency alpha value.
---@field resize_children fun(self:lysa.ui.Widget):nil Resizes children widgets.
---@field add_child fun(self:lysa.ui.Widget, child:lysa.ui.Widget, alignment:integer, resource:string|nil):lysa.ui.Widget Adds a child widget with alignment and optional resource string.

---@class lysa.ui.Panel : lysa.ui.Widget

---@class lysa.ui.Box : lysa.ui.Panel

---@class lysa.ui.Button : lysa.ui.Box

---@class lysa.ui.CheckWidget : lysa.ui.Widget
---@field state integer The current state of the widget (see lysa.ui.CheckState).

---@class lysa.ui.ToggleButton : lysa.ui.CheckWidget

---@class lysa.ui.Line : lysa.ui.Widget
---@field style integer The current line orientation (see lysa.ui.LineStyle).

---@class lysa.ui.HLine : lysa.ui.Line

---@class lysa.ui.VLine : lysa.ui.Line

---@class lysa.ui.Frame : lysa.ui.Panel
---@field title string The frame title.
---@field title_color any The title text color.

---@class lysa.ui.Text : lysa.ui.Widget
---@field text string The displayed text.
---@field text_color any The text color.
---@field size {number, number} The {width, height} size of the rendered text. (read-only)

---@class lysa.ui.TextEdit : lysa.ui.Widget
---@field is_read_only boolean True if the widget is read-only.
---@field text string The current text.
---@field sel_start integer The selection start position.
---@field first_displayed_char integer The index of the first displayed character. (read-only)
---@field displayed_text string The text currently being displayed in the text box. (read-only)
---@field set_resources fun(self:lysa.ui.TextEdit, resource:string):nil Sets the UI resources for the text edit.

---@class lysa.ui.Image : lysa.ui.Widget
---@field set_auto_size fun(self:lysa.ui.Image, autoSize:boolean):nil Sets whether to automatically resize the widget to the image size.
---@field color any The image color tint.
---@field image any The currently displayed image, or nil.

---@class lysa.ui.ValueSelect : lysa.ui.Widget
---@field min number The minimum value.
---@field max number The maximum value.
---@field value number The current value.
---@field step number The step increment.

---@class lysa.ui.ScrollBar : lysa.ui.ValueSelect
---@field scroll_bar_type integer The scroll bar orientation (see lysa.ui.ScrollBarType). (read-only)
---@field set_resources fun(self:lysa.ui.ScrollBar, area:string, cage:string):nil Sets the UI resources for the scroll bar (area = scroll area, cage = scroll lift).

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
---@field resizeable_borders integer Bitmask of which borders can resize the window (see lysa.ui.ResizeableBorder).
---@field widget lysa.ui.Widget The root widget that covers the entire window. (read-only)
---@field style any The current style layout, or nil.
---@field set_widget fun(self:lysa.ui.Window, child:lysa.ui.Widget|nil, resources:string|nil, padding:number|nil):nil Sets the root widget. Call setStyle(nil) first if no layout has been set previously.
---@field set_focused_widget fun(self:lysa.ui.Window, widget:lysa.ui.Widget):nil Moves keyboard focus to the given widget.
---@field width number The client area width.
---@field height number The client area height.
---@field rect any The client area position and size.
---@field set_pos fun(self:lysa.ui.Window, x:number, y:number):nil Sets the window position (bottom-left corner).
---@field set_x fun(self:lysa.ui.Window, x:number):nil Sets the X position (bottom-left).
---@field set_y fun(self:lysa.ui.Window, y:number):nil Sets the Y position (bottom-left).
---@field is_visible boolean Whether the window is visible. The change is effective at the start of the next frame.
---@field show fun(self:lysa.ui.Window):nil Shows the window (effective next frame).
---@field hide fun(self:lysa.ui.Window):nil Hides the window (effective next frame).
---@field set_transparency fun(self:lysa.ui.Window, alpha:number):nil Sets the alpha transparency value.
---@field set_minimum_size fun(self:lysa.ui.Window, width:number, height:number):nil Sets the minimum window size (default 2x2).
---@field set_maximum_size fun(self:lysa.ui.Window, width:number, height:number):nil Sets the maximum window size.
---@field minimum_width number The minimum width of the window. (read-only)
---@field minimum_height number The minimum height of the window. (read-only)
---@field maximum_width number The maximum width of the window. (read-only)
---@field maximum_height number The maximum height of the window. (read-only)
---@field font any The default font for the window.
---@field font_scale number The default font scale.
---@field text_color any The default text color.
---@field refresh fun(self:lysa.ui.Window):nil Forces a redraw of all the UI.
---@field add_child fun(self:lysa.ui.Window, child:lysa.ui.Widget, alignment:integer, resource:string|nil):lysa.ui.Widget Adds a child widget to the root widget.
---@field remove_child fun(self:lysa.ui.Window, child:lysa.ui.Widget):nil Removes a child widget from the root widget.
---@field create_text fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment, text:string):lysa.ui.Text Creates and adds a Text widget to the window.

---@class lysa.ui.WindowManager
---@field create fun(self:lysa.ui.WindowManager, rect:any):lysa.ui.Window Creates and adds a new UI window with the given rectangle.
---@field add fun(self:lysa.ui.WindowManager, window:lysa.ui.Window):lysa.ui.Window Adds an existing UI window to the manager.
---@field remove fun(self:lysa.ui.WindowManager, window:lysa.ui.Window):nil Removes a UI window (effective at the start of the next frame).
---@field default_font any The default font loaded at creation. (read-only)
---@field default_font_scale number The default font scale. (read-only)
---@field default_text_color any The default text color. (read-only)
---@field aspect_ratio number The aspect ratio of the managed rendering window. (read-only)
---@field refresh fun(self:lysa.ui.WindowManager):nil Forces a redraw of all UI at the start of the next frame.
---@field resize_delta number The pixel delta used for window border resizing (default 5.0). (read-only)
---@field set_enable_window_resizing fun(self:lysa.ui.WindowManager, enable:boolean):nil Enables or disables UI window resizing by the user.

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

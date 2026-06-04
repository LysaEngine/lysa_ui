---@meta
---@diagnostic disable: missing-return, lowercase-global

---@class lysa.ui.Alignment Constants controlling how a widget is placed inside its parent's content area.
---@field NONE integer No automatic alignment; position is set manually.
---@field FILL integer Centered and resized to fill the parent's entire content area.
---@field CENTER integer Centered horizontally and vertically within the parent (takes all available space).
---@field HCENTER integer Horizontally centered; vertical position is not constrained.
---@field VCENTER integer Vertically centered; horizontal position is not constrained.
---@field TOP integer Stacked at the top of the parent.
---@field BOTTOM integer Stacked at the bottom of the parent.
---@field LEFT integer Stacked at the left of the parent.
---@field RIGHT integer Stacked at the right of the parent.
---@field TOPCENTER integer Stacked at the top and horizontally centered.
---@field BOTTOMCENTER integer Stacked at the bottom and horizontally centered.
---@field LEFTCENTER integer Stacked at the left and vertically centered.
---@field RIGHTCENTER integer Stacked at the right and vertically centered.
---@field TOPLEFT integer Stacked at the top and left-aligned.
---@field BOTTOMLEFT integer Stacked at the bottom and left-aligned.
---@field BOTTOMRIGHT integer Stacked at the bottom and right-aligned.
---@field TOPRIGHT integer Stacked at the top and right-aligned.
---@field LEFTTOP integer Stacked on the left side then aligned to the top.
---@field LEFTBOTTOM integer Stacked on the left side then aligned to the bottom.
---@field RIGHTBOTTOM integer Stacked on the right side then aligned to the bottom.
---@field RIGHTTOP integer Stacked on the right side then aligned to the top.
---@field CORNERTOPLEFT integer Pinned to the top-left corner of the parent.
---@field CORNERTOPRIGHT integer Pinned to the top-right corner of the parent.
---@field CORNERBOTTOMLEFT integer Pinned to the bottom-left corner of the parent.
---@field CORNERBOTTOMRIGHT integer Pinned to the bottom-right corner of the parent.

---@class lysa.ui.WidgetType Integer constants identifying the concrete type of a widget.
---@field WIDGET integer Transparent container widget with no visual representation.
---@field PANEL integer Rectangular widget with only a background fill.
---@field BOX integer Rectangular widget with a border and a background fill.
---@field LINE integer A horizontal or vertical separator line.
---@field FRAME integer A box with a title label in its border.
---@field BUTTON integer A push button that fires OnClick on release.
---@field TOGGLEBUTTON integer A two-state (on/off) toggle button.
---@field TEXT integer A single-line read-only text label.
---@field TEXTEDIT integer An editable single-line text input field.
---@field SCROLLBAR integer A scroll bar with configurable min, max, and current position.
---@field TREEVIEW integer A hierarchical tree of expandable/collapsible items.
---@field IMAGE integer A widget that displays a 2-D GPU image.
---@field POPUP integer A popup panel placed at fixed (x, y) coordinates and drawn on top of siblings.
---@field LIST integer Base type for list-of-widgets containers.
---@field LISTBOX integer A scrollable list of widgets with selection highlight.
---@field SELECTION integer A selection highlight rectangle used inside a ListBox.
---@field PROGRESSBAR integer A rectangular progress bar widget.
---@field SCROLLBOX integer A scrollable container with horizontal and vertical scroll bars.

---@class lysa.ui.CheckState Check/toggle state constants for CheckWidget and ToggleButton.
---@field UNCHECK integer Unchecked / OFF state.
---@field CHECK integer Checked / ON state.

---@class lysa.ui.LineStyle Orientation constants for Line widgets.
---@field HORIZ integer Horizontal line.
---@field VERT integer Vertical line.

---@class lysa.ui.ScrollBarType Orientation constants for ScrollBar widgets.
---@field HORIZONTAL integer Horizontal scroll bar.
---@field VERTICAL integer Vertical scroll bar.

---@class lysa.ui.ProgressBarType Orientation constants for ProgressBar widgets.
---@field HORIZONTAL integer Horizontal progress bar (fills left to right).
---@field VERTICAL integer Vertical progress bar (fills bottom to top).

---@class lysa.ui.ProgressBarDisplay Optional text display mode drawn over the progress bar.
---@field NONE integer No text displayed.
---@field PERCENT integer Display the current value as a percentage.
---@field VALUE integer Display the raw current value.

---@class lysa.ui.ResizeableBorder Bitmask constants for which borders of a Window can be dragged to resize it.
---@field NONE integer No border is resizable.
---@field LEFT integer The left border is resizable.
---@field RIGHT integer The right border is resizable.
---@field TOP integer The top border is resizable.
---@field BOTTOM integer The bottom border is resizable.

---@class lysa.ui.UIEvent String event-type constants used when subscribing to widget events via EventManager.
---@field OnCreate string Fired after the widget has been created and added to the hierarchy.
---@field OnDestroy string Fired just before the widget is destroyed.
---@field OnKeyDown string Fired when a key is pressed while the widget has keyboard focus.
---@field OnKeyUp string Fired when a key is released while the widget has keyboard focus.
---@field OnMouseDown string Fired when a mouse button is pressed over the widget.
---@field OnMouseUp string Fired when a mouse button is released over the widget.
---@field OnMouseMove string Fired when the mouse cursor moves over the widget.
---@field OnGotFocus string Fired when the widget acquires keyboard focus.
---@field OnLostFocus string Fired when the widget loses keyboard focus.
---@field OnShow string Fired when the widget's visibility changes to visible.
---@field OnHide string Fired when the widget's visibility changes to hidden.
---@field OnEnable string Fired when the widget transitions to the enabled state.
---@field OnDisable string Fired when the widget transitions to the disabled state.
---@field OnTextChange string Fired when the widget's text content changes (TextEdit, Text).
---@field OnTextInput string Fired on each character input from the user (TextEdit).
---@field OnClick string Fired when a Button or ToggleButton is clicked.
---@field OnStateChange string Fired when a CheckWidget changes state (checked ↔ unchecked).
---@field OnValueChange string Fired when the value of a ValueSelect / ScrollBar changes.
---@field OnRangeChange string Fired when the min/max range of a ValueSelect / ScrollBar changes.
---@field OnResize string Fired when the window size changes.
---@field OnMove string Fired when the window position changes.
---@field OnInsertItem string Fired when an item is inserted into a List (ListBox, etc.).
---@field OnRemoveItem string Fired when an item is removed from a List.
---@field OnSelectItem string Fired when the selected item of a List changes.

---@class lysa.ui.Widget The base class for all UI widgets. Provides layout, input handling, and child management.
---@field id integer The unique ID
---@field type integer The concrete widget type (see lysa.ui.WidgetType). (read-only)
---@field children lysa.ui.Widget[] Ordered list of direct child widgets.
---@field visible boolean True if the widget is visible; false hides it and all its children.
---@field user_data any Lua user data.
---@field is_enabled fun(self:lysa.ui.Widget):boolean Returns true if the widget responds to mouse and keyboard input.
---@field enable fun(self:lysa.ui.Widget, enabled:boolean|nil):nil Enables or disables the widget's response to input events (pass nil or true to enable, false to disable).
---@field set_pos fun(self:lysa.ui.Widget, x:number, y:number):nil Moves the widget to the given position in its parent's coordinate space.
---@field width number The widget width in virtual screen units.
---@field height number The widget height in virtual screen units.
---@field set_size fun(self:lysa.ui.Widget, width:number, height:number):nil Resizes the widget to the given width and height in virtual screen units.
---@field rect lysa.Rect The current position and size of the widget as a Rect.
---@field set_rect fun(self:lysa.ui.Widget, x:number, y:number, width:number, height:number):nil Sets the widget's position and size in one call.
---@field alignment integer The current placement alignment within the parent (see lysa.ui.Alignment).
---@field font lysa.Font The font used to render text within this widget.
---@field font_scale number The scale factor applied to the widget's font.
---@field focused boolean True if this widget currently holds keyboard focus. (read-only)
---@field parent lysa.ui.Widget|nil The direct parent widget, or nil if this is a root widget. (read-only)
---@field remove fun(self:lysa.ui.Widget, child:lysa.ui.Widget):nil Removes and detaches the given direct child widget.
---@field remove_all fun(self:lysa.ui.Widget):nil Removes and detaches all descendant widgets recursively.
---@field padding number Spacing in virtual screen units between children during layout.
---@field vborder number Vertical inset between the widget edges and its content area.
---@field hborder number Horizontal inset between the widget edges and its content area.
---@field draw_background boolean False if the widget's background should be drawn transparently.
---@field pushed boolean True if the widget is currently in a pressed state (e.g. mouse button held down over it). (read-only)
---@field pointed boolean True if the mouse cursor is currently over this widget. (read-only)
---@field freezed boolean True if the widget ignores all input events without being visually disabled.
---@field overlapping boolean True if this widget visually overlaps one or more siblings. (read-only)
---@field children_rect lysa.Rect The smallest Rect enclosing all direct children. (read-only)
---@field group_index integer User-defined integer tag used to identify widgets within a logical group.
---@field transparency number Global alpha multiplier for the widget (0.0 = fully transparent, 1.0 = opaque).
---@field resize_children fun(self:lysa.ui.Widget):nil Triggers a layout pass that repositions and resizes all direct children according to their alignment.
---@field create_text fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment, text:string):lysa.ui.Text Creates and adds a Text child widget with the given alignment and initial text. @overload
---@field create_text fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment, text:string):lysa.ui.Text Creates and adds a Text child widget, loading its style from a resource string. @overload
---@field create_panel fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.Panel Creates and adds a Panel child widget with the given alignment. @overload
---@field create_panel fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.Panel Creates and adds a Panel child widget, loading its style from a resource string. @overload
---@field create_popup fun(self:lysa.ui.Widget, x:number, y:number):lysa.ui.Popup Creates and adds a Popup child widget at the given position, rendered on top of siblings. @overload
---@field create_popup fun(self:lysa.ui.Widget, resource:string, x:number, y:number):lysa.ui.Popup Creates and adds a Popup child widget at the given position, loading its style from a resource string. @overload
---@field create_box fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.Box Creates and adds a Box child widget with the given alignment. @overload
---@field create_box fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.Box Creates and adds a Box child widget, loading its style from a resource string. @overload
---@field create_button fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.Button Creates and adds a Button child widget with the given alignment. @overload
---@field create_button fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.Button Creates and adds a Button child widget, loading its style from a resource string. @overload
---@field create_toggle_button fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.ToggleButton Creates and adds a ToggleButton child widget with the given alignment. @overload
---@field create_toggle_button fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.ToggleButton Creates and adds a ToggleButton child widget, loading its style from a resource string. @overload
---@field create_hline fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.HLine Creates and adds a horizontal Line child widget with the given alignment. @overload
---@field create_hline fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.HLine Creates and adds a horizontal Line child widget, loading its style from a resource string. @overload
---@field create_vline fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.VLine Creates and adds a vertical Line child widget with the given alignment. @overload
---@field create_vline fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.VLine Creates and adds a vertical Line child widget, loading its style from a resource string. @overload
---@field create_frame fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment, title:string):lysa.ui.Frame Creates and adds a Frame child widget with the given alignment and title. @overload
---@field create_frame fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment, title:string):lysa.ui.Frame Creates and adds a Frame child widget, loading its style from a resource string. @overload
---@field create_text_edit fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment, text:string|nil):lysa.ui.TextEdit Creates and adds a TextEdit child widget with the given alignment and optional initial text. @overload
---@field create_text_edit fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment, text:string|nil):lysa.ui.TextEdit Creates and adds a TextEdit child widget, loading its style from a resource string. @overload
---@field create_image fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.Image Creates and adds an Image child widget with the given alignment. @overload
---@field create_image fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.Image Creates and adds an Image child widget, loading its style from a resource string. @overload
---@field create_image fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment, autoresize:boolean, fixedsize:boolean):lysa.ui.Image Creates and adds an Image child widget with auto-resize and fixed-size options. @overload
---@field create_vscrollbar fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.VScrollBar Creates and adds a vertical ScrollBar child widget with the given alignment. @overload
---@field create_vscrollbar fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.VScrollBar Creates and adds a vertical ScrollBar child widget, loading its style from a resource string. @overload
---@field create_hscrollbar fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.HScrollBar Creates and adds a horizontal ScrollBar child widget with the given alignment. @overload
---@field create_hscrollbar fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.HScrollBar Creates and adds a horizontal ScrollBar child widget, loading its style from a resource string. @overload
---@field create_tree_view fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.TreeView Creates and adds a TreeView child widget with the given alignment. @overload
---@field create_tree_view fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.TreeView Creates and adds a TreeView child widget, loading its style from a resource string. @overload
---@field create_widget fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.Widget Creates and adds a transparent container Widget child with the given alignment. @overload
---@field create_widget fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.Widget Creates and adds a transparent container Widget child, loading its style from a resource string. @overload
---@field create_list_box fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.ListBox Creates and adds a ListBox child widget with the given alignment. @overload
---@field create_list_box fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.ListBox Creates and adds a ListBox child widget, loading its style from a resource string. @overload
---@field create_progress_bar fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.ProgressBar Creates and adds a ProgressBar child widget with the given alignment. @overload
---@field create_progress_bar fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.ProgressBar Creates and adds a ProgressBar child widget, loading its style from a resource string. @overload
---@field create_vprogress_bar fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.VProgressBar Creates and adds a vertical ProgressBar child widget with the given alignment. @overload
---@field create_vprogress_bar fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.VProgressBar Creates and adds a vertical ProgressBar child widget, loading its style from a resource string. @overload
---@field create_hprogress_bar fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.HProgressBar Creates and adds a horizontal ProgressBar child widget with the given alignment. @overload
---@field create_hprogress_bar fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.HProgressBar Creates and adds a horizontal ProgressBar child widget, loading its style from a resource string. @overload
---@field create_scroll_box fun(self:lysa.ui.Widget, alignment:lysa.ui.Alignment):lysa.ui.ScrollBox Creates and adds a ScrollBox child widget with the given alignment. @overload
---@field create_scroll_box fun(self:lysa.ui.Widget, resource:string, alignment:lysa.ui.Alignment):lysa.ui.ScrollBox Creates and adds a ScrollBox child widget, loading its style from a resource string. @overload
---@field add_child fun(self:lysa.ui.Widget, child:lysa.ui.Widget, alignment:integer, resource:string|nil):lysa.ui.Widget Adds a pre-constructed child widget with the given alignment and optional resource string.

---@class lysa.ui.Panel : lysa.ui.Widget A rectangular widget that renders only a background fill; no border.

---@class lysa.ui.Popup : lysa.ui.Panel A Panel placed at a fixed (x, y) position relative to its parent and always drawn on top of sibling widgets.
---@field x number Horizontal offset from the parent widget's top-left corner (read-only).
---@field y number Vertical offset from the parent widget's top-left corner (read-only).

---@class lysa.ui.Box : lysa.ui.Panel A Panel with a visible border drawn around its edges.

---@class lysa.ui.Button : lysa.ui.Box A push button that fires the OnClick event when pressed and released by the user.

---@class lysa.ui.CheckWidget : lysa.ui.Widget Base class for widgets with a binary checked/unchecked state (e.g. ToggleButton).
---@field state integer The current check state (see lysa.ui.CheckState): UNCHECK or CHECK.

---@class lysa.ui.ToggleButton : lysa.ui.CheckWidget A button that alternates between checked and unchecked states on each click. Fires OnStateChange on toggle.

---@class lysa.ui.Line : lysa.ui.Widget A thin separator line, either horizontal or vertical.
---@field style integer The line orientation (see lysa.ui.LineStyle): HORIZ or VERT.

---@class lysa.ui.HLine : lysa.ui.Line A horizontal separator line widget.

---@class lysa.ui.VLine : lysa.ui.Line A vertical separator line widget.

---@class lysa.ui.Frame : lysa.ui.Panel A bordered panel with a title string rendered in its top border.
---@field title string The text displayed in the frame's title border.
---@field title_color lysa.float4 RGBA color of the title text.

---@class lysa.ui.Text : lysa.ui.Widget A single-line read-only text label.
---@field text string The string displayed by this label.
---@field text_color lysa.float4 RGBA color of the displayed text.
---@field size lysa.float2 Rendered pixel size of the text as (width, height). (read-only)

---@class lysa.ui.TextEdit : lysa.ui.Widget A single-line editable text input field. Fires OnTextChange and OnTextInput events.
---@field is_read_only boolean True if the field is read-only; the user can view but not edit the text.
---@field text string The current text content of the input field.
---@field sel_start integer Character index of the start of the current text selection.
---@field first_displayed_char integer Index of the first character currently visible in the field (scroll offset). (read-only)
---@field displayed_text string The substring of text currently visible inside the widget bounds. (read-only)
---@field set_resources fun(self:lysa.ui.TextEdit, resource:string):nil Reloads the visual style of this TextEdit from the given resource string.

---@class lysa.ui.Image : lysa.ui.Widget A widget that displays a GPU image with an optional color tint.
---@field set_auto_size fun(self:lysa.ui.Image, autoSize:boolean):nil When true, the widget automatically resizes itself to match the displayed image's pixel dimensions.
---@field color lysa.float4 RGBA color tint multiplied with the image pixels (default white = no tint).
---@field image lysa.Image The GPU image currently displayed, or nil if none is set. (read-only)
---@field set_image fun(self:lysa.ui.Image, image:lysa.Image):nil Sets the displayed image from an existing GPU Image object. @overload
---@field set_image fun(self:lysa.ui.Image, uri:string):nil Loads and sets the displayed image from the given virtual URI. @overload

---@class lysa.ui.ValueSelect : lysa.ui.Widget Base class for widgets that expose a numeric value within a bounded range.
---@field min number The minimum selectable value.
---@field max number The maximum selectable value.
---@field value number The current value, clamped to [min, max].
---@field step number The increment applied on each user interaction step.

---@class lysa.ui.ScrollBar : lysa.ui.ValueSelect A scroll bar widget whose value represents a scroll position within [min, max].
---@field scroll_bar_type integer The orientation of this scroll bar (see lysa.ui.ScrollBarType). (read-only)
---@field set_resources fun(self:lysa.ui.ScrollBar, area:string, cage:string):nil Reloads the visual style: area = resource string for the scroll track, cage = resource string for the scroll thumb.

---@class lysa.ui.VScrollBar : lysa.ui.ScrollBar A vertical scroll bar widget.

---@class lysa.ui.HScrollBar : lysa.ui.ScrollBar A horizontal scroll bar widget.

---@class lysa.ui.TreeViewItem : lysa.ui.Panel A single row in a TreeView, which can contain a child widget and be expanded or collapsed.
---@field item lysa.ui.Widget The widget rendered as the visible content of this tree row.
---@field level integer Depth of this item in the tree hierarchy (root items have level 0).
---@field selected boolean True if this item is currently selected.
---@field expanded boolean True if this item's children are currently visible.

---@class lysa.ui.TreeView : lysa.ui.Widget A hierarchical list widget that displays items in an expandable/collapsible tree structure.
---@field set_resources fun(self:lysa.ui.TreeView, resBox:string, resScroll:string, resHandle:string):nil Reloads the visual style: resBox = row style, resScroll = scroll bar style, resHandle = expand/collapse handle style.
---@field remove_all_items fun(self:lysa.ui.TreeView):nil Removes and destroys all items from the tree.
---@field add_item fun(self:lysa.ui.TreeView, parent_or_widget:lysa.ui.TreeViewItem|lysa.ui.Widget, widget:lysa.ui.Widget|nil):lysa.ui.TreeViewItem Adds an item to the tree. Pass only a widget to add a root-level item; pass a TreeViewItem and a widget to add a child under that item.
---@field expand fun(self:lysa.ui.TreeView, item:lysa.ui.Widget):nil Programmatically expands the tree item associated with the given content widget.

---@class lysa.ui.List : lysa.ui.Widget Base class for all list-of-widgets widgets. Fires OnInsertItem, OnRemoveItem and OnSelectItem events.
---@field NO_SELECTION integer Sentinel value returned by selected_index when nothing is selected.
---@field count integer Number of items currently in the list. (read-only)
---@field selected_index integer Index (0-based) of the selected item, or NO_SELECTION if nothing is selected. (read-only)
---@field selected_item lysa.ui.Widget|nil The currently selected widget, or nil. (read-only)
---@field add_item fun(self:lysa.ui.List, item:lysa.ui.Widget, alignment:integer, resource:string):integer Adds a widget at the end of the list and returns its 0-based index.
---@field remove_item fun(self:lysa.ui.List, index:integer):nil Removes the item at the given 0-based index.
---@field remove_all_items fun(self:lysa.ui.List):nil Removes all items from the list.
---@field get_item fun(self:lysa.ui.List, index:integer):lysa.ui.Widget Returns the widget at the given 0-based index.
---@field select fun(self:lysa.ui.List, index:integer):nil Selects the item at the given index; pass NO_SELECTION to clear the selection.

---@class lysa.ui.ListBox : lysa.ui.List A scrollable list of widgets with a selection highlight rectangle. Supports keyboard navigation.
---@field set_resources fun(self:lysa.ui.ListBox, resBox:string, resScroll:string, resSel:string):nil Reloads the visual style: resBox = inner background box, resScroll = vertical scroll bar, resSel = selection highlight.
---@field selection_widget lysa.ui.Selection The internal selection highlight widget. (read-only)

---@class lysa.ui.Selection : lysa.ui.Panel A selection highlight rectangle drawn behind the selected item of a ListBox.

---@class lysa.ui.ProgressBar : lysa.ui.ValueSelect A rectangular progress bar widget that fills as its value increases.
---@field orientation integer The fill orientation (see lysa.ui.ProgressBarType): HORIZONTAL or VERTICAL.
---@field display integer The optional text display mode (see lysa.ui.ProgressBarDisplay): NONE, PERCENT, or VALUE.
---@field set_resources fun(self:lysa.ui.ProgressBar, resBox:string):nil Reloads the visual style from the given inner box resource string.

---@class lysa.ui.VProgressBar : lysa.ui.ProgressBar A vertical progress bar (fills bottom to top).

---@class lysa.ui.HProgressBar : lysa.ui.ProgressBar A horizontal progress bar (fills left to right).

---@class lysa.ui.ScrollBox : lysa.ui.Box A scrollable container with horizontal and vertical scroll bars. Add children via add_content.
---@field set_resources fun(self:lysa.ui.ScrollBox, resBox:string, resVScroll:string, resHScroll:string):nil Reloads the visual style: resBox = inner box, resVScroll = vertical scroll bar, resHScroll = horizontal scroll bar.
---@field add_content fun(self:lysa.ui.ScrollBox, child:lysa.ui.Widget, alignment:integer, resource:string):lysa.ui.Widget Adds a child widget to the scrollable inner box.
---@field remove_content fun(self:lysa.ui.ScrollBox, child:lysa.ui.Widget):nil Removes a child widget from the inner box.
---@field remove_all_content fun(self:lysa.ui.ScrollBox):nil Removes all children from the inner box.
---@field inner_box lysa.ui.Box The scrollable inner box containing the added content widgets. (read-only)

---@class lysa.ui.Window A UI window that owns a root Widget hierarchy and is managed by the WindowManager.
---@field resizeable_borders integer Bitmask of which window borders are user-resizable (see lysa.ui.ResizeableBorder).
---@field widget lysa.ui.Widget The root widget that covers the entire client area of the window. (read-only)
---@field style any The currently active style layout object, or nil if no layout has been applied.
---@field set_widget fun(self:lysa.ui.Window, child:lysa.ui.Widget|nil, resources:string|nil, padding:number|nil):nil Replaces the root widget. Call set_widget(nil) first if a layout was previously applied.
---@field set_focused_widget fun(self:lysa.ui.Window, widget:lysa.ui.Widget):nil Moves keyboard focus to the specified widget within this window.
---@field width number Client area width in virtual screen units.
---@field height number Client area height in virtual screen units.
---@field rect lysa.Rect Client area position and size as a Rect.
---@field set_pos fun(self:lysa.ui.Window, x:number, y:number):nil Moves the window's bottom-left corner to the given position.
---@field x number Current X position of the window's bottom-left corner.
---@field y number Current Y position of the window's bottom-left corner.
---@field visible boolean Whether the window is visible; changes take effect at the start of the next frame.
---@field close fun(self:lysa.ui.Window):nil Closes and removes the window (effective at the start of the next frame).
---@field show fun(self:lysa.ui.Window):nil Makes the window visible (effective at the start of the next frame).
---@field hide fun(self:lysa.ui.Window):nil Hides the window without destroying it (effective at the start of the next frame).
---@field set_transparency fun(self:lysa.ui.Window, alpha:number):nil Sets the global alpha transparency for the entire window (0.0 = invisible, 1.0 = fully opaque).
---@field set_minimum_size fun(self:lysa.ui.Window, width:number, height:number):nil Sets the minimum dimensions the user can resize the window to (default 2×2).
---@field set_maximum_size fun(self:lysa.ui.Window, width:number, height:number):nil Sets the maximum dimensions the user can resize the window to.
---@field minimum_width number The minimum width the window can be resized to. (read-only)
---@field minimum_height number The minimum height the window can be resized to. (read-only)
---@field maximum_width number The maximum width the window can be resized to. (read-only)
---@field maximum_height number The maximum height the window can be resized to. (read-only)
---@field font lysa.Font The default font applied to widgets that do not specify their own.
---@field font_scale number The default font scale applied to widgets that do not specify their own.
---@field text_color lysa.float4 The default text RGBA color applied to widgets that do not specify their own.
---@field refresh fun(self:lysa.ui.Window):nil Forces a full redraw of all widgets in this window at the start of the next frame.
---@field add_child fun(self:lysa.ui.Window, child:lysa.ui.Widget, alignment:integer, resource:string|nil):lysa.ui.Widget Adds a pre-constructed widget to the root widget with the given alignment and optional resource string.
---@field remove_child fun(self:lysa.ui.Window, child:lysa.ui.Widget):nil Removes the given widget from the root widget.
---@field create_text fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment, text:string):lysa.ui.Text Creates and adds a Text widget. @overload
---@field create_text fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment, text:string):lysa.ui.Text Creates and adds a Text widget, loading its style from a resource string. @overload
---@field create_panel fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.Panel Creates and adds a Panel widget. @overload
---@field create_panel fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.Panel Creates and adds a Panel widget, loading its style from a resource string. @overload
---@field create_popup fun(self:lysa.ui.Window, x:number, y:number):lysa.ui.Popup Creates and adds a Popup widget at the given position, rendered on top of siblings. @overload
---@field create_popup fun(self:lysa.ui.Window, resource:string, x:number, y:number):lysa.ui.Popup Creates and adds a Popup widget at the given position, loading its style from a resource string. @overload
---@field create_box fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.Box Creates and adds a Box widget (bordered panel). @overload
---@field create_box fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.Box Creates and adds a Box widget (bordered panel), loading its style from a resource string. @overload
---@field create_button fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.Button Creates and adds a Button widget. @overload
---@field create_button fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.Button Creates and adds a Button widget, loading its style from a resource string. @overload
---@field create_toggle_button fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.ToggleButton Creates and adds a ToggleButton widget. @overload
---@field create_toggle_button fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.ToggleButton Creates and adds a ToggleButton widget, loading its style from a resource string. @overload
---@field create_hline fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.HLine Creates and adds a horizontal Line widget. @overload
---@field create_hline fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.HLine Creates and adds a horizontal Line widget, loading its style from a resource string. @overload
---@field create_vline fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.VLine Creates and adds a vertical Line widget. @overload
---@field create_vline fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.VLine Creates and adds a vertical Line widget, loading its style from a resource string. @overload
---@field create_frame fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment, title:string):lysa.ui.Frame Creates and adds a Frame widget with the given title. @overload
---@field create_frame fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment, title:string):lysa.ui.Frame Creates and adds a Frame widget with the given title, loading its style from a resource string. @overload
---@field create_text_edit fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment, text:string|nil):lysa.ui.TextEdit Creates and adds a TextEdit widget with optional initial text. @overload
---@field create_text_edit fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment, text:string|nil):lysa.ui.TextEdit Creates and adds a TextEdit widget, loading its style from a resource string. @overload
---@field create_image fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.Image Creates and adds an Image widget. @overload
---@field create_image fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.Image Creates and adds an Image widget, loading its style from a resource string. @overload
---@field create_image fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment, autoresize:boolean, fixedsize:boolean):lysa.ui.Image Creates and adds an Image widget with auto-resize and fixed-size options. @overload
---@field create_vscrollbar fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.VScrollBar Creates and adds a vertical ScrollBar widget. @overload
---@field create_vscrollbar fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.VScrollBar Creates and adds a vertical ScrollBar widget, loading its style from a resource string. @overload
---@field create_hscrollbar fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.HScrollBar Creates and adds a horizontal ScrollBar widget. @overload
---@field create_hscrollbar fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.HScrollBar Creates and adds a horizontal ScrollBar widget, loading its style from a resource string. @overload
---@field create_tree_view fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.TreeView Creates and adds a TreeView widget. @overload
---@field create_tree_view fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.TreeView Creates and adds a TreeView widget, loading its style from a resource string. @overload
---@field create_widget fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.Widget Creates and adds a transparent container Widget. @overload
---@field create_widget fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.Widget Creates and adds a transparent container Widget, loading its style from a resource string. @overload
---@field create_list_box fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.ListBox Creates and adds a ListBox widget. @overload
---@field create_list_box fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.ListBox Creates and adds a ListBox widget, loading its style from a resource string. @overload
---@field create_progress_bar fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.ProgressBar Creates and adds a ProgressBar widget. @overload
---@field create_progress_bar fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.ProgressBar Creates and adds a ProgressBar widget, loading its style from a resource string. @overload
---@field create_vprogress_bar fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.VProgressBar Creates and adds a vertical ProgressBar widget. @overload
---@field create_vprogress_bar fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.VProgressBar Creates and adds a vertical ProgressBar widget, loading its style from a resource string. @overload
---@field create_hprogress_bar fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.HProgressBar Creates and adds a horizontal ProgressBar widget. @overload
---@field create_hprogress_bar fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.HProgressBar Creates and adds a horizontal ProgressBar widget, loading its style from a resource string. @overload
---@field create_scroll_box fun(self:lysa.ui.Window, alignment:lysa.ui.Alignment):lysa.ui.ScrollBox Creates and adds a ScrollBox widget. @overload
---@field create_scroll_box fun(self:lysa.ui.Window, resource:string, alignment:lysa.ui.Alignment):lysa.ui.ScrollBox Creates and adds a ScrollBox widget, loading its style from a resource string. @overload

---@class lysa.ui.WindowManager The central manager for all UI windows attached to a rendering target.
---@field create fun(self:lysa.ui.WindowManager, rect:lysa.Rect):lysa.ui.Window Creates and registers a new UI window with the given position and size.
---@field add fun(self:lysa.ui.WindowManager, window:lysa.ui.Window):lysa.ui.Window Registers an existing UI window with this manager so it receives update and render calls.
---@field remove fun(self:lysa.ui.WindowManager, window:lysa.ui.Window):nil Unregisters and destroys the given UI window (effective at the start of the next frame).
---@field default_font lysa.Font The default font loaded at manager creation, applied to new windows that do not specify their own. (read-only)
---@field default_font_scale number The default font scale applied to new windows that do not specify their own.
---@field default_text_color lysa.float4 The default text RGBA color applied to new windows that do not specify their own.
---@field aspect_ratio number The aspect ratio of the rendering window this manager is attached to. (read-only)
---@field refresh fun(self:lysa.ui.WindowManager):nil Forces a full redraw of all managed windows at the start of the next frame.
---@field resize_delta number Pixel distance from a window border within which a drag starts a resize operation (default 5.0). (read-only)
---@field set_enable_window_resizing fun(self:lysa.ui.WindowManager, enable:boolean):nil Globally enables or disables user-driven window resizing by dragging borders.

---@class lysa.ui The lysa.ui sub-module — immediate-mode UI widgets and window management.
---@field Alignment lysa.ui.Alignment Widget placement alignment constants.
---@field WidgetType lysa.ui.WidgetType Widget type identifier constants.
---@field CheckState lysa.ui.CheckState Check/toggle state constants.
---@field LineStyle lysa.ui.LineStyle Line orientation constants.
---@field ScrollBarType lysa.ui.ScrollBarType Scroll bar orientation constants.
---@field ProgressBarType lysa.ui.ProgressBarType Progress bar orientation constants.
---@field ProgressBarDisplay lysa.ui.ProgressBarDisplay Progress bar text display mode constants.
---@field ResizeableBorder lysa.ui.ResizeableBorder Window border resize permission constants.
---@field UIEvent lysa.ui.UIEvent Event type string constants for widget event subscriptions.
---@field Widget lysa.ui.Widget Base widget type (transparent container).
---@field Panel lysa.ui.Panel Background-only rectangular widget type.
---@field Popup lysa.ui.Popup Popup panel at fixed coordinates, drawn on top of siblings.
---@field Box lysa.ui.Box Bordered rectangular widget type.
---@field Button lysa.ui.Button Push button widget type.
---@field CheckWidget lysa.ui.CheckWidget Base type for widgets with a binary check state.
---@field ToggleButton lysa.ui.ToggleButton Two-state toggle button widget type.
---@field Line lysa.ui.Line Base separator line widget type.
---@field HLine lysa.ui.HLine Horizontal separator line widget type.
---@field VLine lysa.ui.VLine Vertical separator line widget type.
---@field Frame lysa.ui.Frame Titled bordered panel widget type.
---@field Text lysa.ui.Text Read-only text label widget type.
---@field TextEdit lysa.ui.TextEdit Editable text input field widget type.
---@field Image lysa.ui.Image GPU image display widget type.
---@field ValueSelect lysa.ui.ValueSelect Base type for numeric value selection widgets.
---@field ScrollBar lysa.ui.ScrollBar Base scroll bar widget type.
---@field VScrollBar lysa.ui.VScrollBar Vertical scroll bar widget type.
---@field HScrollBar lysa.ui.HScrollBar Horizontal scroll bar widget type.
---@field TreeViewItem lysa.ui.TreeViewItem Single expandable row within a TreeView.
---@field TreeView lysa.ui.TreeView Hierarchical expandable list widget type.
---@field List lysa.ui.List Base type for list-of-widgets containers.
---@field ListBox lysa.ui.ListBox Scrollable list with selection highlight widget type.
---@field Selection lysa.ui.Selection Selection highlight rectangle used inside a ListBox.
---@field ProgressBar lysa.ui.ProgressBar Rectangular progress bar widget type.
---@field VProgressBar lysa.ui.VProgressBar Vertical progress bar widget type.
---@field HProgressBar lysa.ui.HProgressBar Horizontal progress bar widget type.
---@field ScrollBox lysa.ui.ScrollBox Scrollable container with horizontal and vertical scroll bars.
---@field Window lysa.ui.Window UI window type managed by the WindowManager.
---@field WindowManager lysa.ui.WindowManager Central manager for all UI windows.

---@type lysa.ui
lysa.ui = {}
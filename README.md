# Lysa UI

Lysa UI is a C++23 user interface library designed specifically for the [Lysa engine](https://github.com/HenriMichelon/lysa)
offering a hybrid system with retained-mode components drawn using an immediate mode vector renderer. 

Please refer to the [Documentation](https://henrimichelon.github.io/LysaUI/) for detailed instructions on how to integrate and use the library.


## Features

### Widgets
- **Widget / Panel / Box** — transparent, background-only, and bordered container primitives
- **Popup** — panel placed at fixed (x, y) coordinates and always drawn on top of sibling widgets
- **Button** — clickable box with push state; **ToggleButton** for two-state toggle
- **Text** — single-line read-only label; **TextEdit** — editable field with selection, read-only mode, and long-text scrolling
- **Frame** — bordered panel with optional title and title color
- **Image** — 2D image display with auto-sizing and color tint
- **ScrollBar** — horizontal or vertical scroll control with page and step scrolling (`HScrollBar` / `VScrollBar` helpers)
- **ScrollBox** — scrollable container with automatic horizontal and vertical scroll bars; content is added to an inner box
- **TreeView** — hierarchical list with expand/collapse handles, item selection, and vertical scrolling
- **ListBox** — scrollable list of arbitrary widgets with keyboard navigation and a configurable selection highlight; base `List` class is extensible
- **ProgressBar** — horizontal or vertical progress bar with optional percentage or raw-value text overlay (`HProgressBar` / `VProgressBar` helpers)
- **Line** — horizontal or vertical separator (`HLine` / `VLine` helpers)

### Layout & Alignment
- 25 alignment modes covering fill, centering, edge stacking (top/bottom/left/right), corner pinning, and edge+direction combinations
- Uniform padding between children and configurable border sizing
- Recursive parent-child resize propagation
- Overlapping widget support

### Windowing
- Virtual **Window** containers with user-resizable borders (per-side flags), minimum/maximum size constraints, and visibility control
- **WindowManager** coordinates multiple simultaneous windows, manages focus, routes input events, and drives per-frame rendering

### Styling & Theming
- Pluggable **Style** system — implement a custom style by subclassing the abstract base
- Built-in **Classic** style: vector-drawn 3D appearance with flat, raised, and lowered modes
- Per-widget overrides: foreground/background colors, shadow colors, font and font scale, transparency (alpha 0–1), and background draw toggle
- Name-value style option system for style-specific configuration

### Event System
- Typed event signals for the full widget lifecycle: create/destroy, show/hide, enable/disable
- Input events: mouse down/up/move with coordinates, keyboard down/up, text input
- Semantic events: `OnClick`, `OnStateChange`, `OnValueChange`, `OnRangeChange`, `OnTextChange`
- List events: `OnInsertItem`, `OnRemoveItem`, `OnSelectItem`
- Window events: `OnResize`, `OnMove`, `OnGotFocus`, `OnLostFocus`
- Integrated with the Lysa engine's centralized event dispatcher; Lua callbacks supported when Lua bindings are enabled

## License

This project is licensed under the MIT License


## Note

The original version of this UI components was developed for the [NMO-SDK](https://github.com/HenriMichelon/nmo-sdk) project
between 1996 and 2001, then ported betwen 2024 and 2026 to C++ 23 for the [Lysa engine](https://github.com/LysaEngine). 



# Lysa UI

Lysa UI is a C++23 user interface library designed specifically for the [Lysa engine](https://github.com/HenriMichelon/lysa)
offering a hybrid system with retained-mode components drawn using an immediate mode vector renderer. 

Please refer to the [Documentation](https://henrimichelon.github.io/LysaUI/) for detailed instructions on how to integrate and use the library.


## Features

### Widgets
- **Widget / Panel / Box** — transparent, background-only, and bordered container primitives
- **Button** — clickable box with push state; **ToggleButton** for two-state toggle
- **Text** — single-line read-only label; **TextEdit** — editable field with selection, read-only mode, and long-text scrolling
- **Frame** — bordered panel with optional title and title color
- **Image** — 2D image display with auto-sizing and color tint
- **ScrollBar** — horizontal or vertical scroll control with page and step scrolling (`HScrollBar` / `VScrollBar` helpers)
- **TreeView** — hierarchical list with expand/collapse handles, item selection, and vertical scrolling
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
- Window events: `OnResize`, `OnMove`, `OnGotFocus`, `OnLostFocus`
- Integrated with the Lysa engine's centralized event dispatcher; Lua callbacks supported when Lua bindings are enabled

### Rendering
- Immediate-mode vector 2D renderer (retained-mode widget tree, immediate-mode draw calls)
- Font loading and rendering with per-widget font and scale overrides
- RGBA color system (`float4`, 0–1 range) throughout
- Before/after-children rendering hooks for style implementations
- Redraw-on-event optimisation with explicit force-refresh support


## License

This project is licensed under the MIT License



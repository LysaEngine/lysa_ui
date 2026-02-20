# Lysa UI

Lysa UI is a C++23 user interface library designed specifically for the [Lysa engine](https://github.com/HenriMichelon/lysa)
offering a hybrid system with retained-mode components drawn using an immediate mode vector renderer. 

## Features

- Powerful alignment and stacking system.
- Support for custom styles and appearances (includes a built-in Classic style).
- Integrated with the Lysa engine's event system for handling clicks, text changes, and more.
- Manage multiple virtual UI windows with focus and resizing support.

## Getting Started

### Prerequisites

- [Lysa engine](https://github.com/HenriMichelon/lysa)
- [Vireo RHI](https://github.com/HenriMichelon/vireo_rhi)
- C++23 compatible compiler (MSVC, LLVM, etc.)
- CMake 3.29+ with a build tool like Ninja

### Integration

Add Lysa UI to your project using CMake. You'll need to set the`LYSA_UI_PROJECT_DIR`, `LYSA_ENGINE_PROJECT_DIR` and `VIREO_RHI_PROJECT_DIR` variables in your environment or a `.env.cmake` file.

```cmake
# .env.cmake
set(VIREO_RHI_PROJECT_DIR "path/to/vireo_rhi")
set(LYSA_ENGINE_PROJECT_DIR "path/to/lysa_engine")
set(LYSA_UI_PROJECT_DIR "path/to/lysa_ui")
```

Then, add it via CMake:

```cmake
set(LUA_BINDING OFF)
set(DIRECTX_BACKEND ON)
set(FORWARD_RENDERER ON)
set(DEFERRED_RENDERER ON)
set(PHYSIC_ENGINE_JOLT ON)
set(PHYSIC_ENGINE_PHYSX OFF)
if(WIN32)
  set(DIRECTX_BACKEND ON)
endif ()
add_subdirectory(${LYSA_ENGINE_PROJECT_DIR})
add_subdirectory(${LYSA_UI_PROJECT_DIR})
target_link_libraries(your_target PUBLIC lysa_engine lysa_ui)
```

## Basic Usage

Here is a simple example of how to create a UI window and add a button:

```cpp
import lysa;
import lysa.ui;

// Initialize WindowManager
lysa::ui::WindowManager windowManager{renderingWindow, "app://res/fonts/MyFont", 0.5f};

// Create a UI window
const auto window = windowManager.create(lysa::RECT_FULLSCREEN);

// Create a panel and a button
const auto panel = window->create<lysa::ui::Box>("200,300", lysa::ui::Alignment::CENTER);
const auto button = panel->create<lysa::ui::Button>("100,80", lysa::ui::Alignment::TOPCENTER);
button->create<lysa::ui::Text>(lysa::ui::Alignment::CENTER, "Click Me!");

// Subscribe to events
ctx().events.subscribe(lysa::ui::UIEvent::OnClick, button->id, [](const lysa::Event&) {
    lysa::Log::info("Button clicked!");
});

```

## License

This project is licensed under the MIT License



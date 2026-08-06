# TypeWriter

TypeWriter is a small desktop typewriter simulator built with C++17 and SFML. It recreates the movement, sounds, and constrained writing area of a physical typewriter, and can save the current page as an image.

## Features

- Typewriter-style text entry and carriage movement
- Key, return, and margin-bell sound effects
- Sound mute, page clear, and image export controls
- Page export to `resources/saved_pages/`

## Requirements

- A C++17 compiler
- CMake 3.16 or newer
- SFML 2.5 or newer (`graphics`, `window`, `system`, `audio`, and `network`)

On macOS with Homebrew:

```bash
brew install cmake sfml@2
```

SFML 3 is not currently supported.

## Build and run

```bash
cmake -S . -B build
cmake --build build
./build/TypeWriter
```

Run the executable from the repository root so it can locate the `resources` directory.

## Controls

- Type to add characters
- `Enter` or `Down Arrow`: move to the next line
- `Up Arrow`: move to the previous line
- `Left Arrow` / `Right Arrow`: move the carriage
- `Tab`: return the carriage to the starting position
- Toolbar buttons: mute sound, save the page, or clear the page

## Project status

This is an experimental personal project. The interface is currently tuned for large displays and supports printable ASCII characters.


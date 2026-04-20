# panda_gfx

GFX library for Micro-Panda. Targets MCU (ESP32, RP2040) and hosted platforms.
Strip-buffer rendering pipeline with node-based scene tree.

## Architecture

- **`Driver`** — driver table: `width`, `height`, `set_rotation`, `wait`, `flush(x, y, w, h, buffer)`
- **`Graphics`** — one instance per display; holds driver reference, root node, strip buffers, format, background color
- **Strip buffer** — one or two `u8[]` buffers; double-buffer: CPU renders back while DMA sends front
- **Rotation** — fully owned by driver (`set_rotation` configures MADCTL/segment remap); `Graphics` only tracks `view_w`/`view_h`
- **Node tree** — `root: &Node`; each node renders itself into `RenderContext` (strip window clipping)
- **Canvas** — indexed pixel buffer (Index1/2/4/8) + `u16[]` palette; palette-only, no direct RGB565 path
- **Transparent** — `TRANSPARENT: u16 = 0x0020` sentinel in `pixel_format.mpd`; renderers skip pixels whose palette entry equals this value

## Color

- All canvas drawing uses palette indices (not direct RGB565)
- `PixelFormat.Mono` — 1-bit OLED framebuffer; `0`=off/black, non-zero=on/white
- `PixelFormat.RGB565` — 16-bit direct color for strip output
- `TRANSPARENT = 0x0020` — R=0, G=1, B=0; visually pure black, reserved as sentinel

## Standard palettes (`palette.mpd`)

| Name | Entries | Use |
|---|---|---|
| `PALETTE_MONO` | 2 | Mono OLED |
| `PALETTE_GRAY4` | 4 | 2-bit grayscale |
| `PALETTE_GRAY16` | 16 | 4-bit grayscale |
| `PALETTE_UI16` | 16 | General UI / color display |

Companion enums: `MonoColor`, `Gray4Color`, `Gray16Color`, `UIColor`.

## Strip buffer / DMA

- `Graphics.init(buffer0, buffer1, format, rotation)` — rotation fixed for lifetime
- Double-buffer: CPU renders into back strip; `driver.wait()` → swap → `driver.flush()`
- Single-buffer: pass empty `buffer1`; `wait`/`flush` are synchronous

## Source files

| File | Contents |
|---|---|
| `src/graphics.mpd` | `GraphicsDriver` + `Graphics` class, strip render loop |
| `src/format.mpd` | `PixelFormat`, `IndexFormat`, `Rotation` enums |
| `src/palette.mpd` | Standard palettes + color index enums |
| `src/context.mpd` | `Context` — strip draw API, window clipping, `intersect` |
| `src/node.mpd` | `Node` base class |
| `src/node/bitmap.mpd` | `Bitmap` node + `create_bitmap_from_image` / `create_bitmap_from_sprite_sheet` |
| `src/node/canvas.mpd` | `Canvas` — indexed pixel buffer, all draw primitives |
| `src/node/text.mpd` | `Text` node + `create_text` |
| `src/node/container.mpd` | `Container` — hierarchical node composition |
| `src/texture/image.mpd` | `Compress` enum + `Image` — single indexed-color bitmap asset |
| `src/texture/sprite_sheet.mpd` | `SpriteSize` enum + `SpriteSheet` — fixed-size sprite collection |
| `src/texture/font.mpd` | `Font` — monospaced bitmap font descriptor backed by `SpriteSheet` |
| `src/fonts/font_default_6x8.mpd` | CP437 6×8 default font bitmap (`const` → flash) |


# Micro Panda — Agent Quick Start

## What is it?

Micro Panda (`.mpd`) is a statically-typed systems language that compiles to C.
Targets: desktop (HOSTED), ESP32 / Cortex-M (MCU32). No heap, no GC, no implicit conversions.
Syntax is indentation-based (Python-style) — no braces, no `end` keywords.

## Toolchain

- Compiler: `mpd` binary (default install: `~/.local/bin/mpd`)
- Every project needs an `mpd.yaml` at its root

## CLI commands

| Command | Description |
| --- | --- |
| `mpd init` | Create `mpd.yaml` + `src/main.mpd` in current directory |
| `mpd build` | Parse → generate C → compile binary |
| `mpd build <target>` | Build a specific named target |
| `mpd run <target>` | Build then execute |
| `mpd test` | Compile and run all `*_test.mpd` files |
| `mpd gen` | Generate C only (no compile) |
| `mpd clean` | Delete `out/` and `bin/` |
| `mpd target add <name> <template>` | Add a target from template |

Templates: `hosted-debug`, `hosted-release`, `esp32-debug`, `esp32-release`

## mpd.yaml structure

```yaml
name: myapp
version: 0.1.0

targets:
  main:
    entry: main        # entry module (maps to src/main.mpd)
    src: src/          # source folder
    type: bin          # bin = compile to executable; c = generate C only
    flags: [HOSTED]    # preprocessor flags passed to #if blocks
    output: bin/main   # output binary path
    test: test/        # test folder (enables mpd test); discovers *_test.mpd
    cc:
      bin: gcc
      flags: [-g, -O0, -Wall]
```

For ESP32 (generate C only, hand off to idf.py):

```yaml
  esp32:
    entry: firmware/main
    src: src/
    type: c
    flags: [MCU32]
    out: main/firmware.c
    build_cmd: idf.py build
    gen:
      entry: app_main
```

## Conditional compile flags

| Flag | Meaning |
| --- | --- |
| `HOSTED` | Desktop (Linux / macOS / Windows) |
| `MCU32` | 32-bit MCU (ESP32, Cortex-M) |
| `DEBUG` | Debug build |

Use in source:

```mpd
#if HOSTED
    // desktop-only code
#else
    // MCU code
#end

#if HOSTED || MCU32
    // either target
#end
```

## Standard library — import paths

All stdlib modules are built-in (no `deps:` needed):

| Import | Available | Contents |
| --- | --- | --- |
| `import console` | all | Terminal/UART output |
| `import string` | all | String utilities, formatting |
| `import math` | HOSTED / MCU32 | Math functions and constants |
| `import mcu32.allocator` | HOSTED / MCU32 | Arena `Allocator` |
| `import mcu32.collection` | HOSTED / MCU32 | `ArrayList<T>`, `RingBuffer<T>` |
| `import hosted.allocator` | HOSTED | `HeapAllocator` (malloc/realloc/free) |
| `import hosted.collection` | HOSTED | `HeapList<T>`, `HeapMap<T>` |
| `import hosted.file` | HOSTED | `File` class, I/O |
| `import hosted.args` | HOSTED | `arg_count()`, `arg_value(i)` |
| `import hosted.time` | HOSTED | `sleep_us()`, `time_us()` |
| `import hosted.signal` | HOSTED | SIGINT / SIGTERM handler |

Import styles:

```mpd
import console                  # module qualifier: console.print(...)
import console::print           # specific symbol: print(...) directly
import console::*               # all public symbols imported directly
import math as m                # alias: m.sqrt(...)
import mcu32.allocator::Allocator  # specific class
```

## Typical project layout

```plaintext
myproject/
  mpd.yaml
  src/
    main.mpd          ← entry point (contains fun main())
    module_a.mpd      ← other source modules
  test/
    module_a_test.mpd ← test files (discovered by mpd test)
  bin/                ← compiled binaries (add to .gitignore)
  out/                ← generated C    (add to .gitignore)
```

## Minimal entry point

```mpd
import console

fun main()
    console.print("Hello, world!")
```

## Visibility rule

Names starting with `_` are private (file-local, C `static`). All other names are public.

## Compilation pipeline

```plaintext
*.mpd → compiler (Dart) → out/<target>.c → gcc → bin/<target>
```

`mpd gen` stops after writing the C file.
`mpd build` continues through to compile.

## See also

- `language/LANGUAGE.md` — complete language syntax cheat sheet
- `language/STDLIB.md` — standard library API reference
- `language/GOTCHAS.md` — common pitfalls
- `language/examples/` — runnable example programs
- `language/starter/` — copy-paste project template


# panda_gfx

GFX library for Micro-Panda. Targets MCU (ESP32, RP2040) and hosted platforms.
Strip-buffer rendering pipeline with node-based scene tree.

## Naming conventions

- Avoid abbreviations — use the full word: `device` not `dev`, `buffer` not `buf`, `index` not `idx`, `format` not `fmt`, `source` not `src`, `destination` not `dst`, `column` not `col`, `length` not `len`, `count` not `cnt`, etc.
- Coordinate order: `x`/`y` before `width`/`height`, offset named `offset_x`/`offset_y`
- Font filenames include cell size: `font_default_6x8.mpd`

## Memory placement (`val` vs `const`)

The Micro-Panda compiler maps keywords to C as follows:

| Keyword | C emission | MCU placement |
|---|---|---|
| `var` | plain variable | RAM |
| `val` | plain variable | RAM |
| `const` | `const` variable | `.rodata` → **flash** |
| `const _x` (private) | `static const` | flash |

**Rules for this library:**

- **Palettes** (`PALETTE_*`) — `val` → RAM. Small (≤512 B), accessed per pixel in hot render path.
- **Font bitmaps** (`_data` in font files) — `const` → flash. Read-only, ~570 B, accessed per glyph column; MCU instruction cache (ESP32 IRAM, RP2040 XIP) covers hot glyphs.
- **Sprite sheets** — `const` → flash. Larger, read-only.
- **Strip buffers, canvas buffers** — `var` → RAM. Written every frame.

## Architecture

- **`GraphicsDriver`** — driver table: `width`, `height`, `set_rotation`, `wait`, `flush(x, y, w, h, buffer)`
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

## Font

- Column-major encoding, `width` bytes per glyph
- `bit 0` = top row, `bit 7` = bottom row
- Glyph lookup: `offset = (c - first) * width + px`
- Default font: `font_default_6x8.mpd` — CP437 0x20–0x7E, 6×8 cell (5×7 pixels + 1 gap col + 1 gap row)
- Font bitmap data declared `const` → flash

## Strip buffer / DMA

- `Graphics.init(buffer0, buffer1, format, rotation)` — rotation fixed for lifetime
- Double-buffer: CPU renders into back strip; `driver.wait()` → swap → `driver.flush()`
- Single-buffer: pass empty `buffer1`; `wait`/`flush` are synchronous

## Source files

| File | Contents |
|---|---|
| `src/graphics.mpd` | `GraphicsDriver` + `Graphics` class, strip render loop |
| `src/pixel_format.mpd` | `PixelFormat` enum, `TRANSPARENT` constant |
| `src/index_format.mpd` | `IndexFormat` enum (Index1/2/4/8) |
| `src/palette.mpd` | Standard palettes + color index enums |
| `src/rotation.mpd` | `Rotation` enum |
| `src/rect.mpd` | `Rect` — axis-aligned rectangle, used for node bounds and culling |
| `src/render_context.mpd` | `RenderContext` — strip draw API, window clipping, `intersect` |
| `src/node/node.mpd` | `Node` union type |
| `src/node/canvas.mpd` | `Canvas` — indexed pixel buffer, all draw primitives |
| `src/font/font.mpd` | `Font` class + `get_pixel` |
| `src/font/font_default_6x8.mpd` | CP437 6×8 default font bitmap (`const` → flash) |

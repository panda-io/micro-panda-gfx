# panda_gfx

GFX library for Micro-Panda. Targets MCU (ESP32, RP2040) and hosted platforms.
Merges low-level drawing primitives with the render pipeline (canvas, palette, sprites).

## Architecture

- **Driver table** (`GfxDriver`) owned by gfx, host fills via `gfx_driver()`
- **Strip buffer** — allocator-backed partial buffer, flushed to display via DMA/SPI
- **No global framebuffer** — canvas mode is opt-in, allocated on demand
- **Rotation** — 4 specialised `_pixel_rX` / `_fill_rX` functions, selected via function pointer on `gfx_set_rotation()`. No branch per pixel
- **`_raw` helpers** — internal draw-only variants (no flush) used by compound primitives

## GfxDriver contract

```
class GfxDriver
    var width:     i32
    var height:    i32
    var set_pixel: fun(i32, i32, i32)
    var fill_rect: fun(i32, i32, i32, i32, i32)
    var flush:     fun()               // no-op for SPI, framebuffer send for I2C
```

## Render modes

| Mode | Canvas buffer | Use case |
|---|---|---|
| Direct | None | SSD1306, simple overlays, debug |
| Canvas | 4-bit indexed, full screen | Turtle, procedural drawing, pixel art |
| Sprite/tile | None | Games, dashboards — sprites composite into strip |

Modes are runtime-switched. Canvas buffer is allocator-backed — free it to reclaim RAM for sprite/tile mode.

## Color

- **Direct mode**: raw RGB565 `i32`
- **Canvas/indexed mode**: 4-bit palette index (0–15), palette table = 16×RGB565 = 32 bytes
- Mono displays: `0` = off/black, non-zero = on/white

## Font

Default font: **CP437 8×8**, row-major, bit7 = leftmost pixel, 256 glyphs × 8 bytes.
Font refactor planned — see TODO.

## Strip buffer / DMA

- Configurable strip height (e.g. 16 rows)
- Double-buffered: CPU fills buffer B while DMA sends buffer A
- Canvas flush: convert 4-bit indices → RGB565 into strip, DMA out strip by strip

## Source

| File | Contents |
|---|---|
| `src/gfx.mpd` | Driver table, rotation, font, all draw primitives |

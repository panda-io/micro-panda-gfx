# panda_gfx

Direct-mode GFX library for Micro-Panda. No framebuffer. Adafruit GFX style.

## Architecture

- **No framebuffer** — every draw call goes directly to hardware via driver callbacks
- **Driver table** (`GfxDriver`) owned by gfx, host fills via `gfx_driver()`
- **Flush** — called once per public primitive. SPI drivers leave `flush` unset (defaults to no-op). I2C drivers (SSD1306) implement flush to send framebuffer
- **Rotation** — 4 specialised `_pixel_rX` / `_fill_rX` functions, selected via function pointer on `gfx_set_rotation()`. No branch per pixel
- **`_raw` helpers** — internal draw-only variants (no flush) used by compound primitives to avoid mid-operation flushes

## GfxDriver contract

All fields required except `flush` (optional, defaults to no-op):

```
class GfxDriver
    var width:     i32
    var height:    i32
    var set_pixel: &fun(x, y, color)
    var fill_rect: &fun(x, y, w, h, color)
    var flush:     &fun()               // no-op for SPI, framebuffer send for I2C
```

## Font

Default font: **CP437 8×8**, row-major, bit7 = leftmost pixel, 256 glyphs × 8 bytes.
Stored as `const uint8_t __mp_gfx_font[256][8]` in `@raw`.

## Color

Currently raw RGB565 `i32`. Palette support planned (see TODO).
Mono displays: `0` = off/black, non-zero = on/white.

## Source

| File | Contents |
|---|---|
| `src/gfx.mpd` | Everything — driver table, rotation, font, all primitives |

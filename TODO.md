# panda_gfx TODO

## Fonts

- [ ] Custom font support — variable-width, user-supplied font tables
- [ ] Font scaling beyond 8×8 (proportional fonts)
- [ ] Common open fonts: Terminus, Unscii, Tom Thumb (tiny 3×5)

## Palette

- [ ] Palette system: 1-bit, 2-bit, 4-bit, 8-bit (256 color)
- [ ] Palette entry: 16-bit RGB555 + 1-bit alpha
- [ ] Palette → RGB565 conversion at render time
- [ ] `gfx_set_palette(index, color)` / `gfx_get_palette(index)`
- [ ] Color params in drawing API become palette indices when palette is active

## Bitmap / Image

- [ ] Bitmap draw: raw pixel array, no palette (RGB565)
- [ ] Indexed bitmap: pixel array of palette indices (1/2/4/8-bit per pixel)
- [ ] Image format: simple header (width, height, bit depth, palette, data)
- [ ] Store images in flash (const arrays)
- [ ] `gfx_bitmap(x, y, data, w, h)` — raw RGB565
- [ ] `gfx_image(x, y, img)` — indexed, uses active palette
- [ ] Transparent color support via alpha bit in palette entry

## Other

- [ ] `gfx_hline` / `gfx_vline` as public API (currently internal only)
- [ ] Dashed line support

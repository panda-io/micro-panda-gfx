# panda_gfx TODO

## Roadmap

### 1. Font system refactor
- [ ] Refactor font API — separate font data from gfx core
- [ ] Font descriptor struct (width, height, glyph data pointer, stride)
- [ ] Custom font support — user-supplied font tables
- [ ] Variable-width / proportional fonts
- [ ] Common built-in fonts: Terminus, Unscii, Tom Thumb (tiny 3×5)

### 2. Double strip buffer / DMA
- [ ] Strip buffer: allocator-backed, configurable height (e.g. 240×16×2 bytes)
- [ ] Double buffer — while DMA sends buffer A, CPU fills buffer B
- [ ] Flush callback hands buffer to DMA, signals completion
- [ ] Remove direct pixel write path — all output goes through strip buffer

### 3. Image and palette
- [ ] 16-color palette (4-bit index), palette table = 16×RGB565 = 32 bytes
- [ ] `gfx_set_palette(index, rgb565)` / `gfx_palette_reset()`
- [ ] Palette → RGB565 conversion during strip flush
- [ ] Indexed image format: header (w, h, bit_depth) + palette + pixel data
- [ ] `gfx_image(x, y, img)` — draw indexed image using active palette
- [ ] Store images in flash (const arrays)
- [ ] Transparent color: one palette index reserved as transparent

### 4. Canvas mode
- [ ] Canvas buffer: allocator-backed, 4-bit per pixel, full screen (240×320/2 = 38KB)
- [ ] All draw primitives write palette indices into canvas
- [ ] Canvas flush: convert 4-bit indices → RGB565 into strip buffer, DMA out
- [ ] `gfx_canvas_alloc()` / `gfx_canvas_free()` — runtime mode switch

### 5. Tilemap / sprite
- [ ] Tile: fixed size (e.g. 8×8 or 16×16), indexed pixel data in flash
- [ ] Tilemap: 2D array of tile indices, rendered strip by strip (no canvas needed)
- [ ] Sprite: position + indexed pixel data, composited into strip during scanline
- [ ] Sprite transparency via reserved palette index
- [ ] Max sprites per scanline limit (configurable)

### 6. UI widget system
- [ ] Defer — evaluate LVGL first
- [ ] Target: game HUD + dashboard only (no scrollbar, no complex layout)
- [ ] Widgets: label, value, button, list (page up/down), progress bar
- [ ] Dirty render for UI region, full render for game region
- [ ] Opaque split regions only (no transparent UI overlay for now)

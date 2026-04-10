#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct GraphicsDriver GraphicsDriver;
typedef struct Graphics Graphics;
typedef struct Point Point;
typedef struct RenderContext RenderContext;
typedef struct Node Node;

typedef void (*__Fn_void_Rotation)(Rotation);
typedef void (*__Fn_void)(void);
typedef void (*__Fn_void_Rect_p_Slice_uint8_t)(Rect*, __Slice_uint8_t);

typedef struct { uint8_t* ptr; size_t size; } __Slice_uint8_t;

#include <math.h>
#include <string.h>

typedef enum {
  PixelFormat_Mono = 0,
  PixelFormat_RGB565 = 1,
} PixelFormat;

typedef enum {
  IndexFormat_Index1 = 0,
  IndexFormat_Index2 = 1,
  IndexFormat_Index4 = 2,
  IndexFormat_Index8 = 3,
} IndexFormat;

typedef enum {
  Rotation_R0 = 0,
  Rotation_R90 = 1,
  Rotation_R180 = 2,
  Rotation_R270 = 3,
} Rotation;

typedef enum {
  Node_Canvas,
} Node_Tag;

typedef struct {
  Canvas canvas;
} Node_Canvas_Data;

struct Node {
  Node_Tag tag;
  union {
    Node_Canvas_Data Canvas;
  } data;
};

struct GraphicsDriver {
  int32_t width;
  int32_t height;
  __Fn_void_Rotation set_rotation;
  __Fn_void wait;
  __Fn_void_Rect_p_Slice_uint8_t flush;
};

struct Point {
  int32_t x;
  int32_t y;
};

struct RenderContext {
  __Slice_uint8_t buffer;
  PixelFormat format;
  Rect viewpoint;
};

struct Graphics {
  GraphicsDriver* _driver;
  Node* _root;
  uint16_t _background;
  bool _dirty_render;
  Rect _render_window;
  __Slice_uint8_t _strip0;
  __Slice_uint8_t _strip1;
  bool _single_buffer;
  int32_t _front_buffer;
  RenderContext _context;
};

void main__main(void);
void Graphics_init(Graphics* this, GraphicsDriver* driver, __Slice_uint8_t buffer0, __Slice_uint8_t buffer1, PixelFormat pixel_format, uint16_t background, Rotation rotation, bool dirty_render);
void Graphics_render(Graphics* this);
static __Slice_uint8_t Graphics__front_strip(Graphics* this);
static __Slice_uint8_t Graphics__back_strip(Graphics* this);
static void Graphics__clear_strip(Graphics* this, __Slice_uint8_t buffer);
static inline bool RenderContext_intersect(RenderContext* this, Rect rect);
void RenderContext_render_node(RenderContext* this, Node* node, int32_t offset_x, int32_t offset_y);
void RenderContext_set_pixel(RenderContext* this, int32_t x, int32_t y, int32_t color);
void RenderContext_fill_rect(RenderContext* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color);
static inline void RenderContext__set_pixel_mono(RenderContext* this, int32_t x, int32_t y, int32_t color);
static inline void RenderContext__set_pixel_rgb565(RenderContext* this, int32_t x, int32_t y, int32_t color);
static inline int32_t math__floor_fixed(int32_t v);
static inline int32_t math__ceil_fixed(int32_t v);
static inline int32_t math__round_fixed(int32_t v);
static inline void memory__memory_zero(__Slice_uint8_t dst, uint32_t size);
static inline int32_t math__min_int32_t(int32_t a, int32_t b);

const uint16_t palette__TRANSPARENT = 0x0020;
const float math__PI = 3.14159265358979323846f;
const float math__TAU = 6.28318530717958647692f;
const float math__E = 2.71828182845904523536f;

static int32_t __mp_argc = 0;
static char** __mp_argv = NULL;

void Graphics_init(Graphics* this, GraphicsDriver* driver, __Slice_uint8_t buffer0, __Slice_uint8_t buffer1, PixelFormat pixel_format, uint16_t background, Rotation rotation, bool dirty_render) {
  (this->_driver = driver);
  (this->_strip0 = buffer0);
  (this->_strip1 = buffer1);
  (this->_context.format = pixel_format);
  (this->_background = background);
  (this->_dirty_render = dirty_render);
  if ((buffer1.size == 0)) {
    (this->_single_buffer = true);
  }
  (this->_render_window.x = 0);
  (this->_render_window.y = 0);
  if (this->_dirty_render) {
    (this->_render_window.width = 0);
    (this->_render_window.height = 0);
  }
  this->_driver->set_rotation(rotation);
  if (((rotation == Rotation_R0) || (rotation == Rotation_R180))) {
    if ((!this->_dirty_render)) {
      (this->_render_window.width = this->_driver->width);
      (this->_render_window.height = this->_driver->height);
    }
  } else {
    if ((!this->_dirty_render)) {
      (this->_render_window.width = this->_driver->height);
      (this->_render_window.height = this->_driver->width);
    }
  }
  (this->_front_buffer = 0);
}

void Graphics_render(Graphics* this) {
  if (((this->_render_window.width == 0) || (this->_render_window.height == 0))) {
    return;
  }
  (this->_context.buffer = Graphics__back_strip(this));
  (this->_context.viewpoint.x = this->_render_window.x);
  (this->_context.viewpoint.width = this->_render_window.width);
  int32_t row_bytes = 0;
  if ((this->_context.format == PixelFormat_Mono)) {
    (row_bytes = ((this->_context.viewpoint.width + 7) / 8));
  } else {
    (row_bytes = (this->_context.viewpoint.width * 2));
  }
  int32_t strip_rows = (((((int32_t)(this->_context.buffer.size)) + row_bytes) - 1) / row_bytes);
  int32_t strip_count = (((this->_render_window.height + strip_rows) - 1) / strip_rows);
  for (int32_t strip_index = 0; strip_index < strip_count; strip_index++) {
    (this->_context.viewpoint.y = (this->_render_window.y + (strip_index * strip_rows)));
    (this->_context.viewpoint.height = math__min_int32_t(strip_rows, ((this->_render_window.y + this->_render_window.height) - this->_context.viewpoint.y)));
    Graphics__clear_strip(this, this->_context.buffer);
    RenderContext_render_node((&this->_context), this->_root, 0, 0);
    this->_driver->wait();
    (this->_front_buffer = (1 - this->_front_buffer));
    this->_driver->flush((&this->_context.viewpoint), Graphics__front_strip(this));
  }
  if (this->_dirty_render) {
    (this->_render_window.x = 0);
    (this->_render_window.y = 0);
    (this->_render_window.width = 0);
    (this->_render_window.height = 0);
  }
}

static __Slice_uint8_t Graphics__front_strip(Graphics* this) {
  if ((this->_single_buffer || (this->_front_buffer == 0))) {
    return this->_strip0;
  }
  return this->_strip1;
}

static __Slice_uint8_t Graphics__back_strip(Graphics* this) {
  if ((this->_single_buffer || (this->_front_buffer == 1))) {
    return this->_strip0;
  }
  return this->_strip1;
}

static void Graphics__clear_strip(Graphics* this, __Slice_uint8_t buffer) {
  if ((this->_context.format == PixelFormat_Mono)) {
    if ((this->_background == 0)) {
      memory__memory_zero(buffer, buffer.size);
    } else {
      memset(buffer, 0xFF, buffer.size);
    }
  } else {
    if ((this->_background == 0)) {
      memory__memory_zero(buffer, buffer.size);
    } else {
      uint32_t i = 0;
      uint32_t size = buffer.size;
      while ((i < size)) {
        (buffer.ptr[i] = ((uint8_t)((this->_background >> 8))));
        (buffer.ptr[(i + 1)] = ((uint8_t)(this->_background)));
        (i += 2);
      }
    }
  }
}

static inline bool RenderContext_intersect(RenderContext* this, Rect rect) {
  return this->viewpoint.intersect(rect);
}

void RenderContext_render_node(RenderContext* this, Node* node, int32_t offset_x, int32_t offset_y) {
  switch ((node)->tag) {
    case Node_Canvas: {
      Canvas canvas = (node)->data.Canvas.canvas;
      canvas.render(this, offset_x, offset_y);
      break;
    }
  }
}

void RenderContext_set_pixel(RenderContext* this, int32_t x, int32_t y, int32_t color) {
  if ((!this->viewpoint.contains(x, y))) {
    return;
  }
  int32_t px = (x - this->viewpoint.x);
  int32_t py = (y - this->viewpoint.y);
  if ((this->format == PixelFormat_Mono)) {
    RenderContext__set_pixel_mono(this, px, py, color);
  } else {
    RenderContext__set_pixel_rgb565(this, px, py, color);
  }
}

void RenderContext_fill_rect(RenderContext* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color) {
  int32_t py = y;
  for (int32_t py = y; py < (y + height); py++) {
    if (((py >= this->viewpoint.y) && (py < (this->viewpoint.y + this->viewpoint.height)))) {
      for (int32_t px = x; px < (x + width); px++) {
        if ((this->format == PixelFormat_Mono)) {
          RenderContext__set_pixel_mono(this, px, (py - this->viewpoint.y), color);
        } else {
          RenderContext__set_pixel_rgb565(this, px, (py - this->viewpoint.y), color);
        }
        (px += 1);
      }
    }
  }
}

static inline void RenderContext__set_pixel_mono(RenderContext* this, int32_t x, int32_t y, int32_t color) {
  int32_t index = (((y * (this->viewpoint.width + 7)) / 8) + (x / 8));
  if ((color == 0)) {
    (this->buffer.ptr[index] = (this->buffer.ptr[index] & ((uint8_t)((~(0x80 >> (x & 7)))))));
  } else {
    (this->buffer.ptr[index] = (this->buffer.ptr[index] | ((uint8_t)((0x80 >> (x & 7))))));
  }
}

static inline void RenderContext__set_pixel_rgb565(RenderContext* this, int32_t x, int32_t y, int32_t color) {
  int32_t index = (((y * this->viewpoint.width) + x) * 2);
  (this->buffer.ptr[index] = ((uint8_t)((color >> 8))));
  (this->buffer.ptr[(index + 1)] = ((uint8_t)(color)));
}

static inline int32_t math__floor_fixed(int32_t v) {
  return (v & (-65536));
}

static inline int32_t math__ceil_fixed(int32_t v) {
  int32_t f = (v & (-65536));
  if ((v != f)) {
    return (f + 65536);
  }
  return f;
}

static inline int32_t math__round_fixed(int32_t v) {
  return ((v + 32768) & (-65536));
}

static inline void memory__memory_zero(__Slice_uint8_t dst, uint32_t size) {
  memset(dst, ((uint8_t)(0)), size);
}

static inline int32_t math__min_int32_t(int32_t a, int32_t b) {
  if ((a < b)) {
    return a;
  }
  return b;
}

int main(int argc, char** argv) { __mp_argc = argc; __mp_argv = argv; main__main(); return 0; }


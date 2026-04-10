#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct Canvas Canvas;
typedef struct GraphicsDriver GraphicsDriver;
typedef struct Graphics Graphics;
typedef struct Point Point;
typedef struct Rect Rect;
typedef struct Node Node;
typedef struct RenderContext RenderContext;
typedef struct Allocator Allocator;

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
  MonoColor_Off = 0,
  MonoColor_On = 1,
} MonoColor;

typedef enum {
  Gray4Color_Black = 0,
  Gray4Color_DarkGray = 1,
  Gray4Color_LightGray = 2,
  Gray4Color_White = 3,
} Gray4Color;

typedef enum {
  Gray16Color_Black = 0,
  Gray16Color_White = 15,
} Gray16Color;

typedef enum {
  UIColor_Black = 0,
  UIColor_White = 1,
  UIColor_Red = 2,
  UIColor_Green = 3,
  UIColor_Blue = 4,
  UIColor_Yellow = 5,
  UIColor_Cyan = 6,
  UIColor_Magenta = 7,
  UIColor_DarkGray = 8,
  UIColor_LightGray = 9,
  UIColor_DarkRed = 10,
  UIColor_DarkGreen = 11,
  UIColor_DarkBlue = 12,
  UIColor_Orange = 13,
  UIColor_Purple = 14,
  UIColor_Teal = 15,
} UIColor;

typedef void (*__Fn_void_int32_t_int32_t_int32_t)(int32_t, int32_t, int32_t);
typedef void (*__Fn_void_RenderContext_p_Rect_p_Point_p)(RenderContext*, Rect*, Point*);
typedef void (*__Fn_void_Rotation)(Rotation);
typedef void (*__Fn_void)(void);
typedef void (*__Fn_void_Rect_p_Slice_uint8_t)(Rect*, __Slice_uint8_t);
typedef void (*__Fn_void_RenderContext_p_Point_p_void_p)(RenderContext*, Point*, void*);

typedef struct { uint8_t* ptr; int32_t size; } __Slice_uint8_t;
typedef struct { uint16_t* ptr; int32_t size; } __Slice_uint16_t;

#include <math.h>
#include <string.h>

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

struct Rect {
  int32_t x;
  int32_t y;
  int32_t width;
  int32_t height;
};

struct Node {
  void* handle;
  __Fn_void_RenderContext_p_Point_p_void_p renderer;
};

struct Allocator {
  __Slice_uint8_t _memory;
  int32_t _cursor;
};

struct RenderContext {
  __Slice_uint8_t buffer;
  PixelFormat format;
  Rect viewpoint;
};

struct Canvas {
  Node _node;
  __Slice_uint8_t _buffer;
  Rect _viewpoint;
  uint16_t _background;
  IndexFormat _index_format;
  __Slice_uint16_t _palette;
  __Fn_void_int32_t_int32_t_int32_t _set_pixel_fn;
  __Fn_void_RenderContext_p_Rect_p_Point_p _render_fn;
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
Canvas* node__canvas__create_canvas(Allocator* allocator, Rect* rect, uint16_t background, IndexFormat index_format, __Slice_uint16_t palette);
void node__canvas__render_canvas(RenderContext* context, Point* offset, void* handle);
Node* Canvas_get_node(Canvas* this);
static inline void Canvas_draw_pixel(Canvas* this, int32_t x, int32_t y, int32_t color);
static inline void Canvas_draw_hline(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t color);
static inline void Canvas_draw_vline(Canvas* this, int32_t x, int32_t y, int32_t height, int32_t color);
void Canvas_draw_line(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color);
void Canvas_draw_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color);
static inline void Canvas_fill_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color);
void Canvas_clear(Canvas* this);
void Canvas_draw_circle(Canvas* this, int32_t cx, int32_t cy, int32_t r, int32_t color);
void Canvas_fill_circle(Canvas* this, int32_t cx, int32_t cy, int32_t r, int32_t color);
void Canvas_draw_triangle(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color);
void Canvas_fill_triangle(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color);
void Canvas_draw_round_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t r, int32_t color);
void Canvas_fill_round_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t r, int32_t color);
static void Canvas__fill_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color);
static void Canvas__circle_8(Canvas* this, int32_t cx, int32_t cy, int32_t x, int32_t y, int32_t color);
static void Canvas__set_pixel_index1(Canvas* this, int32_t x, int32_t y, int32_t color);
static void Canvas__set_pixel_index2(Canvas* this, int32_t x, int32_t y, int32_t color);
static void Canvas__set_pixel_index4(Canvas* this, int32_t x, int32_t y, int32_t color);
static void Canvas__set_pixel_index8(Canvas* this, int32_t x, int32_t y, int32_t color);
static void Canvas__render_index1(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset);
static void Canvas__render_index2(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset);
static void Canvas__render_index4(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset);
static void Canvas__render_index8(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset);
static inline int32_t Canvas__abs(Canvas* this, int32_t v);
static inline int32_t Canvas__sign(Canvas* this, int32_t v);
static inline int32_t Canvas__sqrt(Canvas* this, int32_t n);
void Graphics_set_root(Graphics* this, Node* node);
void Graphics_init(Graphics* this, GraphicsDriver* driver, __Slice_uint8_t buffer0, __Slice_uint8_t buffer1, PixelFormat pixel_format, uint16_t background, Rotation rotation, bool dirty_render);
void Graphics_mark_dirty(Graphics* this, Rect* rect);
void Graphics_render(Graphics* this);
static __Slice_uint8_t Graphics__front_strip(Graphics* this);
static __Slice_uint8_t Graphics__back_strip(Graphics* this);
static void Graphics__clear_strip(Graphics* this, __Slice_uint8_t buffer);
static inline void Point_copy(Point* this, Point* point);
static inline void Rect_copy(Rect* this, Rect* rect);
static inline bool Rect_intersect(Rect* this, Rect* rect);
static inline bool Rect_contains(Rect* this, Point* point);
static inline void Rect_merge(Rect* this, Rect* rect);
static inline bool RenderContext_intersect(RenderContext* this, Rect rect);
void RenderContext_set_pixel(RenderContext* this, Point* point, int32_t color);
void RenderContext_fill_rect(RenderContext* this, Rect* rect, int32_t color);
static inline void RenderContext__set_pixel_mono(RenderContext* this, int32_t x, int32_t y, int32_t color);
static inline void RenderContext__set_pixel_rgb565(RenderContext* this, int32_t x, int32_t y, int32_t color);
static inline int32_t math__floor_q16(int32_t value);
static inline int32_t math__ceil_q16(int32_t value);
static inline int32_t math__round_q16(int32_t value);
static inline int32_t math__floor_fixed(int32_t value);
static inline int32_t math__ceil_fixed(int32_t value);
static inline int32_t math__round_fixed(int32_t value);
void Allocator_init(Allocator* this, __Slice_uint8_t mem);
static inline void* Allocator_allocate(Allocator* this, size_t __sizeof_T);
static inline void Allocator_reset(Allocator* this);
static inline void memory__memory_zero(__Slice_uint8_t dst, int32_t size);
static inline Canvas* Allocator_allocate_Canvas(Allocator* this);
static inline __Slice_uint8_t Allocator_allocate_array_uint8_t(Allocator* this, int32_t length);
static inline int32_t math__max_int32_t(int32_t a, int32_t b);
static inline int32_t math__min_int32_t(int32_t a, int32_t b);

const uint16_t palette__TRANSPARENT = 0x0020;
uint16_t palette__PALETTE_MONO[2] = {0x0000, 0xFFFF};
uint16_t palette__PALETTE_GRAY4[4] = {0x0000, 0x52AA, 0xAD55, 0xFFFF};
uint16_t palette__PALETTE_GRAY16[16] = {0x0000, 0x1082, 0x2104, 0x3186, 0x4208, 0x528A, 0x630C, 0x738E, 0x8410, 0x9492, 0xA514, 0xB596, 0xC618, 0xD69A, 0xE71C, 0xFFFF};
uint16_t palette__PALETTE_UI16[16] = {0x0000, 0xFFFF, 0xF800, 0x07E0, 0x001F, 0xFFE0, 0x07FF, 0xF81F, 0x39E7, 0xC618, 0x8000, 0x0400, 0x000F, 0xFD20, 0x8010, 0x07A0};
const float math__PI = 3.14159265358979323846f;
const float math__TAU = 6.28318530717958647692f;
const float math__E = 2.71828182845904523536f;

static int32_t __mp_argc = 0;
static char** __mp_argv = NULL;

Canvas* node__canvas__create_canvas(Allocator* allocator, Rect* rect, uint16_t background, IndexFormat index_format, __Slice_uint16_t palette) {
  Canvas* canvas = Allocator_allocate_Canvas(allocator);
  Rect_copy((&canvas->_viewpoint), rect);
  (canvas->_background = background);
  (canvas->_index_format = index_format);
  (canvas->_palette = palette);
  if ((index_format == IndexFormat_Index1)) {
    (canvas->_set_pixel_fn = canvas->_set_pixel_index1);
    (canvas->_render_fn = canvas->_render_index1);
    int32_t buffer_size = (((rect->width + 7) / 8) * rect->height);
    (canvas->_buffer = Allocator_allocate_array_uint8_t(allocator, buffer_size));
  }
  if ((index_format == IndexFormat_Index2)) {
    (canvas->_set_pixel_fn = canvas->_set_pixel_index2);
    (canvas->_render_fn = canvas->_render_index2);
    int32_t buffer_size = (((rect->width + 3) / 4) * rect->height);
    (canvas->_buffer = Allocator_allocate_array_uint8_t(allocator, buffer_size));
  }
  if ((index_format == IndexFormat_Index4)) {
    (canvas->_set_pixel_fn = canvas->_set_pixel_index4);
    (canvas->_render_fn = canvas->_render_index4);
    int32_t buffer_size = (((rect->width + 1) / 2) * rect->height);
    (canvas->_buffer = Allocator_allocate_array_uint8_t(allocator, buffer_size));
  }
  if ((index_format == IndexFormat_Index8)) {
    (canvas->_set_pixel_fn = canvas->_set_pixel_index8);
    (canvas->_render_fn = canvas->_render_index8);
    int32_t buffer_size = (rect->width * rect->height);
    (canvas->_buffer = Allocator_allocate_array_uint8_t(allocator, buffer_size));
  }
  (canvas->_node.handle = ((void*)(canvas)));
  (canvas->_node.renderer = node__canvas__render_canvas);
}

void node__canvas__render_canvas(RenderContext* context, Point* offset, void* handle) {
  Canvas* canvas = ((Canvas*)(handle));
  Rect viewpoint = {0};
  (viewpoint.x = (canvas->_viewpoint.x + offset->x));
  (viewpoint.y = (canvas->_viewpoint.y + offset->y));
  (viewpoint.width = canvas->_viewpoint.width);
  (viewpoint.height = canvas->_viewpoint.height);
  if ((!RenderContext_intersect(context, viewpoint))) {
    return;
  }
  (viewpoint.x = math__max_int32_t(viewpoint.x, context->viewpoint.x));
  (viewpoint.y = math__max_int32_t(viewpoint.y, context->viewpoint.y));
  (viewpoint.width = (math__min_int32_t((viewpoint.x + viewpoint.width), (context->viewpoint.x + context->viewpoint.width)) - viewpoint.x));
  (viewpoint.height = (math__min_int32_t((viewpoint.y + viewpoint.height), (context->viewpoint.y + context->viewpoint.height)) - viewpoint.y));
  canvas->_render_fn(context, (&viewpoint), offset);
}

Node* Canvas_get_node(Canvas* this) {
  return (&this->_node);
}

static inline void Canvas_draw_pixel(Canvas* this, int32_t x, int32_t y, int32_t color) {
  this->_set_pixel_fn(x, y, color);
}

static inline void Canvas_draw_hline(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t color) {
  Canvas__fill_rect(this, x, y, width, 1, color);
}

static inline void Canvas_draw_vline(Canvas* this, int32_t x, int32_t y, int32_t height, int32_t color) {
  Canvas__fill_rect(this, x, y, 1, height, color);
}

void Canvas_draw_line(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color) {
  int32_t dx = Canvas__abs(this, (x1 - x0));
  int32_t dy = Canvas__abs(this, (y1 - y0));
  int32_t sx = Canvas__sign(this, (x1 - x0));
  int32_t sy = Canvas__sign(this, (y1 - y0));
  int32_t err = (dx - dy);
  int32_t cx = x0;
  int32_t cy = y0;
  while (true) {
    Canvas_draw_pixel(this, cx, cy, color);
    if (((cx == x1) && (cy == y1))) {
      return;
    }
    int32_t e2 = (err * 2);
    if ((e2 > (-dy))) {
      (err -= dy);
      (cx += sx);
    }
    if ((e2 < dx)) {
      (err += dx);
      (cy += sy);
    }
  }
}

void Canvas_draw_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color) {
  Canvas__fill_rect(this, x, y, width, 1, color);
  Canvas__fill_rect(this, x, ((y + height) - 1), width, 1, color);
  Canvas__fill_rect(this, x, (y + 1), 1, (height - 2), color);
  Canvas__fill_rect(this, ((x + width) - 1), (y + 1), 1, (height - 2), color);
}

static inline void Canvas_fill_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color) {
  Canvas__fill_rect(this, x, y, width, height, color);
}

void Canvas_clear(Canvas* this) {
  Canvas__fill_rect(this, this->_viewpoint.x, this->_viewpoint.y, this->_viewpoint.width, this->_viewpoint.height, this->_background);
}

void Canvas_draw_circle(Canvas* this, int32_t cx, int32_t cy, int32_t r, int32_t color) {
  int32_t x = 0;
  int32_t y = r;
  int32_t d = (1 - r);
  Canvas__circle_8(this, cx, cy, x, y, color);
  while ((x < y)) {
    if ((d < 0)) {
      (d += ((2 * x) + 3));
    } else {
      (d += ((2 * (x - y)) + 5));
      (y -= 1);
    }
    (x += 1);
    Canvas__circle_8(this, cx, cy, x, y, color);
  }
}

void Canvas_fill_circle(Canvas* this, int32_t cx, int32_t cy, int32_t r, int32_t color) {
  for (int32_t dy = (-r); dy < (r + 1); dy++) {
    int32_t dx = Canvas__sqrt(this, ((r * r) - (dy * dy)));
    Canvas__fill_rect(this, (cx - dx), (cy + dy), ((dx * 2) + 1), 1, color);
  }
}

void Canvas_draw_triangle(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color) {
  Canvas_draw_line(this, x0, y0, x1, y1, color);
  Canvas_draw_line(this, x1, y1, x2, y2, color);
  Canvas_draw_line(this, x2, y2, x0, y0, color);
}

void Canvas_fill_triangle(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color) {
  int32_t tx = 0;
  int32_t ty = 0;
  if ((y1 < y0)) {
    (tx = x0);
    (ty = y0);
    (x0 = x1);
    (y0 = y1);
    (x1 = tx);
    (y1 = ty);
  }
  if ((y2 < y0)) {
    (tx = x0);
    (ty = y0);
    (x0 = x2);
    (y0 = y2);
    (x2 = tx);
    (y2 = ty);
  }
  if ((y2 < y1)) {
    (tx = x1);
    (ty = y1);
    (x1 = x2);
    (y1 = y2);
    (x2 = tx);
    (y2 = ty);
  }
  for (int32_t y = y0; y < (y2 + 1); y++) {
    int32_t xa = 0;
    int32_t xb = 0;
    if (((y <= y1) && (y1 != y0))) {
      (xa = (x0 + (((y - y0) * (x1 - x0)) / (y1 - y0))));
    } else {
      (xa = x1);
    }
    if ((y2 != y0)) {
      (xb = (x0 + (((y - y0) * (x2 - x0)) / (y2 - y0))));
    } else {
      (xb = x0);
    }
    if ((xa > xb)) {
      (tx = xa);
      (xa = xb);
      (xb = tx);
    }
    Canvas__fill_rect(this, xa, y, ((xb - xa) + 1), 1, color);
  }
}

void Canvas_draw_round_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t r, int32_t color) {
  Canvas__fill_rect(this, (x + r), y, (width - (2 * r)), 1, color);
  Canvas__fill_rect(this, (x + r), ((y + height) - 1), (width - (2 * r)), 1, color);
  Canvas__fill_rect(this, x, (y + r), 1, (height - (2 * r)), color);
  Canvas__fill_rect(this, ((x + width) - 1), (y + r), 1, (height - (2 * r)), color);
  int32_t px = 0;
  int32_t py = r;
  int32_t d = (1 - r);
  while ((px <= py)) {
    Canvas_draw_pixel(this, ((((x + width) - 1) - r) + py), ((y + r) - px), color);
    Canvas_draw_pixel(this, ((x + r) - py), ((y + r) - px), color);
    Canvas_draw_pixel(this, ((((x + width) - 1) - r) + py), ((((y + height) - 1) - r) + px), color);
    Canvas_draw_pixel(this, ((x + r) - py), ((((y + height) - 1) - r) + px), color);
    Canvas_draw_pixel(this, ((((x + width) - 1) - r) + px), ((y + r) - py), color);
    Canvas_draw_pixel(this, ((x + r) - px), ((y + r) - py), color);
    Canvas_draw_pixel(this, ((((x + width) - 1) - r) + px), ((((y + height) - 1) - r) + py), color);
    Canvas_draw_pixel(this, ((x + r) - px), ((((y + height) - 1) - r) + py), color);
    if ((d < 0)) {
      (d += ((2 * px) + 3));
    } else {
      (d += ((2 * (px - py)) + 5));
      (py -= 1);
    }
    (px += 1);
  }
}

void Canvas_fill_round_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t r, int32_t color) {
  Canvas__fill_rect(this, (x + r), y, (width - (2 * r)), height, color);
  int32_t px = 0;
  int32_t py = r;
  int32_t d = (1 - r);
  while ((px <= py)) {
    Canvas__fill_rect(this, (((((x + width) - 1) - r) - py) + 1), ((y + r) - px), ((py * 2) - 1), 1, color);
    Canvas__fill_rect(this, (((((x + width) - 1) - r) - py) + 1), ((((y + height) - 1) - r) + px), ((py * 2) - 1), 1, color);
    Canvas__fill_rect(this, (((((x + width) - 1) - r) - px) + 1), ((y + r) - py), ((px * 2) - 1), 1, color);
    Canvas__fill_rect(this, (((((x + width) - 1) - r) - px) + 1), ((((y + height) - 1) - r) + py), ((px * 2) - 1), 1, color);
    if ((d < 0)) {
      (d += ((2 * px) + 3));
    } else {
      (d += ((2 * (px - py)) + 5));
      (py -= 1);
    }
    (px += 1);
  }
}

static void Canvas__fill_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color) {
  if (((width <= 0) || (height <= 0))) {
    return;
  }
  bool intersect = ((((x < (this->_viewpoint.x + this->_viewpoint.width)) && ((x + width) > this->_viewpoint.x)) && (y < (this->_viewpoint.y + this->_viewpoint.height))) && ((y + height) > this->_viewpoint.y));
  if ((!intersect)) {
    return;
  }
  int32_t start_x = math__max_int32_t(x, this->_viewpoint.x);
  int32_t start_y = math__max_int32_t(y, this->_viewpoint.y);
  int32_t end_x = math__min_int32_t((x + width), (this->_viewpoint.x + this->_viewpoint.width));
  int32_t end_y = math__min_int32_t((y + height), (this->_viewpoint.y + this->_viewpoint.height));
  for (int32_t py = start_y; py < end_y; py++) {
    for (int32_t px = start_x; px < end_x; px++) {
      Canvas_draw_pixel(this, px, py, color);
    }
  }
}

static void Canvas__circle_8(Canvas* this, int32_t cx, int32_t cy, int32_t x, int32_t y, int32_t color) {
  Canvas_draw_pixel(this, (cx + x), (cy + y), color);
  Canvas_draw_pixel(this, (cx - x), (cy + y), color);
  Canvas_draw_pixel(this, (cx + x), (cy - y), color);
  Canvas_draw_pixel(this, (cx - x), (cy - y), color);
  Canvas_draw_pixel(this, (cx + y), (cy + x), color);
  Canvas_draw_pixel(this, (cx - y), (cy + x), color);
  Canvas_draw_pixel(this, (cx + y), (cy - x), color);
  Canvas_draw_pixel(this, (cx - y), (cy - x), color);
}

static void Canvas__set_pixel_index1(Canvas* this, int32_t x, int32_t y, int32_t color) {
  if (((((x < this->_viewpoint.x) || (x >= (this->_viewpoint.x + this->_viewpoint.width))) || (y < this->_viewpoint.y)) || (y >= (this->_viewpoint.y + this->_viewpoint.height)))) {
    return;
  }
  int32_t lx = (x - this->_viewpoint.x);
  int32_t ly = (y - this->_viewpoint.y);
  int32_t index = ((ly * ((this->_viewpoint.width + 7) / 8)) + (lx / 8));
  if (((color & 1) != 0)) {
    (this->_buffer.ptr[index] = (this->_buffer.ptr[index] | ((uint8_t)((0x80 >> (lx & 7))))));
  } else {
    (this->_buffer.ptr[index] = (this->_buffer.ptr[index] & ((uint8_t)((~(0x80 >> (lx & 7)))))));
  }
}

static void Canvas__set_pixel_index2(Canvas* this, int32_t x, int32_t y, int32_t color) {
  if (((((x < this->_viewpoint.x) || (x >= (this->_viewpoint.x + this->_viewpoint.width))) || (y < this->_viewpoint.y)) || (y >= (this->_viewpoint.y + this->_viewpoint.height)))) {
    return;
  }
  int32_t lx = (x - this->_viewpoint.x);
  int32_t ly = (y - this->_viewpoint.y);
  int32_t index = ((ly * ((this->_viewpoint.width + 3) / 4)) + (lx / 4));
  int32_t shift = ((3 - (lx & 3)) * 2);
  (this->_buffer.ptr[index] = ((this->_buffer.ptr[index] & ((uint8_t)((~(0x03 << shift))))) | ((uint8_t)(((color & 0x03) << shift)))));
}

static void Canvas__set_pixel_index4(Canvas* this, int32_t x, int32_t y, int32_t color) {
  if (((((x < this->_viewpoint.x) || (x >= (this->_viewpoint.x + this->_viewpoint.width))) || (y < this->_viewpoint.y)) || (y >= (this->_viewpoint.y + this->_viewpoint.height)))) {
    return;
  }
  int32_t lx = (x - this->_viewpoint.x);
  int32_t ly = (y - this->_viewpoint.y);
  int32_t index = ((ly * ((this->_viewpoint.width + 1) / 2)) + (lx / 2));
  if (((lx & 1) == 0)) {
    (this->_buffer.ptr[index] = ((this->_buffer.ptr[index] & ((uint8_t)(0x0F))) | ((uint8_t)((color << 4)))));
  } else {
    (this->_buffer.ptr[index] = ((this->_buffer.ptr[index] & ((uint8_t)(0xF0))) | ((uint8_t)((color & 0x0F)))));
  }
}

static void Canvas__set_pixel_index8(Canvas* this, int32_t x, int32_t y, int32_t color) {
  if (((((x < this->_viewpoint.x) || (x >= (this->_viewpoint.x + this->_viewpoint.width))) || (y < this->_viewpoint.y)) || (y >= (this->_viewpoint.y + this->_viewpoint.height)))) {
    return;
  }
  int32_t lx = (x - this->_viewpoint.x);
  int32_t ly = (y - this->_viewpoint.y);
  (this->_buffer.ptr[((ly * this->_viewpoint.width) + lx)] = ((uint8_t)(color)));
}

static void Canvas__render_index1(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset) {
  for (int32_t y = viewpoint->y; y < (viewpoint->y + viewpoint->height); y++) {
    int32_t ly = ((y - this->_viewpoint.y) - offset->y);
    for (int32_t x = viewpoint->x; x < (viewpoint->x + viewpoint->width); x++) {
      int32_t lx = ((x - this->_viewpoint.x) - offset->x);
      int32_t index = ((ly * ((this->_viewpoint.width + 7) / 8)) + (lx / 8));
      uint16_t color = this->_palette.ptr[0];
      if (((this->_buffer.ptr[index] & ((uint8_t)((0x80 >> (lx & 7))))) != 0)) {
        (color = this->_palette.ptr[1]);
      }
      if ((color != palette__TRANSPARENT)) {
        Point point = (Point){x, y};
        RenderContext_set_pixel(context, (&point), color);
      }
    }
  }
}

static void Canvas__render_index2(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset) {
  for (int32_t y = viewpoint->y; y < (viewpoint->y + viewpoint->height); y++) {
    int32_t ly = ((y - this->_viewpoint.y) - offset->y);
    for (int32_t x = viewpoint->x; x < (viewpoint->x + viewpoint->width); x++) {
      int32_t lx = ((x - this->_viewpoint.x) - offset->x);
      int32_t index = ((ly * ((this->_viewpoint.width + 3) / 4)) + (lx / 4));
      int32_t shift = ((3 - (lx & 3)) * 2);
      uint16_t color = this->_palette.ptr[((((int32_t)(this->_buffer.ptr[index])) >> shift) & 0x03)];
      if ((color != palette__TRANSPARENT)) {
        Point point = (Point){x, y};
        RenderContext_set_pixel(context, (&point), color);
      }
    }
  }
}

static void Canvas__render_index4(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset) {
  for (int32_t y = viewpoint->y; y < (viewpoint->y + viewpoint->height); y++) {
    int32_t ly = ((y - this->_viewpoint.y) - offset->y);
    for (int32_t x = viewpoint->x; x < (viewpoint->x + viewpoint->width); x++) {
      int32_t lx = ((x - this->_viewpoint.x) - offset->x);
      int32_t index = ((ly * ((this->_viewpoint.width + 1) / 2)) + (lx / 2));
      uint8_t palette_index = (this->_buffer.ptr[index] & 0x0F);
      if (((lx & 1) == 0)) {
        (palette_index = ((this->_buffer.ptr[index] >> 4) & 0x0F));
      }
      uint16_t color = this->_palette.ptr[palette_index];
      if ((color != palette__TRANSPARENT)) {
        Point point = (Point){x, y};
        RenderContext_set_pixel(context, (&point), color);
      }
    }
  }
}

static void Canvas__render_index8(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset) {
  for (int32_t y = viewpoint->y; y < (viewpoint->y + viewpoint->height); y++) {
    int32_t ly = ((y - this->_viewpoint.y) - offset->y);
    for (int32_t x = viewpoint->x; x < (viewpoint->x + viewpoint->width); x++) {
      int32_t lx = ((x - this->_viewpoint.x) - offset->x);
      uint16_t color = this->_palette.ptr[this->_buffer.ptr[((ly * this->_viewpoint.width) + lx)]];
      if ((color != palette__TRANSPARENT)) {
        Point point = (Point){x, y};
        RenderContext_set_pixel(context, (&point), color);
      }
    }
  }
}

static inline int32_t Canvas__abs(Canvas* this, int32_t v) {
  if ((v < 0)) {
    return (-v);
  }
  return v;
}

static inline int32_t Canvas__sign(Canvas* this, int32_t v) {
  if ((v > 0)) {
    return 1;
  }
  if ((v < 0)) {
    return (-1);
  }
  return 0;
}

static inline int32_t Canvas__sqrt(Canvas* this, int32_t n) {
  if ((n <= 0)) {
    return 0;
  }
  int32_t x = n;
  int32_t y = ((x + 1) / 2);
  while ((y < x)) {
    (x = y);
    (y = ((x + (n / x)) / 2));
  }
  return x;
}

void Graphics_set_root(Graphics* this, Node* node) {
  (this->_root = node);
}

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

void Graphics_mark_dirty(Graphics* this, Rect* rect) {
  int32_t aligned_x = rect->x;
  int32_t aligned_width = rect->width;
  if ((this->_context.format == PixelFormat_Mono)) {
    int32_t right = (((rect->x + rect->width) + 7) & (~7));
    (aligned_x = (rect->x & (~7)));
    (aligned_width = (right - aligned_x));
  }
  Rect aligned = (Rect){aligned_x, rect->y, aligned_width, rect->height};
  if (((this->_render_window.width == 0) && (this->_render_window.height == 0))) {
    Rect_copy((&this->_render_window), (&aligned));
  } else {
    Rect_merge((&this->_render_window), (&aligned));
  }
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
  int32_t strip_rows = (((this->_context.buffer.size + row_bytes) - 1) / row_bytes);
  int32_t strip_count = (((this->_render_window.height + strip_rows) - 1) / strip_rows);
  Point offset = (Point){0, 0};
  for (int32_t strip_index = 0; strip_index < strip_count; strip_index++) {
    (this->_context.viewpoint.y = (this->_render_window.y + (strip_index * strip_rows)));
    (this->_context.viewpoint.height = math__min_int32_t(strip_rows, ((this->_render_window.y + this->_render_window.height) - this->_context.viewpoint.y)));
    Graphics__clear_strip(this, this->_context.buffer);
    this->_root->renderer((&this->_context), (&offset), this->_root->handle);
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
      int32_t i = 0;
      int32_t size = buffer.size;
      while ((i < size)) {
        (buffer.ptr[i] = ((uint8_t)((this->_background >> 8))));
        (buffer.ptr[(i + 1)] = ((uint8_t)(this->_background)));
        (i += 2);
      }
    }
  }
}

static inline void Point_copy(Point* this, Point* point) {
  (this->x = point->x);
  (this->y = point->y);
}

static inline void Rect_copy(Rect* this, Rect* rect) {
  (this->x = rect->x);
  (this->y = rect->y);
  (this->width = rect->width);
  (this->height = rect->height);
}

static inline bool Rect_intersect(Rect* this, Rect* rect) {
  return ((((rect->x < (this->x + this->width)) && ((rect->x + rect->width) > this->x)) && (rect->y < (this->y + this->height))) && ((rect->y + rect->height) > this->y));
}

static inline bool Rect_contains(Rect* this, Point* point) {
  return ((((point->x >= this->x) && (point->x < (this->x + this->width))) && (point->y >= this->y)) && (point->y < (this->y + this->height)));
}

static inline void Rect_merge(Rect* this, Rect* rect) {
  int32_t right = math__max_int32_t((this->x + this->width), (rect->x + rect->width));
  int32_t bottom = math__max_int32_t((this->y + this->height), (rect->y + rect->height));
  (this->x = math__min_int32_t(this->x, rect->x));
  (this->y = math__min_int32_t(this->y, rect->y));
  (this->width = (right - this->x));
  (this->height = (bottom - this->y));
}

static inline bool RenderContext_intersect(RenderContext* this, Rect rect) {
  return Rect_intersect((&this->viewpoint), rect);
}

void RenderContext_set_pixel(RenderContext* this, Point* point, int32_t color) {
  if ((!Rect_contains((&this->viewpoint), point))) {
    return;
  }
  int32_t px = (point->x - this->viewpoint.x);
  int32_t py = (point->y - this->viewpoint.y);
  if ((this->format == PixelFormat_Mono)) {
    RenderContext__set_pixel_mono(this, px, py, color);
  } else {
    RenderContext__set_pixel_rgb565(this, px, py, color);
  }
}

void RenderContext_fill_rect(RenderContext* this, Rect* rect, int32_t color) {
  int32_t py = rect->y;
  for (int32_t py = rect->y; py < (rect->y + rect->height); py++) {
    if (((py >= this->viewpoint.y) && (py < (this->viewpoint.y + this->viewpoint.height)))) {
      for (int32_t px = rect->x; px < (rect->x + rect->width); px++) {
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

static inline int32_t math__floor_q16(int32_t value) {
  return (value & (-65536));
}

static inline int32_t math__ceil_q16(int32_t value) {
  int32_t result = (value & (-65536));
  if ((value != result)) {
    return (result + 65536);
  }
  return result;
}

static inline int32_t math__round_q16(int32_t value) {
  return ((value + 32768) & (-65536));
}

static inline int32_t math__floor_fixed(int32_t value) {
  return (value & (-65536));
}

static inline int32_t math__ceil_fixed(int32_t value) {
  int32_t result = (value & (-65536));
  if ((value != result)) {
    return (result + 65536);
  }
  return result;
}

static inline int32_t math__round_fixed(int32_t value) {
  return ((value + 32768) & (-65536));
}

void Allocator_init(Allocator* this, __Slice_uint8_t mem) {
  (this->_memory = mem);
  (this->_cursor = 0);
}

static inline void* Allocator_allocate(Allocator* this, size_t __sizeof_T) {
  uint64_t size = __sizeof_T;
  if (((this->_cursor + size) > this->_memory.size)) {
    return NULL;
  }
  void* ptr = (void*)((&this->_memory.ptr[this->_cursor]));
  (this->_cursor = (((this->_cursor + size) + 3) & (~((int32_t)(3)))));
  return ptr;
}

static inline void Allocator_reset(Allocator* this) {
  (this->_cursor = 0);
}

static inline void memory__memory_zero(__Slice_uint8_t dst, int32_t size) {
  memset(dst, ((uint8_t)(0)), size);
}

static inline Canvas* Allocator_allocate_Canvas(Allocator* this) {
  uint64_t size = sizeof(Canvas);
  if (((this->_cursor + size) > this->_memory.size)) {
    return NULL;
  }
  Canvas* ptr = ((Canvas*)((&this->_memory.ptr[this->_cursor])));
  (this->_cursor = (((this->_cursor + size) + 3) & (~((int32_t)(3)))));
  return ptr;
}

static inline __Slice_uint8_t Allocator_allocate_array_uint8_t(Allocator* this, int32_t length) {
  uint64_t size = (sizeof(uint8_t) * length);
  if (((this->_cursor + size) > this->_memory.size)) {
    return (__Slice_uint8_t){NULL, 0};
  }
  uint8_t* ptr = ((uint8_t*)((&this->_memory.ptr[this->_cursor])));
  (this->_cursor = (((this->_cursor + size) + 3) & (~((int32_t)(3)))));
  return (__Slice_uint8_t){ptr, length};
}

static inline int32_t math__max_int32_t(int32_t a, int32_t b) {
  if ((a > b)) {
    return a;
  }
  return b;
}

static inline int32_t math__min_int32_t(int32_t a, int32_t b) {
  if ((a < b)) {
    return a;
  }
  return b;
}

int main(int argc, char** argv) { __mp_argc = argc; __mp_argv = argv; main__main(); return 0; }


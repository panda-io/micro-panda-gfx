#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct Canvas Canvas;
typedef struct Container Container;
typedef struct DisplayConn DisplayConn;
typedef struct Point Point;
typedef struct Rect Rect;
typedef struct GraphicsDriver GraphicsDriver;
typedef struct Graphics Graphics;
typedef struct Node Node;
typedef struct RenderContext RenderContext;
typedef struct SpriteSheet SpriteSheet;
typedef struct Allocator Allocator;
typedef struct ArrayList_Node_p ArrayList_Node_p;
typedef struct Font Font;

typedef enum {
  DisplayInterface_I2C = 0,
  DisplayInterface_SPI = 1,
} DisplayInterface;

typedef enum {
  DisplayColor_MONO = 0,
  DisplayColor_RGB565 = 1,
} DisplayColor;

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

typedef enum {
  SpriteSize_Size8x8 = 0,
  SpriteSize_Size16x16 = 1,
  SpriteSize_Size32x32 = 2,
} SpriteSize;

typedef struct { uint8_t* ptr; int32_t size; } __Slice_uint8_t;
typedef struct { uint16_t* ptr; int32_t size; } __Slice_uint16_t;
typedef struct { int32_t* ptr; int32_t size; } __Slice_int32_t;
typedef struct { Node** ptr; int32_t size; } __Slice_Node_p;

typedef void (*__Fn_void_void_p_Rotation)(void*, Rotation);
typedef void (*__Fn_void_void_p_Rect_p_Slice_uint8_t)(void*, Rect*, __Slice_uint8_t);
typedef void (*__Fn_void_void_p)(void*);
typedef void (*__Fn_void_RenderContext_p_Point_p_void_p)(RenderContext*, Point*, void*);

#include <math.h>
#include <string.h>

struct DisplayConn {
  DisplayInterface interface;
  int32_t device;
  int32_t dc_pin;
  int32_t reset_pin;
  int32_t back_light_pin;
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

struct GraphicsDriver {
  int32_t width;
  int32_t height;
  __Slice_uint8_t strip0;
  __Slice_uint8_t strip1;
  void* handle;
  __Fn_void_void_p_Rotation set_rotation;
  __Fn_void_void_p_Rect_p_Slice_uint8_t flush;
  __Fn_void_void_p wait;
  __Fn_void_void_p frame_complete;
};

struct SpriteSheet {
  __Slice_uint8_t data;
  __Slice_int32_t offsets;
  __Slice_uint16_t palette;
  SpriteSize size;
  int32_t count;
  IndexFormat index_format;
};

struct Allocator {
  __Slice_uint8_t _memory;
  int32_t _cursor;
};

struct Font {
  __Slice_uint8_t data;
  int32_t width;
  int32_t height;
  int32_t advance_x;
  int32_t advance_y;
  uint8_t first;
  uint8_t last;
};

struct Node {
  Rect bound;
  void* handle;
  __Fn_void_RenderContext_p_Point_p_void_p renderer;
};

struct RenderContext {
  __Slice_uint8_t buffer;
  PixelFormat format;
  Rect viewpoint;
};

struct Canvas {
  Node _node;
  __Slice_uint8_t _buffer;
  int32_t _background;
  IndexFormat _index_format;
  __Slice_uint16_t _palette;
};

struct ArrayList_Node_p {
  __Slice_Node_p _buffer;
  int32_t _size;
};

struct Container {
  Node _node;
  ArrayList_Node_p _children;
  bool _clip_content;
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
Canvas* canvas__create_canvas(Allocator* allocator, Rect* bound, int32_t background, IndexFormat index_format, __Slice_uint16_t palette);
void canvas__render_canvas(RenderContext* context, Point* offset, void* handle);
Node* Canvas_get_node(Canvas* this);
static inline void Canvas_draw_pixel(Canvas* this, int32_t x, int32_t y, int32_t color_index);
static inline void Canvas_draw_hline(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t color_index);
static inline void Canvas_draw_vline(Canvas* this, int32_t x, int32_t y, int32_t height, int32_t color_index);
void Canvas_draw_line(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color_index);
void Canvas_draw_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color_index);
static inline void Canvas_fill_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color_index);
void Canvas_clear(Canvas* this);
void Canvas_draw_circle(Canvas* this, int32_t cx, int32_t cy, int32_t r, int32_t color_index);
void Canvas_fill_circle(Canvas* this, int32_t cx, int32_t cy, int32_t r, int32_t color_index);
void Canvas_draw_triangle(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color_index);
void Canvas_fill_triangle(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color_index);
void Canvas_draw_round_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t r, int32_t color_index);
void Canvas_fill_round_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t r, int32_t color);
static void Canvas__init(Canvas* this, Allocator* allocator, Rect* bound, int32_t background, IndexFormat index_format, __Slice_uint16_t palette);
static inline void Canvas__render(Canvas* this, RenderContext* context, Rect* rect, Point* offset);
static void Canvas__fill_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color);
static void Canvas__circle_8(Canvas* this, int32_t cx, int32_t cy, int32_t x, int32_t y, int32_t color);
static void Canvas__set_pixel_index1(Canvas* this, int32_t x, int32_t y, int32_t color);
static void Canvas__set_pixel_index2(Canvas* this, int32_t x, int32_t y, int32_t color);
static void Canvas__set_pixel_index4(Canvas* this, int32_t x, int32_t y, int32_t color);
static void Canvas__set_pixel_index8(Canvas* this, int32_t x, int32_t y, int32_t color_index);
static void Canvas__render_index1(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset);
static void Canvas__render_index2(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset);
static void Canvas__render_index4(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset);
static void Canvas__render_index8(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset);
static inline int32_t Canvas__abs(Canvas* this, int32_t v);
static inline int32_t Canvas__sign(Canvas* this, int32_t v);
static inline int32_t Canvas__sqrt(Canvas* this, int32_t n);
Container* container__create_container(Allocator* allocator, Rect* bound, int32_t capacity, bool clip_content);
void container__render_container(RenderContext* context, Point* offset, void* handle);
Node* Container_get_node(Container* this);
bool Container_add(Container* this, Node* node);
static void Container__init(Container* this, Allocator* allocator, Rect* bound, int32_t capacity, bool clip_content);
static inline void Point_copy(Point* this, Point* point);
static inline void Rect_copy(Rect* this, Rect* rect);
static inline bool Rect_intersect(Rect* this, Rect* rect);
static inline bool Rect_clip(Rect* this, Rect* result, Rect* viewpoint, Point* offset);
static inline bool Rect_contains(Rect* this, Point* point);
static inline void Rect_merge(Rect* this, Rect* rect);
void Graphics_set_root(Graphics* this, Node* node);
void Graphics_init(Graphics* this, GraphicsDriver* driver, PixelFormat pixel_format, uint16_t background, Rotation rotation, bool dirty_render);
void Graphics_mark_dirty(Graphics* this, Rect* rect);
void Graphics_render(Graphics* this);
static __Slice_uint8_t Graphics__front_strip(Graphics* this);
static __Slice_uint8_t Graphics__back_strip(Graphics* this);
static void Graphics__clear_strip(Graphics* this, __Slice_uint8_t buffer);
static inline bool RenderContext_intersect(RenderContext* this, Rect* rect);
static inline void RenderContext_set_pixel(RenderContext* this, Point* point, uint16_t color);
static inline void RenderContext_fill_rect(RenderContext* this, Rect* rect, uint16_t color);
static inline void RenderContext_draw_hline(RenderContext* this, int32_t x, int32_t y, int32_t width, uint16_t color);
static inline void RenderContext_draw_vline(RenderContext* this, int32_t x, int32_t y, int32_t height, uint16_t color);
static inline void RenderContext_draw_rect(RenderContext* this, Rect* rect, uint16_t color);
void RenderContext_fill_round_rect(RenderContext* this, Rect* rect, int32_t radius, uint16_t color);
void RenderContext_draw_round_rect(RenderContext* this, Rect* rect, int32_t radius, uint16_t color);
void RenderContext_draw_text(RenderContext* this, int32_t x, int32_t y, __Slice_uint8_t text, Font* font, uint16_t color);
void RenderContext_draw_sprite(RenderContext* this, int32_t x, int32_t y, SpriteSheet* sheet, int32_t id);
void RenderContext_draw_sprite_palette(RenderContext* this, int32_t x, int32_t y, SpriteSheet* sheet, int32_t id, __Slice_uint16_t palette);
static void RenderContext__render_sprite(RenderContext* this, int32_t x, int32_t y, SpriteSheet* sheet, int32_t id, __Slice_uint16_t palette);
static void RenderContext__render_sprite_index1(RenderContext* this, int32_t x, int32_t y, int32_t width, int32_t x0, int32_t x1, int32_t y0, int32_t y1, __Slice_uint8_t data, int32_t base, __Slice_uint16_t palette);
static void RenderContext__render_sprite_index2(RenderContext* this, int32_t x, int32_t y, int32_t width, int32_t x0, int32_t x1, int32_t y0, int32_t y1, __Slice_uint8_t data, int32_t base, __Slice_uint16_t palette);
static void RenderContext__render_sprite_index4(RenderContext* this, int32_t x, int32_t y, int32_t width, int32_t x0, int32_t x1, int32_t y0, int32_t y1, __Slice_uint8_t data, int32_t base, __Slice_uint16_t palette);
static void RenderContext__render_sprite_index8(RenderContext* this, int32_t x, int32_t y, int32_t width, int32_t x0, int32_t x1, int32_t y0, int32_t y1, __Slice_uint8_t data, int32_t base, __Slice_uint16_t palette);
static inline void RenderContext__set_pixel_mono(RenderContext* this, Point* point, uint16_t color);
static inline void RenderContext__set_pixel_rgb565(RenderContext* this, Point* point, uint16_t color);
static inline int32_t SpriteSheet_pixel_width(SpriteSheet* this);
static inline int32_t SpriteSheet_pixel_height(SpriteSheet* this);
static inline int32_t SpriteSheet_bytes_per_sprite(SpriteSheet* this);
static inline int32_t SpriteSheet_sprite_data_offset(SpriteSheet* this, int32_t id);
static inline int32_t math__floor_q16(int32_t value);
static inline int32_t math__ceil_q16(int32_t value);
static inline int32_t math__round_q16(int32_t value);
static inline int32_t math__floor_fixed(int32_t value);
static inline int32_t math__ceil_fixed(int32_t value);
static inline int32_t math__round_fixed(int32_t value);
void Allocator_init(Allocator* this, __Slice_uint8_t mem);
static inline void* Allocator_allocate(Allocator* this, size_t __sizeof_T);
static inline int32_t Allocator_available(Allocator* this);
static inline void Allocator_reset(Allocator* this);
bool ArrayList_Node_p_init(ArrayList_Node_p* this, Allocator* alloc, int32_t capacity);
static inline bool ArrayList_Node_p_push(ArrayList_Node_p* this, Node* value);
static inline bool ArrayList_Node_p_pop(ArrayList_Node_p* this);
bool ArrayList_Node_p_insert(ArrayList_Node_p* this, int32_t i, Node* value);
static inline Node* ArrayList_Node_p_get(ArrayList_Node_p* this, int32_t i);
static inline void ArrayList_Node_p_set(ArrayList_Node_p* this, int32_t i, Node* value);
static inline Node* ArrayList_Node_p_top(ArrayList_Node_p* this);
static inline int32_t ArrayList_Node_p_size(ArrayList_Node_p* this);
static inline int32_t ArrayList_Node_p_capacity(ArrayList_Node_p* this);
static inline bool ArrayList_Node_p_is_empty(ArrayList_Node_p* this);
static inline bool ArrayList_Node_p_is_full(ArrayList_Node_p* this);
static inline void ArrayList_Node_p_clear(ArrayList_Node_p* this);
static inline void memory__memory_set(__Slice_uint8_t dst, uint8_t value);
static inline void memory__memory_copy(__Slice_uint8_t dst, __Slice_uint8_t src, int32_t size);
static inline void memory__memory_move(__Slice_uint8_t dst, __Slice_uint8_t src, int32_t size);
static inline void memory__memory_zero(__Slice_uint8_t dst);
int32_t Font_get_pixel(Font* this, uint8_t c, int32_t px, int32_t py);
static inline Canvas* Allocator_allocate_Canvas(Allocator* this);
static inline Container* Allocator_allocate_Container(Allocator* this);
static inline __Slice_uint8_t Allocator_allocate_array_uint8_t(Allocator* this, int32_t length);
static inline __Slice_Node_p Allocator_allocate_array_Node_p(Allocator* this, int32_t length);
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

Canvas* canvas__create_canvas(Allocator* allocator, Rect* bound, int32_t background, IndexFormat index_format, __Slice_uint16_t palette) {
  Canvas* canvas = Allocator_allocate_Canvas(allocator);
  Canvas__init(canvas, allocator, bound, background, index_format, palette);
  return canvas;
}

void canvas__render_canvas(RenderContext* context, Point* offset, void* handle) {
  Canvas* canvas = ((Canvas*)(handle));
  Rect clipped = {0};
  if ((!Rect_clip((&canvas->_node.bound), (&clipped), (&context->viewpoint), offset))) {
    return;
  }
  Canvas__render(canvas, context, (&clipped), offset);
}

Node* Canvas_get_node(Canvas* this) {
  return (&this->_node);
}

static inline void Canvas_draw_pixel(Canvas* this, int32_t x, int32_t y, int32_t color_index) {
  switch (this->_index_format) {
    case IndexFormat_Index1: {
      Canvas__set_pixel_index1(this, x, y, color_index);
      break;
    }
    case IndexFormat_Index2: {
      Canvas__set_pixel_index2(this, x, y, color_index);
      break;
    }
    case IndexFormat_Index4: {
      Canvas__set_pixel_index4(this, x, y, color_index);
      break;
    }
    case IndexFormat_Index8: {
      Canvas__set_pixel_index8(this, x, y, color_index);
      break;
    }
  }
}

static inline void Canvas_draw_hline(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t color_index) {
  Canvas__fill_rect(this, x, y, width, 1, color_index);
}

static inline void Canvas_draw_vline(Canvas* this, int32_t x, int32_t y, int32_t height, int32_t color_index) {
  Canvas__fill_rect(this, x, y, 1, height, color_index);
}

void Canvas_draw_line(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color_index) {
  int32_t dx = Canvas__abs(this, (x1 - x0));
  int32_t dy = Canvas__abs(this, (y1 - y0));
  int32_t sx = Canvas__sign(this, (x1 - x0));
  int32_t sy = Canvas__sign(this, (y1 - y0));
  int32_t err = (dx - dy);
  int32_t cx = x0;
  int32_t cy = y0;
  while (true) {
    Canvas_draw_pixel(this, cx, cy, color_index);
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

void Canvas_draw_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color_index) {
  Canvas__fill_rect(this, x, y, width, 1, color_index);
  Canvas__fill_rect(this, x, ((y + height) - 1), width, 1, color_index);
  Canvas__fill_rect(this, x, (y + 1), 1, (height - 2), color_index);
  Canvas__fill_rect(this, ((x + width) - 1), (y + 1), 1, (height - 2), color_index);
}

static inline void Canvas_fill_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color_index) {
  Canvas__fill_rect(this, x, y, width, height, color_index);
}

void Canvas_clear(Canvas* this) {
  Canvas__fill_rect(this, 0, 0, this->_node.bound.width, this->_node.bound.height, this->_background);
}

void Canvas_draw_circle(Canvas* this, int32_t cx, int32_t cy, int32_t r, int32_t color_index) {
  int32_t x = 0;
  int32_t y = r;
  int32_t d = (1 - r);
  Canvas__circle_8(this, cx, cy, x, y, color_index);
  while ((x < y)) {
    if ((d < 0)) {
      (d += ((2 * x) + 3));
    } else {
      (d += ((2 * (x - y)) + 5));
      (y -= 1);
    }
    (x += 1);
    Canvas__circle_8(this, cx, cy, x, y, color_index);
  }
}

void Canvas_fill_circle(Canvas* this, int32_t cx, int32_t cy, int32_t r, int32_t color_index) {
  for (int32_t dy = (-r); dy < (r + 1); dy++) {
    int32_t dx = Canvas__sqrt(this, ((r * r) - (dy * dy)));
    Canvas__fill_rect(this, (cx - dx), (cy + dy), ((dx * 2) + 1), 1, color_index);
  }
}

void Canvas_draw_triangle(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color_index) {
  Canvas_draw_line(this, x0, y0, x1, y1, color_index);
  Canvas_draw_line(this, x1, y1, x2, y2, color_index);
  Canvas_draw_line(this, x2, y2, x0, y0, color_index);
}

void Canvas_fill_triangle(Canvas* this, int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color_index) {
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
    Canvas__fill_rect(this, xa, y, ((xb - xa) + 1), 1, color_index);
  }
}

void Canvas_draw_round_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t r, int32_t color_index) {
  Canvas__fill_rect(this, (x + r), y, (width - (2 * r)), 1, color_index);
  Canvas__fill_rect(this, (x + r), ((y + height) - 1), (width - (2 * r)), 1, color_index);
  Canvas__fill_rect(this, x, (y + r), 1, (height - (2 * r)), color_index);
  Canvas__fill_rect(this, ((x + width) - 1), (y + r), 1, (height - (2 * r)), color_index);
  int32_t px = 0;
  int32_t py = r;
  int32_t d = (1 - r);
  while ((px <= py)) {
    Canvas_draw_pixel(this, ((((x + width) - 1) - r) + py), ((y + r) - px), color_index);
    Canvas_draw_pixel(this, ((x + r) - py), ((y + r) - px), color_index);
    Canvas_draw_pixel(this, ((((x + width) - 1) - r) + py), ((((y + height) - 1) - r) + px), color_index);
    Canvas_draw_pixel(this, ((x + r) - py), ((((y + height) - 1) - r) + px), color_index);
    Canvas_draw_pixel(this, ((((x + width) - 1) - r) + px), ((y + r) - py), color_index);
    Canvas_draw_pixel(this, ((x + r) - px), ((y + r) - py), color_index);
    Canvas_draw_pixel(this, ((((x + width) - 1) - r) + px), ((((y + height) - 1) - r) + py), color_index);
    Canvas_draw_pixel(this, ((x + r) - px), ((((y + height) - 1) - r) + py), color_index);
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

static void Canvas__init(Canvas* this, Allocator* allocator, Rect* bound, int32_t background, IndexFormat index_format, __Slice_uint16_t palette) {
  Rect_copy((&this->_node.bound), bound);
  (this->_background = background);
  (this->_index_format = index_format);
  (this->_palette = palette);
  int32_t buffer_size = 0;
  if ((index_format == IndexFormat_Index1)) {
    (buffer_size = (((bound->width + 7) / 8) * bound->height));
  }
  if ((index_format == IndexFormat_Index2)) {
    (buffer_size = (((bound->width + 3) / 4) * bound->height));
  }
  if ((index_format == IndexFormat_Index4)) {
    (buffer_size = (((bound->width + 1) / 2) * bound->height));
  }
  if ((index_format == IndexFormat_Index8)) {
    (buffer_size = (bound->width * bound->height));
  }
  if ((buffer_size > 0)) {
    (this->_buffer = Allocator_allocate_array_uint8_t(allocator, buffer_size));
  }
  (this->_node.handle = ((void*)(this)));
  (this->_node.renderer = canvas__render_canvas);
}

static inline void Canvas__render(Canvas* this, RenderContext* context, Rect* rect, Point* offset) {
  switch (this->_index_format) {
    case IndexFormat_Index1: {
      Canvas__render_index1(this, context, rect, offset);
      break;
    }
    case IndexFormat_Index2: {
      Canvas__render_index2(this, context, rect, offset);
      break;
    }
    case IndexFormat_Index4: {
      Canvas__render_index4(this, context, rect, offset);
      break;
    }
    case IndexFormat_Index8: {
      Canvas__render_index8(this, context, rect, offset);
      break;
    }
  }
}

static void Canvas__fill_rect(Canvas* this, int32_t x, int32_t y, int32_t width, int32_t height, int32_t color) {
  if (((width <= 0) || (height <= 0))) {
    return;
  }
  bool intersect = ((((x < this->_node.bound.width) && ((x + width) > 0)) && (y < this->_node.bound.height)) && ((y + height) > 0));
  if ((!intersect)) {
    return;
  }
  int32_t start_x = math__max_int32_t(x, 0);
  int32_t start_y = math__max_int32_t(y, 0);
  int32_t end_x = math__min_int32_t((x + width), this->_node.bound.width);
  int32_t end_y = math__min_int32_t((y + height), this->_node.bound.height);
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
  if (((((x < 0) || (y < 0)) || (x >= this->_node.bound.width)) || (y >= this->_node.bound.height))) {
    return;
  }
  int32_t index = ((y * ((this->_node.bound.width + 7) / 8)) + (x / 8));
  if (((color & 1) != 0)) {
    (this->_buffer.ptr[index] = (this->_buffer.ptr[index] | ((uint8_t)((0x80 >> (x & 7))))));
  } else {
    (this->_buffer.ptr[index] = (this->_buffer.ptr[index] & ((uint8_t)((~(0x80 >> (x & 7)))))));
  }
}

static void Canvas__set_pixel_index2(Canvas* this, int32_t x, int32_t y, int32_t color) {
  if (((((x < 0) || (y < 0)) || (x >= this->_node.bound.width)) || (y >= this->_node.bound.height))) {
    return;
  }
  int32_t index = ((y * ((this->_node.bound.width + 3) / 4)) + (x / 4));
  int32_t shift = ((3 - (x & 3)) * 2);
  (this->_buffer.ptr[index] = ((this->_buffer.ptr[index] & ((uint8_t)((~(0x03 << shift))))) | ((uint8_t)(((color & 0x03) << shift)))));
}

static void Canvas__set_pixel_index4(Canvas* this, int32_t x, int32_t y, int32_t color) {
  if (((((x < 0) || (y < 0)) || (x >= this->_node.bound.width)) || (y >= this->_node.bound.height))) {
    return;
  }
  int32_t index = ((y * ((this->_node.bound.width + 1) / 2)) + (x / 2));
  if (((x & 1) == 0)) {
    (this->_buffer.ptr[index] = ((this->_buffer.ptr[index] & ((uint8_t)(0x0F))) | ((uint8_t)((color << 4)))));
  } else {
    (this->_buffer.ptr[index] = ((this->_buffer.ptr[index] & ((uint8_t)(0xF0))) | ((uint8_t)((color & 0x0F)))));
  }
}

static void Canvas__set_pixel_index8(Canvas* this, int32_t x, int32_t y, int32_t color_index) {
  if (((((x < 0) || (y < 0)) || (x >= this->_node.bound.width)) || (y >= this->_node.bound.height))) {
    return;
  }
  (this->_buffer.ptr[((y * this->_node.bound.width) + x)] = ((uint8_t)(color_index)));
}

static void Canvas__render_index1(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset) {
  int32_t origin_x = (offset->x + this->_node.bound.x);
  int32_t origin_y = (offset->y + this->_node.bound.y);
  Point point = {0};
  for (int32_t y = viewpoint->y; y < (viewpoint->y + viewpoint->height); y++) {
    int32_t ly = (y - origin_y);
    (point.y = y);
    for (int32_t x = viewpoint->x; x < (viewpoint->x + viewpoint->width); x++) {
      int32_t lx = (x - origin_x);
      int32_t index = ((ly * ((this->_node.bound.width + 7) / 8)) + (lx / 8));
      uint16_t color = this->_palette.ptr[0];
      if (((this->_buffer.ptr[index] & ((uint8_t)((0x80 >> (lx & 7))))) != 0)) {
        (color = this->_palette.ptr[1]);
      }
      if ((color != palette__TRANSPARENT)) {
        (point.x = x);
        RenderContext_set_pixel(context, (&point), color);
      }
    }
  }
}

static void Canvas__render_index2(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset) {
  int32_t origin_x = (offset->x + this->_node.bound.x);
  int32_t origin_y = (offset->y + this->_node.bound.y);
  Point point = {0};
  for (int32_t y = viewpoint->y; y < (viewpoint->y + viewpoint->height); y++) {
    int32_t ly = (y - origin_y);
    (point.y = y);
    for (int32_t x = viewpoint->x; x < (viewpoint->x + viewpoint->width); x++) {
      int32_t lx = (x - origin_x);
      int32_t index = ((ly * ((this->_node.bound.width + 3) / 4)) + (lx / 4));
      int32_t shift = ((3 - (lx & 3)) * 2);
      uint16_t color = this->_palette.ptr[((((int32_t)(this->_buffer.ptr[index])) >> shift) & 0x03)];
      if ((color != palette__TRANSPARENT)) {
        (point.x = x);
        RenderContext_set_pixel(context, (&point), color);
      }
    }
  }
}

static void Canvas__render_index4(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset) {
  int32_t origin_x = (offset->x + this->_node.bound.x);
  int32_t origin_y = (offset->y + this->_node.bound.y);
  Point point = {0};
  for (int32_t y = viewpoint->y; y < (viewpoint->y + viewpoint->height); y++) {
    int32_t ly = (y - origin_y);
    (point.y = y);
    for (int32_t x = viewpoint->x; x < (viewpoint->x + viewpoint->width); x++) {
      int32_t lx = (x - origin_x);
      int32_t index = ((ly * ((this->_node.bound.width + 1) / 2)) + (lx / 2));
      uint8_t palette_index = (this->_buffer.ptr[index] & 0x0F);
      if (((lx & 1) == 0)) {
        (palette_index = ((this->_buffer.ptr[index] >> 4) & 0x0F));
      }
      uint16_t color = this->_palette.ptr[palette_index];
      if ((color != palette__TRANSPARENT)) {
        (point.x = x);
        RenderContext_set_pixel(context, (&point), color);
      }
    }
  }
}

static void Canvas__render_index8(Canvas* this, RenderContext* context, Rect* viewpoint, Point* offset) {
  int32_t origin_x = (offset->x + this->_node.bound.x);
  int32_t origin_y = (offset->y + this->_node.bound.y);
  Point point = {0};
  for (int32_t y = viewpoint->y; y < (viewpoint->y + viewpoint->height); y++) {
    int32_t ly = (y - origin_y);
    (point.y = y);
    for (int32_t x = viewpoint->x; x < (viewpoint->x + viewpoint->width); x++) {
      int32_t lx = (x - origin_x);
      uint16_t color = this->_palette.ptr[this->_buffer.ptr[((ly * this->_node.bound.width) + lx)]];
      if ((color != palette__TRANSPARENT)) {
        (point.x = x);
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

Container* container__create_container(Allocator* allocator, Rect* bound, int32_t capacity, bool clip_content) {
  Container* container = Allocator_allocate_Container(allocator);
  Container__init(container, allocator, bound, capacity, clip_content);
  return container;
}

void container__render_container(RenderContext* context, Point* offset, void* handle) {
  Container* container = ((Container*)(handle));
  Point child_offset = {0};
  (child_offset.x = (offset->x + container->_node.bound.x));
  (child_offset.y = (offset->y + container->_node.bound.y));
  Rect saved = {0};
  if (container->_clip_content) {
    Rect_copy((&saved), (&context->viewpoint));
    Rect clipped = {0};
    if ((!Rect_clip((&container->_node.bound), (&clipped), (&context->viewpoint), offset))) {
      return;
    }
    Rect_copy((&context->viewpoint), (&clipped));
  }
  for (int32_t index = 0; index < ArrayList_Node_p_size((&container->_children)); index++) {
    Node* child = ArrayList_Node_p_get((&container->_children), index);
    child->renderer(context, (&child_offset), child->handle);
  }
  if (container->_clip_content) {
    Rect_copy((&context->viewpoint), (&saved));
  }
}

Node* Container_get_node(Container* this) {
  return (&this->_node);
}

bool Container_add(Container* this, Node* node) {
  return ArrayList_Node_p_push((&this->_children), node);
}

static void Container__init(Container* this, Allocator* allocator, Rect* bound, int32_t capacity, bool clip_content) {
  Rect_copy((&this->_node.bound), bound);
  ArrayList_Node_p_init((&this->_children), allocator, capacity);
  (this->_node.handle = ((void*)(this)));
  (this->_node.renderer = container__render_container);
  (this->_clip_content = clip_content);
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

static inline bool Rect_clip(Rect* this, Rect* result, Rect* viewpoint, Point* offset) {
  int32_t x0 = math__max_int32_t((this->x + offset->x), viewpoint->x);
  int32_t y0 = math__max_int32_t((this->y + offset->y), viewpoint->y);
  int32_t x1 = math__min_int32_t(((this->x + offset->x) + this->width), (viewpoint->x + viewpoint->width));
  int32_t y1 = math__min_int32_t(((this->y + offset->y) + this->height), (viewpoint->y + viewpoint->height));
  if (((x0 >= x1) || (y0 >= y1))) {
    return false;
  }
  (result->x = x0);
  (result->y = y0);
  (result->width = (x1 - x0));
  (result->height = (y1 - y0));
  return true;
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

void Graphics_set_root(Graphics* this, Node* node) {
  (this->_root = node);
}

void Graphics_init(Graphics* this, GraphicsDriver* driver, PixelFormat pixel_format, uint16_t background, Rotation rotation, bool dirty_render) {
  (this->_driver = driver);
  (this->_strip0 = driver->strip0);
  (this->_strip1 = driver->strip1);
  (this->_context.format = pixel_format);
  (this->_background = background);
  (this->_dirty_render = dirty_render);
  if ((driver->strip1.size == 0)) {
    (this->_single_buffer = true);
  }
  (this->_render_window.x = 0);
  (this->_render_window.y = 0);
  if (this->_dirty_render) {
    (this->_render_window.width = 0);
    (this->_render_window.height = 0);
  }
  this->_driver->set_rotation(this->_driver->handle, rotation);
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
    this->_driver->wait(this->_driver->handle);
    (this->_front_buffer = (1 - this->_front_buffer));
    this->_driver->flush(this->_driver->handle, (&this->_context.viewpoint), Graphics__front_strip(this));
  }
  this->_driver->frame_complete(this->_driver->handle);
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
      memory__memory_zero(buffer);
    } else {
      memory__memory_set(buffer, 0xFF);
    }
  } else {
    if ((this->_background == 0)) {
      memory__memory_zero(buffer);
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

static inline bool RenderContext_intersect(RenderContext* this, Rect* rect) {
  return Rect_intersect((&this->viewpoint), rect);
}

static inline void RenderContext_set_pixel(RenderContext* this, Point* point, uint16_t color) {
  if ((!Rect_contains((&this->viewpoint), point))) {
    return;
  }
  if ((this->format == PixelFormat_Mono)) {
    RenderContext__set_pixel_mono(this, point, color);
  } else {
    RenderContext__set_pixel_rgb565(this, point, color);
  }
}

static inline void RenderContext_fill_rect(RenderContext* this, Rect* rect, uint16_t color) {
  Rect clipped = {0};
  Point zero = {0};
  (zero.x = 0);
  (zero.y = 0);
  if ((!Rect_clip(rect, (&clipped), (&this->viewpoint), (&zero)))) {
    return;
  }
  Point point = {0};
  for (int32_t y = clipped.y; y < (clipped.y + clipped.height); y++) {
    for (int32_t x = clipped.x; x < (clipped.x + clipped.width); x++) {
      (point.x = x);
      (point.y = y);
      if ((this->format == PixelFormat_Mono)) {
        RenderContext__set_pixel_mono(this, (&point), color);
      } else {
        RenderContext__set_pixel_rgb565(this, (&point), color);
      }
    }
  }
}

static inline void RenderContext_draw_hline(RenderContext* this, int32_t x, int32_t y, int32_t width, uint16_t color) {
  Rect rect = {0};
  (rect.x = x);
  (rect.y = y);
  (rect.width = width);
  (rect.height = 1);
  RenderContext_fill_rect(this, (&rect), color);
}

static inline void RenderContext_draw_vline(RenderContext* this, int32_t x, int32_t y, int32_t height, uint16_t color) {
  Rect rect = {0};
  (rect.x = x);
  (rect.y = y);
  (rect.width = 1);
  (rect.height = height);
  RenderContext_fill_rect(this, (&rect), color);
}

static inline void RenderContext_draw_rect(RenderContext* this, Rect* rect, uint16_t color) {
  RenderContext_draw_hline(this, rect->x, rect->y, rect->width, color);
  RenderContext_draw_hline(this, rect->x, ((rect->y + rect->height) - 1), rect->width, color);
  RenderContext_draw_vline(this, rect->x, (rect->y + 1), (rect->height - 2), color);
  RenderContext_draw_vline(this, ((rect->x + rect->width) - 1), (rect->y + 1), (rect->height - 2), color);
}

void RenderContext_fill_round_rect(RenderContext* this, Rect* rect, int32_t radius, uint16_t color) {
  if ((!Rect_intersect((&this->viewpoint), rect))) {
    return;
  }
  int32_t r = radius;
  Rect center = {0};
  (center.x = (rect->x + r));
  (center.y = rect->y);
  (center.width = (rect->width - (2 * r)));
  (center.height = rect->height);
  RenderContext_fill_rect(this, (&center), color);
  int32_t px = 0;
  int32_t py = r;
  int32_t d = (1 - r);
  while ((px <= py)) {
    RenderContext_draw_hline(this, ((rect->x + r) - py), ((rect->y + r) - px), ((py * 2) - 1), color);
    RenderContext_draw_hline(this, ((rect->x + r) - py), ((((rect->y + rect->height) - r) + px) - 1), ((py * 2) - 1), color);
    RenderContext_draw_hline(this, ((rect->x + r) - px), ((rect->y + r) - py), ((px * 2) - 1), color);
    RenderContext_draw_hline(this, ((rect->x + r) - px), ((((rect->y + rect->height) - r) + py) - 1), ((px * 2) - 1), color);
    if ((d < 0)) {
      (d += ((2 * px) + 3));
    } else {
      (d += ((2 * (px - py)) + 5));
      (py -= 1);
    }
    (px += 1);
  }
}

void RenderContext_draw_round_rect(RenderContext* this, Rect* rect, int32_t radius, uint16_t color) {
  if ((!Rect_intersect((&this->viewpoint), rect))) {
    return;
  }
  int32_t r = radius;
  RenderContext_draw_hline(this, (rect->x + r), rect->y, (rect->width - (2 * r)), color);
  RenderContext_draw_hline(this, (rect->x + r), ((rect->y + rect->height) - 1), (rect->width - (2 * r)), color);
  RenderContext_draw_vline(this, rect->x, (rect->y + r), (rect->height - (2 * r)), color);
  RenderContext_draw_vline(this, ((rect->x + rect->width) - 1), (rect->y + r), (rect->height - (2 * r)), color);
  Point point = {0};
  int32_t px = 0;
  int32_t py = r;
  int32_t d = (1 - r);
  while ((px <= py)) {
    (point.x = ((((rect->x + rect->width) - 1) - r) + py));
    (point.y = ((rect->y + r) - px));
    RenderContext_set_pixel(this, (&point), color);
    (point.x = ((rect->x + r) - py));
    (point.y = ((rect->y + r) - px));
    RenderContext_set_pixel(this, (&point), color);
    (point.x = ((((rect->x + rect->width) - 1) - r) + py));
    (point.y = ((((rect->y + rect->height) - 1) - r) + px));
    RenderContext_set_pixel(this, (&point), color);
    (point.x = ((rect->x + r) - py));
    (point.y = ((((rect->y + rect->height) - 1) - r) + px));
    RenderContext_set_pixel(this, (&point), color);
    (point.x = ((((rect->x + rect->width) - 1) - r) + px));
    (point.y = ((rect->y + r) - py));
    RenderContext_set_pixel(this, (&point), color);
    (point.x = ((rect->x + r) - px));
    (point.y = ((rect->y + r) - py));
    RenderContext_set_pixel(this, (&point), color);
    (point.x = ((((rect->x + rect->width) - 1) - r) + px));
    (point.y = ((((rect->y + rect->height) - 1) - r) + py));
    RenderContext_set_pixel(this, (&point), color);
    (point.x = ((rect->x + r) - px));
    (point.y = ((((rect->y + rect->height) - 1) - r) + py));
    RenderContext_set_pixel(this, (&point), color);
    if ((d < 0)) {
      (d += ((2 * px) + 3));
    } else {
      (d += ((2 * (px - py)) + 5));
      (py -= 1);
    }
    (px += 1);
  }
}

void RenderContext_draw_text(RenderContext* this, int32_t x, int32_t y, __Slice_uint8_t text, Font* font, uint16_t color) {
  Rect glyph = {0};
  (glyph.y = y);
  (glyph.width = font->width);
  (glyph.height = font->height);
  Point point = {0};
  int32_t cursor_x = x;
  for (int32_t i = 0; i < text.size; i++) {
    (glyph.x = cursor_x);
    uint8_t c = text.ptr[i];
    if ((((c >= font->first) && (c <= font->last)) && Rect_intersect((&this->viewpoint), (&glyph)))) {
      for (int32_t py = 0; py < font->height; py++) {
        (point.y = (y + py));
        for (int32_t px = 0; px < font->width; px++) {
          if ((Font_get_pixel(font, c, px, py) != 0)) {
            (point.x = (cursor_x + px));
            RenderContext_set_pixel(this, (&point), color);
          }
        }
      }
      (cursor_x += font->advance_x);
    }
  }
}

void RenderContext_draw_sprite(RenderContext* this, int32_t x, int32_t y, SpriteSheet* sheet, int32_t id) {
  RenderContext__render_sprite(this, x, y, sheet, id, sheet->palette);
}

void RenderContext_draw_sprite_palette(RenderContext* this, int32_t x, int32_t y, SpriteSheet* sheet, int32_t id, __Slice_uint16_t palette) {
  RenderContext__render_sprite(this, x, y, sheet, id, palette);
}

static void RenderContext__render_sprite(RenderContext* this, int32_t x, int32_t y, SpriteSheet* sheet, int32_t id, __Slice_uint16_t palette) {
  int32_t width = SpriteSheet_pixel_width(sheet);
  int32_t height = SpriteSheet_pixel_height(sheet);
  Rect sprite = {0};
  (sprite.x = x);
  (sprite.y = y);
  (sprite.width = width);
  (sprite.height = height);
  Rect clipped = {0};
  Point zero = {0};
  (zero.x = 0);
  (zero.y = 0);
  if ((!Rect_clip((&sprite), (&clipped), (&this->viewpoint), (&zero)))) {
    return;
  }
  int32_t base = SpriteSheet_sprite_data_offset(sheet, id);
  if ((sheet->index_format == IndexFormat_Index1)) {
    RenderContext__render_sprite_index1(this, x, y, width, clipped.x, (clipped.x + clipped.width), clipped.y, (clipped.y + clipped.height), sheet->data, base, palette);
  }
  if ((sheet->index_format == IndexFormat_Index2)) {
    RenderContext__render_sprite_index2(this, x, y, width, clipped.x, (clipped.x + clipped.width), clipped.y, (clipped.y + clipped.height), sheet->data, base, palette);
  }
  if ((sheet->index_format == IndexFormat_Index4)) {
    RenderContext__render_sprite_index4(this, x, y, width, clipped.x, (clipped.x + clipped.width), clipped.y, (clipped.y + clipped.height), sheet->data, base, palette);
  }
  if ((sheet->index_format == IndexFormat_Index8)) {
    RenderContext__render_sprite_index8(this, x, y, width, clipped.x, (clipped.x + clipped.width), clipped.y, (clipped.y + clipped.height), sheet->data, base, palette);
  }
}

static void RenderContext__render_sprite_index1(RenderContext* this, int32_t x, int32_t y, int32_t width, int32_t x0, int32_t x1, int32_t y0, int32_t y1, __Slice_uint8_t data, int32_t base, __Slice_uint16_t palette) {
  int32_t row_bytes = ((width + 7) / 8);
  Point point = {0};
  for (int32_t sy = y0; sy < y1; sy++) {
    int32_t ly = (sy - y);
    (point.y = sy);
    for (int32_t sx = x0; sx < x1; sx++) {
      int32_t lx = (sx - x);
      int32_t idx = ((base + (ly * row_bytes)) + (lx / 8));
      int32_t p = 0;
      if (((data.ptr[idx] & ((uint8_t)((0x80 >> (lx & 7))))) != 0)) {
        (p = 1);
      }
      uint16_t color = palette.ptr[p];
      if ((color != palette__TRANSPARENT)) {
        (point.x = sx);
        RenderContext_set_pixel(this, (&point), color);
      }
    }
  }
}

static void RenderContext__render_sprite_index2(RenderContext* this, int32_t x, int32_t y, int32_t width, int32_t x0, int32_t x1, int32_t y0, int32_t y1, __Slice_uint8_t data, int32_t base, __Slice_uint16_t palette) {
  int32_t row_bytes = ((width + 3) / 4);
  Point point = {0};
  for (int32_t sy = y0; sy < y1; sy++) {
    int32_t ly = (sy - y);
    (point.y = sy);
    for (int32_t sx = x0; sx < x1; sx++) {
      int32_t lx = (sx - x);
      int32_t idx = ((base + (ly * row_bytes)) + (lx / 4));
      int32_t shift = ((3 - (lx & 3)) * 2);
      int32_t p = ((((int32_t)(data.ptr[idx])) >> shift) & 0x03);
      uint16_t color = palette.ptr[p];
      if ((color != palette__TRANSPARENT)) {
        (point.x = sx);
        RenderContext_set_pixel(this, (&point), color);
      }
    }
  }
}

static void RenderContext__render_sprite_index4(RenderContext* this, int32_t x, int32_t y, int32_t width, int32_t x0, int32_t x1, int32_t y0, int32_t y1, __Slice_uint8_t data, int32_t base, __Slice_uint16_t palette) {
  int32_t row_bytes = ((width + 1) / 2);
  Point point = {0};
  for (int32_t sy = y0; sy < y1; sy++) {
    int32_t ly = (sy - y);
    (point.y = sy);
    for (int32_t sx = x0; sx < x1; sx++) {
      int32_t lx = (sx - x);
      int32_t idx = ((base + (ly * row_bytes)) + (lx / 2));
      int32_t p = (((int32_t)(data.ptr[idx])) & 0x0F);
      if (((lx & 1) == 0)) {
        (p = ((((int32_t)(data.ptr[idx])) >> 4) & 0x0F));
      }
      uint16_t color = palette.ptr[p];
      if ((color != palette__TRANSPARENT)) {
        (point.x = sx);
        RenderContext_set_pixel(this, (&point), color);
      }
    }
  }
}

static void RenderContext__render_sprite_index8(RenderContext* this, int32_t x, int32_t y, int32_t width, int32_t x0, int32_t x1, int32_t y0, int32_t y1, __Slice_uint8_t data, int32_t base, __Slice_uint16_t palette) {
  Point point = {0};
  for (int32_t sy = y0; sy < y1; sy++) {
    int32_t ly = (sy - y);
    (point.y = sy);
    for (int32_t sx = x0; sx < x1; sx++) {
      int32_t lx = (sx - x);
      uint16_t color = palette.ptr[data.ptr[((base + (ly * width)) + lx)]];
      if ((color != palette__TRANSPARENT)) {
        (point.x = sx);
        RenderContext_set_pixel(this, (&point), color);
      }
    }
  }
}

static inline void RenderContext__set_pixel_mono(RenderContext* this, Point* point, uint16_t color) {
  int32_t index = ((point->y * ((this->viewpoint.width + 7) / 8)) + (point->x / 8));
  if ((color == 0)) {
    (this->buffer.ptr[index] = (this->buffer.ptr[index] & ((uint8_t)((~(0x80 >> (point->x & 7)))))));
  } else {
    (this->buffer.ptr[index] = (this->buffer.ptr[index] | ((uint8_t)((0x80 >> (point->x & 7))))));
  }
}

static inline void RenderContext__set_pixel_rgb565(RenderContext* this, Point* point, uint16_t color) {
  int32_t index = (((point->y * this->viewpoint.width) + point->x) * 2);
  (this->buffer.ptr[index] = ((uint8_t)((color >> 8))));
  (this->buffer.ptr[(index + 1)] = ((uint8_t)(color)));
}

static inline int32_t SpriteSheet_pixel_width(SpriteSheet* this) {
  if ((this->size == SpriteSize_Size8x8)) {
    return 8;
  }
  if ((this->size == SpriteSize_Size16x16)) {
    return 16;
  }
  return 32;
}

static inline int32_t SpriteSheet_pixel_height(SpriteSheet* this) {
  return SpriteSheet_pixel_width(this);
}

static inline int32_t SpriteSheet_bytes_per_sprite(SpriteSheet* this) {
  int32_t w = SpriteSheet_pixel_width(this);
  int32_t h = SpriteSheet_pixel_height(this);
  if ((this->index_format == IndexFormat_Index1)) {
    return (((w + 7) / 8) * h);
  }
  if ((this->index_format == IndexFormat_Index2)) {
    return (((w + 3) / 4) * h);
  }
  if ((this->index_format == IndexFormat_Index4)) {
    return (((w + 1) / 2) * h);
  }
  return (w * h);
}

static inline int32_t SpriteSheet_sprite_data_offset(SpriteSheet* this, int32_t id) {
  if ((this->offsets.size > 0)) {
    return this->offsets.ptr[id];
  }
  return (id * SpriteSheet_bytes_per_sprite(this));
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

static inline int32_t Allocator_available(Allocator* this) {
  return (this->_memory.size - this->_cursor);
}

static inline void Allocator_reset(Allocator* this) {
  (this->_cursor = 0);
}

bool ArrayList_Node_p_init(ArrayList_Node_p* this, Allocator* alloc, int32_t capacity) {
  (this->_buffer = Allocator_allocate_array_Node_p(alloc, capacity));
  if ((this->_buffer.size == 0)) {
    return false;
  }
  return true;
}

static inline bool ArrayList_Node_p_push(ArrayList_Node_p* this, Node* value) {
  if ((this->_size >= this->_buffer.size)) {
    return false;
  }
  (this->_buffer.ptr[this->_size] = value);
  (this->_size += 1);
  return true;
}

static inline bool ArrayList_Node_p_pop(ArrayList_Node_p* this) {
  if ((this->_size == 0)) {
    return false;
  }
  (this->_size -= 1);
  return true;
}

bool ArrayList_Node_p_insert(ArrayList_Node_p* this, int32_t i, Node* value) {
  if ((this->_size >= this->_buffer.size)) {
    return false;
  }
  if ((i > this->_size)) {
    return false;
  }
  int32_t j = this->_size;
  while ((j > i)) {
    (this->_buffer.ptr[j] = this->_buffer.ptr[(j - 1)]);
    (j -= 1);
  }
  (this->_buffer.ptr[i] = value);
  (this->_size += 1);
  return true;
}

static inline Node* ArrayList_Node_p_get(ArrayList_Node_p* this, int32_t i) {
  return this->_buffer.ptr[i];
}

static inline void ArrayList_Node_p_set(ArrayList_Node_p* this, int32_t i, Node* value) {
  (this->_buffer.ptr[i] = value);
}

static inline Node* ArrayList_Node_p_top(ArrayList_Node_p* this) {
  return this->_buffer.ptr[(this->_size - 1)];
}

static inline int32_t ArrayList_Node_p_size(ArrayList_Node_p* this) {
  return this->_size;
}

static inline int32_t ArrayList_Node_p_capacity(ArrayList_Node_p* this) {
  return this->_buffer.size;
}

static inline bool ArrayList_Node_p_is_empty(ArrayList_Node_p* this) {
  return (this->_size == 0);
}

static inline bool ArrayList_Node_p_is_full(ArrayList_Node_p* this) {
  return (this->_size >= this->_buffer.size);
}

static inline void ArrayList_Node_p_clear(ArrayList_Node_p* this) {
  (this->_size = 0);
}

static inline void memory__memory_set(__Slice_uint8_t dst, uint8_t value) {
  memset(dst.ptr, value, dst.size);
}

static inline void memory__memory_copy(__Slice_uint8_t dst, __Slice_uint8_t src, int32_t size) {
  memcpy(dst.ptr, src.ptr, size);
}

static inline void memory__memory_move(__Slice_uint8_t dst, __Slice_uint8_t src, int32_t size) {
  memmove(dst.ptr, src.ptr, size);
}

static inline void memory__memory_zero(__Slice_uint8_t dst) {
  memory__memory_set(dst, ((uint8_t)(0)));
}

int32_t Font_get_pixel(Font* this, uint8_t c, int32_t px, int32_t py) {
  if (((c < this->first) || (c > this->last))) {
    return 0;
  }
  if (((((px < 0) || (px >= this->width)) || (py < 0)) || (py >= this->height))) {
    return 0;
  }
  int32_t offset = ((((int32_t)((c - this->first))) * this->width) + px);
  return ((int32_t)(((this->data.ptr[offset] >> ((uint8_t)(py))) & ((uint8_t)(1)))));
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

static inline Container* Allocator_allocate_Container(Allocator* this) {
  uint64_t size = sizeof(Container);
  if (((this->_cursor + size) > this->_memory.size)) {
    return NULL;
  }
  Container* ptr = ((Container*)((&this->_memory.ptr[this->_cursor])));
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

static inline __Slice_Node_p Allocator_allocate_array_Node_p(Allocator* this, int32_t length) {
  uint64_t size = (sizeof(Node*) * length);
  if (((this->_cursor + size) > this->_memory.size)) {
    return (__Slice_Node_p){NULL, 0};
  }
  Node** ptr = ((Node**)((&this->_memory.ptr[this->_cursor])));
  (this->_cursor = (((this->_cursor + size) + 3) & (~((int32_t)(3)))));
  return (__Slice_Node_p){ptr, length};
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


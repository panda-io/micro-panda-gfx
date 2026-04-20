#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct Canvas Canvas;
typedef struct Container Container;
typedef struct Bitmap Bitmap;
typedef struct Text Text;
typedef struct Image Image;
typedef struct SpriteSheet SpriteSheet;
typedef struct Font Font;
typedef struct Context Context;
typedef struct Connection Connection;
typedef struct Point Point;
typedef struct Rect Rect;
typedef struct Driver Driver;
typedef struct Graphics Graphics;
typedef struct Node Node;
typedef struct Allocator Allocator;
typedef struct ArrayList_Node_p ArrayList_Node_p;

typedef enum {
  Interface_I2C = 0,
  Interface_SPI = 1,
} Interface;

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
  Compress_None = 0,
  Compress_RLE = 1,
} Compress;

typedef enum {
  SpriteSize_Size8x8 = 0,
  SpriteSize_Size16x16 = 1,
  SpriteSize_Size32x32 = 2,
} SpriteSize;

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

typedef struct { uint16_t* ptr; int32_t size; } __Slice_uint16_t;
typedef struct { uint8_t* ptr; int32_t size; } __Slice_uint8_t;
typedef struct { int32_t* ptr; int32_t size; } __Slice_int32_t;
typedef struct { Node** ptr; int32_t size; } __Slice_Node_p;

typedef void (*__Fn_void_void_p_Rotation)(void*, Rotation);
typedef void (*__Fn_void_void_p_Rect_p_Slice_uint8_t)(void*, Rect*, __Slice_uint8_t);
typedef void (*__Fn_void_void_p)(void*);
typedef void (*__Fn_void_Context_p_Point_p_void_p)(Context*, Point*, void*);

#include <math.h>
#include <string.h>

struct Image {
  __Slice_uint8_t data;
  __Slice_uint16_t palette;
  int32_t width;
  int32_t height;
  IndexFormat index_format;
  Compress compress;
};

struct SpriteSheet {
  __Slice_uint8_t data;
  __Slice_int32_t offsets;
  __Slice_uint16_t palette;
  SpriteSize size;
  int32_t count;
  IndexFormat index_format;
  Compress compress;
};

struct Font {
  SpriteSheet* sheet;
  int32_t advance_x;
  int32_t advance_y;
  uint8_t first;
  uint8_t last;
};

struct Connection {
  Interface interface;
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

struct Driver {
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

struct Allocator {
  __Slice_uint8_t _memory;
  int32_t _cursor;
};

struct Canvas {
  Image _image;
  int32_t _background;
  Rect _bound;
};

struct Context {
  __Slice_uint8_t buffer;
  PixelFormat format;
  Rect viewpoint;
};

struct Node {
  Rect bound;
  void* handle;
  __Fn_void_Context_p_Point_p_void_p renderer;
};

struct Graphics {
  Driver* _driver;
  Node* _root;
  uint16_t _background;
  bool _dirty_render;
  Rect _render_window;
  __Slice_uint8_t _strip0;
  __Slice_uint8_t _strip1;
  bool _single_buffer;
  int32_t _front_buffer;
  Context _context;
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

struct Bitmap {
  Node _node;
  __Slice_uint8_t _data;
  IndexFormat _index_format;
  __Slice_uint16_t _palette;
};

struct Text {
  Node _node;
  __Slice_uint8_t _text;
  Font* _font;
  uint16_t _color;
  bool _wrap;
};

void main__main(void);
Canvas* texture__canvas__create_canvas(Allocator* allocator, int32_t width, int32_t height, int32_t background, IndexFormat index_format, __Slice_uint16_t palette);
Image* Canvas_get_image(Canvas* this);
static inline void Canvas_draw_pixel(Canvas* this, Point* point, int32_t color_index);
void Canvas_draw_rect(Canvas* this, Rect* rect, int32_t color_index);
void Canvas_fill_rect(Canvas* this, Rect* rect, int32_t color_index);
void Canvas_clear(Canvas* this);
static void Canvas__init(Canvas* this, Allocator* allocator, int32_t width, int32_t height, int32_t background, IndexFormat index_format, __Slice_uint16_t palette);
static void Canvas__set_pixel_index1(Canvas* this, Point* point, int32_t color);
static void Canvas__set_pixel_index2(Canvas* this, Point* point, int32_t color);
static void Canvas__set_pixel_index4(Canvas* this, Point* point, int32_t color);
static void Canvas__set_pixel_index8(Canvas* this, Point* point, int32_t color_index);
Container* node__container__create_container(Allocator* allocator, Rect* bound, int32_t capacity, bool clip_content);
void node__container__render_container(Context* context, Point* offset, void* handle);
Node* Container_get_node(Container* this);
bool Container_add(Container* this, Node* node);
static void Container__init(Container* this, Allocator* allocator, Rect* bound, int32_t capacity, bool clip_content);
Bitmap* node__bitmap__create_bitmap_from_image(Allocator* allocator, Point* point, Image* image);
Bitmap* node__bitmap__create_bitmap_from_sprite_sheet(Allocator* allocator, Point* point, SpriteSheet* sheet, int32_t id);
Bitmap* node__bitmap__create_bitmap_from_canvas(Allocator* allocator, Point* point, Canvas* canvas);
void node__bitmap__render_bitmap(Context* context, Point* offset, void* handle);
Node* Bitmap_get_node(Bitmap* this);
static void Bitmap__init(Bitmap* this, Rect* rect, __Slice_uint8_t data, IndexFormat index_format, __Slice_uint16_t palette);
Text* node__text__create_text(Allocator* allocator, Rect* bound, __Slice_uint8_t text, uint16_t color, bool wrap, Font* font);
void node__text__render_text(Context* context, Point* offset, void* handle);
Node* Text_get_node(Text* this);
static void Text__init(Text* this, Rect* bound, __Slice_uint8_t text, uint16_t color, bool wrap, Font* font);
static inline int32_t SpriteSheet_sprite_width(SpriteSheet* this);
static inline int32_t SpriteSheet_sprite_height(SpriteSheet* this);
static inline int32_t SpriteSheet_bytes_per_sprite(SpriteSheet* this);
static inline int32_t SpriteSheet_sprite_data_offset(SpriteSheet* this, int32_t id);
static inline int32_t SpriteSheet_sprite_data_length(SpriteSheet* this, int32_t id);
static inline bool Context_intersect(Context* this, Rect* rect);
static inline void Context_draw_pixel(Context* this, Point* point, uint16_t color);
void Context_draw_hline(Context* this, Point* point, int32_t width, uint16_t color);
void Context_draw_vline(Context* this, Point* point, int32_t height, uint16_t color);
void Context_draw_rect(Context* this, Rect* rect, uint16_t color);
void Context_fill_rect(Context* this, Rect* rect, uint16_t color);
void Context_draw_round_rect(Context* this, Rect* rect, int32_t radius, uint16_t color);
void Context_fill_round_rect(Context* this, Rect* rect, int32_t radius, uint16_t color);
void Context_draw_bitmap(Context* this, Rect* rect, __Slice_uint8_t data, IndexFormat index_format, __Slice_uint16_t palette);
static void Context__render_bitmap_index1(Context* this, Rect* origin, Rect* clipped, __Slice_uint8_t data, __Slice_uint16_t palette);
static void Context__render_bitmap_index2(Context* this, Rect* origin, Rect* clipped, __Slice_uint8_t data, __Slice_uint16_t palette);
static void Context__render_bitmap_index4(Context* this, Rect* origin, Rect* clipped, __Slice_uint8_t data, __Slice_uint16_t palette);
static void Context__render_bitmap_index8(Context* this, Rect* origin, Rect* clipped, __Slice_uint8_t data, __Slice_uint16_t palette);
static inline void Context__set_pixel_mono(Context* this, Point* point, uint16_t color);
static inline void Context__set_pixel_rgb565(Context* this, Point* point, uint16_t color);
static inline void Point_copy(Point* this, Point* point);
static inline void Rect_copy(Rect* this, Rect* rect);
static inline bool Rect_intersect(Rect* this, Rect* rect);
static inline bool Rect_clip(Rect* this, Rect* result, Rect* viewpoint, Point* offset);
static inline bool Rect_contains(Rect* this, Point* point);
static inline void Rect_merge(Rect* this, Rect* rect);
void Graphics_set_root(Graphics* this, Node* node);
void Graphics_init(Graphics* this, Driver* driver, PixelFormat pixel_format, uint16_t background, Rotation rotation, bool dirty_render);
void Graphics_mark_dirty(Graphics* this, Rect* rect);
void Graphics_render(Graphics* this);
static __Slice_uint8_t Graphics__front_strip(Graphics* this);
static __Slice_uint8_t Graphics__back_strip(Graphics* this);
static void Graphics__clear_strip(Graphics* this, __Slice_uint8_t buffer);
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
static inline Canvas* Allocator_allocate_Canvas(Allocator* this);
static inline Container* Allocator_allocate_Container(Allocator* this);
static inline Bitmap* Allocator_allocate_Bitmap(Allocator* this);
static inline Text* Allocator_allocate_Text(Allocator* this);
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

Canvas* texture__canvas__create_canvas(Allocator* allocator, int32_t width, int32_t height, int32_t background, IndexFormat index_format, __Slice_uint16_t palette) {
  Canvas* canvas = Allocator_allocate_Canvas(allocator);
  Canvas__init(canvas, allocator, width, height, background, index_format, palette);
  return canvas;
}

Image* Canvas_get_image(Canvas* this) {
  return (&this->_image);
}

static inline void Canvas_draw_pixel(Canvas* this, Point* point, int32_t color_index) {
  switch (this->_image.index_format) {
    case IndexFormat_Index1: {
      Canvas__set_pixel_index1(this, point, color_index);
      break;
    }
    case IndexFormat_Index2: {
      Canvas__set_pixel_index2(this, point, color_index);
      break;
    }
    case IndexFormat_Index4: {
      Canvas__set_pixel_index4(this, point, color_index);
      break;
    }
    case IndexFormat_Index8: {
      Canvas__set_pixel_index8(this, point, color_index);
      break;
    }
  }
}

void Canvas_draw_rect(Canvas* this, Rect* rect, int32_t color_index) {
  Rect line_rect = {0};
  (line_rect.x = rect->x);
  (line_rect.y = rect->y);
  (line_rect.width = rect->width);
  (line_rect.height = 1);
  Canvas_fill_rect(this, (&line_rect), color_index);
  (line_rect.y = ((rect->y + rect->height) - 1));
  Canvas_fill_rect(this, (&line_rect), color_index);
  (line_rect.y = (rect->y + 1));
  (line_rect.height = (rect->height - 2));
  Canvas_fill_rect(this, (&line_rect), color_index);
  (line_rect.x = ((rect->x + rect->width) - 1));
  Canvas_fill_rect(this, (&line_rect), color_index);
}

void Canvas_fill_rect(Canvas* this, Rect* rect, int32_t color_index) {
  Rect clipped = {0};
  Point zero = {0};
  (zero.x = 0);
  (zero.y = 0);
  if ((!Rect_clip((&this->_bound), (&clipped), rect, (&zero)))) {
    return;
  }
  Point point = {0};
  for (int32_t y = clipped.y; y < (clipped.y + clipped.height); y++) {
    for (int32_t x = clipped.x; x < (clipped.x + clipped.width); x++) {
      (point.x = x);
      (point.y = y);
      Canvas_draw_pixel(this, (&point), color_index);
    }
  }
}

void Canvas_clear(Canvas* this) {
  Canvas_fill_rect(this, (&this->_bound), this->_background);
}

static void Canvas__init(Canvas* this, Allocator* allocator, int32_t width, int32_t height, int32_t background, IndexFormat index_format, __Slice_uint16_t palette) {
  (this->_image.width = width);
  (this->_image.height = height);
  (this->_image.index_format = index_format);
  (this->_image.palette = palette);
  int32_t buffer_size = 0;
  if ((index_format == IndexFormat_Index1)) {
    (buffer_size = (((width + 7) / 8) * height));
  }
  if ((index_format == IndexFormat_Index2)) {
    (buffer_size = (((width + 3) / 4) * height));
  }
  if ((index_format == IndexFormat_Index4)) {
    (buffer_size = (((width + 1) / 2) * height));
  }
  if ((index_format == IndexFormat_Index8)) {
    (buffer_size = (width * height));
  }
  if ((buffer_size > 0)) {
    (this->_image.data = Allocator_allocate_array_uint8_t(allocator, buffer_size));
  }
  (this->_background = background);
  (this->_bound.x = 0);
  (this->_bound.y = 0);
  (this->_bound.width = width);
  (this->_bound.height = height);
}

static void Canvas__set_pixel_index1(Canvas* this, Point* point, int32_t color) {
  if ((!Rect_contains((&this->_bound), point))) {
    return;
  }
  int32_t index = ((point->y * ((this->_image.width + 7) / 8)) + (point->x / 8));
  if (((color & 1) != 0)) {
    (this->_image.data.ptr[index] = (this->_image.data.ptr[index] | ((uint8_t)((0x80 >> (point->x & 7))))));
  } else {
    (this->_image.data.ptr[index] = (this->_image.data.ptr[index] & ((uint8_t)((~(0x80 >> (point->x & 7)))))));
  }
}

static void Canvas__set_pixel_index2(Canvas* this, Point* point, int32_t color) {
  if ((!Rect_contains((&this->_bound), point))) {
    return;
  }
  int32_t index = ((point->y * ((this->_image.width + 3) / 4)) + (point->x / 4));
  int32_t shift = ((3 - (point->x & 3)) * 2);
  (this->_image.data.ptr[index] = ((this->_image.data.ptr[index] & ((uint8_t)((~(0x03 << shift))))) | ((uint8_t)(((color & 0x03) << shift)))));
}

static void Canvas__set_pixel_index4(Canvas* this, Point* point, int32_t color) {
  if ((!Rect_contains((&this->_bound), point))) {
    return;
  }
  int32_t index = ((point->y * ((this->_image.width + 1) / 2)) + (point->x / 2));
  if (((point->x & 1) == 0)) {
    (this->_image.data.ptr[index] = ((this->_image.data.ptr[index] & ((uint8_t)(0x0F))) | ((uint8_t)((color << 4)))));
  } else {
    (this->_image.data.ptr[index] = ((this->_image.data.ptr[index] & ((uint8_t)(0xF0))) | ((uint8_t)((color & 0x0F)))));
  }
}

static void Canvas__set_pixel_index8(Canvas* this, Point* point, int32_t color_index) {
  if ((!Rect_contains((&this->_bound), point))) {
    return;
  }
  int32_t index = ((point->y * this->_image.width) + point->x);
  (this->_image.data.ptr[index] = ((uint8_t)(color_index)));
}

Container* node__container__create_container(Allocator* allocator, Rect* bound, int32_t capacity, bool clip_content) {
  Container* container = Allocator_allocate_Container(allocator);
  Container__init(container, allocator, bound, capacity, clip_content);
  return container;
}

void node__container__render_container(Context* context, Point* offset, void* handle) {
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
  (this->_node.renderer = node__container__render_container);
  (this->_clip_content = clip_content);
}

Bitmap* node__bitmap__create_bitmap_from_image(Allocator* allocator, Point* point, Image* image) {
  Bitmap* bitmap = Allocator_allocate_Bitmap(allocator);
  Rect bound = {0};
  (bound.x = point->x);
  (bound.y = point->y);
  (bound.width = image->width);
  (bound.height = image->height);
  Bitmap__init(bitmap, (&bound), image->data, image->index_format, image->palette);
  return bitmap;
}

Bitmap* node__bitmap__create_bitmap_from_sprite_sheet(Allocator* allocator, Point* point, SpriteSheet* sheet, int32_t id) {
  Bitmap* bitmap = Allocator_allocate_Bitmap(allocator);
  Rect bound = {0};
  (bound.x = point->x);
  (bound.y = point->y);
  (bound.width = SpriteSheet_sprite_width(sheet));
  (bound.height = SpriteSheet_sprite_height(sheet));
  int32_t offset = SpriteSheet_sprite_data_offset(sheet, id);
  int32_t length = SpriteSheet_sprite_data_length(sheet, id);
  Bitmap__init(bitmap, (&bound), (__Slice_uint8_t){(&sheet->data.ptr[offset]), length}, sheet->index_format, sheet->palette);
  return bitmap;
}

Bitmap* node__bitmap__create_bitmap_from_canvas(Allocator* allocator, Point* point, Canvas* canvas) {
  Bitmap* bitmap = Allocator_allocate_Bitmap(allocator);
  Image* image = Canvas_get_image(canvas);
  Rect bound = {0};
  (bound.x = point->x);
  (bound.y = point->y);
  (bound.width = image->width);
  (bound.height = image->height);
  Bitmap__init(bitmap, (&bound), image->data, image->index_format, image->palette);
  return bitmap;
}

void node__bitmap__render_bitmap(Context* context, Point* offset, void* handle) {
  Bitmap* bitmap = ((Bitmap*)(handle));
  Rect rect = {0};
  (rect.x = (offset->x + bitmap->_node.bound.x));
  (rect.y = (offset->y + bitmap->_node.bound.y));
  (rect.width = bitmap->_node.bound.width);
  (rect.height = bitmap->_node.bound.height);
  Context_draw_bitmap(context, (&rect), bitmap->_data, bitmap->_index_format, bitmap->_palette);
}

Node* Bitmap_get_node(Bitmap* this) {
  return (&this->_node);
}

static void Bitmap__init(Bitmap* this, Rect* rect, __Slice_uint8_t data, IndexFormat index_format, __Slice_uint16_t palette) {
  Rect_copy((&this->_node.bound), rect);
  (this->_node.handle = ((void*)(this)));
  (this->_node.renderer = node__bitmap__render_bitmap);
  (this->_data = data);
  (this->_index_format = index_format);
  (this->_palette = palette);
}

Text* node__text__create_text(Allocator* allocator, Rect* bound, __Slice_uint8_t text, uint16_t color, bool wrap, Font* font) {
  Text* t = Allocator_allocate_Text(allocator);
  Text__init(t, bound, text, color, wrap, font);
  return t;
}

void node__text__render_text(Context* context, Point* offset, void* handle) {
  Text* t = ((Text*)(handle));
  Font* font = t->_font;
  (font->sheet->palette.ptr[1] = t->_color);
  int32_t start_x = (offset->x + t->_node.bound.x);
  int32_t bound_right = (start_x + t->_node.bound.width);
  int32_t bound_bottom = ((offset->y + t->_node.bound.y) + t->_node.bound.height);
  Point cursor = {0};
  (cursor.x = start_x);
  (cursor.y = (offset->y + t->_node.bound.y));
  Rect glyph_rect = {0};
  (glyph_rect.width = font->advance_x);
  (glyph_rect.height = font->advance_y);
  for (int32_t i = 0; i < t->_text.size; i++) {
    if ((t->_wrap && ((cursor.x + font->advance_x) > bound_right))) {
      (cursor.x = start_x);
      (cursor.y += font->advance_y);
      if (((cursor.y + font->advance_y) > bound_bottom)) {
        break;
      }
    }
    uint8_t c = t->_text.ptr[i];
    if (((c >= font->first) && (c <= font->last))) {
      int32_t id = (((int32_t)(c)) - ((int32_t)(font->first)));
      int32_t data_offset = SpriteSheet_sprite_data_offset(font->sheet, id);
      int32_t data_length = SpriteSheet_sprite_data_length(font->sheet, id);
      (glyph_rect.x = cursor.x);
      (glyph_rect.y = cursor.y);
      Context_draw_bitmap(context, (&glyph_rect), (__Slice_uint8_t){(&font->sheet->data.ptr[data_offset]), data_length}, font->sheet->index_format, font->sheet->palette);
    }
    (cursor.x += font->advance_x);
  }
}

Node* Text_get_node(Text* this) {
  return (&this->_node);
}

static void Text__init(Text* this, Rect* bound, __Slice_uint8_t text, uint16_t color, bool wrap, Font* font) {
  Rect_copy((&this->_node.bound), bound);
  (this->_node.handle = ((void*)(this)));
  (this->_node.renderer = node__text__render_text);
  (this->_text = text);
  (this->_font = font);
  (this->_color = color);
  (this->_wrap = wrap);
}

static inline int32_t SpriteSheet_sprite_width(SpriteSheet* this) {
  if ((this->size == SpriteSize_Size8x8)) {
    return 8;
  }
  if ((this->size == SpriteSize_Size16x16)) {
    return 16;
  }
  return 32;
}

static inline int32_t SpriteSheet_sprite_height(SpriteSheet* this) {
  return SpriteSheet_sprite_width(this);
}

static inline int32_t SpriteSheet_bytes_per_sprite(SpriteSheet* this) {
  int32_t w = SpriteSheet_sprite_width(this);
  int32_t h = SpriteSheet_sprite_height(this);
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

static inline int32_t SpriteSheet_sprite_data_length(SpriteSheet* this, int32_t id) {
  if ((this->offsets.size > 0)) {
    if (((id + 1) < this->offsets.size)) {
      return (this->offsets.ptr[(id + 1)] - this->offsets.ptr[id]);
    }
    return (this->data.size - this->offsets.ptr[id]);
  }
  return SpriteSheet_bytes_per_sprite(this);
}

static inline bool Context_intersect(Context* this, Rect* rect) {
  return Rect_intersect((&this->viewpoint), rect);
}

static inline void Context_draw_pixel(Context* this, Point* point, uint16_t color) {
  if ((!Rect_contains((&this->viewpoint), point))) {
    return;
  }
  if ((this->format == PixelFormat_Mono)) {
    Context__set_pixel_mono(this, point, color);
  } else {
    Context__set_pixel_rgb565(this, point, color);
  }
}

void Context_draw_hline(Context* this, Point* point, int32_t width, uint16_t color) {
  Rect rect = {0};
  (rect.x = point->x);
  (rect.y = point->y);
  (rect.width = width);
  (rect.height = 1);
  Context_fill_rect(this, (&rect), color);
}

void Context_draw_vline(Context* this, Point* point, int32_t height, uint16_t color) {
  Rect rect = {0};
  (rect.x = point->x);
  (rect.y = point->y);
  (rect.width = 1);
  (rect.height = height);
  Context_fill_rect(this, (&rect), color);
}

void Context_draw_rect(Context* this, Rect* rect, uint16_t color) {
  Point point = {0};
  (point.x = rect->x);
  (point.y = rect->y);
  Context_draw_hline(this, (&point), rect->width, color);
  (point.y = ((rect->y + rect->height) - 1));
  Context_draw_hline(this, (&point), rect->width, color);
  (point.y = (rect->y + 1));
  Context_draw_vline(this, (&point), (rect->height - 2), color);
  (point.x = ((rect->x + rect->width) - 1));
  Context_draw_vline(this, (&point), (rect->height - 2), color);
}

void Context_fill_rect(Context* this, Rect* rect, uint16_t color) {
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
        Context__set_pixel_mono(this, (&point), color);
      } else {
        Context__set_pixel_rgb565(this, (&point), color);
      }
    }
  }
}

void Context_draw_round_rect(Context* this, Rect* rect, int32_t radius, uint16_t color) {
  if ((!Rect_intersect((&this->viewpoint), rect))) {
    return;
  }
  int32_t r = radius;
  Point point = {0};
  (point.x = (rect->x + r));
  (point.y = rect->y);
  Context_draw_hline(this, (&point), (rect->width - (2 * r)), color);
  (point.y = ((rect->y + rect->height) - 1));
  Context_draw_hline(this, (&point), (rect->width - (2 * r)), color);
  (point.x = rect->x);
  (point.y = (rect->y + r));
  Context_draw_vline(this, (&point), (rect->height - (2 * r)), color);
  (point.x = ((rect->x + rect->width) - 1));
  Context_draw_vline(this, (&point), (rect->height - (2 * r)), color);
  int32_t px = 0;
  int32_t py = r;
  int32_t d = (1 - r);
  while ((px <= py)) {
    (point.x = ((((rect->x + rect->width) - 1) - r) + py));
    (point.y = ((rect->y + r) - px));
    Context_draw_pixel(this, (&point), color);
    (point.x = ((rect->x + r) - py));
    (point.y = ((rect->y + r) - px));
    Context_draw_pixel(this, (&point), color);
    (point.x = ((((rect->x + rect->width) - 1) - r) + py));
    (point.y = ((((rect->y + rect->height) - 1) - r) + px));
    Context_draw_pixel(this, (&point), color);
    (point.x = ((rect->x + r) - py));
    (point.y = ((((rect->y + rect->height) - 1) - r) + px));
    Context_draw_pixel(this, (&point), color);
    (point.x = ((((rect->x + rect->width) - 1) - r) + px));
    (point.y = ((rect->y + r) - py));
    Context_draw_pixel(this, (&point), color);
    (point.x = ((rect->x + r) - px));
    (point.y = ((rect->y + r) - py));
    Context_draw_pixel(this, (&point), color);
    (point.x = ((((rect->x + rect->width) - 1) - r) + px));
    (point.y = ((((rect->y + rect->height) - 1) - r) + py));
    Context_draw_pixel(this, (&point), color);
    (point.x = ((rect->x + r) - px));
    (point.y = ((((rect->y + rect->height) - 1) - r) + py));
    Context_draw_pixel(this, (&point), color);
    if ((d < 0)) {
      (d += ((2 * px) + 3));
    } else {
      (d += ((2 * (px - py)) + 5));
      (py -= 1);
    }
    (px += 1);
  }
}

void Context_fill_round_rect(Context* this, Rect* rect, int32_t radius, uint16_t color) {
  if ((!Rect_intersect((&this->viewpoint), rect))) {
    return;
  }
  int32_t r = radius;
  Rect center = {0};
  (center.x = (rect->x + r));
  (center.y = rect->y);
  (center.width = (rect->width - (2 * r)));
  (center.height = rect->height);
  Context_fill_rect(this, (&center), color);
  int32_t px = 0;
  int32_t py = r;
  int32_t d = (1 - r);
  Point point = {0};
  while ((px <= py)) {
    (point.x = ((rect->x + r) - py));
    (point.y = ((rect->y + r) - px));
    Context_draw_hline(this, (&point), ((py * 2) - 1), color);
    (point.y = ((((rect->y + rect->height) - r) + px) - 1));
    Context_draw_hline(this, (&point), ((py * 2) - 1), color);
    (point.x = ((rect->x + r) - px));
    (point.y = ((rect->y + r) - py));
    Context_draw_hline(this, (&point), ((px * 2) - 1), color);
    (point.y = ((((rect->y + rect->height) - r) + py) - 1));
    Context_draw_hline(this, (&point), ((px * 2) - 1), color);
    if ((d < 0)) {
      (d += ((2 * px) + 3));
    } else {
      (d += ((2 * (px - py)) + 5));
      (py -= 1);
    }
    (px += 1);
  }
}

void Context_draw_bitmap(Context* this, Rect* rect, __Slice_uint8_t data, IndexFormat index_format, __Slice_uint16_t palette) {
  Rect clipped = {0};
  Point zero = {0};
  (zero.x = 0);
  (zero.y = 0);
  if ((!Rect_clip(rect, (&clipped), (&this->viewpoint), (&zero)))) {
    return;
  }
  if ((index_format == IndexFormat_Index1)) {
    Context__render_bitmap_index1(this, rect, (&clipped), data, palette);
  }
  if ((index_format == IndexFormat_Index2)) {
    Context__render_bitmap_index2(this, rect, (&clipped), data, palette);
  }
  if ((index_format == IndexFormat_Index4)) {
    Context__render_bitmap_index4(this, rect, (&clipped), data, palette);
  }
  if ((index_format == IndexFormat_Index8)) {
    Context__render_bitmap_index8(this, rect, (&clipped), data, palette);
  }
}

static void Context__render_bitmap_index1(Context* this, Rect* origin, Rect* clipped, __Slice_uint8_t data, __Slice_uint16_t palette) {
  int32_t row_bytes = ((origin->width + 7) / 8);
  Point point = {0};
  for (int32_t sy = clipped->y; sy < (clipped->y + clipped->height); sy++) {
    int32_t ly = (sy - origin->y);
    (point.y = sy);
    for (int32_t sx = clipped->x; sx < (clipped->x + clipped->width); sx++) {
      int32_t lx = (sx - origin->x);
      int32_t index = ((ly * row_bytes) + (lx / 8));
      int32_t p = 0;
      if (((data.ptr[index] & ((uint8_t)((0x80 >> (lx & 7))))) != 0)) {
        (p = 1);
      }
      uint16_t color = palette.ptr[p];
      if ((color != palette__TRANSPARENT)) {
        (point.x = sx);
        Context_draw_pixel(this, (&point), color);
      }
    }
  }
}

static void Context__render_bitmap_index2(Context* this, Rect* origin, Rect* clipped, __Slice_uint8_t data, __Slice_uint16_t palette) {
  int32_t row_bytes = ((origin->width + 3) / 4);
  Point point = {0};
  for (int32_t sy = clipped->y; sy < (clipped->y + clipped->height); sy++) {
    int32_t ly = (sy - origin->y);
    (point.y = sy);
    for (int32_t sx = clipped->x; sx < (clipped->x + clipped->width); sx++) {
      int32_t lx = (sx - origin->x);
      int32_t index = ((ly * row_bytes) + (lx / 4));
      int32_t shift = ((3 - (lx & 3)) * 2);
      int32_t p = ((((int32_t)(data.ptr[index])) >> shift) & 0x03);
      uint16_t color = palette.ptr[p];
      if ((color != palette__TRANSPARENT)) {
        (point.x = sx);
        Context_draw_pixel(this, (&point), color);
      }
    }
  }
}

static void Context__render_bitmap_index4(Context* this, Rect* origin, Rect* clipped, __Slice_uint8_t data, __Slice_uint16_t palette) {
  int32_t row_bytes = ((origin->width + 1) / 2);
  Point point = {0};
  for (int32_t sy = clipped->y; sy < (clipped->y + clipped->height); sy++) {
    int32_t ly = (sy - origin->y);
    (point.y = sy);
    for (int32_t sx = clipped->x; sx < (clipped->x + clipped->width); sx++) {
      int32_t lx = (sx - origin->x);
      int32_t index = ((ly * row_bytes) + (lx / 2));
      int32_t p = (((int32_t)(data.ptr[index])) & 0x0F);
      if (((lx & 1) == 0)) {
        (p = ((((int32_t)(data.ptr[index])) >> 4) & 0x0F));
      }
      uint16_t color = palette.ptr[p];
      if ((color != palette__TRANSPARENT)) {
        (point.x = sx);
        Context_draw_pixel(this, (&point), color);
      }
    }
  }
}

static void Context__render_bitmap_index8(Context* this, Rect* origin, Rect* clipped, __Slice_uint8_t data, __Slice_uint16_t palette) {
  Point point = {0};
  for (int32_t sy = clipped->y; sy < (clipped->y + clipped->height); sy++) {
    int32_t ly = (sy - origin->y);
    (point.y = sy);
    for (int32_t sx = clipped->x; sx < (clipped->x + clipped->width); sx++) {
      int32_t lx = (sx - origin->x);
      uint16_t color = palette.ptr[data.ptr[((ly * origin->width) + lx)]];
      if ((color != palette__TRANSPARENT)) {
        (point.x = sx);
        Context_draw_pixel(this, (&point), color);
      }
    }
  }
}

static inline void Context__set_pixel_mono(Context* this, Point* point, uint16_t color) {
  int32_t index = ((point->y * ((this->viewpoint.width + 7) / 8)) + (point->x / 8));
  if ((color == 0)) {
    (this->buffer.ptr[index] = (this->buffer.ptr[index] & ((uint8_t)((~(0x80 >> (point->x & 7)))))));
  } else {
    (this->buffer.ptr[index] = (this->buffer.ptr[index] | ((uint8_t)((0x80 >> (point->x & 7))))));
  }
}

static inline void Context__set_pixel_rgb565(Context* this, Point* point, uint16_t color) {
  int32_t index = (((point->y * this->viewpoint.width) + point->x) * 2);
  (this->buffer.ptr[index] = ((uint8_t)((color >> 8))));
  (this->buffer.ptr[(index + 1)] = ((uint8_t)(color)));
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

void Graphics_init(Graphics* this, Driver* driver, PixelFormat pixel_format, uint16_t background, Rotation rotation, bool dirty_render) {
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
  Rect aligned = (Rect){.x = aligned_x, .y = rect->y, .width = aligned_width, .height = rect->height};
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
  Point offset = (Point){.x = 0, .y = 0};
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

static inline Bitmap* Allocator_allocate_Bitmap(Allocator* this) {
  uint64_t size = sizeof(Bitmap);
  if (((this->_cursor + size) > this->_memory.size)) {
    return NULL;
  }
  Bitmap* ptr = ((Bitmap*)((&this->_memory.ptr[this->_cursor])));
  (this->_cursor = (((this->_cursor + size) + 3) & (~((int32_t)(3)))));
  return ptr;
}

static inline Text* Allocator_allocate_Text(Allocator* this) {
  uint64_t size = sizeof(Text);
  if (((this->_cursor + size) > this->_memory.size)) {
    return NULL;
  }
  Text* ptr = ((Text*)((&this->_memory.ptr[this->_cursor])));
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


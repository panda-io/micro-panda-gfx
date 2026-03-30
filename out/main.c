#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef void (*__Fn_void_uint8_t)(uint8_t);

typedef struct { uint8_t* ptr; size_t size; } __Slice_uint8_t;

#include <stdio.h>

void main__main(void);
static void console___write_byte_default(uint8_t b);
void console__init(__Fn_void_uint8_t write_byte);
static inline void console__write_byte(uint8_t b);
void console__println(void);
void console__print_str(__Slice_uint8_t s);
void console__print_bool(bool v);
void console__print_u64(uint64_t v);
void console__print_u32(uint32_t v);
void console__print_u16(uint16_t v);
void console__print_u8(uint8_t v);
void console__print_i64(int64_t v);
void console__print_i32(int32_t v);
void console__print_i16(int16_t v);
void console__print_i8(int8_t v);
void console__print_float(float v);
void console__print_fixed(int32_t v);

static __Fn_void_uint8_t console___write_byte = console___write_byte_default;

static int32_t __mp_argc = 0;
static char** __mp_argv = NULL;

void main__main(void) {
  console__print_str((__Slice_uint8_t){(uint8_t*)"Hello, world!\n", sizeof("Hello, world!\n") - 1});
  return;
}

static void console___write_byte_default(uint8_t b) {
  putchar(b);
}

void console__init(__Fn_void_uint8_t write_byte) {
  (console___write_byte = write_byte);
}

static inline void console__write_byte(uint8_t b) {
  console___write_byte(b);
}

void console__println(void) {
  console__write_byte(10);
}

void console__print_str(__Slice_uint8_t s) {
  uint32_t i = 0;
  while ((i < s.size)) {
    console__write_byte(s.ptr[i]);
    (i += 1);
  }
}

void console__print_bool(bool v) {
  if (v) {
    console__write_byte('t');
    console__write_byte('r');
    console__write_byte('u');
    console__write_byte('e');
  } else {
    console__write_byte('f');
    console__write_byte('a');
    console__write_byte('l');
    console__write_byte('s');
    console__write_byte('e');
  }
}

void console__print_u64(uint64_t v) {
  uint8_t buf[20];
  int32_t i = 19;
  if ((v == 0)) {
    console__write_byte('0');
    return;
  }
  while ((v > 0)) {
    (buf[i] = ((uint8_t)(((v % 10) + 48))));
    (v = (v / 10));
    (i -= 1);
  }
  int32_t j = (i + 1);
  while ((j < 20)) {
    console__write_byte(buf[j]);
    (j += 1);
  }
}

void console__print_u32(uint32_t v) {
  console__print_u64(((uint64_t)(v)));
}

void console__print_u16(uint16_t v) {
  console__print_u64(((uint64_t)(v)));
}

void console__print_u8(uint8_t v) {
  console__print_u64(((uint64_t)(v)));
}

void console__print_i64(int64_t v) {
  if ((v < 0)) {
    console__write_byte('-');
    console__print_u64(((uint64_t)((((int64_t)(0)) - v))));
  } else {
    console__print_u64(((uint64_t)(v)));
  }
}

void console__print_i32(int32_t v) {
  console__print_i64(((int64_t)(v)));
}

void console__print_i16(int16_t v) {
  console__print_i64(((int64_t)(v)));
}

void console__print_i8(int8_t v) {
  console__print_i64(((int64_t)(v)));
}

void console__print_float(float v) {
  float abs = v;
  if ((v < 0.0f)) {
    console__write_byte('-');
    (abs = (0.0f - v));
  }
  int32_t int_part = ((int32_t)(abs));
  console__print_i32(int_part);
  console__write_byte('.');
  float frac = (abs - ((float)(int_part)));
  uint32_t i = 0;
  while ((i < 4)) {
    (frac = (frac * 10.0f));
    int32_t digit = ((int32_t)(frac));
    console__write_byte(((uint8_t)((digit + 48))));
    (frac = (frac - ((float)(digit))));
    (i += 1);
  }
}

void console__print_fixed(int32_t v) {
  uint32_t abs = 0;
  if ((v < 0)) {
    console__write_byte('-');
    (abs = ((uint32_t)((0 - v))));
  } else {
    (abs = ((uint32_t)(v)));
  }
  console__print_u32((abs >> 16));
  console__write_byte('.');
  uint32_t frac = (abs & 0xFFFF);
  uint32_t i = 0;
  while ((i < 4)) {
    (frac *= 10);
    console__write_byte(((uint8_t)(((frac >> 16) + 48))));
    (frac = (frac & 0xFFFF));
    (i += 1);
  }
}

int main(int argc, char** argv) { __mp_argc = argc; __mp_argv = argv; main__main(); return 0; }


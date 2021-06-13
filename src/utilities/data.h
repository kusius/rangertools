#pragma once

struct Vec4 {
  float x, y, z, w;
  Vec4() { x = y = z = w = 0.0f; }
  Vec4(float _x, float _y, float _z, float _w) {
    x = _x;
    y = _y;
    z = _z;
    w = _w;
  }
};
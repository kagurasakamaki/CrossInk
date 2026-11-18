#include "OceanTheme.h"

#include <GfxRenderer.h>

#include <cmath>

namespace {
constexpr float kPi = 3.14159265f;

// Sine wave drawn as a thick polyline. y is the centre line.
void drawWave(const GfxRenderer& r, int x, int y, int width, int amp, int period, int thickness) {
  int px = x;
  int py = y;
  for (int dx = 2; dx <= width; dx += 2) {
    const int cx = x + dx;
    const int cy = y - static_cast<int>(std::lround(amp * std::sin(2.0f * kPi * dx / period)));
    r.drawLine(px, py, cx, cy, thickness, true);
    px = cx;
    py = cy;
  }
}

void drawMoon(const GfxRenderer& r, int cx, int cy, int radius) {
  r.fillRoundedRect(cx - radius, cy - radius, radius * 2, radius * 2, radius, Color::Black);
  r.fillRoundedRect(cx - radius + radius / 2, cy - radius - radius / 4, radius * 2, radius * 2, radius, Color::White);
}

void drawFish(const GfxRenderer& r, int x, int y, int s) {
  const int body_x[] = {x, x + 2 * s, x + 4 * s, x + 2 * s};
  const int body_y[] = {y, y - s, y, y + s};
  r.fillPolygon(body_x, body_y, 4, true);
  const int tail_x[] = {x + 4 * s, x + 6 * s, x + 6 * s};
  const int tail_y[] = {y, y - s, y + s};
  r.fillPolygon(tail_x, tail_y, 3, true);
  r.drawPixel(x + s / 2 + 1, y - 1, false);  // eye
}

void drawBoat(const GfxRenderer& r, int x, int y) {
  r.drawLine(x, y - 26, x, y, 2, true);  // mast
  const int sail_x[] = {x + 2, x + 18, x + 2};
  const int sail_y[] = {y - 26, y - 4, y - 4};
  r.fillPolygon(sail_x, sail_y, 3, true);
  const int jib_x[] = {x - 2, x - 12, x - 2};
  const int jib_y[] = {y - 20, y - 4, y - 4};
  r.fillPolygon(jib_x, jib_y, 3, true);
  const int hull_x[] = {x - 16, x + 20, x + 14, x - 10};
  const int hull_y[] = {y, y, y + 7, y + 7};
  r.fillPolygon(hull_x, hull_y, 4, true);
}

void drawBubbles(const GfxRenderer& r, int x, int y) {
  r.drawRoundedRect(x, y, 8, 8, 1, 4, true);
  r.drawRoundedRect(x + 12, y - 10, 5, 5, 1, 2, true);
  r.drawRoundedRect(x + 4, y - 20, 4, 4, 1, 2, true);
}
}  // namespace

void OceanTheme::drawHeader(const GfxRenderer& renderer, Rect rect, const char* title, const char* subtitle,
                            bool readerContext, bool showStatus) const {
  LyraTheme::drawHeader(renderer, rect, title, subtitle, readerContext, showStatus);
  if (readerContext) return;

  const int left = rect.x + 12;
  const int right = rect.x + rect.width - 12;
  const int seaY = rect.y + 38;  // horizon line
  drawMoon(renderer, rect.x + rect.width / 2 + 24, rect.y + 16, 9);
  drawBoat(renderer, left + 36, seaY - 8);
  drawWave(renderer, left, seaY, right - left, 3, 44, 2);
  drawWave(renderer, left + 11, seaY + 9, right - left - 11, 3, 44, 1);
  drawFish(renderer, right - 70, seaY + 6, 3);
  drawBubbles(renderer, right - 90, seaY + 14);
}

void OceanTheme::drawButtonHints(GfxRenderer& renderer, const char* btn1, const char* btn2, const char* btn3,
                                 const char* btn4, bool allowInvertedText) const {
  LyraTheme::drawButtonHints(renderer, btn1, btn2, btn3, btn4, allowInvertedText);
  // Thin wave ruling above the hint bar, like a waterline.
  const int pageH = renderer.getScreenHeight();
  const int y = pageH - OceanMetrics::values.buttonHintsHeight - 4;
  drawWave(renderer, 0, y, renderer.getScreenWidth(), 2, 44, 1);
}

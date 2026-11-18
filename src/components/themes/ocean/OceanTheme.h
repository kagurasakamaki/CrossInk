#pragma once

#include "components/themes/lyra/LyraTheme.h"

// Ocean theme: Lyra layout + a sea scene in every header (moon, sailboat, layered waves, fish).
// All decoration uses only 1-bit/grey primitives so it stays crisp on the X3/X4 e-ink panels.
namespace OceanMetrics {
constexpr ThemeMetrics makeValues() {
  ThemeMetrics v = LyraMetrics::values;
  v.headerHeight = 96;      // extra room above the title for the sea scene
  v.listRowRadius = 10;     // softer, shell-like selection
  v.progressBarHeight = 14;
  return v;
}
constexpr ThemeMetrics values = makeValues();
}  // namespace OceanMetrics

class OceanTheme : public LyraTheme {
 public:
  void drawHeader(const GfxRenderer& renderer, Rect rect, const char* title, const char* subtitle = nullptr,
                  bool readerContext = false, bool showStatus = true) const override;
  void drawButtonHints(GfxRenderer& renderer, const char* btn1, const char* btn2, const char* btn3, const char* btn4,
                       bool allowInvertedText = false) const override;
};

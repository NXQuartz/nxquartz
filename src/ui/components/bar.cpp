#include "ui/components/bar.hpp"

namespace ui::components {
Bar::Bar(double progress, NVGcolor color) :
    progress(progress), color(color) {
    this->setHeight(20);
}

void Bar::layout(NVGcontext* vg, brls::Style* style, brls::FontStash* stash) { }

void Bar::draw(NVGcontext* vg, int x, int y, unsigned width, unsigned height,
    brls::Style* style, brls::FrameContext* ctx) {
    NVGcolor color = a(this->color);
    if (color.a == 0.0f)
        return;

    // Outer stroke
    nvgStrokeColor(vg, color);
    nvgStrokeWidth(vg, 3);
    nvgBeginPath(vg);
    nvgRoundedRect(vg, x, y, width, height, 1);
    nvgStroke(vg);

    // Inner rectangle bar
    nvgFillColor(vg, color);
    nvgBeginPath(vg);
    nvgRoundedRect(vg, x + 4, y + 4, (width - 8) * progress, height - 8, 1);
    nvgFill(vg);
}

void Bar::setColor(NVGcolor color) { this->color = color; }

void Bar::setProgress(double progress) { this->progress = progress; }
} // namespace ui::components
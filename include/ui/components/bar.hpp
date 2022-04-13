#pragma once

#include <borealis.hpp>

namespace ui::components {
    class Bar : public brls::View {
    protected:
        NVGcolor color;
        double progress = 0;
        void layout(NVGcontext* vg, brls::Style* style, brls::FontStash* stash) override;
    public:
        Bar(double progress, NVGcolor color);
        void setColor(NVGcolor color);
        void setProgress(double progress);
        void draw(NVGcontext* vg, int x, int y, unsigned width, unsigned height, brls::Style* style, brls::FrameContext* ctx) override;
    };
}
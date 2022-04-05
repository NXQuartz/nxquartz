#pragma once

#include <switch.h>
#include <pu/Plutonium>

namespace UI::Layout {
    class BaseLayout : public pu::ui::Layout {
    protected:
        pu::ui::Application* appRef;
    public:
        BaseLayout(pu::ui::Application* appRef) 
            : Layout::Layout(), appRef(appRef)
        {
            this->SetOnInput(std::bind(&BaseLayout::OnInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        }

        virtual void OnInput(const u64 down, const u64 up, const u64 held) = 0;
    };
}
#include <ui/MainApplication.hpp>

// Main entrypoint
int main() {
    // First create our renderer, where one can customize SDL or other stuff's initialization.
    auto renderer_opts = pu::ui::render::RendererInitOptions(SDL_INIT_EVERYTHING, pu::ui::render::RendererHardwareFlags);
    renderer_opts.UseImage(pu::ui::render::IMGAllFlags);
    renderer_opts.UseAudio(pu::ui::render::MixerAllFlags);
    renderer_opts.UseTTF();
    auto renderer = pu::ui::render::Renderer::New(renderer_opts);

    // Create our main application from the renderer
    auto main = UI::MainApplication::New(renderer);

    // Prepare out application. This MUST be called or Show() will exit and nothing will be rendered.
    main->Prepare();

    // Show -> start rendering in an "infinite" loop
    // If wou would like to show with a "fade in" from black-screen to the UI, use instead ->ShowWithFadeIn();
    main->Show();

    // Exit homebrew (Plutonium will handle all disposing of UI and renderer/application, don't worry!

    return 0;
}
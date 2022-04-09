# NXQuartz
NXQuartz is a cloud save backup application for the Nintendo Switch, created with [libnx](https://github.com/switchbrew/libnx)

## Development Guide
### Building the app
Run `make` inside this folder. Put the `.nro` file you just created on your SD card and launch it.

### Debugging with Ryujinx
For running in development run `make run RYUJINX=<Ryujinx executable path>` to run in an emulator. You may also use `nxlink` manually if you want to run on your switch. Please make sure you use the latest version of Ryujinx. Yuzu and older Ryujinx builds have graphical and memory issues while running.

### Development Environment
Make sure you have [devkitPro](https://github.com/devkitPro/installer/releases) installed on your computer with the `DEVKITPRO` and `DEVKITPRO_PATH` set to the install location. `DEVKITPRO_PATH` is required from `DEVKITPRO` because the devkitPro toolchain on windows uses msys paths. It is recommended to use [Pacman](https://github.com/devkitPro/pacman) for installing the required tools on unix based platforms.

We use VSCode as our development environment with classic Makefiles as our build tool. Because Makefiles don't have much intellisense, our include paths and autocompletion settings are within `.vscode/c_cpp_properties.json`. When adding dependencies you must make sure that you add required include paths here.

**Recommended Extensions**
- [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
- [Better C Syntax](https://marketplace.visualstudio.com/items?itemName=jeff-hykin.better-c-syntax)
- [Syntax Highlight Theme](https://marketplace.visualstudio.com/items?itemName=peaceshi.syntax-highlight) (This will automatically apply in the project when installed)
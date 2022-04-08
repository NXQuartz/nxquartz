# NXQuartz
NXQuartz is a cloud save backup application for the Nintendo Switch, created with [libnx](https://github.com/switchbrew/libnx)

## Development Guide
Make sure you have [DevKitA64](https://devkitpro.org/) installed. Installations can be found on their website.
For Unix-like platforms, it is recommended to use [Pacman](https://github.com/devkitPro/pacman) for installing the
required tools. In order to use the development environment in VSCode you must set the `DEVKITPRO_PATH` environment variable. This is seperate from `DEVKITPRO` because the devkitPro toolchain on windows uses msys paths.

### Building the app
Run `make` inside this folder. Put the `.nro` file you just created on your SD card and launch it.

### Running in development
For running in development run `make run RYUJINX=<Ryujinx executable path>` to run in an emulator. You may also use `nxlink` manually if you want to run on your switch. Please make sure you use the latest version of Ryujinx. Yuzu and older Ryujinx builds have graphical and memory issues while running.
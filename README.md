# NXQuartz
NXQuartz is a cloud save backup application for the Nintendo Switch, created with [libnx](https://github.com/switchbrew/libnx) and [Plutonium](https://github.com/XorTroll/Plutonium)

## Development Guide
Make sure you have [DevKitA64](https://devkitpro.org/) installed. Installations can be found on their website.
For Unix-like platforms, it is recommended to use [Pacman](https://github.com/devkitPro/pacman) for installing the
required tools. In order to use the development environment in VSCode you must set the `DEVKITPRO_PATH` environment variable. This is seperate from `DEVKITPRO` because the devkitPro toolchain on windows uses msys paths.

### Running the app
Run `make` inside this folder. Put the `.nro` file you just created on your SD card and launch it.
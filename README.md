# Toof

Toof is a 2D game engine with its focus being on ease of use.

Note that toof is still in its early development phases and therefore not stable. Documentation is also lacking.

## Building

- Install [Meson](https://mesonbuild.com/)
- Set the working directory to Toof
- Configure the build directory with `meson setup build`
- Start compilation with `meson compile -C build`

## Dependencies
 - [SDL2](https://github.com/libsdl-org/SDL)
 - [SDL_image](https://github.com/libsdl-org/SDL_image)
 - [cereal](https://github.com/USCiLab/cereal)

Optional:
 - [Box2D](https://github.com/erincatto/box2d) (required for Physics)

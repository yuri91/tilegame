# Tilegame

An experimental tile engine with SFML

## Features

* display arbitrary layered tilemaps
* support for 2-frame animations
* zoom with mouse wheel
* camera move with left mouse button
* resize to increase area

## Requirements

* CMake
* SFML 2.*
* [tmxparser](https://github.com/andrewrk/tmxparser)
* [Dawnlike tileset] (opengameart.org/content/dawnlike-16x16-universal-rogue-like-tileset-v181)
  extract it in the `tiletest/assets` folder

## Build

```
mkdir build
cd build
cmake ..
make
```
## Run test

```
./run.sh
```

## Author

Yuri Iozzelli (<y.iozzelli@gmail.com>)

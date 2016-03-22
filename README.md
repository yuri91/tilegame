# Tiletest

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

## Build

```
mkdir build
cd build
cmake ..
make
./tiletest ../assets/Mine.tmx
```

## Author

Yuri Iozzelli (<y.iozzelli@gmail.com>)

# SealEngine
SealEngine is a simple game engine and framework that is made using C++ and SDL (and other 3rd party libraries).

## Building
To build the engine simply run:
```bash
make -C engine
```
*This will produce a "libsealengine.so" file that can be used together with a game executable.*

**Atm you cant install the `libsealengine` using make nor a library. So you have to manually update ur path when running the game (see: test.sh). And you also have to add the library to the include path**

## Running
You can run a test game by running the following command:
```bash
./test.sh
```
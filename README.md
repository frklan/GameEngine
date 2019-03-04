# GameEngine

An attemnt to make a game engine. Mostly for fun and to learn how a game engine works. Will most probably crash and destroy your house, should NOT be used in production code ;)

## Compiling

Currently it will only work on MacOS due to using some specific functions to get the exact path to the executable, anyhow you'll need the following to compile

- A C++17 compatible clang++ compiler
- SFML / OpenGL
- ImGui / ImGui-SFML
- boost::filesystem

Run the following to clone, compile and run.

````bash
$ git clone git@github.com:frklan/GameEngine.git --recurse-submodules 
$ cd GameEngine
$ make
$ ./ge
````

Alternativley cmake can be used, with the added bonus of not litter build files all over the place:

````bash
$ git clone git@github.com:frklan/GameEngine.git --recurse-submodules 
$ cd GameEngine
$ mkdir build && cd build
$ cmake ..
$ make
$ ./ge
````

You also need to manually copy (or symlink) src/Resources to the build directory.

Use ````$ cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..```` to compile with debug symbols and verbose output.


## Contributing

Contributions are always welcome!

When contributing to this repository, please first discuss the change you wish to make via the issue tracker, email, or any other method with the owner of this repository before making a change.

Please note that we have a code of conduct, you are required to follow it in all your interactions with the project.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/frklan/GameEngine/tags).

## Authors

* **Fredrik Andersson** - *Initial work* - [frklan](https://github.com/frklan)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

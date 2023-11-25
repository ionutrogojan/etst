# Webbox2

A complete rewrite of all previous versions. Quickly launch a browser with a list of links.

---

### Available on Linux, MacOS and Windows

This is a free and open source application. In order to get it on your system follow the build instructions

## Build Instructions

The following Build Instructions are for `Linux`, the `MacOS` build should be identical and if you're a `Windows` user, may god help you to set up a C compiler.

```C
!IMPORTANT! Make sure you have GCC installed on your system
// feel free to modify the 'makefile' and use a different compiler

// the default build is a static build. It will compile all the libraries and code into an executable with no dependencies
// open the folder through a terminal, locate the 'makefile' and run the following command:
make

// to make a shared executable which will not compile all the libraries and will be dependent on your system's libC, run the following command:
make shared
```
P.S. I just realized I hardcoded the config path and it will probably work only on Linux, so change it to your config path for the moment until I get to that. Sorry for the inconvenience

Once the program is built there's one more step.
Create a folder in your `.config/` folder called webbox and place the `test.cfg` file in there. Your final result should be something like this:
```
../home/<username>/.config/webbox/test.cfg
```
Webbox will look for a `default.cfg` so rename `test.cfg` to that and modify the links to your desired ones.
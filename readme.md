# Webbox2

<p align="center"><img src="https://raw.githubusercontent.com/ionutrogojan/webbox2/main/resources/webbox2.svg" width="480px"/></p>

A complete rewrite of all previous versions. Quickly launch a browser with a list of links.

---

### Available on Linux, MacOS and Windows

This is a free and open source application. In order to get it on your system follow the build instructions

## Prerequisites
- `GCC` or a C compiler of your choice
- `make` to run the automatic build setup

## Build Instructions

The following Build Instructions are for `Linux`, the `MacOS` build should be identical and if you're a `Windows` user, may god help you to set up a C compiler.

```C
!IMPORTANT! Make sure you have a C compiler installed on your system
// feel free to modify the 'makefile' and use a different compiler

// the default build is a static build. It will compile all the libraries and code into an executable with no dependencies
// open the folder through a terminal, locate the 'makefile' and run the following command:
make

// to make a shared executable which will not compile all the libraries and will be dependent on your system's libC, run the following command:
make shared
```

Once the program is built there's one more step.

Create a directory in your `~/.config/` (LINUX) , `~/Library/Preferences/` (MACOS) or `~\AppData\Roaming\` (WINDOWS) directory called webbox and place the `example.cfg` file in there.

Copy the file, don't move it permanently in case you might need an example for later use.

Your final result should be something like this:
```C
/home/<username>/.config/webbox/example.cfg			// LINUX
/Users/<Username>/Library/Preferences/webbox/example.cfg	// MACOS
/C:\Users\YourUsername\AppData\Roaming\webbox\example.cfg	// WINDOWS
```
Webbox will look for a `default.cfg` so rename `example.cfg` to that and modify the links to your desired ones or create a new file and add your links there following the example file.

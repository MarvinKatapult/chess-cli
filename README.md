# chess-cli

Chess in a command line interface

# How to build

### Linux

Dependencies:
- gcc
- (Doxygen)

Just start the build.sh script. If you want to generate Doxygen documentation
start the script with the -D flag (Doxygen needs to be preinstalled on the system)

### Windows

Dependencies:
- cygwin64 (gcc)
- (Doxygen)

Just start the build.cmd script. If you want to generate Doxygen documentation
start the script with the -D flag (Doxygen needs to be preinstalled on the system)

# The Idea

Chess-cli is supposed to be a all around chess playing experience
straight in the terminal. Currently the following features are to be
implemented:

- Playing chess with notation on the side
- A Startmenu
- Api to give out available moves for position
- Support for Fenstring

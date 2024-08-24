set -xe
CFLAGS="-Wall -Wextra `pkg-config --cflags raylib`"
LIBS="`pkg-config --libs raylib`"
clang $CFLAGS -o player.exe main.c $LIBS

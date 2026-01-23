#!/bin/bash

WINDOWS=false
WIN_FLAGS=""

RUN=false

BUILD_PATH="bin/"

INPUT="src/*.c"
OUTPUT="a.out"
RAYLIB="$HOME/raylib"

mkdir -p "$BUILD_PATH"

# parse arguments
while [ $# -gt 0 ]; do
    case $1 in
        -noconsole)
            WIN_FLAGS="$WIN_FLAGS -mwindows"
            shift
            ;;
        -win32)
            WINDOWS=true
            shift
            ;;
        -run)
            RUN=true
            shift
            ;;
        -o)
            if [ -n "$2" ]; then
                OUTPUT="$2"
                shift 2
            else
                echo "Error: -o requires a filename"
                exit 1
            fi
            ;;
        -raylib)
            if [ -n "$2" ]; then
                RAYLIB="$2"
                shift 2
            else
                echo "Error: -raylib requires a path to raylib"
                exit 1
            fi
            ;;
        *)
            echo "Unknown option: $1"
            shift
            ;;
    esac
done

if [ "$WINDOWS" = true ]; then
    x86_64-w64-mingw32-gcc $INPUT \
        -I"$RAYLIB/src" \
        "$RAYLIB/build-mingw/raylib/libraylib.a" \
        -lopengl32 -lgdi32 -lwinmm $WIN_FLAGS \
        -o "$BUILD_PATH/$OUTPUT"
else
    gcc $INPUT \
        -I"$RAYLIB/src" \
        "$RAYLIB/src/libraylib.a" \
        -lGL -lm -lpthread -ldl -lrt -lX11 \
        -o "$BUILD_PATH/$OUTPUT"
fi

if [ "$RUN" = true ]; then
    RUNPATH="$BUILD_PATH/$OUTPUT"
    if [ "$WINDOWS" = true ]; then
        RUNPATH="$RUNPATH.exe"
    fi

    echo "attempting to run $RUNPATH"
    $RUNPATH
fi 
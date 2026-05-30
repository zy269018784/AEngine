apt install meson

meson setup --backend="ninja" --buildtype="release" "./build "."

ninja -C build
ninja -C build install

meson setup --backend="vs2022" --buildtype="release" "./build "."
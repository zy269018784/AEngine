apt install meson

meson setup --backend="ninja" --buildtype="release" "./build "."

ninja -C build
ninja -C build install
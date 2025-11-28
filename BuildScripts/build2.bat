cmake -S .. -B ../../AEngine_build -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_TYPE=Release -DUSE_QT6=true  -DCMAKE_PREFIX_PATH="C:/Qt/6.9.3/msvc2022_64/lib/cmake"
cmake --open   ../../AEngine_build
C:/Qt/6.7.3/msvc2022_64/bin/windeployqt.exe --qmldir ../../AEngine_build  ../../AEngine_build/Release/jiguan.exe




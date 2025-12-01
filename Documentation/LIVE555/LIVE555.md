config.linux-64bit add -std=c++20

./genMakefiles linux-64bit
make -j32
make install

if [ -e build/debug/cmake_install.cmake ]
then
    cmake --install build/debug
fi

if [ -e build/release/cmake_install.cmake ]
then
    cmake --install build/release
fi


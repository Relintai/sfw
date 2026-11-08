#ANDROID_HOME needs to be set
#export ANDROID_HOME=<path>

cd libs/SDL2-2.0.12-src

rm -Rf build
mkdir build

cd ..
cd ..

./libs/SDL2-2.0.12-src/build-scripts/androidbuild.sh net.tapp.sdl  ./main.cpp ./shader.cpp ./material.cpp ./mesh.cpp ./mesh_instance.cpp ./mesh_utils.cpp ./texture.cpp ./camera.cpp

cd libs/SDL2-2.0.12-src/build/net.tapp.sdl

./gradlew installDebug
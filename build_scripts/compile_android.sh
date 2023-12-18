#ANDROID_HOME be kell legyen állítva
#export ANDROID_HOME=<path>

cd libs/SDL2-2.0.12-src

rm -Rf build
mkdir build

cd ..
cd ..

./libs/SDL2-2.0.12-src/build-scripts/androidbuild.sh net.tapp.sdl  ./main.cpp ./shader.cpp ./material.cpp ./mesh.cpp ./mesh_instance.cpp ./mesh_utils.cpp \
        ./texture.cpp ./camera.cpp ./application.cpp ./scene.cpp ./game_scene.cpp ./object_2d.cpp ./tile_map.cpp ./sprite.cpp

cp *.h libs/SDL2-2.0.12-src/build/net.tapp.sdl/app/jni/src
cp -R glm libs/SDL2-2.0.12-src/build/net.tapp.sdl/app/jni/src

mkdir libs/SDL2-2.0.12-src/build/net.tapp.sdl/app/src/main/assets
cp *.bmp libs/SDL2-2.0.12-src/build/net.tapp.sdl/app/src/main/assets/

cd libs/SDL2-2.0.12-src/build/net.tapp.sdl

echo NDK_TOOLCHAIN_VERSION := 4.8 >> app/jni/Application.mk
echo APP_STL := c++_shared >> app/jni/Application.mk

#vagy
#./gradlew installDebug

#vagy
./gradlew assembleDebug
cd ../../../..
cp ./libs/SDL2-2.0.12-src/build/net.tapp.sdl/app/build/outputs/apk/debug/app-debug.apk ./bin/.

# manual install
#cd bin
#adb install app-debug.apk
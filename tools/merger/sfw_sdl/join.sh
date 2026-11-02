cd ..

mkdir -p out

mkdir -p out/sfw_sdl_full

cd ..
cd ..

python tools/merger/join.py --template tools/merger/sfw_sdl/sfw_sdl_full.h.inl --path . --output tools/merger/out/sfw_sdl_full/sfw_sdl.h
python tools/merger/join.py --template tools/merger/sfw_sdl/sfw_sdl_full.cpp.inl --path . --output tools/merger/out/sfw_sdl_full/sfw_sdl.cpp

echo "Running clang format!"

clang-format --Wno-error=unknown -i tools/merger/out/sfw_sdl_full/sfw_sdl.h
clang-format --Wno-error=unknown -i tools/merger/out/sfw_sdl_full/sfw_sdl.cpp

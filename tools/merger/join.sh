
mkdir -p out

mkdir -p out/core
mkdir -p out/full

cd ..
cd ..

python tools/merger/join.py --template tools/merger/sfw_core.h.inl --path . --output tools/merger/out/core/sfw.h
python tools/merger/join.py --template tools/merger/sfw_core.cpp.inl --path . --output tools/merger/out/core/sfw.cpp

python tools/merger/join.py --template tools/merger/sfw_full.h.inl --path . --output tools/merger/out/full/sfw.h
python tools/merger/join.py --template tools/merger/sfw_full.cpp.inl --path . --output tools/merger/out/full/sfw.cpp
python tools/merger/join.py --template tools/merger/sfw_3rd.x.inl --path . --output tools/merger/out/full/sfw_3rd.m

echo "Running clang format!"

clang-format --Wno-error=unknown -i tools/merger/out/core/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/core/sfw.cpp

clang-format --Wno-error=unknown -i tools/merger/out/full/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/full/sfw.cpp
#clang-format --Wno-error=unknown -i tools/merger/out/full/sfw_3rd.m

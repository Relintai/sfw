cd ..

mkdir -p out

mkdir -p out/sfwl_core
mkdir -p out/sfwl_full

cd ..
cd ..

python tools/merger/join.py --template tools/merger/sfwl/sfwl_core.h.inl --path . --output tools/merger/out/sfwl_core/sfwl.h
python tools/merger/join.py --template tools/merger/sfwl/sfwl_core.cpp.inl --path . --output tools/merger/out/sfwl_core/sfwl.cpp

python tools/merger/join.py --template tools/merger/sfwl/sfwl_full.h.inl --path . --output tools/merger/out/sfwl_full/sfwl.h
python tools/merger/join.py --template tools/merger/sfwl/sfwl_full.cpp.inl --path . --output tools/merger/out/sfwl_full/sfwl.cpp

echo "Running clang format!"

clang-format --Wno-error=unknown -i tools/merger/out/sfwl_core/sfwl.h
clang-format --Wno-error=unknown -i tools/merger/out/sfwl_core/sfwl.cpp

clang-format --Wno-error=unknown -i tools/merger/out/sfwl_full/sfwl.h
clang-format --Wno-error=unknown -i tools/merger/out/sfwl_full/sfwl.cpp

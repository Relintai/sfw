cd ..

mkdir -p out

mkdir -p out/sfwl_core
mkdir -p out/sfwl_full

cd ..
cd ..

#python tools/merger/join.py --template tools/merger/sfw_core.h.inl --path . --output tools/merger/out/core/sfw.h
#python tools/merger/join.py --template tools/merger/sfw_core.cpp.inl --path . --output tools/merger/out/core/sfw.cpp

python tools/merger/join.py --template tools/merger/sfwl/sfwl_full.h.inl --path . --output tools/merger/out/sfwl_full/sfwl.h
python tools/merger/join.py --template tools/merger/sfwl/sfwl_full.cpp.inl --path . --output tools/merger/out/sfwl_full/sfwl.cpp

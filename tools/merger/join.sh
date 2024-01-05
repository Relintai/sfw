
mkdir -p out

cd ..
cd ..

python tools/merger/join.py --template tools/merger/sfw.h.inl --path . --output tools/merger/out/sfw.h
python tools/merger/join.py --template tools/merger/sfw.cpp.inl --path . --output tools/merger/out/sfw.cpp
python tools/merger/join.py --template tools/merger/sfw.x.inl --path . --output tools/merger/out/sfw


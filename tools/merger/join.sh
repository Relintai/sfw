
mkdir -p out

cd ..
cd ..

python misc/merger/join.py --template misc/merger/sfw.h.inl --path . --output misc/merger/out/sfw.h
python misc/merger/join.py --template misc/merger/sfw.cpp.inl --path . --output misc/merger/out/sfw.cpp


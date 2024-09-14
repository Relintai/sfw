mkdir -p out

mkdir -p out/core
mkdir -p out/object
mkdir -p out/render_core
mkdir -p out/render_gui
mkdir -p out/render_immediate
mkdir -p out/render_objects
mkdir -p out/full

mkdir -p out/sfwl_core
mkdir -p out/sfwl_full

cd ..
cd ..


# SFW
python tools/merger/join.py --template tools/merger/sfw_core.h.inl --path . --output tools/merger/out/core/sfw.h
python tools/merger/join.py --template tools/merger/sfw_core.cpp.inl --path . --output tools/merger/out/core/sfw.cpp

python tools/merger/join.py --template tools/merger/sfw_object.h.inl --path . --output tools/merger/out/object/sfw.h
python tools/merger/join.py --template tools/merger/sfw_object.cpp.inl --path . --output tools/merger/out/object/sfw.cpp

python tools/merger/join.py --template tools/merger/sfw_render_core.h.inl --path . --output tools/merger/out/render_core/sfw.h
python tools/merger/join.py --template tools/merger/sfw_render_core.cpp.inl --path . --output tools/merger/out/render_core/sfw.cpp
python tools/merger/join.py --template tools/merger/sfw_3rd.x.inl --path . --output tools/merger/out/render_core/sfw_3rd.m

python tools/merger/join.py --template tools/merger/sfw_gui.h.inl --path . --output tools/merger/out/render_gui/sfw.h
python tools/merger/join.py --template tools/merger/sfw_gui.cpp.inl --path . --output tools/merger/out/render_gui/sfw.cpp
python tools/merger/join.py --template tools/merger/sfw_3rd.x.inl --path . --output tools/merger/out/render_gui/sfw_3rd.m

python tools/merger/join.py --template tools/merger/sfw_render_immediate.h.inl --path . --output tools/merger/out/render_immediate/sfw.h
python tools/merger/join.py --template tools/merger/sfw_render_immediate.cpp.inl --path . --output tools/merger/out/render_immediate/sfw.cpp
python tools/merger/join.py --template tools/merger/sfw_3rd.x.inl --path . --output tools/merger/out/render_immediate/sfw_3rd.m

python tools/merger/join.py --template tools/merger/sfw_render_objects.h.inl --path . --output tools/merger/out/render_objects/sfw.h
python tools/merger/join.py --template tools/merger/sfw_render_objects.cpp.inl --path . --output tools/merger/out/render_objects/sfw.cpp
python tools/merger/join.py --template tools/merger/sfw_3rd.x.inl --path . --output tools/merger/out/render_objects/sfw_3rd.m

python tools/merger/join.py --template tools/merger/sfw_full.h.inl --path . --output tools/merger/out/full/sfw.h
python tools/merger/join.py --template tools/merger/sfw_full.cpp.inl --path . --output tools/merger/out/full/sfw.cpp
python tools/merger/join.py --template tools/merger/sfw_3rd.x.inl --path . --output tools/merger/out/full/sfw_3rd.m

# SFWL
python tools/merger/join.py --template tools/merger/sfwl/sfwl_core.h.inl --path . --output tools/merger/out/sfwl_core/sfwl.h
python tools/merger/join.py --template tools/merger/sfwl/sfwl_core.cpp.inl --path . --output tools/merger/out/sfwl_core/sfwl.cpp

python tools/merger/join.py --template tools/merger/sfwl/sfwl_full.h.inl --path . --output tools/merger/out/sfwl_full/sfwl.h
python tools/merger/join.py --template tools/merger/sfwl/sfwl_full.cpp.inl --path . --output tools/merger/out/sfwl_full/sfwl.cpp


echo "Running clang format!"

# SFW
clang-format --Wno-error=unknown -i tools/merger/out/core/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/core/sfw.cpp

clang-format --Wno-error=unknown -i tools/merger/out/object/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/object/sfw.cpp

clang-format --Wno-error=unknown -i tools/merger/out/render_core/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/render_core/sfw.cpp
#clang-format --Wno-error=unknown -i tools/merger/out/render_core/sfw_3rd.m

clang-format --Wno-error=unknown -i tools/merger/out/render_gui/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/render_gui/sfw.cpp
#clang-format --Wno-error=unknown -i tools/merger/out/gui/sfw_3rd.m

clang-format --Wno-error=unknown -i tools/merger/out/render_immediate/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/render_immediate/sfw.cpp
#clang-format --Wno-error=unknown -i tools/merger/out/render_immediate/sfw_3rd.m

clang-format --Wno-error=unknown -i tools/merger/out/render_objects/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/render_objects/sfw.cpp
#clang-format --Wno-error=unknown -i tools/merger/out/render_objects/sfw_3rd.m

clang-format --Wno-error=unknown -i tools/merger/out/full/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/full/sfw.cpp
#clang-format --Wno-error=unknown -i tools/merger/out/full/sfw_3rd.m

#SFWL
clang-format --Wno-error=unknown -i tools/merger/out/sfwl_core/sfwl.h
clang-format --Wno-error=unknown -i tools/merger/out/sfwl_core/sfwl.cpp

clang-format --Wno-error=unknown -i tools/merger/out/sfwl_full/sfwl.h
clang-format --Wno-error=unknown -i tools/merger/out/sfwl_full/sfwl.cpp



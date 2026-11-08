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

mkdir -p out/sfw_sdl_full

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

python tools/merger/join.py --template tools/merger/sfw_full.h.inl --path . --output tools/merger/out/full/sfw.h
python tools/merger/join.py --template tools/merger/sfw_full.cpp.inl --path . --output tools/merger/out/full/sfw.cpp
python tools/merger/join.py --template tools/merger/sfw_3rd.x.inl --path . --output tools/merger/out/full/sfw_3rd.m

# SFWL
python tools/merger/join.py --template tools/merger/sfwl/sfwl_core.h.inl --path . --output tools/merger/out/sfwl_core/sfwl.h
python tools/merger/join.py --template tools/merger/sfwl/sfwl_core.cpp.inl --path . --output tools/merger/out/sfwl_core/sfwl.cpp

python tools/merger/join.py --template tools/merger/sfwl/sfwl_full.h.inl --path . --output tools/merger/out/sfwl_full/sfwl.h
python tools/merger/join.py --template tools/merger/sfwl/sfwl_full.cpp.inl --path . --output tools/merger/out/sfwl_full/sfwl.cpp

# SFW SDL
python tools/merger/join.py --template tools/merger/sfw_sdl/sfw_sdl_full.h.inl --path . --output tools/merger/out/sfw_sdl_full/sfw_sdl.h
#enable this if you disable clang formats
#python tools/merger/replace_placeholder.py --text "// INSERT GLAD HERE" --replace_with_file sfw_sdl/render_core/3rd_glad.h --path tools/merger/out/sfw_sdl_full/sfw_sdl.h
python tools/merger/join.py --template tools/merger/sfw_sdl/sfw_sdl_full.cpp.inl --path . --output tools/merger/out/sfw_sdl_full/sfw_sdl.cpp

# Hash Module
python tools/merger/join.py --template modules/hash/merger/sfw_hash.h.inl --path . --output tools/merger/out/modules/hash/sfw/sfw_hash.h --library_include sfw
python tools/merger/join.py --template modules/hash/merger/sfw_hash.cpp.inl --path . --output tools/merger/out/modules/hash/sfw/sfw_hash.cpp --library_include sfw
python tools/merger/join.py --template modules/hash/merger/sfw_hash.h.inl --path . --output tools/merger/out/modules/hash/sfwl/sfw_hash.h --library_include sfwl
python tools/merger/join.py --template modules/hash/merger/sfw_hash.cpp.inl --path . --output tools/merger/out/modules/hash/sfwl/sfw_hash.cpp --library_include sfwl

# Render Objects Module
python tools/merger/join.py --template modules/render_objects/merger/sfw_render_objects.h.inl --path . --output tools/merger/out/modules/render_objects/sfw_render_objects.h
python tools/merger/join.py --template modules/render_objects/merger/sfw_render_objects.cpp.inl --path . --output tools/merger/out/modules/render_objects/sfw_render_objects.cpp

# Audio Module
python tools/merger/join.py --template modules/audio/merger/sfw_audio.h.inl --path . --output tools/merger/out/modules/audio/sfw/sfw_audio.h --library_include sfw
python tools/merger/join.py --template modules/audio/merger/sfw_audio.cpp.inl --path . --output tools/merger/out/modules/audio/sfw/sfw_audio.cpp --library_include sfw
python tools/merger/join.py --template modules/audio/merger/sfw_audio.h.inl --path . --output tools/merger/out/modules/audio/sfwl/sfw_audio.h --library_include sfwl
python tools/merger/join.py --template modules/audio/merger/sfw_audio.cpp.inl --path . --output tools/merger/out/modules/audio/sfwl/sfw_audio.cpp --library_include sfwl

echo "Running clang format!"

# SFW
clang-format --Wno-error=unknown -i tools/merger/out/core/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/core/sfw.cpp

echo "SFW Core Done."

clang-format --Wno-error=unknown -i tools/merger/out/object/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/object/sfw.cpp

echo "SFW Object Done."

clang-format --Wno-error=unknown -i tools/merger/out/render_core/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/render_core/sfw.cpp
#clang-format --Wno-error=unknown -i tools/merger/out/render_core/sfw_3rd.m

echo "SFW Render Core Done."

clang-format --Wno-error=unknown -i tools/merger/out/render_gui/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/render_gui/sfw.cpp
#clang-format --Wno-error=unknown -i tools/merger/out/gui/sfw_3rd.m

echo "SFW GUI Done."

clang-format --Wno-error=unknown -i tools/merger/out/render_immediate/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/render_immediate/sfw.cpp
#clang-format --Wno-error=unknown -i tools/merger/out/render_immediate/sfw_3rd.m

echo "SFW Render Immediate Done."

clang-format --Wno-error=unknown -i tools/merger/out/full/sfw.h
clang-format --Wno-error=unknown -i tools/merger/out/full/sfw.cpp
#clang-format --Wno-error=unknown -i tools/merger/out/full/sfw_3rd.m

echo "SFW Full Done."

#SFWL
clang-format --Wno-error=unknown -i tools/merger/out/sfwl_core/sfwl.h
clang-format --Wno-error=unknown -i tools/merger/out/sfwl_core/sfwl.cpp

echo "SFWL Core Done."

clang-format --Wno-error=unknown -i tools/merger/out/sfwl_full/sfwl.h
clang-format --Wno-error=unknown -i tools/merger/out/sfwl_full/sfwl.cpp

echo "SFWL Full Done."

# SFW SDL
# NOt that having glad in this file will make current clang format eat all ram and exit, so ve add that in the next line
clang-format --Wno-error=unknown -i tools/merger/out/sfw_sdl_full/sfw_sdl.h
python tools/merger/replace_placeholder.py --text "// INSERT GLAD HERE" --replace_with_file sfw_sdl/render_core/3rd_glad.h --path tools/merger/out/sfw_sdl_full/sfw_sdl.h
clang-format --Wno-error=unknown -i tools/merger/out/sfw_sdl_full/sfw_sdl.cpp

echo "SFW SDL Full Done."

# Hash Module

clang-format --Wno-error=unknown -i tools/merger/out/modules/hash/sfw/sfw_hash.h
clang-format --Wno-error=unknown -i tools/merger/out/modules/hash/sfw/sfw_hash.cpp
clang-format --Wno-error=unknown -i tools/merger/out/modules/hash/sfwl/sfw_hash.h
clang-format --Wno-error=unknown -i tools/merger/out/modules/hash/sfwl/sfw_hash.cpp

echo "SFW Hash Module Done."

# Render Objects Module

clang-format --Wno-error=unknown -i tools/merger/out/modules/render_objects/sfw_render_objects.h
clang-format --Wno-error=unknown -i tools/merger/out/modules/render_objects/sfw_render_objects.cpp

echo "SFW Render Objects Module Done."

# Audio Module

clang-format --Wno-error=unknown -i tools/merger/out/modules/audio/sfw/sfw_audio.h
clang-format --Wno-error=unknown -i tools/merger/out/modules/audio/sfwl/sfw_audio.h
# Don't. Not needed, and it takes ridiculous amount of memory.
#clang-format --Wno-error=unknown -i tools/merger/out/modules/audio/sfw/sfw_audio.cpp
#clang-format --Wno-error=unknown -i tools/merger/out/modules/audio/sfwl/sfw_audio.cpp

echo "SFW Audio Module Done."


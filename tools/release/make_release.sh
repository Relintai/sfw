
# This script generates the final release zip
# Before running this:
# 0. Make sure that the repository is clean. 
#    (Technically only the sfw, sfwl and demos folders need to be clean, as they will be copied using cp -R.)
#    Run: `git clean -f -x` or `git clean -f -x -d` if you want to get rid of folders too
# 1. Run tools/merger/join_all.sh
# 2. Run tools/doc/compile_linux.sh
# 3. Run tools/doc/generate_all.sh
# 4. Run tools/doc/inline_docs.py using python:
#    cd tools/doc/
#    python inline_docs.py

rm -Rf out

mkdir -p out
mkdir -p out/sfw
mkdir -p out/sfw/merged
mkdir -p out/sfw/split
mkdir -p out/sfw/demos

mkdir -p out/sfwl
mkdir -p out/sfwl/merged
mkdir -p out/sfwl/split
mkdir -p out/sfwl/demos

version=""

if [ ! -z $1 ]; then
    version=""
    version+=$1
fi

cd ..
cd ..

project_root_folder=$(pwd)
sfw_out_folder=$(pwd)/tools/release/out/sfw
sfwl_out_folder=$(pwd)/tools/release/out/sfwl

doc_folder=$(pwd)/tools/doc/out/processed

echo "Building SFW release v: $version"

# SFW Split
cp -R "$project_root_folder/sfw" "$sfw_out_folder/split/sfw"
cp "$project_root_folder/compile_linux.sh" "$sfw_out_folder/split/compile_linux.sh"
cp "$project_root_folder/compile_osx.sh" "$sfw_out_folder/split/compile_osx.sh"
cp "$project_root_folder/compile_vs.bat" "$sfw_out_folder/split/compile_vs.bat"
cp "$project_root_folder/compile_windows.sh" "$sfw_out_folder/split/compile_windows.sh"
cp "$project_root_folder/Makefile" "$sfw_out_folder/split/Makefile"

cp "$project_root_folder/.clang-format" "$sfw_out_folder/split/.clang-format"
cp "$project_root_folder/.clang-tidy" "$sfw_out_folder/split/.clang-tidy"
cp "$project_root_folder/.editorconfig" "$sfw_out_folder/split/.editorconfig"
cp "$project_root_folder/.gitignore" "$sfw_out_folder/split/.gitignore"
cp "$project_root_folder/LICENSE.txt" "$sfw_out_folder/split/LICENSE.txt"
cp "$project_root_folder/README.md" "$sfw_out_folder/split/README.md"
cp "$project_root_folder/icon.png" "$sfw_out_folder/split/icon.png"

cp "$project_root_folder/tools/doc/out/processed/sfw_full.html" "$sfw_out_folder/split/sfw.html"

# SFW Merged

# Core
current_in_fol=$project_root_folder/tools/merger/out/core
current_out_fol=$sfw_out_folder/merged/core

mkdir -p "$current_out_fol"
cp "$current_in_fol/sfw.h" "$current_out_fol/sfw.h"
cp "$current_in_fol/sfw.cpp" "$current_out_fol/sfw.cpp"
cp "$doc_folder/sfw_core.html" "$current_out_fol/sfw.html"

# Object
current_in_fol=$project_root_folder/tools/merger/out/object
current_out_fol=$sfw_out_folder/merged/object

mkdir -p "$current_out_fol"
cp "$current_in_fol/sfw.h" "$current_out_fol/sfw.h"
cp "$current_in_fol/sfw.cpp" "$current_out_fol/sfw.cpp"
cp "$doc_folder/sfw_object.html" "$current_out_fol/sfw.html"

# Render Core
current_in_fol=$project_root_folder/tools/merger/out/render_core
current_out_fol=$sfw_out_folder/merged/render_core

mkdir -p "$current_out_fol"
cp "$current_in_fol/sfw.h" "$current_out_fol/sfw.h"
cp "$current_in_fol/sfw.cpp" "$current_out_fol/sfw.cpp"
cp "$current_in_fol/sfw_3rd.m" "$current_out_fol/sfw_3rd.m"
cp "$doc_folder/sfw_render_core.html" "$current_out_fol/sfw.html"

# Render Immediate
current_in_fol=$project_root_folder/tools/merger/out/render_immediate
current_out_fol=$sfw_out_folder/merged/render_immediate

mkdir -p "$current_out_fol"
cp "$current_in_fol/sfw.h" "$current_out_fol/sfw.h"
cp "$current_in_fol/sfw.cpp" "$current_out_fol/sfw.cpp"
cp "$current_in_fol/sfw_3rd.m" "$current_out_fol/sfw_3rd.m"
cp "$doc_folder/sfw_render_immediate.html" "$current_out_fol/sfw.html"

# Render Objects
current_in_fol=$project_root_folder/tools/merger/out/render_objects
current_out_fol=$sfw_out_folder/merged/render_objects

mkdir -p "$current_out_fol"
cp "$current_in_fol/sfw.h" "$current_out_fol/sfw.h"
cp "$current_in_fol/sfw.cpp" "$current_out_fol/sfw.cpp"
cp "$current_in_fol/sfw_3rd.m" "$current_out_fol/sfw_3rd.m"
cp "$doc_folder/sfw_render_objects.html" "$current_out_fol/sfw.html"

# Full
current_in_fol=$project_root_folder/tools/merger/out/full
current_out_fol=$sfw_out_folder/merged/full

mkdir -p "$current_out_fol"
cp "$current_in_fol/sfw.h" "$current_out_fol/sfw.h"
cp "$current_in_fol/sfw.cpp" "$current_out_fol/sfw.cpp"
cp "$current_in_fol/sfw_3rd.m" "$current_out_fol/sfw_3rd.m"
cp "$doc_folder/sfw_full.html" "$current_out_fol/sfw.html"

# SFW Demos

# Minimal APP
current_out_fol=$sfw_out_folder/demos/minimal_app

current_in_fol=$project_root_folder/tools/merger/out/full

cp -R "$project_root_folder/demos/build_scripts/full_minimal/" "$current_out_fol"

cp "$current_in_fol/sfw.h" "$current_out_fol/sfw.h"
cp "$current_in_fol/sfw.cpp" "$current_out_fol/sfw.cpp"
cp "$current_in_fol/sfw_3rd.m" "$current_out_fol/sfw_3rd.m"

current_in_fol=$project_root_folder/demos/minimal_app

cp "$current_in_fol/main.cpp" "$current_out_fol/main.cpp"

# Single Header APP
current_out_fol=$sfw_out_folder/demos/single_header_app

current_in_fol=$project_root_folder/tools/merger/out/full

cp -R "$project_root_folder/demos/build_scripts/full_minimal/" "$current_out_fol"

cp "$current_in_fol/sfw.h" "$current_out_fol/sfw.h"
cp "$current_in_fol/sfw.cpp" "$current_out_fol/sfw.cpp"
cp "$current_in_fol/sfw_3rd.m" "$current_out_fol/sfw_3rd.m"

current_in_fol=$project_root_folder/demos/single_header_app

cp "$current_in_fol/main.cpp" "$current_out_fol/main.cpp"
cp "$current_in_fol/game_application.h" "$current_out_fol/game_application.h"
cp "$project_root_folder/icon.png" "$current_out_fol/icon.png"

# Render Test APP
current_out_fol=$sfw_out_folder/demos/render_test_app

current_in_fol=$project_root_folder/tools/merger/out/full

cp -R "$project_root_folder/demos/build_scripts/full/" "$current_out_fol"

cp "$current_in_fol/sfw.h" "$current_out_fol/sfw.h"
cp "$current_in_fol/sfw.cpp" "$current_out_fol/sfw.cpp"
cp "$current_in_fol/sfw_3rd.m" "$current_out_fol/sfw_3rd.m"

current_in_fol=$project_root_folder/demos/render_test_app

cp "$current_in_fol/main.cpp" "$current_out_fol/main.cpp"
cp "$current_in_fol/game_application.h" "$current_out_fol/game_application.h"
cp "$current_in_fol/game_scene.h" "$current_out_fol/game_scene.h"
cp "$current_in_fol/game_scene.cpp" "$current_out_fol/game_scene.cpp"
cp "$project_root_folder/icon.png" "$current_out_fol/icon.png"

# SFWL Split
cp -R "$project_root_folder/sfwl" "$sfwl_out_folder/split/sfwl"
cp "$project_root_folder/compile_linux_sfwl.sh" "$sfwl_out_folder/split/compile_linux.sh"
cp "$project_root_folder/compile_osx_sfwl.sh" "$sfwl_out_folder/split/compile_osx.sh"
cp "$project_root_folder/compile_vs_sfwl.bat" "$sfwl_out_folder/split/compile_vs.bat"
cp "$project_root_folder/compile_windows_sfwl.sh" "$sfwl_out_folder/split/compile_windows.sh"
cp "$project_root_folder/Makefile_sfwl" "$sfwl_out_folder/split/Makefile"

cp "$project_root_folder/.clang-format" "$sfwl_out_folder/split/.clang-format"
cp "$project_root_folder/.clang-tidy" "$sfwl_out_folder/split/.clang-tidy"
cp "$project_root_folder/.editorconfig" "$sfwl_out_folder/split/.editorconfig"
cp "$project_root_folder/.gitignore" "$sfwl_out_folder/split/.gitignore"
cp "$project_root_folder/LICENSE.txt" "$sfwl_out_folder/split/LICENSE.txt"
cp "$project_root_folder/README.md" "$sfwl_out_folder/split/README.md"

cp "$project_root_folder/tools/doc/out/processed/sfwl_full.html" "$sfwl_out_folder/split/sfwl.html"

# SFWL Merged

# Core
current_in_fol=$project_root_folder/tools/merger/out/sfwl_core
current_out_fol=$sfwl_out_folder/merged/core

mkdir -p "$current_out_fol"
cp "$current_in_fol/sfwl.h" "$current_out_fol/sfwl.h"
cp "$current_in_fol/sfwl.cpp" "$current_out_fol/sfwl.cpp"
cp "$doc_folder/sfwl_core.html" "$current_out_fol/sfwl.html"

# Full
current_in_fol=$project_root_folder/tools/merger/out/sfwl_full
current_out_fol=$sfwl_out_folder/merged/full

mkdir -p "$current_out_fol"
cp "$current_in_fol/sfwl.h" "$current_out_fol/sfwl.h"
cp "$current_in_fol/sfwl.cpp" "$current_out_fol/sfwl.cpp"
cp "$doc_folder/sfwl_full.html" "$current_out_fol/sfwl.html"

# SFW Demos

# Minimal APP
current_out_fol=$sfwl_out_folder/demos/sfwl_doc_merger

current_in_fol=$project_root_folder/tools/merger/out/sfwl_full

cp -R "$project_root_folder/demos/build_scripts/sfwl/" "$current_out_fol"

cp "$current_in_fol/sfwl.h" "$current_out_fol/sfwl.h"
cp "$current_in_fol/sfwl.cpp" "$current_out_fol/sfwl.cpp"

current_in_fol=$project_root_folder/demos/sfwl_doc_merger

cp "$current_in_fol/main.cpp" "$current_out_fol/main.cpp"

cp "$current_in_fol/code_remaining_template.md.html" "$current_out_fol/code_remaining_template.md.html"
cp "$current_in_fol/code_template.md.html" "$current_out_fol/code_template.md.html"
cp "$current_in_fol/compilation_no_renderer.md.html" "$current_out_fol/compilation_no_renderer.md.html"
cp "$current_in_fol/index_remaining_template.md.html" "$current_out_fol/index_remaining_template.md.html"
cp "$current_in_fol/licenses_renderer.md.html" "$current_out_fol/licenses_renderer.md.html"
cp "$current_in_fol/markdeep.min.js" "$current_out_fol/markdeep.min.js"
cp "$current_in_fol/run.sh" "$current_out_fol/run.sh"
cp "$current_in_fol/sfwl_full_template.html" "$current_out_fol/sfwl_full_template.html"
cp "$current_in_fol/slate.css" "$current_out_fol/slate.css"

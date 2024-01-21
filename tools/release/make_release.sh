
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

project_root_folder=$(pwd)/
sfw_out_folder=$(pwd)/tools/release/out/sfw/
sfwl_out_folder=$(pwd)/tools/release/out/sfwl/

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

cp "$project_root_folder/tools/doc/out/processed/sfw_full.html" "$sfw_out_folder/split/sfw.html"

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


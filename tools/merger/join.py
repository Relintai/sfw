#!/usr/bin/python
#
# Copyright (c) 2023-present Péter Magyar
# Copyright (c) 2020 Krzysztof Gabis
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

import sys
import argparse
import re
import os

template_args = {}
input_path = ""

print_includes_dict = dict()

def print_includes(f):
    s = f.split("\n")

    for l in s:
        if l.startswith("#include <"):
            l = l.strip()

            if not l in print_includes_dict:
                print(l)
                print_includes_dict[l] = 1

def strip_file(f):
    if "//--STRIP" in f:
        s = f.split("//--STRIP")
        
        if len(s) % 2 != 1:
            print("File likely has non-terminated //--STRIP comments!")
            return f

        f = ""

        for i in range(len(s)):
            if i % 2 == 0:
                f += s[i]

    return f

def process_file(f):
    #print_includes(f)

    f = strip_file(f)

    #return f.replace('#include ', '//#include ')

    return f

def process_command(name, value):
    if name == "ARG":
        print("Appending arg: " + value)
        return template_args[value]
    elif name == "FILE":
        file_path = os.path.join(input_path, value)
        print("Appending file: " + value)
        with open(file_path, "r") as file:
            res = "#line 1 \"" + value + "\"\n"
            res += process_file(file.read())
            res += "#line 0"
            return res
    elif name == "FILEINLINE":
        file_path = os.path.join(input_path, value)
        print("Appending inline file: " + value)
        with open(file_path, "r") as file:
            res = process_file(file.read())
            return res

def process_template(template):
    regex = r"{{([A-Z]*):([\w./]*)}}"
    matches = re.finditer(regex, template, re.MULTILINE)
    for _, match in enumerate(matches, start=1):
        res = process_command(match.group(1), match.group(2))
        template = template.replace(match.group(0), res)

    return template

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--template", required=True)
    parser.add_argument("--path", required=True)
    parser.add_argument("--output", required=True)

    args, unknown = parser.parse_known_args()

    global input_path
    input_path = args.path

    if len(unknown) % 2 != 0:
        print("Uneven number or template args")
        return 1
    for i in range(0, len(unknown), 2):
        arg = unknown[i]
        if arg.startswith("--"):
            template_args[arg[2:]] = unknown[i + 1]

    with open(args.template, "r") as f:
        output = process_template(strip_file(f.read()))

    with open(args.output, "w") as f:
        f.write(output)

    print("OK")

if __name__ == "__main__":
    main()
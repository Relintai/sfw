# The way markdeep works, is that it will process the entire document on load and it generates
# proper html from it's markdown syntax, and then it deletes itself from the page.
# It cannot be inlined into html, but I'd like to distribute a single file that doesn't need
# internet access to properly open.
# This script will open the generated docs in a browser using selenium, and save the final dom
# to a new file. There are probably better way to do this.

# You need selenium to use this. Also firefox. Just use the latest:

# Create virtual env:
# python -m venv venv

# Activate it (This is for bash on linux). Commands for other shells: https://docs.python.org/3/library/venv.html#how-venvs-work
# . ./venv/bin/activate

# Install:
# pip install selenium

import time 
import math
import os
import shutil
import random
import subprocess
import selenium
from selenium import webdriver
from selenium.webdriver.common.by import By


def ensure_dir(storage_path):
    if not os.path.exists(storage_path):
        os.makedirs(storage_path)

def write_to_file(path, data, mode = "w"):
    lf = open(path, "w")
    lf.write(data)
    lf.close()

def process_file(driver, in_file, out_file):
    browser_file_link = "file://" + os.path.abspath(in_file)

    print("Processing: " + browser_file_link)

    driver.get(browser_file_link)

    #wait a few seconds
    time.sleep(5)

    write_to_file(out_file, driver.page_source)


#headless=False
driver = webdriver.Firefox()

#wait a few seconds
time.sleep(10)

ensure_dir("out/processed")

files = [
    "sfw_core.html",
    "sfw_full.html",
    "sfw_object.html",
    "sfw_render_core.html",
    "sfw_render_gui.html",
    "sfw_render_immediate.html",
    "sfw_render_objects.html",
    "sfwl_core.html",
    "sfwl_full.html",
    "sfw_hash.html",
]

for f in files:
    process_file(driver, "out/" + f, "out/processed/" + f)

time.sleep(5)

driver.close()

#!/usr/bin/python

import py_compile
import compileall

py_compile.compile(r'testngppstgen.py')
compileall.compile_dir(r'./testngppstgen', 0)

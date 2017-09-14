#!/bin/bash
    find . -name "*.h" >>cscope.files
    find . -name "*.go" >>cscope.files
    find . -name "*.cpp" >>cscope.files
    find . -name "*.cc" >>cscope.files
    find . -name "*.c" >>cscope.files
    cscope -Rbkq -i cscope.files
    ctags -R .

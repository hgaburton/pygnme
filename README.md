# pygnme

The `pygnme` package is a python interface to the [`libgnme`](https://github.com/hgaburton/libgnme) package.

### Prequisites

`pygnme` requires the pybind11 package, which can be installed with 

```
python -m pip install pybind11
```

### Installation

`pygnme` is packaged with a `setup.py`:

```
git clone --recurse-submodules git@github.com:hgaburton/pygnme.git
python -m pip install . -v --user
```

If an error such as `ImportError: libgnme_wick.so: cannot open shared object file: No such file or directory` is encountered, add the `site-packages` directory corresponding to your python instance to `LD_LIBRARY_PATH`.

A common error in the installation is 
```
Could NOT find Python3 (missing: Python3_NumPy_INCLUDE_DIRS NumPy) (found version "3.14.2")
```
This appears because CMake cannot find the NumPy include directories, often if the code is being compiled
in a virtual environment. 

A workaround is to add the following CMake arguments to the `cmake_args` in the setup script:
```
"-DPython3_NumPy_INCLUDE_DIRS=<NUMPY_PATH>"
```
where `<NUMPY_PATH>` can be found through the command-line function 
```
python -c 'import numpy;print(numpy.get_include())'
```

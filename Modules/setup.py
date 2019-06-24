from distutils.core import setup, Extension

# static_libraries = ['igraph']
# static_lib_dir = '/system/lib'
# libraries = ['z', 'xml2', 'gmp']
# library_dirs = ['/system/lib', '/system/lib64']
#
# extra_objects = ['{}/lib{}.a'.format(static_lib_dir, l) for l in static_libraries]
#
# ext = Extension('spam',
#                 sources=['spammodule.c'],
#                 libraries=libraries,
#                 library_dirs=library_dirs,
#                 include_dirs=[],
#                 extra_objects=extra_objects)

setup(name = 'spam', version = '1.0', \
      ext_modules = [Extension('spam', ['spammodule.c'])])
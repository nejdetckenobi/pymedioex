from distutils.core import setup, Extension

module = Extension('medioex',
                   sources=['medioex.c', 'pmedex.c'],
                   libraries=['bcm2835'],
                   library_dirs=['./'],
                   extra_compile_args=['-std=gnu11', '-lbcm2835'],
                   extra_link_args = ['-std=gnu11']
                   )

setup(name='PyMedIOEx',
      version='1.0',
      description='This is a demo package',
      ext_modules=[module])


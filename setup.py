from distutils.core import setup, Extension

module = Extension('medioex',
                   sources=['medioex.c', 'pmedex.c'],
                   libraries=['bcm2835'],
                   library_dirs=['./'],
                   extra_compile_args=['-std=gnu11', '-lbcm2835'],
                   extra_link_args = ['-std=gnu11']
                   )

setup(name='PyMedIOEx',
      version='1.1',
      description='A Python3 wrapper for MedIOEx for Raspberry Pi 3',
      author='Nejdet Çağdaş Yücesoy / Ülkü Bayraktar',
      author_email='nejdetyucesoy@gmail.com',
      url='https://github.com/nejdetckenobi/pymedioex',
      download_url='https://github.com/nejdetckenobi/pymedioex/archive/1.1.tar.gz',
      ext_modules=[module])


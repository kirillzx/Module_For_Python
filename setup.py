from distutils.core import setup, Extension

module1 = Extension(
	'MatrixNorm',
	sources = ['module.c']
)

setup(
	name = 'module',
	version = '1.1',
	description = 'Simple module',
	ext_modules= [module1]
)

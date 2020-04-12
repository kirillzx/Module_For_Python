from distutils.core import setup, Extension

module1 = Extension(
	'MatrixNorm',
	sources = ['Module.c']
)

setup(
	name = 'Module',
	version = '1.1',
	description = 'Simple module',
	ext_modules= [module1]
)

from distutils.core import setup, Extension

module1 = Extension(
	'MatrixNorm',
	sources = ['MatrixNorm.c']
)

setup(
	name = 'MatrixNorm',
	version = '1.1',
	description = 'Simple module',
	ext_modules= [module1]
)

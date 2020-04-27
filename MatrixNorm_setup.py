from distutils.core import setup, Extension

module1 = Extension(
      'MatrixNorm', # название модуля внутри Python
      sources = ['MatrixNorm.c'] # Исходные файлы модуля
)

setup(
      name = 'MatrixNorm', # название модуля (my_plus.__name__)
      version = '1.1', # версия модуля
      description = 'Matrix norm', # описание модуля
      ext_modules= [module1] # объекты типа Extension (мы объявили его выше)
)

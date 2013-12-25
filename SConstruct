# SConstruct - root SCons script for SuperSpaceShipsShootingStuff

from scons_common import *
import os
import glob

###### Sconstruct ######

env = createEnvironment(generate_help=True)	# generate the help

if os.name == 'posix':
	env['LINK'] = 'g++'	# We got some problem of gcc being used instead of g++ when using VariantDir()...

#env['ENV']['PKG_CONFIG_PATH'] = os.path.join(qtdir, 'lib/pkgconfig')
env.Append(LFLAGS=['-Wl'])

### Libs
# opengl
if env['PLATFORM'] == 'win32':
	env.Append(LIBPATH=['dep/glew/lib-win32'])
	env.Append(CPPPATH = ['dep/glew/include'])
	env.Append(LIBS=['-lopengl32','-lglew32','-lglu32'])
else:
	env.Append(LIBS=['-lGL','-lGLU','-lGLEW'])
# openal
if env['PLATFORM'] == 'win32':
	env.Append(CPPPATH=['dep/openal/include'])
	env.Append(LIBPATH=['dep/openal/lib-win32'])
	env.Append(LIBS=['-lOpenAL32','-lalut'])
else:
	env.Append(LIBS=['-lopenal','-lalut'])
# assimp
if env['PLATFORM'] == 'win32':
	env.Append(LIBPATH=['dep/assimp/lib-win32'])
#else:
#	env.Append(LIBPATH=['dep/assimp/lib'])
env.Append(CPPPATH = ['dep/assimp/include'])
env.Append(LIBS=['-lassimp'])
# bullet
env.Append(LIBS=
		['BulletSoftBody',
		'BulletDynamics',
		'BulletCollision',
		'LinearMath'])
if env['PLATFORM'] == 'win32':
	env.Append(CPPPATH=['dep/bullet/src'])
	env.Append(LIBPATH=['dep/bullet/lib-win32'])
else:
	env.ParseConfig('pkg-config bullet --cflags --libs')

env.ParseConfig('pkg-config uuid --cflags --libs')

SConscript('SConscript_engine','env')

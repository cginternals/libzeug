libzeug
=======

Libzeug is a collection of C++ functions, classes and libraries that are too small to be standalone.
It acts like a storage point for useful and reusable code for everyone using C++.
Libzeug is a cross-platform library licenced under the [MIT license](http://opensource.org/licenses/MIT).

The current modules in libzeug are:
 * [iozeug](#iozeug)
 * [propertyguizeug](#propertyguizeug)
 * [reflectionzeug](#reflectionzeug)
 * [scriptzeug](#scriptzeug)
 * [signalzeug](#signalzeug)
 * [threadingzeug](#threadingzeug)

The current pre-release is [libzeug-v0.1.0](https://github.com/hpicgs/libzeug/releases/tag/libzeug-v0.1).
To find out more about libzeug and how to use it, check out our [wiki](https://github.com/hpicgs/libzeug/wiki).

### Documentation

A first basic libzeug documentation can be found [here](http://costumebrother.de/libzeug).

### Dependencies

The following dev-libraries and programs need to be provided for correct CMake configuration:
* C++11 compatible compiler (e.g. gcc 4.8, better 4.9, VS 2013)
* CMake (>=2.8.9, better 2.8.12): http://www.cmake.org/
* Qt5 (>= 5.0): http://www.qt-project.org/


## Development Notes

If you are contributing to this project, please keep the following notes in mind:
* Add your name and email to the AUTHORS file.
* Follow coding conventions according to google's [C++ Style Guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml).
* Commits should provide a meaningful  message, which uses the imperative, present tense: "change", not "changed" nor "changes", AND start with a capital letter.
* Commits should always refer to an issue: use ```#xxx```, ```fix #xxx```, or ```close #xxx```.
* Pull Requests are reviewed by at least one other developer on another platform.
* Use lazy initialization as often as possible for time consuming tasks.
* Member Variables always start with ```m_```, ```g_```, and ```s_``` (e.g.,```m_member```, ```g_global```, and ```s_static```)..
* Interface or abstract class names always start with Abstract (e.g., ```AbstractPainter```).
* Enforce strict include sequence: gl, glew, std, glm, header, glow (there should be only a few exceptions).



iozeug
------

iozeug contains a function to read a file into an std::string.

propertyguizeug
---------------

propertyguizeug contains the automatic generation of a GUI from a set of properties from [reflectionzeug](#reflectionzeug).

reflectionzeug
------------

reflectionzeug allows the definition of properties that can be used to parameterize a program.
It supports saving and loading properties to and from a file.
The currently implemented property types are `int`, `double`, `std::string`, fixed size `std::vector` for mathematical vectors and matrices, `bool`, `FilePath` and `Color`.

scriptzeug
----------

configure V8 in Win with x64 and no i18n:
`python build\gyp_v8 -Dtarget_arch=x64 -Dv8_enable_i18n_support=0 -Dcomponent=shared_library`
build:
`msbuild /p:Configuration=Release tools\gyp\v8.sln`


signalzeug
----------

signalzeug is a small library that provides classes for a simple signal system.
Objects can define signals they can fire and other objects can register on those signals.
Arbitrary parameters and even signal chaining are allowed.

threadingzeug
-------------

threadingzeug provides a `parallel_for` function that uses either OpenMP or the `std::thread` classes to execute a for loop concurrently.

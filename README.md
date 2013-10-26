libzeug
=======

Libzeug is a collection of C++ functions, classes and libraries that are too small to be standalone.
It acts like a storage point for useful and reusable code for everyone using C++.

The current modules in libzeug are:
 * [iozeug](#iozeug)
 * [propertyguizeug](#propertyguizeug)
 * [propertyzeug](#propertyzeug)
 * [signalzeug](#signalzeug)
 * [stagezeug](#stagezeug)
 * [threadingzeug](#threadingzeug)
 * [treeimportzeug](#treeimportzeug)
 * [treezeug](#treezeug)

iozeug
------

iozeug contains a function to read a file into an std::string.

propertyguizeug
---------------

propertyguizeug contains the automatic generation of a GUI from a set of properties from [propertyzeug](#propertyzeug).

propertyzeug
------------

propertyzeug allows the definition of properties that can be used to parameterize a program.
It supports saving and loading properties to and from a file.
The currently implemented property types are `int`, `double`, fixed size `std::vector` for mathematical vectors and matrices, `bool`, `FilePath` and `Color`.

signalzeug
----------

signalzeug is a small library that provides classes for a simple signal system.
Objects can define signals they can fire and other objects can register on those signals.
Arbitrary parameters and even signal chaining are allowed.

stagezeug
---------

stagezeug allows the definition of `Pipelines` that consist of `Stages` which builds a dependency graph.
This library ensures that each stage is only executed once when the pipeline is executed and it determines an order in which the stages can be executed regarding their dependencies.

threadingzeug
-------------

threadingzeug provides a `parallel_for` function that uses either OpenMP or the `std::thread` classes to execute a for loop concurrently.

treeimportzeug
--------------

treeimportzeug handles several tree data file types and creates `Trees` from [treezeug](#treezeug).

treezeug
--------

treezeug provides classes that build a `Tree` that consists of `Nodes`.
Each tree has an arbitrary number of attributes and each node may have a value for each registered attribute.
An additional class helps with the linearization of such a tree (e.g. optimized for concurrent traversal).

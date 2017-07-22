Pessum
======

.. image:: https://travis-ci.org/LuxAtrumStudio/Pessum.svg?branch=cmake
    :target: https://travis-ci.org/LuxAtrumStudio/Pessum

.. image:: https://coveralls.io/repos/github/LuxAtrumStudio/Pessum/badge.svg?branch=cmake
    :target: https://coveralls.io/github/LuxAtrumStudio/Pessum?branch=cmake


Pessum is a C++ library to implement a few simple utilities to projects. These
utilities include a logging system, and Data Loading system.

Components
~~~~~~~~~~

Logging
-------

The logging structure is simple made with one main function to call for adding
new log entries.

.. code:: c++

   pessum::Log(int type, std::string msg, std::string function, ...)

Data Loading
------------

The data loading system is a method that creates a vector of a dynamic data
type, that is loaded from a file, and can be saved to a file with a simple
output.

Installation
~~~~~~~~~~~~

Get the project source code with:

:: 

   git clone hhtps://github.com/LuxAtrumStudio/Pessum.git

Then run the following commands in the terminal:

::

   cd Pessum
   sudo make install

Reference
~~~~~~~~~

API Reference can be found on the `github
page <https://luxatrumstudio.github.io/Pessum/>`_.

Tests
~~~~~

Test can be run after installation with this command:

::

   ./pessum-test

This will run the googletest program associated with the pessum library.

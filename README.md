Pessum
======

[![image](https://travis-ci.org/LuxAtrumStudio/Pessum.svg?branch=master)](https://travis-ci.org/LuxAtrumStudio/Pessum)

[![image](https://codecov.io/gh/LuxAtrumStudio/Pessum/branch/master/graph/badge.svg)](https://codecov.io/gh/LuxAtrumStudio/Pessum)

[![image](https://api.codacy.com/project/badge/Grade/76f87d72988a4c7b9816f04a48b102bb)](https://www.codacy.com/app/LuxAtrumStudio/Pessum?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=LuxAtrumStudio/Pessum&amp;utm_campaign=Badge_Grade)

Pessum is a C++ library to implement a few simple utilities to projects.
These utilities include a logging system, and Data Loading system.

-   [Travis CI](https://travis-ci.org/LuxAtrumStudio/Pessum).
-   [Code Coverage](https://codecov.io/LuxAtrumStudio/Pessum).
-   [Code Quality](https://www.codacy.com/app/LuxAtrunStudio/Pessum/dashboard).

Components
----------

### Logging

The logging structure is simple made with one main function to call for
adding new log entries.

``` {.sourceCode .c++}
pessum::Log(int type, std::string msg, std::string function, ...)
```

### Data Loading

The data loading system is a method that creates a vector of a dynamic
data type, that is loaded from a file, and can be saved to a file with a
simple output.

Installation
------------

Get the project source code with:

    git clone hhtps://github.com/LuxAtrumStudio/Pessum.git

Then run the following commands in the terminal:

    cd Pessum
    sudo make install

Reference
---------

API Reference can be found on the [github page](https://luxatrumstudio.github.io/Pessum/).

Tests
-----

Test can be run after installation with this command:

    ./pessum-test

This will run the googletest program associated with the pessum library.

![Logo](img/pessum_title.svg)

---

[![Github Release](https://img.shields.io/github/downloads/LuxAtrumStudio/pessum/latest/total.svg)](https://github.com/LuxAtrumStudio/Pessum)

[![Build Status](https://img.shields.io/travis/LuxAtrumStudio/Pessum.svg)](https://travis-ci.org/LuxAtrumStudio/Pessum)
[![codecov](https://img.shields.io/codecov/c/github/LuxAtrumStudio/Pessum.svg)](https://codecov.io/gh/LuxAtrumStudio/Pessum)
[![Codacy grade](https://img.shields.io/codacy/grade/76f87d72988a4c7b9816f04a48b102bb.svg)](https://www.codacy.com/app/LuxAtrumStudio/Pessum)

---

## Introduction ##

Pessum is a small header only library focused on providing implementation for
log handling. Pessum provides a system for storing logs in a global vector,
which contains log type, log message, and log origin. It can optionally
implement the inclusion of time stamps and date stamps.

## Example ##

Here is a simple example that will set the handle to output log message to the
console.
```cpp
#include <iostream>
#include <pessum/pessum.hpp>

void log_handle(std::string msg){
  std::cout << msg;
}

int main(void){
  pessum::SetLogHandle(log_handle);
  pessum::Log(pessum::SUCCESS, "Set Log Handle", "main")
}
```

```
[SUCCESS]Set Log Handle[main]
```

## Getting Started ##

A complete tutorial guide is provided at
[Tutorials](tutorials/index.md). This guide will walk new users
through the different methods that are available in the Pessum library, and how
to implement them successfully.

A full API reference guide can be found at [Reference](reference/index.md). The API
reference provides specific documentation on each function, including
parameters, and return results.

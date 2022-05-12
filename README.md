opensource Sita Team Decompiler
==============

A decompiler for [opentext Gupta Team Developer](https://www.opentext.com/products-and-solutions/products/specialty-technologies/opentext-gupta-development-tools-databases/opentext-gupta-team-developer) applications.

### Usage

Run `Sita` in the command prompt to view the usage hint.

### Building

Run `make` to build the application.

Alternatively, create a new Visual Studio C++ project and add cpp source and hpp/inc header files to that project.

### Project status

The decompiler is in an early stage of development. As of now, it can read the basic Outline structure of standard applications and decompile some basic operations. Not all language features, variable names, etc. are decompiled correctly. Only 32bit Team Developer applications are officially supported yet. Decompiling 64bit applications is currently still buggy.

Currently, TD 5.1 – 7.4 are supported.

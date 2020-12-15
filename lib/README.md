# Common libraries

This folder contains libraries that are available for use from clients in other parts of the repository.

## Build system

The build system automatically cretes the static archive for each library in the `lib/bin` folder under the name `libname.a` (for a library named `name`).

Each library must expose a public header named `public.h` that will be copied in the `lib/hdr` folder with the name `name.h` (for a library named `name`). Alternatively a library can include a makefile that will be executed
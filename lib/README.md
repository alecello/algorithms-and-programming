# Common libraries

This folder contains libraries that are available for use from clients in other parts of the repository.

## Build system

Building a library proceeds as follows

- Create an `obj` subfolder in the library folder if it does not exist
- Compile all the code units of the library to object files in the `obj` folder
- Assemble all the object files inside an archive named `lib[name].a` in the `lib/bin` folder
- Copy the `public.h` header to `libs/hdr/lib[name].h`
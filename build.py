#!/bin/env python

import sys, os, glob, re, subprocess, shutil

librarySrcRoot = os.path.join('lib', 'src')
libraryHdrRoot = os.path.join('lib', 'hdr')
libraryBinRoot = os.path.join('lib', 'bin')

programBinName = 'main'
publicHeaderName = 'public.h'

# Dictionary of special system headers that require a dynamic library to be manually specified
# Each key is a header as it appears in the include (EG: "math.h")
# Each value is the corresponding library name stripped of the initial lib and the .so extension (EG: "m" for "math.h", as in "libm.so" and the "-lm" switch for GCC)
dynamicallyLikedLibraries = {'math.h': 'm'}



class Program:
    systemHeaders = []      # Contains list of included system headers as-is (for example, "stdio.h", "math.h")
    localsHeaders = []      # Contains list of included locals headers adjusted to represent a relative path with respect to the local includes dir (for example, "test/test.h" becomes "test\\test.h" on Windows)

    staticDependencies = [] # List of static library dependencies
    sharedDependencies = [] # List of shared library dependencies

    sources = []            # Contains a list of source files
    headers = []            # Contains a list of header files

    isLibrary = False       # Wether the current project is a library or not
    hasMakefile = False     # Wether the current project has a Makefile

    directory = ''          # Path of project directory
    package = ''            # Relative directory with respect to sources, binaries, header root directories for the specific project
    name = ''               # Name of the project

    binaryPath = ''         # Path of the binary file
    publicHeaderPath = ''   # Path of the public header file
    objectFilesPath = ''    # Path of the objets folder


    def printDetails(self):
        print('========================================================================================================================')
        print('System Headers:')
        print('\n'.join(['\t' + lib for lib in self.systemHeaders]))
        print('Local Headers:')
        print('\n'.join(['\t' + lib for lib in self.localsHeaders]))
        print('Source files:')
        print('\n'.join(['\t' + src for src in self.sources]))
        print('Header files:')
        print('\n'.join(['\t' + hdr for hdr in self.headers]))
        print('Dependencies:')
        print('\n'.join(['\t' + dep for dep in self.staticDependencies + self.sharedDependencies]))
        print(f'\nThis project {"is" if self.isLibrary else "is not"} a library')
        print('Directory: ' + self.directory)
        print('package: ' + self.package)
        print('Name: ' + self.name)
        print('Binary path: ' + self.binaryPath)
        print('Public header path: ' + (self.publicHeaderPath if self.isLibrary else '<None>'))
        print('Object files directory: ' + self.objectFilesPath)
        print('========================================================================================================================')


    def splitPath(self):
        return os.path.join(*self.directory.split(os.path.sep)[:-1]).replace(librarySrcRoot, '').strip(os.path.sep), os.path.basename(self.directory)


    def checkIfLibrary(self):
        return self.directory.startswith('lib')
    

    def checkForMakefile(self):
        return os.path.isfile(os.path.join(self.directory, 'Makefile')) or os.path.isfile(os.path.join(self.directory, 'makefile'))


    def getHeaders(self):
        self.localsHeaders = []
        self.systemHeaders = []

        for entity in self.sources + self.headers:
            with open(entity) as f:
                for line in f.readlines():
                    s_match = re.search('#include\s*<(?P<name>.+)>', line)
                    l_match = re.search('#include\s+"(?P<name>.+)"', line)

                    if s_match is not None:
                        if s_match.group('name') not in self.systemHeaders:
                            self.systemHeaders.append(s_match.group('name'))

                    if l_match is not None:
                        if not os.path.exists(os.path.join(self.directory, *l_match.group('name').split('/'))):
                            if l_match.group('name') not in self.localsHeaders:
                                self.localsHeaders.append(os.path.join(*l_match.group('name').split('/')))
    

    def getDependencies(self):
        self.staticDependencies = []
        self.sharedDependencies = []

        for dep in self.localsHeaders:
            filename = os.path.splitext(os.path.basename(dep))[0]
            path = dep.replace(os.path.basename(dep), '').strip(os.path.sep)

            prefix = 'lib'
            extension = '.a'
            
            result = os.path.join(libraryBinRoot, path, prefix + filename + extension)
            self.staticDependencies.append(result)
        
        for dep in self.systemHeaders:
            if dep in dynamicallyLikedLibraries:
                self.sharedDependencies.append(f'-l{dynamicallyLikedLibraries[dep]}')


    def buildProject(self):
        if self.hasMakefile:
            runCommand(f'make -C {self.directory}')
        else:
            output = []

            os.makedirs(self.objectFilesPath, exist_ok=True)
            
            for source in self.sources:
                objectFileName = os.path.splitext(os.path.basename(source))[0] + '.o'
                objectFilePath = os.path.join(self.objectFilesPath, objectFileName)
                output.append(objectFilePath)

                runCommand(f'gcc -Wall -pedantic -ggdb -I {libraryHdrRoot} {" ".join(self.sharedDependencies)} -c -o {objectFilePath} {source}')

                os.makedirs(os.path.dirname(self.binaryPath), exist_ok=True)

                if self.isLibrary:
                    os.makedirs(os.path.dirname(self.publicHeaderPath), exist_ok=True)
                    shutil.copy(os.path.join(self.directory, publicHeaderName), self.publicHeaderPath)

                    for obj in output:
                        runCommand(f'ar rcs {self.binaryPath} {obj}')
                else:
                    runCommand(f'gcc -Wall -pedantic -ggdb -I {libraryHdrRoot} {" ".join(self.sharedDependencies)} -o {self.binaryPath} {" ".join(output)} {" ".join(self.staticDependencies)}')
    

    def clean(self):
        if self.hasMakefile:
            runCommand(f'make -C {self.directory} clean')
        else:
            delete(self.binaryPath)
            delete(self.objectFilesPath)

            if self.isLibrary:
                delete(self.publicHeaderPath)


    def __init__(self, directory='example'):
        self.directory = directory

        self.package, self.name = self.splitPath()
        self.isLibrary = self.checkIfLibrary()
        self.hasMakefile = self.checkForMakefile()

        self.sources = glob.glob(os.path.join(self.directory, '**', '*.c'), recursive=True)
        self.headers = glob.glob(os.path.join(self.directory, '**', '*.h'), recursive=True)

        self.getHeaders()
        self.getDependencies()

        self.binaryPath = os.path.join(self.directory, 'main') if not self.isLibrary else os.path.join(libraryBinRoot, self.package, f'lib{self.name}.a')
        self.publicHeaderPath = os.path.join(libraryHdrRoot, self.package, f'{self.name}.h') if self.isLibrary else ''
        self.objectFilesPath = os.path.join(self.directory, 'out')



def runCommand(command: str):
    process = subprocess.Popen(command.split())
    process.wait()

def delete(path: str):
    if os.path.isfile(path):
        os.remove(path)
    elif os.path.isdir(path):
        shutil.rmtree(path)


def findAllProjects() -> list:
    source_files = glob.glob(os.path.join('**', '*.c'), recursive=True)

    # All projects have a flat file hierarchy so getting the list of directories containing source files is
    # equivalent to getting the list of projects.
    return list(set([ os.path.dirname(x) for x in source_files ]))


projects = []

if len(sys.argv) != 3:
    print('ERROR: Wrong number of parameters.')
    exit(1)

if sys.argv[2] == 'all':
    for project in findAllProjects():
        projects.append(Program(project))
    
    projects.sort(key=lambda x: 0 if x.isLibrary else 1)
else:
    projects = [ Program(sys.argv[2]) ]

for project in projects:
    if sys.argv[1] == 'build':
        project.buildProject()
    elif sys.argv[1] == 'clean':
        project.clean()
    else:
        print('ERROR: Unknown verb.')
        exit(1)

if sys.argv[1] == 'clean' and sys.argv[2] == 'all':
    delete(libraryBinRoot)
    delete(libraryHdrRoot)
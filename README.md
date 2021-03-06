Madronalib
----------

A C++ framework for DSP applications.

Copyright (c) 2019 Madrona Labs LLC. http://www.madronalabs.com

Distributed under the MIT license: http://madrona-labs.mit-license.org/


C++ for audio: the good parts
------------

C++ is an excellent tool for writing audio software. Unfortunately it's difficult to get started with, and provides a mine field of bad ways to do things. Madronalib provides one clear path to writing maintainable audio code without sacrificing performance. It enables efficient audio DSP on SIMD processors with readable, brief code.

With the advent of C++11, new features became available as part of the standard library, and new syntax provided clearer ways to express abstractions with no overhead. Madronalib leans on C++11 to reduce its code footprint and increase clarity.

To get reliable audio performance in a multiprocessing system, careful attention must be paid to memory allocation, shared object access, and any use of OS calls. (see: http://www.rossbencina.com/code/real-time-audio-programming-101-time-waits-for-nothing) Madronalib encapsulates these concerns and provides a simple API to the writers of audio applications.

Adding new DSP modules is straightforward. The syntax of the signal library encourages code to "read like the math." There are no weird macros to learn.

The Google C++ style guidelines (https://google-styleguide.googlecode.com/svn/trunk/cppguide.html) are followed, for the most part. 


Status
------------

(as of June 2019)

The files in /source/DSP are a useful header-only DSP library and can be included without other dependencies:  `#include mldsp.h`. These provide a bunch of utilities for writing efficient and readable DSP code in a functional style. SIMD operations for sin, cos, log and exp provide a big speed gain over native math libraries and come in both precise and approximate variations.  An SSE version is complete, NEON support is a work in progress. Shipping products at Madrona Labs are relying on these headers and breaking changes have, for the most part, stopped. 

The code in /source/app is also relied upon by shipping products, though it may still change more often. 

Good examples await doing. A starting point for this would be showing how to use madronalib with JUCE or IPlug to make cross-platform plugins.

Tests exist for most modules. Someone should set up continuous integration.

OSC (Open Sound control) networking still awaits porting to Windows / Linux.


Building
----------

Madronalib can be built with the default settings as follows:

	mkdir build
	cd build
	cmake ..
	make
    
This will create a command-line build of all the new code.
To build an XCode project with JUCE support, run something like

	mkdir build-xcode
	cd build-xcode
	cmake -GXcode ..

To build a VS2015 project for a 64-bit Windows app I'm currently using the command 

	cmake .. -G "Visual Studio 14 2015 Win64"


Contents
--------

	/cmake : any modules or tools for the cmake build system
  
	/examples: example projects
  
	/external: small supporting code projects included as source. cJSON, oscpack etc.
  
	/include: top-level public headers: mldsp.h, madronalib.h
  
	/source:
  
		/app: utilities for low-level application support: symbols,
			timers, queues, data structures, models, etc. these modules shall 
			only depend on other code in /app.
      
		/DSP: header-only library for SIMD DSP.
			These modules shall only depend on code in /DSP, 
			with the exception of the externals/ffft library. Include 
			mldsp.h to include all DSP files. NEON code is work 
			in progress.
      
		/matrix: matrix and vector data and functions. Depends only on 
			/DSP, for SIMD math.
      
		/networking: OSC and MIDI support.
    
		/procs: higher level DSP code designed to support dynamic graphs
			(changing at runtime.) These rely on code in /DSP as well as
			the symbolic code in /app. work in progress.
      
	/tests: tests for all modules implemented using the Catch library.





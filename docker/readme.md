In file included from /home/snac_user/snac/build/include/StGermain/Discretisation/Utils/Utils.h:46,
                 from /home/snac_user/snac/build/include/StGermain/Discretisation/Discretisation.h:48,
                 from /home/snac_user/snac/build/include/StGermain/StGermain.h:50,
                 from RemeshElements.c:35:




-I/usr/include/libxml2      RemeshElements.c
In file included from /home/snac_user/snac/build/include/StGermain/Discretisation/Utils/Utils.h:46,
                 from /home/snac_user/snac/build/include/StGermain/Discretisation/Discretisation.h:48,
                 from /home/snac_user/snac/build/include/StGermain/StGermain.h:50,
                 from RemeshElements.c:35:


problem file is /StGermain/Utils/Src/RegularMeshUtils.h I think. I think that StGermain/Discretisation/Utils/Utils.h:46, is not able to find RegularMeshUtils.h. Some kind of include error?

here is where the error function is:
./Snac/plugins/remesher_BI/RemeshElements.c:69: void createBarycenterGrids( void* _context );
./Snac/plugins/remesher_BI/RemeshElements.c:98: createBarycenterGrids( context );
./Snac/plugins/remesher_BI/RemeshElements.c:319:void createBarycenterGrids( void* _context )
-------------

Warning: /usr/lib/x86_64-linux-gnu/lib/libdl.[a|so]  not found. Set the DL_DIR environment variables. Darwin requires the dlcompat package installed.

Warning: /usr/lib/x86_64-linux-gnu/include/dlfcn.h not found. Set the environment variables.



/usr/lib/x86_64-linux-gnu/lib/libdl.[so/a]

libdl.[so/a] is actually in:
/usr/lib/x86_64-linux-gnu

This is raising a warning in configure.

grep -r DL_DIR

Need to edit some files to point DL_DIR to include the x86_64 directory I think.
Here is the files where DL_DIR is mentioned:

Snac/Vmake/configure.sh
Snac/VMake/Config/sdl-config.sh
VMake/configure.sh
VMake/Config/sdl-config.sh
StGermain/VMake/configure.sh
StGermain/VMake/Config/sdl-config.sh
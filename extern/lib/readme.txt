glut32 = glut64 = both are 64 bit binaries

i made a copy of the glut64 and renamed it to glut32 because i was getting a linker error, couldn't figure out where the linker was looking for glut

looked in the header file, and found GLUT_NO_LIB_PRAGMA but that didnt work

will have to fix this later

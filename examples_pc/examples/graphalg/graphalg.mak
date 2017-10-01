# ****************************************************************************
# *                                                                          *
# *  graphalg.mak                                                            *
# *  ============                                                            * 
# *                                                                          *
# ****************************************************************************

# ****************************************************************************
# *                                                                          *
# *  Define the name of the makefile.                                        *
# *                                                                          *
# ****************************************************************************

MAKNAM = graphalg.mak

# ****************************************************************************
# *                                                                          *
# *  Define the directories in which to search for library files.            *
# *                                                                          *
# ****************************************************************************

LIBDRS =

# ****************************************************************************
# *                                                                          *
# *  Define the directories in which to search for include files.            *
# *                                                                          *
# ****************************************************************************

INCDRS = -I$(ALGOWC_TOPDIR)/include

# ****************************************************************************
# *                                                                          *
# *  Define the library files.                                               *
# *                                                                          *
# ****************************************************************************

LIBFLS = -lm

# ****************************************************************************
# *                                                                          *
# *  Define the source files.                                                *
# *                                                                          *
# ****************************************************************************

SRCFLS = ex-1.c\
         $(ALGOWC_TOPDIR)/source/graph.c\
         $(ALGOWC_TOPDIR)/source/list.c\
         $(ALGOWC_TOPDIR)/source/mst.c\
         $(ALGOWC_TOPDIR)/source/route.c\
         $(ALGOWC_TOPDIR)/source/set.c\
         $(ALGOWC_TOPDIR)/source/shortest.c\
         $(ALGOWC_TOPDIR)/source/tsp.c
         
# ****************************************************************************
# *                                                                          *
# *  Define the object files.                                                *
# *                                                                          *
# ****************************************************************************

OBJFLS = ex-1.o\
         $(ALGOWC_TOPDIR)/source/graph.o\
         $(ALGOWC_TOPDIR)/source/list.o\
         $(ALGOWC_TOPDIR)/source/mst.o\
         $(ALGOWC_TOPDIR)/source/route.o\
         $(ALGOWC_TOPDIR)/source/set.o\
         $(ALGOWC_TOPDIR)/source/shortest.o\
         $(ALGOWC_TOPDIR)/source/tsp.o

# ****************************************************************************
# *                                                                          *
# *  Define the executable.                                                  *
# *                                                                          *
# ****************************************************************************

EXE    = ex-1.exe

# ****************************************************************************
# *                                                                          *
# *  Define the compile and link options.                                    *
# *                                                                          *
# ****************************************************************************

CC     = c89
LL     = c89
CFLAGS = -D_HPUX_SOURCE
LFLAGS =

# ****************************************************************************
# *                                                                          *
# *  Define the rules.                                                       *
# *                                                                          *
# ****************************************************************************

$(EXE): $(OBJFLS)
	$(LL) $(LFLAGS) -o $@ $(OBJFLS) $(LIBDRS) $(LIBFLS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $(INCDRS) $<

all:
	make -f $(MAKNAM) clean
	make -f $(MAKNAM) depend

depend:
	makedepend $(INCDRS) -f $(MAKNAM) $(SRCFLS)
	make -f $(MAKNAM) $(EXE)

clean:
	-rm $(EXE)
	-rm $(OBJFLS)

# DO NOT DELETE THIS LINE -- make depend depends on it.

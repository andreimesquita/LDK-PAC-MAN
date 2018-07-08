# source paths
LDKSDK=include
GAMESRC=game\game.cpp

#build targets
OUTDIR=build
LDK_GAME=$(OUTDIR)\ldk_game.dll

#DEBUG OPTIONS
LIBS=user32.lib gdi32.lib Opengl32.lib Msimg32.lib Ole32.lib
DEBUG_DEFINES=/D "_LDK_DEBUG_" 
DEBUG_COMPILE_OPTIONS=/nologo /EHsc /MT /I$(LDKSDK) $(DEBUG_DEFINES) /Zi
DEBUG_LINK_OPTIONS=/link /subsystem:console $(LIBS)

#RELEASE OPTIONS
RELEASE_DEFINES=/D "_LDK_RELEASE_"
RELEASE_COMPILE_OPTIONS=/nologo /EHsc /MT /I$(LDKSDK) $(RELEASE_DEFINES) /Zi
RELEASE_LINK_OPTIONS=/link /subsystem:windows $(LIBS)

#DEBUG build
CFLAGS=$(DEBUG_COMPILE_OPTIONS)
LINKFLAGS=$(DEBUG_LINK_OPTIONS)
#RELEASE build
#CFLAGS=$(RELEASE_COMPILE_OPTIONS)
#LINKFLAGS=$(RELEASE_LINK_OPTIONS)
.PHONY: game assets

game: $(GAMESRC)
	@echo Building game dll...
	cl $(GAMESRC) /Fo$(OUTDIR)\ /Fe$(LDK_GAME) /LD $(CFLAGS) /link /subsystem:windows lib/ldk.lib
	@copy /Y $(OUTDIR)\ldk_game.dll .

assets:
	@echo copying assets ...
	@xcopy game\assets $(OUTDIR)\assets /Y /I /E /F > NUL
	@xcopy assets $(OUTDIR)\assets /Y /I /E /F > NUL
	@copy /Y ldk.cfg $(OUTDIR) > NUL

clean:
	@IF EXIST "_game_copy.dll" del \S \Q "_game_copy.dll" > NUL
	@IF EXIST "$(OUTDIR)" del /S /Q .\$(OUTDIR)\* > NUL
	@IF EXIST "$(OUTDIR)\assets" rd /S /Q .\$(OUTDIR)\assets > NUL

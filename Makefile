ifndef config
  config=debug_x64
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

# Libraries
ALL_LDFLAGS += -lsqlite3

ifeq ($(origin CC), default)
  CC = clang
endif
ifeq ($(origin CXX), default)
  CXX = clang++
endif
ifeq ($(origin AR), default)
  AR = ar
endif
INCLUDES += -Isrc -Iinclude -I../external/raylib-master/src -I../external/raylib-master/src/external -I../external/raylib-master/src/external/glfw/include
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),debug_x64)
TARGETDIR = bin/Debug
TARGET = $(TARGETDIR)/rpg
OBJDIR = build/obj/x64/Debug/rpg
DEFINES += -DDEBUG -DPLATFORM_DESKTOP -DGRAPHICS_API_OPENGL_33
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -Wshadow -g -std=c99 -Wno-deprecated-declarations
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -Wshadow -g -std=c++17 -Wno-deprecated-declarations
LIBS += bin/Debug/libraylib.a -framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreAudio -framework CoreVideo -framework AudioToolbox
LDDEPS += bin/Debug/libraylib.a
ALL_LDFLAGS += $(LDFLAGS) -m64

else ifeq ($(config),debug_x86)
TARGETDIR = bin/Debug
TARGET = $(TARGETDIR)/rpg
OBJDIR = build/obj/x86/Debug/rpg
DEFINES += -DDEBUG -DPLATFORM_DESKTOP -DGRAPHICS_API_OPENGL_33
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -Wshadow -g -std=c99 -Wno-deprecated-declarations
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -Wshadow -g -std=c++17 -Wno-deprecated-declarations
LIBS += bin/Debug/libraylib.a -framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreAudio -framework CoreVideo -framework AudioToolbox
LDDEPS += bin/Debug/libraylib.a
ALL_LDFLAGS += $(LDFLAGS) -m32

else ifeq ($(config),debug_arm64)
TARGETDIR = bin/Debug
TARGET = $(TARGETDIR)/rpg
OBJDIR = build/obj/ARM64/Debug/rpg
DEFINES += -DDEBUG -DPLATFORM_DESKTOP -DGRAPHICS_API_OPENGL_33
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -Wshadow -g -std=c99 -Wno-deprecated-declarations
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -Wshadow -g -std=c++17 -Wno-deprecated-declarations
LIBS += bin/Debug/libraylib.a -framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreAudio -framework CoreVideo -framework AudioToolbox
LDDEPS += bin/Debug/libraylib.a
ALL_LDFLAGS += $(LDFLAGS)

else ifeq ($(config),release_x64)
TARGETDIR = bin/Release
TARGET = $(TARGETDIR)/rpg
OBJDIR = build/obj/x64/Release/rpg
DEFINES += -DNDEBUG -DPLATFORM_DESKTOP -DGRAPHICS_API_OPENGL_33
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -Wshadow -O2 -std=c99 -Wno-deprecated-declarations
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -Wshadow -O2 -std=c++17 -Wno-deprecated-declarations
LIBS += bin/Release/libraylib.a -framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreAudio -framework CoreVideo -framework AudioToolbox
LDDEPS += bin/Release/libraylib.a
ALL_LDFLAGS += $(LDFLAGS) -m64

else ifeq ($(config),release_x86)
TARGETDIR = bin/Release
TARGET = $(TARGETDIR)/rpg
OBJDIR = build/obj/x86/Release/rpg
DEFINES += -DNDEBUG -DPLATFORM_DESKTOP -DGRAPHICS_API_OPENGL_33
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -Wshadow -O2 -std=c99 -Wno-deprecated-declarations
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -Wshadow -O2 -std=c++17 -Wno-deprecated-declarations
LIBS += bin/Release/libraylib.a -framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreAudio -framework CoreVideo -framework AudioToolbox
LDDEPS += bin/Release/libraylib.a
ALL_LDFLAGS += $(LDFLAGS) -m32

else ifeq ($(config),release_arm64)
TARGETDIR = bin/Release
TARGET = $(TARGETDIR)/rpg
OBJDIR = build/obj/ARM64/Release/rpg
DEFINES += -DNDEBUG -DPLATFORM_DESKTOP -DGRAPHICS_API_OPENGL_33
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -Wshadow -O2 -std=c99 -Wno-deprecated-declarations
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -Wshadow -O2 -std=c++17 -Wno-deprecated-declarations
LIBS += bin/Release/libraylib.a -framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreAudio -framework CoreVideo -framework AudioToolbox
LDDEPS += bin/Release/libraylib.a
ALL_LDFLAGS += $(LDFLAGS)

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

SOURCES := $(shell find src -name '*.cpp')

OBJECTS := $(SOURCES:src/%.cpp=$(OBJDIR)/%.o)
GENERATED := $(OBJECTS)

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking rpg
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning rpg
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) rmdiq $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdiq $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


# File Rules
# #############################################

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	@echo Compiling $<
	$(SILENT) mkdir -p $(dir $@)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif

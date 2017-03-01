# Attempt to load a config.make file.
# If none is found, project defaults in config.project.make will be used.
ifneq ($(wildcard config.make),)
	include config.make
endif

# make sure the the OF_ROOT location is defined
ifndef OF_ROOT
# This for path project in myApp or exemples
#	OF_ROOT=$(realpath ../../..)
# But now
	OF_ROOT=$(realpath ../../eclipse/of_v0.9.8_android_release/of_v0.9.8_android_release)
endif

# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk

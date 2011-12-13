#########################################################
#Initalize the enviornment				#
#This build is not currently using the 'packaging' tool,#
#but its there just in case.				#
#########################################################
env = Environment(tools=['default', 'packaging'])

#########################################
#build the executable 'helloworld'	#
#put it in './outputs'			#
#########################################
hello = env.Program(target = './outputs/helloworld', source = ["./c-files/helloworld.c"])
#########################################################
#Currently commented out, becuase its not working	#
#with the shared library				#
#########################################		#
##build the executable 'ma'		#		#
##put it in './outputs'			#		#
##link it with 'libcma.so'		#		#
#########################################		#
#ma = env.Program(	target = './outputs/ma',	#
#			source = ['./c-files/ma.c'], 	#
#			LIBS = ['cma'], 		#
#			LIBPATH ='./LIBS'		#
#			)				#
#########################################################

#########################################
#build the executable 'ma'		#
#put it in './outputs'			#
#link it with 'libcma.a'		#
#########################################
ma = env.Program(	target = ['./outputs/ma'], 
			source = ['./c-files/ma.c', './LIBS/libcma.a'], 
			)

#########################################################################
#build the cma shared libray. and put output in ./LIBS folder.		#
#!!NOTE!! the prefix and extension can vary from platform to platform	#
#									#
#This isnt working for some reason. compiles and links fine, but when	#
#you try to run the 'ma' executable, it says cant find shared		#
#library 'libcma.so'.  All gcc compiler flags look correct,and libcma.so#
#is in the correct directory.						#
#########################################################################
lib_target = "./LIBS/cma"
lib_sources = ["./c-files/cma.c"]
env.SharedLibrary(target = lib_target, source = lib_sources)

#########################################################
#Testing using a static library to get 'ma' working.	#
#Should put a static lib in ./LIBS			#
#output will be: libcma.a (posix), or cma.lib(windows)	#
#########################################################

env.StaticLibrary(target = ['./LIBS/cma'], source = ['./c-files/cma.c'])

#################################################################	
#this is the "InstallAs" method. need to look into this more."	#
#################################################################

#env.InstallAs(	target = ['./programs/ma', './helloworld'],
#             	source = ['ma.o', './outputs/helloworld']
#		)

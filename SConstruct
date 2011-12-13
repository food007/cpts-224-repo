
#Initalize the enviornment
env = Environment()

#build the executable "helloworld"
env.Program(target = 'helloworld', source = ["helloworld.c"])

#build the cma shared libray.
#!!NOTE!! the prefix and extension can vary from platform to platform
lib_target = "cma"
lib_sources = ["cma.c"]
env.SharedLibrary(target = lib_target, source = lib_sources)


#this is the "install" method. need to look into this more."
hello = env.Program(source = ["helloworld.c"], target = "helloworld")
env.Install("./hello", hello)

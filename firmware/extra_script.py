import os
Import("env")

# include toolchain paths in compile_commands
env.Replace(COMPILATIONDB_INCLUDE_TOOLCHAIN=True)

# write compile_commands.json to project root
env.Replace(COMPILATIONDB_PATH="compile_commands.json")

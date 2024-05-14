Import("env")

import os

def after_test(source, target, env):
    os.system('gcovr -r . --xml -o coverage.xml')

env.AddPostAction("test", after_test)

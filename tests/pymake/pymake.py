from os.path import isfile
from subprocess import check_output, call


class PyMake:
    def __init__(self, makefile_path):
        if isfile(makefile_path) is False:
            raise OSError("Not a valid path : %s" % makefile_path)
        self.makefile_path = makefile_path
        self.makefile_dir = makefile_path.split("Makefile")[0]

    def __repr__(self):
        with open(self.makefile_path, "r") as makefile:
            return makefile.read()
        
    def make(self, string_arg=None, verbose=False):
        cmd = ["make", "__arg", "-C", self.makefile_dir]
        if string_arg is None:
            cmd.pop(1)
        elif type(string_arg) is str:
            cmd[1] = string_arg
        else:
            raise AttributeError("not a string arg")
        if verbose is False:
            check_output(cmd)
        elif verbose is True:
            call(cmd)
        else:
            raise AttributeError("Only support bool type")
        
    def make_re(self):
        self.make("re")
    
    def make_fclean(self):
        self.make("fclean")
        
    def make_clean(self):
        self.make("clean")
# **********************************************************************************
#   FileName:
#       chimera_format.py
#
#   Description:
#       Runs custom clang-formatting options on the project
#
#   Usage Examples:
#       python chimera_format.py
#
#   2019 | Brandon Braun | brandonbraun653@gmail.com
# **********************************************************************************

import os
import sys
import subprocess

from lib.CommonTools.swqa.clangformat import ClangFormatter


this_dir = os.path.join(os.path.dirname(__file__))
format_file = os.path.join(this_dir, 'chimera_clangformat.json')
clang_format = 'clang-format.exe'
working_dir = this_dir

llvm_download = "http://releases.llvm.org/download.html"


def run_clang_format():
    """
    Executes clang formatting on the Thor project

    :return: Process status code
    :rtype: int
    """

    rc = subprocess.call(['where', clang_format])
    if rc != 0:
        print("LLVM (which provides clang-format) is not installed on the system path. Please download\nit from here: "
              "{}".format(llvm_download))

    cf = ClangFormatter(project_file=format_file, working_dir=working_dir, clang_format_exe=clang_format)
    return cf.execute()


if __name__ == "__main__":
    sys.exit(run_clang_format())

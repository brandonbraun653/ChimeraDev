# **********************************************************************************
#   FileName:
#       run_tests.py
#
#   Description:
#       Runs all the tests associated with Chimera. To be used in conjunction with
#       boost.build targets as the executables this script searches for are built
#       by them.
#
#       Currently this is a very quick writeup just to get the system working. It is
#       by no means scalable or very robust.
#
#   Usage Examples:
#       N/A
#
#   2019 | Brandon Braun | brandonbraun653@gmail.com
# **********************************************************************************

import os
import glob
import argparse
import subprocess


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--root', help="Specifies the root directory to search for both source files "
                                       "and .gcda files. Must be high enough to encompass both.")
    parser.add_argument('--output', help='Output directory to store the coverage files')
    parser.add_argument('--exe', help='Directory to recursively search for test executables')
    parser.add_argument('--exclude', help='Directory to exclude in search for coverage files')

    args = parser.parse_args()

    # ---------------------------------------------
    # Make sure the output directory exists
    # ---------------------------------------------
    output_abs_path = os.path.abspath(args.output)
    root_abs_path = os.path.abspath(args.root)
    exclude_abs_path = os.path.abspath(args.exclude)

    if not os.path.isdir(output_abs_path):
        os.makedirs(output_abs_path)

    if not os.path.isdir(root_abs_path):
        raise RuntimeError("Root directory is invalid")

    if not os.path.isdir(exclude_abs_path):
        raise RuntimeError("Exclude directory is invalid")

    # ---------------------------------------------
    # Grab all our tests
    # ---------------------------------------------
    exe_search_path = os.path.abspath(args.exe)
    match_pattern = os.path.join(exe_search_path, '**', '*.exe')
    executables = glob.glob(match_pattern, recursive=True)

    # ---------------------------------------------
    # Run the tests and output their coverage files
    # into the same directory
    # ---------------------------------------------
    my_env = os.environ.copy()
    for exe in executables:
        # my_env["GCOV_PREFIX"] = os.path.dirname(exe)
        # my_env["GCOV_PREFIX_STRIP"] = '0'
        command = "{}".format(exe)
        subprocess.Popen(command, env=my_env).wait()

    # ---------------------------------------------
    # Generate the coverage reports. The root directory
    # needs to be high enough to find both the source files
    # as well as the coverage instrumentation results (.gcda)
    # ---------------------------------------------
    title = "ChimeraCoverage"

    html_command = ['gcovr', '-r', root_abs_path, '-e', exclude_abs_path,
                    '--html-title', title, '--html-details', '-o',
                    os.path.join(output_abs_path, 'cov.html')]
    gcovr_html = ' '.join(html_command)

    xml_command = ['gcovr', '-r', root_abs_path, '-e', exclude_abs_path,
                   '-x', '-o', os.path.join(output_abs_path, 'cov.xml')]
    gcovr_xml = ' '.join(xml_command)

    gcovr_html = gcovr_html.replace('\\', '/')
    gcovr_xml = gcovr_xml.replace('\\', '/')

    subprocess.Popen(gcovr_html, env=my_env).wait()
    subprocess.Popen(gcovr_xml, env=my_env).wait()


if __name__ == "__main__":
    main()

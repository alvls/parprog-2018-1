import subprocess

# run writer
subprocess.check_call(["py", "-2.7", "writer.py"])

# run gaussian filter program
subprocess.check_call(["./GaussianOpenMP.exe", # execution path
                       "1", # count of threads
                       "1" # filter radius
                     ])

# show result
subprocess.check_call(["py", "-2.7", "reader.py"])

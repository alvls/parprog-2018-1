import subprocess

# run writer
subprocess.check_call(["py", # execution path
                       "-2.7", # count of threads
                       "writer.py", # filter radius
                     ])

# run gaussian filter program
subprocess.check_call(["./GaussianOpenMP.exe", # execution path
                       "1", # count of threads
                       "1" # filter radius
                     ])

# show result
subprocess.check_call(["py", # execution path
                       "-2.7", # count of threads
                       "reader.py", # filter radius
                     ])

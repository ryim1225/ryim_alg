import os
import sys
import platform

Build_flag  = ""


def getCurrentWorkspace():
    path = sys.path
    print(path[0])
    return path[0]

def createFolder(path):
    if os.path.exists(path):
        print("the folder exists")
    else:
        os.makedirs(path)


def doWorkOne(dirName):
    root_path = getCurrentWorkspace()
    p = platform.architecture()
    bits = p[0][0:2]
    print(bits)
    if "ryimll" == dirName:
        build_path = root_path + "/" + dirName + "/build_" + bits
    else:
        build_path = root_path + "/RyimAlg_samples/" + dirName + "/build_" + bits
    print(build_path)
    createFolder(build_path)
    os.chdir(build_path)
    buid_cmd = "cmake .. -DCMAKE_BUILD_TYPE=" + sys.argv[2] + " && make 2> makeinfo.txt "
    print(buid_cmd)
    os.system(buid_cmd)
    makeinfo_path = build_path + "/makeinfo.txt"
    if os.path.exists(makeinfo_path):
        with open(makeinfo_path, "r") as f:
            for line in f.readlines():
                if line.find("fatal error:"):
                    exit(1)


def doWorkAll():
    dirNames = os.listdir(getCurrentWorkspace() + "/RyimAlg_samples")
    print(dirNames)
    #dirNames = ["ryimll","utility", "rAlgorithms_sort_sample", "rArrayList_sample",
    #"rAlgorithms_substring_sample", "rHeap_sample", "rGraph_sample", "rTree_sample"]
    for name in dirNames:
        doWorkOne(name)

if __name__ == "__main__":
    print(sys.argv)
    if len(sys.argv) != 3:
        print("build.py [model name] [Debug/Release]")
        exit(1)
    if sys.argv[2] != "Debug" and sys.argv[2] != "Release":
        print("build.py [model name] [Debug/Release]")
        exit(1)


    if "all" == str(sys.argv[1]):
        doWorkAll()
    else:
        doWorkOne(sys.argv[1])
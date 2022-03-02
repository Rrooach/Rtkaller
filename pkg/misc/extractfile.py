import os

file_object = open("patch-5.9-rc2-rt1.patch", "rw")


fileList = []


try:
    for line in file_object:
        if "diff" in line: 
            start = line.find("a/")
            end = line.find(" b/") 
            tmp = line[start+1: end]
            fileList.append(tmp)
finally:
    file_object.close()


files = []


for lists in fileList: 
    if ".c" in lists:
        files.append(lists)
    if ".h" in lists:
        files.append(lists)  


for f in files[:]: 
    if "arch/" in f:
        files.remove(f)
    # elif "include/" in f:    
    #     files.remove(f) 
    elif "kernel" in f:
        files.remove(f) 
    elif "efi" in f:
        files.remove(f) 
    elif "boot" in f:
        files.remove(f) 
    elif ".h" in f:
        files.remove(f) 
    elif "mm" in f:
        files.remove(f) 


add_to_makefile = []


for lists in files:
    print(lists)
    start = lists.rfind("/")
    end = lists.find(".")
    file_path = lists[1:start]  
    path_Makefile = file_path+"/Makefile"
    print(path_Makefile)
    file = lists[start+1:end]
    kcov = "KCOV_INSTRUMENT_" + file + ".o := y\n"
    ff = open(path_Makefile, "ar+")
    ff.write(kcov)
    ff.close()


black_list = []


os.system("grep -rn KCOV_INSTRUMENT > blackList")
block_object = open("blackList", "rw")


try:
    for line in block_object:
        end1 = line.find(":") - 9
        str1 = line[:end1]
        start = line.find("MENT_")
        end2 = line.find(".o")
        str2 = line[start:end2]
        strr = str1 + "/" + str2 + ".c"
        black_list.append(strr)
finally:
    block_object.close()


for ll in black_list:
    print(ll)

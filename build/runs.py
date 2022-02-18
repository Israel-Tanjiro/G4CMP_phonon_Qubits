import os
i=0
z=0
for z in range(0,4):
    for i in range(0,2):
        print(i)
        a_file = open("vis2.mac", "r")
        list_of_lines = a_file.readlines()
        j=0.1*i
        jj=0.0036*z
        list_of_lines[1] = "/gun/position %s 0 %s cm\n" %(j,jj)
        a_file = open("vis2.mac", "w")
        a_file.writelines(list_of_lines)
        a_file.close()
        os.system("./g4cmpPhonon ../vis2.mac")
        b_file = open("phonon_hits.txt","r")
        list_of_lines2 = b_file.readlines()
        list_of_lines2=list_of_lines2[:-1]
        name = "phonon_hits_%d_0_%d.txt" %(i,z)
        print(name)
        b_file=open(name,"w")
        b_file.writelines(list_of_lines2)
        b_file.close()
        os.system("rm phonon_hits.txt")

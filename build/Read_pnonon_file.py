import csv
name ="Phonons_impacts.txt"
b_file=open(name,"w")

for IS in range (0,3):
    names="phonon_hits_0_0_%d.txt" %IS
    with open(names) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        list_of_column_names = []

        # loop to iterate through the rows of csv
        for row in csv_reader:

            # adding the first row
            list_of_column_names.append(row)

            # breaking the loop after the
            # first iteration itself
            break




        x=[]
        y=[]
        names=[]
        Energy_Initial_e=[]
        i=0
        z=[]# the final position

        for lines in csv_reader:
            #print(lines[9])
            i=1+i
            #print(i)
            #Energy_Initial_e.append(float(lines[4]))
            x.append(float(lines[11])*100)
            y.append(float(lines[12])*100)
            names.append(lines[3])
            z.append(float(lines[13])*100)#Converting to cm from meter
    print("List of column names : ",list_of_column_names[0][11])


    #print(x)
    #Print the names of the LogicalSurfacests
    #x.remove('Energy_Deposited')
    #print(x)
    list_of_floatsF = [] # The only tryef
    list_of_floatsS = []
    list_of_floatsL = []
    list_of_floatsZ = []
    list_of_floatsE = []
    #Adding only the transverse photon
    A="phononTF"

    B="phononTS"
    C="phononL"
    D='G4CMPDriftElectron'
    E='G4CMPDriftHole'
    import numpy as geek
    i=0
    #Counting the number of photons
    Ts=0
    L=0
    Tf=0
    Elec=0
    i=0
    j=0
    Hole=0
    print(x[0])
    for i in range(len(x)):
        if x[i]<0.007 and x[i]>-0.007 :
            if z[i]>0:
                if y[i]<0.007 and y[i]>-0.007:
                    if names[i]==A:
                        Tf=Tf+1
                    if names[i]==B:
                        Ts=Ts+1

                    if names[i]==C:
                        L=L+1


                    if names[i]==D:
                        Elec=Elec+1

                    if names[i]==E:
                        Hole=Hole+1



    print(j)
    print(len(x))










    #print(list_of_floats)
    # import matplotlib.pyplot as plt
    # import numpy as np

    print("The number of phononTS is",Ts)
    print("The number of phononTF is",Tf)
    print("The number of phononL is",L)
    print("G4CMPDriftElectron",Elec)
    print("G4CMPDriftHole",Hole)

    b_file.write(""+str(Ts))
    b_file.write("\t" +str(Tf))
    b_file.write("\t" +str(Tf))
    b_file.write("\t" +str(L))
    b_file.write("\t" +str(Elec))
    b_file.write("\t" +str(Hole))
    b_file.write("\n")

b_file.close()

# #
# a = np.hstack(list_of_floatsZ)
# _ = plt.hist(a, bins='auto', color = "green")
# plt.xlabel('Start Energ [eV]');
# plt.show()
#
# mean = sum(list_of_floatsE) / len(list_of_floatsE)
# print("The mean Energy is ",mean)

#Saving on a File all the Simulations The numbers of phonon as a function of the Distance and the Mean Energy of the Electrons as the number of electrons


# b = np.hstack(list_of_floatsS)
# _ = plt.hist(b, bins='auto',color = "blue")
# plt.xlabel('Energy Deposited [eV]');
# plt.show()
# c = np.hstack(list_of_floatsL)
# _ = plt.hist(c, bins='auto',color = "Red")
# plt.xlabel('Energy Deposited [eV]');
# plt.show()


# z = np.hstack(list_of_floatsZ,)
# _ = plt.hist(z, bins='auto')
# plt.show()

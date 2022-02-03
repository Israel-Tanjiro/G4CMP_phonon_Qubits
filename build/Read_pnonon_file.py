import csv

with open('phonon_hits.txt') as csv_file:
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
    names=[]
    Energy_Initial_e=[]
    i=0
    z=[]# the final position

    for lines in csv_reader:
        #print(lines[9])
        #i=1+i
        #print(i)
        Energy_Initial_e.append(lines[4])
        x.append(lines[9])
        names.append(lines[3])
        z.append(lines[13])
print("List of column names : ",list_of_column_names[0][13])
#print(x)
#Print the names of the lists
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

i=0
#Counting the number of photons
Ts=0
L=0
Tf=0
Elec=0
for item in x:

    if names[i]==A:
        #print(names[i])
        Tf=Tf+1
        list_of_floatsF.append(float(item))
    if names[i]==B:
        #print(names[i])
        Ts=Ts+1
        list_of_floatsS.append(float(item))
    if names[i]==C:
        #print(names[i])
        L=L+1
        list_of_floatsL.append(float(item))
    if names[i]==D:
        Elec=Elec+1
    i=i+1
        #list_of_floatsE.append(float(item))


i=0
for item  in Energy_Initial_e:
    if names[i]==D:
        list_of_floatsE.append(float(item))
    i=i+1

for item in z:
    list_of_floatsZ.append(float(item))


#print(list_of_floats)
import matplotlib.pyplot as plt
import numpy as np

print("The number of phononTS is",Ts)
print("The number of phononTF is",Tf)
print("The number of phononL is",L)
print("G4CMPDriftElectron",Elec)
#
a = np.hstack(list_of_floatsE)
_ = plt.hist(a, bins='auto', color = "green")
plt.xlabel('Start Energ [eV]');
plt.show()

mean = sum(list_of_floatsE) / len(list_of_floatsE)
print("The mean Energy is ",mean)

#Saving on a File all the Simulations The numbers of phonon as a function of the Distance and the Mean Energy of the Electrons as the number of electrons


# b = np.hstack(list_of_floatsS)
# _ = plt.hist(b, bins='auto',color = "blue")
# plt.xlabel('Energy Deposited [eV]');
# plt.show()
# c = np.hstack(list_of_floatsL)
# _ = plt.hist(c, bins='auto',color = "Red")
# plt.xlabel('Energy Deposited [eV]');
# plt.show()


z = np.hstack(list_of_floatsZ,)
_ = plt.hist(z, bins='auto')
plt.show()

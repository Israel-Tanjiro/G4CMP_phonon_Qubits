import csv
name ="Phonons_impacts_1.txt"
b_file=open(name,"a")
names="phonon_hits_0_0_0.txt"
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
    Energy_Deposited=[]
    Start_Energy=[]
    i=0
    z=[]# the final position

    for lines in csv_reader:
        #print(lines[9])
        i=1+i
        #print(i)
        #Energy_Initial_e.append(float(lines[4]))

        Start_Energy.append(float(lines[4])*100)
        Energy_Deposited.append(float(lines[9]))
        x.append(float(lines[11])*100)
        y.append(float(lines[12])*100)
        names.append(lines[3])
        z.append(float(lines[13])*100)#Converting to cm from meter
print("List of column names : ",list_of_column_names[0][4])


#print(x)
#Print the names of the LogicalSurfacests
#x.remove('Energy_Deposited')
#print(x)
ETF = [] # The only tryef
ETS = []
EL = []
Ee = []
EH = []
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
                    ETF.append(Energy_Deposited[i])
                if names[i]==B:
                    Ts=Ts+1
                    ETS.append(Energy_Deposited[i])

                if names[i]==C:
                    L=L+1
                    EL.append(Energy_Deposited[i])


                if names[i]==D:
                    Elec=Elec+1
                    Ee.append(Energy_Deposited[i])

                if names[i]==E:
                    Hole=Hole+1
                    EH.append(Energy_Deposited[i])



#print(ETF)


#

import matplotlib.pyplot as plt
import numpy as np




if len(ETF)!=0 :
    meanTF= sum(ETF) / len(ETF)
else:
    meanTF=0


if len(EL)!=0 :
    meanL= sum(EL) / len(EL)
else:
    meanL=0

if len(ETS)!=0 :
    meanTS= sum(ETS) / len(ETS)
else:
    meanTS=0


if len(Ee)!=0:
    meanee= sum(Ee) / len(Ee)
    meanH= sum(EH) / len(EH)
else :
    meanee=0
    meanH=0

#print("The mean Energy is ",meanTS)
#print("The mean Energy is ",meanTF)
#print("The mean Energy is ",meanL)
#print("The mean Energy is ",meanee)
#print("The mean Energy is ",meanH)







#print(list_of_floats)


print("The number of phononTS is",Ts)
print("The number of phononTF is",Tf)
print("The number of phononL is",L)
print("G4CMPDriftElectron",Elec)
print("G4CMPDriftHole",Hole)

b_file.write(""+str(Ts))
b_file.write("\t" +str(Tf))
#b_file.write("\t" +str(Tf))
b_file.write("\t" +str(L))
b_file.write("\t" +str(Elec))
b_file.write("\t" +str(Hole))

b_file.write("\t" +str(meanTS))
b_file.write("\t" +str(meanTF))
b_file.write("\t" +str(meanL))
b_file.write("\t" +str(meanee))
b_file.write("\t" +str(meanH))
b_file.write("\n")

b_file.close()

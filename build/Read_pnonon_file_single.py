import csv
name ="phonons_impacts.txt"
Radial_posTS="Position_detector_TS.txt"
Radial_posTF="Position_detector_TF.txt"
Radial_posTL="Position_detector_TL.txt"
Radial_posE="Position_detector_E.txt"
Radial_posH="Position_detector_H.txt"
Energy_Analysis="Energy_Analysis.txt"
Radial_posTS_Nb="Position_detector_TS_Nb.txt"
Radial_posTF_Nb="Position_detector_TF_Nb.txt"
Radial_posTL_Nb="Position_detector_TL_Nb.txt"
Radial_posE_Nb="Position_detector_E_Nb.txt"
Radial_posH_Nb="Position_detector_H_Nb.txt"
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

        Start_Energy.append(float(lines[4]))
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
##
ETF_Nb = [] # The only tryef
ETS_Nb = []
EL_Nb = []
Ee_Nb = []
EH_Nb = []

#Adding only the transverse photon
A="phononTF"

B="phononTS"
C="phononL"
D='G4CMPDriftElectron'
E='G4CMPDriftHole'
#import numpy as geek
i=0
#Counting the number of photons
Ts=0
L=0
Tf=0
Elec=0
i=0
j=0
Hole=0
#Counting the number of phonon in the Nb
Ts_Nb=0
L_Nb=0
Tf_Nb=0
Elec_Nb=0
Hole_Nb=0
#Position Distribution of the Electrones and Holes
xL=[]
yL=[]
xTF=[]
yTF=[]
xTS=[]
yTS=[]
xe=[]
ye=[]
xH=[]
yH=[]

#Position Distribution of the Electrons and Holes in the Nb Region
xL_Nb=[]
yL_Nb=[]
xTF_Nb=[]
yTF_Nb=[]
xTS_Nb=[]
yTS_Nb=[]
xe_Nb=[]
ye_Nb=[]
xH_Nb=[]
yH_Nb=[]


print(x[0])
for i in range(len(x)):
    if x[i]<0.007 and x[i]>-0.007 :
        if z[i]>0:
            if y[i]<0.007 and y[i]>-0.007:
                if names[i]==A:
                    Tf=Tf+1
                    ETF.append(Energy_Deposited[i])
                    xTF.append(x[i])
                    yTF.append(y[i])
                if names[i]==B:
                    Ts=Ts+1
                    ETS.append(Energy_Deposited[i])
                    xTS.append(x[i])
                    yTS.append(y[i])

                if names[i]==C:
                    L=L+1
                    EL.append(Energy_Deposited[i])
                    xL.append(x[i])
                    yL.append(y[i])


                if names[i]==D:
                    Elec=Elec+1
                    Ee.append(Energy_Deposited[i])
                    xe.append(x[i])
                    ye.append(y[i])

                if names[i]==E:
                    Hole=Hole+1
                    EH.append(Energy_Deposited[i])
                    xH.append(x[i])
                    yH.append(y[i])
i=0
j=0
for i in range(len(x)):
    if x[i]>0.0 or x[i]<-0.0000001:
        if z[i]>0:
            if y[i]>0.0 or y[i]<-0.0000001 :
                if names[i]==A:
                    Tf_Nb=Tf_Nb+1
                    ETF_Nb.append(Energy_Deposited[i])
                    xTF_Nb.append(x[i])
                    yTF_Nb.append(y[i])
                if names[i]==B:
                    Ts_Nb=Ts_Nb+1
                    ETS_Nb.append(Energy_Deposited[i])
                    xTS_Nb.append(x[i])
                    yTS_Nb.append(y[i])

                if names[i]==C:
                    L_Nb=L_Nb+1
                    EL_Nb.append(Energy_Deposited[i])
                    xL_Nb.append(x[i])
                    yL_Nb.append(y[i])


                if names[i]==D:
                    Elec_Nb=Elec_Nb+1
                    EL_Nb.append(Energy_Deposited[i])
                    xe_Nb.append(x[i])
                    ye_Nb.append(y[i])

                if names[i]==E:
                    Hole_Nb=Hole_Nb+1
                    EH_Nb.append(Energy_Deposited[i])
                    xH_Nb.append(x[i])
                    yH_Nb.append(y[i])



#print(ETF)


#

#import matplotlib.pyplot as plt
#import numpy as np




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


print("The number of phononTS in Nb",Ts_Nb)
print("The number of phononTF in Nb",Tf_Nb)
print("The number of phononL in Nb",L_Nb)
print("G4CMPDriftElectron in Nb",Elec_Nb)
print("G4CMPDriftHole in Nb",Hole_Nb)

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

zip(xTS,yTS)
zip(xTF,yTF)
zip(xL,yL)
zip(xe,ye)
zip(xH,yH)

import csv
with open(Radial_posTS, 'a') as f:
     writer = csv.writer(f, delimiter='\t')
     writer.writerows(zip(xTS,yTS))

with open(Radial_posTF, 'a') as f:
     writer = csv.writer(f, delimiter='\t')
     writer.writerows(zip(xTF,yTF))

with open(Radial_posTL, 'a') as f:
     writer = csv.writer(f, delimiter='\t')
     writer.writerows(zip(xL,yL))

with open(Radial_posE, 'a') as f:
     writer = csv.writer(f, delimiter='\t')
     writer.writerows(zip(xe,ye))

with open(Radial_posH, 'a') as f:
     writer = csv.writer(f, delimiter='\t')
     writer.writerows(zip(xH,yH))


#Nb paart


zip(xTS_Nb,yTS_Nb)
zip(xTF_Nb,yTF_Nb)
zip(xL_Nb,yL_Nb)
zip(xe_Nb,ye_Nb)
zip(xH_Nb,yH_Nb)

import csv
with open(Radial_posTS_Nb, 'a') as f:
     writer = csv.writer(f, delimiter='\t')
     writer.writerows(zip(xTS_Nb,yTS_Nb))

with open(Radial_posTF_Nb, 'a') as f:
     writer = csv.writer(f, delimiter='\t')
     writer.writerows(zip(xTF_Nb,yTF_Nb))

with open(Radial_posTL_Nb, 'a') as f:
     writer = csv.writer(f, delimiter='\t')
     writer.writerows(zip(xL_Nb,yL_Nb))

with open(Radial_posE_Nb, 'a') as f:
     writer = csv.writer(f, delimiter='\t')
     writer.writerows(zip(xe_Nb,ye_Nb))

with open(Radial_posH_Nb, 'a') as f:
     writer = csv.writer(f, delimiter='\t')
     writer.writerows(zip(xH_Nb,yH_Nb))

with open(Energy_Analysis, 'a') as f:
     writer = csv.writer(f, delimiter='\t')
     writer.writerows(zip(Start_Energy,Energy_Deposited))


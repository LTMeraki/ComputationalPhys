# Python 3.10.6.
# Author: Laura Carolina Triana Martínez. 20202107004.la
# Title: example2.py

# This program imports an excel file with a table of position and time, performs numerical differentiation to find the velocities and accelerations and exports a new excel file with the generated table.

# Import mathematics and data management libraries.
import matplotlib.pyplot as plt
from tabulate import *
import pandas as pd
import glob


# With glob it searches for the first .xlsx file that is in the folder.
dataexcel = glob.glob("*.xlsx")[0]
print(dataexcel)

# The excel file which must contain the position and velocity data is imported.
dfexcel = pd.read_excel(dataexcel)

# The data for each column is attached in a list for time and position.
times = list(dfexcel["Tiempo"])
positions = list(dfexcel["Posición"])

# Forward differentiation is performed for each of the time and position data.
velocities  = []
for n in range(len(times)-1):
    v = (positions[n+1]-positions[n])/(times[n+1]-times[n])
    velocities.append(v)
velocities.insert(0,0)

# Forward differentiation is performed for each of the time and velocity data.
accelerations = []
for n in range(len(times)-2):   
    a = (velocities[n+1]-velocities[n])/(times[n+1]-times[n])
    accelerations.append(a)
accelerations.insert(0,0)
accelerations.insert(len(accelerations),0)


# A new data frame is made for the found velocity and acceleration columns and concatenated with the original data frame.
dfnuevo = pd.DataFrame({"Velocidad": velocities, "Aceleración": accelerations})
dfexcel2= pd.concat([dfexcel, dfnuevo], axis=1)

# The data frame is exported in a new file with extension .xlsx.
dfexcel2.to_excel("dfexcel2.xlsx", index=False)
finaltable = tabulate(dfexcel2, headers = 'keys', tablefmt = 'fancy_grid', showindex=False, numalign='center')
archivo = open("finaltable.txt","w")
archivo.write(finaltable)
archivo.close()


print("")
print("The table with velocities and accelerations is as follows: ")
print("")
print(finaltable)

# GRAFICAS, MULTIPLES OPCIONES DE EXTENSIONES, ELEGIR ARCHIVO, MAKEFILE CONSTRUCTOR PARA GENERAR GRAFICAS. C++
# DEBUGGER


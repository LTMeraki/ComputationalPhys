# Python 3.10.6
# Author: Laura Carolina Triana Martínez
# Title: differentiation2.py

velocity = []
acceleration = []

positions = [0, 0.61, 0.18, 2.13, 3.63, 6.05, 10.02, 16.54, 27.29] # Remplace los valores que considere deba tomar el vector del tiempos
times= [0.0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4] # Remplace los valores que considere deba tomar el vector de posiciones


 d = int(input("How many data pairs?: "))
 print()

 for i in range (d):
     t = float(input("Enter a time data: "))
    p = float(input("Enter a position data: "))
     time.append(t)
     position.append(p)


for n in range(d-1):
    v = (position[n+1]-position[n])/(time[n+1]-time[n])
    velocity.append(v)

for n in range(d-2):
    a = (velocity[n+1]-velocity[n])/(time[n+1]-time[n])
    acceleration.append(a)

print()
print("Velocities: ")
print(velocity)
print()
print("Accelerations: ")
print(acceleration)


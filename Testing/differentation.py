time = []
position = []
velocityd = []
velocityc = []
velocitya = []

a = int(input("How many data pairs?: "))

for i in range (a):
    t = float(input("Enter a time data: "))
    p = float(input("Enter a position data: "))
    time.append(t)
    position.append(p)

print("Choose the method of numerical ifferentiation")
print("")
print("a. Forward \nb. Backward \nc. Central ")
decision = input()

if (decision == a):
    for n in range(a-1):
        v = (position[n+1]-position[n])/(time[n+1]-time[n])
        velocityd.append(v)
        print(velocityd)

elif (decision == b):
    for o in range(1, a):
        va = (position[o]-position[o-1])/(time[o]-time[o-1])
        velocitya.append(va)
        print(velocitya)

elif (decision == c):
    for m in range(1, a-1):
        vc = (position[m+1]-position[m-1])/(time[m+1]-time[m-1])
        velocityc.append(vc)
        print(velocityc)

else:
    exit(0)






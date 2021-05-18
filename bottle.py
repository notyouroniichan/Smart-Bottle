from datetime import datetime, timedelta
import copy
from playsound import playsound

global z
x = []


def sensory_input():
    y = int(input("enter the value"))
    if y == 1:
        t = datetime.now() + timedelta(seconds=5)
        while y == 1:
            if datetime.now() >= t:
                break
            else:

                f = datetime.now()
                g = f.strftime("%d/%m/%Y %H:%M:%S")
                x.append([g, f])
                y = int(input('enter value'))
        return x
    else:
        y = 0


sensory_input()
u_l = copy.deepcopy(x)
print(u_l)


def reset_1():
    z = int(input("Enter key value"))
    if z == 1:
        u_l.clear()
        sensory_input()
    else:
        return u_l


reset_1()


def advance():
    for i in range(len(u_l)):
        u_l[i][1] = u_l[i][1] + timedelta(seconds=10)
        u_l[i][0] = u_l[i][1].strftime("%d/%m/%Y %H:%M:%S")
    return u_l


advance()
print(u_l)
print(len(u_l))


def alarm():
    i = 0
    j = len(u_l)
    while i < j:
        c = datetime.now()
        d = c.strftime('%d/%m/%Y %H:%M:%S')
        if u_l[i][0] == d:
            #playsound("C:/Windows/Media/Alarm01.wav")
            print("hi")
            i = i + 1


alarm()

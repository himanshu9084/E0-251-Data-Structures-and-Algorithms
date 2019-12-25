#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt

print('Enter for sp plot-1  dn plot-2')
op=input()

if(op==1):
     fp=open('sp_plot.txt','r')
     X,Y,Z=np.loadtxt(fp,delimiter=' ',usecols=[0,1,2],unpack=True)
     fp.close()
elif(op==2):
     fp=open('dn_plot.txt','r')
     X,Y,Z=np.loadtxt(fp,delimiter=' ',usecols=[0,1,2],unpack=True)
     fp.close()
else:
     print('Wrong input')
     exit(0)

Y1=[]
Z1=[]
Y2=[]

for i in range(0,len(X)):
  if(X[i]==1):
      Y1.append(Y[i])
      Z1.append(Z[i])
  if(X[i]==2):
      Y2.append(Y[i])
     
#print(X1,X2,Y1,Y2)
		
plt.plot(Z1,Y1,color='blue',linewidth=2,marker='o',markerfacecolor='blue',label='floyd')
plt.plot(Z1,Y2,color='red',linewidth=2,marker='o',markerfacecolor='red',label='bfs')
#plt.plot(Y2,Z2)
if(op==1):
    plt.axis([500,20200,0,70000])
    plt.title('Sparse graph plot')
elif(op==2):
    plt.axis([500,20200,0,80000])
    plt.title('Dense graph plot')
plt.xlabel('Graph nodes')
plt.ylabel('Time taken(in seconds)')
plt.legend()
plt.show()


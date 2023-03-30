import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib.colors import ListedColormap, LinearSegmentedColormap


n_x = 200
n_y = 1
n_z = 200

_x = np.linspace(-10,10,n_x)
_y = 0 
_z = np.linspace(-10,10,n_z)

_xx, _yy, _zz = np.meshgrid(_x, _y, _z, indexing='ij')
c = np.array(np.arange(n_x*n_y*n_z, dtype = float).reshape(n_x,n_y,n_z))

c[int(n_x/4):int(n_x/2),:,:] = np.nan
print(c)
fig = plt.figure(figsize=(12, 5))
ax0 = fig.add_subplot(121, projection='3d')

ax0.scatter(_xx, _yy, _zz, c = c, marker = 's')
ax0.set_title('`alpha` OFF')
ax1 = fig.add_subplot(122, projection='3d')
ax1.set_title('`alpha` ON')

scat3d = ax1.scatter(_xx, _yy, _zz, c = c, 
                     marker = 's', alpha = 1)

plt.show()
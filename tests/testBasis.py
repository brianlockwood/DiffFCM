import sys
sys.path.append(r'./build/lib')
import basis_python as basis

import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator
import numpy as np

#customTypes.test()

# x = np.linspace(-1.0, 1.0, 100)
# y = np.linspace(-1.0, 1.0, 100)

# X, Y = np.meshgrid(x, y)
# Z = np.zeros_like(X)

# for p in range(9):
#     for i in range(x.shape[0]):
#         for j in range(y.shape[0]):
#             Z[i,j] = basis.eval2D(p, X[i,j], Y[i,j])

#     fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
    
#     surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
#                        linewidth=0, antialiased=False)

#     plt.show()

x = np.linspace(-1.0, 1.0, 2)
y = np.linspace(-1.0, 1.0, 2)
z = np.linspace(-1.0, 1.0, 2)

X, Y, Z = np.meshgrid(x, y, z)

for i in range(x.shape[0]):
    for j in range(y.shape[0]):
        for k in range(z.shape[0]):
            print(X[i,j,k], Y[i,j,k], Z[i,j,k])

data = np.zeros_like(X)

for p in range(8):
    for i in range(x.shape[0]):
        for j in range(y.shape[0]):
            for k in range(z.shape[0]):
               data[i,j,k] = basis.eval3D(p, X[i,j,k], Y[i,j,k], Z[i,j,k])

    kw = {
        'vmin': data.min(),
        'vmax': data.max(),
        'levels': np.linspace(data.min(), data.max(), 10),
    }

    fig = plt.figure(figsize=(5, 4))
    ax = fig.add_subplot(111, projection='3d')

    _ = ax.contourf(
        X[:, :, 0], Y[:, :, 0], data[:, :, 0],
        zdir='z', offset=-1, **kw
    )
    _ = ax.contourf(
        X[:, :, -1], Y[:, :, -1], data[:, :, -1],
        zdir='z', offset=1, **kw
    )
    _ = ax.contourf(
        X[0, :, :], data[0, :, :], Z[0, :, :],
        zdir='y', offset=-1, **kw
    )
    _ = ax.contourf(
        X[-1, :, :], data[-1, :, :], Z[-1, :, :],
        zdir='y', offset=1, **kw
    )
    _ = ax.contourf(
        data[:, 0, :], Y[:, 0, :], Z[:, 0, :],
        zdir='x', offset=-1, **kw
    )
    C = ax.contourf(
        data[:, -1, :], Y[:, -1, :], Z[:, -1, :],
        zdir='x', offset=1, **kw
    )
   
    # Set limits of the plot from coord limits
    xmin, xmax = X.min(), X.max()
    ymin, ymax = Y.min(), Y.max()
    zmin, zmax = Z.min(), Z.max()
    ax.set(xlim=[xmin, xmax], ylim=[ymin, ymax], zlim=[zmin, zmax])

    # Plot edges
    edges_kw = dict(color='0.4', linewidth=1, zorder=1e3)
    ax.plot([xmax, xmax], [ymin, ymax], [zmin, zmin], **edges_kw)
    ax.plot([xmin, xmin], [ymin, ymax], [zmin, zmin], **edges_kw)
    ax.plot([xmin, xmax], [ymin, ymin], [zmin, zmin], **edges_kw)
    ax.plot([xmin, xmax], [ymax, ymax], [zmin, zmin], **edges_kw)

    ax.plot([xmax, xmax], [ymin, ymax], [zmax, zmax], **edges_kw)
    ax.plot([xmin, xmin], [ymin, ymax], [zmax, zmax], **edges_kw)
    ax.plot([xmin, xmax], [ymin, ymin], [zmax, zmax], **edges_kw)
    ax.plot([xmin, xmax], [ymax, ymax], [zmax, zmax], **edges_kw)

    ax.plot([xmax, xmax], [ymax, ymax], [zmin, zmax], **edges_kw)
    ax.plot([xmin, xmin], [ymin, ymin], [zmin, zmax], **edges_kw)
    ax.plot([xmax, xmax], [ymin, ymin], [zmin, zmax], **edges_kw)
    ax.plot([xmin, xmin], [ymax, ymax], [zmin, zmax], **edges_kw)

    # Set labels and zticks
    ax.set(
        xlabel='X [km]',
        ylabel='Y [km]',
        zlabel='Z [m]'
    )

    # Set zoom and angle view
    ax.view_init(40, -30, 0)
    ax.set_box_aspect(None, zoom=0.9)

    # Colorbar
    fig.colorbar(C, ax=ax, fraction=0.02, pad=0.1, label='Name [units]')

    # surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
    #                    linewidth=0, antialiased=False)

    plt.show()


# for j in range(6):
#     y = legendre.evalVector(j, x)

#     fig = plt.figure()

#     plt.plot(x, y)

#     plt.show()
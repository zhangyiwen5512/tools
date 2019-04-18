import matplotlib.pyplot as plt
import numpy as np

n = 512
p = 16
lam = 0.95
s = 20
alpha = 0.4

plt.figure()

px = np.random.normal(0, 1.5, n)
py = np.random.normal(0, 1.5, n)
plt.scatter(x=px, y=py, s=s, c='r', alpha=alpha)

px_est = np.random.normal(0, 1.5, n) * 0.5 - 1
py_est = np.random.normal(0, 1.5, n) * 0.5 - 0.75
plt.scatter(x=px_est[p + 1:], y=py_est[p + 1:], s=s, c='black', alpha=alpha)

px_out = np.random.normal(0, 1.5, n) * 0.5 - 3
py_out = np.random.normal(0, 1.5, n) * 0.5 - 3
plt.scatter(x=px_out[0:p], y=py_out[0:p], s=s, c='b', alpha=alpha)


plt.figure()
plt.scatter(x=px, y=py, s=s, c='r', alpha=alpha)
min_ind = np.arange(n)
np.random.shuffle(min_ind)

px_est[0:p] = px_out[0:p] + 0
py_est[0:p] = py_out[0:p] + 0

px_mix = lam * px_est + (1 - lam) * px_est[min_ind]
py_mix = lam * py_est + (1 - lam) * py_est[min_ind]
plt.scatter(x=px_mix[0:p], y=py_mix[0:p], s=s, c='b', alpha=alpha)
plt.scatter(x=px_mix[p + 1:], y=py_mix[p + 1:], s=s, c='black', alpha=alpha)

#plt.xlim((-1.5, 1.5))
#plt.ylim((-1.5, 1.5))
#plt.xticks(())
#plt.yticks(())
plt.show()

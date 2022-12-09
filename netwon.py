import numpy as np
import sympy as sp
from enum import Enum
class ErrType(Enum):
    EEUCLID = 0
    EMAX = 1

class NewtonSolver:
    def __init__(self, n, func, syms): # n: dimension, func: f(r):R^n -> R^n, syms: symbols
        self.n = n # f: R^n -> R^n
        self.func = func
        self.syms = syms 
        self.jac = func.jacobian(syms).inv()
    def solve(self, init, max_err=1e-8, err_type=ErrType.EEUCLID, max_iter=128): # init: inital vector
        currerr = max_err+1
        itt = 0
        X = sp.Matrix(init)
        while (currerr > max_err and itt < max_iter):
            Xn = sp.N(X - self.jac.subs(list(zip(self.syms, X))) * self.func.subs(list(zip(self.syms, X))))
            if(err_type == ErrType.EEUCLID):
                currerr = (Xn - X).norm()
            elif(err_type == ErrType.EMAX):
                currerr = abs(max(list(Xn - X)))
            itt += 1
            X = Xn
        return (sp.N(X), currerr, itt)

x = sp.Symbol("x")
y = sp.Symbol("y")
syms = sp.Matrix([x, y])
decplc = 3
print (f"calculating the solution to non-linear system upto {decplc} decimal places:")
function = sp.Matrix([
    x + 2*y - 3,
    2*x**2 + y**2 -5
    ])
print(function)
ns = NewtonSolver(2, function, syms)
ans, err, its = ns.solve([-1,2], (1/10)**decplc, err_type=ErrType.EEUCLID)
print(f"answer:\n{list(syms)}={np.array(list(map(lambda x:round(x, decplc), list(ans))))}\nestimated error: {err}\ncomputed in {its} iterations")


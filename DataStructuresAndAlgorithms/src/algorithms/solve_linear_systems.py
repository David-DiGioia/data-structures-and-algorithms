from sympy import *

def get_coefficients(x, count):
  arr = []
  for i in range(0,count):
    arr.append(x**(count - i - 1))
  return arr

def get_equations_and_syms(b):
  eqns = []
  syms = symbols('x1:' + str(len(b)))
  for i in range(1, len(b)):
    coefficients = get_coefficients(i, len(syms))
    eqn = None
    j = 0
    for sym in syms:
      if eqn is None:
        eqn = coefficients[j] * sym
      else:
        eqn += coefficients[j] * sym
      j += 1
    eqns.append(eqn - b[i])
  return eqns, syms

def get_equations_omit(sub_first_n, omit, b):
  pass

b = [23504, 82164, 244092, 681706, 1832736, 4777646, 12107608, 29858042, 71680232, 167557926, 381449340, 845887278, 1827779920, 3849869190]

eqns, syms = get_equations_and_syms(b)
print(solve(eqns, syms))

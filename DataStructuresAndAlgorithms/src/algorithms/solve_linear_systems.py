from sympy import *
from sympy import linsolve, symbols, fraction

def get_coefficients(x, count):
  arr = []
  for i in range(0,count):
    arr.append(x**(count - i - 1))
  return arr

def get_equations_and_syms(b, sub_list, degree):
  eqns = []
  syms = symbols('x0:' + str(degree + 1))
  for i in range(0, len(b)):
    # -1 signifies a member of b to omit
    if b[i] == -1:
      continue
    coefficients = get_coefficients(i+1, len(syms))
    eqn = None
    j = 0
    for sym in syms:
      # substitute for known coefficients
      s = sub_list[j] if j < len(sub_list) else sym
      if eqn is None:
        eqn = coefficients[j] * s
      else:
        eqn += coefficients[j] * s
      j += 1
    eqns.append(eqn - b[i])
  return eqns, syms

def get_equations_omit(sub_first_n, omit, b, degree):
  x = degree / 2
  sub_list = [1, x, x*(x+1)*(4*x+5)/6]
  print(sub_list)
  return get_equations_and_syms(b, sub_list[:sub_first_n], degree)

# does this solution have denominators of the form (n!)^2
def expected_sol(sol_set):
  # extract denominator from each coefficient in solution
  for sol in sol_set:
    for frac in sol:
      print(fraction(frac)[1])

b = [-1, 14220, 41872, 115668, 306410, 783536, 1938602, 4645126, 10784280, 24267500, 52950744, 112087996, 230348214, 459963092, 893334830]

eqns, syms = get_equations_omit(0, -1, b, 12)
#print(eqns)
sol_set = linsolve(eqns, syms)

print(expected_sol(sol_set))

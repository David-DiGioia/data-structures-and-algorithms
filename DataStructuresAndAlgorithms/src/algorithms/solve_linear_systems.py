from sympy import *
from sympy import linsolve, symbols, fraction, Rational
from math import factorial

valid_solutions = []

def get_coefficients(x, count):
  arr = []
  for i in range(0,count):
    arr.append(x**(count - i - 1))
  return arr

def get_equations_and_syms(b, sub_list, degree):
  global basic_solve
  eqns = []
  syms = symbols('x' + str(len(sub_list)) + ':' + str(degree + 1))
  for i in range(0, len(b)):
    # -1 signifies a member of b to omit
    if b[i] == -1:
      continue
    coefficients = get_coefficients(i+1, degree + 1)
    eqn = None
    denom = 1 if basic_solve else factorial((degree / 2))**2
    for j in range(0, degree + 1):
      # substitute for known coefficients
      s = Rational(sub_list[j], denom) if j < len(sub_list) else syms[j - len(sub_list)]
      if eqn is None:
        eqn = coefficients[j] * s
      else:
        eqn += coefficients[j] * s
    eqns.append(eqn - b[i])
  return eqns, syms

# does this solution have denominators of the form (n!)^2
def expected_sol(sol_set, degree):
  if (len(sol_set) == 0):
    return False
  denom = factorial((degree / 2))**2
  # extract denominator from each coefficient in solution
  for sol in sol_set:
    for frac in sol:
      if frac < 0 or denom % fraction(frac)[1] != 0:
        return False
  return True

def omit_combinations_rec(vec, omitted_count, idx, degree, sub_first_n):
  global valid_solutions
  global break_if_valid
  global basic_solve
  if omitted_count == 0:
    eqns, syms = get_equations_omit(sub_first_n, omitted_count, b, degree)
    sol_set = linsolve(eqns, syms)
    if basic_solve or expected_sol(sol_set, degree):
      print("Found valid solution.")
      valid_solutions += sol_set
      if break_if_valid:
        return True
    else:
      print("Found invalid solution.")
    return False
  for i in range(idx, len(vec) - omitted_count + 1):
    temp = vec[i]
    vec[i] = -1
    if omit_combinations_rec(vec, omitted_count - 1, i + 1, degree, sub_first_n):
      return True
    vec[i] = temp
  return False


def omit_combinations(vec, omitted_count, degree, sub_first_n):
  omit_combinations_rec(vec, omitted_count, 0, degree, sub_first_n)


def get_equations_omit(sub_first_n, omit, b, degree):
  x = degree / 2 - 1
  sub_list = [1, x+1, x*(x+1)*(4*x+5)/6]
  return get_equations_and_syms(b, sub_list[:sub_first_n], degree)

# ---------------------------------------------------------------------
# If you've already found solution, don't bother checking others
break_if_valid = True
# For solving numerator polynomials. omit_count and sub_first_n must be 0
# to use basic solve!
basic_solve = True
# Degree of polynomial we're looking for
degree = 5
# How many data points to omit (every combination will be tried)
omit_count = 0
# Assume first n variables to be expected values (helpful if there are
# not enough data points to find polynomial)
# Currently must be <= 3
sub_first_n = 0
# Data points to fit polynomial to
# -1 indicates an omitted element (shouldn't be entered manually, just use
# omit_count and all combinations will be tried)
b = [18, 129, 472, 1250, 2730, 5243]
# ---------------------------------------------------------------------

if len(b) >= (degree + 1) + omit_count - sub_first_n:
  omit_combinations(b, omit_count, degree, sub_first_n)
  print("Finished!\nFound " + str(len(valid_solutions)) + " valid solutions:")
  denom = 1 if basic_solve else factorial((degree / 2))**2
  for solution in valid_solutions:
    for frac in solution:
      if basic_solve:
        print(frac)
      else:
        num = fraction(frac)[0] * (denom / fraction(frac)[1])
        print(num, end='')
        print('/' + str(denom))
else:
  print("Variables do not fulfill requirement:")
  print("len(b) >= (degree + 1) + omit_count - sub_first_n")
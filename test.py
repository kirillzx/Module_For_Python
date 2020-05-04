from MatrixNorm import *

x = [-1, 2, -3, 4, 5]
a = [[2, 2, 4, 3], [3, 1, 1, 2], [1, 4, 5, 1]]

#Vectors
print("Result: {:.3}   Answer: 7.416".format(NormEuclidean(x)))
print("Result: {:.3}   Answer: 15".format(NormManhattan(x)))
print("Result: {:.3}   Answer: 5".format(NormInfinity(x)))
print("Result: {:.3}   Answer: 5.593".format(NormLp(x, 4)))

#Matrix
print("Result: {:.3}   Answer: 9.539".format(MatrixNormLp(a, 2)))
print("Result: {:.3}   Answer: 9.539".format(MatrixNormFrobenius(a)))

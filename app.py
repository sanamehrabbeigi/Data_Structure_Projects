from PIL import Image
from numpy import array
import numpy
import PIL


def convolution_multiply(n, m, matrix, filter):
    # n = rows of matrix
    # m = columns of matrix
    result_matrix = numpy.array([[0]*(n-2)]*(m-2), numpy.float)
    for i in range(n-2):
        for j in range(m-2):
            sum = 0
            for k in range(3):
                for l in range(3):
                    sum += matrix[i+k][j+l] * filter[k][l]
            result_matrix[i][j] = sum
    return numpy.array(result_matrix, numpy.float)


filter = numpy.array([[0]*3]*3, numpy.float)
for i in range(3):
    filter[0][i] = 1
    filter[1][i] = 0
    filter[2][i] = -1

first_greyscale_image = Image.open(
    'firstphoto.png').convert('L').resize((1500, 1500))
first_arr = numpy.array(first_greyscale_image, numpy.float)
first_result = Image.fromarray(numpy.array(convolution_multiply(
    1500, 1500, first_arr, filter), numpy.float)).show()


for i in range(3):
    filter[i][0] = 1
    filter[i][1] = 0
    filter[i][2] = -1

second_greyscale_image = Image.open(
    'secondphoto.jpg').convert('L').resize((1500, 1500))
second_arr = numpy.array(second_greyscale_image, numpy.float)
second_result = Image.fromarray(numpy.array(convolution_multiply(
    1500, 1500, second_arr, filter), numpy.float)).show()

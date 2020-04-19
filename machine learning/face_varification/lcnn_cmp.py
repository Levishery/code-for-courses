import numpy as np
from PIL import Image
import os
import scipy.io as scio


class Conv2D(object):
    def __init__(self, input_shape, output_channels, weights, bias, ksize=3, stride=1):
        self.input_shape = input_shape
        self.output_channels = output_channels
        self.input_channels = input_shape[-1]
        self.batchsize = input_shape[0]
        self.stride = stride
        self.ksize = ksize
        self.weights = weights
        self.bias = bias

    def im2col(self, image, ksize, stride):
        # image is a 4d tensor([batchsize, width ,height, channel])
        # By expanding the image, the convolution operation can be turned into two matrix multiplications
        image_col = []
        for i in range(0, image.shape[1] - ksize + 1, stride):
            for j in range(0, image.shape[2] - ksize + 1, stride):
                col = image[:, i:i + ksize, j:j + ksize, :].reshape([-1])
                image_col.append(col)
        image_col = np.array(image_col)
        return image_col

    def forward(self, x):
        col_weights = self.weights.reshape([-1, self.output_channels])
        # do SAME padding
        x = np.pad(x, ((0, 0), (self.ksize // 2, self.ksize // 2), (self.ksize // 2, self.ksize // 2), (0, 0)),
                   'constant', constant_values=0)
        self.col_image = []
        self.output_shape = (self.input_shape[0], self.input_shape[1]//self.stride, self.input_shape[2]//self.stride,self.output_channels)
        conv_out = np.zeros(self.output_shape)
        for i in range(self.batchsize):
            img_i = x[i][np.newaxis, :]
            self.col_image_i = self.im2col(img_i, self.ksize, self.stride)
            conv_out[i] = np.reshape(np.dot(self.col_image_i, col_weights) + self.bias, conv_out[0].shape)
            self.col_image.append(self.col_image_i)
        self.col_image = np.array(self.col_image)
        return conv_out



class mfm(object):
    def __init__(self, input_shape, out_channels, weights, bias, kernel_size=3, stride=1):
        self.out_channels = out_channels
        self.filter = Conv2D(input_shape, 2*out_channels, weights, bias, ksize=kernel_size, stride=stride)

    def forward(self, x):
        x = self.filter.forward(x)
        out = np.split(x, 2, -1)
        return np.maximum(out[0], out[1])


class group(object):
    def __init__(self, input_shape, out_channels, weight_conv, bias_conv, weight_mfm, bias_mfm, kernel_size=3, stride=1):
        self.conv_m = mfm(input_shape, input_shape[3], weight_mfm, bias_mfm, 1, 1)
        self.conv_c = mfm(input_shape, out_channels, weight_conv, bias_conv, kernel_size, stride)

    def forward(self, x):
        x = self.conv_m.forward(x)
        x = self.conv_c.forward(x)
        return x


class FullyConnect(object):
    def __init__(self, input_shape, weight, bias, output_num=2):
        self.input_shape = input_shape
        self.batchsize = input_shape[0]
        self.weights = weight
        self.bias = bias
        self.output_shape = [self.batchsize, output_num]

    def forward(self, x):
        self.x = x.reshape([self.batchsize, -1])
        output = np.dot(self.x, self.weights)+self.bias
        return output


def max_pooling(z, strides=(2,2)):
    N, H, W, C = z.shape
    out_h = H  // strides[0]
    out_w = W // strides[1]

    pool_z = np.zeros((N, out_h, out_w, C))

    for n in np.arange(N):
        for c in np.arange(C):
            for i in np.arange(out_h):
                for j in np.arange(out_w):
                    pool_z[n, i, j, c] = np.max(z[n,
                                          strides[0] * i:strides[0] * i + strides[0],
                                          strides[1] * j:strides[1] * j + strides[1], c])
    return pool_z


def load_image(filename):
    img = Image.open(filename)
    img.load()
    data = np.asarray(img, dtype="int32")
    return data



if __name__ == '__main__':
    im_path = '/Users/janechen/Desktop/coarse_test/'
    result_path = '/Users/janechen/Desktop/feature_test/'

    for filename in os.listdir(im_path):
        if filename.endswith('jpg'):
            file_path = im_path+filename
            img = load_image(file_path)
            img = np.expand_dims(img, axis=0)
            img = np.expand_dims(img, axis=-1)

            weight = np.transpose(np.load("param/conv_1.weight.npy"))
            bias = np.load('param/conv_1.bias.npy')
            conv_1 = mfm([1, 128, 128, 1], 48, weight, bias, 5)
            x = conv_1.forward(img)
            x = max_pooling(x)

            weight_conv = np.transpose(np.load('param/conv_2.weight.npy'))
            bias_conv = np.load('param/conv_2.bias.npy')
            weight_mfm = np.transpose(np.load('param/mfm_1.filter.weight.npy'))
            bias_mfm = np.load('param/mfm_1.bias.npy')
            group_1 = group([1, 64, 64, 48], 96, weight_conv, bias_conv, weight_mfm, bias_mfm)
            x = group_1.forward(x)
            x = max_pooling(x)

            weight_conv = np.transpose(np.load('param/conv_3.weight.npy'))
            bias_conv = np.load('param/conv_3.bias.npy')
            weight_mfm = np.transpose(np.load('param/mfm_2.weight.npy'))
            bias_mfm = np.load('param/mfm_2.bias.npy')
            group_2 = group([1, 32, 32, 96], 192, weight_conv, bias_conv, weight_mfm, bias_mfm)
            x = group_2.forward(x)
            x = max_pooling(x)

            weight_conv = np.transpose(np.load('param/conv_4.weight.npy'))
            bias_conv = np.load('param/conv_4.bias.npy')
            weight_mfm = np.transpose(np.load('param/mfm_3.weight.npy'))
            bias_mfm = np.load('param/mfm_3.bias.npy')
            group_3 = group([1, 16, 16, 192], 128, weight_conv, bias_conv, weight_mfm, bias_mfm)
            x = group_3.forward(x)

            weight_conv = np.transpose(np.load('param/conv_5.weight.npy'))
            bias_conv = np.load('param/conv_5.bias.npy')
            weight_mfm = np.transpose(np.load('param/mfm_4.weight.npy'))
            bias_mfm = np.load('param/mfm_4.bias.npy')
            group_4 = group([1, 16, 16, 128], 128, weight_conv, bias_conv, weight_mfm, bias_mfm)
            x = group_4.forward(x)
            x = max_pooling(x)

            x = np.expand_dims(np.transpose(x[0]), axis=0)
            #x = np.expand_dims(np.transpose(x[0]), axis=0)
            #x = np.swapaxes(x, -1, -2)
            x = np.expand_dims(x.reshape(8*8*128), axis=0)
            weight = np.transpose(np.load('param/fc1.weight.npy'))
            bias = np.load('param/fc1.bias.npy')
            fc1 = FullyConnect([1, 8*8*128], weight, bias, 512)
            x = fc1.forward(x)
            out = np.split(x, 2, -1)
            x = np.maximum(out[0], out[1])

            save_path = result_path + filename[0:-4] + '.mat'
            scio.savemat(save_path, {'x': x})







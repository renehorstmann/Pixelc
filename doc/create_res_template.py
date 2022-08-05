import numpy as np

def nn_resample(img, shape):
    def per_axis(in_sz, out_sz):
        ratio = 0.5 * in_sz / out_sz
        return np.round(np.linspace(ratio - 0.5, in_sz - ratio - 0.5, num=out_sz)).astype(int)

    return img[per_axis(img.shape[0], shape[0])[:, None],
               per_axis(img.shape[1], shape[1])]


if __name__ == '__main__':
    import os
    import imageio.v3 as iio
    import glob

    print('generating scaled res buttons...')

    if not os.path.exists('res2'):
        os.makedirs('res2')
    if not os.path.exists('res4'):
        os.makedirs('res4')

    for im_path in glob.glob("../res/*.png"):
        print('Asset:', im_path)
        im = iio.imread(im_path)

        dst_2_path = 'res2/' + im_path[6:]  # without ../res
        scale_shape = np.array(im.shape)
        scale_shape[:2] *= 2
        scaled = nn_resample(im, scale_shape)
        iio.imwrite(dst_2_path, scaled)

        dst_4_path = 'res4/' + im_path[6:]  # without ../res
        scale_shape = np.array(im.shape)
        scale_shape[:2] *= 4
        scaled = nn_resample(im, scale_shape)
        iio.imwrite(dst_4_path, scaled)

    print('done')
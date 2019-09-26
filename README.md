# Median-Filter
Introduction
The focus of this practical is partitioning data for multi-threaded applications. The
test case is a median filter.
Median filters utilise statistics to remove extraneous values (noise) from data sets.
These data sets can be of an arbitrary number of dimensions, but for this practical
you will only be working with two-dimensional data sets, or images.

The Algorithm
A 9x9 median filter should be used. Each pixel in the output image is the median of
the corresponding pixel in the input image and the surrounding 80 pixels.
You can decide how to handle the border cases. Typically the pixel indices are
clamped to the border, but you can also use zeros for pixels outside the image, for
instance.
Each colour component is handled on its own, so for a full colour image you need
to run the algorithm three times on the same pixel.

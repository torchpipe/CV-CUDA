/*
 * SPDX-FileCopyrightText: Copyright (c) 2022-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file Types.h
 *
 * @brief Defines types to be used by operators.
 * @defgroup NVCV_C_TYPES Types
 * @{
 */

#ifndef CVCUDAERATORS_TYPES_H
#define CVCUDAERATORS_TYPES_H

#include "detail/Export.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

// @brief Flag to choose the interpolation method to be used
typedef enum
{
    NVCV_INTERP_NEAREST   = 0,
    NVCV_INTERP_LINEAR    = 1,
    NVCV_INTERP_CUBIC     = 2,
    NVCV_INTERP_AREA      = 3,
    NVCV_INTERP_LANCZOS   = 4,
    NVCV_INTERP_MAX       = 7,
    NVCV_WARP_INVERSE_MAP = 16,
    NVCV_INTERP_HAMMING   = 17,
    NVCV_INTERP_BOX       = 18
} NVCVInterpolationType;

typedef enum
{
    NVCV_ERODE  = 0,
    NVCV_DILATE = 1,
    NVCV_OPEN   = 2,
    NVCV_CLOSE  = 3,
} NVCVMorphologyType;

// @brief Flag to choose the color conversion to be used
typedef enum
{
    NVCV_COLOR_BGR2BGRA = 0, //!< add alpha channel to RGB or BGR image
    NVCV_COLOR_RGB2RGBA = NVCV_COLOR_BGR2BGRA,

    NVCV_COLOR_BGRA2BGR = 1, //!< remove alpha channel from RGB or BGR image
    NVCV_COLOR_RGBA2RGB = NVCV_COLOR_BGRA2BGR,

    NVCV_COLOR_BGR2RGBA = 2, //!< convert between RGB and BGR color spaces (with or without alpha channel)
    NVCV_COLOR_RGB2BGRA = NVCV_COLOR_BGR2RGBA,

    NVCV_COLOR_RGBA2BGR = 3,
    NVCV_COLOR_BGRA2RGB = NVCV_COLOR_RGBA2BGR,

    NVCV_COLOR_BGR2RGB = 4,
    NVCV_COLOR_RGB2BGR = NVCV_COLOR_BGR2RGB,

    NVCV_COLOR_BGRA2RGBA = 5,
    NVCV_COLOR_RGBA2BGRA = NVCV_COLOR_BGRA2RGBA,

    NVCV_COLOR_BGR2GRAY = 6, //!< convert between RGB/BGR and grayscale, @ref color_convert_rgb_gray "color conversions"
    NVCV_COLOR_RGB2GRAY = 7,
    NVCV_COLOR_GRAY2BGR = 8,
    NVCV_COLOR_GRAY2RGB = NVCV_COLOR_GRAY2BGR,
    NVCV_COLOR_GRAY2BGRA = 9,
    NVCV_COLOR_GRAY2RGBA = NVCV_COLOR_GRAY2BGRA,
    NVCV_COLOR_BGRA2GRAY = 10,
    NVCV_COLOR_RGBA2GRAY = 11,

    NVCV_COLOR_BGR2BGR565  = 12, //!< convert between RGB/BGR and BGR565 (16-bit images)
    NVCV_COLOR_RGB2BGR565  = 13,
    NVCV_COLOR_BGR5652BGR  = 14,
    NVCV_COLOR_BGR5652RGB  = 15,
    NVCV_COLOR_BGRA2BGR565 = 16,
    NVCV_COLOR_RGBA2BGR565 = 17,
    NVCV_COLOR_BGR5652BGRA = 18,
    NVCV_COLOR_BGR5652RGBA = 19,

    NVCV_COLOR_GRAY2BGR565 = 20, //!< convert between grayscale to BGR565 (16-bit images)
    NVCV_COLOR_BGR5652GRAY = 21,

    NVCV_COLOR_BGR2BGR555  = 22, //!< convert between RGB/BGR and BGR555 (16-bit images)
    NVCV_COLOR_RGB2BGR555  = 23,
    NVCV_COLOR_BGR5552BGR  = 24,
    NVCV_COLOR_BGR5552RGB  = 25,
    NVCV_COLOR_BGRA2BGR555 = 26,
    NVCV_COLOR_RGBA2BGR555 = 27,
    NVCV_COLOR_BGR5552BGRA = 28,
    NVCV_COLOR_BGR5552RGBA = 29,

    NVCV_COLOR_GRAY2BGR555 = 30, //!< convert between grayscale and BGR555 (16-bit images)
    NVCV_COLOR_BGR5552GRAY = 31,

    NVCV_COLOR_BGR2XYZ = 32, //!< convert RGB/BGR to CIE XYZ, @ref color_convert_rgb_xyz "color conversions"
    NVCV_COLOR_RGB2XYZ = 33,
    NVCV_COLOR_XYZ2BGR = 34,
    NVCV_COLOR_XYZ2RGB = 35,

    NVCV_COLOR_BGR2YCrCb
        = 36, //!< convert RGB/BGR to luma-chroma (aka YCC), @ref color_convert_rgb_ycrcb "color conversions"
    NVCV_COLOR_RGB2YCrCb = 37,
    NVCV_COLOR_YCrCb2BGR = 38,
    NVCV_COLOR_YCrCb2RGB = 39,

    NVCV_COLOR_BGR2HSV
        = 40, //!< convert RGB/BGR to HSV (hue saturation value), @ref color_convert_rgb_hsv "color conversions"
    NVCV_COLOR_RGB2HSV = 41,

    NVCV_COLOR_BGR2Lab = 44, //!< convert RGB/BGR to CIE Lab, @ref color_convert_rgb_lab "color conversions"
    NVCV_COLOR_RGB2Lab = 45,

    NVCV_COLOR_BGR2Luv = 50, //!< convert RGB/BGR to CIE Luv, @ref color_convert_rgb_luv "color conversions"
    NVCV_COLOR_RGB2Luv = 51,
    NVCV_COLOR_BGR2HLS
        = 52, //!< convert RGB/BGR to HLS (hue lightness saturation), @ref color_convert_rgb_hls "color conversions"
    NVCV_COLOR_RGB2HLS = 53,

    NVCV_COLOR_HSV2BGR = 54, //!< backward conversions to RGB/BGR
    NVCV_COLOR_HSV2RGB = 55,

    NVCV_COLOR_Lab2BGR = 56,
    NVCV_COLOR_Lab2RGB = 57,
    NVCV_COLOR_Luv2BGR = 58,
    NVCV_COLOR_Luv2RGB = 59,
    NVCV_COLOR_HLS2BGR = 60,
    NVCV_COLOR_HLS2RGB = 61,

    NVCV_COLOR_BGR2HSV_FULL = 66, //!<
    NVCV_COLOR_RGB2HSV_FULL = 67,
    NVCV_COLOR_BGR2HLS_FULL = 68,
    NVCV_COLOR_RGB2HLS_FULL = 69,

    NVCV_COLOR_HSV2BGR_FULL = 70,
    NVCV_COLOR_HSV2RGB_FULL = 71,
    NVCV_COLOR_HLS2BGR_FULL = 72,
    NVCV_COLOR_HLS2RGB_FULL = 73,

    NVCV_COLOR_LBGR2Lab = 74,
    NVCV_COLOR_LRGB2Lab = 75,
    NVCV_COLOR_LBGR2Luv = 76,
    NVCV_COLOR_LRGB2Luv = 77,

    NVCV_COLOR_Lab2LBGR = 78,
    NVCV_COLOR_Lab2LRGB = 79,
    NVCV_COLOR_Luv2LBGR = 80,
    NVCV_COLOR_Luv2LRGB = 81,

    NVCV_COLOR_BGR2YUV = 82, //!< convert between RGB/BGR and YUV
    NVCV_COLOR_RGB2YUV = 83,
    NVCV_COLOR_YUV2BGR = 84,
    NVCV_COLOR_YUV2RGB = 85,

    //! YUV 4:2:0 family to RGB
    NVCV_COLOR_YUV2RGB_NV12 = 90,
    NVCV_COLOR_YUV2BGR_NV12 = 91,
    NVCV_COLOR_YUV2RGB_NV21 = 92,
    NVCV_COLOR_YUV2BGR_NV21 = 93,
    NVCV_COLOR_YUV420sp2RGB = NVCV_COLOR_YUV2RGB_NV21,
    NVCV_COLOR_YUV420sp2BGR = NVCV_COLOR_YUV2BGR_NV21,

    NVCV_COLOR_YUV2RGBA_NV12 = 94,
    NVCV_COLOR_YUV2BGRA_NV12 = 95,
    NVCV_COLOR_YUV2RGBA_NV21 = 96,
    NVCV_COLOR_YUV2BGRA_NV21 = 97,
    NVCV_COLOR_YUV420sp2RGBA = NVCV_COLOR_YUV2RGBA_NV21,
    NVCV_COLOR_YUV420sp2BGRA = NVCV_COLOR_YUV2BGRA_NV21,

    NVCV_COLOR_YUV2RGB_YV12 = 98,
    NVCV_COLOR_YUV2BGR_YV12 = 99,
    NVCV_COLOR_YUV2RGB_IYUV = 100,
    NVCV_COLOR_YUV2BGR_IYUV = 101,
    NVCV_COLOR_YUV2RGB_I420 = NVCV_COLOR_YUV2RGB_IYUV,
    NVCV_COLOR_YUV2BGR_I420 = NVCV_COLOR_YUV2BGR_IYUV,
    NVCV_COLOR_YUV420p2RGB  = NVCV_COLOR_YUV2RGB_YV12,
    NVCV_COLOR_YUV420p2BGR  = NVCV_COLOR_YUV2BGR_YV12,

    NVCV_COLOR_YUV2RGBA_YV12 = 102,
    NVCV_COLOR_YUV2BGRA_YV12 = 103,
    NVCV_COLOR_YUV2RGBA_IYUV = 104,
    NVCV_COLOR_YUV2BGRA_IYUV = 105,
    NVCV_COLOR_YUV2RGBA_I420 = NVCV_COLOR_YUV2RGBA_IYUV,
    NVCV_COLOR_YUV2BGRA_I420 = NVCV_COLOR_YUV2BGRA_IYUV,
    NVCV_COLOR_YUV420p2RGBA  = NVCV_COLOR_YUV2RGBA_YV12,
    NVCV_COLOR_YUV420p2BGRA  = NVCV_COLOR_YUV2BGRA_YV12,

    NVCV_COLOR_YUV2GRAY_420  = 106,
    NVCV_COLOR_YUV2GRAY_NV21 = NVCV_COLOR_YUV2GRAY_420,
    NVCV_COLOR_YUV2GRAY_NV12 = NVCV_COLOR_YUV2GRAY_420,
    NVCV_COLOR_YUV2GRAY_YV12 = NVCV_COLOR_YUV2GRAY_420,
    NVCV_COLOR_YUV2GRAY_IYUV = NVCV_COLOR_YUV2GRAY_420,
    NVCV_COLOR_YUV2GRAY_I420 = NVCV_COLOR_YUV2GRAY_420,
    NVCV_COLOR_YUV420sp2GRAY = NVCV_COLOR_YUV2GRAY_420,
    NVCV_COLOR_YUV420p2GRAY  = NVCV_COLOR_YUV2GRAY_420,

    //! YUV 4:2:2 family to RGB
    NVCV_COLOR_YUV2RGB_UYVY = 107,
    NVCV_COLOR_YUV2BGR_UYVY = 108,
    //NVCV_COLOR_YUV2RGB_VYUY = 109,
    //NVCV_COLOR_YUV2BGR_VYUY = 110,
    NVCV_COLOR_YUV2RGB_Y422 = NVCV_COLOR_YUV2RGB_UYVY,
    NVCV_COLOR_YUV2BGR_Y422 = NVCV_COLOR_YUV2BGR_UYVY,
    NVCV_COLOR_YUV2RGB_UYNV = NVCV_COLOR_YUV2RGB_UYVY,
    NVCV_COLOR_YUV2BGR_UYNV = NVCV_COLOR_YUV2BGR_UYVY,

    NVCV_COLOR_YUV2RGBA_UYVY = 111,
    NVCV_COLOR_YUV2BGRA_UYVY = 112,
    //NVCV_COLOR_YUV2RGBA_VYUY = 113,
    //NVCV_COLOR_YUV2BGRA_VYUY = 114,
    NVCV_COLOR_YUV2RGBA_Y422 = NVCV_COLOR_YUV2RGBA_UYVY,
    NVCV_COLOR_YUV2BGRA_Y422 = NVCV_COLOR_YUV2BGRA_UYVY,
    NVCV_COLOR_YUV2RGBA_UYNV = NVCV_COLOR_YUV2RGBA_UYVY,
    NVCV_COLOR_YUV2BGRA_UYNV = NVCV_COLOR_YUV2BGRA_UYVY,

    NVCV_COLOR_YUV2RGB_YUY2 = 115,
    NVCV_COLOR_YUV2BGR_YUY2 = 116,
    NVCV_COLOR_YUV2RGB_YVYU = 117,
    NVCV_COLOR_YUV2BGR_YVYU = 118,
    NVCV_COLOR_YUV2RGB_YUYV = NVCV_COLOR_YUV2RGB_YUY2,
    NVCV_COLOR_YUV2BGR_YUYV = NVCV_COLOR_YUV2BGR_YUY2,
    NVCV_COLOR_YUV2RGB_YUNV = NVCV_COLOR_YUV2RGB_YUY2,
    NVCV_COLOR_YUV2BGR_YUNV = NVCV_COLOR_YUV2BGR_YUY2,

    NVCV_COLOR_YUV2RGBA_YUY2 = 119,
    NVCV_COLOR_YUV2BGRA_YUY2 = 120,
    NVCV_COLOR_YUV2RGBA_YVYU = 121,
    NVCV_COLOR_YUV2BGRA_YVYU = 122,
    NVCV_COLOR_YUV2RGBA_YUYV = NVCV_COLOR_YUV2RGBA_YUY2,
    NVCV_COLOR_YUV2BGRA_YUYV = NVCV_COLOR_YUV2BGRA_YUY2,
    NVCV_COLOR_YUV2RGBA_YUNV = NVCV_COLOR_YUV2RGBA_YUY2,
    NVCV_COLOR_YUV2BGRA_YUNV = NVCV_COLOR_YUV2BGRA_YUY2,

    NVCV_COLOR_YUV2GRAY_UYVY = 123,
    NVCV_COLOR_YUV2GRAY_YUY2 = 124,
    //CV_YUV2GRAY_VYUY    = CV_YUV2GRAY_UYVY,
    NVCV_COLOR_YUV2GRAY_Y422 = NVCV_COLOR_YUV2GRAY_UYVY,
    NVCV_COLOR_YUV2GRAY_UYNV = NVCV_COLOR_YUV2GRAY_UYVY,
    NVCV_COLOR_YUV2GRAY_YVYU = NVCV_COLOR_YUV2GRAY_YUY2,
    NVCV_COLOR_YUV2GRAY_YUYV = NVCV_COLOR_YUV2GRAY_YUY2,
    NVCV_COLOR_YUV2GRAY_YUNV = NVCV_COLOR_YUV2GRAY_YUY2,

    //! alpha premultiplication
    NVCV_COLOR_RGBA2mRGBA = 125,
    NVCV_COLOR_mRGBA2RGBA = 126,

    //! RGB to YUV 4:2:0 family
    NVCV_COLOR_RGB2YUV_I420 = 127,
    NVCV_COLOR_BGR2YUV_I420 = 128,
    NVCV_COLOR_RGB2YUV_IYUV = NVCV_COLOR_RGB2YUV_I420,
    NVCV_COLOR_BGR2YUV_IYUV = NVCV_COLOR_BGR2YUV_I420,

    NVCV_COLOR_RGBA2YUV_I420 = 129,
    NVCV_COLOR_BGRA2YUV_I420 = 130,
    NVCV_COLOR_RGBA2YUV_IYUV = NVCV_COLOR_RGBA2YUV_I420,
    NVCV_COLOR_BGRA2YUV_IYUV = NVCV_COLOR_BGRA2YUV_I420,
    NVCV_COLOR_RGB2YUV_YV12  = 131,
    NVCV_COLOR_BGR2YUV_YV12  = 132,
    NVCV_COLOR_RGBA2YUV_YV12 = 133,
    NVCV_COLOR_BGRA2YUV_YV12 = 134,

    //! Demosaicing
    NVCV_COLOR_BayerBG2BGR = 46,
    NVCV_COLOR_BayerGB2BGR = 47,
    NVCV_COLOR_BayerRG2BGR = 48,
    NVCV_COLOR_BayerGR2BGR = 49,

    NVCV_COLOR_BayerBG2RGB = NVCV_COLOR_BayerRG2BGR,
    NVCV_COLOR_BayerGB2RGB = NVCV_COLOR_BayerGR2BGR,
    NVCV_COLOR_BayerRG2RGB = NVCV_COLOR_BayerBG2BGR,
    NVCV_COLOR_BayerGR2RGB = NVCV_COLOR_BayerGB2BGR,

    NVCV_COLOR_BayerBG2GRAY = 86,
    NVCV_COLOR_BayerGB2GRAY = 87,
    NVCV_COLOR_BayerRG2GRAY = 88,
    NVCV_COLOR_BayerGR2GRAY = 89,

    //! Demosaicing using Variable Number of Gradients
    NVCV_COLOR_BayerBG2BGR_VNG = 62,
    NVCV_COLOR_BayerGB2BGR_VNG = 63,
    NVCV_COLOR_BayerRG2BGR_VNG = 64,
    NVCV_COLOR_BayerGR2BGR_VNG = 65,

    NVCV_COLOR_BayerBG2RGB_VNG = NVCV_COLOR_BayerRG2BGR_VNG,
    NVCV_COLOR_BayerGB2RGB_VNG = NVCV_COLOR_BayerGR2BGR_VNG,
    NVCV_COLOR_BayerRG2RGB_VNG = NVCV_COLOR_BayerBG2BGR_VNG,
    NVCV_COLOR_BayerGR2RGB_VNG = NVCV_COLOR_BayerGB2BGR_VNG,

    //! Edge-Aware Demosaicing
    NVCV_COLOR_BayerBG2BGR_EA = 135,
    NVCV_COLOR_BayerGB2BGR_EA = 136,
    NVCV_COLOR_BayerRG2BGR_EA = 137,
    NVCV_COLOR_BayerGR2BGR_EA = 138,

    NVCV_COLOR_BayerBG2RGB_EA = NVCV_COLOR_BayerRG2BGR_EA,
    NVCV_COLOR_BayerGB2RGB_EA = NVCV_COLOR_BayerGR2BGR_EA,
    NVCV_COLOR_BayerRG2RGB_EA = NVCV_COLOR_BayerBG2BGR_EA,
    NVCV_COLOR_BayerGR2RGB_EA = NVCV_COLOR_BayerGB2BGR_EA,

    NVCV_COLOR_COLORCVT_MAX = 139,

    NVCV_COLOR_RGB2YUV_NV12 = 140,
    NVCV_COLOR_BGR2YUV_NV12 = 141,
    NVCV_COLOR_RGB2YUV_NV21 = 142,
    NVCV_COLOR_RGB2YUV420sp = NVCV_COLOR_RGB2YUV_NV21,
    NVCV_COLOR_BGR2YUV_NV21 = 143,
    NVCV_COLOR_BGR2YUV420sp = NVCV_COLOR_BGR2YUV_NV21,

    NVCV_COLOR_RGBA2YUV_NV12 = 144,
    NVCV_COLOR_BGRA2YUV_NV12 = 145,
    NVCV_COLOR_RGBA2YUV_NV21 = 146,
    NVCV_COLOR_RGBA2YUV420sp = NVCV_COLOR_RGBA2YUV_NV21,
    NVCV_COLOR_BGRA2YUV_NV21 = 147,
    NVCV_COLOR_BGRA2YUV420sp = NVCV_COLOR_BGRA2YUV_NV21,

    NVCV_COLORCVT_MAX = 148,

} NVCVColorConversionCode;

typedef enum
{
    NVCV_THRESH_BINARY     = 0x01,
    NVCV_THRESH_BINARY_INV = 0x02,
    NVCV_THRESH_TRUNC      = 0x04,
    NVCV_THRESH_TOZERO     = 0x08,
    NVCV_THRESH_TOZERO_INV = 0x10,
    NVCV_THRESH_MASK       = 0x1F,
    NVCV_THRESH_OTSU       = 0x20,
    NVCV_THRESH_TRIANGLE   = 0x40,

} NVCVThresholdType;

typedef enum
{
    NVCV_ADAPTIVE_THRESH_MEAN_C     = 0,
    NVCV_ADAPTIVE_THRESH_GAUSSIAN_C = 1
} NVCVAdaptiveThresholdType;

// @brief Flag to choose the map value type of the remap operator
typedef enum
{
    NVCV_REMAP_ABSOLUTE            = 0,
    NVCV_REMAP_ABSOLUTE_NORMALIZED = 1,
    NVCV_REMAP_RELATIVE_NORMALIZED = 2
} NVCVRemapMapValueType;

typedef enum
{
    NVCV_OSD_NONE         = 0,
    NVCV_OSD_RECT         = 1,  // \ref NVCVBndBoxI.
    NVCV_OSD_TEXT         = 2,  // \ref NVCVText.
    NVCV_OSD_SEGMENT      = 3,  // \ref NVCVSegment.
    NVCV_OSD_POINT        = 4,  // \ref NVCVPoint.
    NVCV_OSD_LINE         = 5,  // \ref NVCVLine.
    NVCV_OSD_POLYLINE     = 6,  // \ref NVCVPolyLine.
    NVCV_OSD_ROTATED_RECT = 7,  // \ref NVCVRotatedBox.
    NVCV_OSD_CIRCLE       = 8,  // \ref NVCVCircle.
    NVCV_OSD_ARROW        = 9,  // \ref NVCVArrow.
    NVCV_OSD_CLOCK        = 10, // \ref NVCVClock.
    NVCV_OSD_MAX          = 11,
} NVCVOSDType;

// @brief Flag to choose SIFT operator flags
typedef enum
{
    NVCV_SIFT_USE_ORIGINAL_INPUT = 0,
    NVCV_SIFT_USE_EXPANDED_INPUT = 1
} NVCVSIFTFlagType;

// @brief Defines connectivity of elements
typedef enum
{
    NVCV_CONNECTIVITY_4_2D,  //!< Immediate (cross) neighborhood of pixels.
    NVCV_CONNECTIVITY_6_3D,  //!< Immediate (cross) neighborhood of voxels.
    NVCV_CONNECTIVITY_8_2D,  //!< All direct (full) neighborhood of pixels.
    NVCV_CONNECTIVITY_26_3D, //!< All direct (full) neighborhood of voxels.
} NVCVConnectivityType;

// @brief Defines how labels are assigned in Label operator
typedef enum
{
    NVCV_LABEL_FAST,       //!< Does not guarantee consecutive label numbers.
    NVCV_LABEL_SEQUENTIAL, //!< Assigns consecutive numbers to labels.
} NVCVLabelType;

// @brief Defines pair-wise matcher algorithms of choice
typedef enum
{
    NVCV_BRUTE_FORCE //!< Select brute-force algorithm as the matcher
} NVCVPairwiseMatcherType;

// @brief Defines how a vector normalization should occur
typedef enum
{
    NVCV_NORM_HAMMING = 0, //!< Equivalent to the Hamming distance (or L_0 norm)
    NVCV_NORM_L1      = 1, //!< Equivalent to the absolute distance = |x1-x2| + |y1-y2| (or L_1 norm)
    NVCV_NORM_L2      = 2, //!< Equivalent to the Euclidean distance (or L_2 norm)
    NVCV_NORM_C       = 3, //!< distance = max(|x1-x2|,|y1-y2|)
    NVCV_NORM_L12     = 4, //!< L1-L2 metric: distance = 2(sqrt(1+x*x/2) - 1))
    NVCV_NORM_FAIR    = 5, //!< distance = c^2(|x|/c-log(1+|x|/c)), c = 1.3998
    NVCV_NORM_WELSCH  = 6, //!< distance = c^2/2(1-exp(-(x/c)^2)), c = 2.9846
    NVCV_NORM_HUBER   = 7, //!< distance = |x|<c ? x^2/2 : c(|x|-c/2), c=1.345

} NVCVNormType;

typedef unsigned char uint8_t;
typedef int           int32_t;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} NVCVColorRGBA;

typedef struct
{
    int32_t x; //!< x coordinate
    int32_t y; //!< y coordinate
} NVCVPointI;

typedef struct
{
    int32_t x;      //!< x coordinate of the top-left corner
    int32_t y;      //!< y coordinate of the top-left corner
    int32_t width;  //!< width of the box
    int32_t height; //!< height of the box
} NVCVBoxI;

typedef struct
{
    NVCVBoxI      box;         // Bounding box, \ref NVCVBoxI.
    int32_t       thickness;   // Border thickness of bounding box.
    NVCVColorRGBA borderColor; // Border color of bounding box.
    NVCVColorRGBA fillColor;   // Filled color of bounding box.
} NVCVBndBoxI;

typedef void *NVCVBndBoxesI;

typedef struct
{
    NVCVBoxI box;        // Blur box, \ref NVCVBoxI.
    int32_t  kernelSize; // Kernel sizes of mean filter, refer to cv::blur().
} NVCVBlurBoxI;

typedef void *NVCVBlurBoxesI;

typedef struct
{
    NVCVPointI    centerPos; // Center point, \ref NVCVPointI.
    int32_t       radius;    // Point size.
    NVCVColorRGBA color;     // Point color.
} NVCVPoint;

typedef struct
{
    NVCVPointI    pos0;          // Start point, \ref NVCVPointI.
    NVCVPointI    pos1;          // End point, \ref NVCVPointI.
    int32_t       thickness;     // Line thickness.
    NVCVColorRGBA color;         // Line color.
    bool          interpolation; // Default: true.
} NVCVLine;

typedef struct
{
    NVCVPointI    centerPos;     // Center point, \ref NVCVPointI.
    int32_t       width;         // Box width.
    int32_t       height;        // Box height.
    float         yaw;           // Box yaw.
    int32_t       thickness;     // Box border thickness.
    NVCVColorRGBA borderColor;   // Box border color.
    NVCVColorRGBA bgColor;       // Box filled color.
    bool          interpolation; // Default: false.
} NVCVRotatedBox;

typedef struct
{
    NVCVPointI    centerPos;   // Center point, \ref NVCVPointI.
    int32_t       radius;      // Circle radius.
    int32_t       thickness;   // Circle thickness.
    NVCVColorRGBA borderColor; // Circle border color.
    NVCVColorRGBA bgColor;     // Circle filled color.
} NVCVCircle;

typedef struct
{
    NVCVPointI    pos0;          // Start point, \ref NVCVPointI.
    NVCVPointI    pos1;          // End point, \ref NVCVPointI.
    int32_t       arrowSize;     // Arrow size.
    int32_t       thickness;     // Arrow line thickness.
    NVCVColorRGBA color;         // Arrow line color.
    bool          interpolation; // Default: false
} NVCVArrow;

typedef enum
{
    None          = 0,
    YYMMDD_HHMMSS = 1,
    YYMMDD        = 2,
    HHMMSS        = 3
} NVCVClockFormat;

typedef void *NVCVElements;

#ifdef __cplusplus
}
#endif

#endif /* CVCUDAERATORS_TYPES_H */

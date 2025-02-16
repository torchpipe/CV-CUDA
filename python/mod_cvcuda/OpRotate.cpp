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

#include "Operators.hpp"

#include <common/PyUtil.hpp>
#include <common/String.hpp>
#include <cvcuda/OpRotate.hpp>
#include <cvcuda/Types.h>
#include <nvcv/cuda/TypeTraits.hpp>
#include <nvcv/python/ImageBatchVarShape.hpp>
#include <nvcv/python/ResourceGuard.hpp>
#include <nvcv/python/Stream.hpp>
#include <nvcv/python/Tensor.hpp>
#include <pybind11/stl.h>

namespace cvcudapy {

namespace {
Tensor RotateInto(Tensor &output, Tensor &input, double angleDeg, const std::tuple<double, double> &shift,
                  NVCVInterpolationType interpolation, std::optional<Stream> pstream)
{
    if (!pstream)
    {
        pstream = Stream::Current();
    }

    auto rotate = CreateOperator<cvcuda::Rotate>(0);

    ResourceGuard guard(*pstream);
    guard.add(LockMode::LOCK_READ, {input});
    guard.add(LockMode::LOCK_WRITE, {output});
    guard.add(LockMode::LOCK_WRITE, {*rotate});

    double2 shiftArg{std::get<0>(shift), std::get<1>(shift)};

    rotate->submit(pstream->cudaHandle(), input, output, angleDeg, shiftArg, interpolation);

    return output;
}

Tensor Rotate(Tensor &input, double angleDeg, const std::tuple<double, double> &shift,
              const NVCVInterpolationType interpolation, std::optional<Stream> pstream)
{
    Tensor output = Tensor::Create(input.shape(), input.dtype());

    return RotateInto(output, input, angleDeg, shift, interpolation, pstream);
}

ImageBatchVarShape VarShapeRotateInto(ImageBatchVarShape &output, ImageBatchVarShape &input, Tensor &angleDeg,
                                      Tensor &shift, NVCVInterpolationType interpolation, std::optional<Stream> pstream)
{
    if (!pstream)
    {
        pstream = Stream::Current();
    }

    auto rotate = CreateOperator<cvcuda::Rotate>(input.capacity());

    ResourceGuard guard(*pstream);
    guard.add(LockMode::LOCK_READ, {input, angleDeg, shift});
    guard.add(LockMode::LOCK_WRITE, {output});
    guard.add(LockMode::LOCK_WRITE, {*rotate});

    rotate->submit(pstream->cudaHandle(), input, output, angleDeg, shift, interpolation);

    return output;
}

ImageBatchVarShape VarShapeRotate(ImageBatchVarShape &input, Tensor &angleDeg, Tensor &shift,
                                  NVCVInterpolationType interpolation, std::optional<Stream> pstream)
{
    ImageBatchVarShape output = ImageBatchVarShape::Create(input.capacity());

    for (int i = 0; i < input.numImages(); ++i)
    {
        nvcv::ImageFormat format = input[i].format();
        nvcv::Size2D      size   = input[i].size();
        auto              image  = Image::Create(size, format);
        output.pushBack(image);
    }

    return VarShapeRotateInto(output, input, angleDeg, shift, interpolation, pstream);
}

} // namespace

void ExportOpRotate(py::module &m)
{
    using namespace pybind11::literals;

    py::options options;
    options.disable_function_signatures();

    m.def("rotate", &Rotate, "src"_a, "angle_deg"_a, "shift"_a, "interpolation"_a, py::kw_only(), "stream"_a = nullptr,
          R"pbdoc(

	cvcuda.rotate(src: nvcv.Tensor, angle_deg: double, shift: Tuple [double, double], interpolation : Interp, stream: Optional[nvcv.cuda.Stream] = None) -> nvcv.Tensor

        Executes the Rotate operation on the given cuda stream.

        See also:
            Refer to the CV-CUDA C API reference for the Rotate operator
            for more details and usage examples.

        Args:
            src (Tensor): Input tensor containing one or more images.
            angle_deg (double): Angle used for rotation in degrees.
            shift (Tuple [double, double]): Value of shift in {x, y} directions to move the center at the same coord after rotation.
            interpolation (Interp): Interpolation type used for transform.
            stream (Stream, optional): CUDA Stream on which to perform the operation.

        Returns:
            cvcuda.Tensor: The output tensor.

        Caution:
            Restrictions to several arguments may apply. Check the C
            API references of the CV-CUDA operator.
    )pbdoc");

    m.def("rotate_into", &RotateInto, "dst"_a, "src"_a, "angle_deg"_a, "shift"_a, "interpolation"_a, py::kw_only(),
          "stream"_a = nullptr, R"pbdoc(

	cvcuda.rotate_into(dst: nvcv.Tensor, src: nvcv.Tensor, angle_deg: double, shift: Tuple [double, double], interpolation : Interp, stream: Optional[nvcv.cuda.Stream] = None)

        Executes the Rotate operation on the given cuda stream.

        See also:
            Refer to the CV-CUDA C API reference for the Rotate operator
            for more details and usage examples.

        Args:
            dst (Tensor): Output tensor to store the result of the operation.
            src (Tensor): Input tensor containing one or more images.
            angle_deg (double): Angle used for rotation in degrees.
            shift (Tuple [double, double]): Value of shift in {x, y} directions to move the center at the same coord after rotation.
            interpolation (Interp): Interpolation type used for transform.
            stream (Stream, optional): CUDA Stream on which to perform the operation.

        Returns:
            None

        Caution:
            Restrictions to several arguments may apply. Check the C
            API references of the CV-CUDA operator.
    )pbdoc");

    m.def("rotate", &VarShapeRotate, "src"_a, "angle_deg"_a, "shift"_a, "interpolation"_a, py::kw_only(),
          "stream"_a = nullptr, R"pbdoc(

	cvcuda.rotate(src: nvcv.ImageBatchVarShape, angle_deg: double, shift: Tuple [double, double], interpolation : Interp, stream: Optional[nvcv.cuda.Stream] = None) -> nvcv.ImageBatchVarShape


	Executes the Rotate operation on the given cuda stream.

        See also:
            Refer to the CV-CUDA C API reference for the Rotate operator
            for more details and usage examples.

        Args:
            src (ImageBatchVarShape): Input image batch containing one or more images.
            dst (ImageBatchVarShape): Output image batch containing the result of the operation.
            angle_deg (Tensor): Angle used for rotation in degrees for each image.
            shift (Tensor): Value of shift in {x, y} directions to move the center at the same coord after rotation for each image.
            interpolation (Interp): Interpolation type used for transform.
            stream (Stream, optional): CUDA Stream on which to perform the operation.

        Returns:
            cvcuda.ImageBatchVarShape: The output image batch.

        Caution:
            Restrictions to several arguments may apply. Check the C
            API references of the CV-CUDA operator.
    )pbdoc");

    m.def("rotate_into", &VarShapeRotateInto, "dst"_a, "src"_a, "angle_deg"_a, "shift"_a, "interpolation"_a,
          py::kw_only(), "stream"_a = nullptr, R"pbdoc(

	cvcuda.rotate_into(dst:ImageBatchVarShape, src: nvcv.ImageBatchVarShape, angle_deg: double, shift: Tuple [double, double], interpolation : Interp, stream: Optional[nvcv.cuda.Stream] = None)

        Executes the Rotate operation on the given cuda stream.

        See also:
            Refer to the CV-CUDA C API reference for the Rotate operator
            for more details and usage examples.

        Args:
            src (ImageBatchVarShape): Input image batch containing one or more images.
            dst (ImageBatchVarShape): Output image batch containing the result of the operation.
            angle_deg (Tensor): Angle used for rotation in degrees for each image.
            shift (Tensor): Value of shift in {x, y} directions to move the center at the same coord after rotation for each image.
            interpolation (Interp): Interpolation type used for transform.
            stream (Stream, optional): CUDA Stream on which to perform the operation.

        Returns:
            None

        Caution:
            Restrictions to several arguments may apply. Check the C
            API references of the CV-CUDA operator.
    )pbdoc");
}

} // namespace cvcudapy

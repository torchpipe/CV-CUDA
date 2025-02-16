..
  # SPDX-FileCopyrightText: Copyright (c) 2022-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
  # SPDX-License-Identifier: Apache-2.0
  #
  # Licensed under the Apache License, Version 2.0 (the "License");
  # you may not use this file except in compliance with the License.
  # You may obtain a copy of the License at
  #
  # http://www.apache.org/licenses/LICENSE-2.0
  #
  # Unless required by applicable law or agreed to in writing, software
  # distributed under the License is distributed on an "AS IS" BASIS,
  # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  # See the License for the specific language governing permissions and
  # limitations under the License.

.. _python_classification:

Classification
====================

In this example, we use CVCUDA to accelerate the pre and post processing pipelines in the deep learning inference use case involving an image classification model. The deep learning model can utilize either PyTorch or TensorRT to run the inference. The pre-processing pipeline converts the input into the format required by the input layer of the model whereas the post processing pipeline converts the output produced by the model into a visualization-friendly format. We use the ResNet50 model (from torchvision) to generate the predictions. This sample can work on a single image or a folder full of images or on a single video. All images have to be in the JPEG format and with the same dimensions unless run under the batch size of one. Video has to be in mp4 format with a fixed frame rate. We use the torchnvjpeg library to read the images and NVIDIA's Video Processing Framework (VPF) to read/write videos.


**The exact pre-processing operations are:** ::

   Decode Data -> Resize -> Convert Datatype(Float) -> Normalize (to 0-1 range, mean and stddev) -> convert to NCHW

**The exact post-processing operations are:** ::

   Sorting the probabilities to get the top N -> Print the top N classes with the confidence scores


Writing the Sample App
----------------------

The classification sample app has been designed to be modular in all aspects. It imports and uses various modules such as data decoders, pipeline pre and post processors and the model inference. Some of these modules are defined in the same folder as the sample whereas the rest are defined in the common scripts folder for a wider re-use.

1. Modules used by this sample app that are defined in the common folder (i.e. not specific just to this sample) are the ``ImageBatchDecoderPyTorch`` for PyTorch based image decoding and ``VideoBatchDecoderVPF`` for VPF based video decoding.

2. Modules specific to this sample (i.e. defined in the classification sample folder) are ``PreprocessorCvcuda`` and ``PostprocessorCvcuda`` for CVCUDA based pre and post processing pipelines and ``ClassificationPyTorch`` and ``ClassificationTensorRT`` for the model inference.

The first stage in our pipeline is importing all necessary python modules. Apart from the modules described above, this also includes modules such as torch and torchvision, torchnvjpeg, vpf and the main package of CVCUDA (i.e. nvcv) among others. Be sure to import ``pycuda.driver`` before importing any other GPU packages like torch or cvcuda to ensure a proper initialization.

.. literalinclude:: ../../../../samples/classification/python/main.py
   :language: python
   :linenos:
   :start-after: begin_python_imports
   :end-before: end_python_imports
   :dedent:

Then we define the main function which helps us parse various configuration parameters used throughout this sample as command line
arguments. This sample allows configuring following parameters. All of them have their default values already set so that one can execute the sample without supplying any. Some of these arguments are shared across many other CVCUDA samples and hence come from the ``perf_utils.py`` class's ``get_default_arg_parser()`` method.

1. ``-i``, ``--input_path`` : Either a path to a JPEG image/MP4 video or a directory containing JPG images to use as input. When pointing to a directory, only JPG images will be read.
2. ``-o``, ``--output_dir`` : The directory where the outputs should be stored.
3. ``-th``, ``--target_img_height`` : The height to which you want to resize the input_image before running inference.
4. ``-tw``, ``--target_img_width`` : The width to which you want to resize the input_image before running inference.
5. ``-b``, ``--batch_size`` : The batch size used during inference. If only one image is used as input, the same input image will be read and used this many times. Useful for performance bench-marking.
6. ``-d``, ``--device_id``  : The GPU device to use for this sample.
7. ``-bk``, ``--backend``  : The inference backend to use. Currently supports PyTorch or TensorRT.


Once we are done parsing all the command line arguments, we would setup the ``CvCudaPerf`` object for any performance benchmarking needs and simply call the function ``run_sample`` with all those arguments.


.. literalinclude:: ../../../../samples/classification/python/main.py
   :language: python
   :linenos:
   :start-after: start_call_run_sample
   :end-before: end_call_run_sample
   :dedent:

The ``run_sample`` function is the primary function that runs this sample. It sets up the requested CUDA device, CUDA context and CUDA stream. CUDA streams help us execute CUDA operations on a non-default stream and enhances the overall performance. Additionally, NVTX markers are used throughout this sample (via ``CvCudaPerf``) to facilitate performance bench-marking using `NVIDIA NSIGHT systems <https://developer.nvidia.com/nsight-systems>`_ and ``benchmark.py``. In order to keep things simple, we are only creating one CUDA stream to run all the stages of this sample. The same stream is available in CVCUDA, PyTorch and TensorRT.

.. literalinclude:: ../../../../samples/classification/python/main.py
   :language: python
   :linenos:
   :start-after: begin_setup_gpu
   :end-before: end_setup_gpu
   :dedent:

Next, we instantiate various classes to help us run the sample. These classes are:

1. ``PreprocessorCvcuda`` : A CVCUDA based pre-processing pipeline for classification.
2. ``ImageBatchDecoderPyTorch`` : A PyTorch based image decoder to read the images.
3. ``VideoBatchDecoderVPF`` : A VPF based video decoder to read the video.
4. ``PostprocessorCvcuda`` : A post-processing pipeline for classification.
5. ``classificationPyTorch`` : A PyTorch based classification model to execute inference.
6. ``classificationTensorRT`` : A TensorRT based classification model to execute inference.


These classes are defined in modular fashion and exposes a uniform interface which allows easy plug-and-play in appropriate places. For example, one can use the same API to decode/encode images using PyTorch as that of decode/encode videos using VPF. Similarly, one can invoke the inference in the exact same way with PyTorch as with TensorRT.

Additionally, decoder interface also exposes start and join methods, making it easy to upgrade them to a multi-threading environment (if needed.) Such multi-threading capabilities are slated for a future release.

.. literalinclude:: ../../../../samples/classification/python/main.py
   :language: python
   :linenos:
   :start-after: begin_setup_stages
   :end-before: end_setup_stages
   :dedent:

With all of these components initialized, the overall data flow per a data batch looks like the following:

Decode batch -> Preprocess Batch -> Run Inference -> Post Process Batch -> Encode batch

.. literalinclude:: ../../../../samples/classification/python/main.py
   :language: python
   :linenos:
   :start-after: begin_pipeline
   :end-before: end_pipeline
   :dedent:


That's it for the classification sample. To understand more about how each stage in the pipeline works, please explore the following sections:

.. toctree::
    :maxdepth: 1

    PreprocessorCvcuda <classification/preprocessor_cvcuda>
    PostprocessorCvcuda <classification/postprocessor_cvcuda>
    ImageBatchDecoderPyTorch <commons/imagebatchdecoder_pytorch>
    VideoBatchDecoderVPF <commons/videobatchdecoder_vpf>
    ClassificationPyTorch <classification/classification_pytorch>
    ClassificationTensorRT <classification/classification_tensorrt>


Running the Sample
------------------

This sample can be invoked without any command-line arguments like the following. In that case it will use the default values. It uses TensorRT as the inference engine, tabby_tiger_cat.jpg as the input image and runs with batch size of 4. Upon the first run, generating serialized TensorRT model may take some time for a given batch size.


.. code-block:: bash

   python3 classification/python/main.py


To run it on a single image with batch size 4 with the default backend of TensorRT:

.. code-block:: bash

   python3 classification/python/main.py -i assets/images/tabby_tiger_cat.jpg -b 4


To run it on a folder worth of images with batch size 4 using the PyTorch backend instead of TensorRT:

.. code-block:: bash

   python3 classification/python/main.py -i assets/images/ -b 4 -bk pytorch


To run on a single video with batch size of 1:

.. code-block:: bash

   python classification/python/main.py -i assets/videos/pexels-ilimdar-avgezer-7081456.mp4 -b 1



Understanding the Output
------------------------


This sample takes as input the one or more images or one video and generates the classification probabilities for top 5 classes. Since this sample works on batches, sometimes the batch size and the number of images read may not be a perfect multiple. In such cases, the last batch may have a smaller batch size. If the batch size to anything above 1 for one image input case, the same image is fed in the entire batch and identical image masks are generated and saved for all of them.

The top 5 classification results for the tabby_cat_tiger.jpg image is as follows:

.. code-block:: bash

   user@machine:~/cvcuda/samples$ python3 classification/python/main.py -b 1
   [perf_utils:85] 2023-07-27 22:27:17 WARNING perf_utils is used without benchmark.py. Benchmarking mode is turned off.
   [perf_utils:89] 2023-07-27 22:27:17 INFO    Using CV-CUDA version: 0.5.0-beta
   [pipelines:35] 2023-07-27 22:27:17 INFO     Using CVCUDA as preprocessor.
   [torch_utils:77] 2023-07-27 22:27:17 INFO   Using torchnvjpeg as decoder.
   [pipelines:122] 2023-07-27 22:27:17 INFO    Using CVCUDA as post-processor.
   [model_inference:230] 2023-07-27 22:27:18 INFO  Using TensorRT as the inference engine.
   [classification:161] 2023-07-27 22:27:18 INFO   Processing batch 0
   [pipelines:144] 2023-07-27 22:27:18 INFO   Classification probabilities for the image: 1 of 1
   [pipelines:151] 2023-07-27 22:27:18 INFO     tiger cat: 20.844%
   [pipelines:151] 2023-07-27 22:27:18 INFO     tabby: 18.831%
   [pipelines:151] 2023-07-27 22:27:18 INFO     Egyptian cat: 4.073%
   [pipelines:151] 2023-07-27 22:27:18 INFO     lynx: 0.276%
   [pipelines:151] 2023-07-27 22:27:18 INFO     Persian cat: 0.228%

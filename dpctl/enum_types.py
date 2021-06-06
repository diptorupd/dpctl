#                      Data Parallel Control (dpctl)
#
# Copyright 2020 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Defines Python enumeration types for SYCL enumerations.

This module provides two enumeration types corresponding to SYCL's
backend and device_type enumerations.

"""
from enum import Enum, auto

__all__ = [
    "device_type",
    "backend_type",
]


class device_type(Enum):
    """
    An enumeration of supported SYCL device types.

    ==================   ============
    Device type          Enum value
    ==================   ============
    all                  0
    accelerator          1
    automatic            2
    cpu                  3
    custom               4
    gpu                  5
    host_device          6
    ==================   ============
    """

    all = auto()
    accelerator = auto()
    automatic = auto()
    cpu = auto()
    custom = auto()
    gpu = auto()
    host_device = auto()


class backend_type(Enum):
    """
    An enumeration of supported SYCL backends.

    ==================   ============
    Name of backend      Enum value
    ==================   ============
    all                  0
    cuda                 1
    host                 2
    level_zero           3
    opencl               4
    ==================   ============

    """

    all = auto()
    cuda = auto()
    host = auto()
    level_zero = auto()
    opencl = auto()

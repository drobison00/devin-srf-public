# SPDX-FileCopyrightText: Copyright (c) 2021-2022, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

import logging

import pytest

import srf


def test_module_registry():
    registry = srf.ModuleRegistry()
    # registry.register_module(simple_mod_name, release_version, simple_mod_func);


def test_contains_namespace():
    registry = srf.ModuleRegistry()

    assert registry.contains_namespace('xyz') is not True
    assert registry.contains_namespace('default')


def test_contains():
    registry = srf.ModuleRegistry()

    assert registry.contains('SimpleModule', 'srf_unittest')
    assert registry.contains('SourceModule', 'srf_unittest')
    assert registry.contains('SinkModule', 'srf_unittest')
    assert registry.contains('SimpleModule') is not True


def test_find_module():

    config = {"config_key_1": True}

    registry = srf.ModuleRegistry()

    simple_mod = registry.find_module("SimpleModule", "srf_unittest", "ModuleInitializationTest_mod", config)

    assert "config_key_1" in simple_mod.config()

    with pytest.raises(Exception):
        simple_mod = registry.find_module("SimpleModule", "default", "ModuleInitializationTest_mod", config)


def test_is_version_compatible():
    registry = srf.ModuleRegistry()

    release_version = [22, 11, 0]
    old_release_version = [22, 10, 0]
    no_version_patch = [22, 10]
    no_version_minor_and_patch = [22]

    assert registry.is_version_compatible(release_version)
    assert registry.is_version_compatible(old_release_version) is not True
    assert registry.is_version_compatible(no_version_patch) is not True
    assert registry.is_version_compatible(no_version_minor_and_patch) is not True


def test_unregister_module():
    registry = srf.ModuleRegistry()

    registry_namespace = "srf_unittest2"
    simple_mod_name = "SimpleModule"

    # TODO Need to register the module before unregistering the module.
    # registry.unregister_module(simple_mod_name, registry_namespace)

    with pytest.raises(Exception):
        registry.unregister_module(simple_mod_name, registry_namespace)

    with pytest.raises(Exception):
        registry.unregister_module(simple_mod_name, False)

    registry.unregister_module(simple_mod_name)
    registry.unregister_module(simple_mod_name, True)
    registry.unregister_module(simple_mod_name, registry_namespace, True)


# def test_registered_modules():
#     registry = srf.ModuleRegistry()

if (__name__ in ("__main__", )):
    test_contains_namespace()
    test_contains()
    test_find_module()
    test_is_version_compatible()
    test_unregister_module()
    # test_registered_modules()

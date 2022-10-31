/**
 * SPDX-FileCopyrightText: Copyright (c) 2021-2022, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#pragma once
#include "srf/experimental/modules/module_registry.hpp"

namespace srf::pysrf {

// Export everything in the srf::pysrf namespace by default since we compile with -fvisibility=hidden
#pragma GCC visibility push(default)

class ModuleRegistryProxy
{
  public:
    ModuleRegistryProxy() = default;

    static bool contains_namespace(ModuleRegistryProxy& self, const std::string& registry_namespace)
    {
        return srf::modules::ModuleRegistry::contains_namespace(registry_namespace);
    }

    static bool contains(ModuleRegistryProxy& self, const std::string& name, const std::string& registry_namespace)
    {
        return srf::modules::ModuleRegistry::contains(name, registry_namespace);
    }

    static std::map<std::string, std::vector<std::string>> registered_modules(ModuleRegistryProxy& self){
        return srf::modules::ModuleRegistry::registered_modules();
    }

    static void unregister_module(ModuleRegistryProxy& self, const std::string& name, const std::string& registry_namespace, bool optional){
        return srf::modules::ModuleRegistry::unregister_module(name, registry_namespace, optional);
    }

    static void unregister_module(ModuleRegistryProxy& self, const std::string& name, const std::string& registry_namespace){
        return srf::modules::ModuleRegistry::unregister_module(name, registry_namespace);
    }

    static bool is_version_compatible(ModuleRegistryProxy& self, const std::vector<unsigned int>& release_version){
        return srf::modules::ModuleRegistry::is_version_compatible(release_version);
    }

    std::shared_ptr<srf::modules::SegmentModule> ModuleRegistry::find_module(
                                                        ModuleRegistryProxy& self,
                                                        const std::string& module_id,
                                                        const std::string& registry_namespace,
                                                        std::string module_name,
                                                        py::dict config)
    {
    auto json_config = cast_from_pyobject(config);
    auto fn_module_constructor = srf::modules::ModuleRegistry::find_module(module_id, registry_namespace);
    auto module                = std::move(fn_module_constructor(std::move(module_name), std::move(config)));

    return std::move(module);
    }
    // TODO(devin)
    // register_module

    // TODO(bhargav)
};
#pragma GCC visibility pop
} // namespace srf::pysrf

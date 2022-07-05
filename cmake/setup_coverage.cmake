#=============================================================================
# SPDX-FileCopyrightText: Copyright (c) 2020-2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#=============================================================================

# ######################################################################################################################
# * CMake properties ------------------------------------------------------------------------------

list(APPEND CMAKE_MESSAGE_CONTEXT "coverage")

# Include coverage tools if enabled
if(SRF_WITH_CODECOV)
  include(cmake/LibCodeCoverage.cmake)

  message("SRF_WITH_CODECOV is ON, configuring report exclusions and setting up coverage build targets")
  set(CODECOV_REPORT_EXCLUSIONS
      ".cache/*"
      "tests/*"
      "${CMAKE_BINARY_DIR}/protos/*" # Remove this if/when we get protobuf code unit tested.
      "python/srf/tests/*"
      "python/srf/_pysrf/tests/*"
      "src/tests/*"
      )

  # setup_target_for_coverage_lcov(
  #     NAME lcov-report
  #     EXCLUDE ${CODECOV_REPORT_EXCLUSIONS}
  # )

  setup_target_for_coverage_gcovr_xml(
      NAME gcovr-xml-report
      EXCLUDE ${CODECOV_REPORT_EXCLUSIONS}
  )

  setup_target_for_coverage_gcovr_html(
      NAME gcovr-html-report
      EXCLUDE ${CODECOV_REPORT_EXCLUSIONS}
  )

  # Anaconda doesn't seem to have a fastcov package -- disable for now
  # setup_target_for_coverage_fastcov(
  #     NAME fastcov-report
  #     EXCLUDE ".cache/*"
  # )
endif()


#[=======================================================================[
@brief : Given a target, configure the target with appropriate gcov if
SRF_WITH_CODECOV is enabled.

ex. configure_codecov(target_name)
results --

configure_codecov <TARGET_NAME>
#]=======================================================================]
function(configure_codecov target)
  if (${SRF_WITH_CODECOV} STREQUAL "ON")
    message("Configuring target <${target}> for code coverage.")
    append_coverage_compiler_flags_to_target("${target}")
  endif()
endfunction()

list(POP_BACK CMAKE_MESSAGE_CONTEXT)

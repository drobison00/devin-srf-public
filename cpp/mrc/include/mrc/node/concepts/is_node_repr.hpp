//
// Created by drobison on 1/20/23.
//

#pragma once

#include "mrc/segment/object.hpp"
#include "mrc/type_traits.hpp"

#include <concepts>

template<typename TypeT>
concept MRCObject = mrc::segment::is_object_v<TypeT>;

template<typename TypeT>
concept MRCObjectSharedPtr = mrc::segment::is_object_shared_ptr_v<TypeT>;

template<typename TypeT>
concept MRCObjectProperties = std::is_same_v<TypeT, mrc::segment::ObjectProperties>;

template<typename TypeT>
concept MRCObjectPropertiesSharedPtr = std::is_same_v<TypeT, std::shared_ptr<mrc::segment::ObjectProperties>>;

template<typename TypeT>
concept ObjectPropertiesRep = MRCObject<TypeT> || MRCObjectSharedPtr<TypeT>
                              || MRCObjectProperties<TypeT> || MRCObjectPropertiesSharedPtr<TypeT>
                              || std::is_convertible_v<TypeT, std::string>;

template<typename TypeT>
concept EdgeEndpoint = mrc::is_base_of_template<mrc::edge::IWritableAcceptor, TypeT>::value ||
                       mrc::is_base_of_template<mrc::edge::IWritableProvider, TypeT>::value ||
                       mrc::is_base_of_template<mrc::edge::IReadableProvider, TypeT>::value ||
                       mrc::is_base_of_template<mrc::edge::IReadableAcceptor, TypeT>::value ||
                       std::is_base_of_v<mrc::edge::IWritableProviderBase, TypeT> ||
                       std::is_base_of_v<mrc::edge::IWritableAcceptorBase, TypeT> ||
                       std::is_base_of_v<mrc::edge::IReadableProviderBase, TypeT> ||
                       std::is_base_of_v<mrc::edge::IReadableAcceptorBase, TypeT>;

template<typename TypeT>
concept Hmm = ObjectPropertiesRep<TypeT> || EdgeEndpoint<TypeT>;

// Given a TypeT, that is an ObjectPropertiesRep


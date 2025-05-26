// ID666ExtendedTag.h - Declares the ID666ExtendedTag class.
//
// Copyright (C) 2025 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ID666_EXTENDED_TAG_H
#define ID666_EXTENDED_TAG_H

#include <memory>
#include <vector>
#include "SpcStruct.h"
#include "SpcTextField.h"
#include "SpcEmulatorField.h"
#include "SpcDateField.h"
#include "SpcNumericField.h"
#include "SpcTrackField.h"
#include "SpcBinaryField.h"

struct ID666ExtendedTag : public SpcStruct
{
    std::shared_ptr<SpcTextField> songName;
    std::shared_ptr<SpcTextField> gameName;
    std::shared_ptr<SpcTextField> artistName;
    std::shared_ptr<SpcTextField> dumperName;
    std::shared_ptr<SpcDateField> dateDumped;
    std::shared_ptr<SpcEmulatorField> emulatorUsed;
    std::shared_ptr<SpcTextField> comments;
    std::shared_ptr<SpcTextField> ostTitle;
    std::shared_ptr<SpcNumericField> ostDisc;
    std::shared_ptr<SpcTrackField> ostTrack;
    std::shared_ptr<SpcTextField> publisherName;
    std::shared_ptr<SpcNumericField> copyrightYear;
    std::shared_ptr<SpcNumericField> introLength;
    std::shared_ptr<SpcNumericField> loopLength;
    std::shared_ptr<SpcNumericField> endLength;
    std::shared_ptr<SpcNumericField> fadeLength;
    std::shared_ptr<SpcBinaryField> mutedVoices;
    std::shared_ptr<SpcNumericField> loopTimes;
    std::shared_ptr<SpcNumericField> preampLevel;

    //ID666ExtendedTag();

    /// @brief Provides a vector of raw pointers to the structure's fields.
    ///
    /// This method is primarily intended for use by Binary::Stream and its
    /// derivatives for reading the fields from and to those streams.
    /// Access the fields directly rather than via this method.
    ///
    /// @return The vector containing the raw pointers for the field.
    //std::vector<Binary::DataField*> Fields() override;

    /// @brief Gets list of pointers to this struct's fields.
    ///
    /// This method will be called by the ToString() method to output each
    /// field as a formatted string on its own line of the format,
    ///
    /// label: value
    ///
    /// This method is also called by the Fields() method to get a pointer to
    /// each field so SpcFileStream can read this struct from and write it to
    /// an SPC file in a cross platform way, preserving the order, size, and
    /// endianness of each field no matter which architecture the program runs
    /// on.
    ///
    /// Structs that inherit from this struct should provide an implementation
    /// for this method that generates the vector in the correct order.
    ///
    /// @return A vector containing pointers to the SpcFields.
    std::vector<SpcField*> SpcFields() const override;
};

#endif

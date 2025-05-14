// SpcNumericField.h - Declares the SpcNumericField class.
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

#ifndef SPC_NUMERIC_FIELD_H
#define SPC_NUMERIC_FIELD_H

#include <string>
#include "IntField.h"
#include "RawField.h"
#include "SpcField.h"

class SpcNumericField : public SpcField
{
public:
    SpcNumericField(std::string label, uintmax_t offset, size_t size) 
        : SpcField{ label, offset, size }
    { };

    bool IsZero() const;

    bool IsText() const;

    /// @brief Detects the correct value based on if the field is text or not.
    ///
    /// Because a numeric field could contain either a text or binary
    /// representation of the value, this method attempts to determine the
    /// correct value based on the detected type. Note that this may be
    /// incorrect 
    /// @return The detected value.
    unsigned long long DetectValue() const;

    /// @brief Gets the value assuming the field is binary.
    /// @return The value of the field.
    unsigned long long Value() const;

    std::string ToString() const override;

    std::string ToString(Binary::StringFormat format) const override
    {
        return Binary::RawField::ToString(format);
    }
};

#endif
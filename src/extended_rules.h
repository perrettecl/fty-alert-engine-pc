/*  =========================================================================
    extended_rules - Rule classes implementation

    Copyright (C) 2019 - 2019 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#ifndef EXTENDED_RULES_H_INCLUDED
#define EXTENDED_RULES_H_INCLUDED

#include <string>
#include <cxxtools/serializationinfo.h>
#include <vector>
#include <map>

// force proper header order
#include "rule.h"
#include "lua_evaluate.h"

#ifdef __cplusplus
extern "C" {
#endif

///  Self test of this class
FTY_ALERT_ENGINE_PRIVATE void
    extended_rules_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

class SingleRule : public Rule, public DecoratorLuaEvaluate {
    protected:
        //internal functions
        void loadFromSerializedObject (const cxxtools::SerializationInfo &si);
        void saveToSerializedObject (cxxtools::SerializationInfo &si) const;
    public:
        // ctors, dtors, =
        SingleRule (const std::string name, const Rule::VectorStrings metrics, const Rule::VectorStrings assets,
                const Rule::VectorStrings categories, const ResultsMap results, std::string code,
                DecoratorLuaEvaluate::VariableMap variables);
        SingleRule (const cxxtools::SerializationInfo &si) : Rule (si) { loadFromSerializedObject (si); };
        SingleRule (const std::string json) : Rule (json) { };
        virtual ~SingleRule () {};
        // virtual functions
        virtual std::string whoami () const { return std::string ("single"); };
        virtual Rule::VectorStrings evaluate (const Rule::VectorStrings &metrics);
};

class PatternRule : public Rule, public DecoratorLuaEvaluate {
    protected:
        //internal functions
        void loadFromSerializedObject (const cxxtools::SerializationInfo &si);
        void saveToSerializedObject (cxxtools::SerializationInfo &si) const;
    public:
        // ctors, dtors, =
        PatternRule (const std::string name, const Rule::VectorStrings metrics, const Rule::VectorStrings assets,
                const Rule::VectorStrings categories, const ResultsMap results, std::string code,
                DecoratorLuaEvaluate::VariableMap variables);
        PatternRule (const cxxtools::SerializationInfo &si) : Rule (si) { loadFromSerializedObject (si); };
        PatternRule (const std::string json) : Rule (json) { };
        virtual ~PatternRule () {};
        // virtual functions
        virtual std::string whoami () const { return std::string ("pattern"); };
        virtual Rule::VectorStrings evaluate (const Rule::VectorStrings &metrics);
        bool metricNameMatchesPattern (std::string &metric_name);
};

class ThresholdRule : public Rule, public DecoratorLuaEvaluate {
    protected:
        //internal functions
        void loadFromSerializedObject (const cxxtools::SerializationInfo &si);
        void saveToSerializedObject (cxxtools::SerializationInfo &si) const;
    public:
        // ctors, dtors, =
        ThresholdRule (const std::string name, const Rule::VectorStrings metrics, const Rule::VectorStrings assets,
                const Rule::VectorStrings categories, const ResultsMap results, std::string code,
                DecoratorLuaEvaluate::VariableMap variables);
        ThresholdRule (const cxxtools::SerializationInfo &si) : Rule (si) { loadFromSerializedObject (si); };
        ThresholdRule (const std::string json) : Rule (json) { };
        virtual ~ThresholdRule () {};
        // virtual functions
        virtual std::string whoami () const { return std::string ("threshold"); };
        virtual Rule::VectorStrings evaluate (const Rule::VectorStrings &metrics);
};

class FlexibleRule : public Rule, public DecoratorLuaEvaluate {
    protected:
        /// store list of models for better matching
        Rule::VectorStrings models_;

        //internal functions
        void loadFromSerializedObject (const cxxtools::SerializationInfo &si);
        void saveToSerializedObject (cxxtools::SerializationInfo &si) const;
    public:
        // ctors, dtors, =
        FlexibleRule (const std::string name, const Rule::VectorStrings metrics, const Rule::VectorStrings assets,
                const Rule::VectorStrings categories, const ResultsMap results, std::string code,
                DecoratorLuaEvaluate::VariableMap variables);
        FlexibleRule (const cxxtools::SerializationInfo &si) : Rule (si) { loadFromSerializedObject (si); };
        FlexibleRule (const std::string json);
        virtual ~FlexibleRule () {};
        // virtual functions
        virtual std::string whoami () const { return std::string ("flexible"); };
        virtual Rule::VectorStrings evaluate (const Rule::VectorStrings &metrics);
};

#endif

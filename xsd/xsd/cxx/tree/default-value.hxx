// file      : xsd/cxx/tree/default-value.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_TREE_DEFAULT_VALUE_HXX
#define XSD_CXX_TREE_DEFAULT_VALUE_HXX

#include <libxsd-frontend/semantic-graph.hxx>
#include <libxsd-frontend/traversal.hxx>

#include <xsd/cxx/tree/elements.hxx>

namespace CXX
{
  namespace Tree
  {
    struct IsLiteralValue: IsFundamentalType, Traversal::Complex
    {
      IsLiteralValue (bool& r);

      virtual void
      traverse (SemanticGraph::Complex&);

    private:
      Traversal::Inherits inherits_;
    };

    struct LiteralValue: Traversal::Fundamental::Byte,
                         Traversal::Fundamental::UnsignedByte,
                         Traversal::Fundamental::Short,
                         Traversal::Fundamental::UnsignedShort,
                         Traversal::Fundamental::Int,
                         Traversal::Fundamental::UnsignedInt,
                         Traversal::Fundamental::Long,
                         Traversal::Fundamental::UnsignedLong,
                         Traversal::Fundamental::Integer,
                         Traversal::Fundamental::NonPositiveInteger,
                         Traversal::Fundamental::NonNegativeInteger,
                         Traversal::Fundamental::PositiveInteger,
                         Traversal::Fundamental::NegativeInteger,

                         Traversal::Fundamental::Boolean,

                         Traversal::Fundamental::Float,
                         Traversal::Fundamental::Double,
                         Traversal::Fundamental::Decimal,

                         Traversal::Complex,

                         Context
    {
      LiteralValue (Context&);

      String
      dispatch (SemanticGraph::Node& type, String const& value);

      // Handle inheritance.
      //
      virtual void
      traverse (SemanticGraph::Complex&);

      // Boolean.
      //
      virtual void
      traverse (SemanticGraph::Fundamental::Boolean&);

      // Integral types.
      //
      virtual void
      traverse (SemanticGraph::Fundamental::Byte&);

      virtual void
      traverse (SemanticGraph::Fundamental::UnsignedByte&);

      virtual void
      traverse (SemanticGraph::Fundamental::Short&);

      virtual void
      traverse (SemanticGraph::Fundamental::UnsignedShort&);

      virtual void
      traverse (SemanticGraph::Fundamental::Int&);

      virtual void
      traverse (SemanticGraph::Fundamental::UnsignedInt&);

      virtual void
      traverse (SemanticGraph::Fundamental::Long&);

      virtual void
      traverse (SemanticGraph::Fundamental::UnsignedLong&);

      virtual void
      traverse (SemanticGraph::Fundamental::Integer&);

      virtual void
      traverse (SemanticGraph::Fundamental::NonPositiveInteger&);

      virtual void
      traverse (SemanticGraph::Fundamental::NonNegativeInteger&);

      virtual void
      traverse (SemanticGraph::Fundamental::PositiveInteger&);

      virtual void
      traverse (SemanticGraph::Fundamental::NegativeInteger&);

      // Floats.
      //
      virtual void
      traverse (SemanticGraph::Fundamental::Float&);

      virtual void
      traverse (SemanticGraph::Fundamental::Double&);

      virtual void
      traverse (SemanticGraph::Fundamental::Decimal&);

    private:
      String value_;
      String literal_;

      Traversal::Inherits inherits_;
    };

    // Some initialization (e.g., list) need a function body while others
    // (e.g., *binary) require extra data.
    //
    struct InitKind: Traversal::List,
                     Traversal::Complex,

                     Traversal::Fundamental::Base64Binary,
                     Traversal::Fundamental::HexBinary,

                     Traversal::Fundamental::NameTokens,
                     Traversal::Fundamental::IdRefs,
                     Traversal::Fundamental::Entities
    {
      enum Kind
      {
        simple,
        data,
        function
      };

      // Should be simple initially.
      //
      InitKind (Kind& r);

      virtual void
      traverse (SemanticGraph::List&);

      virtual void
      traverse (SemanticGraph::Complex&);

      virtual void
      traverse (SemanticGraph::Fundamental::Base64Binary&);

      virtual void
      traverse (SemanticGraph::Fundamental::HexBinary&);

      virtual void
      traverse (SemanticGraph::Fundamental::NameTokens&);

      virtual void
      traverse (SemanticGraph::Fundamental::IdRefs&);

      virtual void
      traverse (SemanticGraph::Fundamental::Entities&);

    private:
      Kind& r_;
      Traversal::Inherits inherits_;
    };

    struct InitValue: Traversal::List,
                      Traversal::Union,
                      Traversal::Complex,

                      Traversal::AnyType,
                      Traversal::AnySimpleType,

                      Traversal::Fundamental::String,
                      Traversal::Fundamental::NormalizedString,
                      Traversal::Fundamental::Token,
                      Traversal::Fundamental::Name,
                      Traversal::Fundamental::NameToken,
                      Traversal::Fundamental::NameTokens,
                      Traversal::Fundamental::NCName,
                      Traversal::Fundamental::Language,

                      Traversal::Fundamental::QName,

                      Traversal::Fundamental::Id,
                      Traversal::Fundamental::IdRef,
                      Traversal::Fundamental::IdRefs,

                      Traversal::Fundamental::AnyURI,

                      Traversal::Fundamental::Base64Binary,
                      Traversal::Fundamental::HexBinary,

                      Traversal::Fundamental::Date,
                      Traversal::Fundamental::DateTime,
                      Traversal::Fundamental::Duration,
                      Traversal::Fundamental::Day,
                      Traversal::Fundamental::Month,
                      Traversal::Fundamental::MonthDay,
                      Traversal::Fundamental::Year,
                      Traversal::Fundamental::YearMonth,
                      Traversal::Fundamental::Time,

                      Traversal::Fundamental::Entity,
                      Traversal::Fundamental::Entities,

                      Context
    {
      InitValue (Context&);

      void
      data (String const& data)
      {
        data_ = data;
        dispatch_count_ = 0;
      }

      void
      dispatch (SemanticGraph::Node& type, String const& value);

      virtual void
      traverse (SemanticGraph::List&);

      virtual void
      traverse (SemanticGraph::Union&);

      virtual void
      traverse (SemanticGraph::Complex&);

      // anyType & anySimpleType.
      //
      virtual void
      traverse (SemanticGraph::AnyType&);

      virtual void
      traverse (SemanticGraph::AnySimpleType&);

      // Strings.
      //
      virtual void
      traverse (SemanticGraph::Fundamental::String&);

      virtual void
      traverse (SemanticGraph::Fundamental::NormalizedString&);

      virtual void
      traverse (SemanticGraph::Fundamental::Token&);

      virtual void
      traverse (SemanticGraph::Fundamental::NameToken&);

      virtual void
      traverse (SemanticGraph::Fundamental::NameTokens&);

      virtual void
      traverse (SemanticGraph::Fundamental::Name&);

      virtual void
      traverse (SemanticGraph::Fundamental::NCName&);

      virtual void
      traverse (SemanticGraph::Fundamental::Language&);

      // Qualified name.
      //
      virtual void
      traverse (SemanticGraph::Fundamental::QName&);

      // ID/IDREF.
      //
      virtual void
      traverse (SemanticGraph::Fundamental::Id&);

      virtual void
      traverse (SemanticGraph::Fundamental::IdRef&);

      virtual void
      traverse (SemanticGraph::Fundamental::IdRefs&);

      // URI.
      //
      virtual void
      traverse (SemanticGraph::Fundamental::AnyURI&);

      // Binary.
      //
      virtual void
      traverse (SemanticGraph::Fundamental::Base64Binary&);

      virtual void
      traverse (SemanticGraph::Fundamental::HexBinary&);

      // Date/time.
      //
      virtual void
      traverse (SemanticGraph::Fundamental::Date&);

      virtual void
      traverse (SemanticGraph::Fundamental::DateTime&);

      virtual void
      traverse (SemanticGraph::Fundamental::Duration&);

      virtual void
      traverse (SemanticGraph::Fundamental::Day&);

      virtual void
      traverse (SemanticGraph::Fundamental::Month&);

      virtual void
      traverse (SemanticGraph::Fundamental::MonthDay&);

      virtual void
      traverse (SemanticGraph::Fundamental::Year&);

      virtual void
      traverse (SemanticGraph::Fundamental::YearMonth&);

      virtual void
      traverse (SemanticGraph::Fundamental::Time&);

      // Entity.
      //
      virtual void
      traverse (SemanticGraph::Fundamental::Entity&);

      virtual void
      traverse (SemanticGraph::Fundamental::Entities&);

    private:
      void
      string_sequence_type (SemanticGraph::Type& element_type);

      void
      time_zone (size_t pos);

    private:
      String value_;
      String data_;
      size_t dispatch_count_;
      MemberTypeName type_name_;
      LiteralValue literal_value_;
    };
  }
}

#endif // XSD_CXX_TREE_DEFAULT_VALUE_HXX

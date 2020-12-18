// file      : xsd/cxx/tree/default-value.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd/cxx/tree/default-value.hxx>

using std::hex;
using std::dec;

namespace CXX
{
  namespace Tree
  {
    namespace
    {
      void
      normalize (String& s)
      {
        size_t n (s.size ());

        for (size_t i (0); i < n; ++i)
        {
          wchar_t& c (s[i]);

          if (c == 0x0D || // carriage return
              c == 0x09 || // tab
              c == 0x0A)
            c = 0x20;
        }
      }

      void
      collapse (String& s)
      {
        size_t n (s.size ()), j (0);
        bool subs (false), trim (true);

        for (size_t i (0); i < n; ++i)
        {
          wchar_t c (s[i]);

          if (c == 0x20 || c == 0x09 || c == 0x0A)
            subs = true;
          else
          {
            if (subs)
            {
              subs = false;

              if (!trim)
                s[j++] = 0x20;
            }

            if (trim)
              trim = false;

            s[j++] = c;
          }
        }

        s.resize (j);
      }

      void
      strip_zeros (String& s)
      {
        size_t n (s.size ()), i (0);

        if (n > 0 && (s[i] == '-' || s[i] == '+'))
          i++;

        size_t j (i);

        bool strip (true);

        for (; i < n; ++i)
        {
          wchar_t c (s[i]);

          if (c == '0')
          {
            if (!strip)
              s[j++] = c;
          }
          else
          {
            s[j++] = c;

            if (strip)
              strip = false;
          }
        }

        if (strip && j < n)
          s[j++] = '0'; // There was nothing except zeros so add one back.

        s.resize (j);
      }

      void
      make_float (String& s)
      {
        if (s.find ('.') == String::npos &&
            s.find ('e') == String::npos &&
            s.find ('E') == String::npos)
          s += L".0";
      }
    }

    //
    // IsLiteralValue
    //

    IsLiteralValue::
    IsLiteralValue (bool& r)
        : IsFundamentalType (r)
    {
      *this >> inherits_ >> *this;
    }

    void IsLiteralValue::
    traverse (SemanticGraph::Complex& c)
    {
      inherits (c);
    }

    //
    // LiteralValue
    //

    LiteralValue::
    LiteralValue (Context& c)
        : Context (c)
    {
      *this >> inherits_ >> *this;
    }

    String LiteralValue::
    dispatch (SemanticGraph::Node& type, String const& value)
    {
      literal_.clear ();
      value_ = value;
      Traversal::NodeBase::dispatch (type);
      return literal_;
    }

    void LiteralValue::
    traverse (SemanticGraph::Complex& c)
    {
      inherits (c);
    }

    // Boolean.
    //
    void LiteralValue::
    traverse (SemanticGraph::Fundamental::Boolean&)
    {
      collapse (value_);
      literal_ = (value_ == L"true" || value_ == L"1") ? L"true" : L"false";
    }

    // Integral types.
    //
    void LiteralValue::
    traverse (SemanticGraph::Fundamental::Byte&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::UnsignedByte&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"U";
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::Short&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::UnsignedShort&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"U";
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::Int&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::UnsignedInt&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"U";
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::Long&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
      literal_ += L"LL";
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::UnsignedLong&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_;
      literal_ += L"ULL";
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::Integer&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"LL";
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::NonPositiveInteger&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"LL";
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::NonNegativeInteger&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"ULL";
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::PositiveInteger&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"ULL";
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::NegativeInteger&)
    {
      collapse (value_);
      strip_zeros (value_);
      literal_ = value_ + L"LL";
    }

    // Floats.
    //
    void LiteralValue::
    traverse (SemanticGraph::Fundamental::Float& t)
    {
      collapse (value_);

      if (value_ == L"NaN")
      {
        literal_ = L"::std::numeric_limits< " + fq_name (t) +
          L" >::quiet_NaN ()";
      }
      else if (value_ == L"INF")
      {
        literal_ = L"::std::numeric_limits< " + fq_name (t) +
          L" >::infinity ()";
      }
      else if (value_ == L"-INF")
      {
        literal_ = L"- ::std::numeric_limits< " + fq_name (t) +
          L" >::infinity ()";
      }
      else
      {
        strip_zeros (value_);
        make_float (value_);
        literal_ = value_ + L"F";
      }
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::Double& t)
    {
      collapse (value_);

      if (value_ == L"NaN")
      {
        literal_ = L"::std::numeric_limits< " + fq_name (t) +
          L" >::quiet_NaN ()";
      }
      else if (value_ == L"INF")
      {
        literal_ = L"::std::numeric_limits< " + fq_name (t) +
          L" >::infinity ()";
      }
      else if (value_ == L"-INF")
      {
        literal_ = L"- ::std::numeric_limits< " + fq_name (t) +
          L" >::infinity ()";
      }
      else
      {
        strip_zeros (value_);
        make_float (value_);
        literal_ = value_;
      }
    }

    void LiteralValue::
    traverse (SemanticGraph::Fundamental::Decimal&)
    {
      collapse (value_);
      strip_zeros (value_);
      make_float (value_);
      literal_ = value_;
    }

    //
    // InitKind
    //

    InitKind::
    InitKind (Kind& r)
        : r_ (r)
    {
      *this >> inherits_ >> *this;
    }

    void InitKind::
    traverse (SemanticGraph::List&)
    {
      r_ = function;
    }

    void InitKind::
    traverse (SemanticGraph::Complex& c)
    {
      inherits (c);
    }

    void InitKind::
    traverse (SemanticGraph::Fundamental::Base64Binary&)
    {
      r_ = data;
    }

    void InitKind::
    traverse (SemanticGraph::Fundamental::HexBinary&)
    {
      r_ = data;
    }

    void InitKind::
    traverse (SemanticGraph::Fundamental::NameTokens&)
    {
      r_ = function;
    }

    void InitKind::
    traverse (SemanticGraph::Fundamental::IdRefs&)
    {
      r_ = function;
    }

    void InitKind::
    traverse (SemanticGraph::Fundamental::Entities&)
    {
      r_ = function;
    }

    //
    // InitValue
    //

    InitValue::
    InitValue (Context& c)
        : Context (c), type_name_ (c), literal_value_ (c)
    {
    }

    void InitValue::
    dispatch (SemanticGraph::Node& type, String const& value)
    {
      value_ = value;
      Traversal::NodeBase::dispatch (type);
    }

    void InitValue::
    traverse (SemanticGraph::List& l)
    {
      collapse (value_);

      if (!value_)
        return;

      SemanticGraph::Type& t (l.argumented ().type ());

      String ov (value_);
      size_t b (0);

      for (size_t e (ov.find (' ')); ; e = ov.find (' ', b))
      {
        String v (ov, b, e != String::npos ? e - b : e);

        os << "{";
        type_name_.dispatch (t);
        os << " tmp (";

        String lit (literal_value_.dispatch (t, v));

        if (lit)
          os << lit;
        else
        {
          value_ = v;
          Traversal::NodeBase::dispatch (t);
        }

        os << ");"
           << "r.push_back (tmp);"
           << "}";

        if (e == String::npos)
          break;

        b = e + 1;
      }

      value_ = ov;
    }

    void InitValue::
    traverse (SemanticGraph::Union&)
    {
      os << strlit (value_);
    }

    void InitValue::
    traverse (SemanticGraph::Complex& c)
    {
      Traversal::NodeBase::dispatch (ultimate_base (c));
    }

    // anyType & anySimpleType.
    //
    void InitValue::
    traverse (SemanticGraph::AnyType& t)
    {
      os << fq_name (t) << " (" << strlit (value_) << ")";
    }

    void InitValue::
    traverse (SemanticGraph::AnySimpleType& t)
    {
      os << fq_name (t) << " (" << strlit (value_) << ")";
    }

    // Strings.
    //
    void InitValue::
    traverse (SemanticGraph::Fundamental::String&)
    {
      os << strlit (value_);
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::NormalizedString&)
    {
      normalize (value_);
      os << strlit (value_);
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::Token&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::NameToken&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::NameTokens&)
    {
      string_sequence_type (
        dynamic_cast<SemanticGraph::Type&> (
          xs_ns ().find ("NMTOKEN").first->named ()));
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::Name&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::NCName&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::Language&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    // Qualified name.
    //
    void InitValue::
    traverse (SemanticGraph::Fundamental::QName& t)
    {
      size_t p (value_.rfind ('#'));

      if (p != String::npos)
      {
        String ns (value_, 0, p);
        String qname (value_, p + 1, String::npos);

        collapse (ns);
        collapse (qname);

        p = qname.find (':');

        String name;
        if (p != String::npos)
          name.assign (qname, p + 1, String::npos);
        else
          name = qname;

        os << fq_name (t) << " (" << strlit (ns) << ", " <<
          strlit (name) << ")";
      }
      else
      {
        // Unqualified name.
        //
        collapse (value_);
        os << fq_name (t) << " (" << strlit (value_) << ")";
      }
    }

    // ID/IDREF.
    //
    void InitValue::
    traverse (SemanticGraph::Fundamental::Id&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::IdRef&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::IdRefs&)
    {
      string_sequence_type (
        dynamic_cast<SemanticGraph::Type&> (
          xs_ns ().find ("IDREF").first->named ()));
    }

    // URI.
    //
    void InitValue::
    traverse (SemanticGraph::Fundamental::AnyURI&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    // Binary.
    //
    static unsigned char
    base64_decode (unsigned char c)
    {
      unsigned char r = 0xFF;

      if (c >= 'A' && c <= 'Z')
        r = static_cast<unsigned char> (c - 'A');
      else if (c >= 'a' && c <= 'z')
        r = static_cast<unsigned char> (c - 'a' + 26);
      else if (c >= '0' && c <= '9')
        r = static_cast<unsigned char> (c - '0' + 52);
      else if (c == '+')
        r = 62;
      else if (c == '/')
        r = 63;

      return r;
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::Base64Binary& t)
    {
      collapse (value_);

      if (dispatch_count_++ == 0)
      {
        if (value_)
        {
          os << "unsigned char " << data_ << "[] = {";

          // Decode.
          //
          size_t size (value_.size ());

          // Remove all whitespaces.
          //
          {
            size_t j (0);
            bool subs (false);

            for (size_t i (0); i < size; ++i)
            {
              wchar_t c (value_[i]);

              if (c == 0x20 || c == 0x0A || c == 0x0D || c == 0x09)
                subs = true;
              else
              {
                if (subs)
                  subs = false;

                value_[j++] = c;
              }
            }

            size = j;
            value_.resize (size, '\0');
          }

          // Our length should be a multiple of four.
          //
          size_t quad_count (size / 4);

          // Source and destination indexes.
          //
          size_t si (0), di (0);

          // Process all quads except the last one.
          //
          unsigned short v;
          unsigned char b1, b2, b3, b4;

          wchar_t prev_fill (os.fill ('0'));

          for (size_t q (0); q < quad_count - 1; ++q)
          {
            b1 = base64_decode (value_[si++]);
            b2 = base64_decode (value_[si++]);
            b3 = base64_decode (value_[si++]);
            b4 = base64_decode (value_[si++]);

            if (q != 0)
              os << ", ";

            if (di % 9 == 0)
              os << endl;

            os << hex;

            v = static_cast<unsigned char> ((b1 << 2) | (b2 >> 4));
            os.width (2);
            os << "0x" << v;

            v = static_cast<unsigned char> ((b2 << 4) | (b3 >> 2));
            os.width (2);
            os << ", 0x" << v;

            v = static_cast<unsigned char> ((b3 << 6) | b4);
            os.width (2);
            os << ", 0x" << v;

            os << dec;

            di += 3;
          }

          // Process the last quad. The first two octets are always there.
          //
          b1 = base64_decode (value_[si++]);
          b2 = base64_decode (value_[si++]);

          wchar_t e3 (value_[si++]), e4 (value_[si++]);

          if (quad_count != 1)
            os << ", ";

          if (di % 9 == 0)
            os << endl;

          if (e4 == '=')
          {
            if (e3 == '=')
            {
              // Two pads. Last 4 bits in b2 should be zero.
              //
              v = static_cast<unsigned char> ((b1 << 2) | (b2 >> 4));
              os << "0x" << hex << v << dec;
              di++;
            }
            else
            {
              // One pad. Last 2 bits in b3 should be zero.
              //
              b3 = base64_decode (e3);

              os << hex;

              v = static_cast<unsigned char> ((b1 << 2) | (b2 >> 4));
              os.width (2);
              os << "0x" << v;

              v = static_cast<unsigned char> ((b2 << 4) | (b3 >> 2));
              os.width (2);
              os << ", 0x" << v;

              os << dec;

              di += 2;
            }
          }
          else
          {
            // No pads.
            //
            b3 = base64_decode (e3);
            b4 = base64_decode (e4);

            os << hex;

            v = static_cast<unsigned char> ((b1 << 2) | (b2 >> 4));
            os.width (2);
            os << "0x" << v;

            v = static_cast<unsigned char> ((b2 << 4) | (b3 >> 2));
            os.width (2);
            os << ", 0x" << v;

            v = static_cast<unsigned char> ((b3 << 6) | b4);
            os.width (2);
            os << ", 0x" << v;

            os << dec;

            di += 3;
          }

          os.fill (prev_fill);

          os << "};";
        }
      }
      else
      {
        os << fq_name (t) << " (";

        if (value_)
          os << data_ << "," << endl
             << "sizeof (" << data_ << ")," << endl
             << "sizeof (" << data_ << ")," << endl
             << "false";
        else
          os << "0";


        os << ")";
      }
    }

    static unsigned char
    hex_decode (unsigned char c)
    {
      unsigned char r = 0xFF;

      if (c >= '0' && c <= '9')
        r = static_cast<unsigned char> (c - '0');
      else if (c >= 'A' && c <= 'F')
        r = static_cast<unsigned char> (10 + (c - 'A'));
      else if (c >= 'a' && c <= 'f')
        r = static_cast<unsigned char> (10 + (c - 'a'));

      return r;
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::HexBinary& t)
    {
      collapse (value_);

      if (dispatch_count_++ == 0)
      {
        if (value_)
        {
          os << "unsigned char " << data_ << "[] = {";

          // Decode.
          //
          size_t n (value_.size () / 2);
          wchar_t prev_fill (os.fill ('0'));

          for (size_t i (0); i < n; ++i)
          {
            unsigned char h (hex_decode (value_[2 * i]));
            unsigned char l (hex_decode (value_[2 * i + 1]));

            if (h == 0xFF || l == 0xFF)
              break;

            if (i != 0)
              os << ", ";

            if (i % 9 == 0)
              os << endl;

            unsigned short v = static_cast<unsigned char> ((h << 4) | l);
            os.width (2);
            os << "0x" << hex << v << dec;
          }

          os.fill (prev_fill);

          os << "};";
        }
      }
      else
      {
        os << fq_name (t) << " (";

        if (value_)
          os << data_ << "," << endl
             << "sizeof (" << data_ << ")," << endl
             << "sizeof (" << data_ << ")," << endl
             << "false";
        else
          os << "0";


        os << ")";
      }
    }

    // Date/time.
    //
    void InitValue::
    traverse (SemanticGraph::Fundamental::Date& t)
    {
      // date := [-]CCYY[N]*-MM-DD[Z|(+|-)HH:MM]
      //
      collapse (value_);

      size_t b (0);
      size_t e (value_.find ('-', value_[0] == '-' ? 5 : 4));
      String year (value_, 0, e);

      b = e + 1;
      String month (value_, b, 2);

      b += 3;
      String day (value_, b, 2);

      strip_zeros (year);
      strip_zeros (month);
      strip_zeros (day);

      os << fq_name (t) << " (" << year << ", " << month << ", " << day;
      time_zone (b + 2);
      os << ")";
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::DateTime& t)
    {
      // date_time := [-]CCYY[N]*-MM-DDTHH:MM:SS[.S+][Z|(+|-)HH:MM]
      //
      collapse (value_);

      size_t b (0);
      size_t e (value_.find ('-', value_[0] == '-' ? 5 : 4));
      String year (value_, 0, e);
      b = e + 1;

      String month (value_, b, 2);
      b += 3;

      String day (value_, b, 2);
      b += 3;

      String hours (value_, b, 2);
      b += 3;

      String minutes (value_, b, 2);
      b += 3;

      e = b + 2;
      for (; e < value_.size (); ++e)
      {
        wchar_t c (value_[e]);

        if (c == 'Z' || c == '+' || c == '-')
          break;
      }

      String seconds (value_, b, e - b);

      strip_zeros (year);
      strip_zeros (month);
      strip_zeros (day);
      strip_zeros (hours);
      strip_zeros (minutes);
      strip_zeros (seconds);
      make_float (seconds);

      os << fq_name (t) << " ("
         << year << ", " << month << ", " << day << ", "
         << hours << ", " << minutes << ", " << seconds;
      time_zone (e);
      os << ")";
    }

    namespace
    {
      size_t
      find_delim (String const& s, size_t pos)
      {
        for (; pos < s.size (); ++pos)
        {
          wchar_t c (s[pos]);

          if (c == 'Y' || c == 'D' || c == 'M' || c == 'H' ||
              c == 'M' || c == 'S' || c == 'T')
            break;
        }

        return pos;
      }
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::Duration& t)
    {
      // duration := [-]P[nY][nM][nD][TnHnMn[.n+]S]
      //
      collapse (value_);

      size_t b (1), e, n (value_.size ());

      os << fq_name (t) << " (";

      if (value_[0] == '-')
      {
        os << "true, ";
        b++;
      }
      else
        os << "false, ";

      e = find_delim (value_, b);

      if (e < n && value_[e] == 'Y')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        os << v << ", ";

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0, ";

      if (e < n && value_[e] == 'M')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        os << v << ", ";

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0, ";

      if (e < n && value_[e] == 'D')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        os << v << ", ";

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0, ";

      if (e < n && value_[e] == 'T')
      {
        b = e + 1;
        e = find_delim (value_, b);
      }

      if (e < n && value_[e] == 'H')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        os << v << ", ";

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0, ";

      if (e < n && value_[e] == 'M')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        os << v << ", ";

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0, ";

      if (e < n && value_[e] == 'S')
      {
        String v (value_, b, e - b);
        strip_zeros (v);
        make_float (v);
        os << v;

        b = e + 1;
        e = find_delim (value_, b);
      }
      else
        os << "0.0";

      os << ")";
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::Day& t)
    {
      // gday := ---DD[Z|(+|-)HH:MM]
      //
      collapse (value_);

      String day (value_, 3, 2);
      strip_zeros (day);

      os << fq_name (t) << " (" << day;
      time_zone (5);
      os << ")";
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::Month& t)
    {
      // gmonth := --MM[Z|(+|-)HH:MM]
      //
      collapse (value_);

      String month (value_, 2, 2);
      strip_zeros (month);

      os << fq_name (t) << " (" << month;
      time_zone (4);
      os << ")";
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::MonthDay& t)
    {
      // gmonth_day := --MM-DD[Z|(+|-)HH:MM]
      //
      collapse (value_);

      String month (value_, 2, 2);
      String day (value_, 5, 2);

      strip_zeros (month);
      strip_zeros (day);

      os << fq_name (t) << " (" << month << ", " << day;
      time_zone (7);
      os << ")";
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::Year& t)
    {
      // gyear := [-]CCYY[N]*[Z|(+|-)HH:MM]
      //
      collapse (value_);

      size_t pos (value_[0] == '-' ? 5 : 4);
      for (; pos < value_.size (); ++pos)
      {
        wchar_t c (value_[pos]);

        if (c == 'Z' || c == '+' || c == '-')
          break;
      }

      String year (value_, 0, pos);
      strip_zeros (year);

      os << fq_name (t) << " (" << year;
      time_zone (pos);
      os << ")";
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::YearMonth& t)
    {
      // gyear_month := [-]CCYY[N]*-MM[Z|(+|-)HH:MM]
      //
      collapse (value_);

      size_t pos (value_.find ('-', value_[0] == '-' ? 5 : 4));

      String year (value_, 0, pos);
      String month (value_, pos + 1, 2);

      strip_zeros (year);
      strip_zeros (month);

      os << fq_name (t) << " (" << year << ", " << month;
      time_zone (pos + 3);
      os << ")";
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::Time& t)
    {
      // time := HH:MM:SS[.S+][Z|(+|-)HH:MM]
      //
      collapse (value_);

      String hours (value_, 0, 2);
      String minutes (value_, 3, 2);

      size_t e (8);
      for (; e < value_.size (); ++e)
      {
        wchar_t c (value_[e]);

        if (c == 'Z' || c == '+' || c == '-')
          break;
      }

      String seconds (value_, 6, e - 6);

      strip_zeros (hours);
      strip_zeros (minutes);
      strip_zeros (seconds);
      make_float (seconds);

      os << fq_name (t) << " (" << hours << ", " << minutes << ", " << seconds;
      time_zone (e);
      os << ")";
    }

    void InitValue::
    time_zone (size_t pos)
    {
      // time_zone := Z|(+|-)HH:MM
      //
      if (pos < value_.size ())
      {
        String h, m;

        if (value_[pos] == 'Z')
        {
          h = "0";
          m = "0";
        }
        else
        {
          if (value_[pos] == '-')
          {
            h = "-";
            m = "-";
          }

          h.append (value_, pos + 1, 2);
          m.append (value_, pos + 4, 2);

          strip_zeros (h);
          strip_zeros (m);
        }

        os << ", " << h << ", " << m;
      }
    }

    // Entity.
    //
    void InitValue::
    traverse (SemanticGraph::Fundamental::Entity&)
    {
      collapse (value_);
      os << strlit (value_);
    }

    void InitValue::
    traverse (SemanticGraph::Fundamental::Entities&)
    {
      string_sequence_type (
        dynamic_cast<SemanticGraph::Type&> (
          xs_ns ().find ("ENTITY").first->named ()));
    }

    void InitValue::
    string_sequence_type (SemanticGraph::Type& t)
    {
      collapse (value_);

      if (!value_)
        return;

      size_t b (0);

      for (size_t e (value_.find (' ')); ; e = value_.find (' ', b))
      {
        String v (value_, b, e != String::npos ? e - b : e);

        os << "{";
        type_name_.dispatch (t);
        os << " tmp (" << strlit (v) << ");"
           << "r.push_back (tmp);"
           << "}";

        if (e == String::npos)
          break;

        b = e + 1;
      }
    }
  }
}

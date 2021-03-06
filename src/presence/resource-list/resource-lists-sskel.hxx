// Copyright (c) 2005-2011 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD/e, an XML Schema
// to C++ data binding compiler for embedded systems.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
//

#ifndef RESOURCE_LISTS_SSKEL_HXX
#define RESOURCE_LISTS_SSKEL_HXX

#include <xsde/cxx/version.hxx>

#if (XSDE_INT_VERSION != 3020000L)
#error XSD/e runtime version mismatch
#endif

#include <xsde/cxx/config.hxx>

#ifndef XSDE_ENCODING_UTF8
#error the generated code uses the UTF-8 encodingwhile the XSD/e runtime does not (reconfigure the runtime or change the --char-encoding value)
#endif

#ifndef XSDE_STL
#error the generated code uses STL while the XSD/e runtime does not (reconfigure the runtime or add --no-stl)
#endif

#ifndef XSDE_IOSTREAM
#error the generated code uses iostream while the XSD/e runtime does not (reconfigure the runtime or add --no-iostream)
#endif

#ifndef XSDE_EXCEPTIONS
#error the generated code uses exceptions while the XSD/e runtime does not (reconfigure the runtime or add --no-exceptions)
#endif

#ifndef XSDE_LONGLONG
#error the generated code uses long long while the XSD/e runtime does not (reconfigure the runtime or add --no-long-long)
#endif

#ifndef XSDE_SERIALIZER_VALIDATION
#error the generated code uses validation while the XSD/e runtime does not (reconfigure the runtime or add --suppress-validation)
#endif

#ifndef XSDE_POLYMORPHIC
#error the generated code expects XSD/e runtime with polymorphism support (reconfigure the runtime or remove --generate-polymorphic/--runtime-polymorphic)
#endif

#ifndef XSDE_REUSE_STYLE_TIEIN
#error the generated code uses the tiein reuse style while the XSD/e runtime does not (reconfigure the runtime or add --reuse-style-mixin or --reuse-style-none)
#endif

#ifdef XSDE_CUSTOM_ALLOCATOR
#error the XSD/e runtime uses custom allocator while the generated code does not (reconfigure the runtime or add --custom-allocator)
#endif

#include <xsde/cxx/pre.hxx>

// Begin prologue.
//

#include <xsde/cxx/hybrid/any-type.hxx>
#include <xsde/cxx/hybrid/any-type-sskel.hxx>
#include <xsde/cxx/hybrid/any-type-simpl.hxx>

namespace xml_schema
{
  using ::xsde::cxx::hybrid::any_type;

  using ::xsde::cxx::hybrid::any_type_sskel;
  using ::xsde::cxx::hybrid::any_type_simpl;
}


//
// End prologue.

// Forward declarations
//
namespace resource_lists
{
  class display_nameType_sskel;
  class display_name_sskel;
  class entryType_sskel;
  class entry_refType_sskel;
  class externalType_sskel;
  class listType_sskel;
  class list_sskel;
  class resource_lists_sskel;
}


#include <string>

#include <xsde/cxx/serializer/xml-schema.hxx>

#include <xsde/cxx/serializer/exceptions.hxx>

#include <xsde/cxx/serializer/map.hxx>
#include <xsde/cxx/serializer/substitution-map-callback.hxx>
#include <xsde/cxx/serializer/substitution-map-load.hxx>
#include <xsde/cxx/serializer/validating/inheritance-map-load.hxx>

#include <xsde/cxx/serializer/validating/serializer.hxx>
#include <xsde/cxx/serializer/validating/xml-schema-sskel.hxx>
#include <xsde/cxx/serializer/validating/xml-schema-simpl.hxx>

#include <xsde/cxx/serializer/genx/document.hxx>

#include "resource-lists.hxx"

namespace xml_schema
{
  // Built-in XML Schema types mapping.
  //
  using ::xsde::cxx::string_sequence;
  using ::xsde::cxx::qname;
  using ::xsde::cxx::buffer;
  using ::xsde::cxx::time_zone;
  using ::xsde::cxx::gday;
  using ::xsde::cxx::gmonth;
  using ::xsde::cxx::gyear;
  using ::xsde::cxx::gmonth_day;
  using ::xsde::cxx::gyear_month;
  using ::xsde::cxx::date;
  using ::xsde::cxx::time;
  using ::xsde::cxx::date_time;
  using ::xsde::cxx::duration;

  // Base serializer skeletons.
  //
  using ::xsde::cxx::serializer::serializer_base;
  typedef ::xsde::cxx::serializer::validating::empty_content serializer_empty_content;
  typedef ::xsde::cxx::serializer::validating::simple_content serializer_simple_content;
  typedef ::xsde::cxx::serializer::validating::complex_content serializer_complex_content;

  // Serializer map interface and default implementation.
  //
  using ::xsde::cxx::serializer::serializer_map;
  using ::xsde::cxx::serializer::serializer_map_impl;

  // Serializer substitution map callack.
  //
  using ::xsde::cxx::serializer::serializer_smap_callback;

  // Substitution and inheritance hashmaps load querying.
  //
  using ::xsde::cxx::serializer::serializer_smap_buckets;
  using ::xsde::cxx::serializer::serializer_smap_elements;
  using ::xsde::cxx::serializer::serializer_smap_bucket_buckets;
  using ::xsde::cxx::serializer::serializer_smap_bucket_elements;
  using ::xsde::cxx::serializer::validating::serializer_imap_buckets;
  using ::xsde::cxx::serializer::validating::serializer_imap_elements;

  // Serializer skeletons and implementations for the
  // XML Schema built-in types.
  //
  using ::xsde::cxx::serializer::validating::any_simple_type_sskel;
  using ::xsde::cxx::serializer::validating::any_simple_type_simpl;

  using ::xsde::cxx::serializer::validating::byte_sskel;
  using ::xsde::cxx::serializer::validating::byte_simpl;

  using ::xsde::cxx::serializer::validating::unsigned_byte_sskel;
  using ::xsde::cxx::serializer::validating::unsigned_byte_simpl;

  using ::xsde::cxx::serializer::validating::short_sskel;
  using ::xsde::cxx::serializer::validating::short_simpl;

  using ::xsde::cxx::serializer::validating::unsigned_short_sskel;
  using ::xsde::cxx::serializer::validating::unsigned_short_simpl;

  using ::xsde::cxx::serializer::validating::int_sskel;
  using ::xsde::cxx::serializer::validating::int_simpl;

  using ::xsde::cxx::serializer::validating::unsigned_int_sskel;
  using ::xsde::cxx::serializer::validating::unsigned_int_simpl;

  using ::xsde::cxx::serializer::validating::long_sskel;
  using ::xsde::cxx::serializer::validating::long_simpl;

  using ::xsde::cxx::serializer::validating::unsigned_long_sskel;
  using ::xsde::cxx::serializer::validating::unsigned_long_simpl;

  using ::xsde::cxx::serializer::validating::integer_sskel;
  using ::xsde::cxx::serializer::validating::integer_simpl;

  using ::xsde::cxx::serializer::validating::non_positive_integer_sskel;
  using ::xsde::cxx::serializer::validating::non_positive_integer_simpl;

  using ::xsde::cxx::serializer::validating::non_negative_integer_sskel;
  using ::xsde::cxx::serializer::validating::non_negative_integer_simpl;

  using ::xsde::cxx::serializer::validating::positive_integer_sskel;
  using ::xsde::cxx::serializer::validating::positive_integer_simpl;

  using ::xsde::cxx::serializer::validating::negative_integer_sskel;
  using ::xsde::cxx::serializer::validating::negative_integer_simpl;

  using ::xsde::cxx::serializer::validating::boolean_sskel;
  using ::xsde::cxx::serializer::validating::boolean_simpl;

  using ::xsde::cxx::serializer::validating::float_sskel;
  using ::xsde::cxx::serializer::validating::float_simpl;

  using ::xsde::cxx::serializer::validating::double_sskel;
  using ::xsde::cxx::serializer::validating::double_simpl;

  using ::xsde::cxx::serializer::validating::decimal_sskel;
  using ::xsde::cxx::serializer::validating::decimal_simpl;

  using ::xsde::cxx::serializer::validating::string_sskel;
  using ::xsde::cxx::serializer::validating::string_simpl;

  using ::xsde::cxx::serializer::validating::normalized_string_sskel;
  using ::xsde::cxx::serializer::validating::normalized_string_simpl;

  using ::xsde::cxx::serializer::validating::token_sskel;
  using ::xsde::cxx::serializer::validating::token_simpl;

  using ::xsde::cxx::serializer::validating::name_sskel;
  using ::xsde::cxx::serializer::validating::name_simpl;

  using ::xsde::cxx::serializer::validating::nmtoken_sskel;
  using ::xsde::cxx::serializer::validating::nmtoken_simpl;

  using ::xsde::cxx::serializer::validating::nmtokens_sskel;
  using ::xsde::cxx::serializer::validating::nmtokens_simpl;

  using ::xsde::cxx::serializer::validating::ncname_sskel;
  using ::xsde::cxx::serializer::validating::ncname_simpl;

  using ::xsde::cxx::serializer::validating::language_sskel;
  using ::xsde::cxx::serializer::validating::language_simpl;

  using ::xsde::cxx::serializer::validating::id_sskel;
  using ::xsde::cxx::serializer::validating::id_simpl;

  using ::xsde::cxx::serializer::validating::idref_sskel;
  using ::xsde::cxx::serializer::validating::idref_simpl;

  using ::xsde::cxx::serializer::validating::idrefs_sskel;
  using ::xsde::cxx::serializer::validating::idrefs_simpl;

  using ::xsde::cxx::serializer::validating::uri_sskel;
  using ::xsde::cxx::serializer::validating::uri_simpl;

  using ::xsde::cxx::serializer::validating::qname_sskel;
  using ::xsde::cxx::serializer::validating::qname_simpl;

  using ::xsde::cxx::serializer::validating::base64_binary_sskel;
  using ::xsde::cxx::serializer::validating::base64_binary_simpl;

  using ::xsde::cxx::serializer::validating::hex_binary_sskel;
  using ::xsde::cxx::serializer::validating::hex_binary_simpl;

  using ::xsde::cxx::serializer::validating::date_sskel;
  using ::xsde::cxx::serializer::validating::date_simpl;

  using ::xsde::cxx::serializer::validating::date_time_sskel;
  using ::xsde::cxx::serializer::validating::date_time_simpl;

  using ::xsde::cxx::serializer::validating::duration_sskel;
  using ::xsde::cxx::serializer::validating::duration_simpl;

  using ::xsde::cxx::serializer::validating::gday_sskel;
  using ::xsde::cxx::serializer::validating::gday_simpl;

  using ::xsde::cxx::serializer::validating::gmonth_sskel;
  using ::xsde::cxx::serializer::validating::gmonth_simpl;

  using ::xsde::cxx::serializer::validating::gmonth_day_sskel;
  using ::xsde::cxx::serializer::validating::gmonth_day_simpl;

  using ::xsde::cxx::serializer::validating::gyear_sskel;
  using ::xsde::cxx::serializer::validating::gyear_simpl;

  using ::xsde::cxx::serializer::validating::gyear_month_sskel;
  using ::xsde::cxx::serializer::validating::gyear_month_simpl;

  using ::xsde::cxx::serializer::validating::time_sskel;
  using ::xsde::cxx::serializer::validating::time_simpl;

  // Error codes.
  //
  typedef xsde::cxx::serializer::genx::xml_error serializer_xml_error;
  typedef xsde::cxx::schema_error serializer_schema_error;

  // Exceptions.
  //
  typedef xsde::cxx::serializer::exception serializer_exception;
  typedef xsde::cxx::serializer::xml serializer_xml;
  typedef xsde::cxx::serializer::schema serializer_schema;

  // Document serializer.
  //
  using xsde::cxx::serializer::genx::writer;
  using xsde::cxx::serializer::genx::document_simpl;

  // Serializer context.
  //
  typedef xsde::cxx::serializer::context serializer_context;
}

#include "../xml/xml-sskel.hxx"

namespace resource_lists
{
  class display_nameType_sskel: public ::xml_schema::string_sskel
  {
    public:
    // Serializer callbacks. Override them in your implementation.
    //

    virtual void
    pre (const ::resource_lists::display_nameType&) = 0;

    // Attributes.
    //
    virtual bool
    lang_present ();

    virtual const ::namespace_::lang&
    lang () = 0;

    // virtual void
    // post ();

    // Serializer construction API.
    //
    void
    serializers (::namespace_::lang_sskel& /* lang */);

    // Individual attribute serializers.
    //
    void
    lang_serializer (::namespace_::lang_sskel&);

    virtual void
    _reset ();

    // Constructor.
    //
    display_nameType_sskel (::xml_schema::string_sskel* tiein);

    public:
    static const char*
    _static_type ();

    virtual const char*
    _dynamic_type () const;

    // Implementation.
    //
    public:
    virtual void
    pre (const ::std::string&);

    virtual void
    _serialize_attributes ();

    protected:
    display_nameType_sskel* display_nameType_impl_;
    display_nameType_sskel (display_nameType_sskel*, void*);

    protected:
    ::namespace_::lang_sskel* lang_serializer_;
  };

  class display_name_sskel: public ::resource_lists::display_nameType_sskel
  {
    public:
    // Serializer callbacks. Override them in your implementation.
    //

    virtual void
    pre (const ::resource_lists::display_name&) = 0;

    // virtual void
    // post ();

    // Constructor.
    //
    display_name_sskel (::resource_lists::display_nameType_sskel* tiein);

    public:
    static const char*
    _static_type ();

    virtual const char*
    _dynamic_type () const;

    // Implementation.
    //
    public:
    virtual void
    pre (const ::resource_lists::display_nameType&);

    virtual const ::namespace_::lang&
    lang ();

    protected:
    display_name_sskel* display_name_impl_;
    display_name_sskel (display_name_sskel*, void*);
  };

  class entryType_sskel: public ::xsde::cxx::serializer::validating::complex_content
  {
    public:
    // Serializer callbacks. Override them in your implementation.
    //

    virtual void
    pre (const ::resource_lists::entryType&) = 0;

    // Attributes.
    //
    virtual ::std::string
    uri () = 0;

    virtual bool
    any_attribute_next ();

    virtual void
    any_attribute (::std::string& ns, ::std::string& name);

    virtual void
    serialize_any_attribute ();

    // Elements.
    //
    virtual bool
    display_name_present ();

    virtual const ::resource_lists::display_name&
    display_name () = 0;

    virtual bool
    any_next ();

    virtual void
    any (::std::string& ns, ::std::string& name);

    virtual void
    serialize_any ();

    // virtual void
    // post ();

    // Serializer construction API.
    //
    void
    serializers (::xml_schema::uri_sskel& /* uri */,
                 ::resource_lists::display_name_sskel& /* display-name */);

    // Individual attribute serializers.
    //
    void
    uri_serializer (::xml_schema::uri_sskel&);

    // Individual element serializers.
    //
    void
    display_name_serializer (::resource_lists::display_name_sskel&);

    virtual void
    _reset ();

    // Constructor.
    //
    entryType_sskel ();

    public:
    static const char*
    _static_type ();

    virtual const char*
    _dynamic_type () const;

    // Implementation.
    //
    public:
    virtual void
    _serialize_attributes ();

    virtual void
    _serialize_content ();

    protected:
    entryType_sskel* entryType_impl_;
    entryType_sskel (entryType_sskel*, void*);

    protected:
    ::xml_schema::uri_sskel* uri_serializer_;
    ::resource_lists::display_name_sskel* display_name_serializer_;
  };

  class entry_refType_sskel: public ::xsde::cxx::serializer::validating::complex_content
  {
    public:
    // Serializer callbacks. Override them in your implementation.
    //

    virtual void
    pre (const ::resource_lists::entry_refType&) = 0;

    // Attributes.
    //
    virtual ::std::string
    ref () = 0;

    virtual bool
    any_attribute_next ();

    virtual void
    any_attribute (::std::string& ns, ::std::string& name);

    virtual void
    serialize_any_attribute ();

    // Elements.
    //
    virtual bool
    display_name_present ();

    virtual const ::resource_lists::display_nameType&
    display_name () = 0;

    virtual bool
    any_next ();

    virtual void
    any (::std::string& ns, ::std::string& name);

    virtual void
    serialize_any ();

    // virtual void
    // post ();

    // Serializer construction API.
    //
    void
    serializers (::xml_schema::uri_sskel& /* ref */,
                 ::resource_lists::display_nameType_sskel& /* display-name */);

    void
    serializer_maps (::xml_schema::serializer_map& /* display-name */);

    // Individual attribute serializers.
    //
    void
    ref_serializer (::xml_schema::uri_sskel&);

    // Individual element serializers.
    //
    void
    display_name_serializer (::resource_lists::display_nameType_sskel&);

    void
    display_name_serializer (::xml_schema::serializer_map&);

    virtual void
    _reset ();

    // Constructor.
    //
    entry_refType_sskel ();

    public:
    static const char*
    _static_type ();

    virtual const char*
    _dynamic_type () const;

    // Implementation.
    //
    public:
    virtual void
    _serialize_attributes ();

    virtual void
    _serialize_content ();

    protected:
    entry_refType_sskel* entry_refType_impl_;
    entry_refType_sskel (entry_refType_sskel*, void*);

    protected:
    ::xml_schema::uri_sskel* ref_serializer_;
    ::resource_lists::display_nameType_sskel* display_name_serializer_;
    ::xml_schema::serializer_map* display_name_serializer_map_;
  };

  class externalType_sskel: public ::xsde::cxx::serializer::validating::complex_content
  {
    public:
    // Serializer callbacks. Override them in your implementation.
    //

    virtual void
    pre (const ::resource_lists::externalType&) = 0;

    // Attributes.
    //
    virtual bool
    anchor_present ();

    virtual ::std::string
    anchor () = 0;

    virtual bool
    any_attribute_next ();

    virtual void
    any_attribute (::std::string& ns, ::std::string& name);

    virtual void
    serialize_any_attribute ();

    // Elements.
    //
    virtual bool
    display_name_present ();

    virtual const ::resource_lists::display_nameType&
    display_name () = 0;

    virtual bool
    any_next ();

    virtual void
    any (::std::string& ns, ::std::string& name);

    virtual void
    serialize_any ();

    // virtual void
    // post ();

    // Serializer construction API.
    //
    void
    serializers (::xml_schema::uri_sskel& /* anchor */,
                 ::resource_lists::display_nameType_sskel& /* display-name */);

    void
    serializer_maps (::xml_schema::serializer_map& /* display-name */);

    // Individual attribute serializers.
    //
    void
    anchor_serializer (::xml_schema::uri_sskel&);

    // Individual element serializers.
    //
    void
    display_name_serializer (::resource_lists::display_nameType_sskel&);

    void
    display_name_serializer (::xml_schema::serializer_map&);

    virtual void
    _reset ();

    // Constructor.
    //
    externalType_sskel ();

    public:
    static const char*
    _static_type ();

    virtual const char*
    _dynamic_type () const;

    // Implementation.
    //
    public:
    virtual void
    _serialize_attributes ();

    virtual void
    _serialize_content ();

    protected:
    externalType_sskel* externalType_impl_;
    externalType_sskel (externalType_sskel*, void*);

    protected:
    ::xml_schema::uri_sskel* anchor_serializer_;
    ::resource_lists::display_nameType_sskel* display_name_serializer_;
    ::xml_schema::serializer_map* display_name_serializer_map_;
  };

  class listType_sskel: public ::xsde::cxx::serializer::validating::complex_content
  {
    public:
    // Serializer callbacks. Override them in your implementation.
    //

    virtual void
    pre (const ::resource_lists::listType&) = 0;

    // Attributes.
    //
    virtual bool
    name_present ();

    virtual ::std::string
    name () = 0;

    virtual bool
    any_attribute_next ();

    virtual void
    any_attribute (::std::string& ns, ::std::string& name);

    virtual void
    serialize_any_attribute ();

    // Elements.
    //
    virtual bool
    display_name_present ();

    virtual const ::resource_lists::display_nameType&
    display_name () = 0;

    virtual bool
    sequence_next ();

    enum choice_arm_tag
    {
      list_tag,
      external_tag,
      entry_tag,
      entry_ref_tag
    };

    virtual choice_arm_tag
    choice_arm () = 0;

    virtual const ::resource_lists::list&
    list () = 0;

    virtual const ::resource_lists::externalType&
    external () = 0;

    virtual const ::resource_lists::entryType&
    entry () = 0;

    virtual const ::resource_lists::entry_refType&
    entry_ref () = 0;

    virtual bool
    any_next ();

    virtual void
    any (::std::string& ns, ::std::string& name);

    virtual void
    serialize_any ();

    // virtual void
    // post ();

    // Serializer construction API.
    //
    void
    serializers (::xml_schema::string_sskel& /* name */,
                 ::resource_lists::display_nameType_sskel& /* display-name */,
                 ::resource_lists::list_sskel& /* list */,
                 ::resource_lists::externalType_sskel& /* external */,
                 ::resource_lists::entryType_sskel& /* entry */,
                 ::resource_lists::entry_refType_sskel& /* entry-ref */);

    void
    serializer_maps (::xml_schema::serializer_map& /* display-name */,
                     ::xml_schema::serializer_map& /* external */,
                     ::xml_schema::serializer_map& /* entry */,
                     ::xml_schema::serializer_map& /* entry-ref */);

    // Individual attribute serializers.
    //
    void
    name_serializer (::xml_schema::string_sskel&);

    // Individual element serializers.
    //
    void
    display_name_serializer (::resource_lists::display_nameType_sskel&);

    void
    display_name_serializer (::xml_schema::serializer_map&);

    void
    list_serializer (::resource_lists::list_sskel&);

    void
    external_serializer (::resource_lists::externalType_sskel&);

    void
    external_serializer (::xml_schema::serializer_map&);

    void
    entry_serializer (::resource_lists::entryType_sskel&);

    void
    entry_serializer (::xml_schema::serializer_map&);

    void
    entry_ref_serializer (::resource_lists::entry_refType_sskel&);

    void
    entry_ref_serializer (::xml_schema::serializer_map&);

    virtual void
    _reset ();

    // Constructor.
    //
    listType_sskel ();

    public:
    static const char*
    _static_type ();

    virtual const char*
    _dynamic_type () const;

    // Implementation.
    //
    public:
    virtual void
    _serialize_attributes ();

    virtual void
    _serialize_content ();

    protected:
    listType_sskel* listType_impl_;
    listType_sskel (listType_sskel*, void*);

    protected:
    ::xml_schema::string_sskel* name_serializer_;
    ::resource_lists::display_nameType_sskel* display_name_serializer_;
    ::xml_schema::serializer_map* display_name_serializer_map_;

    ::resource_lists::list_sskel* list_serializer_;
    ::resource_lists::externalType_sskel* external_serializer_;
    ::xml_schema::serializer_map* external_serializer_map_;

    ::resource_lists::entryType_sskel* entry_serializer_;
    ::xml_schema::serializer_map* entry_serializer_map_;

    ::resource_lists::entry_refType_sskel* entry_ref_serializer_;
    ::xml_schema::serializer_map* entry_ref_serializer_map_;
  };

  class list_sskel: public ::resource_lists::listType_sskel
  {
    public:
    // Serializer callbacks. Override them in your implementation.
    //

    virtual void
    pre (const ::resource_lists::list&) = 0;

    // virtual void
    // post ();

    // Constructor.
    //
    list_sskel (::resource_lists::listType_sskel* tiein);

    public:
    static const char*
    _static_type ();

    virtual const char*
    _dynamic_type () const;

    // Implementation.
    //
    public:
    virtual void
    pre (const ::resource_lists::listType&);

    virtual ::std::string
    name ();

    virtual const ::resource_lists::display_nameType&
    display_name ();

    virtual choice_arm_tag
    choice_arm ();

    virtual const ::resource_lists::list&
    list ();

    virtual const ::resource_lists::externalType&
    external ();

    virtual const ::resource_lists::entryType&
    entry ();

    virtual const ::resource_lists::entry_refType&
    entry_ref ();

    protected:
    list_sskel* list_impl_;
    list_sskel (list_sskel*, void*);
  };

  class resource_lists_sskel: public ::xsde::cxx::serializer::validating::complex_content
  {
    public:
    // Serializer callbacks. Override them in your implementation.
    //

    virtual void
    pre (const ::resource_lists::resource_lists&) = 0;

    // Elements.
    //
    virtual bool
    sequence_next ();

    virtual const ::resource_lists::listType&
    list () = 0;

    // virtual void
    // post ();

    // Serializer construction API.
    //
    void
    serializers (::resource_lists::listType_sskel& /* list */);

    void
    serializer_maps (::xml_schema::serializer_map& /* list */);

    // Individual element serializers.
    //
    void
    list_serializer (::resource_lists::listType_sskel&);

    void
    list_serializer (::xml_schema::serializer_map&);

    virtual void
    _reset ();

    // Constructor.
    //
    resource_lists_sskel ();

    public:
    static const char*
    _static_type ();

    virtual const char*
    _dynamic_type () const;

    // Implementation.
    //
    public:
    virtual void
    _serialize_content ();

    protected:
    resource_lists_sskel* resource_lists_impl_;
    resource_lists_sskel (resource_lists_sskel*, void*);

    protected:
    ::resource_lists::listType_sskel* list_serializer_;
    ::xml_schema::serializer_map* list_serializer_map_;
  };
}

// Begin epilogue.
//
//
// End epilogue.

#include <xsde/cxx/post.hxx>

#endif // RESOURCE_LISTS_SSKEL_HXX

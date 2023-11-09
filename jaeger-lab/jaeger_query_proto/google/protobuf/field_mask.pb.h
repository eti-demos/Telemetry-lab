// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/field_mask.proto
// Protobuf C++ Version: 4.24.0-main

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2ffield_5fmask_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2ffield_5fmask_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4025000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4025000 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2ffield_5fmask_2eproto PROTOBUF_EXPORT

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct PROTOBUF_EXPORT TableStruct_google_2fprotobuf_2ffield_5fmask_2eproto {
  static const ::uint32_t offsets[];
};
PROTOBUF_EXPORT extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_google_2fprotobuf_2ffield_5fmask_2eproto;
namespace google {
namespace protobuf {
class FieldMask;
struct FieldMaskDefaultTypeInternal;
PROTOBUF_EXPORT extern FieldMaskDefaultTypeInternal _FieldMask_default_instance_;
}  // namespace protobuf
}  // namespace google

namespace google {
namespace protobuf {

// ===================================================================


// -------------------------------------------------------------------

class PROTOBUF_EXPORT FieldMask final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:google.protobuf.FieldMask) */ {
 public:
  inline FieldMask() : FieldMask(nullptr) {}
  ~FieldMask() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR FieldMask(::google::protobuf::internal::ConstantInitialized);

  inline FieldMask(const FieldMask& from)
      : FieldMask(nullptr, from) {}
  FieldMask(FieldMask&& from) noexcept
    : FieldMask() {
    *this = ::std::move(from);
  }

  inline FieldMask& operator=(const FieldMask& from) {
    CopyFrom(from);
    return *this;
  }
  inline FieldMask& operator=(FieldMask&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const FieldMask& default_instance() {
    return *internal_default_instance();
  }
  static inline const FieldMask* internal_default_instance() {
    return reinterpret_cast<const FieldMask*>(
               &_FieldMask_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(FieldMask& a, FieldMask& b) {
    a.Swap(&b);
  }
  inline void Swap(FieldMask* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr &&
        GetArena() == other->GetArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(FieldMask* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  FieldMask* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<FieldMask>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const FieldMask& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const FieldMask& from) {
    FieldMask::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg);
  public:
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(FieldMask* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "google.protobuf.FieldMask";
  }
  protected:
  explicit FieldMask(::google::protobuf::Arena* arena);
  FieldMask(::google::protobuf::Arena* arena, const FieldMask& from);
  const ::google::protobuf::MessageLite::ClassData* GetClassData() const final;
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPathsFieldNumber = 1,
  };
  // repeated string paths = 1;
  int paths_size() const;
  private:
  int _internal_paths_size() const;

  public:
  void clear_paths() ;
  const std::string& paths(int index) const;
  std::string* mutable_paths(int index);
  void set_paths(int index, const std::string& value);
  void set_paths(int index, std::string&& value);
  void set_paths(int index, const char* value);
  void set_paths(int index, const char* value, std::size_t size);
  void set_paths(int index, absl::string_view value);
  std::string* add_paths();
  void add_paths(const std::string& value);
  void add_paths(std::string&& value);
  void add_paths(const char* value);
  void add_paths(const char* value, std::size_t size);
  void add_paths(absl::string_view value);
  const ::google::protobuf::RepeatedPtrField<std::string>& paths() const;
  ::google::protobuf::RepeatedPtrField<std::string>* mutable_paths();

  private:
  const ::google::protobuf::RepeatedPtrField<std::string>& _internal_paths() const;
  ::google::protobuf::RepeatedPtrField<std::string>* _internal_mutable_paths();

  public:
  // @@protoc_insertion_point(class_scope:google.protobuf.FieldMask)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
      39, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct PROTOBUF_EXPORT Impl_ {

        inline explicit constexpr Impl_(
            ::google::protobuf::internal::ConstantInitialized) noexcept;
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena);
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena, const Impl_& from);
    ::google::protobuf::RepeatedPtrField<std::string> paths_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_google_2fprotobuf_2ffield_5fmask_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// FieldMask

// repeated string paths = 1;
inline int FieldMask::_internal_paths_size() const {
  return _internal_paths().size();
}
inline int FieldMask::paths_size() const {
  return _internal_paths_size();
}
inline void FieldMask::clear_paths() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.paths_.Clear();
}
inline std::string* FieldMask::add_paths()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  std::string* _s = _internal_mutable_paths()->Add();
  // @@protoc_insertion_point(field_add_mutable:google.protobuf.FieldMask.paths)
  return _s;
}
inline const std::string& FieldMask::paths(int index) const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:google.protobuf.FieldMask.paths)
  return _internal_paths().Get(index);
}
inline std::string* FieldMask::mutable_paths(int index)
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable:google.protobuf.FieldMask.paths)
  return _internal_mutable_paths()->Mutable(index);
}
inline void FieldMask::set_paths(int index, const std::string& value) {
  _internal_mutable_paths()->Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set:google.protobuf.FieldMask.paths)
}
inline void FieldMask::set_paths(int index, std::string&& value) {
  _internal_mutable_paths()->Mutable(index)->assign(std::move(value));
  // @@protoc_insertion_point(field_set:google.protobuf.FieldMask.paths)
}
inline void FieldMask::set_paths(int index, const char* value) {
  ABSL_DCHECK(value != nullptr);
  _internal_mutable_paths()->Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:google.protobuf.FieldMask.paths)
}
inline void FieldMask::set_paths(int index, const char* value,
                              std::size_t size) {
  _internal_mutable_paths()->Mutable(index)->assign(
      reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:google.protobuf.FieldMask.paths)
}
inline void FieldMask::set_paths(int index, absl::string_view value) {
  _internal_mutable_paths()->Mutable(index)->assign(value.data(),
                                                     value.size());
  // @@protoc_insertion_point(field_set_string_piece:google.protobuf.FieldMask.paths)
}
inline void FieldMask::add_paths(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _internal_mutable_paths()->Add()->assign(value);
  // @@protoc_insertion_point(field_add:google.protobuf.FieldMask.paths)
}
inline void FieldMask::add_paths(std::string&& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _internal_mutable_paths()->Add(std::move(value));
  // @@protoc_insertion_point(field_add:google.protobuf.FieldMask.paths)
}
inline void FieldMask::add_paths(const char* value) {
  ABSL_DCHECK(value != nullptr);
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _internal_mutable_paths()->Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:google.protobuf.FieldMask.paths)
}
inline void FieldMask::add_paths(const char* value, std::size_t size) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _internal_mutable_paths()->Add()->assign(
      reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:google.protobuf.FieldMask.paths)
}
inline void FieldMask::add_paths(absl::string_view value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _internal_mutable_paths()->Add()->assign(value.data(), value.size());
  // @@protoc_insertion_point(field_add_string_piece:google.protobuf.FieldMask.paths)
}
inline const ::google::protobuf::RepeatedPtrField<std::string>&
FieldMask::paths() const ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:google.protobuf.FieldMask.paths)
  return _internal_paths();
}
inline ::google::protobuf::RepeatedPtrField<std::string>*
FieldMask::mutable_paths() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:google.protobuf.FieldMask.paths)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _internal_mutable_paths();
}
inline const ::google::protobuf::RepeatedPtrField<std::string>&
FieldMask::_internal_paths() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.paths_;
}
inline ::google::protobuf::RepeatedPtrField<std::string>*
FieldMask::_internal_mutable_paths() {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return &_impl_.paths_;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace protobuf
}  // namespace google


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2ffield_5fmask_2eproto_2epb_2eh

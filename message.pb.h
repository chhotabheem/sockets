// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_message_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_message_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3011000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3011002 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_message_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_message_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_message_2eproto;
class Data;
class DataDefaultTypeInternal;
extern DataDefaultTypeInternal _Data_default_instance_;
class Payload;
class PayloadDefaultTypeInternal;
extern PayloadDefaultTypeInternal _Payload_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::Data* Arena::CreateMaybeMessage<::Data>(Arena*);
template<> ::Payload* Arena::CreateMaybeMessage<::Payload>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class Data :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Data) */ {
 public:
  Data();
  virtual ~Data();

  Data(const Data& from);
  Data(Data&& from) noexcept
    : Data() {
    *this = ::std::move(from);
  }

  inline Data& operator=(const Data& from) {
    CopyFrom(from);
    return *this;
  }
  inline Data& operator=(Data&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Data& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Data* internal_default_instance() {
    return reinterpret_cast<const Data*>(
               &_Data_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Data& a, Data& b) {
    a.Swap(&b);
  }
  inline void Swap(Data* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Data* New() const final {
    return CreateMaybeMessage<Data>(nullptr);
  }

  Data* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Data>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Data& from);
  void MergeFrom(const Data& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Data* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Data";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_message_2eproto);
    return ::descriptor_table_message_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kClientMsgFieldNumber = 2,
    kMsgIdFieldNumber = 1,
  };
  // string client_msg = 2;
  void clear_client_msg();
  const std::string& client_msg() const;
  void set_client_msg(const std::string& value);
  void set_client_msg(std::string&& value);
  void set_client_msg(const char* value);
  void set_client_msg(const char* value, size_t size);
  std::string* mutable_client_msg();
  std::string* release_client_msg();
  void set_allocated_client_msg(std::string* client_msg);
  private:
  const std::string& _internal_client_msg() const;
  void _internal_set_client_msg(const std::string& value);
  std::string* _internal_mutable_client_msg();
  public:

  // int32 msg_id = 1;
  void clear_msg_id();
  ::PROTOBUF_NAMESPACE_ID::int32 msg_id() const;
  void set_msg_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_msg_id() const;
  void _internal_set_msg_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:Data)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr client_msg_;
  ::PROTOBUF_NAMESPACE_ID::int32 msg_id_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_message_2eproto;
};
// -------------------------------------------------------------------

class Payload :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Payload) */ {
 public:
  Payload();
  virtual ~Payload();

  Payload(const Payload& from);
  Payload(Payload&& from) noexcept
    : Payload() {
    *this = ::std::move(from);
  }

  inline Payload& operator=(const Payload& from) {
    CopyFrom(from);
    return *this;
  }
  inline Payload& operator=(Payload&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Payload& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Payload* internal_default_instance() {
    return reinterpret_cast<const Payload*>(
               &_Payload_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Payload& a, Payload& b) {
    a.Swap(&b);
  }
  inline void Swap(Payload* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Payload* New() const final {
    return CreateMaybeMessage<Payload>(nullptr);
  }

  Payload* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Payload>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Payload& from);
  void MergeFrom(const Payload& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Payload* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Payload";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_message_2eproto);
    return ::descriptor_table_message_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDataFieldNumber = 3,
  };
  // repeated .Data data = 3;
  int data_size() const;
  private:
  int _internal_data_size() const;
  public:
  void clear_data();
  ::Data* mutable_data(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Data >*
      mutable_data();
  private:
  const ::Data& _internal_data(int index) const;
  ::Data* _internal_add_data();
  public:
  const ::Data& data(int index) const;
  ::Data* add_data();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Data >&
      data() const;

  // @@protoc_insertion_point(class_scope:Payload)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Data > data_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_message_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Data

// int32 msg_id = 1;
inline void Data::clear_msg_id() {
  msg_id_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Data::_internal_msg_id() const {
  return msg_id_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Data::msg_id() const {
  // @@protoc_insertion_point(field_get:Data.msg_id)
  return _internal_msg_id();
}
inline void Data::_internal_set_msg_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  msg_id_ = value;
}
inline void Data::set_msg_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_msg_id(value);
  // @@protoc_insertion_point(field_set:Data.msg_id)
}

// string client_msg = 2;
inline void Data::clear_client_msg() {
  client_msg_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Data::client_msg() const {
  // @@protoc_insertion_point(field_get:Data.client_msg)
  return _internal_client_msg();
}
inline void Data::set_client_msg(const std::string& value) {
  _internal_set_client_msg(value);
  // @@protoc_insertion_point(field_set:Data.client_msg)
}
inline std::string* Data::mutable_client_msg() {
  // @@protoc_insertion_point(field_mutable:Data.client_msg)
  return _internal_mutable_client_msg();
}
inline const std::string& Data::_internal_client_msg() const {
  return client_msg_.GetNoArena();
}
inline void Data::_internal_set_client_msg(const std::string& value) {
  
  client_msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void Data::set_client_msg(std::string&& value) {
  
  client_msg_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Data.client_msg)
}
inline void Data::set_client_msg(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  client_msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Data.client_msg)
}
inline void Data::set_client_msg(const char* value, size_t size) {
  
  client_msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Data.client_msg)
}
inline std::string* Data::_internal_mutable_client_msg() {
  
  return client_msg_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Data::release_client_msg() {
  // @@protoc_insertion_point(field_release:Data.client_msg)
  
  return client_msg_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Data::set_allocated_client_msg(std::string* client_msg) {
  if (client_msg != nullptr) {
    
  } else {
    
  }
  client_msg_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), client_msg);
  // @@protoc_insertion_point(field_set_allocated:Data.client_msg)
}

// -------------------------------------------------------------------

// Payload

// repeated .Data data = 3;
inline int Payload::_internal_data_size() const {
  return data_.size();
}
inline int Payload::data_size() const {
  return _internal_data_size();
}
inline void Payload::clear_data() {
  data_.Clear();
}
inline ::Data* Payload::mutable_data(int index) {
  // @@protoc_insertion_point(field_mutable:Payload.data)
  return data_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Data >*
Payload::mutable_data() {
  // @@protoc_insertion_point(field_mutable_list:Payload.data)
  return &data_;
}
inline const ::Data& Payload::_internal_data(int index) const {
  return data_.Get(index);
}
inline const ::Data& Payload::data(int index) const {
  // @@protoc_insertion_point(field_get:Payload.data)
  return _internal_data(index);
}
inline ::Data* Payload::_internal_add_data() {
  return data_.Add();
}
inline ::Data* Payload::add_data() {
  // @@protoc_insertion_point(field_add:Payload.data)
  return _internal_add_data();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Data >&
Payload::data() const {
  // @@protoc_insertion_point(field_list:Payload.data)
  return data_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_message_2eproto

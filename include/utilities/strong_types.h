#if !defined(STRONG_TYPES)
#define STRONG_TYPES

namespace minpass::utilities {

template <typename Type, typename Meaning>
class StrongType {
 public:
  explicit StrongType(Type const& value) : value_(value) {}
  explicit StrongType(Type&& value) : value_(value) {}
  StrongType() : value_(Type({})){};
  auto get() -> Type { return value_; }
  auto set(Type const& value) -> void { value_ = value; }

 private:
  Type value_;
};

}  // namespace minpass::utilities

#endif  // STRONG_TYPES

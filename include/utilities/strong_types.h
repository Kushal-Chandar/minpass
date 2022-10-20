#if !defined(STRONG_TYPES)
#define STRONG_TYPES

namespace minpass::utilities {

template <typename Type, typename Meaning>
class StrongType {
 public:
  explicit StrongType(Type const& value) : value_(value) {}
  auto get() -> Type { return value_ }

 private:
  Type value_;
};

}  // namespace minpass::utilities

#endif  // STRONG_TYPES

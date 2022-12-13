#if !defined(MINPASS_SRC_INC_UTILITIES_STRONG_TYPES_H_)
#define MINPASS_SRC_INC_UTILITIES_STRONG_TYPES_H_

namespace minpass::utilities {

template <typename Type, typename Meaning>
class StrongType {
 public:
  explicit StrongType(Type const& value) : value_(value) {}
  explicit StrongType(Type&& value) : value_(value) {}
  StrongType() : value_(Type({})){};
  auto get() const -> Type { return value_; }
  auto set(Type const& value) -> void { value_ = value; }

 private:
  Type value_;
};

}  // namespace minpass::utilities

#endif  // MINPASS_SRC_INC_UTILITIES_STRONG_TYPES_H_

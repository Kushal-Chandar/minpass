#if !defined(AES_GCM)
#define AES_GCM

namespace minpass::utilities {

class AES_GCM_256 {
 public:
  auto encrypt() -> void;
  auto decrypt() -> void;
};

}  // namespace minpass::utilities

#endif  // AES_GCM

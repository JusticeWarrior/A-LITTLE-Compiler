#include <unordered_set>

template <typename T>
class MemorySet {
  public:
    MemorySet() = default;
    ~MemorySet();
    void register_object(T*);
    void destroy_object(T*);
  private:
    typedef typename std::unordered_set<T*> set_t;
    set_t pointer_set;
};

template <typename T>
MemorySet<T>::~MemorySet() {
  typename set_t::iterator it;
  for (it = pointer_set.begin(); it != pointer_set.end(); it++) {
    delete (*it);
  }
}

template <typename T>
void MemorySet<T>::register_object(T* obj) {
  pointer_set.insert(obj);
}

template <typename T>
void MemorySet<T>::destroy_object(T* obj) {
  pointer_set.erase(obj);
  delete obj;
}

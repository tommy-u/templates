// Citing: https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern

// The Curiously Recurring Template Pattern (CRTP)
template <class T> class Base {
  // methods within Base can use template to access members of Derived
};

class Derived : public Base<Derived> {
  // ...
};

// Typically, the base class template will take advantage of the fact that
// member function bodies (definitions) are not instantiated until long after
// their declarations, and will use members of the derived class within its own
// member functions, via the use of a cast; e.g.:
template <class T> struct Base {
  void interface() {
    // ...
    static_cast<T *>(this)->implementation();
    // ...
  }

  static void static_func() {
    // ...
    T::static_sub_func();
    // ...
  }
};

struct Derived : Base<Derived> {
  void implementation();
  static void static_sub_func();
};

template <typename T> struct counter {
  static int objects_created;
  static int objects_alive;

  counter() {
    ++objects_created;
    ++objects_alive;
  }

  counter(const counter &) {
    ++objects_created;
    ++objects_alive;
  }

protected:
  ~counter() // objects should never be removed through pointers of this type
  {
    --objects_alive;
  }
};

template <typename T> int counter<T>::objects_created(0);

template <typename T> int counter<T>::objects_alive(0);

class X : counter<X> {
  // ...
};

class Y : counter<Y> {
  // ...
};

int main() {}

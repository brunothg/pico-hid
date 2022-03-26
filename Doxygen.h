/**
 * Do not import.
 * Just provides definitions for Doxygen that would otherwise be missing.
 */

namespace std {
    template<class T> class shared_ptr {
    public:
        T *ptr;
    };

    template<class T> class unique_ptr {
    public:
        T *ptr;
    };
}
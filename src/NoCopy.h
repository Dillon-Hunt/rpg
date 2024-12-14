#ifndef NO_COPY_H
#define NO_COPY_H

/**
 * Base class that prevents copying for memory safety
 */
class NoCopy {
    public:
        NoCopy() = default;

        // Copy constructor
        NoCopy(const NoCopy&) = delete;

        // Copy assignment
        NoCopy& operator=(const NoCopy&) = delete;

        // Move constructor
        NoCopy(NoCopy&&) = default;

        // Move assignment
        NoCopy& operator=(NoCopy&&) = default;

        virtual ~NoCopy() = default;
};

#endif // NO_COPY_H

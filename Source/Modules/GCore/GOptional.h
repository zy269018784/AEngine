#pragma once
#include <iostream>

namespace GCore {

    /**
     * @brief  GOptional value container that may or may not hold a value
     * @tparam T Type of the value to store
     */
    template <typename T>
    class  GOptional {
    public:
        using value_type = T;

        // ========================================================================
        // Constructors
        // ========================================================================

        /**
         * @brief Default constructor - creates an empty optional
         */
         GOptional() = default;

        /**
         * @brief Construct from a const reference
         * @param v Value to store
         */
         GOptional(const T& v) : set(true) {
            new (ptr()) T(v);
        }

        /**
         * @brief Construct from an rvalue reference
         * @param v Value to move into storage
         */
         GOptional(T&& v) : set(true) {
            new (ptr()) T(std::move(v));
        }

        /**
         * @brief Copy constructor
         * @param v Other optional to copy from
         */
         GOptional(const  GOptional& v) : set(v.has_value()) {
            if (v.has_value())
                new (ptr()) T(v.value());
        }

        /**
         * @brief Move constructor
         * @param v Other optional to move from
         */
         GOptional( GOptional&& v) : set(v.has_value()) {
            if (v.has_value()) {
                new (ptr()) T(std::move(v.value()));
                v.reset();
            }
        }

        // ========================================================================
        // Assignment Operators
        // ========================================================================

        /**
         * @brief Assign from a const reference
         * @param v Value to assign
         * @return Reference to this optional
         */
         GOptional& operator=(const T& v) {
            reset();
            new (ptr()) T(v);
            set = true;
            return *this;
        }

        /**
         * @brief Assign from an rvalue reference
         * @param v Value to move into storage
         * @return Reference to this optional
         */
         GOptional& operator=(T&& v) {
            reset();
            new (ptr()) T(std::move(v));
            set = true;
            return *this;
        }

        /**
         * @brief Copy assignment
         * @param v Other optional to copy from
         * @return Reference to this optional
         */
         GOptional& operator=(const  GOptional& v) {
            reset();
            if (v.has_value()) {
                new (ptr()) T(v.value());
                set = true;
            }
            return *this;
        }

        /**
         * @brief Move assignment
         * @param v Other optional to move from
         * @return Reference to this optional
         */
         GOptional& operator=( GOptional&& v) {
            reset();
            if (v.has_value()) {
                new (ptr()) T(std::move(v.value()));
                set = true;
                v.reset();
            }
            return *this;
        }

        // ========================================================================
        // Destructor
        // ========================================================================

        /**
         * @brief Destructor - destroys the stored value if present
         */
        ~ GOptional() { reset(); }

        // ========================================================================
        // Observers
        // ========================================================================

        /**
         * @brief Check if the optional contains a value
         * @return true if has value, false otherwise
         */
        explicit operator bool() const { return set; }

        /**
         * @brief Get the value or a default alternative
         * @param alt Alternative value to return if empty
         * @return Value if present, otherwise alt
         */
        T value_or(const T& alt) const {
            return set ? value() : alt;
        }

        // ========================================================================
        // Accessors
        // ========================================================================

        /**
         * @brief Member access via arrow operator
         * @return Pointer to the stored value
         */
        T* operator->() { return &value(); }

        /**
         * @brief Member access via arrow operator (const)
         * @return Const pointer to the stored value
         */
        const T* operator->() const { return &value(); }

        /**
         * @brief Dereference operator
         * @return Reference to the stored value
         */
        T& operator*() { return value(); }

        /**
         * @brief Dereference operator (const)
         * @return Const reference to the stored value
         */
        const T& operator*() const { return value(); }

        /**
         * @brief Get the stored value (non-const)
         * @return Reference to the stored value
         */
        T& value() { return *ptr(); }

        /**
         * @brief Get the stored value (const)
         * @return Const reference to the stored value
         */
        const T& value() const { return *ptr(); }

        // ========================================================================
        // Modifiers
        // ========================================================================

        /**
         * @brief Destroy the stored value if present
         */
        void reset() {
            if (set) {
                value().~T();
                set = false;
            }
        }

        /**
         * @brief Check if the optional contains a value
         * @return true if has value, false otherwise
         */
        bool has_value() const { return set; }

        // ========================================================================
        // Internal Accessors
        // ========================================================================

        /**
         * @brief Get pointer to the underlying storage (non-const)
         * @return Pointer to the storage
         */
        T* ptr() {
            return std::launder(reinterpret_cast<T*>(&optionalValue));
        }

        /**
         * @brief Get pointer to the underlying storage (const)
         * @return Const pointer to the storage
         */
        const T* ptr() const {
            return std::launder(reinterpret_cast<const T*>(&optionalValue));
        }

    private:
        // ========================================================================
        // Private Members
        // ========================================================================

        std::aligned_storage_t<sizeof(T), alignof(T)> optionalValue;  ///< Raw storage for the value
        bool set = false;                                               ///< Whether a value is stored
    };

} // namespace GCore
#ifndef CLOASTR_HPP
#define CLOASTR_HPP

// based

constexpr unsigned long long djb2_hash( const char* input )
{
    return *input ? static_cast< unsigned long long >( *input ) + 33 * djb2_hash( input + 1 ) : 5381;
}

constexpr unsigned long long prng( unsigned long long seed, unsigned int index )
{
    return ( seed ^ ( static_cast< unsigned long long >( index ) * 0x45d9f3b ) ) * 0x27d4eb2d % 0xffffffff;
}

enum class clom
{
    xoR,
    roT
};

template <unsigned long long uid, size_t N, typename T, clom mode>
class cloastr_impl
{
public:
    constexpr cloastr_impl( const T* str )
    {
        for ( size_t i = 0; i < N; ++i )
        {
            if constexpr ( mode == clom::xoR )
            {
                data[ i ] = str[ i ] ^ static_cast< T >( prng( uid, i ) & 0xFF );
            }
            else if constexpr ( mode == clom::roT )
            {
                data[ i ] = static_cast< T >( str[ i ] + ( prng( uid, i ) % 26 ) );
            }
        }
    }

    constexpr T* decrypt( ) const
    {
        for ( size_t i = 0; i < N; ++i )
        {
            if constexpr ( mode == clom::xoR )
            {
                decrypted_data[ i ] = data[ i ] ^ static_cast< T >( prng( uid, i ) & 0xFF );
            }
            else if constexpr ( mode == clom::roT )
            {
                decrypted_data[ i ] = static_cast< T >( data[ i ] - ( prng( uid, i ) % 26 ) );
            }
        }
        return decrypted_data;
    }

    constexpr void clear( )
    {
        for ( size_t i = 0; i < N; ++i )
        {
            data[ i ] = 0;
            decrypted_data[ i ] = 0;
        }
    }

private:
    T data[ N ]{};
    mutable T decrypted_data[ N ]{};
};

#define cloastr(str, mode) []() { \
    constexpr static auto const_str = cloastr_impl< \
        djb2_hash(__DATE__ __TIME__) + __COUNTER__ * __COUNTER__, \
        sizeof(str) / sizeof(str[0]), \
        std::remove_const_t<std::remove_reference_t<decltype(str[0])>>, \
        mode>((std::remove_const_t<std::remove_reference_t<decltype(str[0])>>*)str); \
    return const_str; }()

#endif // !CLOASTR_HPP

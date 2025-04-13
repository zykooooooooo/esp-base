#pragma once
#include <src/cache/index.h>
#include <algorithm>
#include <d3d9types.h>
#include <numbers>
#include <thirdparty/memory/memory.h>
#include "offsets.h"

namespace numerics {

	inline int screen_width = GetSystemMetrics( 0 );
	inline int screen_height = GetSystemMetrics( 1 );
	inline int screen_width_center = screen_width / 2;
	inline int screen_height_center = screen_height / 2;
	inline float aspect_ratio = static_cast< float >( screen_width ) / screen_height;

	//class fname
	//{
	//public:
	//	int32_t ComparisonIndex;

	//	std::string ToString( )
	//	{
	//		return ToString( ComparisonIndex );
	//	}

	//	static std::string ToString( int32_t index )
	//	{
	//		int32_t DecryptedIndex = DecryptIndex( index );
	//		uint64_t NamePoolChunk = read<uint64_t>( target_process_t.process_base + ( 0x1719F7C0 + 8 * ( DecryptedIndex >> 16 ) + 16 ) ) + 2 * ( uint16_t ) DecryptedIndex;
	//		uint16_t Pool = read<uint16_t>( NamePoolChunk );

	//		if ( ( ( Pool ^ 0x1980 ) & 0x7FE0 ) <= 0 )
	//		{
	//			DecryptedIndex = DecryptIndex( read<int32_t>( NamePoolChunk + 6 ) );
	//			NamePoolChunk = read<uint64_t>( target_process_t.process_base + ( 0x1719F7C0 + 8 * ( DecryptedIndex >> 16 ) + 16 ) ) + 2 * ( uint16_t ) DecryptedIndex;
	//			Pool = read<uint16_t>( NamePoolChunk );
	//		}

	//		int32_t Length = ( ( ( Pool ^ 0x1980u ) >> 5 ) & 0x3FF ) * ( ( Pool & 0x8000u ) == 0 ? 1 : 2 );

	//		char* NameBuffer = new char [ Length + 1 ];
	//		read_physical( ( NamePoolChunk + 2 ) , NameBuffer , Length );
	//		DecryptFName( NameBuffer , Length );
	//		return std::string( NameBuffer );
	//	}

	//	static int32_t DecryptIndex( int32_t index )
	//	{
	//		if ( index )
	//		{
	//			int32_t DecryptedIndex = ( ( uint32_t( index - 1 ) >> 1 ) | ( uint32_t( index - 1 ) << 31 ) ) + 0x156B90C9;
	//			return DecryptedIndex ? DecryptedIndex : 0x156B90C8;
	//		}

	//		return 0;
	//	}

	//	static void DecryptFName( char* buffer , int length )
	//	{
	//		if ( length )
	//		{
	//			uint8_t* EncryptedBuffer = new uint8_t [ length ];
	//			memcpy( EncryptedBuffer , buffer , length );

	//			int v7 = ( 16 * length ) ^ ( 8978 * length + 19717748 );
	//			for ( int i = 0; i < length; i++ ) {
	//				v7 = ( 16 * v7 ) ^ ( 8978 * v7 + 19717748 );
	//				buffer [ length - 1 - i ] = v7 - 50 + ( ( EncryptedBuffer [ i ] >> 1 ) | ( EncryptedBuffer [ i ] << 7 ) );
	//			}

	//			delete[ ] EncryptedBuffer;
	//		}

	//		buffer [ length ] = '\0';
	//	}
	//};

	class fvector {
	public:
		double x = 0.0 , y = 0.0 , z = 0.0;

		fvector( ) = default;
		fvector( double _x , double _y , double _z ) : x( _x ) , y( _y ) , z( _z ) { }

		fvector operator+( const fvector& v ) const { return { x + v.x, y + v.y, z + v.z }; }
		fvector operator-( const fvector& v ) const { return { x - v.x, y - v.y, z - v.z }; }
		fvector operator*( double scalar ) const { return { x * scalar, y * scalar, z * scalar }; }
		fvector operator/( double scalar ) const { return { x / scalar, y / scalar, z / scalar }; }

		fvector& operator*=( double scalar ) { x *= scalar; y *= scalar; z *= scalar; return *this; }
		fvector& operator+=( const fvector& v ) { x += v.x; y += v.y; z += v.z; return *this; }
		fvector& operator-=( const fvector& v ) { x -= v.x; y -= v.y; z -= v.z; return *this; }

		bool operator==( const fvector& v ) const { return x == v.x && y == v.y && z == v.z; }
		bool operator!=( const fvector& v ) const { return !( *this == v ); }

		double dot( const fvector& v ) const { return x * v.x + y * v.y + z * v.z; }
		double distance( const fvector& v ) const { return ( *this - v ).length( ); }
		double length( ) const { return std::sqrt( x * x + y * y + z * z ); }

		void add_scale( const fvector& v , float scale )
		{
			x += v.x * scale; y += v.y * scale; z += v.z * scale;
		}
	};

	struct FFortWeaponRampingData
	{
	public:
		bool bIsRampingWeapon; // 0x0 (Size: 0x1)
		float MaxRampStacks; // 0x8 (Size: 0x28)
		float RampFireRateToAdd; // 0x30 (Size: 0x28)
		float RampGraceDuration; // 0x58 (Size: 0x28)
	};

	class fvector2d {
	public:
		double x = 0.0 , y = 0.0;

		fvector2d( ) = default;
		fvector2d( double _x , double _y ) : x( _x ) , y( _y ) { }

		fvector2d operator+( const fvector2d& v ) const { return { x + v.x, y + v.y }; }
		fvector2d operator-( const fvector2d& v ) const { return { x - v.x, y - v.y }; }
		fvector2d operator*( double scalar ) const { return { x * scalar, y * scalar }; }
		fvector2d operator/( double scalar ) const { return { x / scalar, y / scalar }; }

		fvector2d& operator*=( double scalar ) { x *= scalar; y *= scalar; return *this; }
		fvector2d& operator+=( const fvector2d& v ) { x += v.x; y += v.y; return *this; }
		fvector2d& operator-=( const fvector2d& v ) { x -= v.x; y -= v.y; return *this; }

		bool operator==( const fvector2d& v ) const { return x == v.x && y == v.y; }
		bool operator!=( const fvector2d& v ) const { return !( *this == v ); }

		double dot( const fvector2d& v ) const { return x * v.x + y * v.y; }
		double distance( const fvector2d& v ) const { return std::sqrt( ( v.x - x ) * ( v.x - x ) + ( v.y - y ) * ( v.y - y ) ); }
		double length( ) const { return std::sqrt( x * x + y * y ); }

		static fvector2d from_angle( double angle , double magnitude = 1.0f )
		{
			return fvector2d( cos( angle ) * magnitude , sin( angle ) * magnitude );
		}
	};

	class frotator {
	public:
		double pitch = 0.0 , yaw = 0.0 , roll = 0.0;

		frotator( ) = default;
		frotator( double pitch , double yaw , double roll ) : pitch( pitch ) , yaw( yaw ) , roll( roll ) { }

		frotator operator+( const frotator& r ) const { return { pitch + r.pitch, yaw + r.yaw, roll + r.roll }; }
		frotator operator-( const frotator& r ) const { return { pitch - r.pitch, yaw - r.yaw, roll - r.roll }; }
		frotator operator*( double scalar ) const { return { pitch * scalar, yaw * scalar, roll * scalar }; }
		frotator operator/( double scalar ) const { return { pitch / scalar, yaw / scalar, roll / scalar }; }

		frotator& operator*=( double scalar ) { pitch *= scalar; yaw *= scalar; roll *= scalar; return *this; }
		frotator& operator+=( const frotator& r ) { pitch += r.pitch; yaw += r.yaw; roll += r.roll; return *this; }
		frotator& operator-=( const frotator& r ) { pitch -= r.pitch; yaw -= r.yaw; roll -= r.roll; return *this; }

		bool operator==( const frotator& r ) const { return pitch == r.pitch && yaw == r.yaw && roll == r.roll; }
		bool operator!=( const frotator& r ) const { return !( *this == r ); }

		double dot( const frotator& r ) const { return pitch * r.pitch + yaw * r.yaw + roll * r.roll; }
		double distance( const frotator& r ) const { return ( *this - r ).length( ); }
		double length( ) const { return std::sqrt( pitch * pitch + yaw * yaw + roll * roll ); }

		static frotator find_rotation( const fvector& start , const fvector& target )
		{
			fvector dir = ( target - start ) / ( target - start ).length( );
			return {
				std::atan2( dir.z, std::sqrt( dir.x * dir.x + dir.y * dir.y ) ) * ( 180.0 / std::numbers::pi ),
				std::atan2( dir.y, dir.x ) * ( 180.0 / std::numbers::pi ),
				0.0
			};
		}

		static double clamp_angle( double value , double min , double max )
		{
			return std::clamp( value , min , max );
		}

		static frotator clamp_rotation( const frotator& start , const frotator& end , double scale_pitch , double scale_yaw )
		{
			frotator delta = end - start;

			delta.yaw = std::fmod( delta.yaw + 360.0 , 360.0 );
			if ( delta.yaw > 180.0 ) delta.yaw -= 360.0;

			delta.pitch = clamp_angle( delta.pitch , -74.0 , 74.0 );
			return {
				delta.pitch / scale_pitch + start.pitch,
				delta.yaw / scale_yaw + start.yaw,
				0.0
			};
		}

		static void normalize_rotation( frotator& in )
		{
			in.pitch = std::fmod( in.pitch + 180.0 , 360.0 ) - 180.0;
			in.yaw = std::fmod( in.yaw + 180.0 , 360.0 ) - 180.0;
			in.roll = std::fmod( in.roll + 180.0 , 360.0 ) - 180.0;
		}
	};

	struct fplane : fvector {
		double w = 0.0;
	};

	struct alignas( 16 ) matrix_elements {
		double m11 , m12 , m13 , m14;
		double m21 , m22 , m23 , m24;
		double m31 , m32 , m33 , m34;
		double m41 , m42 , m43 , m44;

		matrix_elements( ) : m11( 0 ) , m12( 0 ) , m13( 0 ) , m14( 0 ) ,
			m21( 0 ) , m22( 0 ) , m23( 0 ) , m24( 0 ) ,
			m31( 0 ) , m32( 0 ) , m33( 0 ) , m34( 0 ) ,
			m41( 0 ) , m42( 0 ) , m43( 0 ) , m44( 0 ) {
		}
	};

	struct alignas( 16 ) dbl_matrix {
		union {
			matrix_elements elements;
			double m [ 4 ][ 4 ];
		};

		dbl_matrix( ) : elements( ) { }

		double& operator()( size_t row , size_t col ) { return m [ row ][ col ]; }
		const double& operator()( size_t row , size_t col ) const { return m [ row ][ col ]; }
	};

	struct alignas( 16 ) fmatrix : public dbl_matrix {
		numerics::fplane x_plane;
		numerics::fplane y_plane;
		numerics::fplane z_plane;
		numerics::fplane w_plane;

		fmatrix( ) : dbl_matrix( ) , x_plane( ) , y_plane( ) , z_plane( ) , w_plane( ) { }
	};

	template< class t >
	class tarray
	{
	public:
		tarray( ) : data( ) , count( ) , max_count( ) { }
		tarray( t* data , uint32_t count , uint32_t max_count ) :data( data ) , count( count ) , max_count( max_count ) { }

		t get( uintptr_t idx )
		{
			return cmd::read< t >( reinterpret_cast< uintptr_t >( data ) + ( idx * sizeof( t ) ) );
		}

		std::vector<t> get_all( )
		{
			if ( count <= 0 || count > max_count )
			{
				return {};
			}

			try
			{
				std::vector<t> buffer( count );

				cmd::read_phy_mem_only(
					reinterpret_cast< PVOID >( data ) ,
					buffer.data( ) ,
					sizeof( t ) * count
				);

				return buffer;
			}
			catch ( const std::bad_alloc& )
			{
				return {};
			}
		}

		uintptr_t get_address( )
		{
			return reinterpret_cast< uintptr_t >( data );
		}

		uint32_t get_count( ) const
		{
			return count;
		};

		uint32_t get_max_count( ) const
		{
			return max_count;
		};

		bool is_valid( ) const
		{
			return data != nullptr;
		};

		t& operator[]( int i )
		{
			return this->data [ i ];
		};

		t* data;
		uint32_t count;
		uint32_t max_count;
	};



} // namespace numerics

namespace matrix_operations {

	inline D3DMATRIX matrix_multiplication( const D3DMATRIX& matrix1 , const D3DMATRIX& matrix2 )
	{
		D3DMATRIX result{};

		result._11 = matrix1._11 * matrix2._11 + matrix1._12 * matrix2._21 + matrix1._13 * matrix2._31 + matrix1._14 * matrix2._41;
		result._12 = matrix1._11 * matrix2._12 + matrix1._12 * matrix2._22 + matrix1._13 * matrix2._32 + matrix1._14 * matrix2._42;
		result._13 = matrix1._11 * matrix2._13 + matrix1._12 * matrix2._23 + matrix1._13 * matrix2._33 + matrix1._14 * matrix2._43;
		result._14 = matrix1._11 * matrix2._14 + matrix1._12 * matrix2._24 + matrix1._13 * matrix2._34 + matrix1._14 * matrix2._44;

		result._21 = matrix1._21 * matrix2._11 + matrix1._22 * matrix2._21 + matrix1._23 * matrix2._31 + matrix1._24 * matrix2._41;
		result._22 = matrix1._21 * matrix2._12 + matrix1._22 * matrix2._22 + matrix1._23 * matrix2._32 + matrix1._24 * matrix2._42;
		result._23 = matrix1._21 * matrix2._13 + matrix1._22 * matrix2._23 + matrix1._23 * matrix2._33 + matrix1._24 * matrix2._43;
		result._24 = matrix1._21 * matrix2._14 + matrix1._22 * matrix2._24 + matrix1._23 * matrix2._34 + matrix1._24 * matrix2._44;

		result._31 = matrix1._31 * matrix2._11 + matrix1._32 * matrix2._21 + matrix1._33 * matrix2._31 + matrix1._34 * matrix2._41;
		result._32 = matrix1._31 * matrix2._12 + matrix1._32 * matrix2._22 + matrix1._33 * matrix2._32 + matrix1._34 * matrix2._42;
		result._33 = matrix1._31 * matrix2._13 + matrix1._32 * matrix2._23 + matrix1._33 * matrix2._33 + matrix1._34 * matrix2._43;
		result._34 = matrix1._31 * matrix2._14 + matrix1._32 * matrix2._24 + matrix1._33 * matrix2._34 + matrix1._34 * matrix2._44;

		result._41 = matrix1._41 * matrix2._11 + matrix1._42 * matrix2._21 + matrix1._43 * matrix2._31 + matrix1._44 * matrix2._41;
		result._42 = matrix1._41 * matrix2._12 + matrix1._42 * matrix2._22 + matrix1._43 * matrix2._32 + matrix1._44 * matrix2._42;
		result._43 = matrix1._41 * matrix2._13 + matrix1._42 * matrix2._23 + matrix1._43 * matrix2._33 + matrix1._44 * matrix2._43;
		result._44 = matrix1._41 * matrix2._14 + matrix1._42 * matrix2._24 + matrix1._43 * matrix2._34 + matrix1._44 * matrix2._44;

		return result;
	}

	inline D3DMATRIX create_rotation_matrix( const numerics::frotator& rotation )
	{
		auto rad_x = rotation.pitch * float( std::numbers::pi ) / 180.f;
		auto rad_y = rotation.yaw * float( std::numbers::pi ) / 180.f;
		auto rad_z = rotation.roll * float( std::numbers::pi ) / 180.f;

		auto sp = sinf( rad_x ) , cp = cosf( rad_x );
		auto sy = sinf( rad_y ) , cy = cosf( rad_y );
		auto sr = sinf( rad_z ) , cr = cosf( rad_z );

		D3DMATRIX matrix{};
		matrix.m [ 0 ][ 0 ] = cp * cy;
		matrix.m [ 0 ][ 1 ] = cp * sy;
		matrix.m [ 0 ][ 2 ] = sp;
		matrix.m [ 0 ][ 3 ] = 0.f;

		matrix.m [ 1 ][ 0 ] = sr * sp * cy - cr * sy;
		matrix.m [ 1 ][ 1 ] = sr * sp * sy + cr * cy;
		matrix.m [ 1 ][ 2 ] = -sr * cp;
		matrix.m [ 1 ][ 3 ] = 0.f;

		matrix.m [ 2 ][ 0 ] = -( cr * sp * cy + sr * sy );
		matrix.m [ 2 ][ 1 ] = cy * sr - cr * sp * sy;
		matrix.m [ 2 ][ 2 ] = cr * cp;
		matrix.m [ 2 ][ 3 ] = 0.f;

		matrix.m [ 3 ][ 0 ] = matrix.m [ 3 ][ 1 ] = matrix.m [ 3 ][ 2 ] = 0.0f;
		matrix.m [ 3 ][ 3 ] = 1.0f;

		return matrix;
	}

	struct ftransform
	{
		numerics::fplane rot;
		numerics::fvector translation;
		char pad_38 [ 4 ];
		numerics::fvector scale = { 1.0, 1.0, 1.0 };
		char pad_58 [ 4 ];

		inline D3DMATRIX to_matrix_with_scale( ) const
		{
			D3DMATRIX m{};
			m._41 = translation.x;
			m._42 = translation.y;
			m._43 = translation.z;

			auto x2 = rot.x + rot.x , y2 = rot.y + rot.y , z2 = rot.z + rot.z;
			auto xx2 = rot.x * x2 , yy2 = rot.y * y2 , zz2 = rot.z * z2;
			m._11 = ( 1.0f - ( yy2 + zz2 ) ) * scale.x;
			m._22 = ( 1.0f - ( xx2 + zz2 ) ) * scale.y;
			m._33 = ( 1.0f - ( xx2 + yy2 ) ) * scale.z;

			auto yz2 = rot.y * z2 , wx2 = rot.w * x2;
			m._32 = ( yz2 - wx2 ) * scale.z;
			m._23 = ( yz2 + wx2 ) * scale.y;

			auto xy2 = rot.x * y2 , wz2 = rot.w * z2;
			m._21 = ( xy2 - wz2 ) * scale.y;
			m._12 = ( xy2 + wz2 ) * scale.x;

			auto xz2 = rot.x * z2 , wy2 = rot.w * y2;
			m._31 = ( xz2 + wy2 ) * scale.z;
			m._13 = ( xz2 - wy2 ) * scale.x;

			m._14 = m._24 = m._34 = 0.0f;
			m._44 = 1.0f;

			return m;
		}
	};

} // namespace matrix_operations

namespace bones {

	//std::optional<std::pair<std::vector<matrix_operations::ftransform>, matrix_operations::ftransform>> get_bone_data( uintptr_t mesh )
	//{
	//	auto bone_array = read<containers::tarray<matrix_operations::ftransform>>( mesh + offsets::component_space_transforms_array );
	//	if ( !bone_array.is_valid( ) || bone_array.get_count( ) < 110 ) 
	//	{
	//		bone_array = read<containers::tarray<matrix_operations::ftransform>>( mesh + offsets::component_space_transforms_array + 0x10 );
	//	}

	//	if ( !bone_array.is_valid( ) || bone_array.get_count( ) == 0 ) 
	//	{
	//		return std::nullopt;
	//	}

	//	return std::optional{
	//		std::make_pair(
	//			bone_array.get_all( ),
	//			read<matrix_operations::ftransform>( mesh + offsets::component_to_world )
	//		)
	//	};
	//}

	//numerics::fvector get_bone_position( const std::pair<std::vector<matrix_operations::ftransform>, matrix_operations::ftransform>& bone_data, int bone_id )
	//{
	//	if ( bone_id < 0 || bone_id >= bone_data.first.size( ) )
	//	{
	//		return { 0.0f, 0.0f, 0.0f };
	//	}

	//	const auto& bone = bone_data.first[ bone_id ];
	//	const auto& component_to_world = bone_data.second;

	//	auto bone_matrix = matrix_operations::matrix_multiplication( bone.to_matrix_with_scale( ), component_to_world.to_matrix_with_scale( ) );
	//	return { bone_matrix._41, bone_matrix._42, bone_matrix._43 };
	//}


	inline numerics::fvector get_bone_position( uintptr_t mesh , int boneId ) {
		int32_t active_transforms = cmd::read<int32_t>( mesh + offsets::component_space_transforms_array + 0x48 ) * 0x10;
		uintptr_t bone_array_ptr = mesh + offsets::component_space_transforms_array + active_transforms;
		auto bone_array = cmd::read<numerics::tarray<matrix_operations::ftransform>>( bone_array_ptr );
		auto bone = bone_array.get( boneId );
		auto component_to_world = cmd::read<matrix_operations::ftransform>( mesh + offsets::component_to_world );

		auto bone_matrix = matrix_operations::matrix_multiplication( bone.to_matrix_with_scale( ) , component_to_world.to_matrix_with_scale( ) );
		return { bone_matrix._41, bone_matrix._42, bone_matrix._43 };
	}
}

namespace udata {

	struct world
	{
		uintptr_t gworld;
		uintptr_t owning_game_instance;
		uintptr_t local_player;
		uintptr_t player_controller;
		uintptr_t player_state;
		uintptr_t local_pawn;
		uintptr_t root_component;

		int team_id;

		uintptr_t game_state;
		std::vector<uintptr_t> player_array;
	};

	struct actor
	{
		uintptr_t player_state;
		uintptr_t pawn_private;
		uintptr_t mesh;

		int team_id;
		int kill_score;

		uintptr_t character_movement;
		uintptr_t current_weapon;

		numerics::fvector location;
		bool knocked;
		bool visibility;
	};

	typedef struct environment
	{
		uintptr_t actor;
		std::string name;
		bool is_pickup;
		float distance;
	} environment;
	inline std::vector<environment> inline environment_list;
	inline std::vector<environment> temp_environment_list;

	inline world world_t;
	inline std::vector<actor>( actor_t );

} // namespace udata

namespace camera {

	inline uintptr_t view_state = 0;

	inline numerics::fvector location{};
	inline numerics::frotator rotation{};
	inline float fov = 0.0f;

	inline void setup_camera( )
	{
		uintptr_t view_matrix = cmd::read<uintptr_t>( udata::world_t.local_player + 0xd0 );

		view_state = cmd::read<uintptr_t>( view_matrix + 0x8 );
	}

	inline void update_camera( )
	{
		if ( !view_state )
		{
			setup_camera( );
		}

		auto projection = cmd::read<numerics::fmatrix>( view_state + 0x940 );

		rotation.pitch = asin( projection.z_plane.w ) * 180.0f / std::numbers::pi;
		rotation.yaw = atan2( projection.y_plane.w , projection.x_plane.w ) * 180.0f / std::numbers::pi;
		rotation.roll = 0.0f;

		location.x = projection.m [ 3 ][ 0 ];
		location.y = projection.m [ 3 ][ 1 ];
		location.z = projection.m [ 3 ][ 2 ];

		auto fov_radians = 2.0f * atanf( 1.0f / static_cast< float >(cmd::read<double>( view_state + 0x740 ) ) );
		fov = fov_radians * 180.0f / std::numbers::pi;
	}
}

namespace world_to_screen {
	inline D3DMATRIX rotation_matrix;
	inline float inv_fov;

	inline numerics::fvector2d project_to_screen( const numerics::fvector& location )
	{
		auto& axis_x = rotation_matrix.m [ 0 ];
		auto& axis_y = rotation_matrix.m [ 1 ];
		auto& axis_z = rotation_matrix.m [ 2 ];

		auto delta = location - camera::location;

		auto transformed_x = delta.dot( numerics::fvector( axis_y [ 0 ] , axis_y [ 1 ] , axis_y [ 2 ] ) );
		auto transformed_y = delta.dot( numerics::fvector( axis_z [ 0 ] , axis_z [ 1 ] , axis_z [ 2 ] ) );
		auto transformed_z = max( delta.dot( numerics::fvector( axis_x [ 0 ] , axis_x [ 1 ] , axis_x [ 2 ] ) ) , 1.0f );

		auto screen_x = numerics::screen_width_center + transformed_x * ( numerics::screen_height_center / inv_fov ) / transformed_z;
		auto screen_y = numerics::screen_height_center - transformed_y * ( numerics::screen_height_center / inv_fov ) / transformed_z;

		return numerics::fvector2d( screen_x , screen_y );
	}

	inline bool is_within_screen_bounds( const numerics::fvector2d& screen_location )
	{
		return screen_location.x >= 0 && screen_location.x <= numerics::screen_width && screen_location.y >= 0 && screen_location.y <= numerics::screen_height;
	}

} // namespace world_to_screen

struct bounds
{
	double min_x , max_x , min_y , max_y;
};

namespace player {
	inline bounds get_player_bounds( uintptr_t mesh )
	{
		const std::vector<int> bone_indices = { 110, 71, 78, 72, 79, 83, 76, 9, 38, 33, 62 };
		std::vector<numerics::fvector2d> bone_screen_coords( bone_indices.size( ) );

		std::transform( bone_indices.begin( ) , bone_indices.end( ) , bone_screen_coords.begin( ) , [ & ] ( int index ) {
			return world_to_screen::project_to_screen( bones::get_bone_position( mesh , index ) );
			} );

		auto [min_x , max_x] = std::minmax_element( bone_screen_coords.begin( ) , bone_screen_coords.end( ) , [ ] ( const auto& a , const auto& b ) { return a.x < b.x; } );
		auto [min_y , max_y] = std::minmax_element( bone_screen_coords.begin( ) , bone_screen_coords.end( ) , [ ] ( const auto& a , const auto& b ) { return a.y < b.y; } );

		const auto box_height = max_y->y - min_y->y;
		const auto box_width = max_x->x - min_x->x;

		const auto width_offset = box_width * 0.175f;
		const auto height_offset_top = box_height * 0.125f;
		const auto height_offset_bottom = box_height * 0.05f;

		return {
			min_x->x - width_offset,
			max_x->x + width_offset,
			min_y->y - height_offset_top,
			max_y->y + height_offset_bottom
		};
	}
}
export module R3;

import <type_traits>;
import <concepts>;
import <iostream>;
import <fstream>;
import <cmath>;
import <numbers>;

// 3D real space
export namespace R3
{
	// arithmetic concept
	template<class T> concept arithmetic = std::is_arithmetic_v<T>;

	// coordinate systems tag
	struct cartesian_system {};
	struct cylindrical_system {};
	struct spherical_system {};

	// coordinates data structure
	template<std::floating_point T, class CoordinateSystemTag> struct coordinates
	{
		// type definitions
		using value_type = T;
		using coordinate_system_tag = CoordinateSystemTag;

		// constants
		static constexpr inline const value_type epsilon = std::numeric_limits<value_type>::epsilon();

		// members
		alignas(alignof(value_type)) value_type _1, _2, _3;

		// accessors

		// x getter
		constexpr value_type x() const
		{
			if constexpr (std::is_same_v<coordinate_system_tag, cartesian_system>)// _1 == x, _2 == y, _3 == z
				return _1;// x == x
			else if constexpr (std::is_same_v<coordinate_system_tag, cylindrical_system>)// _1 == rho, _2 == phi, _3 == z
				return _1 * std::cos(_2);// x = rho cos(phi)
			else if constexpr (std::is_same_v<coordinate_system_tag, spherical_system>)// _1 == r, _2 == theta, _3 == phi
				return _1 * std::sin(_2) * std::cos(_3);// x = r sin(theta) cos(phi)
		}

		// x setter
		constexpr void x(value_type x_v)
		{
			static_assert(std::is_same_v<coordinate_system_tag, cartesian_system>,
				"there is no x in non-cartesian coordinate systems for setting value.");
			_1 = x_v;
		}

		// y getter
		constexpr value_type y() const
		{
			if constexpr (std::is_same_v<coordinate_system_tag, cartesian_system>)// _1 == x, _2 == y, _3 == z
				return _2;// y == y
			else if constexpr (std::is_same_v<coordinate_system_tag, cylindrical_system>)// _1 == rho, _2 == phi, _3 == z
				return _1 * std::sin(_2);// x = rho sin(phi)
			else if constexpr (std::is_same_v<coordinate_system_tag, spherical_system>)// _1 == r, _2 == theta, _3 == phi
				return _1 * std::sin(_2) * std::sin(_3);// x = r sin(theta) sin(phi)
		}

		// y setter
		constexpr void y(value_type y_v)
		{
			static_assert(std::is_same_v<coordinate_system_tag, cartesian_system>,
				"there is no y in non-cartesian coordinate systems for setting value.");
			_2 = y_v;
		}

		// z getter
		constexpr value_type z() const
		{
			if constexpr (std::is_same_v<coordinate_system_tag, cartesian_system>)// _1 == x, _2 == y, _3 == z
				return _3;// z == z
			else if constexpr (std::is_same_v<coordinate_system_tag, cylindrical_system>)// _1 == rho, _2 == phi, _3 == z
				return _3;// z == z
			else if constexpr (std::is_same_v<coordinate_system_tag, spherical_system>)// _1 == r, _2 == theta, _3 == phi
				return _1 * std::cos(_2);// z = r cos(theta)
		}

		// z setter
		constexpr void z(value_type z_v)
		{
			static_assert(std::is_same_v<coordinate_system_tag, cartesian_system> || std::is_same_v<coordinate_system_tag, cylindrical_system>,
				"there is no z in spherical coordinate system for setting value.");
			_3 = z_v;
		}

		// rho getter
		constexpr value_type rho() const
		{
			if constexpr (std::is_same_v<coordinate_system_tag, cartesian_system>)// _1 == x, _2 == y, _3 == z
				return std::hypot(_1, _2);// rho = sqrt(x*x + y*y)
			else if constexpr (std::is_same_v<coordinate_system_tag, cylindrical_system>)// _1 == rho, _2 == phi, _3 == z
				return _1;// rho == rho
			else if constexpr (std::is_same_v<coordinate_system_tag, spherical_system>)// _1 == r, _2 == theta, _3 == phi
				return _1 * std::sin(_2);// rho = r sin(theta)
		}

		// rho setter
		constexpr void rho(value_type rho_v)
		{
			static_assert(std::is_same_v<coordinate_system_tag, cylindrical_system>,
				"there is no rho in non-cylindrical coordinate systems for setting value.");
			_1 = rho_v;
		}

		// phi getter
		constexpr value_type phi() const
		{
			if constexpr (std::is_same_v<coordinate_system_tag, cartesian_system>)// _1 == x, _2 == y, _3 == z
				return std::atan2(_2, _1);// phi = arctan(y/x)
			else if constexpr (std::is_same_v<coordinate_system_tag, cylindrical_system>)// _1 == rho, _2 == phi, _3 == z
				return _2;// phi == phi
			else if constexpr (std::is_same_v<coordinate_system_tag, spherical_system>)// _1 == r, _2 == theta, _3 == phi
				return _3;// phi = phi
		}

		// phi setter
		constexpr void phi(value_type phi_v)
		{
			static_assert(std::is_same_v<coordinate_system_tag, cylindrical_system> || std::is_same_v<coordinate_system_tag, spherical_system>,
				"there is no phi in cartesian coordinate system for setting value.");
			if constexpr (std::is_same_v<coordinate_system_tag, cylindrical_system>)// _1 == rho, _2 == phi, _3 == z
				_2 = phi_v;
			else if constexpr (std::is_same_v<coordinate_system_tag, spherical_system>)// _1 == r, _2 == theta, _3 == phi
				_3 = phi_v;
		}

		// r getter
		constexpr value_type r() const
		{
			if constexpr (std::is_same_v<coordinate_system_tag, cartesian_system>)// _1 == x, _2 == y, _3 == z
				return std::hypot(_1, _2, _3);// r = sqrt(x*x + y*y + z*z)
			else if constexpr (std::is_same_v<coordinate_system_tag, cylindrical_system>)// _1 == rho, _2 == phi, _3 == z
				return std::hypot(_1, _3);// r = sqrt(rho*rho + z*z)
			else if constexpr (std::is_same_v<coordinate_system_tag, spherical_system>)// _1 == r, _2 == theta, _3 == phi
				return _1;// r = r
		}

		// r setter
		constexpr void r(value_type r_v)
		{
			static_assert(std::is_same_v<coordinate_system_tag, spherical_system>,
				"there is no r in non-spherical coordinate systems for setting value.");
			_1 = r_v;
		}

		// theta getter
		constexpr value_type theta() const
		{
			if constexpr (std::is_same_v<coordinate_system_tag, cartesian_system>)// _1 == x, _2 == y, _3 == z
				return std::acos(_3 / std::hypot(_1, _2, _3));// theta = acos(z / sqrt(x*x + y*y + z*z))
			else if constexpr (std::is_same_v<coordinate_system_tag, cylindrical_system>)// _1 == rho, _2 == phi, _3 == z
				return std::atan2(_1, _3);// theta = arctan(rho / z)
			else if constexpr (std::is_same_v<coordinate_system_tag, spherical_system>)// _1 == r, _2 == theta, _3 == phi
				return _2;// theta = theta
		}

		// theta setter
		constexpr void theta(value_type theta_v)
		{
			static_assert(std::is_same_v<coordinate_system_tag, spherical_system>,
				"there is no theta in non-spherical coordinate systems for setting value.");
			_2 = theta_v;
		}

		// overloaded arithmetic/logical operators
		// overloaded equality/unequality operators
		constexpr bool operator==(const coordinates& rhs) const
		{
			return std::abs(_1 - rhs._1) < epsilon &&
				std::abs(_2 - rhs._2) < epsilon &&
				std::abs(_3 - rhs._3) < epsilon;
		}
		constexpr bool operator!=(const coordinates& rhs) const
		{
			return !(*this == rhs);
		}

		// overloaded element-wise addition operators
		constexpr coordinates operator+(const coordinates& rhs) const
		{
			return {
				_1 + rhs._1,
				_2 + rhs._2,
				_3 + rhs._3
			};
		}
		constexpr void operator+=(const coordinates& rhs)
		{
			_1 += rhs._1;
			_2 += rhs._2;
			_3 += rhs._3;
		}

		// overloaded element-wise subtraction operators
		constexpr coordinates operator-(const coordinates& rhs) const
		{
			return {
				_1 - rhs._1,
				_2 - rhs._2,
				_3 - rhs._3
			};
		}
		constexpr void operator-=(const coordinates& rhs)
		{
			_1 -= rhs._1;
			_2 -= rhs._2;
			_3 -= rhs._3;
		}

		// overloaded element-wise multiplication operators
		constexpr coordinates operator*(const coordinates& rhs) const
		{
			return {
				_1 * rhs._1,
				_2 * rhs._2,
				_3 * rhs._3
			};
		}
		constexpr void operator*=(const coordinates& rhs)
		{
			_1 *= rhs._1;
			_2 *= rhs._2;
			_3 *= rhs._3;
		}

		// overloaded scalar multiplication operators
		template<arithmetic S> constexpr coordinates operator*(S scalar) const
		{
			return {
				_1 * scalar,
				_2 * scalar,
				_3 * scalar
			};
		}
		template<arithmetic S> constexpr void operator*=(S scalar)
		{
			_1 *= scalar;
			_2 *= scalar;
			_3 *= scalar;
		}

		// overloaded scalar division operators
		template<arithmetic S> constexpr coordinates operator/(S scalar) const
		{
			auto multiplier = static_cast<value_type>(scalar);
			if (std::abs(multiplier) < epsilon)
				throw std::overflow_error("Division by zero");
			return { _1 / multiplier, _2 / multiplier, _3 / multiplier };
		}
		template<arithmetic S> constexpr void operator/=(S scalar)
		{
			auto multiplier = static_cast<value_type>(scalar);
			if (std::abs(multiplier) < epsilon)
				throw std::overflow_error("Division by zero");
			_1 /= multiplier;
			_2 /= multiplier;
			_3 /= multiplier;
		}

		// overloaded vectorial operators
		constexpr value_type dot(const coordinates& rhs) const
		{
			return _1 * rhs._1 + _2 * rhs._2 + _3 * rhs._3;
		}
		constexpr coordinates cross(const coordinates& rhs) const
		{
			return {
				_2 * rhs._3 - _3 * rhs._2,
				_3 * rhs._1 - _1 * rhs._3,
				_1 * rhs._2 - _2 * rhs._1
			};
		}

		// metrics
		// Minkowski metric
		constexpr value_type Minkowski_distance(const coordinates& rhs, T p) const
		{
			return std::pow(std::pow(std::abs(_1 - rhs._1), p) + std::pow(std::abs(_2 - rhs._2), p) + std::pow(std::abs(_3 - rhs._3), p), 1 / p);
		}
		constexpr value_type Minkowski_norm(value_type p) const
		{
			return std::pow(std::pow(std::abs(_1), p) + std::pow(std::abs(_2), p) + std::pow(std::abs(_3), p), 1 / p);
		}
		constexpr coordinates Minkowski_normalize(value_type p) const
		{
			const auto n = Minkowski_norm(p);
			if (n < epsilon)
				throw std::overflow_error("Division by zero");
			return *this / n;
		}
		constexpr void Minkowski_normalize(value_type p)
		{
			const auto n = Minkowski_norm(p);
			if (n < epsilon)
				throw std::overflow_error("Division by zero");
			_1 /= n;
			_2 /= n;
			_3 /= n;
		}
		constexpr coordinates Minkowski_direction(const coordinates& to, value_type p) const
		{
			return (to - *this).Minkowski_normalize(p);
		}

		// Manhattan metric (L1 norm)
		constexpr value_type Manhattan_distance(const coordinates& rhs) const
		{
			return std::abs(_1 - rhs._1) + std::abs(_2 - rhs._2) + std::abs(_3 - rhs._3);
		}
		constexpr value_type Manhattan_norm() const
		{
			return std::abs(_1) + std::abs(_2) + std::abs(_3);
		}
		constexpr coordinates Manhattan_normalize() const
		{
			const auto n = Manhattan_norm();
			if (n < epsilon)
				throw std::overflow_error("Division by zero");
			return *this / n;
		}
		constexpr void Manhattan_normalize()
		{
			const auto n = Manhattan_norm();
			if (n < epsilon)
				throw std::overflow_error("Division by zero");
			_1 /= n;
			_2 /= n;
			_3 /= n;
		}
		constexpr coordinates Manhattan_direction(const coordinates& to) const
		{
			return (to - *this).Manhattan_normalize();
		}

		// Euclidean metric (L2 norm)
		constexpr value_type Euclidean_distance(const coordinates& rhs) const
		{
			return std::sqrt(
				((_1 - rhs._1) * (_1 - rhs._1)) +
				((_2 - rhs._2) * (_2 - rhs._2)) +
				((_3 - rhs._3) * (_3 - rhs._3))
			);
		}
		constexpr value_type Euclidean_norm() const
		{
			return std::sqrt(_1 * _1 + _2 * _2 + _3 * _3);
		}
		constexpr coordinates Euclidean_normalize() const
		{
			const auto n = Euclidean_norm();
			if (n < epsilon)
				throw std::overflow_error("Division by zero");
			return *this / n;
		}
		constexpr void Euclidean_normalize()
		{
			const auto n = Euclidean_norm();
			if (n < epsilon)
				throw std::overflow_error("Division by zero");
			_1 /= n;
			_2 /= n;
			_3 /= n;
		}
		constexpr coordinates Euclidean_direction(const coordinates& to) const
		{
			return (to - *this).Euclidean_normalize();
		}
		constexpr value_type Cosine_similarity(const coordinates& rhs) const
		{
			return this->dot(rhs) / Euclidean_norm() * rhs.Euclidean_norm();
		}

		// Chebyshev metric (Linf norm)
		constexpr T Chebyshev_distance(const coordinates& rhs) const
		{
			return std::max({ std::abs(_1 - rhs._1), std::abs(_2 - rhs._2), std::abs(_3 - rhs._3) });
		}
		constexpr T Chebyshev_norm() const
		{
			return std::max({ std::abs(_1), std::abs(_2), std::abs(_3) });
		}
		constexpr coordinates Chebyshev_normalize() const
		{
			const auto n = Chebyshev_norm();
			if (n < epsilon)
				throw std::overflow_error("Division by zero");
			return *this / n;
		}
		constexpr void Chebyshev_normalize()
		{
			const auto n = Chebyshev_norm();
			if (n < epsilon)
				throw std::overflow_error("Division by zero");
			_1 /= n;
			_2 /= n;
			_3 /= n;
		}
		constexpr coordinates Chebyshev_direction(const coordinates& to)
		{
			return (to - *this).Chebyshev_normalize();
		}

		// converter methods
		constexpr coordinates<value_type, cartesian_system> to_cartesian_coordinates() const
		{
			return {
				x(),
				y(),
				z()
			};
		}
		constexpr coordinates<value_type, cylindrical_system> to_cylindrical_coordinates() const
		{
			return {
				rho(),
				phi(),
				z()
			};
		}
		constexpr coordinates<value_type, spherical_system> to_spherical_coordinates() const
		{
			return {
				r(),
				theta(),
				phi()
			};
		}

		// overloaded friend operators
		// overloaded oputput streaming operators
		friend constexpr std::ostream& operator<<(std::ostream& os, const coordinates& c)
		{
			os << '(' << c._1 << ", " << c._2 << ", " << c._3 << ')';
			return os;
		}
		friend constexpr std::ofstream& operator<<(std::ofstream& os, const coordinates& c)
		{
			os << '(' << c._1 << ", " << c._2 << ", " << c._3 << ')';
			return os;
		}

		template<arithmetic S> friend constexpr coordinates operator*(S scalar, const coordinates& rhs)
		{
			return rhs * scalar;
		}
		template<arithmetic S> friend constexpr coordinates operator/(S scalar, const coordinates& rhs)
		{
			if (rhs._1 < epsilon || rhs._2 < epsilon || rhs._3 < epsilon)
				throw std::overflow_error("Division by zero.");
			return {
				static_cast<value_type>(scalar) / rhs._1,
				static_cast<value_type>(scalar) / rhs._2,
				static_cast<value_type>(scalar) / rhs._3
			};
		}
	};
}
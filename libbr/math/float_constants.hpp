/**
 * @file
 * @brief Float constants
 * @author Bromine0x23
 * @since 2016/10/11
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TFloat >
struct FloatConstants {
	/**
	 * @brief 1/2
	 */
	constexpr static TFloat half = 0.5000000000000000000000000000000000000000E+00L;

	/**
	 * @brief 1/3
	 */
	constexpr static TFloat third = 0.3333333333333333333333333333333333333333E+00L;

	/**
	 * @brief 2/3
	 */
	constexpr static TFloat two_thirds = 0.6666666666666666666666666666666666666667E+00L;

	/**
	 * @brief 1/4
	 */
	constexpr static TFloat quarter = 0.2500000000000000000000000000000000000000E+00L;

	/**
	 * @brief 3/4
	 */
	constexpr static TFloat three_quarters = 0.7500000000000000000000000000000000000000E+00L;

	/**
	 * @brief 2^-2
	 */
	constexpr static TFloat root_two = 0.1414213562373095048801688724209698078569E+01L;

	/**
	 * @brief 2^-2 / 2 == 1 / 2^-2
	 */
	constexpr static TFloat half_root_two = 0.7071067811865475244008443621048490392848E+00L;

	/**
	 * @brief 3^-2
	 */
	constexpr static TFloat root_three = 0.1732050807568877293527446341505872366942E+01L;

	/**
	 * @brief e
	 */
	constexpr static TFloat e = 0.2718281828459045235360287471352662497757E+01L;

	/**
	 * @brief e^-2
	 */
	constexpr static TFloat root_e = 0.1648721270700128146848650787814163571653E+01L;

	/**
	 * @brief log_e(2)
	 */
	constexpr static TFloat ln_two = 0.6931471805599453094172321214581765680755E+00L;

	/**
	 * @brief log_2(e) == 1 / log_e(2)
	 */
	constexpr static TFloat lb_e = 0.1442695040888963407359924681001892137426E+01L;

	/**
	 * @brief log_e(log_e(2))
	 */
	constexpr static TFloat ln_ln_two = -0.3665129205816643270124391582326694694542E+00L;

	/**
	 * @brief log_e(10)
	 */
	constexpr static TFloat ln_ten = 0.2302585092994045684017991454684364207601E+01L;

	/**
	 * @brief log_10(e) == 1 / log_e(10)
	 */
	constexpr static TFloat lg_e = 0.4342944819032518276511289189166050822943E+00L;

	/**
	 * @brief π
	 */
	constexpr static TFloat pi = 0.3141592653589793238462643383279502884197E+01L;

	/**
	 * @brief π / 2
	 */
	constexpr static TFloat half_pi = 0.1570796326794896619231321691639751442098E+01L;

	/**
	 * @brief π / 3
	 */
	constexpr static TFloat third_pi = 0.1047197551196597746154214461093167628065E+01L;

	/**
	 * @brief 1 / π
	 */
	constexpr static TFloat one_div_pi = 0.3183098861837906715377675267450287240689E+00L;

	/**
	 * @brief 2 / π
	 */
	constexpr static TFloat two_div_pi = 0.6366197723675813430755350534900574481378E+00L;

	/**
	 * @brief π^-2
	 */
	constexpr static TFloat root_pi = 0.1772453850905516027298167483341145182797E+01L;

	/**
	 * @brief (π / 2)^-2
	 */
	constexpr static TFloat root_half_pi = 0.1253314137315500251207882642405522626503E+01L;

	/**
	 * @brief (2π)^-2
	 */
	constexpr static TFloat root_two_pi = 0.2506628274631000502415765284811045253006E+01L;

	/**
	 * @brief π^2
	 */
	constexpr static TFloat pi_sqr = 0.9869604401089358618834490999876151135313E+01L;

	/**
	 * @brief π^2 / 6 = ∑1/(n^2)
	 */
	constexpr static TFloat pi_sqr_div_six = 0.1644934066848226436472415166646025189218E+01L;

	/**
	 * @brief sin(1)
	 */
	constexpr static TFloat sin_one = 0.8414709848078965066525023216302989996225E+00L;

	/**
	 * @brief cos(1)
	 */
	constexpr static TFloat cos_one = 0.5403023058681397174009366074429766037323E+00L;

	/**
	 * @brief φ
	 */
	constexpr static TFloat phi = 0.1618033988749894848204586834365638117720E+01L;
};

} // namespace BR
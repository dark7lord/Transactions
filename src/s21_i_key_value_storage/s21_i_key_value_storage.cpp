#include "s21_i_key_value_storage.h"

namespace s21 {

	bool operator==(const Value& l, const Value& r) {
		return (
			(l.last_name == r.last_name || l.last_name == "-" || r.last_name == "-") &&
			(l.first_name == r.first_name || l.first_name == "-" || r.first_name == "-") &&
			(l.birth_year == r.birth_year || l.birth_year == "-" || r.birth_year == "-") &&
			(l.city == r.city || l.city == "-" || r.city == "-") &&
			(l.coins_number == r.coins_number || l.coins_number == "-" || r.coins_number == "-")
		);
	}

} // end of namespace s21


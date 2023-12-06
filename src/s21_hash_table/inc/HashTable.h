#ifndef S21_HASHTABLE
#define S21_HASHTABLE

#include "../../s21_i_key_value_storage/s21_i_key_value_storage.h"
#include <list>
#include <iostream>

namespace s21 {

	typedef std::size_t HashCode;

	class HashTable : IKeyValueStorage {
	public:

		/* HashTable. Defined in HashTable_core.cpp */
		HashTable();
		HashTable(const HashTable&);
		HashTable(HashTable&&) noexcept;
		HashTable& operator=(const HashTable&);
		HashTable& operator=(HashTable&&) noexcept;
		~HashTable();

		/* HashTable base functional. Defined in HashTable.cpp */
		void				set(const Key&, const Value&, TimeLimit=-1) override;
		const Value*		get(const Key&) const noexcept override;
		bool				exists(const Key&) const noexcept override;
		bool				del(const Key&) noexcept override;
		void				update(const Key&, const Value&) override;
		std::vector<Key>	keys() const noexcept override;
		void				rename(const Key&, const Key&) override;
		TimeLimit			ttl(const Key&) const noexcept override;
		std::vector<Key>	find(const Value&) const noexcept override;
		std::vector<Value>	showall(void) const noexcept override;
		void				upload(const std::string& filename) override;
		void				save(const std::string& filename) const override;

		/* Exceptions. Defined in Exceptions.cpp. */
		struct HashTableException;
		struct KeyException;

	private:

		/* HashTable configurations. Defined in HashTable_core.cpp. */
		static constexpr std::size_t    initialBucketCount_ = 4;
		static constexpr std::size_t    maximumCapacity_ = 1 << 30;
		static constexpr double         initialLoadFactor_ = 0.75f;
		static constexpr HashCode       hashSeed_ = 4;
		static HashCode					hashCode_(const Key&) noexcept;

		/* Key-Value pair and additional information to store in HashTable. */
		struct Node {
			HashCode    hash;
			Key			key;
			Value		val;
			TimeLimit   time;
		};

		/* HashTable private fields. Mechanism of nodes storage. Defined in HashTable_core.cpp. */
		std::vector<std::list<Node>>*	table_;
		std::size_t						currentBucketCount_;
		std::size_t						currentLoadCount_;

		HashCode    		indexFor_(HashCode) const noexcept;
		double      		currentLoadFactor_() const noexcept;
		void        		increaseTable_();

		/* Utility functions. Defined in utils.cpp. */
		friend std::list<Node>::iterator
		first_bigger_or_equal_hash(const HashCode& hash,
								   std::list<Node>& lst) noexcept;
		friend bool
		check_key_exists(const Key& key,
						 const HashCode& hash,
						 const std::list<Node>& lst,
						 std::list<Node>::iterator& first) noexcept;

	};

} // namespace s21

#endif // S21_HASHTABLE

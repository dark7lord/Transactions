#include "s21_key_value_storage.h"

namespase s21 {

    Value::Value() {}

    template<class T>
    void KeyValueStorage<T>::KeyValueStorage() {
        this -> _instance = T();
    }

    template<class T>
    void KeyValueStorage<T>::KeyValueStorage(KeyValueStorage& other) {
        this -> _instance = other._instance;
    }

    template<class T>
    void KeyValueStorage<T>::KeyValueStorage(KeyValueStorage&& other) {
        this -> _instance = other._instance;
    }

    template<class T>
    KeyValueStorage& KeyValueStorage<T>::KeyValueStorage& operator=(KeyValueStorage& other) {
        if (*this != other) {
            this -> _instance = other._instance;
        }
        return *this;
    }

    template<class T>
    KeyValueStorage& KeyValueStorage<T>::KeyValueStorage& operator=(KeyValueStorage&&) {
        if (*this != other) {
            this -> _instance = other._instance;
        }
        return *this;
    }

    template<class T>
    void KeyValueStorage<T>::~KeyValueStorage() {
        ~(this -> _instance);
    }


    template<class T>
    void KeyValueStorage<T>::set(Key k, Value v, TimeLimit t) {
        return (this -> _instance).set(k, v, t);
    }

    template<class T>
    Value KeyValueStorage<T>::get(Key k) {
        return (this -> _instance).get(k);
    }

    // bool KeyValueStorage::exists(Key) {

    // }

    // void KeyValueStorage::del(Key) {

    // }

    // std::array<Key> KeyValueStorage::keys(void) {

    // }

    // void KeyValueStorage::rename(Key, Key) {

    // }

    // TimeLimit KeyValueStorage::ttl(Key) {

    // }

    // std::array<Key> KeyValueStorage::find(Value) {

    // }

    // std::array<Value> KeyValueStorage::showall(void) {

    // }

    // void KeyValueStorage::upload(const std::string& filename) {

    // }

    // void KeyValueStorage::export(const std::string& filename) {

    // }

}


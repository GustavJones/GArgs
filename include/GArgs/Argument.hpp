#pragma once
#include <ostream>
#include <string>
#include <stdexcept>
#include <vector>

namespace GArgs {
class ArgumentKey {
private:
  std::string m_key;

public:
  ArgumentKey(const std::string &_key = "") : m_key(_key) {};
  ArgumentKey(ArgumentKey &&) = default;
  ArgumentKey(const ArgumentKey &) = default;
  ArgumentKey &operator=(ArgumentKey &&) = default;
  ArgumentKey &operator=(const ArgumentKey &) = default;
  ~ArgumentKey() = default;

  operator const std::string &() const { return GetKey(); }
  bool operator==(const ArgumentKey &_key) const { return _key.m_key == m_key; }
  bool operator!=(const ArgumentKey &_key) const { return _key.m_key != m_key; }

  [[nodiscard]]
  const std::string &GetKey() const { return m_key; }

  void SetKey(const std::string &_key) { m_key = _key; }
};

inline std::ostream &operator<<(std::ostream &_stream, const ArgumentKey &_key) {
  _stream << _key.GetKey();
  return _stream;
}

class ArgumentKeysContainer : private std::vector<ArgumentKey> {
public:
  ArgumentKeysContainer() = default;
  ArgumentKeysContainer(ArgumentKeysContainer &&) = default;
  ArgumentKeysContainer(const ArgumentKeysContainer &) = default;
  ArgumentKeysContainer &operator=(ArgumentKeysContainer &&) = default;
  ArgumentKeysContainer &operator=(const ArgumentKeysContainer &) = default;
  ~ArgumentKeysContainer() = default;

  [[nodiscard]]
  size_t Size() const { return std::vector<ArgumentKey>::size(); }
  void Erase(const size_t &_index) { std::vector<ArgumentKey>::erase(std::vector<ArgumentKey>::begin() + _index); }
  void Clear() { std::vector<ArgumentKey>::clear(); }
  void PushBack(const ArgumentKey &_x) { std::vector<ArgumentKey>::push_back(_x); }

  [[nodiscard]]
  ArgumentKey &operator[](const size_t &_n) { return std::vector<ArgumentKey>::operator[](_n); }
  
  [[nodiscard]]
  const ArgumentKey &operator[](const size_t &_n) const { return std::vector<ArgumentKey>::operator[](_n); }
};

class ArgumentValue {
private:
  std::string m_value;

public:
  ArgumentValue(const std::string &_value = "") : m_value(_value) {};
  ArgumentValue(ArgumentValue &&) = default;
  ArgumentValue(const ArgumentValue &) = default;
  ArgumentValue &operator=(ArgumentValue &&) = default;
  ArgumentValue &operator=(const ArgumentValue &) = default;
  ~ArgumentValue() = default;

  operator const std::string &() const { return GetValue(); }

  [[nodiscard]]
  const std::string &GetValue() const { return m_value; }
  void SetValue(const std::string &_value) { m_value = _value; }
};

inline std::ostream &operator<<(std::ostream &_stream, const ArgumentValue &_value) {
  _stream << _value.GetValue();
  return _stream;
}

class ArgumentValuesContainer : private std::vector<ArgumentValue> {
public:
  ArgumentValuesContainer() = default;
  ArgumentValuesContainer(ArgumentValuesContainer &&) = default;
  ArgumentValuesContainer(const ArgumentValuesContainer &) = default;
  ArgumentValuesContainer &operator=(ArgumentValuesContainer &&) = default;
  ArgumentValuesContainer &operator=(const ArgumentValuesContainer &) = default;
  ~ArgumentValuesContainer() = default;

  [[nodiscard]]
  size_t Size() const { return std::vector<ArgumentValue>::size(); }

  void Erase(const size_t &_index) { std::vector<ArgumentValue>::erase(std::vector<ArgumentValue>::begin() + _index); }
  void Clear() { std::vector<ArgumentValue>::clear(); }
  void PushBack(const ArgumentValue &_x) { std::vector<ArgumentValue>::push_back(_x); }

  [[nodiscard]]
  ArgumentValue &operator[](const size_t &_n) { return std::vector<ArgumentValue>::operator[](_n); }

  [[nodiscard]]
  const ArgumentValue &operator[](const size_t &_n) const { return std::vector<ArgumentValue>::operator[](_n); }

  [[nodiscard]]
  bool Has(const std::string &_value) const {
    for (size_t __valueIndex = 0; __valueIndex < std::vector<ArgumentValue>::size(); __valueIndex++) {
      if ((std::string)std::vector<ArgumentValue>::operator[](__valueIndex) == _value) {
        return true;
      }
    }

    return false;
  }
};

class ArgumentSlot {
private:
  std::string m_name;
  std::string m_description;
  std::string m_filter;
  size_t m_requiredAmount;
  size_t m_maxAmount;

  ArgumentKeysContainer m_keys;
  ArgumentValuesContainer m_values;

public:
  ArgumentSlot(const std::string &_name = "",
               const std::string &_description = "",
               const std::string &_filter = "",
               const size_t &_requiredAmount = 0, const size_t _maxAmount = 0)
      : m_name(_name), m_description(_description), m_filter(_filter),
        m_requiredAmount(_requiredAmount), m_maxAmount(_maxAmount), m_keys(),
        m_values() {};
  ArgumentSlot(ArgumentSlot &&) = default;
  ArgumentSlot(const ArgumentSlot &) = default;
  ArgumentSlot &operator=(ArgumentSlot &&) = default;
  ArgumentSlot &operator=(const ArgumentSlot &) = default;
  ~ArgumentSlot() = default;

  bool HasRequired() const {
    if (m_values.Size() >= m_requiredAmount) {
      return true;
    } else {
      return false;
    }
  }

  void AddKey(const ArgumentKey &_key) { m_keys.PushBack(_key); }
  void AddValue(const ArgumentValue &_value) { m_values.PushBack(_value); }
  void RemoveValue(const size_t &_index) { m_values.Erase(_index); }
  void ClearValues() { m_values.Clear(); }

  [[nodiscard]]
  const std::string &GetName() const { return m_name; };

  [[nodiscard]]
  const std::string &GetDescription() const { return m_description; };

  [[nodiscard]]
  const std::string &GetFilter() const { return m_filter; };

  [[nodiscard]]
  const size_t &GetRequiredAmount() const { return m_requiredAmount; };

  [[nodiscard]]
  const size_t &GetMaxAmount() const { return m_maxAmount; };

  [[nodiscard]]
  const ArgumentKeysContainer &GetArguments() const { return m_keys; }

  [[nodiscard]]
  const ArgumentValuesContainer &GetValues() const { return m_values; };

  [[nodiscard]]
  ArgumentValuesContainer &GetValues() { return m_values; };

  [[nodiscard]]
  size_t GetValuesAmount() const { return m_values.Size(); }

  void SetName(const std::string &_name) { m_name = _name; };
  void SetDescription(const std::string &_description) { m_description = _description; };
  void SetFilter(const std::string &_filter) { m_filter = _filter; };
  void SetRequiredAmount(const size_t &_requiredAmount) { m_requiredAmount = _requiredAmount; };
  void SetMaxAmount(const size_t &_maxAmount) { m_maxAmount = _maxAmount; };
};
} // namespace GArgs

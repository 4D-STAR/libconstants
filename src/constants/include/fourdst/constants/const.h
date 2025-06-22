/* ***********************************************************************
//
//   Copyright (C) 2025 -- The 4D-STAR Collaboration
//   File Author: Emily Boudreaux
//   Last Modified: March 17, 2025
//
//   libconstants is free software; you can use it and/or modify
//   it under the terms and restrictions the GNU General Library Public
//   License version 3 (GPLv3) as published by the Free Software Foundation.
//
//   libconstants is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU Library General Public License for more details.
//
//   You should have received a copy of the GNU Library General Public License
//   along with this software; if not, write to the Free Software
//   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
// *********************************************************************** */
#pragma once
#include <string>
#include <iostream>
#include <set>
#include <map>

namespace fourdst::constant {
/**
 * @brief Structure to hold a constant's details.
 */
struct Constant {
  const std::string name;         ///< Name of the constant
  const double value;             ///< Value of the constant
  const double uncertainty;       ///< Uncertainty in the constant's value
  const std::string unit;         ///< Unit of the constant
  const std::string reference;    ///< Reference for the constant's value

  /**
   * @brief Parameterized constructor.
   * @param name The name of the constant.
   * @param value The value of the constant.
   * @param uncertainty The uncertainty in the constant's value.
   * @param unit The unit of the constant.
   * @param reference The reference for the constant's value.
   */
  Constant(const std::string& name, const double value, const double uncertainty, const std::string& unit, const std::string& reference)
    : name(name), value(value), uncertainty(uncertainty), unit(unit), reference(reference) {}

  /**
   * @brief overload the << operator for pretty printing
   */
   friend std::ostream& operator<<(std::ostream& os, const Constant& c) {
     os << "<" << c.name << ": ";
     os << c.value << "±" << c.uncertainty << " ";
     os << c.unit << " (" << c.reference << ")>\n";
     return os;
   }
};

/**
 * @brief Class to manage a collection of constants.
 */
class Constants {
private:
  bool loaded_ = false; ///< Flag to indicate if constants are loaded
  const int col_widths_[6] = {25, 52, 20, 20, 17, 45}; // From the python script used to generate the constants file
  std::map<std::string, Constant> constants_; ///< Map to store constants by name

  /**
   * @brief Default constructor. Private to avoid direct instantiation
   */
  Constants();

  /**
   * @brief Load constants from the embedded header file.
   * @return True if loading was successful, false otherwise.
   */
  bool load();

  /**
   * @brief Initialize constants.
   * @return True if initialization was successful, false otherwise.
   */
  bool initialize();

  /**
   * @brief Trim leading and trailing whitespace from a string.
   * @param str The string to trim.
   * @return The trimmed string.
   */
  std::string trim(const std::string& str);

public:

  /**
   * @brief get instance of constants singleton
   * @return instance of constants
   */
  static Constants& getInstance() {
    static Constants instance;
    return instance;
  }

  /**
   * @brief Check if constants are loaded.
   * @return True if constants are loaded, false otherwise.
   */
  bool isLoaded() const { return loaded_; }

  /**
   * @brief Get a constant by key.
   * @param key The name of the constant to retrieve.
   * @return The constant associated with the given key.
   */
  Constant get(const std::string& key) const;

  /**
   * @brief Overloaded subscript operator to access constants by key.
   * @param key The name of the constant to retrieve.
   * @return The constant associated with the given key.
   * @throws std::out_of_range if the key is not found.
   */
  Constant operator[](const std::string& key) const;

  /**
   * @brief Check if a constant exists by key.
   * @param key The name of the constant to check.
   * @return True if the constant exists, false otherwise.
   */
  bool has(const std::string& key) const;

  /**
   * @brief Get a list of all constant keys.
   * @return A vector of all constant keys.
   */
  std::set<std::string> keys() const;

};

} // namespace fourdst::const


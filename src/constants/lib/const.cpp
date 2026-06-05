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
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <exception>


#include "fourdst/constants/const.h"
#include "embedded_constants.h" // Generated at build time by meson

namespace fourdst::constant {
    Constants::Constants() {
        loaded_ = initialize();
    }

    bool Constants::initialize() {
        return load();
    }

    Constant Constants::get(const std::string& name) const {
        auto it = constants_.find(name);
        if (it != constants_.end()) {
            return it->second;
        } else {
            throw std::out_of_range("Constant '" + name + "' not found.");
        }
    }

    Constant Constants::operator[](const std::string& name) const {
        return this->get(name);
    }

    bool Constants::has(const std::string& name) const {
        return constants_.find(name) != constants_.end();
    }

    std::set<std::string> Constants::keys() const {
        std::set<std::string> keys;
        for (const auto& pair : constants_) {
            keys.insert(pair.first);
        }
        return keys;
    }

    std::string Constants::trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t");
        return str.substr(first, last - first + 1);
    }

    bool Constants::load() {
        std::istringstream fileStream(embeddedConstants);

        std::string line;
        bool data_section = false;
        int line_count = 0;

        while (std::getline(fileStream, line)) {
            line_count++;

            // Detect start of data section (double divider line)
            if (!data_section) {
                if (line.find("Symbol") != std::string::npos) {  // Find header row
                    std::getline(fileStream, line);  // Skip dashed divider
                    std::getline(fileStream, line);  // Skip second dashed divider
                    data_section = true;
                }
                continue;
            }

            // Ensure the line is long enough to contain all fields
            if (line.length() < 125) continue;

            // Define exact column widths from Python script
            int start = 0;

            const std::string symbol       = trim(line.substr(start, col_widths_[0])); start += col_widths_[0];
            const std::string name         = trim(line.substr(start, col_widths_[1])); start += col_widths_[1];
            const std::string valueStr     = line.substr(start, col_widths_[2]); start += col_widths_[2];
            const std::string unit         = trim(line.substr(start, col_widths_[3])); start += col_widths_[3]; // Only trim the unit
            const std::string uncertaintyStr = line.substr(start, col_widths_[4]); start += col_widths_[4];
            const std::string reference    = trim(line.substr(start, col_widths_[5])); // Only trim reference

            // Convert numerical fields safely
            double value = 0.0, uncertainty = 0.0;
            try {
                value = std::stod(valueStr);
            } catch (...) {
                std::cerr << "Warning: Invalid value in line " << line_count << ": " << valueStr << std::endl;
            }
            try {
                uncertainty = std::stod(uncertaintyStr);
            } catch (...) {
                std::cerr << "Warning: Invalid uncertainty in line " << line_count << ": " << uncertaintyStr << std::endl;
            }

            // Store in map
            constants_.emplace(symbol, Constant{name, value, uncertainty, unit, reference});
        }
        loaded_ = true;
        return true;
    }
}

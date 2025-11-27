// Copyright 2025 kzw
#include "height.h"

#include <ostream>
#include <string>

namespace {
const double kInchesPerFoot = 12.0;
const double kCentimetersPerInch = 2.54;
const double kCentimetersPerMeter = 100.0;

double ToCentimeters(double value, const std::string& units) {
  if (units == "centimeters") {
    return value;
  } else if (units == "meters") {
    return value * kCentimetersPerMeter;
  } else if (units == "inches") {
    return value * kCentimetersPerInch;
  } else {  // feet
    return value * kInchesPerFoot * kCentimetersPerInch;
  }
}

double FromCentimeters(double value_cm, const std::string& units) {
  if (units == "centimeters") {
    return value_cm;
  } else if (units == "meters") {
    return value_cm / kCentimetersPerMeter;
  } else if (units == "inches") {
    return value_cm / kCentimetersPerInch;
  } else {  // feet
    return value_cm / (kInchesPerFoot * kCentimetersPerInch);
  }
}
}  // namespace

Height::Height(double value, const std::string& units) : value_(0.0),
                                                         units_("feet") {
  SetValue(value);
  if (!SetUnits(units)) {
    units_ = "feet";
  }
}

double Height::GetValue() const {
  return value_;
}

std::string Height::GetUnits() const {
  return units_;
}

bool Height::SetValue(double value) {
  if (value < 0.0) {
    return false;
  }
  value_ = value;
  return true;
}

bool Height::SetUnits(const std::string& units) {
  if (!ValidUnits(units)) {
    return false;
  }
  units_ = units;
  return true;
}

bool Height::ValidUnits(const std::string& units) {
  return units == "inches" || units == "feet" ||
         units == "centimeters" || units == "meters";
}

void Height::ConvertUnits(const std::string& new_units) {
  if (!ValidUnits(new_units) || new_units == units_) {
    return;
  }
  const double cm = ToCentimeters(value_, units_);
  value_ = FromCentimeters(cm, new_units);
  units_ = new_units;
}

std::ostream& operator<<(std::ostream& out, const Height& h) {
  out << h.value_ << ' ' << h.units_;
  return out;
}
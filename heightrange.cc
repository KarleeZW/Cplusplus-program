// Copyright 2025 kzw
#include "heightrange.h"

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
}  // namespace

double HeightRange::ValueInCentimeters(const Height& h) {
  return ToCentimeters(h.GetValue(), h.GetUnits());
}

HeightRange::HeightRange() : shortest_(0.0, "feet"), tallest_(0.0, "feet") {}

HeightRange::HeightRange(const Height& a, const Height& b)
    : shortest_(a), tallest_(b) {
  const double a_cm = ValueInCentimeters(a);
  const double b_cm = ValueInCentimeters(b);
  if (a_cm <= b_cm) {
    shortest_ = a;
    tallest_ = b;
  } else {
    shortest_ = b;
    tallest_ = a;
  }
}

Height HeightRange::GetShortest() const {
  return shortest_;
}

Height HeightRange::GetTallest() const {
  return tallest_;
}

void HeightRange::SetShortest(const Height& h) {
  const double h_cm = ValueInCentimeters(h);
  const double tall_cm = ValueInCentimeters(tallest_);
  if (h_cm <= tall_cm) {
    shortest_ = h;
  }
}

void HeightRange::SetTallest(const Height& h) {
  const double h_cm = ValueInCentimeters(h);
  const double short_cm = ValueInCentimeters(shortest_);
  if (h_cm >= short_cm) {
    tallest_ = h;
  }
}

bool HeightRange::InRange(const Height& h, bool inclusive) const {
  const double v = ValueInCentimeters(h);
  const double lo = ValueInCentimeters(shortest_);
  const double hi = ValueInCentimeters(tallest_);
  if (inclusive) {
    return v >= lo && v <= hi;
  } else {
    return v > lo && v < hi;
  }
}

Height HeightRange::Width() const {
  const double lo = ValueInCentimeters(shortest_);
  const double hi = ValueInCentimeters(tallest_);
  double diff_cm = hi - lo;
  if (diff_cm < 0) {
    diff_cm = 0;
  }
  Height result(diff_cm, "centimeters");
  result.ConvertUnits(tallest_.GetUnits());
  return result;
}
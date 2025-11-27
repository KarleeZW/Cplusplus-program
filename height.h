// Copyright 2025 kzw
#ifndef HEIGHT_H_
#define HEIGHT_H_

#include <iosfwd>
#include <string>

class Height {
 public:
  // Constructors
  explicit Height(double value = 0.0, const std::string& units = "feet");

  // Accessors
  double GetValue() const;
  std::string GetUnits() const;

  // Mutators
  bool SetValue(double value);
  bool SetUnits(const std::string& units);

  // Unit conversion
  void ConvertUnits(const std::string& new_units);

  // Stream insertion
  friend std::ostream& operator<<(std::ostream& out, const Height& h);

 private:
  double value_;
  std::string units_;

  // Helpers
  static bool ValidUnits(const std::string& units);
};

#endif  // HEIGHT_H_

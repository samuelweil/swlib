#pragma once

class TestClass {
 public:
  TestClass(int val) : _value(val) {}
  TestClass() : TestClass(1) {}

  int value() const { return _value; }

  TestClass& value(int new_val) {
    _value = new_val;
    return *this;
  }

 private:
  int _value;
};
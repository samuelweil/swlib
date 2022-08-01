#pragma once

class TestClass {
 public:
  TestClass(int val) : _value(val) {}
  TestClass() : TestClass(1) {}

  int value() const { return _value; }

 private:
  int _value;
};
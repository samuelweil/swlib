BUILD_DIR=build
TEST_EXE=$(BUILD_DIR)/test/unit_tests

# -- Dev Commands --

tests: $(TEST_EXE)
	cd $(BUILD_DIR) && ctest

clean:
	rm -rf $(BUILD_DIR)

# -- Helpers --

.PHONY: clean $(BUILD_DIR)

$(TEST_EXE): $(BUILD_DIR)
	make -C $(BUILD_DIR)

$(BUILD_DIR): CMakeLists.txt
	cmake -B $(BUILD_DIR) .
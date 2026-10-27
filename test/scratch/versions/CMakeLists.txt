define_example_program(test.scratch.versions main.cpp)

if(shwild_FOUND)

	target_link_libraries(test.scratch.versions
		shwild::core
	)
endif()

if(TARGET xTests::core)

	target_link_libraries(test.scratch.versions
		xTests::core
	)
endif()

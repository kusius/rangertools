#Copy assets if modified or new 
#(does not sync, i.e delete target asset if it has been deleted from source dir)
# file(COPY ${CMAKE_CURRENT_LIST_DIR}/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Copy ddls (not all needed for all configurations)
file(COPY ${CMAKE_CURRENT_LIST_DIR}/../thirdparty/bin/dll/glfw3.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
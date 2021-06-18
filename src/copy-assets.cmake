#Copy assets if modified or new 
#(does not sync, i.e delete target asset if it has been deleted from source dir)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/../assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
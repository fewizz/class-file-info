root=$(dirname `realpath ${BASH_SOURCE[0]}`)

mkdir -p ${root}/build

clang++ \
	-std=c++20 \
	-Wall -Wextra \
	-O3 \
	-march=native \
	-static \
	-nostdinc++ \
	-I ${root}/include/ \
	-I ${root}/../core/include \
	-I ${root}/../class-file/include \
	-I ${root}/../posix-wrapper/include \
	-o ${root}/build/class-file-info \
	${root}/src/class_file_info.cpp
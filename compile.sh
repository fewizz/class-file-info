root=$(dirname `realpath ${BASH_SOURCE[0]}`)

mkdir -p ${root}/build

declare -a additional_args

if [[ $OS != Windows_NT ]]; then
	additional_args+=(-fsanitize=undefined)
	additional_args+=(-fsanitize=memory)
	additional_args+=(-pthreads)
fi

clang++ \
	-std=c++20 \
	-Wall -Wextra \
	-nostdinc++ \
	-I ${root}/include/ \
	-I ${root}/../core/include \
	-I ${root}/../class-file/include \
	-I ${root}/../posix-wrapper/include \
	-o ${root}/build/class-file-info \
	${additional_args[@]} \
	${root}/src/class_file_info.cpp
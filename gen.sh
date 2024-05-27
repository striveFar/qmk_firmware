#!/bin/bash

# 检查参数是否为空
if [ -z "$1" ]; then
    echo "Usage: $0 <build_dir>"
    exit 1
fi

# 清空 cscope.files 文件
> cscope.files

# 遍历工程编译目录下的所有 .d 文件
for d_file in $(find "$1" -name "*.d"); do
    # 提取 .d 文件中的所有 .c、.h、.S 文件路径并去重排序，添加到 cscope.files 中
    grep -oP '\S+\.(c|h|S)(?= \\|$)' "$d_file" | sort -u | sed "s|^\./|$1/|" | xargs realpath -esq $([ -z "$KBUILD_ABS_SRCTREE" ] && echo --relative-to=.) >> cscope.files
done

# 再次对 cscope.files 进行去重排序
sort -u -o cscope.files cscope.files
cscope -bR -f cscope.out


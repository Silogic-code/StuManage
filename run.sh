#!/bin/bash

# run.sh - 学生成绩管理系统编译运行脚本
# Student Grade Management System - Build & Run Script
#
# 用法 Usage:
#   ./run.sh build    编译项目
#   ./run.sh run      编译并运行
#   ./run.sh clean    清理编译产物
#   ./run.sh help     显示帮助

set -e

PROJECT_NAME="stu_manage"
CXX="g++"
CXXFLAGS="-std=c++17 -I."
SOURCES="service/core/main.cpp service/utils/Stu_List.cpp service/data/Stu_Manage.cpp service/tools/System_Items.cpp"

print_help() {
    echo "========================================"
    echo "  学生成绩管理系统 / Build Script"
    echo "========================================"
    echo ""
    echo "用法 Usage: ./run.sh [command]"
    echo ""
    echo "命令 Commands:"
    echo "  build   编译项目 Compile the project"
    echo "  run     编译并运行 Compile and run"
    echo "  clean   清理编译产物 Clean build files"
    echo "  help    显示帮助 Show this help message"
    echo ""
    echo "示例 Example:"
    echo "  ./run.sh build"
    echo "  ./run.sh run"
    echo ""
}

case "${1:-run}" in
    build)
        echo "[INFO] 正在编译... / Compiling..."
        $CXX $CXXFLAGS $SOURCES -o $PROJECT_NAME
        echo "[OK] 编译成功！/ Build successful!"
        echo "     可执行文件: ./$PROJECT_NAME"
        ;;
    run)
        if [ ! -f "$PROJECT_NAME" ]; then
            echo "[INFO] 可执行文件不存在，先编译... / Executable not found, compiling first..."
            $CXX $CXXFLAGS $SOURCES -o $PROJECT_NAME
            echo "[OK] 编译成功！/ Build successful!"
        fi
        echo "[INFO] 运行程序 / Running..."
        echo "========================================"
        ./$PROJECT_NAME
        ;;
    clean)
        if [ -f "$PROJECT_NAME" ]; then
            rm -f $PROJECT_NAME
            echo "[OK] 已清理 / Cleaned."
        else
            echo "[INFO] 无需清理 / Nothing to clean."
        fi
        ;;
    help|--help|-h)
        print_help
        ;;
    *)
        echo "[ERROR] 未知命令: $1"
        print_help
        exit 1
        ;;
esac

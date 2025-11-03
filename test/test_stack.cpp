#include "Stack.h"
#include <gtest.h>

// Конструкторы
TEST(TStackTest, default_constructor_works) {
    TStack<int> stack;
    EXPECT_EQ(stack.GetLen(), 0); // Длина 0
    EXPECT_TRUE(stack.IsEmpty()); // Пустой стек
}

TEST(TStackTest, parameterized_constructor_sets_length) {
    TStack<int> stack(7);
    EXPECT_EQ(stack.GetLen(), 7); // Длина равна параметру
    EXPECT_TRUE(stack.IsEmpty()); // Стек пуст
}

TEST(TStackTest, parameterized_constructor_throws_on_negative_size) {
    EXPECT_THROW(TStack<int> stack(-5), std::invalid_argument); // Исключение при отрицательном размере
}

TEST(TStackTest, copy_constructor_creates_independent_stack) {
    TStack<int> stack1(4);
    stack1.Push(11);
    stack1.Push(22);
    TStack<int> stack2(stack1); // Копирование
    EXPECT_EQ(stack2.GetLen(), 4);
    EXPECT_FALSE(stack2.IsEmpty());
}

TEST(TStackTest, move_constructor_transfers_ownership) {
    TStack<int> stack1(3);
    stack1.Push(15);
    stack1.Push(25);
    TStack<int> stack2(std::move(stack1)); // Перемещение
    EXPECT_EQ(stack2.GetLen(), 3);
    EXPECT_FALSE(stack2.IsEmpty());
}

// Основные методы
TEST(TStackTest, push_and_pop_maintain_lifo) {
    TStack<int> stack(4);
    stack.Push(12);
    stack.Push(24);
    stack.Push(36);
    EXPECT_EQ(stack.Pop(), 36);
    EXPECT_EQ(stack.Pop(), 24);
    EXPECT_EQ(stack.Pop(), 12);
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStackTest, push_throws_when_stack_full) {
    TStack<int> stack(3);
    stack.Push(7);
    stack.Push(14);
    stack.Push(21);
    EXPECT_THROW(stack.Push(28), std::logic_error);
}

TEST(TStackTest, pop_throws_when_stack_empty) {
    TStack<int> stack;
    EXPECT_THROW(stack.Pop(), std::logic_error);
}

TEST(TStackTest, is_empty_and_is_full_return_correct_values) {
    TStack<int> stack(3);
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_FALSE(stack.isFull());
    stack.Push(5);
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_FALSE(stack.isFull());
    stack.Push(10);
    stack.Push(15);
    EXPECT_TRUE(stack.isFull());
}

// Операторы
TEST(TStackTest, assignment_operator_copies_stack) {
    TStack<int> stack1(4);
    stack1.Push(5);
    stack1.Push(10);
    TStack<int> stack2;
    stack2 = stack1;
    EXPECT_EQ(stack2.GetLen(), 4);
    EXPECT_FALSE(stack2.IsEmpty());
}

TEST(TStackTest, move_assignment_operator_moves_stack) {
    TStack<int> stack1(3);
    stack1.Push(8);
    stack1.Push(16);
    TStack<int> stack2;
    stack2 = std::move(stack1);
    EXPECT_EQ(stack2.GetLen(), 3);
    EXPECT_FALSE(stack2.IsEmpty());
}

TEST(TStackTest, equality_operator_checks_equal_stacks) {
    TStack<int> stack1(5);
    stack1.Push(3);
    stack1.Push(6);
    TStack<int> stack2(stack1);
    EXPECT_TRUE(stack1 == stack2);
    stack2.Pop();
    EXPECT_FALSE(stack1 == stack2);
}

TEST(TStackTest, inequality_operator_checks_different_stacks) {
    TStack<int> stack1(3);
    stack1.Push(2);
    TStack<int> stack2(3);
    stack2.Push(4);
    EXPECT_TRUE(stack1 != stack2);
}

// Поиск минимального элемента
TEST(TStackTest, find_min_returns_smallest_element) {
    TStack<int> stack(6);
    stack.Push(13);
    stack.Push(6);
    stack.Push(19);
    stack.Push(2);
    stack.Push(18);
    EXPECT_EQ(stack.FindMin(), 2);
}

TEST(TStackTest, find_min_throws_on_empty_stack) {
    TStack<int> stack;
    EXPECT_THROW(stack.FindMin(), std::logic_error);
}

TEST(TStackTest, find_min_single_element) {
    TStack<int> stack(1);
    stack.Push(99);
    EXPECT_EQ(stack.FindMin(), 99);
}

// Работа с файлами
TEST(TStackTest, save_and_load_to_file) {
    TStack<int> stack1(5);
    stack1.Push(101);
    stack1.Push(202);
    stack1.Push(303);
    stack1.SaveToFile("test_stack.txt");
    TStack<int> stack2;
    stack2.LoadFromFile("test_stack.txt");
    EXPECT_FALSE(stack2.IsEmpty());
    EXPECT_EQ(stack2.GetLen(), 3);
}

TEST(TStackTest, save_empty_stack_to_file) {
    TStack<int> stack1;
    stack1.SaveToFile("empty_stack.txt");
    TStack<int> stack2;
    stack2.LoadFromFile("empty_stack.txt");
    EXPECT_TRUE(stack2.IsEmpty());
}

TEST(TStackTest, load_from_non_existent_file_throws) {
    TStack<int> stack;
    EXPECT_THROW(stack.LoadFromFile("non_existent_file.txt"), std::runtime_error);
}

// Потоки

TEST(TStackTest, stream_input_operator_reads_stack) {
    std::stringstream ss;
    ss << "4 11 22 33 44";
    TStack<int> stack;
    ss >> stack;
    EXPECT_EQ(stack.GetLen(), 4);
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_EQ(stack.FindMin(), 11);
}

TEST(TStackTest, stream_output_operator_writes_stack) {
    TStack<int> stack(3);
    stack.Push(5);
    stack.Push(10);
    std::stringstream ss;
    ss << stack;
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("TStack"), std::string::npos);
}

// Самоприсваивание
TEST(TStackTest, self_assignment_does_not_break_stack) {
    TStack<int> stack(3);
    stack.Push(7);
    stack.Push(14);
    stack = stack;
    EXPECT_FALSE(stack.IsEmpty());
}

// Resize
TEST(TStackTest, resize_increases_stack_capacity) {
    TStack<int> stack(2);
    stack.Push(1);
    stack.Push(2);
    stack.Resize(4);
    EXPECT_EQ(stack.GetLen(), 4);
    EXPECT_FALSE(stack.IsEmpty());
    stack.Push(3);
    stack.Push(4);
    EXPECT_TRUE(stack.isFull());
}

TEST(TStackTest, resize_to_zero_clears_stack) {
    TStack<int> stack(3);
    stack.Push(1);
    stack.Push(2);
    stack.Resize(0);
    EXPECT_EQ(stack.GetLen(), 0);
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStackTest, resize_negative_throws) {
    TStack<int> stack;
    EXPECT_THROW(stack.Resize(-10), std::invalid_argument);
}

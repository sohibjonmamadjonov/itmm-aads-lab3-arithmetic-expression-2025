#include "texpressionanalyzer.h"

#include <gtest.h>

#include <gtest/gtest.h>
#include "texpressionanalyzer.h"

// Тест на создание анализатора
TEST(TExpressionAnalyzer, can_create_analyzer) {
    ASSERT_NO_THROW(TExpressionAnalyzer a);
}

// Тест на установку выражения
TEST(TExpressionAnalyzer, can_set_expression) {
    TExpressionAnalyzer a;
    std::string expr = "2 + 2";
    ASSERT_NO_THROW(a.SetExpression(expr));
}

// Тест на проверку пустого выражения
TEST(TExpressionAnalyzer, empty_expression_throws) {
    TExpressionAnalyzer a;
    a.SetExpression("");
    ASSERT_THROW(a.CheckSyntax(), std::invalid_argument);
}

// Тест на простую корректную арифметику
TEST(TExpressionAnalyzer, simple_addition_is_correct) {
    TExpressionAnalyzer a;
    a.SetExpression("2 + 3");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 5.0);
}

// Тест на сложение и вычитание
TEST(TExpressionAnalyzer, addition_and_subtraction_work) {
    TExpressionAnalyzer a;
    a.SetExpression("10 - 3 + 5");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 12.0);
}

// Тест на умножение и деление
TEST(TExpressionAnalyzer, multiplication_and_division_work) {
    TExpressionAnalyzer a;
    a.SetExpression("6 * 4 / 3");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 8.0);
}

// Тест на приоритет операций
TEST(TExpressionAnalyzer, operator_precedence_is_correct) {
    TExpressionAnalyzer a;
    a.SetExpression("2 + 3 * 4");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 14.0); // 2 + (3*4) = 14
}

// Тест на скобки
TEST(TExpressionAnalyzer, parentheses_change_order) {
    TExpressionAnalyzer a;
    a.SetExpression("(2 + 3) * 4");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 20.0); // (2+3)*4 = 20
}

// Тест на вложенные скобки
TEST(TExpressionAnalyzer, nested_parentheses_work) {
    TExpressionAnalyzer a;
    a.SetExpression("((2 + 3) * (4 - 1)) / 5");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 3.0); // ((5)*(3))/5 = 3
}

// Тест на отрицательные числа
TEST(TExpressionAnalyzer, negative_numbers_work) {
    TExpressionAnalyzer a;
    a.SetExpression("-5 + 10");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 5.0);
}

// Тест на десятичные дроби
TEST(TExpressionAnalyzer, decimal_numbers_work) {
    TExpressionAnalyzer a;
    a.SetExpression("3.14 + 2.86");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 6.0);
}

// Тест на пробелы в выражении
TEST(TExpressionAnalyzer, handles_spaces_correctly) {
    TExpressionAnalyzer a;
    a.SetExpression("  2   +   3   *   4  ");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 14.0);
}

// Тест на синтаксические ошибки - лишний оператор
TEST(TExpressionAnalyzer, detects_syntax_error_extra_operator) {
    TExpressionAnalyzer a;
    a.SetExpression("2 + + 3");
    EXPECT_FALSE(a.CheckSyntax());
}

// Тест на синтаксические ошибки - несогласованные скобки
TEST(TExpressionAnalyzer, detects_unmatched_parentheses) {
    TExpressionAnalyzer a;
    a.SetExpression("(2 + 3");
    EXPECT_FALSE(a.CheckSyntax());
}

// Тест на синтаксические ошибки - пустые скобки
TEST(TExpressionAnalyzer, detects_empty_parentheses) {
    TExpressionAnalyzer a;
    a.SetExpression("2 + ()");
    EXPECT_FALSE(a.CheckSyntax());
}

// Тест на деление на ноль
TEST(TExpressionAnalyzer, division_by_zero_throws) {
    TExpressionAnalyzer a;
    a.SetExpression("5 / 0");
    EXPECT_TRUE(a.CheckSyntax()); // Синтаксис корректен
    ASSERT_THROW(a.Calculate(), std::runtime_error);
}

// Тест на неизвестный оператор
TEST(TExpressionAnalyzer, detects_unknown_operator) {
    TExpressionAnalyzer a;
    a.SetExpression("2 ^ 3");
    EXPECT_FALSE(a.CheckSyntax());
}

// Тест на выражение с переменными (если поддерживается)
TEST(TExpressionAnalyzer, expression_with_variables_works) {
    TExpressionAnalyzer a;
    a.SetExpression("x + y");
    // Если переменные поддерживаются, должны быть методы для установки значений
    a.SetVariable("x", 2.0);
    a.SetVariable("y", 3.0);
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 5.0);
}

// Тест на отсутствие значения переменной
TEST(TExpressionAnalyzer, unset_variable_throws) {
    TExpressionAnalyzer a;
    a.SetExpression("x + 5");
    a.SetVariable("x", 2.0);
    // Если есть неинициализированная переменная
    a.SetExpression("x + y");
    EXPECT_TRUE(a.CheckSyntax());
    ASSERT_THROW(a.Calculate(), std::runtime_error);
}

// Тест на сложное выражение
TEST(TExpressionAnalyzer, complex_expression_works) {
    TExpressionAnalyzer a;
    a.SetExpression("(3.5 + 2.5) * (10 - 4) / 3.0");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 12.0); // 6 * 6 / 3 = 12
}

// Тест на многократное использование одного анализатора
TEST(TExpressionAnalyzer, reusable_analyzer) {
    TExpressionAnalyzer a;

    a.SetExpression("2 + 3");
    EXPECT_DOUBLE_EQ(a.Calculate(), 5.0);

    a.SetExpression("10 * 2");
    EXPECT_DOUBLE_EQ(a.Calculate(), 20.0);

    a.SetExpression("(1 + 2) * 3");
    EXPECT_DOUBLE_EQ(a.Calculate(), 9.0);
}

// Тест на получение постфиксной записи (если есть такой метод)
TEST(TExpressionAnalyzer, can_get_postfix_notation) {
    TExpressionAnalyzer a;
    a.SetExpression("2 + 3 * 4");
    EXPECT_TRUE(a.CheckSyntax());

    // Если есть метод GetPostfix()
    std::string postfix = a.GetPostfix();
    EXPECT_EQ(postfix, "2 3 4 * +");
}

// Тест на очистку состояния
TEST(TExpressionAnalyzer, clear_resets_state) {
    TExpressionAnalyzer a;
    a.SetExpression("2 + 3");
    a.Calculate();

    a.Clear();
    a.SetExpression("5 * 6");
    EXPECT_DOUBLE_EQ(a.Calculate(), 30.0);
}

// Стресс-тест: длинное выражение
TEST(TExpressionAnalyzer, long_expression_works) {
    TExpressionAnalyzer a;
    std::string expr = "1 + 2 - 3 + 4 - 5 + 6 - 7 + 8 - 9 + 10";
    a.SetExpression(expr);
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 7.0); // Результат вычислений
}

// Тест на порядок вычислений без скобок
TEST(TExpressionAnalyzer, left_to_right_for_same_precedence) {
    TExpressionAnalyzer a;
    a.SetExpression("10 - 3 - 2"); // Должно быть (10-3)-2 = 5
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 5.0);
}

// Тест на обработку очень больших чисел
TEST(TExpressionAnalyzer, handles_large_numbers) {
    TExpressionAnalyzer a;
    a.SetExpression("1000000 * 1000000");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 1e12);
}

// Тест на обработку очень маленьких чисел
TEST(TExpressionAnalyzer, handles_small_numbers) {
    TExpressionAnalyzer a;
    a.SetExpression("0.000001 + 0.000002");
    EXPECT_TRUE(a.CheckSyntax());
    EXPECT_DOUBLE_EQ(a.Calculate(), 0.000003);
}
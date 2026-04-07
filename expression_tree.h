#ifndef EXPRESSION_TREE_H_
#define EXPRESSION_TREE_H_


#include <memory>
#include <string>

// Базовый класс узла дерева выражения
class ExpressionNode {
public:
    virtual ~ExpressionNode() = default;
    // Вычисляет значение выражения для заданного x
    virtual int evaluate(int x) const = 0;
    // Преобразует дерево в инфиксную форму с избыточными скобками
    virtual std::string to_infix() const = 0;
    // Преобразует дерево в префиксную форму
    virtual std::string to_prefix() const = 0;
    // Преобразует дерево в постфиксную форму
    virtual std::string to_postfix() const = 0;
    // Выполняет преобразование A+x -> x+A
    virtual void transform() = 0;
};

// Класс узла для числа
class NumberNode : public ExpressionNode {
public:
    explicit NumberNode(int value);
    int evaluate(int x) const override;
    std::string to_infix() const override;
    std::string to_prefix() const override;
    std::string to_postfix() const override;
    void transform() override;

private:
    int value_;
};

// Класс узла для переменной x
class VariableNode : public ExpressionNode {
public:
    int evaluate(int x) const override;
    std::string to_infix() const override;
    std::string to_prefix() const override;
    std::string to_postfix() const override;
    void transform() override;
};

// Класс узла для бинарной операции
class BinaryOperationNode : public ExpressionNode {
public:
    BinaryOperationNode(char op,
        std::unique_ptr<ExpressionNode> left,
        std::unique_ptr<ExpressionNode> right);
    int evaluate(int x) const override;
    std::string to_infix() const override;
    std::string to_prefix() const override;
    std::string to_postfix() const override;
    void transform() override;

private:
    char op_;
    std::unique_ptr<ExpressionNode> left_;
    std::unique_ptr<ExpressionNode> right_;
};

// Парсер выражений
class ExpressionParser {
public:
    // Строит дерево выражения из инфиксной строки
    std::unique_ptr<ExpressionNode> parse(const std::string& expression);

private:
    size_t pos_;
    std::string expr_;

    // Парсит выражение с учётом приоритетов операций
    std::unique_ptr<ExpressionNode> parse_expression();
    // Парсит слагаемые (операции + и -)
    std::unique_ptr<ExpressionNode> parse_additive();
    // Парсит множители (операции *, /, %)
    std::unique_ptr<ExpressionNode> parse_multiplicative();
    // Парсит степени (операция ^)
    std::unique_ptr<ExpressionNode> parse_power();
    // Парсит первичные выражения (числа, переменные, скобки)
    std::unique_ptr<ExpressionNode> parse_primary();
};

#endif  // EXPRESSION_TREE_H_

#define  _CRT_SECURE_NO_WARNINGS

#include "Postfix.h"
#include "Stack.h"
#include "AppView.h"
#include <string.h>

void Postfix_showTokenAndStack(_this, currentToken);

struct _Postfix
{
	int		_maxNumberOfTokens;
	char*	_expression;
	int		_evaluatedValue;
	Stack*	_operandStack;
};

Postfix*	Postfix_new(int givenMaxNumberOfTokens) {
	Postfix* _this = NewObject(Postfix);
	_this->_maxNumberOfTokens = givenMaxNumberOfTokens;
	_this->_expression = NewVector(char, givenMaxNumberOfTokens);
	_this->_operandStack = Stack_new(givenMaxNumberOfTokens);
	return _this;
}

void Postfix_delete(Postfix* _this) {
	Stack_delete(_this->_operandStack);
	free(_this->_expression);
	free(_this);
}

void	Postfix_setExpression(Postfix* _this, char* anExpression) {
	strcpy(_this->_expression, anExpression);
}

Boolean	Postfix_evaluate(Postfix* _this) {
	int		operand, operand1, operand2, calculated;
	char	currentToken;
	int		i = 0;
	Stack_reset(_this->_operandStack);
	while (_this->_expression[i] != '\0') {
		currentToken = _this->_expression[i];
		if (currentToken >= '0' && currentToken <= '9') {
			// token is an operand. Push it into stack
			operand = (currentToken - '0');
			Stack_push(_this->_operandStack, operand);
		}
		else {	// The token is an operator
			if (currentToken == '+') {
				operand2 = Stack_pop(_this->_operandStack);
				operand1 = Stack_pop(_this->_operandStack);
				calculated = operand1 + operand2;
				Stack_push(_this->_operandStack, calculated);
			}
			else if (currentToken == '-') {
				operand2 = Stack_pop(_this->_operandStack);
				operand1 = Stack_pop(_this->_operandStack);
				calculated = operand1 - operand2;
				Stack_push(_this->_operandStack, calculated);
			}
			else if (currentToken == '*') {
				operand2 = Stack_pop(_this->_operandStack);
				operand1 = Stack_pop(_this->_operandStack);
				calculated = operand1 * operand2;
				Stack_push(_this->_operandStack, calculated);
			}
			else if (currentToken == '/') {
				operand2 = Stack_pop(_this->_operandStack);
				operand1 = Stack_pop(_this->_operandStack);
				calculated = operand1 / operand2;
				Stack_push(_this->_operandStack, calculated);
			}
			else if (currentToken == '%') {
				operand2 = Stack_pop(_this->_operandStack);
				operand1 = Stack_pop(_this->_operandStack);
				calculated = operand1 % operand2;
				Stack_push(_this->_operandStack, calculated);
			}
		}
		Postfix_showTokenAndStack(_this, currentToken);
		i++;
	}
	_this->_evaluatedValue = Stack_pop(_this->_operandStack);
	return TRUE;
}

int		Postfix_evaluatedValue(Postfix* _this) {
	return (_this->_evaluatedValue);
}

void Postfix_showTokenAndStack(Postfix* _this, char currentToken) {
	int stackElement;
	printf("%c : Stack ", currentToken);
	AppView_out_bottomOfStack();
	for (int i = 0; i < Stack_size(_this->_operandStack); i++) {
		stackElement = Stack_elementAt(_this->_operandStack, i);
		AppView_out_element(stackElement);
	}
	AppView_out_topOfStack();
	AppView_out_newLine();
}

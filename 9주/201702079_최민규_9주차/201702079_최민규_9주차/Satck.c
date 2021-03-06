#include "Stack.h"

#define DEFAULT_STACK_CAPACITY 5

struct _Stack
{
	int			_capacity;
	int			_top;
	Element*	_elements;		// 배열을 동적으로 할당한다.
};

Stack*	Stack_new() {
	Stack*_this;
	_this = NewObject(Stack);
	_this->_capacity = DEFAULT_STACK_CAPACITY - 1;
	_this->_elements = NewVector(Element, _this->_capacity);
	_this->_top = -1;
	return _this;
}

void	Stack_delete(Stack* _this) {
	free(_this->_elements);
	free(_this);
}

Boolean Stack_isEmpty(Stack* _this) {
	return ((_this->_top) < 0);
}

Boolean Stack_isFull(Stack* _this) {
	return ((_this->_top) == (_this->_capacity - 1));
}

int	Stack_size(Stack* _this) {
	return (_this->_top + 1);
}

Boolean Stack_push(Stack* _this, Element anElement) {
	if (!Stack_isFull(_this)) {
		_this->_top++;
		_this->_elements[_this->_top] = anElement;
		return TRUE;
	}
	else {
		return FALSE;	// Stack이 empty
	}
}

Element Stack_pop(Stack* _this) {
	Element poppedElement = _this->_elements[_this->_top];
	_this->_top--;
	return poppedElement;
}

Element Stack_topElement(Stack* _this) {
	return (_this->_elements[_this->_top]);
}

Element Stack_elementAt(Stack* _this, int anOrder) {
	return (_this->_elements[anOrder]);
}